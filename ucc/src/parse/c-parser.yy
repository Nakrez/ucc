%require "2.4"
%skeleton "glr.cc"

%code requires
{
# include <string>
# include <misc/symbol.hh>
# include <ast/fwd.hh>
# include <ast/all.hh>

    namespace ucc
    {
        namespace parse
        {
            class Driver;
        }
    }

typedef ucc::ast::DeclSpecifier::StorageClassSpecifier StorageClassSpecifier;
typedef ucc::ast::DeclSpecifier::FunctionSpecifier FunctionSpecifier;
typedef ucc::ast::DeclSpecifier::TypeQualifier TypeQualifier;
typedef ucc::ast::DeclSpecifier::TypeSpecifier TypeSpecifier;
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

%code
{
# include <parse/driver.hh>
}

%union
{
    std::list<ucc::ast::Declarator*>* declarator_list;
    std::list<ucc::ast::VarDecl*>* vardecl_list;
    ucc::misc::Symbol* symbol;
    int int_;
    long double float_;
    std::string* string_;
    ucc::ast::DeclSpecifier* declspecifier;
    ucc::ast::Declarator* declarator;
    ucc::ast::Decl* decl;
    ucc::ast::Expr* expr;
    ucc::ast::DeclList* decl_list;
    ucc::ast::StmtList* stmt_list;
    ucc::ast::VarDecl* vardecl;
    ucc::ast::PtrType* ptr_type;
    ucc::ast::FunctionDecl* fun_decl;
    ucc::ast::AstList* ast_list;
    ucc::ast::Ast* ast;
    ucc::ast::Stmt* stmt;
    ucc::ast::ExprList* expr_list;
    ucc::ast::AssignExpr::AssignOp assign_op;
    ucc::ast::UnaryExpr::UnaryOp unary_op;
    ucc::ast::CompoundStmt* compound_stmt;
    ucc::ast::FieldDecl* field;
    ucc::ast::FieldList* field_list;
    ucc::ast::RecordDecl::RecordType rec_type;
    ucc::ast::EnumExprDecl* enum_expr_decl;
    ucc::ast::EnumExprList* enum_expr_list;
    ucc::ast::Type* type;
}


%token<symbol>  IDENTIFIER      "identifier"
                TYPEDEF_NAME    "typedef_name"
                ENUM_CONSTANT   "enum_constant"

%token<int_>    I_CONSTANT      "i_constant"
%token<float_>  F_CONSTANT      "f_constant"
%token<string_> STRING_LITERAL  "string"

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
        NORETURN        "__noreturn__"
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

%type <string_>         string

%type <declspecifier>   storage_class_specifier
                        declaration_specifiers
                        type_specifier
                        type_qualifier
                        function_specifier
                        type_qualifier_list
                        specifier_qualifier_list

%type <declarator>      declarator
                        direct_declarator
                        init_declarator
                        abstract_declarator
                        direct_abstract_declarator


%type <declarator_list> init_declarator_list
%type <decl_list>       declaration
                        declaration_list
                        external_declaration
%type <vardecl>         parameter_declaration
%type <vardecl_list>    parameter_type_list
                        parameter_list
%type <fun_decl>        function_definition
%type <ptr_type>        pointer
%type <compound_stmt>   compound_statement
%type <ast_list>        statement_list
%type <ast>             struct_or_union_specifier
                        enum_specifier

%type <expr>            initializer
                        expression_statement
                        expression
                        assignment_expression
                        primary_expression
                        constant
                        postfix_expression
                        unary_expression
                        conditional_expression
                        constant_expression
                        logical_or_expression
                        logical_and_expression
                        inclusive_or_expression
                        exclusive_or_expression
                        and_expression
                        equality_expression
                        relational_expression
                        shift_expression
                        additive_expression
                        multiplicative_expression
                        cast_expression

%type <stmt>            jump_statement
                        iteration_statement
                        labeled_statement
                        statement
                        selection_statement

%type <expr_list>       argument_expression_list
                        initializer_list
%type <assign_op>       assignment_operator
%type <unary_op>        unary_operator

%type <field>           struct_declarator
%type <field_list>      struct_declarator_list
                        struct_declaration
                        struct_declaration_list
%type <rec_type>        struct_or_union
%type <enum_expr_decl>  enumeration_constant
                        enumerator

%type <enum_expr_list>  enumerator_list
%type <type>            type_name

%start translation_unit
%%

primary_expression
    : "identifier"
    {
        $$ = new ucc::ast::VarExpr(@1, *$1);

        delete $1;
    }
    | constant
    {
        $$ = $1;
    }
    | string
    {
        $$ = new ucc::ast::StringExpr(@1, $1);
    }
    | "(" expression ")"
    {
        $$ = $2;
    }
    /*| generic_selection*/
    ;

constant
    : "i_constant"
    {
        $$ = new ucc::ast::IntExpr(@1, $1);
    }
    | "f_constant"
    {
        $$ = new ucc::ast::FloatExpr(@1, $1);
    }
    | "enum_constant"
    {
        $$ = new ucc::ast::EnumExpr(@1, *$1);

        delete $1;
    }
    ;

enumeration_constant        /* before it has been defined as such */
    : "identifier"
    {
        driver.sym_.put($1->data_get(),
                        ucc::parse::Parser::token::ENUM_CONSTANT);

        $$ = new ucc::ast::EnumExprDecl(@1, *$1, nullptr);

        delete $1;
    }
    ;

string
    : "string"
    {
        $$ = $1;
    }
    /*| "__func__"*/
    ;
/*
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
*/

postfix_expression
    : primary_expression
    {
        $$ = $1;
    }
    | postfix_expression "[" expression "]"
    {
        $$ = new ucc::ast::SubscriptExpr(@1, $1, $3);
    }
    | postfix_expression "(" ")"
    {
        $$ = new ucc::ast::CallExpr(@1, $1, nullptr);
    }
    | postfix_expression "(" argument_expression_list ")"
    {
        $$ = new ucc::ast::CallExpr(@1, $1, $3);
    }
    | postfix_expression "." "identifier"
    {
        $$ = new ucc::ast::MemberExpr(@1, $1, *$3, false);

        delete $3;
    }
    | postfix_expression "->" "identifier"
    {
        $$ = new ucc::ast::MemberExpr(@1, $1, *$3, true);

        delete $3;
    }
    | postfix_expression "++"
    {
        $$ = new ucc::ast::UnaryExpr(@1,
                                     ucc::ast::UnaryExpr::UnaryOp::POST_INCR,
                                     $1);
    }
    | postfix_expression "--"
    {
        $$ = new ucc::ast::UnaryExpr(@1,
                                     ucc::ast::UnaryExpr::UnaryOp::POST_DECR,
                                     $1);
    }

/*
    | "(" type_name ")" "{" initializer_list "}"
    | "(" type_name ")" "{" initializer_list "," "}"
*/
    ;

argument_expression_list
    : assignment_expression
    {
        $$ = new ucc::ast::ExprList(@1);
        $$->push_back(std::shared_ptr<ucc::ast::Expr>($1));
    }
    | argument_expression_list "," assignment_expression
    {
        $$ = $1;
        $$->push_back(std::shared_ptr<ucc::ast::Expr>($3));
    }
    ;

unary_expression
    : postfix_expression
    {
        $$ = $1;
    }
    | "++" unary_expression
    {
        $$ = new ucc::ast::UnaryExpr(@1,
                                     ucc::ast::UnaryExpr::UnaryOp::PRE_INCR,
                                     $2);
    }
    | "--" unary_expression
    {
        $$ = new ucc::ast::UnaryExpr(@1,
                                     ucc::ast::UnaryExpr::UnaryOp::PRE_DECR,
                                     $2);
    }
    | unary_operator cast_expression
    {
        $$ = new ucc::ast::UnaryExpr(@1, $1, $2);
    }
    | "sizeof" unary_expression
    {
        $$ = new ucc::ast::SizeofExpr(@1, $2);
    }
    | "sizeof" "(" type_name ")"
    {
        $$ = new ucc::ast::SizeofExpr(@1, $3);
    }
    /*| "_Alignof" "(" type_name ")"*/
    ;

unary_operator
    : "&"
    {
        $$ = ucc::ast::UnaryExpr::UnaryOp::BAND;
    }
    | "*"
    {
        $$ = ucc::ast::UnaryExpr::UnaryOp::DEREF;
    }
    | "+"
    {
        $$ = ucc::ast::UnaryExpr::UnaryOp::PLUS;
    }
    | "-"
    {
        $$ = ucc::ast::UnaryExpr::UnaryOp::MINUS;
    }
    | "~"
    {
        $$ = ucc::ast::UnaryExpr::UnaryOp::TILDE;
    }
    | "!"
    {
        $$ = ucc::ast::UnaryExpr::UnaryOp::BANG;
    }
    ;

cast_expression
    : unary_expression
    {
        $$ = $1;
    }
    | "(" type_name ")" cast_expression
    {
        $$ = new ucc::ast::CastExpr(@1, $2, $4);
    }
    ;

multiplicative_expression
    : cast_expression
    {
        $$ = $1;
    }
    | multiplicative_expression "*" cast_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_MUL, $3);
    }
    | multiplicative_expression "/" cast_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_DIV, $3);
    }
    | multiplicative_expression "%" cast_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_MOD, $3);
    }
    ;

