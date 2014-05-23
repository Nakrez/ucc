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
    , unit_(u)
    , c_(u->context_get())
    , val_(nullptr)
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

void Generator::operator()(const ast::FunctionDecl& ast)
{
    if (ast.compound_get())
    {
        FunctionType* ft = get_fun_type(ast);

        Function* f = new Function(ft, ast.name_get(), unit_);

        BasicBlock* bb = new BasicBlock(c_, f);
        gen_.insert_pt_set(bb);

        ast.compound_get()->accept(*this);
    }
}

void Generator::operator()(const ast::OpExpr& ast)
{
    Value* left = generate(*ast.lexpr_get());
    Value* right = generate(*ast.rexpr_get());

    switch (ast.op_get())
    {
        case ast::OpExpr::OP_PLUS:
            val_ = gen_.create_add(left, right);
            break;
        default:
            break;
    }
}

void Generator::operator()(const ast::IntExpr& ast)
{
    val_ = new IntConstant(c_, ast.value_get());
}
