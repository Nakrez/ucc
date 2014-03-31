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
void ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Type>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<NamedType>::type&)
{
}

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
ucc::ast::GenDefaultVisitor<Const>::operator()(typename Const<Stmt>::type& ast)
{
    ast.accept(*this);
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

#endif /* !UCC_AST_DEFAULT_VISITOR_HXX */
