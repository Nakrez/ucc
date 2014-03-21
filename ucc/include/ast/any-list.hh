#ifndef UCC_AST_ANY_LIST_HH
# define UCC_AST_ANY_LIST_HH

# include <list>

# include <ast/ast.hh>

namespace ucc
{
    namespace ast
    {
        template <class T>
        class AnyList : public Ast
        {
            public:
                AnyList(const ucc::parse::location& loc);
                virtual ~AnyList();

                const std::list<T*>& list_get() const;
                std::list<T*>& list_get();

                void push_back(T* elem);

                void splice_front(AnyList<T>& list);
                void splice_back(AnyList<T>& list);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

            protected:
                std::list<T*> list_;
        };
    } // namespace ast
} // namespace ucc

# include <ast/any-list.hxx>

#endif /* !UCC_AST_ANY_LIST_HH */
