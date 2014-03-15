%{

# include <parse/driver.hh>

typedef ucc::parse::Parser::token token;

# undef yywrap
# define yywrap() 1
# define yyterminate() return token::END_OF_FILE

%}

%option noyywrap noinput batch stack noyy_top_state

%%
. {}
%%

void ucc::parse::Driver::lexer_begin()
{
    yy_flex_debug = trace_lexer_;

    if (file_.empty() || file_ == "-")
        yyin = stdin;
    else if (!(yyin = fopen (file_.c_str(), "r")))
    {
        std::cerr << "Cannot open file " << file_ << std::endl;
        exit (EXIT_FAILURE);
    }
}

void ucc::parse::Driver::lexer_end()
{
    if (!file_.empty() && file_ != "-")
        fclose(yyin);
}
