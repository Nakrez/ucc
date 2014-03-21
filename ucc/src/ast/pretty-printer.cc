#include <ast/pretty-printer.hh>

using namespace ucc;
using namespace ast;

PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ConstVisitor()
    , ostr_(ostr)
{}

PrettyPrinter::~PrettyPrinter()
{}
