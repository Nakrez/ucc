#ifndef UCC_AST_VISITOR_HXX
# define UCC_AST_VISITOR_HXX

# include <ast/visitor.hh>

template <template <typename> class Const>
void ucc::ast::GenVisitor::operator()(typename Const<Ast>::type& ast)
{
    ast.accept(*this);
}

#endif /* !UCC_AST_VISITOR_HXX */
