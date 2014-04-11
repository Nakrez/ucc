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

#ifndef UCC_BIND_BINDER_HH
# define UCC_BIND_BINDER_HH

# include <misc/error.hh>
# include <misc/scope-map.hh>
# include <misc/symbol.hh>

# include <ast/default-visitor.hh>
# include <ast/decl.hh>

namespace ucc
{
    namespace bind
    {
        class Binder : public ucc::ast::DefaultVisitor
        {
            public:
                using ucc::ast::DefaultVisitor::operator();

                Binder();
                virtual ~Binder();

                virtual void operator()(ucc::ast::VarDecl& ast);
                virtual void operator()(ucc::ast::FunctionDecl& ast);

                virtual void operator()(ucc::ast::VarExpr& ast);

                virtual void operator()(ucc::ast::CompoundStmt& ast);

                ucc::misc::Error& error_get();

            protected:
                void error(const ucc::ast::Ast& ast, std::string msg);

            protected:
                ucc::misc::Error error_;

                ucc::misc::ScopeMap<ucc::misc::Symbol, ucc::ast::Decl> scope_;
        };
    } // namespace bind
} // namespace ucc

#endif /* !UCC_BIND_BINDER_HH */
