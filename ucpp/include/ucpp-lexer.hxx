#ifndef UCPP_LEXER_HXX
# define UCPP_LEXER_HXX

# include <ucpp-lexer.hh>

inline void UcppLexer::push_state(std::istream *stream)
{
    buffers_.push(LexerState(stream, out_));
}

inline void UcppLexer::pop_state()
{
    buffers_.pop();
}

inline bool UcppLexer::eof() const
{
    return buffers_.top().eof();
}

inline void UcppLexer::preprocess_line_set(bool b)
{
    buffers_.top().preprocess_line_set(b);
}

#endif /* !UCPP_LEXER_HXX */
