#ifndef CALLBACK_COMMAND_HH
# define CALLBACK_COMMAND_HH

# include <basic-command.hh>

typedef void (*CallbackHandler)();

class CallbackCommand : public BasicCommand
{
    public:
        CallbackCommand(const std::string& opt,
                        const std::string& description,
                        const std::string& dependancies,
                        CallbackHandler handler);
        virtual ~CallbackCommand();

        virtual void run() override;

    private:
        CallbackHandler handler_;
};

#endif /* !CALLBACK_COMMAND_HH */
