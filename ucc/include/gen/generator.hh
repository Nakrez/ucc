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
# include <type/function.hh>

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

                virtual void operator()(ast::VarDecl& ast) override;
                virtual void operator()(ast::FunctionDecl& ast) override;

                virtual void operator()(ast::ReturnStmt& ast) override;
                virtual void operator()(ast::WhileStmt& ast) override;
                virtual void operator()(ast::DoWhileStmt& ast) override;
                virtual void operator()(ast::LabelStmt& ast) override;
                virtual void operator()(ast::GotoStmt& ast) override;
                virtual void operator()(ast::BreakStmt& ast) override;
                virtual void operator()(ast::ContinueStmt& ast) override;
                virtual void operator()(ast::IfStmt& ast) override;
                //virtual void operator()(ast::SwitchStmt& ast) override;
                //virtual void operator()(ast::CaseStmt& ast) override;
                //virtual void operator()(ast::DefaultStmt& ast) override;
                virtual void operator()(ast::ForStmt& ast) override;

                virtual void operator()(ast::IntExpr& ast) override;
                //virtual void operator()(ast::FloatExpr& ast) override;
                //virtual void operator()(ast::StringExpr& ast) override;
                virtual void operator()(ast::VarExpr& ast) override;
                virtual void operator()(ast::SubscriptExpr& ast) override;
                virtual void operator()(ast::CallExpr& ast) override;
                virtual void operator()(ast::AssignExpr& ast) override;
                virtual void operator()(ast::ConditionalExpr& ast) override;
                virtual void operator()(ast::OpExpr& ast) override;
                virtual void operator()(ast::UnaryExpr& ast) override;
                virtual void operator()(ast::MemberExpr& ast) override;
                //virtual void operator()(ast::EnumExpr& ast) override;
                virtual void operator()(ast::CastExpr& ast) override;
                virtual void operator()(ast::ImplicitCastExpr& ast) override;
                virtual void operator()(ast::SizeofExpr& ast) override;
                //virtual void operator()(ast::InitListExpr& ast) override;

            protected:
                bool is_end_block(ucmp::ir::Instruction* i)
                {
                    return i->itype_get() == ucmp::ir::Instruction::RET ||
                           i->itype_get() == ucmp::ir::Instruction::CJUMP ||
                           i->itype_get() == ucmp::ir::Instruction::JUMP;
                }

                ucmp::ir::FunctionType*
                get_fun_type(const ast::FunctionDecl& ast);

                ucmp::ir::Value* create_stack_alloc(ucmp::ir::sType t,
                                            const ucmp::misc::Symbol& s = "");

                void generate_cast(const type::Type* t1, const type::Type* t2,
                                   ucmp::ir::Value* v);

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
                std::map<ucc::ast::LabelStmt*, ucmp::ir::BasicBlock*> labels_;

                int allocas_;
                bool lvalue_;
                bool no_load_;
        };
    } // namespace gen
} // namespace ucc

#endif /* !UCC_GEN_GENERATOR_HH */
