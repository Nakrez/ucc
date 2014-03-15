#include <ucc.hh>

#include <command/command.hh>

#include <parse/driver.hh>

REGISTER_COMMAND(parse, "p|parse", "Parse the input file",
                 parse_file, "");

void parse_file()
{
    ucc::parse::Driver driver;

    driver.parse_file(ucc::input_file);
}
