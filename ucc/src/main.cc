#include <command/command.hh>

int main(int argc, char *argv[])
{
    char *input_files[1] = { nullptr };

    command::Command::instance().description_set("ucc: Micro C compiler");
    command::Command::instance().option_set("file...");
    command::Command::instance().extra_args_set(input_files);

    command::Command::instance().parse_cmd(argc, argv);
    command::Command::instance().enable_cmd("parse");
    command::Command::instance().run();

    return 0;
}
