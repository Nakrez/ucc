#include <misc/symbol.hh>

using namespace ucc;
using namespace misc;

Symbol::Symbol(const std::string& s)
    : data_(&(*(symbol_set_get().insert(s).first)))
{}

Symbol::Symbol(const char* s)
    : data_(&(*(symbol_set_get().insert(s).first)))
{}

Symbol::~Symbol()
{}

Symbol& Symbol::operator=(const Symbol& s)
{
    if (this != &s)
        data_ = s.data_;

    return *this;
}

std::set<std::string>& Symbol::symbol_set_get()
{
    static std::set<std::string> set;

    return set;
}

std::ostream& operator<<(std::ostream& o, const ucc::misc::Symbol& s)
{
    o << s.data_get();

    return o;
}