additive_expression
    : multiplicative_expression
    {
        $$ = $1;
    }
    | additive_expression "+" multiplicative_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_PLUS, $3);
    }
    | additive_expression "-" multiplicative_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_MINUS, $3);
    }
    ;

shift_expression
    : additive_expression
    {
        $$ = $1;
    }
    | shift_expression "<<" additive_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_LSHIFT, $3);
    }
    | shift_expression ">>" additive_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_RSHIFT, $3);
    }
    ;

relational_expression
    : shift_expression
    {
        $$ = $1;
    }
    | relational_expression "<" shift_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_LT, $3);
    }
    | relational_expression ">" shift_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_GT, $3);
    }
    | relational_expression "<=" shift_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_LE, $3);
    }
    | relational_expression ">=" shift_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_GE, $3);
    }
    ;

equality_expression
    : relational_expression
    {
        $$ = $1;
    }
    | equality_expression "==" relational_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_EQ, $3);
    }
    | equality_expression "!=" relational_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_DIFF, $3);
    }
    ;

and_expression
    : equality_expression
    {
        $$ = $1;
    }
    | and_expression "&" equality_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_BAND, $3);
    }
    ;

exclusive_or_expression
    : and_expression
    {
        $$ = $1;
    }
    | exclusive_or_expression "^" and_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_XOR, $3);
    }
    ;

inclusive_or_expression
    : exclusive_or_expression
    {
        $$ = $1;
    }
    | inclusive_or_expression "|" exclusive_or_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_BOR, $3);
    }
    ;

