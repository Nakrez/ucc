#ifndef BOOLEAN_COMMAND_HH
# define BOOLEAN_COMMAND_HH

# include <command/basic-command.hh>

namespace command
{
    class BooleanCommand : public BasicCommand
    {
        public:
            BooleanCommand(const std::string& opt,
                           const std::string& description,
                           const std::string& dependancies,
                           bool& b);
            virtual ~BooleanCommand();

            virtual void run();

        private:
            bool& b_;
    };
} // namespace command

#endif /* !BOOLEAN_COMMAND_HH */
