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

                /// \brief  Check type correctness on an assignment
                /// \param  loc The location of the assignment
                /// \param  op  The assignment operator
                /// \param  t1  The left expression type
                /// \param  t2  The right expression type
                void check_assign_types(const ucc::misc::location& loc,
                                        ast::AssignExpr::AssignOp op,
                                        const Type* t1, const Type* t2);

                virtual void operator()(ast::VarDecl& ast);
                virtual void operator()(ast::TypeDecl& ast);

                virtual void operator()(ast::NamedTy& ast);
                virtual void operator()(ast::PtrTy& ast);

                virtual void operator()(ast::IntExpr& e);
                virtual void operator()(ast::FloatExpr& e);
                virtual void operator()(ast::StringExpr& e);
                virtual void operator()(ast::VarExpr& ast);
        };
    } // namespace type
} // namespace ucc

#endif /* !UCC_TYPE_TYPE_CHECKER_HH */