logical_and_expression
    : inclusive_or_expression
    {
        $$ = $1;
    }
    | logical_and_expression "&&" inclusive_or_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_AND, $3);
    }
    ;

logical_or_expression
    : logical_and_expression
    {
        $$ = $1;
    }
    | logical_or_expression "||" logical_and_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_OR, $3);
    }
    ;

conditional_expression
    : logical_or_expression
    {
        $$ = $1;
    }
    | logical_or_expression "?" expression ":" conditional_expression
    {
        $$ = new ucc::ast::ConditionalExpr(@1, $1, $3, $5);
    }
    ;

assignment_expression
    : conditional_expression
    {
        $$ = $1;
    }
    | unary_expression assignment_operator assignment_expression
    {
        $$ = new ucc::ast::AssignExpr(@1, $1, $2, $3);
    }
    ;

assignment_operator
    : "="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::ASSIGN;
    }
    | "*="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::MUL_ASSIGN;
    }
    | "/="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::DIV_ASSIGN;
    }
    | "%="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::MOD_ASSIGN;
    }
    | "+="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::PLUS_ASSIGN;
    }
    | "-="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::MINUS_ASSIGN;
    }
    | "<<="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::LSHIFT_ASSIGN;
    }
    | ">>="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::RSHIFT_ASSIGN;
    }
    | "&="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::BAND_ASSIGN;
    }
    | "^="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::BXOR_ASSIGN;
    }
    | "|="
    {
        $$ = ucc::ast::AssignExpr::AssignOp::BOR_ASSIGN;
    }
    ;

expression
    : assignment_expression
    {
        $$ = $1;
    }
    | expression "," assignment_expression
    {
        $$ = new ucc::ast::OpExpr(@1, $1, ucc::ast::OpExpr::Op::OP_COMA, $3);
    }
    ;

constant_expression
    : conditional_expression    /* with constraints */
    {
        $$ = $1;
    }
    ;

declaration
    : declaration_specifiers ";"
    {
        $$ = new ucc::ast::DeclList(@1);

        if ($1->decl_get())
            $$->push_back(std::shared_ptr<ucc::ast::Decl>($1->decl_get()));
        else if ($1->is_struct())
        {
            ucc::ast::RecordDecl* d = new ucc::ast::RecordDecl(@1,
                                $1->name_get(),
                                ucc::ast::RecordDecl::RecordType::STRUCT,
                                nullptr);
            $$->push_back(std::shared_ptr<ucc::ast::Decl>(d));
        }
        else if ($1->is_enum())
        {
            ucc::ast::EnumDecl* d = new ucc::ast::EnumDecl(@1, $1->name_get(),
                                                           nullptr);
            $$->push_back(std::shared_ptr<ucc::ast::Decl>(d));
        }
        else if ($1->is_union())
        {
            ucc::ast::RecordDecl* d = new ucc::ast::RecordDecl(@1,
                                $1->name_get(),
                                ucc::ast::RecordDecl::RecordType::UNION,
                                nullptr);
            $$->push_back(std::shared_ptr<ucc::ast::Decl>(d));
        }

        delete $1;
    }
    | declaration_specifiers init_declarator_list ";"
    {
        ucc::ast::Decl* new_decl = nullptr;
        $$ = new ucc::ast::DeclList(@1);
        ucc::ast::Type* type;

        if ($1->decl_get())
            $$->push_back(std::shared_ptr<ucc::ast::Decl>($1->decl_get()));
        else if (driver.sym_.size() == 1 || $1->is_typedef())
        {
            ucc::ast::Type* t;
            ucc::ast::RecordType* rt;
            ucc::ast::EnumType* et;

            t = $1->type_get();
            rt = dynamic_cast<ucc::ast::RecordType*>(t);
            et = dynamic_cast<ucc::ast::EnumType*>(t);

            if (rt)
                $$->push_back(std::shared_ptr<ucc::ast::Decl>(
                                new ucc::ast::RecordDecl(@1,
                                                        rt->name_get(),
                                                        rt->type_get(),
                                                        nullptr)));
            else if (et)
                $$->push_back(std::shared_ptr<ucc::ast::Decl>(
                                new ucc::ast::EnumDecl(@1,
                                                       et->name_get(),
                                                       nullptr)));

            delete t;
        }

        for (auto decl : *$2)
        {
            type = decl->type_get();

            if (!type)
                type = $1->type_get();
            else
                type->extends_type($1->type_get());

            if ($1->is_typedef())
            {
                if (decl->init_get())
                    yyparser.error(decl->location_get(), "illegal initializer"
                                   " (only variables can be initialized)");
                new_decl = new ucc::ast::TypeDecl(@1, decl->name_get(), type);
                driver.sym_.put(decl->name_get().data_get(),
                    ucc::parse::Parser::token::TYPEDEF_NAME);
            }
            else if (type && dynamic_cast<ucc::ast::FunctionType*>(type))
            {
                ucc::ast::FunctionType* t;
                t = dynamic_cast<ucc::ast::FunctionType*>(type);

                new_decl = new ucc::ast::FunctionDecl(@1, decl->name_get(), t);
            }
            else
                new_decl = new ucc::ast::VarDecl(@$, decl->name_get(),
                                                 type, decl->init_get());

            new_decl->storage_class_set($1->storage_class_get());

            delete decl;

            $$->push_back(std::shared_ptr<ucc::ast::Decl>(new_decl));
        }

        delete $1;
        delete $2;
    }
    /* | static_assert_declaration */
    ;

