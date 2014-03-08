#include <ucpp.hh>

#include <ucpp-process.hh>

namespace ucpp
{
    REGISTER_COMMAND(parse, "", "Preprocess the input file", ucpp, "");

    std::string input_file = "-";
    std::string output_file = "-";

    void ucpp()
    {
        UcppProcess processor(input_file, output_file);

        std::cout << "In: " << input_file << ", Out: " << output_file << std::endl;
        processor.init();
        processor.process();
    }
}
