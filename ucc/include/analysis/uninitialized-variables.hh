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

#ifndef UNINITIALIZED_VARIABLES_HH
# define UNINITIALIZED_VARIABLES_HH

# include <ast/default-visitor.hh>

namespace ucc
{
    namespace analysis
    {
        /// Check if a local variable is uninitialized when used
        class UninitializedVariables : public ast::DefaultVisitor
        {
            public:
                using ast::DefaultVisitor::operator();

                UninitializedVariables();
                virtual ~UninitializedVariables();

                void warn(const std::string& msg,
                          const ucmp::misc::location& loc);

                virtual void operator()(ast::FunctionDecl& ast);
                virtual void operator()(ast::VarDecl& ast);
                virtual void operator()(ast::VarExpr& ast);
                virtual void operator()(ast::AssignExpr& ast);

            private:
                bool in_function_;
        };
    } // namespace analysis
} // namespace ucc

#endif /* !UNINITIALIZED_VARIABLES_HH */
