#ifndef UCPP_LEXER_HH
# define UCPP_LEXER_HH

# include <string>
# include <stack>
# include <iostream>
# include <fstream>

# include <lexer-state.hh>

class UcppLexer
{
    public:
        UcppLexer();
        UcppLexer(std::ostream *out);
        ~UcppLexer();

        bool push_state(const std::string& file);
        void push_state(std::istream *stream);

        void pop_state();
        bool eof() const;

        void preprocess_line_set(bool b);

        void next();

    private:
        std::stack<LexerState> buffers_;

        std::ostream *out_;
};

# include <ucpp-lexer.hxx>

#endif /* !UCPP_LEXER_HH */
