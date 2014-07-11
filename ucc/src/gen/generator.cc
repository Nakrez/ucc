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
#include <type/ptr.hh>
#include <type/record.hh>
#include <type/array.hh>

#include <ucmp/ir/int-constant.hh>
#include <ucmp/ir/load.hh>

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
    , lvalue_(false)
    , no_load_(false)
{
}

Generator::~Generator()
{}

FunctionType* Generator::get_fun_type(const ast::FunctionDecl& ast)
{
    const type::Function* ast_ft;
    sType ret_type;
    FunctionType* ft;

    ast_ft = dynamic_cast<const type::Function*> (ast.built_type_get());
    ret_type = ast_ft->return_type_get()->to_ir_type(c_);

    ft = new FunctionType(ret_type);

    if (ast_ft->size_get() && !ast_ft->no_param())
    {
        for (auto arg : ast.param_get())
            ft->arg_add(arg->type_get()->to_ir_type(c_));
    }

    return ft;
}

Value* Generator::create_stack_alloc(sType t, const misc::Symbol& s)
{
    // stack_alloc_ generator is always meant to point on the right point of a
    // basic block to insert a new stack allocation

    // FIXME
    // Sorry for the above code... It's...
    auto it = stack_alloc_.insert_block_get()->begin();

    for (int i = 0; i < allocas_; ++i, ++it)
        ;

    stack_alloc_.insert_pt_set(stack_alloc_.insert_block_get(), it);

    Value* v = stack_alloc_.create_stack_alloc(t, s);

    ++allocas_;

    return v;
}

void Generator::generate_cast(const type::Type* exprt, const type::Type* castt,
                              Value *v)
{
    if (*exprt == *castt)
    {
        val_ = v;
        return;
    }

    int exprt_size = exprt->size();
    int castt_size = castt->size();

    if (exprt_size > castt_size)
        val_ = gen_.create_demot(castt->to_ir_type(c_), v);
    else if (exprt_size < castt_size)
        val_ = gen_.create_promot(castt->to_ir_type(c_), v);
    else
        val_ = gen_.create_cast(castt->to_ir_type(c_), v);
}

void Generator::operator()(ast::VarDecl& ast)
{
    Value *v;

    v = create_stack_alloc(ast.type_get()->to_ir_type(c_), ast.name_get());

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
        allocas_ = 0;

        FunctionType* ft = get_fun_type(ast);

        Function* f = new Function(ft, ast.name_get(), unit_);

        BasicBlock* bb = new BasicBlock(c_, f);
        gen_.insert_pt_set(bb);
        stack_alloc_.insert_pt_set(bb, bb->begin());

        scope_.put(ast.name_get(), f);

        scope_.scope_begin();

        if (ast.param_get().size() &&
            (*ast.param_get().begin())->type_get() != &type::Void::instance_get())
        {
            // Name correctly every parameter and put them on the stack
            auto ir_param = f->a_begin();
            Value* v;

            for (auto ast_param : ast.param_get())
            {
                (*ir_param)->name_set(ast_param->name_get());

                v = create_stack_alloc((*ir_param)->type_get());

                scope_.put(ast_param->name_get(), v);

                gen_.create_store(*ir_param, v);
                ++ir_param;
            }
        }

        ast.compound_get()->accept(*this);
        scope_.scope_end();

        Instruction* i = f->f_back()->back();

        if (!f->f_back()->size() || !is_end_block(i))
            gen_.create_ret();
    }
}

void Generator::operator()(ast::BreakStmt& ast)
{
    Function* f = gen_.insert_block_get()->parent_get();

    gen_.create_jump(loops_[ast.def_get()].second);

    gen_.insert_pt_set(new BasicBlock(c_, f));
}

void Generator::operator()(ast::ContinueStmt& ast)
{
    Function* f = gen_.insert_block_get()->parent_get();

    gen_.create_jump(loops_[ast.def_get()].first);

    gen_.insert_pt_set(new BasicBlock(c_, f));
}

void Generator::operator()(ast::ReturnStmt& ast)
{
    if (ast.expr_get())
    {
        Value *v = generate(*ast.expr_get());
        gen_.create_ret(v);
    }
    else
        gen_.create_ret();
}

