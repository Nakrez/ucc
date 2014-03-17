%require "2.4"
%skeleton "glr.cc"

%code requires
{
# include <string>

    namespace ucc
    {
        namespace parse
        {
            class Driver;
        }
    }
}

%glr-parser

%define api.namespace { ucc::parse }

%define parser_class_name { Parser }

%debug
%defines
%verbose
%error-verbose
%locations

%parse-param { ucc::parse::Driver& driver }
%lex-param { ucc::parse::Driver& driver }

%union
{

}

%code
{
# include <parse/driver.hh>
}

%token  IDENTIFIER     "identifier"
        I_CONSTANT      "i_constant"
        F_CONSTANT      "f_constant"
        STRING_LITERAL  "string"
        TYPEDEF_NAME    "typedef_name"
        ENUM_CONSTANT   "enum_constant"

%token  AUTO            "auto"
        BREAK           "break"
        CASE            "case"
        CHAR            "char"
        CONST           "const"
        CONTINUE        "continue"
        DEFAULT         "default"
        DO              "do"
        DOUBLE          "double"
        ELSE            "else"
        ENUM            "enum"
        EXTERN          "extern"
        FLOAT           "float"
        FOR             "for"
        GOTO            "goto"
        IF              "if"
        INLINE          "inline"
        INT             "int"
        LONG            "long"
        REGISTER        "register"
        RESTRICT        "restrict"
        RETURN          "return"
        SHORT           "short"
        SIGNED          "signed"
        SIZEOF          "sizeof"
        STATIC          "static"
        STRUCT          "struct"
        SWITCH          "switch"
        TYPEDEF         "typedef"
        UNION           "union"
        UNSIGNED        "unsigned"
        VOID            "void"
        VOLATILE        "volatile"
        WHILE           "while"

        ASM             "__asm__"
        ATTRIBUTE       "__attribute__"

        ALIAS           "__alias__"
        ALIGNED         "__aligned__"
        ALWAYS_INLINE   "__always_inline__"
        CDECL           "__cdecl__"
        CLEANUP         "__cleanup__"
        CONSTRUCTOR     "__constructor__"
        DEPRECATED      "__deprecated__"
        DESTRUCTOR      "__destructor__"
        DLLEXPORT       "__dllexport__"
        DLLIMPORT       "__dllimport__"
        FORMAT          "__format__"
        LEAF            "__leaf__"
        NONNULL         "__nonnull__"
        NOTHROW         "__nothrow__"
        PRINTF          "__printf__"
        PURE            "__pure__"
        SCANF           "__scanf__"

        ALIGNAS         "_Alignas"
        ALIGNOF         "_Alignof"
        ATOMIC          "_Atomic"
        BOOL            "_Bool"
        COMPLEX         "_Complex"
        GENERIC         "_Generic"
        IMAGINARY       "_Imaginary"
        NORETURN        "_Noreturn"
        STATIC_ASSERT   "_Static_assert"
        THREAD_LOCAL    "_Thread_local"
        FUNC_NAME       "__func__"

        ELLIPSIS        "..."
        RIGHT_ASSIGN    ">>="
        LEFT_ASSIGN     "<<="
        ADD_ASSIGN      "+="
        SUB_ASSIGN      "-="
        MUL_ASSIGN      "*="
        DIV_ASSIGN      "/="
        MOD_ASSIGN      "%="
        AND_ASSIGN      "&="
        XOR_ASSIGN      "^="
        OR_ASSIGN       "|="

        RIGHT_OP        ">>"
        LEFT_OP         "<<"
        INC_OP          "++"
        DEC_OP          "--"
        PTR_OP          "->"
        AND_OP          "&&"
        OR_OP           "||"
        LE_OP           "<="
        GE_OP           ">="
        EQ_OP           "=="
        NE_OP           "!="

        SEMI_COLON      ";"
        LBRACE          "{"
        RBRACE          "}"
        COMA            ","
        COLON           ":"
        ASSIGN          "="
        LPAR            "("
        RPAR            ")"
        LBRACKET        "["
        RBRACKET        "]"
        DOT             "."
        B_AND           "&"
        NOT             "!"
        TILDE           "~"
        MINUS           "-"
        PLUS            "+"
        TIME            "*"
        DIV             "/"
        MOD             "%"
        L_OP            "<"
        G_OP            ">"
        XOR             "^"
        B_OR            "|"
        TERNARY         "?"

        END_OF_FILE 0   "eof"

