#ifndef CALLBACK_COMMAND_HH
# define CALLBACK_COMMAND_HH

# include <command/basic-command.hh>

namespace command
{
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
} // namespace command

#endif /* !CALLBACK_COMMAND_HH */
