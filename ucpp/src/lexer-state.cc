#include <lexer-state.hh>

LexerState::LexerState(std::istream *input, std::ostream *out)
    : in_(input)
    , out_(out)
    , column_(1)
    , line_(1)
    , preprocess_line_(false)
{

}

LexerState::~LexerState()
{
    if (in_ != &std::cin)
    {
        std::ifstream *in = dynamic_cast<std::ifstream*>(in);

        if (in)
        {
            in->close();
            delete in;
        }
    }
}
