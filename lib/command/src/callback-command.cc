#include <command/callback-command.hh>

namespace command
{
    CallbackCommand::CallbackCommand(const std::string& opt,
                                     const std::string& description,
                                     const std::string& dependancies,
                                     CallbackHandler handler)
        : BasicCommand(opt, description, dependancies)
        , handler_(handler)
    {}

    CallbackCommand::~CallbackCommand()
    {}

    void CallbackCommand::run()
    {
        handler_();
    }
} // namespace command