void Generator::operator()(ast::WhileStmt& ast)
{
    Function* f = gen_.insert_block_get()->parent_get();
    BasicBlock* cond = new BasicBlock(c_, f);
    BasicBlock* body = new BasicBlock(c_);
    BasicBlock* end = new BasicBlock(c_);

    // Add loops begin and end to the loop map
    loops_[&ast] = std::make_pair(cond, end);

    gen_.create_jump(cond);

    gen_.insert_pt_set(cond);

    Value* v = generate(*ast.cond_get());

    gen_.create_cjump(v, body, end);

    gen_.insert_pt_set(body);
    body->parent_set(f);
    f->insert_bb(body);

    operator()(*ast.body_get());

    gen_.create_jump(cond);

    gen_.insert_pt_set(end);
    end->parent_set(f);
    f->insert_bb(end);
}

void Generator::operator()(ast::DoWhileStmt& ast)
{
    Function* f = gen_.insert_block_get()->parent_get();
    BasicBlock *body = new BasicBlock(c_, f);
    BasicBlock *cond= new BasicBlock(c_);
    BasicBlock *end = new BasicBlock(c_);

    /* Set loops_ (usefull for break/continue) */
    loops_[&ast] = std::make_pair(cond, end);

    /* Generate body code */
    gen_.insert_pt_set(body);
    operator()(*ast.body_get());
    gen_.create_jump(cond);

    /* Generate condition block */
    gen_.insert_pt_set(cond);
    cond->parent_set(f);
    f->insert_bb(cond);
    Value *c = generate(*ast.cond_get());
    gen_.create_cjump(c, body, end);

    /* Start end block */
    gen_.insert_pt_set(end);
    end->parent_set(f);
    f->insert_bb(end);
}

void Generator::operator()(ast::LabelStmt& ast)
{
    BasicBlock* bb = gen_.insert_block_get();
    Function* f = bb->parent_get();

    if (!bb || !(bb = labels_[&ast]))
        bb = new BasicBlock(c_);

    if (!f->f_back()->size() || !is_end_block(f->f_back()->back()))
        gen_.create_jump(bb);

    gen_.insert_pt_set(bb);
    bb->parent_set(f);
    f->insert_bb(bb);

    labels_[&ast] = bb;
    ast.stmt_get()->accept(*this);
}

void Generator::operator()(ast::GotoStmt& ast)
{
    BasicBlock* current = gen_.insert_block_get();
    Function* f = current->parent_get();

    if (!f->f_back()->size() || !is_end_block(f->f_back()->back()))
    {
        // If this goto jumps to a forward label just create the basic block
        if (!labels_[ast.def_get()])
            labels_[ast.def_get()] = new BasicBlock(c_);

        gen_.create_jump(labels_[ast.def_get()]);
        BasicBlock* bb = new BasicBlock(c_, f);
        gen_.insert_pt_set(bb);
    }
}

void Generator::operator()(ast::IfStmt& ast)
{
    Value* cond = generate(*ast.cond_get());
    Function* f = gen_.insert_block_get()->parent_get();
    BasicBlock* if_ = new BasicBlock(c_, f);
    BasicBlock* join_ = new BasicBlock(c_);
    BasicBlock* else_ = nullptr;

    if (ast.else_body_get())
    {
        else_ = new BasicBlock(c_);
        gen_.create_cjump(cond, if_, else_);
    }
    else
        gen_.create_cjump(cond, if_, join_);

    gen_.insert_pt_set(if_);
    operator()(*ast.if_body_get());

    if (!f->f_back()->size() || !is_end_block(f->f_back()->back()))
        gen_.create_jump(join_);

    if (ast.else_body_get())
    {
        gen_.insert_pt_set(else_);
        else_->parent_set(f);
        f->insert_bb(else_);
        operator()(*ast.else_body_get());

        if (!f->f_back()->size() || !is_end_block(f->f_back()->back()))
            gen_.create_jump(join_);
    }

    gen_.insert_pt_set(join_);
    join_->parent_set(f);
    f->insert_bb(join_);
}

