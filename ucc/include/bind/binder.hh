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

# include <misc/diagnostic-reporter.hh>
# include <misc/scope-map.hh>
# include <misc/symbol.hh>

# include <ast/default-visitor.hh>
# include <ast/decl.hh>
# include <ast/enum-decl.hh>
# include <ast/record-decl.hh>

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

                void scope_begin()
                {
                    scope_.scope_begin();
                    record_enum_.scope_begin();
                }

                void scope_end()
                {
                    scope_.scope_end();
                    record_enum_.scope_end();
                }

                virtual void operator()(ucc::ast::VarDecl& ast);
                virtual void operator()(ucc::ast::FunctionDecl& ast);
                virtual void operator()(ucc::ast::TypeDecl& ast);
                virtual void operator()(ucc::ast::RecordDecl& ast);
                virtual void operator()(ucc::ast::EnumDecl& ast);
                virtual void operator()(ucc::ast::EnumExprDecl& ast);

                virtual void operator()(ucc::ast::NamedType& ast);
                virtual void operator()(ucc::ast::RecordType& ast);
                virtual void operator()(ucc::ast::EnumType& ast);

                virtual void operator()(ucc::ast::VarExpr& ast);
                virtual void operator()(ucc::ast::EnumExpr& ast);

                virtual void operator()(ucc::ast::CompoundStmt& ast);
                virtual void operator()(ucc::ast::DoWhileStmt& ast);
                virtual void operator()(ucc::ast::WhileStmt& ast);
                virtual void operator()(ucc::ast::ForStmt& ast);
                virtual void operator()(ucc::ast::SwitchStmt& ast);
                virtual void operator()(ucc::ast::BreakStmt& ast);
                virtual void operator()(ucc::ast::ContinueStmt& ast);

            protected:
                void error(const ucc::ast::Ast& ast, std::string msg);
                bool is_builtin_type(const ucc::misc::Symbol& s);

            protected:
                ucc::misc::ScopeMap<ucc::misc::Symbol, ucc::ast::Decl*> scope_;
                ucc::misc::ScopeMap<ucc::misc::Symbol,
                                    ucc::ast::Decl*> record_enum_;
                std::list<ucc::ast::Stmt*> loop_switch_;
        };
    } // namespace bind
} // namespace ucc

#endif /* !UCC_BIND_BINDER_HH */
