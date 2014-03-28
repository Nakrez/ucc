#ifndef UCC_AST_ANY_LIST_HH
# define UCC_AST_ANY_LIST_HH

# include <list>
# include <memory>

# include <ast/visitor.hh>

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

                const std::list<std::shared_ptr<T>>& list_get() const;
                std::list<std::shared_ptr<T>>& list_get();

                void push_back(std::shared_ptr<T> elem);

                void splice_front(AnyList<T>& list);
                void splice_back(AnyList<T>& list);

                virtual void accept(Visitor& v);
                virtual void accept(ConstVisitor& v) const;

                template <class U>
                AnyList<U>* convert();

            protected:
                std::list<std::shared_ptr<T>> list_;
        };
    } // namespace ast
} // namespace ucc

# include <ast/any-list.hxx>

#endif /* !UCC_AST_ANY_LIST_HH */