declaration_specifiers
    : storage_class_specifier declaration_specifiers
    {
        $$ = $1;
        $$->merge($2, driver.error_);

        delete $2;
    }
    | storage_class_specifier
    {
        $$ = $1;
    }
    | type_specifier declaration_specifiers
    {
        $$ = $1;
        $$->merge($2, driver.error_);

        delete $2;
    }
    | type_specifier
    {
        $$ = $1;
    }
    | type_qualifier attribute_spec declaration_specifiers
    {
        $$ = $1;
        $$->merge($3, driver.error_);

        delete $3;
    }
    | type_qualifier declaration_specifiers
    {
        $$ = $1;
        $$->merge($2, driver.error_);
        delete $2;
    }
    | type_qualifier
    {
        $$ = $1;
    }
    | type_qualifier attribute_spec
    {
        $$ = $1;
    }
    | function_specifier declaration_specifiers
    {
        $$ = $1;
        $$->merge($2, driver.error_);
        delete $2;
    }
    | function_specifier
    {
        $$ = $1;
    }
    /*
    | alignment_specifier declaration_specifiers
    | alignment_specifier
    */
    ;

init_declarator_list
    : init_declarator
    {
        $$ = new std::list<ucc::ast::Declarator*>();
        $$->push_back($1);
    }
    | init_declarator_list "," init_declarator
    {
        $$ = $1;
        $$->push_back($3);
    }
    ;

init_declarator
    : declarator "=" initializer
    {
        $$ = $1;
        $$->init_set($3);
    }
    | declarator
    {
        $$ = $1;
    }
    ;

storage_class_specifier
    : "typedef"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->storage_class_set(StorageClassSpecifier::SCS_typedef,
                              driver.error_);
    }
    | "extern"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->storage_class_set(StorageClassSpecifier::SCS_extern,
                              driver.error_);
    }
    | "static"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->storage_class_set(StorageClassSpecifier::SCS_static,
                              driver.error_);
    }
    /*| "_Thread_local"*/
    | "auto"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->storage_class_set(StorageClassSpecifier::SCS_auto, driver.error_);
    }
    | "register"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->storage_class_set(StorageClassSpecifier::SCS_register,
                              driver.error_);
    }
    ;

type_specifier
    : "void"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_void, driver.error_);
    }
    | "char"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_char, driver.error_);
    }
    | "short"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_short, driver.error_);
    }
    | "int"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_int, driver.error_);
    }
    | "long"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_long, driver.error_);
    }
    | "float"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_float, driver.error_);
    }
    | "double"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_double, driver.error_);
    }
    | "signed"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_signed, driver.error_);
    }
    | "unsigned"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_unsigned, driver.error_);
    }
    /*| "_Bool"*/
    /*| "_Complex"*/
    /*| "_Imaginary"*/
    /*| atomic_type_specifier*/
    | struct_or_union_specifier
    {
        ucc::ast::RecordType* ty = dynamic_cast<ucc::ast::RecordType*>($1);
        ucc::ast::RecordDecl* decl = dynamic_cast<ucc::ast::RecordDecl*>($1);

        $$ = new ucc::ast::DeclSpecifier(@1);

        if (ty)
        {
            $$->type_name_set(ty->name_get());

            if (ty->type_get() == ucc::ast::RecordDecl::RecordType::STRUCT)
                $$->type_specifier_set(TypeSpecifier::TS_struct, driver.error_);
            else
                $$->type_specifier_set(TypeSpecifier::TS_union, driver.error_);

            delete ty;
        }
        else
        {
            $$->type_name_set(decl->name_get());
            $$->decl_set(decl);

            if (decl->type_get() == ucc::ast::RecordDecl::RecordType::STRUCT)
                $$->type_specifier_set(TypeSpecifier::TS_struct, driver.error_);
            else
                $$->type_specifier_set(TypeSpecifier::TS_union, driver.error_);
        }
    }
    | enum_specifier
    {
        ucc::ast::EnumType* ty = dynamic_cast<ucc::ast::EnumType*>($1);
        ucc::ast::EnumDecl* decl = dynamic_cast<ucc::ast::EnumDecl*>($1);

        $$ = new ucc::ast::DeclSpecifier(@1);

        if (ty)
        {
            $$->type_name_set(ty->name_get());

            delete ty;
        }
        else
        {
            $$->type_name_set(decl->name_get());
            $$->decl_set(decl);
        }

        $$->type_specifier_set(TypeSpecifier::TS_enum, driver.error_);
    }
    | "typedef_name"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_specifier_set(TypeSpecifier::TS_type_name, driver.error_);
        $$->type_name_set(*$1);

        delete $1;
    }
    ;

struct_or_union_specifier
    : struct_or_union "{" struct_declaration_list "}"
    {
        $$ = new ucc::ast::RecordDecl(@1, "", $1, $3);
    }
    | struct_or_union attribute_spec "{" struct_declaration_list "}"
    {
        $$ = new ucc::ast::RecordDecl(@1, "", $1, $4);
    }
    | struct_or_union "{" struct_declaration_list "}" attribute_spec
    {
        $$ = new ucc::ast::RecordDecl(@1, "", $1, $3);
    }
    | struct_or_union attribute_spec "{" struct_declaration_list "}" attribute_spec
    {
        $$ = new ucc::ast::RecordDecl(@1, "", $1, $4);
    }
    | struct_or_union "identifier" "{" struct_declaration_list "}"
    {
        $$ = new ucc::ast::RecordDecl(@1, *$2, $1, $4);

        delete $2;
    }
    | struct_or_union "identifier"
    {
        $$ = new ucc::ast::RecordType(@1, $1, *$2);

        delete $2;
    }
    | struct_or_union attribute_spec "identifier"
    {
        $$ = new ucc::ast::RecordType(@1, $1, *$3);

        delete $3;
    }
    ;

