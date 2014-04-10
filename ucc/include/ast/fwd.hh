#ifndef FWD_HH
# define FWD_HH

namespace ucc
{
    namespace ast
    {
        class Ast;

        template<class T>
        class AnyList;

        class Decl;
        class DeclSpecifier;
        class Declarator;
        class VarDecl;
        class FunctionDecl;
        class TypeDecl;
        class FieldDecl;
        class RecordDecl;

        class Type;
        class NamedType;
        class ArrayType;
        class FunctionType;
        class PtrType;
        class RecordType;

        class Stmt;
        class CompoundStmt;
        class ReturnStmt;
        class WhileStmt;
        class DoWhileStmt;
        class LabelStmt;
        class GotoStmt;
        class BreakStmt;
        class ContinueStmt;
        class IfStmt;
        class SwitchStmt;
        class CaseStmt;
        class DefaultStmt;
        class ForStmt;

        class Expr;
        class IntExpr;
        class FloatExpr;
        class StringExpr;
        class VarExpr;
        class SubscriptExpr;
        class CallExpr;
        class AssignExpr;
        class ConditionalExpr;
        class OpExpr;
        class UnaryExpr;
        class MemberExpr;

        typedef AnyList<Ast> AstList;
        typedef AnyList<Decl> DeclList;
        typedef AnyList<Stmt> StmtList;
        typedef AnyList<Expr> ExprList;
        typedef AnyList<FieldDecl> FieldList;
    } // namespace ast
} // namespace ucc

#endif /* !FWD_HH */