void Generator::operator()(ast::ForStmt& ast)
{
    Function* f = gen_.insert_block_get()->parent_get();
    BasicBlock *cond;
    BasicBlock *body = new BasicBlock(c_);
    BasicBlock *end = new BasicBlock(c_);
    BasicBlock *inc = new BasicBlock(c_);

    /* Generate initial block */
    if (ast.init_get())
    {
        BasicBlock *init = new BasicBlock(c_, f);
        gen_.create_jump(init);
        gen_.insert_pt_set(init);

        operator()(*ast.init_get());
    }

    /* Add jump to cond and set it as insert point */
    cond = new BasicBlock(c_, f);
    gen_.create_jump(cond);
    gen_.insert_pt_set(cond);

    /* Generate condition */
    if (ast.cond_get())
    {
        Value *c = generate(*ast.cond_get());
        gen_.create_cjump(c, body, end);
    }
    else
        gen_.create_jump(body);

    /* Set loops_ (usefull for break/continue) */
    loops_[&ast] = std::make_pair(inc, end);

    gen_.insert_pt_set(body);
    body->parent_set(f);
    f->insert_bb(body);

    if (ast.body_get())
        operator()(*ast.body_get());

    gen_.create_jump(inc);

    gen_.insert_pt_set(inc);
    inc->parent_set(f);
    f->insert_bb(inc);

    if (ast.inc_get())
        operator()(*ast.inc_get());

    if (ast.cond_get())
        gen_.create_jump(cond);
    else
        gen_.create_jump(body);

    gen_.insert_pt_set(end);
    end->parent_set(f);
    f->insert_bb(end);
}

void Generator::operator()(ast::IntExpr& ast)
{
    val_ = c_.iconstant_get(ast.value_get());
}

void Generator::operator()(ast::VarExpr& ast)
{
    ast::VarDecl* vd = dynamic_cast<ast::VarDecl*> (ast.def_get());

    if (!vd)
    {
        Value* v = scope_.get(ast.name_get());

        assert(dynamic_cast<Function*> (v));

        val_ = v;
        return;
    }

    Value* mem = scope_.get(vd->name_get());

    if (lvalue_ || no_load_)
    {
        val_ = mem;
        return;
    }

    val_ = gen_.create_load(mem);
}

void Generator::operator()(ast::SubscriptExpr& ast)
{
    const type::Type* t_inner = ast.type_get();
    bool tmp = no_load_;

    no_load_ = true;
    Value* var = generate(*ast.var_get());
    no_load_ = tmp;

    Value* expr = generate(*ast.expr_get());

    PtrType* t = new PtrType(t_inner->to_ir_type(c_));

    val_ = gen_.create_data_ptr(sType(t), var, expr);

    if (!lvalue_ && !no_load_)
        val_ = gen_.create_load(val_);
}

void Generator::operator()(ast::CallExpr& ast)
{
    Function* f = dynamic_cast<Function*> (generate(*ast.var_get()));

    if (ast.param_get())
    {
        std::vector<Value*> args;
        Value* v;

        assert(f);

        for (auto ast_arg : ast.param_get()->list_get())
        {
            v = generate(*ast_arg);

            args.push_back(v);
        }

        if (f->return_type_get() == c_.void_ty_get())
            val_ = gen_.create_call(f, args);
        else
            val_ = gen_.create_call(f, args, "");

        return;
    }

    if (f->return_type_get() == c_.void_ty_get())
        val_ = gen_.create_call(f);
    else
        val_ = gen_.create_call(f, "");
}

void Generator::operator()(ast::AssignExpr& ast)
{
    bool tmp = lvalue_;

    lvalue_ = true;

    Value* lv = generate(*ast.lvalue_get());

    lvalue_ = tmp;

    Value* rv = generate(*ast.rvalue_get());

    gen_.create_store(rv, lv);
    val_ = rv;
}

void Generator::operator()(ast::ConditionalExpr& ast)
{
    Value* v = generate(*ast.cond_get());
    Function* f = gen_.insert_block_get()->parent_get();
    BasicBlock* true_bb = new BasicBlock(c_, f);
    BasicBlock* false_bb = new BasicBlock(c_);
    BasicBlock* join = new BasicBlock(c_);

    gen_.create_cjump(v, true_bb, false_bb);

    // Get true expression value;
    gen_.insert_pt_set(true_bb);
    Value* tv = generate(*ast.true_expr_get());
    gen_.create_jump(join);

    // Get false expression value;
    gen_.insert_pt_set(false_bb);
    false_bb->parent_set(f);
    f->insert_bb(false_bb);
    Value* fv = generate(*ast.false_expr_get());
    gen_.create_jump(join);

    // Use phi node to reunite values
    gen_.insert_pt_set(join);
    join->parent_set(f);
    f->insert_bb(join);

    PhiNode* pn = gen_.create_phi(tv->type_get());

    pn->incoming_add(true_bb, tv);
    pn->incoming_add(false_bb, fv);

    val_ = pn;
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
        case ast::OpExpr::OP_XOR:
            val_ = gen_.create_xor(left, right);
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
        case ast::OpExpr::OP_DIFF:
            val_ = gen_.create_ne(left, right);
            break;
        case ast::OpExpr::OP_COMA:
            val_ = right;
            break;
        default:
            break;
    }
}

