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

#ifndef UCC_AST_DECL_HH
# define UCC_AST_DECL_HH

# include <ucmp/misc/symbol.hh>

# include <ast/ast.hh>

# include <ast/decl-specifier.hh>

namespace ucc
{
    namespace ast
    {
        class Decl : public Ast
        {
            public:
                Decl(const ucmp::misc::location& loc,
                     const ucmp::misc::Symbol& name);
                virtual ~Decl();

                const ucmp::misc::Symbol& name_get() const;
                ucmp::misc::Symbol& name_get();

                bool is_static() const;
                bool is_extern() const;
                bool is_auto() const;
                bool is_register() const;

                DeclSpecifier::StorageClassSpecifier storage_class_get() const;

                void storage_class_set(DeclSpecifier::StorageClassSpecifier);

                virtual void accept(Visitor& v) = 0;
                virtual void accept(ConstVisitor& v) const = 0;

            protected:
                ucmp::misc::Symbol name_;
                DeclSpecifier::StorageClassSpecifier storage_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_DECL_HH */
