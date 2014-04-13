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

#ifndef UCC_AST_TYPE_HH
# define UCC_AST_TYPE_HH

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        class Type: public Ast
        {
            public:
                Type(const ucc::parse::location& loc);
                virtual ~Type();

                bool is_const() const;
                bool is_volatile() const;
                bool is_restrict() const;
                bool is_unsigned() const;

                void const_set(bool b = true);
                void volatile_set(bool b = true);
                void restrict_set(bool b = true);
                void unsigned_set(bool b = true);

                virtual bool extends_type(Type *t) = 0;

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;

            private:
                bool is_const_;
                bool is_volatile_;
                bool is_restrict_;
                bool is_unsigned_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_TYPE_HH */
