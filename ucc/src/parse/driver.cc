#include <parse/driver.hh>
#include <ucc.hh>

using namespace ucc;
using namespace parse;

Driver::Driver()
    : error_()
    , in_attribute_(false)
    , trace_parser_(ucc::parse::parse_trace)
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

const std::string& Driver::file_get() const
{
    return file_;
}
