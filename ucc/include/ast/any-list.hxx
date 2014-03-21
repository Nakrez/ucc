#ifndef UCC_AST_ANY_LIST_HXX
# define UCC_AST_ANY_LIST_HXX

# include <ast/any-list.hh>

namespace ucc
{
    namespace ast
    {
        template <class T>
        AnyList<T>::AnyList(const ucc::parse::location& loc)
            : Ast(loc)
        {}

        template <class T>
        AnyList<T>::~AnyList()
        {}

        template <class T>
        const std::list<T*>& AnyList<T>::list_get() const
        {
            return list_;
        }

        template <class T>
        std::list<T*>& AnyList<T>::list_get()
        {
            return list_;
        }

        template <class T>
        void AnyList<T>::push_back(T* elem)
        {
            list_.push_back(elem);
        }

        template <class T>
        void AnyList<T>::accept(Visitor& v)
        {
            v(*this);
        }

        template <class T>
        void AnyList<T>::accept(ConstVisitor& v) const
        {
            v(*this);
        }
    } // namespace ast
} // namespace ucc

#endif /* !UCC_AST_ANY_LIST_HXX */
