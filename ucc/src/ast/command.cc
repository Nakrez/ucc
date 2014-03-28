#include <ucc.hh>

#include <command/command.hh>

#include <ast/pretty-printer.hh>

REGISTER_COMMAND(pretty, "pretty-print", "Pretty print the input file (debug "
                 "purpose)", pretty_print, "parse");

void pretty_print()
{
    ucc::ast::PrettyPrinter printer(std::cout);

    assert(ucc::ast::the_ast &&
           "Internal error: No ast retrieved by the parser");
    printer(*ucc::ast::the_ast);
    std::cout << std::endl;
}
