#ifndef UCC_AST_AST_HXX
# define UCC_AST_AST_HXX

# include <ast/ast.hh>

const ucc::parse::location& ucc::ast::Ast::location_get() const
{
    return loc_;
}
ucc::parse::location& ucc::ast::Ast::location_get()
{
    return loc_;
}

#endif /* !UCC_AST_AST_HXX */
