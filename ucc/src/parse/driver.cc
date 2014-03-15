#include <parse/driver.hh>

using namespace ucc;
using namespace parse;

Driver::Driver()
    : trace_parser_(false)
    , trace_lexer_(false)
{}

Driver::~Driver()
{}

void Driver::parse_file(const std::string& name)
{
    file_ = name;

    lexer_begin();

    Parser parser(*this);
    parser.set_debug_level(trace_parser_);
    parser.parse();

    lexer_end();
}
