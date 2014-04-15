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

#ifndef UCC_AST_PTR_TYPE_HH
# define UCC_AST_PTR_TYPE_HH

# include <ast/type.hh>

namespace ucc
{
    namespace ast
    {
        class PtrType : public Type
        {
            public:
                PtrType(const ucc::misc::location& loc);
                PtrType(const ucc::misc::location& loc, Type* pointed_type);
                virtual ~PtrType();

                const Type* pointed_type_get() const;
                Type* pointed_type_get();

                virtual bool extends_type(Type *t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                Type* pointed_type_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_PTR_TYPE_HH */
