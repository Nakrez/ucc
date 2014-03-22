#include <misc/indent.hh>
#include <iomanip>
#include <ostream>

namespace ucc
{
    namespace misc
    {
        static inline long int& indent_level_get(std::ostream& o)
        {
            static const long int indent_index = std::ios::xalloc();

            return o.iword(indent_index);
        }

        std::ostream& iendl(std::ostream& o)
        {
            o << std::endl;

            char fill = o.fill(' ');

            return o << std::setw(indent_level_get(o)) << "" << std::setfill(fill);
        }

        std::ostream& incendl(std::ostream& o)
        {
            indent_level_get(o) += 4;

            return o << iendl;
        }

        std::ostream& decendl(std::ostream& o)
        {
            indent_level_get(o) -= 4;

            return o << iendl;
        }
    } // namespace misc
} // namespace ucc
