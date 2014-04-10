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

#ifndef UCC_AST_VAR_DECL_HH
# define UCC_AST_VAR_DECL_HH

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class Expr;
        class Type;

        class VarDecl : public Decl
        {
            public:
                VarDecl(const ucc::parse::location& loc,
                        const ucc::misc::Symbol& name,
                        Type* type,
                        Expr* e);
                VarDecl(const ucc::parse::location& loc);
                ~VarDecl();

                const Type* type_get() const;
                Type* type_get();

                const Expr* init_get() const;
                Expr* init_get();

                bool is_elipsis() const;

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            private:
                Type* type_;
                Expr* init_;
                bool is_elipsis_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_VAR_DECL_HH */
