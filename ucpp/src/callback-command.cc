#include <callback-command.hh>


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
