#include <ucc.hh>

#include <command/command.hh>

#include <parse/driver.hh>

REGISTER_COMMAND(parse, "p|parse", "Parse the input file",
                 parse_file, "");

REGISTER_BOOLEAN(parse_trace, "parse-trace", "Activate parse trace",
                 ucc::parse::parse_trace, "");

void parse_file()
{
    ucc::parse::Driver driver;

    driver.parse_file(ucc::input_file);

    driver.error_.throw_on_error();
}
