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

#ifndef UCC_AST_DECLARATOR_HH
# define UCC_AST_DECLARATOR_HH

# include <misc/symbol.hh>

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class Ty;
        class Expr;

        class Declarator : public Decl
        {
            public:
                /// \brief  Constructor
                /// \param  loc The location of the Declarator
                /// \param  s   The name of the Declarator
                Declarator(const ucmp::misc::location& loc,
                           const ucmp::misc::Symbol& s);

                /// Destructor
                virtual ~Declarator() = default;

                /// Return the type node of the Declarator
                const Ty* ty_get() const
                {
                    return ty_;
                }

                /// Return the type node of the Declarator
                Ty* ty_get()
                {
                    return ty_;
                }

                /// Return the initialization expression
                const Expr* init_get() const
                {
                    return init_;
                }

                /// Return the initialization expression
                Expr* init_get()
                {
                    return init_;
                }

                /// Set the initialization expression
                void init_set(Expr* e)
                {
                    init_ = e;
                }

                bool extends_ty(Ty* t);

                virtual void accept(Visitor& v) override
                {
                    v(*this);
                }

                virtual void accept(ConstVisitor& v) const override
                {
                    v(*this);
                }

            private:
                Ty* ty_;
                Expr* init_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECLARATOR_HH */
