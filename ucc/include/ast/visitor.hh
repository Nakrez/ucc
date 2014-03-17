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
        };

        typedef GenVisitor<ucc::misc::const_type> ConstVisitor;
        typedef GenVisitor<ucc::misc::nonconst_type> Visitor;
    } // namespace ast
} // namespace ucc

# include <ast/visitor.hh>

#endif /* !UCC_AST_VISITOR_HH */
