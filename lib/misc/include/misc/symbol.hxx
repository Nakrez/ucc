#ifndef SYMBOL_HXX
# define SYMBOL_HXX

# include <misc/symbol.hh>

const std::string& ucc::misc::Symbol::data_get() const
{
    return *data_;
}

#endif /* !SYMBOL_HXX */
