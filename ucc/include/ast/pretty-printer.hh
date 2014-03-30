#ifndef UCC_AST_PRETTY_PRINTER_HH
# define UCC_AST_PRETTY_PRINTER_HH

# include <ostream>

# include <ast/all.hh>
# include <ast/default-visitor.hh>

namespace ucc
{
    namespace ast
    {
        class PrettyPrinter : public DefaultConstVisitor
        {
            public:
                using DefaultConstVisitor::operator();

                PrettyPrinter(std::ostream& ostr);
                virtual ~PrettyPrinter();

                virtual void operator()(const AstList& ast);
                virtual void operator()(const DeclList& ast);

                virtual void operator()(const VarDecl& ast);
                virtual void operator()(const TypeDecl& ast);
                virtual void operator()(const FunctionDecl& ast);

                virtual void operator()(const NamedType& ast);
                virtual void operator()(const PtrType& ast);

                virtual void operator()(const ReturnStmt& ast);

                virtual void operator()(const IntExpr& ast);
                virtual void operator()(const FloatExpr& ast);
                virtual void operator()(const StringExpr& ast);
                virtual void operator()(const VarExpr& ast);

            protected:
                bool print_fun_ptr(const Type* ast,
                                   const ucc::misc::Symbol& sym);

            protected:
                bool formals_;
                std::ostream& ostr_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_PRETTY_PRINTER_HH */
