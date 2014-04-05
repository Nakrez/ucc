#include <ast/pretty-printer.hh>
#include <misc/indent.hh>

using namespace ucc;
using namespace ast;

PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : DefaultConstVisitor()
    , formals_(false)
    , ostr_(ostr)
{}

PrettyPrinter::~PrettyPrinter()
{}

void PrettyPrinter::operator()(const AstList& ast)
{
    auto it = ast.list_get().cbegin();
    auto begin = it;
    auto end = ast.list_get().cend();

    for (; it != end; ++it)
    {
        if (it != begin)
        {
            ostr_ << ucc::misc::iendl;
        }

        (*it)->accept(*this);

        if (!dynamic_cast<const Decl*> (it->get()) &&
            !dynamic_cast<const IfStmt*> (it->get()) &&
            !dynamic_cast<const SwitchStmt*> (it->get()) &&
            !dynamic_cast<const CaseStmt*> (it->get()) &&
            !dynamic_cast<const WhileStmt*> (it->get()))
            ostr_ << ";";
    }
}

void PrettyPrinter::operator()(const DeclList& ast)
{
    auto it = ast.list_get().cbegin();
    auto begin = it;
    auto end = ast.list_get().cend();

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ucc::misc::iendl;
        (*it)->accept(*this);
    }
}

void PrettyPrinter::operator()(const ExprList& ast)
{
    auto it = ast.list_get().cbegin();
    auto begin = it;
    auto end = ast.list_get().cend();

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ", ";
        (*it)->accept(*this);
    }
}

void PrettyPrinter::operator()(const VarDecl& ast)
{
    if (ast.is_static())
        ostr_ << "static ";
    else if (ast.is_extern())
        ostr_ << "extern ";

    if (ast.type_get())
    {
        if (print_fun_ptr(ast.type_get(), ast.name_get()))
        {
            if (!formals_)
                ostr_ << ";";
            return;
        }

        ast.type_get()->accept(*this);
    }

    if (ast.name_get().data_get() != "" &&
        !dynamic_cast<const PtrType*> (ast.type_get()))
        ostr_ << " ";

    ostr_ << ast.name_get();

    if (ast.init_get())
    {
        ostr_ << " = ";
        ast.init_get()->accept(*this);
    }

    if (!formals_)
        ostr_ << ";";
}

void PrettyPrinter::operator()(const TypeDecl& ast)
{
    ostr_ << "typedef ";

    if (ast.type_get())
    {
        if (print_fun_ptr(ast.type_get(), ast.name_get()))
        {
            ostr_ << ";";
            return;
        }

        ast.type_get()->accept(*this);
    }

    ostr_ << " " << ast.name_get() << ";";
}

void PrettyPrinter::operator()(const FunctionDecl& ast)
{
    auto it = ast.param_get().cbegin();
    auto begin = it;
    auto end = ast.param_get().cend();

    if (ast.return_type_get())
    {
        ast.return_type_get()->accept(*this);

        if (!dynamic_cast<const PtrType*>(ast.return_type_get()))
            ostr_ << " ";
    }

    ostr_ << ast.name_get();

    ostr_ << "(";

    bool old = formals_;

    formals_ = true;

    for (; it != end; ++it)
    {
        if (it != begin)
            ostr_ << ", ";

        (*it)->accept(*this);
    }

    formals_ = old;

    ostr_ << ")";

    if (ast.compound_get())
        ast.compound_get()->accept(*this);
    else
        ostr_ << ";";
}

void PrettyPrinter::operator()(const NamedType& ast)
{
    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";

    ostr_ << ast.name_get();
}

void PrettyPrinter::operator()(const PtrType& ast)
{
    if (ast.pointed_type_get())
        ast.pointed_type_get()->accept(*this);

    if (!dynamic_cast<const PtrType*>(ast.pointed_type_get()))
        ostr_ << " ";

    ostr_ << "*";

    if (ast.is_const())
        ostr_ << "const ";
    if (ast.is_restrict())
        ostr_ << "restrict ";
}

void PrettyPrinter::operator()(const CompoundStmt& ast)
{
    ostr_ << ucc::misc::iendl;
    ostr_ << "{" << ucc::misc::incendl;

    if (ast.compound_get())
        ast.compound_get()->accept(*this);

    ostr_ << ucc::misc::decendl << "}";
}

void PrettyPrinter::operator()(const WhileStmt& ast)
{
    ostr_ << "while (";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << misc::incendl;

    if (ast.body_get())
        ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << ";" << misc::decendl;
}

void PrettyPrinter::operator()(const DoWhileStmt& ast)
{
    ostr_ << "do";

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << misc::incendl;

    if (ast.body_get())
        ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.body_get()))
        ostr_ << ";" << misc::decendl;
    else
        ostr_ << " ";

    ostr_ << "while (";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ");";
}

void PrettyPrinter::operator()(const LabelStmt& ast)
{
    ostr_ << ast.name_get() << ":" << misc::iendl;

    if (ast.stmt_get())
        ast.stmt_get()->accept(*this);
}

void PrettyPrinter::operator()(const GotoStmt& ast)
{
    ostr_ << "goto " << ast.name_get();
}

void PrettyPrinter::operator()(const BreakStmt&)
{
    ostr_ << "break";
}

void PrettyPrinter::operator()(const ContinueStmt&)
{
    ostr_ << "continue";
}

