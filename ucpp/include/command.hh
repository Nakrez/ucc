#ifndef COMMAND_HH
# define COMMAND_HH

# include <iostream>
# include <list>

# include <basic-command.hh>
# include <callback-command.hh>

# define REGISTER_COMMAND(name, opt, description, callback, dep)            \
    extern void (callback)();                                                 \
    static CallbackCommand callback##name(opt, description, dep, callback);

class Command
{
    Command(const Command&) = delete;
    Command operator=(const Command&) = delete;

    public:
        static Command& instance();

        const std::list<BasicCommand*> registered_cmd_get() const;
        void enable_cmd(BasicCommand* cmd);
        void enable_cmd(const std::string& cmd);
        bool is_enable(const std::string& cmd) const;

        void register_command(BasicCommand* cmd);
        void parse_cmd(int argc, char *argv[]);

        void run();

    private:
        Command();
        ~Command();

    private:
        std::list<BasicCommand*> registered_cmd_;
        std::list<BasicCommand*> enabled_cmd_;
};

#endif /* !COMMAND_HH */
