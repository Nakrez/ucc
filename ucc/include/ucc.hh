#ifndef UCC_HH
# define UCC_HH

# include <string>

# include <ast/all.hh>

namespace ucc
{
    extern std::string input_file;

    namespace parse
    {
        extern bool parse_trace;
    } // namespace parse

    namespace ast
    {
        extern Ast* the_ast;
    } // namespace ast
} // namespace ucc

#endif /* !UCC_HH */