void PrettyPrinter::operator()(const IfStmt& ast)
{
    ostr_ << "if (";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*>(ast.if_body_get()))
        ostr_ << misc::incendl;

    if (ast.if_body_get())
        ast.if_body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*>(ast.if_body_get()))
        ostr_ << ";" << misc::decendl;
    else
        ostr_ << misc::iendl;

    if (ast.else_body_get())
    {
        ostr_ << "else";

        if (!dynamic_cast<const CompoundStmt*>(ast.else_body_get()))
            ostr_ << misc::incendl;

        ast.else_body_get()->accept(*this);

        if (!dynamic_cast<const CompoundStmt*>(ast.else_body_get()))
        {
            if (!dynamic_cast<const IfStmt*>(ast.else_body_get()))
            ostr_ << ";";

            ostr_ << misc::decendl;
        }
    }
}

void PrettyPrinter::operator()(const SwitchStmt& ast)
{
    ostr_ << "switch (";

    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << ")";

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::incendl;

    ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::decendl;
}

void PrettyPrinter::operator()(const CaseStmt& ast)
{
    ostr_ << "case ";

    if (ast.expr_get())
        ast.expr_get()->accept(*this);

    ostr_ << ":";

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << misc::incendl;

    ast.body_get()->accept(*this);

    if (!dynamic_cast<const CompoundStmt*> (ast.body_get()))
        ostr_ << ";" << misc::decendl;
}

void PrettyPrinter::operator()(const ReturnStmt& ast)
{
    ostr_ << "return";

    if (ast.expr_get())
    {
        ostr_ << " ";
        ast.expr_get()->accept(*this);
    }
}

void PrettyPrinter::operator()(const IntExpr& ast)
{
    ostr_ << ast.value_get();
}

void PrettyPrinter::operator()(const FloatExpr& ast)
{
    ostr_ << ast.value_get();
}

void PrettyPrinter::operator()(const StringExpr& ast)
{
    ostr_ << *ast.str_get();
}

void PrettyPrinter::operator()(const VarExpr& ast)
{
    ostr_ << ast.name_get();
}

void PrettyPrinter::operator()(const SubscriptExpr& ast)
{
    if (ast.var_get())
        ast.var_get()->accept(*this);

    ostr_ << "[";

    if (ast.expr_get())
        ast.expr_get()->accept(*this);

    ostr_ << "]";
}

void PrettyPrinter::operator()(const CallExpr& ast)
{
    if (ast.var_get())
        ast.var_get()->accept(*this);

    ostr_ << "(";

    if (ast.param_get())
        ast.param_get()->accept(*this);

    ostr_ << ")";
}

void PrettyPrinter::operator()(const AssignExpr& ast)
{
    if (ast.lvalue_get())
        ast.lvalue_get()->accept(*this);

    ostr_ << " ";
    ostr_ << ast.op_to_str();
    ostr_ << " ";

    if (ast.rvalue_get())
        ast.rvalue_get()->accept(*this);
}

void PrettyPrinter::operator()(const ConditionalExpr& ast)
{
    if (ast.cond_get())
        ast.cond_get()->accept(*this);

    ostr_ << " ? ";

    if (ast.true_expr_get())
        ast.true_expr_get()->accept(*this);

    ostr_ << " : ";

    if (ast.false_expr_get())
        ast.false_expr_get()->accept(*this);
}

void PrettyPrinter::operator()(const OpExpr& ast)
{
    ostr_ << "(";

    if (ast.lexpr_get())
        ast.lexpr_get()->accept(*this);

    ostr_ << " ";
    ostr_ << ast.op_to_str();
    ostr_ << " ";

    if (ast.rexpr_get())
        ast.rexpr_get()->accept(*this);

    ostr_ << ")";
}

void PrettyPrinter::operator()(const UnaryExpr& ast)
{
    ostr_ << ast.op_to_str();

    if (ast.expr_get())
        ast.expr_get()->accept(*this);
}

bool PrettyPrinter::print_fun_ptr(const Type* ast,
        const ucc::misc::Symbol& sym)
{
    const PtrType* ptr = dynamic_cast<const PtrType*> (ast);
    const PtrType* tmp = nullptr;
    const FunctionType* fn = nullptr;
    int ptr_nb = 1;

    if (ptr)
    {
        while (1)
        {
            tmp = dynamic_cast<const PtrType*> (ptr->pointed_type_get());

            if (!tmp)
                break;

            ++ptr_nb;
            ptr = tmp;
        }

        fn = dynamic_cast<const FunctionType*> (ptr->pointed_type_get());

        if (!fn)
            return false;

        if (fn->return_type_get())
            fn->return_type_get()->accept(*this);

        if (!dynamic_cast<const PtrType*>(fn->return_type_get()))
            ostr_ << " ";

        ostr_ << "(";

        for (int i = 0; i < ptr_nb; ++i)
            ostr_ << "*";

        ostr_ << sym << ")(";

        bool old = formals_;
        auto it = fn->param_get().cbegin();
        auto begin = it;
        auto end = fn->param_get().cend();

        formals_ = true;

        for (; it != end; ++it)
        {
            if (it != begin)
                ostr_ << ", ";

            (*it)->accept(*this);
        }

        formals_ = old;

        ostr_ << ")";

        return true;
    }

    return false;
}
