#ifndef CONSTNESS_HH
# define CONSTNESS_HH

namespace ucc
{
    namespace misc
    {
        template <typename T>
        struct const_type
        {
            typedef const T type;
        };

        template <typename T>
        struct nonconst_type
        {
            typedef T type;
        };
    } // namespace misc
} // namespace ucc

#endif /* !CONSTNESS_HH */
