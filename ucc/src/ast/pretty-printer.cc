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
    const PtrType* ptr_type;
    const FunctionType* fun_type;

    if (ast.is_static())
        ostr_ << "static ";
    else if (ast.is_extern())
        ostr_ << "extern ";

    if (ast.type_get())
    {
        ptr_type = dynamic_cast<const PtrType*>(ast.type_get());

        if (ptr_type)
        {
            fun_type = dynamic_cast<const FunctionType*>
                            (ptr_type->pointed_type_get());

            if (fun_type)
            {
                if (fun_type->return_type_get())
                    fun_type->return_type_get()->accept(*this);

                ostr_ << " (*" << ast.name_get() << ")";

                ostr_ << "(";

                auto it = fun_type->param_get().cbegin();
                auto begin = it;
                auto end = fun_type->param_get().cend();

                for (; it != end; ++it)
                {
                    if (it != begin)
                        ostr_ << ", ";

                    (*it)->accept(*this);
                }

                ostr_ << ")";

                return;
            }
        }

        ast.type_get()->accept(*this);
    }

    ostr_ << " " << ast.name_get();

    if (ast.init_get())
    {
        ostr_ << " = ";
        ast.init_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const TypeDecl& ast)
{
    const PtrType* ptr_type;
    const FunctionType* fun_type;

    ostr_ << "typedef ";

    if (ast.type_get())
    {
        ptr_type = dynamic_cast<const PtrType*>(ast.type_get());

        if (ptr_type)
        {
            fun_type = dynamic_cast<const FunctionType*>
                            (ptr_type->pointed_type_get());

            if (fun_type)
            {
                if (fun_type->return_type_get())
                    fun_type->return_type_get()->accept(*this);

                ostr_ << " (*" << ast.name_get() << ")";

                ostr_ << "(";

                auto it = fun_type->param_get().cbegin();
                auto begin = it;
                auto end = fun_type->param_get().cend();

                for (; it != end; ++it)
                {
                    if (it != begin)
                        ostr_ << ", ";

                    (*it)->accept(*this);
                }

                ostr_ << ")";

                return;
            }
        }

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

    ostr_ << " *";

    if (ast.is_const())
        ostr_ << " const";
    if (ast.is_restrict())
        ostr_ << " restrict";
}
