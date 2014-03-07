#include <basic-command.hh>

BasicCommand::BasicCommand(const std::string& opt,
                           const std::string& description,
                           const std::string& dependancies)
    : desc_(description)
    , dep_(dependancies)
{}
BasicCommand::~BasicCommand()
{}

const std::string& BasicCommand::long_opt_get() const
{
    return long_opt_;
}

const std::string& BasicCommand::short_opt_get() const
{
    return short_opt_;
}

const std::string& BasicCommand::desc_get() const
{
    return desc_;
}

const std::string& BasicCommand::dep_get() const
{
    return dep_;
}
