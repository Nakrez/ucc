#include <basic-command.hh>
#include <command.hh>

BasicCommand::BasicCommand(const std::string& opt,
                           const std::string& description,
                           const std::string& dependancies)
    : desc_(description)
    , dep_(dependancies)
{
    if (opt.size() > 2)
    {
        if (opt.at(1) == '|')
        {
            short_opt_ = opt.at(0);
            long_opt_ = opt.substr(2, opt.size() - 2);
        }
        else
            long_opt_ = opt;
    }
    else if (opt.size() == 1)
        short_opt_ = opt.at(0);

    Command::instance().register_command(this);
}

BasicCommand::~BasicCommand()
{}

const std::string& BasicCommand::long_opt_get() const
{
    return long_opt_;
}

int BasicCommand::short_opt_get() const
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