struct_or_union
    : "struct"
    {
        $$ = ucc::ast::RecordDecl::RecordType::STRUCT;
    }
    | "union"
    {
        $$ = ucc::ast::RecordDecl::RecordType::UNION;
    }
    ;

struct_declaration_list
    : struct_declaration
    {
        $$ = $1;
    }
    | struct_declaration_list struct_declaration
    {
        $$ = $1;
        $$->splice_back(*$2);

        delete $2;
    }
    ;

struct_declaration
    : specifier_qualifier_list struct_declarator_list ";"
    {
        ucc::ast::Type* type;

        for (auto decl : $2->list_get())
        {
            type = decl->type_get();

            if (!type)
                type = $1->type_get();
            else
                type->extends_type($1->type_get());

            decl->type_set(type);

            decl->storage_class_set($1->storage_class_get());
        }

        $$ = $2;

        delete $1;
    }
    /*
    | specifier_qualifier_list ";"
    | static_assert_declaration
    */
    ;

specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    {
        $$ = $1;
        $$->merge($2, driver.error_);

        delete $2;
    }
    | type_specifier
    {
        $$ = $1;
    }
    | type_qualifier specifier_qualifier_list
    {
        $$ = $1;
        $$->merge($2, driver.error_);

        delete $2;
    }
    | type_qualifier
    {
        $$ = $1;
    }
    ;

struct_declarator_list
    : struct_declarator
    {
        $$ = new ucc::ast::FieldList(@1);
        $$->push_back(std::shared_ptr<ucc::ast::FieldDecl>($1));
    }
    | struct_declarator_list "," struct_declarator
    {
        $$ = $1;
        $$->push_back(std::shared_ptr<ucc::ast::FieldDecl>($3));
    }
    ;

struct_declarator
    : ":" constant_expression
    {
        $$ = new ucc::ast::FieldDecl(@1, "", nullptr, $2);
    }
    | declarator ":" constant_expression
    {
        $$ = new ucc::ast::FieldDecl(@1, $1->name_get(), $1->type_get(), $3);

        delete $1;
    }
    | declarator
    {
        $$ = new ucc::ast::FieldDecl(@1, $1->name_get(), $1->type_get(), nullptr);

        delete $1;
    }
    ;

enum_specifier
    : "enum" "{" enumerator_list "}"
    {
        $$ = new ucc::ast::EnumDecl(@1, "", $3);
    }
    | "enum" "{" enumerator_list "," "}"
    {
        $$ = new ucc::ast::EnumDecl(@1, "", $3);
    }
    | "enum" "identifier" "{" enumerator_list "}"
    {
        $$ = new ucc::ast::EnumDecl(@1, *$2, $4);

        delete $2;
    }
    | "enum" "identifier" "{" enumerator_list "," "}"
    {
        $$ = new ucc::ast::EnumDecl(@1, *$2, $4);

        delete $2;
    }
    | "enum" "identifier"
    {
        $$ = new ucc::ast::EnumType(@1, *$2);

        delete $2;
    }
    ;

enumerator_list
    : enumerator
    {
        $$ = new ucc::ast::EnumExprList(@1);
        $$->push_back(std::shared_ptr<ucc::ast::EnumExprDecl>($1));
    }
    | enumerator_list "," enumerator
    {
        $$ = $1;
        $$->push_back(std::shared_ptr<ucc::ast::EnumExprDecl>($3));
    }
    ;

enumerator
    : enumeration_constant "=" constant_expression
    {
        $$ = $1;
        $$->value_set($3);
    }
    | enumeration_constant
    {
        $$ = $1;
    }
    ;

/*
atomic_type_specifier
    : "_Atomic" "(" type_name ")"
    ;
*/

type_qualifier
    : "const"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_qualifier_set(TypeQualifier::TQ_const, driver.error_);
    }
    | "restrict"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_qualifier_set(TypeQualifier::TQ_restrict, driver.error_);
    }
    | "volatile"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->type_qualifier_set(TypeQualifier::TQ_volatile, driver.error_);
    }
    /*| "_Atomic"*/
    ;

function_specifier
    : "inline"
    {
        $$ = new ucc::ast::DeclSpecifier(@1);
        $$->function_specifier_set(FunctionSpecifier::FS_inline, driver.error_);
    }
    /*| "_Noreturn"*/
    ;

/*
alignment_specifier
    : "_Alignas" "(" Type_name ")"
    | "_Alignas" "(" constant_expression ")"
    ;
*/

declarator
    : pointer direct_declarator
    {
        $2->extends_type($1);
        $$ = $2;
    }
    | attribute_spec pointer direct_declarator
    {
        $3->extends_type($2);
        $$ = $3;
    }
    | attribute_spec pointer direct_declarator attribute_spec
    {
        $3->extends_type($2);
        $$ = $3;
    }
    | pointer direct_declarator attribute_spec
    {
        $2->extends_type($1);
        $$ = $2;
    }
    | direct_declarator
    {
        $$ = $1;
    }
    | attribute_spec direct_declarator
    {
        $$ = $2;
    }
    | attribute_spec direct_declarator attribute_spec
    {
        $$ = $2;
    }
    | direct_declarator attribute_spec
    {
        $$ = $1;
    }
    ;

