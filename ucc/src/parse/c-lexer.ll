
%{

# include <parse/driver.hh>

typedef ucc::parse::Parser::token token;

# undef yywrap
# define yywrap() 1
# define yyterminate() return token::END_OF_FILE

static void comment(ucc::parse::Driver& driver, ucc::parse::location* yylloc);
static ucc::parse::Parser::token_type check_type(ucc::parse::Driver& driver);

# define ATTRIBUTE(tok)                                 \
    if (driver.in_attribute_)                           \
        return tok;                                     \
    else                                                \
    {                                                   \
        yylval->symbol = new ucc::misc::Symbol(yytext); \
        return token::IDENTIFIER;                       \
    }

%}

%{
# define YY_USER_ACTION yylloc->columns(yyleng);
%}

%option noyywrap

%e  1019
%p  2807
%n  371
%k  284
%a  1213
%o  1117

O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\f]

%%

%{
    yylloc->step();
%}

"/*"                    { comment(driver, yylloc); }
"//".*                  {
                          yylloc->lines(yyleng);
                          yylloc->step();
                        }
"#".*                   { /* ignore #line file */ }

"auto"                  { return token::AUTO; }
"break"                 { return token::BREAK; }
"case"                  { return token::CASE; }
"char"                  { return token::CHAR; }
"const"                 { return token::CONST; }
"__const"               { return token::CONST; }
"const__"               { return token::CONST; }
"__const__"             { return token::CONST; }
"continue"              { return token::CONTINUE; }
"default"               { return token::DEFAULT; }
"do"                    { return token::DO; }
"double"                { return token::DOUBLE; }
"else"                  { return token::ELSE; }
"enum"                  { return token::ENUM; }
"extern"                { return token::EXTERN; }
"float"                 { return token::FLOAT; }
"for"                   { return token::FOR; }
"goto"                  { return token::GOTO; }
"if"                    { return token::IF; }
"inline"                { return token::INLINE; }
"int"                   { return token::INT; }
"long"                  { return token::LONG; }
"register"              { return token::REGISTER; }
"restrict"              { return token::RESTRICT; }
"__restrict"            { return token::RESTRICT; }
"restrict__"            { return token::RESTRICT; }
"__restrict__"          { return token::RESTRICT; }
"return"                { return token::RETURN; }
"short"                 { return token::SHORT; }
"signed"                { return token::SIGNED; }
"sizeof"                { return token::SIZEOF; }
"static"                { return token::STATIC; }
"struct"                { return token::STRUCT; }
"switch"                { return token::SWITCH; }
"typedef"               { return token::TYPEDEF; }
"union"                 { return token::UNION; }
"unsigned"              { return token::UNSIGNED; }
"void"                  { return token::VOID; }
"volatile"              { return token::VOLATILE; }
"__volatile"            { return token::VOLATILE; }
"volatile__"            { return token::VOLATILE; }
"__volatile__"          { return token::VOLATILE; }
"while"                 { return token::WHILE; }

"asm"                   { return token::ASM; }
"__asm"                 { return token::ASM; }
"asm__"                 { return token::ASM; }
"__asm__"               { return token::ASM; }

"__attribute__"         {
                          driver.in_attribute_ = true;
                          return token::ATTRIBUTE;
                        }

"alias"                 { ATTRIBUTE(token::ALIAS) }
"__alias"               { ATTRIBUTE(token::ALIAS) }
"__alias__"             { ATTRIBUTE(token::ALIAS) }
"alias__"               { ATTRIBUTE(token::ALIAS) }

"aligned"               { ATTRIBUTE(token::ALIGNED) }
"__aligned"             { ATTRIBUTE(token::ALIGNED) }
"__aligned__"           { ATTRIBUTE(token::ALIGNED) }
"aligned__"             { ATTRIBUTE(token::ALIGNED) }

"always_inline"         { ATTRIBUTE(token::ALWAYS_INLINE) }
"__always_inline"       { ATTRIBUTE(token::ALWAYS_INLINE) }
"__always_inline__"     { ATTRIBUTE(token::ALWAYS_INLINE) }
"always_inline__"       { ATTRIBUTE(token::ALWAYS_INLINE) }

