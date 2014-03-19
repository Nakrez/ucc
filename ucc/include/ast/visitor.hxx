#ifndef UCC_AST_VISITOR_HXX
# define UCC_AST_VISITOR_HXX

# include <ast/visitor.hh>

template <template <typename> class Const>
void ucc::ast::GenVisitor<Const>::operator()(typename Const<Ast>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenVisitor<Const>::operator()(typename Const<Decl>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void
ucc::ast::GenVistor<Const>::operator()(typename Const<DeclSpecifier>::type&)
{
    abort(false && "Internal compiler error: should not reach DeclSpecifier");
}

template <template <typename> class Const>
void ucc::ast::Genvisitor<Const>::operator()(typename Const<Declarator>::type&)
{
    abort(false && "Internal compiler error: should not reach Declarator");
}

#endif /* !UCC_AST_VISITOR_HXX */
