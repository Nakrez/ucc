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
        ostr_ << misc::iendl;
    }
}

void PrettyPrinter::operator()(const VarDecl& ast)
{
    if (ast.is_static())
        ostr_ << "static ";
    else if (ast.is_extern())
        ostr_ << "extern ";

    if (ast.type_get())
        ast.type_get()->accept(*this);

    ostr_ << " " << ast.name_get();

    if (ast.init_get())
    {
        ostr_ << " = ";
        ast.init_get()->accept(*this);
    }

    ostr_ << ";";
}

void PrettyPrinter::operator()(const TypeDecl& ast)
{
    ostr_ << "typedef ";

    if (ast.type_get())
        ast.type_get()->accept(*this);

    ostr_ << " " << ast.name_get() << ";";
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

        if ((*it)->type_get())
            (*it)->type_get()->accept(*this);
        else
            ostr_ << "int";

        if ((*it)->name_get().data_get() != "")
            ostr_ << (*it)->name_get();
    }

    ostr_ << ");";
}

void PrettyPrinter::operator()(const NamedType& ast)
{
    ostr_ << ast.name_get();
}