"cdecl"                 { ATTRIBUTE(token::CDECL) }
"__cdecl"               { ATTRIBUTE(token::CDECL) }
"__cdecl__"             { ATTRIBUTE(token::CDECL) }
"cdecl__"               { ATTRIBUTE(token::CDECL) }

"cleanup"               { ATTRIBUTE(token::CLEANUP) }
"__cleanup"             { ATTRIBUTE(token::CLEANUP) }
"__cleanup__"           { ATTRIBUTE(token::CLEANUP) }
"cleanup__"             { ATTRIBUTE(token::CLEANUP) }

"constructor"           { ATTRIBUTE(token::CONSTRUCTOR) }
"__constructor"         { ATTRIBUTE(token::CONSTRUCTOR) }
"__constructor__"       { ATTRIBUTE(token::CONSTRUCTOR) }
"constructor__"         { ATTRIBUTE(token::CONSTRUCTOR) }

"deprecated"            { ATTRIBUTE(token::DEPRECATED) }
"__deprecated"          { ATTRIBUTE(token::DEPRECATED) }
"deprecated__"          { ATTRIBUTE(token::DEPRECATED) }
"__deprecated__"        { ATTRIBUTE(token::DEPRECATED) }

"destructor"            { ATTRIBUTE(token::DESTRUCTOR) }
"__destructor"          { ATTRIBUTE(token::DESTRUCTOR) }
"destructor__"          { ATTRIBUTE(token::DESTRUCTOR) }
"__destructor__"        { ATTRIBUTE(token::DESTRUCTOR) }

"dllexport"             { ATTRIBUTE(token::DLLEXPORT) }
"__dllexport"           { ATTRIBUTE(token::DLLEXPORT) }
"dllexport__"           { ATTRIBUTE(token::DLLEXPORT) }
"__dllexport__"         { ATTRIBUTE(token::DLLEXPORT) }

"dllimport"             { ATTRIBUTE(token::DLLIMPORT) }
"__dllimport"           { ATTRIBUTE(token::DLLIMPORT) }
"dllimport__"           { ATTRIBUTE(token::DLLIMPORT) }
"__dllimport__"         { ATTRIBUTE(token::DLLIMPORT) }

"format"                { ATTRIBUTE(token::FORMAT) }
"__format"              { ATTRIBUTE(token::FORMAT) }
"format__"              { ATTRIBUTE(token::FORMAT) }
"__format__"            { ATTRIBUTE(token::FORMAT) }

"leaf"                  { ATTRIBUTE(token::LEAF) }
"__leaf"                { ATTRIBUTE(token::LEAF) }
"leaf__"                { ATTRIBUTE(token::LEAF) }
"__leaf__"              { ATTRIBUTE(token::LEAF) }

"nonnull"               { ATTRIBUTE(token::NONNULL) }
"__nonnull"             { ATTRIBUTE(token::NONNULL) }
"nonnull__"             { ATTRIBUTE(token::NONNULL) }
"__nonnull__"           { ATTRIBUTE(token::NONNULL) }

"noreturn"              { ATTRIBUTE(token::NORETURN) }
"__noreturn"            { ATTRIBUTE(token::NORETURN) }
"noreturn__"            { ATTRIBUTE(token::NORETURN) }
"__noreturn__"          { ATTRIBUTE(token::NORETURN) }

"nothrow"               { ATTRIBUTE(token::NOTHROW) }
"__nothrow"             { ATTRIBUTE(token::NOTHROW) }
"nothrow__"             { ATTRIBUTE(token::NOTHROW) }
"__nothrow__"           { ATTRIBUTE(token::NOTHROW) }

"pure"                  { ATTRIBUTE(token::PURE) }
"__pure"                { ATTRIBUTE(token::PURE) }
"pure__"                { ATTRIBUTE(token::PURE) }
"__pure__"              { ATTRIBUTE(token::PURE) }

"printf"                { ATTRIBUTE(token::PRINTF) }
"__print"               { ATTRIBUTE(token::PRINTF) }
"printf__"              { ATTRIBUTE(token::PRINTF) }
"__printf__"            { ATTRIBUTE(token::PRINTF) }

