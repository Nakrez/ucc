#include <command.hh>

Command::Command()
{}

Command::~Command()
{}

Command& Command::instance()
{
    static Command command;

    return command;
}

void Command::register_command(BasicCommand* cmd)
{
    for (BasicCommand* it_cmd : rcmd_)
    {
        if (it_cmd->long_opt_get() == cmd->long_opt_get() ||
            it_cmd->short_opt_get() == cmd->short_opt_get())
            std::cout << "Warning options already defined ("
                      << cmd->long_opt_get() << ", " << cmd->short_opt_get()
                      << ")" << std::endl;
    }

}
