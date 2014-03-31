#ifndef UCC_AST_DEFAULT_VISITOR_HH
# define UCC_AST_DEFAULT_VISITOR_HH

# include <cassert>

# include <misc/constness.hh>

# include <ast/visitor.hh>
# include <ast/all.hh>

namespace ucc
{
    namespace ast
    {
        template <template <typename> class Const>
        class GenDefaultVisitor : public GenVisitor<Const>
        {
            public:
                using GenVisitor<Const>::operator();

                GenDefaultVisitor() = default;
                virtual ~GenDefaultVisitor() = default;

                virtual void operator()(typename Const<AstList>::type& ast);
                virtual void operator()(typename Const<DeclList>::type& ast);
                virtual void operator()(typename Const<ExprList>::type& ast);

                virtual void operator()(typename Const<Decl>::type& ast);

                virtual void operator()(typename Const<Declarator>::type& ast);
                virtual void operator()(typename Const<VarDecl>::type& ast);
                virtual void operator()(typename Const<FunctionDecl>::type& ast);
                virtual void operator()(typename Const<TypeDecl>::type& ast);

                virtual void operator()(typename Const<Type>::type& ast);

                virtual void operator()(typename Const<NamedType>::type& ast);
                virtual void operator()(typename Const<ArrayType>::type& ast);
                virtual void
                operator()(typename Const<FunctionType>::type& ast);
                virtual void operator()(typename Const<PtrType>::type& ast);

                virtual void operator()(typename Const<Stmt>::type& ast);
                virtual void operator()(typename Const<CompoundStmt>::type& ast);
                virtual void operator()(typename Const<ReturnStmt>::type& ast);
                virtual void operator()(typename Const<WhileStmt>::type& ast);

                virtual void operator()(typename Const<Expr>::type& ast);
                virtual void operator()(typename Const<IntExpr>::type& ast);
                virtual void operator()(typename Const<FloatExpr>::type& ast);
                virtual void operator()(typename Const<StringExpr>::type& ast);
                virtual void operator()(typename Const<VarExpr>::type& ast);
                virtual void operator()(typename Const<SubscriptExpr>::type& ast);
                virtual void operator()(typename Const<CallExpr>::type& ast);
                virtual void operator()(typename Const<AssignExpr>::type& ast);
                virtual void operator()(typename Const<ConditionalExpr>::type& ast);
                virtual void operator()(typename Const<OpExpr>::type& ast);
                virtual void operator()(typename Const<UnaryExpr>::type& ast);
        };

        typedef GenDefaultVisitor<ucc::misc::const_type> DefaultConstVisitor;
        typedef GenDefaultVisitor<ucc::misc::nonconst_type> DefaultVisitor;
    } // namespace ast
} // namespace ucc

# include <ast/default-visitor.hxx>

#endif /* !UCC_AST_DEFAULT_VISITOR_HH */
