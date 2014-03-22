#include <misc/error.hh>

#include <command/command.hh>

#include <ucc.hh>

int main(int argc, char *argv[])
{
    char *input_files[1] = { nullptr };

    command::Command::instance().description_set("ucc: Micro C compiler");
    command::Command::instance().option_set("file...");
    command::Command::instance().extra_args_set(input_files);

    command::Command::instance().parse_cmd(argc, argv);

    ucc::input_file = input_files[0];

    try
    {
        command::Command::instance().run();
    }
    catch (ucc::misc::Error& e)
    {
        std::cerr << e.msg_get() << std::endl;

        delete ucc::ast::the_ast;

        return e.error_code_get();
    }

    delete ucc::ast::the_ast;

    return 0;
}
