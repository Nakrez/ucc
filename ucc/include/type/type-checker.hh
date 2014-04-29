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

#ifndef UCC_TYPE_TYPE_CHECKER_HH
# define UCC_TYPE_TYPE_CHECKER_HH

# include <misc/error.hh>

# include <ast/default-visitor.hh>

namespace ucc
{
    namespace type
    {
        /// Check type consistency in an ast
        class TypeChecker : public ucc::ast::DefaultVisitor
        {
            public:
                using ucc::ast::DefaultVisitor::operator();

                /// Constructor
                TypeChecker();

                /// Destructor
                virtual ~TypeChecker();

                /// \brief  Return the type of an ast node.
                /// \param  a   The ast node you want to get the type
                const Type* node_type(ast::TypeUser& a);

                void error(const std::string& msg,
                           const ucc::misc::location& loc);

                /// \brief  Check type correctness on an assignment
                /// \param  loc The location of the assignment
                /// \param  t1  The left expression type
                /// \param  t2  The right expression type
                void check_assign_types(const ucc::misc::location& loc,
                                        const Type* t1, const Type* t2);

                /// \brief  Check type correctness on an operation
                /// \param  loc The location of the assignment
                /// \param  op  The operation operator
                /// \param  t1  The left expression type
                /// \param  t2  The right expression type
                void check_op_types(const ucc::misc::location& loc,
                                    ast::OpExpr::Op op,
                                    const Type* t1, const Type* t2);

                /// \brief  Return true if the Type @a t is scalar
                /// \param  t   The type you want to know if it is scalar
                /// \return true if the Type @a t is scalar, false otherwise
                bool is_scalar(const Type* t);

                virtual void operator()(ast::VarDecl& ast);
                virtual void operator()(ast::FunctionDecl& ast);
                virtual void operator()(ast::TypeDecl& ast);
                virtual void operator()(ast::RecordDecl& ast);

                virtual void operator()(ast::NamedTy& ast);
                virtual void operator()(ast::ArrayTy& ast);
                virtual void operator()(ast::FunctionTy& ast);
                virtual void operator()(ast::PtrTy& ast);
                virtual void operator()(ast::RecordTy& ast);

                virtual void operator()(ast::ReturnStmt& ast);
                virtual void operator()(ast::WhileStmt& ast);
                virtual void operator()(ast::DoWhileStmt& ast);
                virtual void operator()(ast::IfStmt& ast);
                virtual void operator()(ast::SwitchStmt& ast);
                virtual void operator()(ast::ForStmt& ast);

                virtual void operator()(ast::IntExpr& e);
                virtual void operator()(ast::FloatExpr& e);
                virtual void operator()(ast::StringExpr& e);
                virtual void operator()(ast::VarExpr& ast);
                virtual void operator()(ast::SubscriptExpr& ast);
                virtual void operator()(ast::CallExpr& ast);
                virtual void operator()(ast::UnaryExpr& ast);
                virtual void operator()(ast::MemberExpr& ast);
                virtual void operator()(ast::AssignExpr& ast);
                virtual void operator()(ast::OpExpr& ast);
                virtual void operator()(ast::CastExpr& ast);
                virtual void operator()(ast::SizeofExpr& ast);

            private:
                bool fun_param_;
                ast::FunctionDecl *declared_fun_;
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_TYPE_CHECKER_HH */
