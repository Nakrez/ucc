#ifndef UCC_MISC_SYMBOL_HH
# define UCC_MISC_SYMBOL_HH

# include <string>
# include <set>

namespace ucc
{
    namespace misc
    {
        class Symbol
        {
            public:
                Symbol(const std::string& s);
                Symbol(const char* s);
                ~Symbol();

                const std::string& data_get() const;

            private:
                static std::set<std::string>& symbol_set_get();

            private:
                const std::string *data_;
        };
    } // namespace misc
} // namespace ucc

std::ostream& operator<<(std::ostream& o, const ucc::misc::Symbol& s);

# include <misc/symbol.hxx>

#endif /* !UCC_MISC_SYMBOL_HH */