void Generator::operator()(ast::UnaryExpr& ast)
{
    Value *v = generate(*ast.expr_get());

    switch (ast.op_get())
    {
        case ast::UnaryExpr::MINUS:
            val_ = gen_.create_sub(c_.iconstant_get(0), v);
            break;
        case ast::UnaryExpr::PRE_INCR:
            {
                Load* l = dynamic_cast<Load*> (v);

                assert(l);

                val_ = gen_.create_add(v, c_.iconstant_get(1));
                gen_.create_store(val_, l->operand_get(0));
            }
            break;
        case ast::UnaryExpr::PRE_DECR:
            {
                Load* l = dynamic_cast<Load*> (v);

                assert(l);

                val_ = gen_.create_sub(v, c_.iconstant_get(1));
                gen_.create_store(val_, l->operand_get(0));
            }
            break;
        case ast::UnaryExpr::POST_INCR:
            {
                Load* l = dynamic_cast<Load*> (v);

                assert(l);

                Value* ret = gen_.create_add(v, c_.iconstant_get(1));
                gen_.create_store(ret, l->operand_get(0));

                val_ = v;
            }
            break;
        case ast::UnaryExpr::POST_DECR:
            {
                Load* l = dynamic_cast<Load*> (v);

                assert(l);

                Value* ret = gen_.create_sub(v, c_.iconstant_get(1));
                gen_.create_store(ret, l->operand_get(0));

                val_ = v;
            }
            break;
        case ast::UnaryExpr::BAND:
            {
                Load* l = dynamic_cast<Load*> (v);

                assert(l);

                val_ = l->operand_get(0);
                gen_.remove(l);
            }
            break;
        case ast::UnaryExpr::DEREF:
            val_ = gen_.create_load(v);
            break;
        case ast::UnaryExpr::TILDE:
            val_ = gen_.create_xor(v, c_.iconstant_get(-1));
            break;
        case ast::UnaryExpr::BANG:
            if (v->type_get() != c_.i1_ty_get())
                v = gen_.create_ne(v, c_.iconstant_get(0));
            gen_.create_xor(v, c_.iconstant_get(1));
            break;
        /* Plus operator : nothing to do */
        default:
            break;
    }
}

void Generator::operator()(ast::MemberExpr& ast)
{
    bool tmp = no_load_;
    Value* v;
    const type::Type* t;
    const type::Record* rtype;

    no_load_ = true;
    v = generate(*ast.lexpr_get());
    no_load_ = tmp;

    t = ast.lexpr_get()->type_get();

    if (ast.is_arrow())
    {
        v = gen_.create_load(v);

        const type::Ptr *pt = dynamic_cast<const type::Ptr*> (t);

        t = pt->pointed_type_get();
    }

    rtype = dynamic_cast<const type::Record*> (t);

    if (rtype->is_struct())
    {
        const type::Type* t_member = rtype->field_type_get(ast.name_get());
        int i_member = rtype->field_index_get(ast.name_get());
        PtrType* t = new PtrType(t_member->to_ir_type(c_));

        val_ = gen_.create_data_ptr(sType(t), v, i_member);
    }
    else
    {
        PtrType *t = new PtrType(ast.type_get()->to_ir_type(c_));

        val_ = gen_.create_cast(sType(t), v);
    }

    // We need to load the value if we need it
    if (!lvalue_ && !no_load_)
        val_ = gen_.create_load(val_);
}

void Generator::operator()(ast::CastExpr& ast)
{
    Value* v = generate(*ast.expr_get());

    generate_cast(ast.expr_get()->type_get(), ast.ty_get()->type_get(), v);
}

void Generator::operator()(ast::ImplicitCastExpr& ast)
{
    Value* v = generate(*ast.expr_get());

    generate_cast(ast.expr_get()->type_get(), ast.type_get(), v);
}
