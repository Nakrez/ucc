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

#ifndef UCC_GEN_GENERATOR_HH
# define UCC_GEN_GENERATOR_HH

# include <cassert>
# include <map>

# include <ast/default-visitor.hh>

# include <ucmp/misc/scope-map.hh>
# include <ucmp/ir/ir-generator.hh>

namespace ucc
{
    namespace gen
    {
        class Generator : public ast::DefaultVisitor
        {
            public:
                using ast::DefaultVisitor::operator();

                Generator(ucmp::ir::Unit* u);
                virtual ~Generator();

                ucmp::ir::Value* generate(ast::Ast& ast)
                {
                    operator()(ast);

                    assert(val_);

                    return val_;
                }

                bool is_end_block(ucmp::ir::Instruction* i)
                {
                    return i->itype_get() == ucmp::ir::Instruction::RET ||
                           i->itype_get() == ucmp::ir::Instruction::CJUMP ||
                           i->itype_get() == ucmp::ir::Instruction::JUMP;
                }

                virtual void operator()(ast::VarDecl& ast) override;
                virtual void operator()(ast::FunctionDecl& ast) override;

                virtual void operator()(ast::WhileStmt& ast) override;
                virtual void operator()(ast::BreakStmt& ast) override;
                virtual void operator()(ast::ContinueStmt& ast) override;
                virtual void operator()(ast::IfStmt& ast) override;

                virtual void operator()(ast::OpExpr& ast) override;
                virtual void operator()(ast::IntExpr& ast) override;
                virtual void operator()(ast::VarExpr& ast) override;
                virtual void operator()(ast::AssignExpr& ast) override;

            protected:
                ucmp::ir::FunctionType*
                get_fun_type(const ast::FunctionDecl& ast);

            protected:
                ucmp::ir::IrGenerator gen_;
                ucmp::ir::IrGenerator stack_alloc_;
                ucmp::ir::Unit* unit_;
                ucmp::ir::Context& c_;
                ucmp::ir::Value* val_;
                ucmp::misc::ScopeMap<ucmp::misc::Symbol,
                                     ucmp::ir::Value*> scope_;

                /// Contains the entry and the end label of each loops.
                /// It is used for break and continue statement.
                std::map<ast::Stmt*, std::pair<ucmp::ir::BasicBlock*,
                                               ucmp::ir::BasicBlock*>> loops_;
                int allocas_;
                bool lvalue_;
        };
    } // namespace gen
} // namespace ucc

#endif /* !UCC_GEN_GENERATOR_HH */
