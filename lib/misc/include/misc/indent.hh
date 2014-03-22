#ifndef UCC_MISC_INDENT_HH
# define UCC_MISC_INDENT_HH

# include <iosfwd>

namespace ucc
{
    namespace misc
    {
        std::ostream& iendl(std::ostream& o);
        std::ostream& incendl(std::ostream& o);
        std::ostream& decendl(std::ostream& o);
    } // namespace misc
} // namespace ucc

#endif /* !UCC_MISC_INDENT_HH */
