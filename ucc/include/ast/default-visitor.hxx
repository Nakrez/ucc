#ifndef UCC_AST_DEFAULT_VISITOR_HXX
# define UCC_AST_DEFAULT_VISITOR_HXX

# include <ast/visitor.hh>

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<AstList>::type& ast)
{
    for (auto elem : ast.list_get())
        elem->accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<DeclList>::type& ast)
{
    for (auto elem : ast.list_get())
        elem->accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<ExprList>::type& ast)
{
    for (auto elem : ast.list_get())
        elem->accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<FieldList>::type& ast)
{
    for (auto elem : ast.list_get())
        elem->accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<EnumExprList>::type& ast)
{
    for (auto elem : ast.list_get())
        elem->accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Decl>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Declarator>::type&)
{
    assert(false && "Internal compiler error: should not reach Declarator");
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<VarDecl>::type& ast)
{
    if (ast.type_get())
        ast.type_get()->accept(*this);

    if (ast.init_get())
        ast.init_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<FunctionDecl>::type& ast)
{
    if (ast.return_type_get())
        ast.return_type_get()->accept(*this);

    for (auto param : ast.param_get())
        param->accept(*this);

    if (ast.compound_get())
        ast.compound_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<TypeDecl>::type& ast)
{
    if (ast.type_get())
        ast.type_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<FieldDecl>::type& ast)
{
    if (ast.type_get())
        ast.type_get()->accept(*this);

    if (ast.bit_field_get())
        ast.bit_field_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<RecordDecl>::type& ast)
{
    if (ast.fields_get())
        ast.fields_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<EnumExprDecl>::type& ast)
{
    if (ast.value_get())
        ast.value_get()->accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Type>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<NamedType>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<ArrayType>::type& ast)
{
    if (ast.sub_type_get())
        ast.sub_type_get()->accept(*this);

    if (ast.size_get())
        ast.size_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<FunctionType>::type& ast)
{
    if (ast.return_type_get())
        ast.return_type_get()->accept(*this);

    for (auto param : ast.param_get())
        param->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<PtrType>::type& ast)
{
    if (ast.pointed_type_get())
        ast.pointed_type_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<RecordType>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Stmt>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<CompoundStmt>::type& ast)
{
    if (ast.compound_get())
        ast.compound_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<ReturnStmt>::type& ast)
{
    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<WhileStmt>::type& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.body_get())
        ast.body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<DoWhileStmt>::type& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.body_get())
        ast.body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<LabelStmt>::type& ast)
{
    if (ast.stmt_get())
        ast.stmt_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<GotoStmt>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<BreakStmt>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<ContinueStmt>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<IfStmt>::type& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.if_body_get())
        ast.if_body_get()->accept(*this);

    if (ast.else_body_get())
        ast.else_body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<SwitchStmt>::type& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.body_get())
        ast.body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<CaseStmt>::type& ast)
{
    if (ast.expr_get())
        ast.expr_get()->accept(*this);

    if (ast.body_get())
        ast.body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<DefaultStmt>::type& ast)
{
    if (ast.body_get())
        ast.body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<ForStmt>::type& ast)
{
    if (ast.init_get())
        ast.init_get()->accept(*this);

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.inc_get())
        ast.inc_get()->accept(*this);

    if (ast.body_get())
        ast.body_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Expr>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<IntExpr>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<FloatExpr>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<StringExpr>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<VarExpr>::type&)
{}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<SubscriptExpr>::type& ast)
{
    if (ast.var_get())
        ast.var_get()->accept(*this);

    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<CallExpr>::type& ast)
{
    if (ast.var_get())
        ast.var_get()->accept(*this);

    if (ast.param_get())
        ast.param_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<AssignExpr>::type& ast)
{
    if (ast.lvalue_get())
        ast.lvalue_get()->accept(*this);

    if (ast.rvalue_get())
        ast.rvalue_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<ConditionalExpr>::type& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    if (ast.true_expr_get())
        ast.true_expr_get()->accept(*this);

    if (ast.false_expr_get())
        ast.false_expr_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<OpExpr>::type& ast)
{
    if (ast.lexpr_get())
        ast.lexpr_get()->accept(*this);

    if (ast.rexpr_get())
        ast.rexpr_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<UnaryExpr>::type& ast)
{
    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<MemberExpr>::type& ast)
{
    if (ast.lexpr_get())
        ast.lexpr_get()->accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<EnumExpr>::type&)
{}

#endif /* !UCC_AST_DEFAULT_VISITOR_HXX */
