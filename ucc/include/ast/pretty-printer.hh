#ifndef UCC_AST_PRETTY_PRINTER_HH
# define UCC_AST_PRETTY_PRINTER_HH

# include <ostream>

# include <ast/all.hh>
# include <ast/visitor.hh>

namespace ucc
{
    namespace ast
    {
        class PrettyPrinter : public ConstVisitor
        {
            public:
                using ConstVisitor::operator();

                PrettyPrinter(std::ostream& ostr);
                virtual ~PrettyPrinter();

            protected:
                std::ostream& ostr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_PRETTY_PRINTER_HH */
