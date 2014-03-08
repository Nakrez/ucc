#ifndef UCPP_PROCESS_HH
# define UCPP_PROCESS_HH

# include <string>
# include <iostream>
# include <fstream>

# include <ucpp-lexer.hh>

class UcppProcess
{
    public:
        UcppProcess(const std::string& in, const std::string& out);
        ~UcppProcess();

        void init();
        void process();

    private:
        std::string input_;
        std::string output_;

        std::ostream *soutput_;

        UcppLexer lexer_;
};

#endif /* !UCPP_PROCESS_HH */
