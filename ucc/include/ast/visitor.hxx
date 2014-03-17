#ifndef UCC_AST_VISITOR_HXX
# define UCC_AST_VISITOR_HXX

# include <ast/visitor.hh>

template <template <typename> class Const>
void ucc::ast::GenVisitor::operator()(typename Const<Ast>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenVisitor::operator()(typename Const<Decl>::type& ast)
{
    ast.accept(*this);
}

template <template <typename> class Const>
void ucc::ast::GenVistor::operator()(typename Const<DeclSpecifier>::type& ast)
{
    abort(false && "Internal compiler error: should not reach DeclSpecifier");
}

#endif /* !UCC_AST_VISITOR_HXX */
