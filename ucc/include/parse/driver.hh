/*
Copyright (C) 2014 Baptiste Covolato <b.covolato@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef UCC_PARSE_DRIVER_HH
# define UCC_PARSE_DRIVER_HH

# include <map>
# include <string>

# include <misc/error.hh>

# include <parse/c-parser.hh>

# include <ast/fwd.hh>

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

                const std::string& file_get() const;

            public:
                ucc::misc::Error error_;
                bool in_attribute_;

                ucc::ast::DeclList* ast_;

                std::map<std::string, ucc::parse::Parser::token_type> sym_;

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