"scanf"                 { ATTRIBUTE(token::SCANF) }
"__scanf"               { ATTRIBUTE(token::SCANF) }
"scanf__"               { ATTRIBUTE(token::SCANF) }
"__scanf__"             { ATTRIBUTE(token::SCANF) }

"_Alignas"              { return token::ALIGNAS; }
"_Alignof"              { return token::ALIGNOF; }
"_Atomic"               { return token::ATOMIC; }
"_Bool"                 { return token::BOOL; }
"_Complex"              { return token::COMPLEX; }
"_Generic"              { return token::GENERIC; }
"_Imaginary"            { return token::IMAGINARY; }
"_Noreturn"             { return token::NORETURN; }
"_Static_assert"        { return token::STATIC_ASSERT; }
"_Thread_local"         { return token::THREAD_LOCAL; }
"__func__"              { return token::FUNC_NAME; }

{L}{A}*                 {
                          yylval->symbol = new ucc::misc::Symbol(yytext);
                          return check_type(driver);
                        }

{HP}{H}+{IS}?               {
                                yylval->int_ = strtol(yytext, NULL, 16);
                                return token::I_CONSTANT;
                            }
{NZ}{D}*{IS}?               {
                                yylval->int_ = atoi(yytext);
                                return token::I_CONSTANT;
                            }
