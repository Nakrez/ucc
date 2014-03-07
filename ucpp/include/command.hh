#ifndef COMMAND_HH
# define COMMAND_HH

# include <iostream>
# include <list>

# include <basic-command.hh>

class Command
{
    Command(const Command&) = delete;
    Command operator=(const Command&) = delete;

    public:
        static Command& instance();

        void register_command(BasicCommand* cmd);

    private:
        Command();
        ~Command();

    private:
        std::list<BasicCommand*> rcmd_;
};

#endif /* !COMMAND_HH */
