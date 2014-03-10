#ifndef LEXER_STATE_HH
# define LEXER_STATE_HH

# include <iostream>
# include <fstream>

class LexerState
{
    public:
        LexerState(std::istream *input, std::ostream *out);
        ~LexerState();

        bool eof() const;

        unsigned line_get() const;
        unsigned column_get() const;

        void preprocess_line_set(bool b);

    private:
        std::istream *in_;
        std::ostream *out_;

        unsigned column_;
        unsigned line_;

        bool preprocess_line_;

        std::string line_buffer_;
};

# include <lexer-state.hxx>

#endif /* !LEXER_STATE_HH */
