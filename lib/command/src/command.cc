#include <cstring>
#include <sstream>

#include <argp.h>

#include <command/command.hh>

namespace command
{
    Command::Command()
    {}

    Command::~Command()
    {}

    Command& Command::instance()
    {
        static Command command;

        return command;
    }

    const std::list<BasicCommand*> Command::registered_cmd_get() const
    {
        return registered_cmd_;
    }

    bool Command::is_enable(const std::string& cmd) const
    {
        std::list<BasicCommand*>::const_iterator it;

        for (it = enabled_cmd_.cbegin(); it != enabled_cmd_.cend(); ++it)
        {
            if ((*it)->long_opt_get() == cmd)
                return true;
        }

        return false;
    }

    void Command::enable_cmd(BasicCommand* cmd)
    {
        if (cmd->dep_get() != "")
        {
            std::istringstream stream(cmd->dep_get());

            do
            {
                std::string dep;
                stream >> dep;

                if (!is_enable(dep))
                {
                    for (auto c : registered_cmd_)
                    {
                        if (c->long_opt_get() == dep)
                        {
                            enable_cmd(c);
                            break;
                        }
                    }
                }
            } while (stream);
        }

        enabled_cmd_.push_back(cmd);
    }

    void Command::enable_cmd(const std::string& cmd)
    {
        for (BasicCommand* c : registered_cmd_)
        {
            if (c->long_opt_get() == cmd)
            {
                enable_cmd(c);
                return;
            }
        }
    }

    void Command::register_command(BasicCommand* cmd)
    {
        for (BasicCommand* it_cmd : registered_cmd_)
        {
            if ((it_cmd->long_opt_get() != "" &&
                        it_cmd->long_opt_get() == cmd->long_opt_get()) ||
                    (it_cmd->short_opt_get() != 0 &&
                     it_cmd->short_opt_get() == cmd->short_opt_get()))
                std::cout << "Warning options already defined ("
                    << cmd->long_opt_get() << ", " << cmd->short_opt_get()
                    << ")" << std::endl;
        }

        registered_cmd_.push_back(cmd);
    }

    static error_t parse_opt(int key, char* arg, struct argp_state* state)
    {
        switch (key)
        {
            case ARGP_KEY_ARG:
                if (state->arg_num >= 3)
                    argp_usage(state);
                else
                {
                    if (arg)
                        ((char **)state->input)[state->arg_num] = arg;
                }

                return 0;
            case ARGP_KEY_END:
                if (state->arg_num < 1)
                    argp_usage(state);
                return 0;
            default:
                for (auto it : Command::instance().registered_cmd_get())
                {
                    if (it->short_opt_get() == key)
                    {
                        Command::instance().enable_cmd(it);
                        return 0;
                    }
                }
        }

        return ARGP_ERR_UNKNOWN;
    }

    void Command::parse_cmd(int argc, char *argv[])
    {
        size_t cmd_size = registered_cmd_.size() + 1;
        struct argp_option available_options[cmd_size];
        size_t i = 0;

        std::memset(available_options, 0, sizeof (argp_option) * cmd_size);

        for (BasicCommand* cmd : registered_cmd_)
        {
            available_options[i].name = cmd->long_opt_get().c_str();
            available_options[i].key = cmd->short_opt_get();
            available_options[i].arg = nullptr;
            available_options[i].flags = 0;
            available_options[i].doc = cmd->desc_get().c_str();
            available_options[i].group = 0;

            ++i;
        }

        argp_child child[1] = { {nullptr, 0, nullptr, 0} };

        struct argp argp =
        {
            available_options,
            parse_opt,
            options_.c_str(),
            desc_.c_str(),
            child,
            nullptr,
            nullptr
        };

        argp_parse(&argp, argc, argv, 0, 0, extra_args_);
    }

    void Command::run()
    {
        for (auto cmd : enabled_cmd_)
            cmd->run();
    }

    void Command::option_set(const std::string& s)
    {
        options_ = s;
    }

    void Command::description_set(const std::string& s)
    {
        desc_ = s;
    }

    void Command::extra_args_set(char **args)
    {
        extra_args_ = args;
    }
} // namespace command
