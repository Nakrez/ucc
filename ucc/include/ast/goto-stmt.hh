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

#ifndef UCC_AST_GOTO_STMT_HH
# define UCC_AST_GOTO_STMT_HH

# include <ucmp/misc/symbol.hh>

# include <ast/stmt.hh>

namespace ucc
{
    namespace ast
    {
        class GotoStmt : public Stmt
        {
            public:
                GotoStmt(const ucmp::misc::location& loc,
                         const ucmp::misc::Symbol& name);
                virtual ~GotoStmt() = default;

                const ucmp::misc::Symbol& name_get() const { return name_; }
                ucmp::misc::Symbol& name_get() { return name_; }

                const LabelStmt* def_get() const { return def_; }
                LabelStmt* def_get() { return def_; }

                void def_set(LabelStmt* l) { def_ = l; }

                virtual void accept(Visitor& v) { v(*this); }
                virtual void accept(ConstVisitor& v) const { v(*this); }

            protected:
                ucmp::misc::Symbol name_;
                LabelStmt* def_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_GOTO_STMT_HH */
