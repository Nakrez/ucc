#include <iostream>
#include <command.hh>

int main (int argc, char *argv[])
{
    Command::instance().parse_cmd(argc, argv);
    Command::instance().enable_cmd("");
    Command::instance().run();

    return 0;
}