%start translation_unit
%%

primary_expression
    : IDENTIFIER
    | constant
    | string
    | "(" expression ")"
    | generic_selection
    ;

constant
    : "i_constant"
    | "f_constant"
    | "enum_constant"
    ;

enumeration_constant        /* before it has been defined as such */
    : "identifier"
    ;

string
    : "string"
    | "__func__"
    ;

generic_selection
    : "_Generic" "(" assignment_expression "," generic_assoc_list ")"
    ;

generic_assoc_list
    : generic_association
    | generic_assoc_list "," generic_association
    ;

generic_association
    : type_name ":" assignment_expression
    | "default" ":" assignment_expression
    ;

postfix_expression
    : primary_expression
    | postfix_expression "[" expression "]"
    | postfix_expression "(" ")"
    | postfix_expression "(" argument_expression_list ")"
    | postfix_expression "." "identifier"
    | postfix_expression "->" "identifier"
    | postfix_expression "++"
    | postfix_expression "--"
    | "(" type_name ")" "{" initializer_list "}"
    | "(" type_name ")" "{" initializer_list "," "}"
    ;

argument_expression_list
    : assignment_expression
    | argument_expression_list "," assignment_expression
    ;

unary_expression
    : postfix_expression
    | "++" unary_expression
    | "--" unary_expression
    | unary_operator cast_expression
    | "sizeof" unary_expression
    | "sizeof" "(" type_name ")"
    | "_Alignof" "(" type_name ")"
    ;

unary_operator
    : "&"
    | "*"
    | "+"
    | "-"
    | "~"
    | "!"
    ;

cast_expression
    : unary_expression
    | "(" type_name ")" cast_expression
    ;

multiplicative_expression
    : cast_expression
    | multiplicative_expression "*" cast_expression
    | multiplicative_expression "/" cast_expression
    | multiplicative_expression "%" cast_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression "+" multiplicative_expression
    | additive_expression "-" multiplicative_expression
    ;

shift_expression
    : additive_expression
    | shift_expression "<<" additive_expression
    | shift_expression ">>" additive_expression
    ;

relational_expression
    : shift_expression
    | relational_expression "<" shift_expression
    | relational_expression ">" shift_expression
    | relational_expression "<=" shift_expression
    | relational_expression ">=" shift_expression
    ;

equality_expression
    : relational_expression
    | equality_expression "==" relational_expression
    | equality_expression "!=" relational_expression
    ;

and_expression
    : equality_expression
    | and_expression "&" equality_expression
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression "^" and_expression
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression "|" exclusive_or_expression
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression "&&" inclusive_or_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression "||" logical_and_expression
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression "?" expression ":" conditional_expression
    ;

assignment_expression
    : conditional_expression
    | unary_expression assignment_operator assignment_expression
    ;

assignment_operator
    : "="
    | "*="
    | "/="
    | "%="
    | "+="
    | "-="
    | "<<="
    | ">>="
    | "&="
    | "^="
    | "|="
    ;

expression
    : assignment_expression
    | expression "," assignment_expression
    ;

constant_expression
    : conditional_expression    /* with constraints */
    ;

declaration
    : declaration_specifiers ";"
    | declaration_specifiers init_declarator_list ";"
    | static_assert_declaration
    ;

declaration_specifiers
    : storage_class_specifier declaration_specifiers
    | storage_class_specifier
    | type_specifier declaration_specifiers
    | type_specifier
    | type_qualifier attribute_spec declaration_specifiers
    | type_qualifier declaration_specifiers
    | type_qualifier
    | type_qualifier attribute_spec
    | function_specifier declaration_specifiers
    | function_specifier
    | alignment_specifier declaration_specifiers
    | alignment_specifier
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list "," init_declarator
    ;

init_declarator
    : declarator "=" initializer
    | declarator
    ;

storage_class_specifier
    : "typedef" /* identifiers must be flagged as TYPEDEF_NAME */
    | "extern"
    | "static"
    | "_Thread_local"
    | "auto"
    | "register"
    ;

