#ifndef UCC_AST_VISITOR_HH
# define UCC_AST_VISITOR_HH

# include <misc/constness.hh>

# include <ast/fwd.hh>

namespace ucc
{
    namespace ast
    {
        template <template <typename> class Const>
        class GenVisitor
        {
            public:
                GenVisitor() = default;
                virtual ~GenVisitor() = default;

                virtual void operator()(typename Const<Ast>::type& ast);

                virtual void operator()(typename Const<Decl>::type& ast);

                virtual void
                operator()(typename Const<DeclSpecifier>::type& ast);
                virtual void operator()(typename Const<Declarator>::type& ast);
                virtual void operator()(typename Const<VarDecl>::type& ast);

                virtual void operator()(typename Const<Type>::type& ast);

                virtual void operator()(typename Const<ArrayType>::type& ast);
                virtual void
                operator()(typename Const<FunctionType>::type& ast);

                virtual void operator()(typename Const<Stmt>::type& ast);

                virtual void operator()(typename Const<Expr>::type& ast);
        };

        typedef GenVisitor<ucc::misc::const_type> ConstVisitor;
        typedef GenVisitor<ucc::misc::nonconst_type> Visitor;
    } // namespace ast
} // namespace ucc

# include <ast/visitor.hh>

#endif /* !UCC_AST_VISITOR_HH */
