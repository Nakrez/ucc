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

                virtual void operator()(typename Const<AstList>::type& ast) = 0;
                virtual void operator()(typename Const<DeclList>::type& ast) = 0;

                virtual void operator()(typename Const<Decl>::type& ast) = 0;

                virtual void operator()(typename Const<Declarator>::type& ast) = 0;
                virtual void operator()(typename Const<VarDecl>::type& ast) = 0;
                virtual void operator()(typename Const<FunctionDecl>::type& ast) = 0;
                virtual void operator()(typename Const<TypeDecl>::type& ast) = 0;

                virtual void operator()(typename Const<Type>::type& ast) = 0;

                virtual void operator()(typename Const<NamedType>::type& ast) = 0;
                virtual void operator()(typename Const<ArrayType>::type& ast) = 0;
                virtual void
                operator()(typename Const<FunctionType>::type& ast) = 0;
                virtual void operator()(typename Const<PtrType>::type& ast) = 0;

                virtual void operator()(typename Const<Stmt>::type& ast) = 0;
                virtual void operator()(typename Const<ReturnStmt>::type& ast) = 0;

                virtual void operator()(typename Const<Expr>::type& ast) = 0;
                virtual void operator()(typename Const<IntExpr>::type& ast) = 0;
        };

        typedef GenVisitor<ucc::misc::const_type> ConstVisitor;
        typedef GenVisitor<ucc::misc::nonconst_type> Visitor;
    } // namespace ast
} // namespace ucc

# include <ast/visitor.hxx>

#endif /* !UCC_AST_VISITOR_HH */
