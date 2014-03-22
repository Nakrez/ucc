#include <ast/pretty-printer.hh>

using namespace ucc;
using namespace ast;

PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ConstVisitor()
    , ostr_(ostr)
{}

PrettyPrinter::~PrettyPrinter()
{}

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

void PrettyPrinter::operator()(const NamedType& ast)
{
    ostr_ << ast.name_get();
}
