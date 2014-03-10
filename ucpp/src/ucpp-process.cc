#include <ucpp-process.hh>

UcppProcess::UcppProcess(const std::string& in, const std::string& out)
    : input_(in)
    , output_(out)
    , soutput_(nullptr)
{}

UcppProcess::~UcppProcess()
{
    if (soutput_ != nullptr && soutput_ != &std::cout)
    {
        std::ofstream *out = dynamic_cast<std::ofstream*>(soutput_);

        if (out)
            out->close();

        delete out;
    }
}

void UcppProcess::init()
{
    if (output_ == "-")
        soutput_ = &std::cout;
    else
    {
        std::ofstream *out = new std::ofstream;

        out->open(output_);

        if (!out->is_open())
        {
            delete out;
            std::cerr << "Error opening " << output_ << std::endl;
            /* XXX: throw */
            return;
        }

        soutput_ = out;
    }

    if (input_ == "-")
        lexer_.push_state(&std::cin);
    else
    {
        std::ifstream *in = new std::ifstream;

        in->open(input_);

        if (!in->is_open())
        {
            delete in;
            std::cerr << "Error opening " << input_ << std::endl;
            /* XXX: throw */
            return;
        }

        lexer_.push_state(in);
    }
}

void UcppProcess::process()
{
    while (!lexer_.eof())
        ;
}
