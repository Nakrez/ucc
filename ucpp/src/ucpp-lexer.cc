#include <ucpp-lexer.hh>

UcppLexer::UcppLexer()
    : out_(nullptr)
{}

UcppLexer::UcppLexer(std::ostream *out)
    : out_(out)
{}

UcppLexer::~UcppLexer()
{}

bool UcppLexer::push_state(const std::string& file)
{
    std::ifstream *stream = new std::ifstream;

    stream->open(file);

    if (!stream->is_open())
    {
        delete stream;
        return false;
    }

    buffers_.push(LexerState(stream, out_));

    return true;
}

void UcppLexer::next()
{
}