direct_declarator
    : "identifier"
    {
        $$ = new ucc::ast::Declarator(@1, *$1);
        delete $1;
    }
    | "(" declarator ")"
    {
        $$ = $2;
    }
    | direct_declarator "[" "]"
    {
        $$ = $1;
        if (!$$->extends_type(new ucc::ast::ArrayType(@2)))
            yyparser.error(@2, "incompatible type used with array");
    }
    | direct_declarator "[" constant_expression "]"
    {
        $$ = $1;
        if (!$$->extends_type(new ucc::ast::ArrayType(@2, $3)))
            yyparser.error(@2, "incompatible type used with array");
    }
    | direct_declarator "(" parameter_type_list ")"
    {
        $$ = $1;
        if (!$$->extends_type(new ucc::ast::FunctionType(@2, *$3)))
            yyparser.error(@2, "incompatible type used with function");

        delete $3;
    }
    | direct_declarator "(" ")"
    {
        $$ = $1;
        if (!$$->extends_type(new ucc::ast::FunctionType(@2)))
            yyparser.error(@2, "incompatible type used with function");
    }
    | direct_declarator "(" identifier_list ")"
    /* | direct_declarator "[" "*" "]" */
    /* | direct_declarator "[" "static" type_qualifier_list assignment_expression "]" */
    /* | direct_declarator "[" "static" assignment_expression "]" */
    /* | direct_declarator "[" type_qualifier_list "*" "]" */
    /* | direct_declarator "[" type_qualifier_list "static" assignment_expression "]" */
    /* | direct_declarator "[" type_qualifier_list assignment_expression "]" */
    /* | direct_declarator "[" type_qualifier_list "]" */
    /* | direct_declarator "[" assignment_expression "]" */
    ;

pointer
    : "*" type_qualifier_list pointer
    {
        $$ = new ucc::ast::PtrType(@1);
        $$->const_set($2->is_const());
        $$->restrict_set($2->is_restrict());
        $$->volatile_set($2->is_volatile());
        $3->extends_type($$);

        $$ = $3;

        delete $2;
    }
    | "*" type_qualifier_list
    {
        $$ = new ucc::ast::PtrType(@1);
        $$->const_set($2->is_const());
        $$->restrict_set($2->is_restrict());
        $$->volatile_set($2->is_volatile());

        delete $2;
    }
    | "*" pointer
    {
        $$ = new ucc::ast::PtrType(@1);
        $2->extends_type($$);

        $$ = $2;
    }
    | "*"
    {
        $$ = new ucc::ast::PtrType(@1);
    }
    ;

type_qualifier_list
    : type_qualifier
    {
        $$ = $1;
    }
    | type_qualifier_list type_qualifier
    {
        $$ = $1;

        if ($2->is_const())
            $$->type_qualifier_set(TypeQualifier::TQ_const, driver.error_);
        if ($2->is_restrict())
            $$->type_qualifier_set(TypeQualifier::TQ_restrict, driver.error_);
        if ($2->is_restrict())
            $$->type_qualifier_set(TypeQualifier::TQ_volatile, driver.error_);

        delete $2;
    }
    ;


parameter_type_list
    : parameter_list "," "..."
    {
        $$ = $1;
        $$->push_back(new ucc::ast::VarDecl(@3));
    }
    | parameter_list
    {
        $$ = $1;
    }
    ;

parameter_list
    : parameter_declaration
    {
        $$ = new std::list<ucc::ast::VarDecl*>();
        $$->push_back($1);
    }
    | parameter_list "," parameter_declaration
    {
        $$ = $1;
        $$->push_back($3);
    }
    ;

parameter_declaration
    : declaration_specifiers declarator
    {
        if ($1->storage_class_get() !=
            ucc::ast::DeclSpecifier::StorageClassSpecifier::SCS_unspecified)
            yyparser.error(@1, "parameter can not have storage class");

        ucc::ast::Type* t = $2->type_get();

        if (!t)
            t = $1->type_get();
        else
            t->extends_type($1->type_get());

        $$ = new ucc::ast::VarDecl(@1, $2->name_get(), t, nullptr);

        delete $1;
        delete $2;
    }
    | declaration_specifiers abstract_declarator
    {
        if ($1->storage_class_get() !=
            ucc::ast::DeclSpecifier::StorageClassSpecifier::SCS_unspecified)
            yyparser.error(@1, "parameter can not have storage class");

        ucc::ast::Type* t = $2->type_get();

        if (!t)
            t = $1->type_get();
        else
            t->extends_type($1->type_get());

        $$ = new ucc::ast::VarDecl(@1, $2->name_get(), t, nullptr);

        delete $1;
        delete $2;
    }
    | declaration_specifiers
    {
        if ($1->storage_class_get() !=
            ucc::ast::DeclSpecifier::StorageClassSpecifier::SCS_unspecified)
            yyparser.error(@1, "parameter can not have storage class");
        else
            $$ = new ucc::ast::VarDecl(@1, "", $1->type_get(), nullptr);

        delete $1;
    }
    ;

identifier_list
    : "identifier"
    | identifier_list "," "identifier"
    ;

