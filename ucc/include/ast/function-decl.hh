#ifndef UCC_AST_FUNCTION_DECL_HH
# define UCC_AST_FUNCTION_DECL_HH

# include <list>

# include <ast/decl.hh>

namespace ucc
{
    namespace ast
    {
        class FunctionType;

        class FunctionDecl : public Decl
        {
            public:
                FunctionDecl(const ucc::parse::location& loc,
                             const ucc::misc::Symbol& name,
                             FunctionType* type);
                FunctionDecl(const ucc::parse::location& loc,
                             const ucc::misc::Symbol& name,
                             FunctionType* type,
                             CompoundStmt* compound);
                virtual ~FunctionDecl();

                const CompoundStmt* compound_get() const;
                CompoundStmt* compound_get();

                const Type* return_type_get() const;
                Type* return_type_get();

                const std::list<VarDecl*>& param_get() const;
                std::list<VarDecl*>& param_get();

                void return_type_set(Type* t);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                FunctionType* type_;
                CompoundStmt* compound_;
        };
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_FUNCTION_DECL_HH */
