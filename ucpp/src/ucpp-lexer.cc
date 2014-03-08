#include <ucpp-lexer.hh>

UcppLexer::UcppLexer()
{}

UcppLexer::~UcppLexer()
{
    while (buffers_.size() > 0)
    {
        if (buffers_.top() != &std::cin)
        {
            std::ifstream *in = dynamic_cast<std::ifstream*>(buffers_.top());

            in->close();

            delete in;
        }

        buffers_.pop();
    }
}

bool UcppLexer::push_state(const std::string& file)
{
    std::ifstream *stream = new std::ifstream;

    stream->open(file);

    if (!stream->is_open())
    {
        delete stream;
        return false;
    }

    buffers_.push(stream);

    return true;
}

void UcppLexer::push_state(std::istream *stream)
{
    buffers_.push(stream);
}

void UcppLexer::pop_state()
{
    if (buffers_.size() > 0)
    {
        if (buffers_.top() != &std::cin)
        {
            std::ifstream *in = dynamic_cast<std::ifstream*>(buffers_.top());

            in->close();

            delete in;
        }

        buffers_.pop();
    }
}