type_name
    : specifier_qualifier_list abstract_declarator
    {
        $$ = $2->type_get();

        if (!$$->extends_type($1->type_get()))
            yyparser.error(@1, "incompatible type combinaison");

        delete $1;
        delete $2;
    }
    | specifier_qualifier_list
    {
        $$ = $1->type_get();

        delete $1;
    }
    ;

abstract_declarator
    : pointer direct_abstract_declarator
    {
        $2->extends_type($1);
        $$ = $2;
    }
    | pointer
    {
        $$ = new ucc::ast::Declarator(@1, "");
        $$->extends_type($1);
    }
    | direct_abstract_declarator
    {
        $$ = $1;
    }
    ;

direct_abstract_declarator
    : "(" abstract_declarator ")"
    {
        $$ = $2;
    }
    | "[" "]"
    {
        $$ = new ucc::ast::Declarator(@1, "");

        if (!$$->extends_type(new ucc::ast::ArrayType(@2)))
            yyparser.error(@2, "incompatible type used with array");
    }
    | "[" constant_expression "]"
    {
        $$ = new ucc::ast::Declarator(@1, "");

        if (!$$->extends_type(new ucc::ast::ArrayType(@2, $2)))
            yyparser.error(@2, "incompatible type used with array");
    }
    | direct_abstract_declarator "[" "]"
    {
        $$ = $1;

        if (!$$->extends_type(new ucc::ast::ArrayType(@2)))
            yyparser.error(@2, "incompatible type used with array");
    }
    | direct_abstract_declarator "[" constant_expression "]"
    {
        $$ = $1;

        if (!$$->extends_type(new ucc::ast::ArrayType(@2, $3)))
            yyparser.error(@2, "incompatible type used with array");
    }
/*
    | "[" "*" "]"
    | "[" "static" type_qualifier_list assignment_expression "]"
    | "[" "static" assignment_expression "]"
    | "[" type_qualifier_list "static" assignment_expression "]"
    | "[" type_qualifier_list assignment_expression "]"
    | "[" type_qualifier_list "]"
    | "[" assignment_expression "]"
    | direct_abstract_declarator "[" "*" "]"
    | direct_abstract_declarator "[" "static" type_qualifier_list assignment_expression "]"
    | direct_abstract_declarator "[" "static" assignment_expression "]"
    | direct_abstract_declarator "[" type_qualifier_list assignment_expression "]"
    | direct_abstract_declarator "[" type_qualifier_list "static" assignment_expression "]"
    | direct_abstract_declarator "[" type_qualifier_list "]"
    | direct_abstract_declarator "[" assignment_expression "]"
*/
    | "(" ")"
    {
        $$ = new ucc::ast::Declarator(@1, "");
        if (!$$->extends_type(new ucc::ast::FunctionType(@2)))
            yyparser.error(@2, "incompatible type used with function");
    }
    | "(" parameter_type_list ")"
    {
        $$ = new ucc::ast::Declarator(@1, "");

        if (!$$->extends_type(new ucc::ast::FunctionType(@2, *$2)))
            yyparser.error(@2, "incompatible type used with function");

        delete $2;
    }
    | direct_abstract_declarator "(" ")"
    {
        $$ = $1;
        if (!$$->extends_type(new ucc::ast::FunctionType(@2)))
            yyparser.error(@2, "incompatible type used with function");
    }
    | direct_abstract_declarator "(" parameter_type_list ")"
    {
        $$ = $1;

        if (!$$->extends_type(new ucc::ast::FunctionType(@2, *$3)))
            yyparser.error(@2, "incompatible type used with function");

        delete $3;
    }
    ;

initializer
    : "{" initializer_list "}"
    {
        $$ = new ucc::ast::InitListExpr(@1, $2);
    }
    | "{" initializer_list "," "}"
    {
        $$ = new ucc::ast::InitListExpr(@1, $2);
    }
    | assignment_expression
    {
        $$ = $1;
    }
    ;

initializer_list
    : initializer
    {
        $$ = new ucc::ast::ExprList(@1);
        $$->push_back(std::shared_ptr<ucc::ast::Expr>($1));
    }
/*  | designation initializer */
/*  | initializer_list "," designation initializer */
    | initializer_list "," initializer
    {
        $$ = $1;
        $$->push_back(std::shared_ptr<ucc::ast::Expr>($3));
    }
    ;

/*
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
*/

statement
    : labeled_statement
    {
        $$ = $1;
    }
    | compound_statement
    {
        $$ = $1;
    }
    | expression_statement
    {
        $$ = $1;
    }
    | selection_statement
    {
        $$ = $1;
    }
    | iteration_statement
    {
        $$ = $1;
    }
    | jump_statement
    {
        $$ = $1;
    }
    ;

labeled_statement
    : "identifier" ":" attribute_spec statement
    {
        $$ = new ucc::ast::LabelStmt(@1, *$1, $4);

        delete $1;
    }
    | "identifier" ":" statement
    {
        $$ = new ucc::ast::LabelStmt(@1, *$1, $3);

        delete $1;
    }
    | "case" constant_expression ":" statement
    {
        $$ = new ucc::ast::CaseStmt(@1, $2, $4);
    }
    | "default" ":" statement
    {
        $$ = new ucc::ast::DefaultStmt(@1, $3);
    }
    ;

