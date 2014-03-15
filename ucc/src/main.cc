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

    command::Command::instance().run();

    return 0;
}