type_specifier
    : "void"
    | "char"
    | "short"
    | "int"
    | "long"
    | "float"
    | "double"
    | "signed"
    | "unsigned"
    | "_Bool"
    | "_Complex"
    | "_Imaginary"
    | atomic_type_specifier
    | struct_or_union_specifier
    | enum_specifier
    | enum_specifier attribute_spec
    | "typedef_name"
    ;

struct_or_union_specifier
    : struct_or_union "{" struct_declaration_list "}"
    | struct_or_union attribute_spec "{" struct_declaration_list "}"
    | struct_or_union "{" struct_declaration_list "}" attribute_spec
    | struct_or_union attribute_spec "{" struct_declaration_list "}" attribute_spec
    | struct_or_union "identifier" "{" struct_declaration_list "}"
    | struct_or_union attribute_spec "identifier"
    ;

struct_or_union
    : "struct"
    | "union"
    ;

struct_declaration_list
    : struct_declaration
    | struct_declaration_list struct_declaration
    ;

struct_declaration
    : specifier_qualifier_list ";"  /* for anonymous struct/union */
    | specifier_qualifier_list struct_declarator_list ";"
    | static_assert_declaration
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    | type_specifier
    | type_qualifier specifier_qualifier_list
    | type_qualifier
    ;

struct_declarator_list
    : struct_declarator
    | struct_declarator_list "," struct_declarator
    ;

struct_declarator
    : ":" constant_expression
    | declarator ":" constant_expression
    | declarator
    ;

enum_specifier
    : "enum" "{" enumerator_list "}"
    | "enum" "{" enumerator_list "," "}"
    | "enum" "identifier" "{" enumerator_list "}"
    | "enum" "identifier" "{" enumerator_list "," "}"
    | "enum" "identifier"
    ;

enumerator_list
    : enumerator
    | enumerator_list "," enumerator
    ;

enumerator  /* identifiers must be flagged as ENUMERATION_CONSTANT */
    : enumeration_constant "=" constant_expression
    | enumeration_constant
    ;

atomic_type_specifier
    : "_Atomic" "(" type_name ")"
    ;

type_qualifier
    : "const"
    | "restrict"
    | "volatile"
    | "_Atomic"
    ;

function_specifier
    : "inline"
    | "_Noreturn"
    ;

alignment_specifier
    : "_Alignas" "(" type_name ")"
    | "_Alignas" "(" constant_expression ")"
    ;

declarator
    : pointer direct_declarator
    | attribute_spec pointer direct_declarator
    | attribute_spec pointer direct_declarator attribute_spec
    | pointer direct_declarator attribute_spec
    | direct_declarator
    | attribute_spec direct_declarator
    | attribute_spec direct_declarator attribute_spec
    | direct_declarator attribute_spec
    ;

direct_declarator
    : "identifier"
    | "(" declarator ")"
    | direct_declarator "[" "]"
    | direct_declarator "[" "*" "]"
    | direct_declarator "[" "static" type_qualifier_list assignment_expression "]"
    | direct_declarator "[" "static" assignment_expression "]"
    | direct_declarator "[" type_qualifier_list "*" "]"
    | direct_declarator "[" type_qualifier_list "static" assignment_expression "]"
    | direct_declarator "[" type_qualifier_list assignment_expression "]"
    | direct_declarator "[" type_qualifier_list "]"
    | direct_declarator "[" assignment_expression "]"
    | direct_declarator "(" parameter_type_list ")"
    | direct_declarator "(" ")"
    | direct_declarator "(" identifier_list ")"
    ;

pointer
    : "*" type_qualifier_list pointer
    | "*" type_qualifier_list
    | "*" pointer
    | "*"
    ;

type_qualifier_list
    : type_qualifier
    | type_qualifier_list type_qualifier
    ;


parameter_type_list
    : parameter_list "," "..."
    | parameter_list
    ;

parameter_list
    : parameter_declaration
    | parameter_list "," parameter_declaration
    ;

parameter_declaration
    : declaration_specifiers declarator
    | declaration_specifiers abstract_declarator
    | declaration_specifiers
    ;

identifier_list
    : "identifier"
    | identifier_list "," "identifier"
    ;

type_name
    : specifier_qualifier_list abstract_declarator
    | specifier_qualifier_list
    ;

abstract_declarator
    : pointer direct_abstract_declarator
    | pointer
    | direct_abstract_declarator
    ;

