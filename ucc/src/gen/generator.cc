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

#include <gen/generator.hh>
#include <type/function.hh>

#include <ucmp/ir/int-constant.hh>

using namespace ucc;
using namespace gen;
using namespace ucmp;
using namespace ir;

Generator::Generator(ucmp::ir::Unit* u)
    : gen_(u->context_get())
    , stack_alloc_(u->context_get())
    , unit_(u)
    , c_(u->context_get())
    , val_(nullptr)
    , allocas_(0)
{
}

Generator::~Generator()
{}

FunctionType* Generator::get_fun_type(const ast::FunctionDecl& ast)
{
    const type::Function* ast_ft;
    sType ret_type;

    ast_ft = dynamic_cast<const type::Function*> (ast.built_type_get());
    ret_type = ast_ft->return_type_get()->to_ir_type(c_);

    return new FunctionType(ret_type);
}

void Generator::operator()(ast::VarDecl& ast)
{
    // stack_alloc_ generator is always meant to point on the right point of a
    // basic block to insert a new stack allocation

    // FIXME
    // Sorry for the above code... It's...
    stack_alloc_.insert_pt_get() = stack_alloc_.insert_block_get()->begin();

    for (int i = 0; i < allocas_; ++i)
        ++stack_alloc_.insert_pt_get();

    Value* v = stack_alloc_.create_stack_alloc(ast.type_get()->to_ir_type(c_),
                                               ast.name_get());

    ++allocas_;

    // Little tweak here to avoid name collision. VarExpr operator()
    // should use the name of it declaration.
    ast.name_set(v->name_get());

    scope_.put(ast.name_get(), v);

    if (ast.init_get())
    {
        Value* val = generate(*ast.init_get());

        gen_.create_store(val, v);
    }
}

void Generator::operator()(ast::FunctionDecl& ast)
{
    if (ast.compound_get())
    {
        FunctionType* ft = get_fun_type(ast);

        Function* f = new Function(ft, ast.name_get(), unit_);

        BasicBlock* bb = new BasicBlock(c_, f);
        gen_.insert_pt_set(bb);
        stack_alloc_.insert_pt_set(bb, bb->begin());

        scope_.scope_begin();
        ast.compound_get()->accept(*this);
        scope_.scope_end();

        Instruction* i = f->f_back()->back();

        if (i->itype_get() != Instruction::RET)
            gen_.create_ret();
    }
}

void Generator::operator()(ast::OpExpr& ast)
{
    Value* left = generate(*ast.lexpr_get());
    Value* right = generate(*ast.rexpr_get());

    switch (ast.op_get())
    {
        case ast::OpExpr::OP_PLUS:
            val_ = gen_.create_add(left, right);
            break;
        case ast::OpExpr::OP_MINUS:
            val_ = gen_.create_sub(left, right);
            break;
        case ast::OpExpr::OP_MUL:
            val_ = gen_.create_mul(left, right);
            break;
        case ast::OpExpr::OP_DIV:
            val_ = gen_.create_div(left, right);
            break;
        case ast::OpExpr::OP_MOD:
            val_ = gen_.create_mod(left, right);
            break;
        case ast::OpExpr::OP_GT:
            val_ = gen_.create_gt(left, right);
            break;
        case ast::OpExpr::OP_GE:
            val_ = gen_.create_ge(left, right);
            break;
        case ast::OpExpr::OP_LT:
            val_ = gen_.create_lt(left, right);
            break;
        case ast::OpExpr::OP_LE:
            val_ = gen_.create_le(left, right);
            break;
        case ast::OpExpr::OP_EQ:
            val_ = gen_.create_eq(left, right);
            break;
        case ast::OpExpr::OP_COMA:
            val_ = right;
            break;
        default:
            break;
    }
}

void Generator::operator()(ast::IntExpr& ast)
{
    val_ = new IntConstant(c_, ast.value_get());
}

void Generator::operator()(ast::VarExpr& ast)
{
    ast::VarDecl* vd = dynamic_cast<ast::VarDecl*> (ast.def_get());

    if (!vd)
        return;

    Value* mem = scope_.get(vd->name_get());

    val_ = gen_.create_load(mem);
}
