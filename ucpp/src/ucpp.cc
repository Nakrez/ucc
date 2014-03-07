#include <ucpp.hh>


namespace ucpp
{
    REGISTER_COMMAND(parse, "", "Preprocess the input file", ucpp, "");

    std::string input_file = "-";
    std::string output_file = "-";

    void ucpp()
    {
        std::cout << "Default action" << std::endl;
    }
}