direct_abstract_declarator
    : "(" abstract_declarator ")"
    | "[" "]"
    | "[" "*" "]"
    | "[" "static" type_qualifier_list assignment_expression "]"
    | "[" "static" assignment_expression "]"
    | "[" type_qualifier_list "static" assignment_expression "]"
    | "[" type_qualifier_list assignment_expression "]"
    | "[" type_qualifier_list "]"
    | "[" assignment_expression "]"
    | direct_abstract_declarator "[" "]"
    | direct_abstract_declarator "[" "*" "]"
    | direct_abstract_declarator "[" "static" type_qualifier_list assignment_expression "]"
    | direct_abstract_declarator "[" "static" assignment_expression "]"
    | direct_abstract_declarator "[" type_qualifier_list assignment_expression "]"
    | direct_abstract_declarator "[" type_qualifier_list "static" assignment_expression "]"
    | direct_abstract_declarator "[" type_qualifier_list "]"
    | direct_abstract_declarator "[" assignment_expression "]"
    | "(" ")"
    | "(" parameter_type_list ")"
    | direct_abstract_declarator "(" ")"
    | direct_abstract_declarator "(" parameter_type_list ")"
    ;

initializer
    : "{" initializer_list "}"
    | "{" initializer_list "," "}"
    | assignment_expression
    ;

initializer_list
    : designation initializer
    | initializer
    | initializer_list "," designation initializer
    | initializer_list "," initializer
    ;

designation
    : designator_list "="
    ;

designator_list
    : designator
    | designator_list designator
    ;

designator
    : "[" constant_expression "]"
    | "." "identifier"
    ;

static_assert_declaration
    : "_Static_assert" "(" constant_expression "," "string" ")" ";"
    ;

statement
    : labeled_statement
    | compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;

labeled_statement
    :"identifier" ":" attribute_spec statement
    :"identifier" ":" statement
    | "case" constant_expression ":" statement
    | "default" ":" statement
    ;

compound_statement
    : "{" "}"
    | "{"  block_item_list "}"
    ;

block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : declaration
    | statement
    ;

expression_statement
    : ";"
    | expression ";"
    ;

selection_statement
    : "if" "(" expression ")" statement "else" statement
    | "if" "(" expression ")" statement
    | "switch" "(" expression ")" statement
    ;

iteration_statement
    : WHILE "(" expression ")" statement
    | "do" statement WHILE "(" expression ")" ";"
    | "for" "(" expression_statement expression_statement ")" statement
    | "for" "(" expression_statement expression_statement expression ")" statement
    | "for" "(" declaration expression_statement ")" statement
    | "for" "(" declaration expression_statement expression ")" statement
    ;

jump_statement
    : "goto""identifier"";"
    | "continue" ";"
    | "break" ";"
    | "return" ";"
    | "return" expression ";"
    ;

translation_unit
    : external_declaration
    | translation_unit external_declaration
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : declaration_specifiers declarator declaration_list compound_statement
    | declaration_specifiers declarator compound_statement

declaration_list
    : declaration
    | declaration_list declaration
    ;

attribute_spec
    : "__attribute__" "(" "(" attribute_list ")" ")"
    {
        driver.in_attribute_ = false;
    }
    ;

attribute_list
    : attribute_extension
    | attribute_list "," attribute_extension
    ;

attribute_extension
    : "__alias__" "(" "string" ")"
    | "__aligned__"
    | "__aligned__" "(" "i_constant" ")"
    /* TODO: aligned "(" alignof ")" */
    | "__always_inline__"
    | "__cdecl__"
    | "__cleanup__"
    | "const"
    | "__constructor__"
    | "__deprecated__"
    | "__destructor__"
    | "__dllexport__"
    | "__dllimport__"
    | "__format__" "(" format_archetype "," "i_constant" "," "i_constant" ")"
    | "__leaf__"
    | "__pure__"
    | "__nonnull__" "(" num_list ")"
    | "__nothrow__"
    ;

num_list
    : "i_constant"
    | num_list "i_constant"
    ;

format_archetype
    : "__printf__"
    | "__scanf__"
    /* | "__strftime__" */
    /* | "__strfmon__" */
    ;

%%

void ucc::parse::Parser::error(ucc::parse::location const& l,
                               std::string const& s)
{
    driver.error_ << ucc::misc::Error::Type::parse
                  << driver.file_get() << ":"  << l << ": " << s << std::endl;
}