compound_statement
    : "{" "}"
    {
        $$ = new ucc::ast::CompoundStmt(@1, nullptr);
    }
    | "{" statement_list "}"
    {
        $$ = new ucc::ast::CompoundStmt(@1, $2);
    }
    | "{" declaration_list "}"
    {
        ucc::ast::AstList* l = $2->convert<ucc::ast::Ast>();
        delete $2;

        $$ = new ucc::ast::CompoundStmt(@1, l);
    }
    | "{" declaration_list statement_list "}"
    {
        ucc::ast::AstList* l = $2->convert<ucc::ast::Ast>();
        l->splice_back(*$3);

        $$ = new ucc::ast::CompoundStmt(@1, l);

        delete $3;
        delete $2;
    }
    /*
    | "{" "}"
    | "{"  block_item_list "}"
    */
    ;

statement_list
    : statement
    {
        $$ = new ucc::ast::AstList(@1);

        if ($1)
            $$->push_back(std::shared_ptr<ucc::ast::Ast>($1));
    }
    | statement_list statement
    {
        $$ = $1;
        if ($2)
            $$->push_back(std::shared_ptr<ucc::ast::Ast>($2));
    }
    ;
/*
block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : declaration
    | statement
    ;
*/

expression_statement
    : ";"
    {
        $$ = nullptr;
    }
    | expression ";"
    {
        $$ = $1;
    }
    ;

selection_statement
    : "if" "(" expression ")" statement "else" statement
    {
        $$ = new ucc::ast::IfStmt(@1, $3, $5, $7);
    }
    | "if" "(" expression ")" statement
    {
        $$ = new ucc::ast::IfStmt(@1, $3, $5, nullptr);
    }
    | "switch" "(" expression ")" statement
    {
        $$ = new ucc::ast::SwitchStmt(@1, $3, $5);
    }
    ;

iteration_statement
    : "while" "(" expression ")" statement
    {
        $$ = new ucc::ast::WhileStmt(@1, $3, $5);
    }
    | "do" statement WHILE "(" expression ")" ";"
    {
        $$ = new ucc::ast::DoWhileStmt(@1, $5, $2);
    }
    | "for" "(" expression_statement expression_statement ")" statement
    {
        $$ = new ucc::ast::ForStmt(@1, $3, $4, nullptr, $6);
    }
    | "for" "(" expression_statement expression_statement expression ")" statement
    {
        $$ = new ucc::ast::ForStmt(@1, $3, $4, $5, $7);
    }
    /*
    | "for" "(" declaration expression_statement ")" statement
    | "for" "(" declaration expression_statement expression ")" statement
    */
    ;

jump_statement
    : "goto" "identifier" ";"
    {
        $$ = new ucc::ast::GotoStmt(@1, *$2);

        delete $2;
    }
    | "continue" ";"
    {
        $$ = new ucc::ast::ContinueStmt(@1);
    }
    | "break" ";"
    {
        $$ = new ucc::ast::BreakStmt(@1);
    }
    | "return" ";"
    {
        $$ = new ucc::ast::ReturnStmt(@1);
    }
    | "return" expression ";"
    {
        $$ = new ucc::ast::ReturnStmt(@1, $2);
    }
    ;

translation_unit
    : external_declaration
    {
        driver.ast_ = $1;
    }
    | translation_unit external_declaration
    {
        driver.ast_->splice_back(*$2);
        delete $2;
    }
    ;

external_declaration
    : function_definition
    {
        $$ = new ucc::ast::DeclList(@1);
        $$->push_back(std::shared_ptr<ucc::ast::Decl>($1));
    }
    | declaration
    {
        $$ = $1;
    }
    ;

function_definition
    : declaration_specifiers declarator declaration_list compound_statement
    {
        yyparser.error(@1, "unsupported declaration list after function");
    }
    | declaration_specifiers declarator compound_statement
    {
        ucc::ast::Type* type;

        type = $2->type_get();

        if (!type)
            type = $1->type_get();
        else
            type->extends_type($1->type_get());

        if ($1->is_typedef())
            yyparser.error(@1,
                           "Cannot define function with typedef specifier");

        else if (type && dynamic_cast<ucc::ast::FunctionType*>(type))
        {
            ucc::ast::FunctionType* t;
            t = dynamic_cast<ucc::ast::FunctionType*>(type);

            $$ = new ucc::ast::FunctionDecl(@1, $2->name_get(), t, $3);
            $$->storage_class_set($1->storage_class_get());
        }
        else
            yyparser.error(@1, "Wrong combination of types for function"
                           " declaration");

        delete $1;
        delete $2;
    }
    | declarator declaration_list compound_statement
    {
        yyparser.error(@1, "unsupported declaration list after function");
    }
    | declarator compound_statement
    {
        ucc::ast::Type* type = $1->type_get();

        type->extends_type(new ucc::ast::NamedType(@1, "int"));

        if (type && dynamic_cast<ucc::ast::FunctionType*>(type))
        {
            ucc::ast::FunctionType* t;
            t = dynamic_cast<ucc::ast::FunctionType*>(type);

            $$ = new ucc::ast::FunctionDecl(@1, $1->name_get(), t, $2);
            $$->storage_class_set($1->storage_class_get());
        }
        else
            yyparser.error(@1, "Wrong combination of types for function"
                           " declaration");

        delete $1;
    }

declaration_list
    : declaration
    {
        $$ = $1;
    }
    | declaration_list declaration
    {
        $$ = $1;
        $$->splice_back(*$2);

        delete $2;
    }
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
    | "__noreturn__"
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
                  << driver.file_get() << ":"  << l << ": error: "
                  << s << std::endl;
}
