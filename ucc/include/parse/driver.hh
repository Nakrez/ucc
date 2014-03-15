#ifndef UCC_PARSE_DRIVER_HH
# define UCC_PARSE_DRIVER_HH

# include <string>

# include <parse/c-parser.hh>

# define YY_DECL                                        \
    ucc::parse::Parser::token_type yylex (             \
            ucc::parse::Parser::semantic_type* yylval,  \
            ucc::parse::Parser::location_type* yylloc,  \
            ucc::parse::Driver& driver)

YY_DECL;

namespace ucc
{
    namespace parse
    {
        class Driver
        {
            public:
                Driver();
                ~Driver();

                void parse_file(const std::string& name);

            private:
                void lexer_begin();
                void lexer_end();

            private:
                bool trace_parser_;
                bool trace_lexer_;

                std::string file_;
        };
    } // namespace parse
} // namespace ucc

#endif /* !UCC_PARSE_DRIVER_HH */
