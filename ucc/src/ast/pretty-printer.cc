#include <ast/pretty-printer.hh>
#include <misc/indent.hh>

using namespace ucc;
using namespace ast;

PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : DefaultConstVisitor()
    , ostr_(ostr)
{}

PrettyPrinter::~PrettyPrinter()
{}

void PrettyPrinter::operator()(const DeclList& ast)
{
    for (auto elem : ast.list_get())
    {
        elem->accept(*this);
        ostr_ << ";" << misc::iendl;
    }
}

void PrettyPrinter::operator()(const VarDecl& ast)
{
    if (ast.is_static())
        ostr_ << "static ";
    else if (ast.is_extern())
        ostr_ << "extern ";

    if (ast.type_get())
    {
        if (print_fun_ptr(ast.type_get(), ast.name_get()))
            return;

        ast.type_get()->accept(*this);
    }

    if (ast.name_get().data_get() != "" &&
        !dynamic_cast<const PtrType*> (ast.type_get()))
        ostr_ << " ";

    ostr_ << ast.name_get();

    if (ast.init_get())
    {
        ostr_ << " = ";
        ast.init_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const TypeDecl& ast)
{
    ostr_ << "typedef ";

    if (ast.type_get())
    {
        if (print_fun_ptr(ast.type_get(), ast.name_get()))
            return;

        ast.type_get()->accept(*this);
    }

    ostr_ << " " << ast.name_get();
}

void PrettyPrinter::operator()(const FunctionDecl& ast)
{
    auto it = ast.param_get().cbegin();
    auto begin = it;
    auto end = ast.param_get().cend();

    if (ast.return_type_get())
    {
        ast.return_type_get()->accept(*this);

        if (!dynamic_cast<const PtrType*>(ast.return_type_get()))
            ostr_ << " ";
    }

    ostr_ << ast.name_get();

    ostr_ << "(";

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ", ";

        (*it)->accept(*this);
    }

    ostr_ << ")";
}

void PrettyPrinter::operator()(const NamedType& ast)
{
    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";

    ostr_ << ast.name_get();
}

void PrettyPrinter::operator()(const PtrType& ast)
{
    if (ast.pointed_type_get())
        ast.pointed_type_get()->accept(*this);

    if (!dynamic_cast<const PtrType*>(ast.pointed_type_get()))
        ostr_ << " ";

    ostr_ << "*";

    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";
}

bool PrettyPrinter::print_fun_ptr(const Type* ast,
                                  const ucc::misc::Symbol& sym)
{
    const PtrType* ptr = dynamic_cast<const PtrType*> (ast);
    const PtrType* tmp = nullptr;
    const FunctionType* fn = nullptr;
    int ptr_nb = 1;

    if (ptr)
    {
        while (1)
        {
            tmp = dynamic_cast<const PtrType*> (ptr->pointed_type_get());

            if (!tmp)
                break;

            ++ptr_nb;
            ptr = tmp;
        }

        fn = dynamic_cast<const FunctionType*> (ptr->pointed_type_get());

        if (!fn)
            return false;

        if (fn->return_type_get())
            fn->return_type_get()->accept(*this);

        if (!dynamic_cast<const PtrType*>(fn->return_type_get()))
            ostr_ << " ";

        ostr_ << "(";

        for (int i = 0; i < ptr_nb; ++i)
            ostr_ << "*";

        ostr_ << sym << ")(";

        auto it = fn->param_get().cbegin();
        auto begin = it;
        auto end = fn->param_get().cend();

        for (; it != end; ++it)
        {
            if (it != begin)
                ostr_ << ", ";

            (*it)->accept(*this);
        }

        ostr_ << ")";

        return true;
    }

    return false;
}
