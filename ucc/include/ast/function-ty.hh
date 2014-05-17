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

#ifndef UCC_AST_FUNCTION_TY_HH
# define UCC_AST_FUNCTION_TY_HH

# include <list>

# include <ast/ty.hh>

namespace ucc
{
    namespace ast
    {
        class VarDecl;

        /// Represents a function type in the ast
        class FunctionTy : public Ty
        {
            public:
                /// \brief  Constructor
                /// \param  loc The location of the FunctionTy
                FunctionTy(const ucmp::misc::location& loc);

                /// \brief  Constructor
                /// \param  loc     The location of the FunctionTy
                /// \param  param   The list of parameter of the FunctionTy
                FunctionTy(const ucmp::misc::location& loc,
                           const std::list<VarDecl*>& param);

                /// Destructor
                virtual ~FunctionTy();

                /// Return the Ty that hold the return type node of the
                /// FunctionTy
                const Ty* return_ty_get() const
                {
                    return return_ty_;
                }

                /// Return the Ty that hold the return type node of the
                /// FunctionTy
                Ty* return_ty_get()
                {
                    return return_ty_;
                }

                /// Return the parameter list of the FunctionTy
                const std::list<VarDecl*>& param_get() const
                {
                    return param_;
                }

                /// Return the parameter list of the FunctionTy
                std::list<VarDecl*>& param_get()
                {
                    return param_;
                }

                /// Set the return type node of the FunctionTy
                void return_ty_set(Ty* t);

                virtual bool extends_ty(Ty *t) override;

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const override
                {
                    v(*this);
                }

            private:
                Ty* return_ty_;
                std::list<VarDecl*> param_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FUNCTION_TY_HH */
