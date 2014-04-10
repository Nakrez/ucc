#include <ucc.hh>

namespace ucc
{
    std::string input_file = "-";

    namespace parse
    {
        bool parse_trace = false;
    } // namespace parse

    namespace ast
    {
        Ast* the_ast = nullptr;
    } // namespace ast
} // namespace ucc
