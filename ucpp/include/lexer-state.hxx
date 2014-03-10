#ifndef LEXER_STATE_HXX
# define LEXER_STATE_HXX

# include <lexer-state.hh>

inline bool LexerState::eof() const
{
    if (!in_)
        return true;

    return in_->eof();
}

inline void LexerState::preprocess_line_set(bool b)
{
    preprocess_line_ = b;
}

inline unsigned LexerState::line_get() const
{
    return line_;
}

inline unsigned LexerState::column_get() const
{
    return column_;
}

#endif /* !LEXER_STATE_HXX */