"0"{O}*{IS}?                {
                                yylval->int_ = atoi(yytext);
                                return token::I_CONSTANT;
                            }
{CP}?"'"([^'\\\n]|{ES})+"'" {
                                std::string s(yytext, 1, strlen(yytext) - 2);

                                if (s.size() == 1)
                                    yylval->int_ = s[0];
                                else if (s[0] == '\\')
                                {
                                    switch (s[1])
                                    {
                                        case 'a':
                                            yylval->int_ = '\a';
                                            break;
                                        case 'b':
                                            yylval->int_ = '\b';
                                            break;
                                        case 'f':
                                            yylval->int_ = '\f';
                                            break;
                                        case 'n':
                                            yylval->int_ = '\n';
                                            break;
                                        case 'r':
                                            yylval->int_ = '\r';
                                            break;
                                        case 't':
                                            yylval->int_ = '\t';
                                            break;
                                        case 'v':
                                            yylval->int_ = '\v';
                                            break;
                                        case '\\':
                                            yylval->int_ = '\\';
                                            break;
                                        case '"':
                                            yylval->int_ = '\"';
                                            break;
                                        case '0':
                                            yylval->int_ = '\0';
                                            break;
                                        default:
                                            driver.error_
                                                << ucc::misc::Error::Type::lex
                                                << "Unexpected escape char"
                                                << yytext << std::endl;
                                            yylval->int_ = '\0';
                                            break;
                                    }
                                }
                                else
                                    yylval->int_ = '\0';

                                return token::I_CONSTANT;
                            }

{D}+{E}{FS}?                {
                                char *endptr;
                                yylval->float_ = strtold(yytext, &endptr);
                                return token::F_CONSTANT;
                            }
{D}*"."{D}+{E}?{FS}?        {
                                char *endptr;
                                yylval->float_ = strtold(yytext, &endptr);
                                return token::F_CONSTANT;
                            }
{D}+"."{E}?{FS}?            {
                                char *endptr;
                                yylval->float_ = strtold(yytext, &endptr);
                                return token::F_CONSTANT;
                            }
{HP}{H}+{P}{FS}?            {
                                char *endptr;
                                yylval->float_ = strtold(yytext, &endptr);
                                return token::F_CONSTANT;
                            }
{HP}{H}*"."{H}+{P}{FS}?     {
                                char *endptr;
                                yylval->float_ = strtold(yytext, &endptr);
                                return token::F_CONSTANT;
                            }
{HP}{H}+"."{P}{FS}?         {
                                char *endptr;
                                yylval->float_ = strtold(yytext, &endptr);
                                return token::F_CONSTANT;
                            }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+   {
                                        std::string* str;
                                        str = new std::string(yytext);
                                        yylval->string_ = str;
                                        return token::STRING_LITERAL;
                                    }

"..."                   { return token::ELLIPSIS; }
">>="                   { return token::RIGHT_ASSIGN; }
"<<="                   { return token::LEFT_ASSIGN; }
"+="                    { return token::ADD_ASSIGN; }
"-="                    { return token::SUB_ASSIGN; }
"*="                    { return token::MUL_ASSIGN; }
"/="                    { return token::DIV_ASSIGN; }
"%="                    { return token::MOD_ASSIGN; }
"&="                    { return token::AND_ASSIGN; }
"^="                    { return token::XOR_ASSIGN; }
"|="                    { return token::OR_ASSIGN; }
">>"                    { return token::RIGHT_OP; }
"<<"                    { return token::LEFT_OP; }
"++"                    { return token::INC_OP; }
"--"                    { return token::DEC_OP; }
"->"                    { return token::PTR_OP; }
"&&"                    { return token::AND_OP; }
"||"                    { return token::OR_OP; }
"<="                    { return token::LE_OP; }
">="                    { return token::GE_OP; }
"=="                    { return token::EQ_OP; }
"!="                    { return token::NE_OP; }
";"                     { return token::SEMI_COLON; }
("{"|"<%")              { driver.sym_.scope_begin(); return token::LBRACE; }
("}"|"%>")              { driver.sym_.scope_end(); return token::RBRACE; }
","                     { return token::COMA; }
":"                     { return token::COLON; }
"="                     { return token::ASSIGN; }
"("                     { return token::LPAR; }
")"                     { return token::RPAR; }
("["|"<:")              { return token::LBRACKET; }
("]"|":>")              { return token::RBRACKET; }
"."                     { return token::DOT; }
"&"                     { return token::B_AND; }
"!"                     { return token::NOT; }
"~"                     { return token::TILDE; }
"-"                     { return token::MINUS; }
"+"                     { return token::PLUS; }
"*"                     { return token::TIME; }
"/"                     { return token::DIV; }
"%"                     { return token::MOD; }
"<"                     { return token::L_OP; }
">"                     { return token::G_OP; }
"^"                     { return token::XOR; }
"|"                     { return token::B_OR; }
"?"                     { return token::TERNARY; }

[\n]+                   {
                          yylloc->lines(yyleng);
                          yylloc->step();
                        }
{WS}                    { yylloc->step(); }
.                       { driver.error_ << ucc::misc::Error::Type::lex
                                        << "Unexpected char "
                                        << yytext << std::endl;
                        }

%%

static void comment(ucc::parse::Driver& driver, ucc::parse::location* yylloc)
{
    int c;

    while ((c = yyinput()) != 0)
    {
        yylloc->columns(1);

        if (c == '*')
        {
            while ((c = yyinput()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
        else if (c == '\n')
        {
            yylloc->lines();
            yylloc->step();
        }
        else if (c == ' ' || c == '\t')
            yylloc->step();
    }

    driver.error_ << ucc::misc::Error::Type::lex
                  << "Unterminated comment" << std::endl;
}

static ucc::parse::Parser::token_type check_type(ucc::parse::Driver& driver)
{
    switch (driver.sym_.get(yytext))
    {
        case token::TYPEDEF_NAME:
            return token::TYPEDEF_NAME;
        case token::ENUM_CONSTANT:
            return token::ENUM_CONSTANT;
        default:
            return token::IDENTIFIER;
    }
}

void ucc::parse::Driver::lexer_begin()
{
    yy_flex_debug = trace_lexer_;

    if (file_.empty() || file_ == "-")
        yyin = stdin;
    else if (!(yyin = fopen (file_.c_str(), "r")))
    {
        error_ << ucc::misc::Error::Type::lex
               << "Cannot open file " << file_ << std::endl;
    }

    yypush_buffer_state(yy_create_buffer(yyin, YY_BUF_SIZE));
}

void ucc::parse::Driver::lexer_end()
{
    yypop_buffer_state();

    if (!file_.empty() && file_ != "-")
        fclose(yyin);
}
