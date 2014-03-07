#ifndef BASIC_COMMAND_HH
# define BASIC_COMMAND_HH

# include <string>

class Command;

class BasicCommand
{
    public:
        BasicCommand(const std::string& opt,
                     const std::string& description,
                     const std::string& dependancies);
        virtual ~BasicCommand();

        virtual void run() = 0;

        const std::string& long_opt_get() const;
        int short_opt_get() const;
        const std::string& desc_get() const;
        const std::string& dep_get() const;

    private:
        std::string long_opt_;
        int short_opt_;
        std::string desc_;
        std::string dep_;
};

#endif /* !BASIC_COMMAND_HH */
