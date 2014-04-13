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

namespace ucc
{
    namespace ast
    {
        class FunctionType;

        class FunctionDecl : public Decl
        {
            public:
                FunctionDecl(const ucc::parse::location& loc,
                             const ucc::misc::Symbol& name,
                             FunctionType* type);
                FunctionDecl(const ucc::parse::location& loc,
                             const ucc::misc::Symbol& name,
                             FunctionType* type,
                             CompoundStmt* compound);
                virtual ~FunctionDecl();

                const CompoundStmt* compound_get() const;
                CompoundStmt* compound_get();

                const Type* return_type_get() const;
                Type* return_type_get();

                const std::list<VarDecl*>& param_get() const;
                std::list<VarDecl*>& param_get();

                const FunctionDecl* prev_get() const;
                FunctionDecl* prev_get();

                void prev_set(FunctionDecl* d);

                void return_type_set(Type* t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                FunctionType* type_;
                CompoundStmt* compound_;
                FunctionDecl* prev_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FUNCTION_DECL_HH */
