#ifndef COMMAND_HH
# define COMMAND_HH

# include <iostream>
# include <list>

# include <command/basic-command.hh>
# include <command/callback-command.hh>

# define REGISTER_COMMAND(name, opt, description, callback, dep)            \
    extern void (callback)();                                               \
    static command::CallbackCommand callback##name(opt, description, dep,   \
                                                   callback);

namespace command
{
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

            void option_set(const std::string& s);
            void description_set(const std::string& s);
            void extra_args_set(char **args);

        private:
            Command();
            ~Command();

        private:
            std::list<BasicCommand*> registered_cmd_;
            std::list<BasicCommand*> enabled_cmd_;

            std::string options_;
            std::string desc_;
            char **extra_args_;
    };
} // namespace command

#endif /* !COMMAND_HH */
