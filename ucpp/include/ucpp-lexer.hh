#ifndef UCPP_LEXER_HH
# define UCPP_LEXER_HH

# include <string>
# include <stack>
# include <iostream>
# include <fstream>

class UcppLexer
{
    public:
        UcppLexer();
        ~UcppLexer();

        bool push_state(const std::string& file);
        void push_state(std::istream *stream);

        void pop_state();

    private:
        std::stack<std::istream*> buffers_;
};

#endif /* !UCPP_LEXER_HH */
