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

#ifndef UCC_AST_FUNCTION_DECL_HH
# define UCC_AST_FUNCTION_DECL_HH

# include <list>

# include <ast/decl.hh>
# include <ast/function-ty.hh>
# include <ast/type-builder.hh>

namespace ucc
{
    namespace ast
    {
        class FunctionTy;

        /// Represent a function declaration in the ast
        class FunctionDecl : public Decl, public TypeBuilder
        {
            public:
                /// \brief  Constructor
                /// \param  loc     The location of the FunctionDecl
                /// \param  name    The name of the function
                /// \param  ty      The signature of the function
                FunctionDecl(const ucmp::misc::location& loc,
                             const ucmp::misc::Symbol& name,
                             FunctionTy* ty);

                /// \brief  Constructor
                /// \param  loc         The location of the FunctionDecl
                /// \param  name        The name of the function
                /// \param  ty          The signature of the function
                /// \param  compound    The body of the function
                FunctionDecl(const ucmp::misc::location& loc,
                             const ucmp::misc::Symbol& name,
                             FunctionTy* ty,
                             CompoundStmt* compound);

                /// Destructor
                virtual ~FunctionDecl();

                /// Get the body of the function
                const CompoundStmt* compound_get() const
                {
                    return compound_;
                }

                /// Get the body of the function
                CompoundStmt* compound_get()
                {
                    return compound_;
                }

                /// Get the return ty of the function
                const Ty* return_ty_get() const
                {
                    return ty_->return_ty_get();
                }

                /// Get the return ty of the function
                Ty* return_ty_get()
                {
                    return ty_->return_ty_get();
                }

                /// Get the parameter list
                const std::list<VarDecl*>& param_get() const
                {
                    return ty_->param_get();
                }

                /// Get the parameter list
                std::list<VarDecl*>& param_get()
                {
                    return ty_->param_get();
                }

                /// Get the previous declaration of the function
                const FunctionDecl* prev_get() const
                {
                    return prev_;
                }

                /// Get the previous declaration of the function
                FunctionDecl* prev_get()
                {
                    return prev_;
                }

                /// \brief  Set the previous declaration of the function
                /// \param  d   The previous declaration of the function
                void prev_set(FunctionDecl* d)
                {
                    prev_ = d;
                }

                /// \brief  Set the return Ty of the FunctionTy
                /// \param  t   The return ty you want to set
                void return_ty_set(Ty* t)
                {
                    ty_->return_ty_set(t);
                }

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const override
                {
                    v(*this);
                }

            protected:
                FunctionTy* ty_;
                CompoundStmt* compound_;
                FunctionDecl* prev_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FUNCTION_DECL_HH */
