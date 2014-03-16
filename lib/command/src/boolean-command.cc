#include <command/boolean-command.hh>

using namespace command;

BooleanCommand::BooleanCommand(const std::string& opt,
                               const std::string& description,
                               const std::string& dependancies,
                               bool& b)
    : BasicCommand(opt, description, dependancies)
    , b_(b)
{}

BooleanCommand::~BooleanCommand()
{}

void BooleanCommand::run()
{
    b_ = true;
}
