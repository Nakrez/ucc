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

        class Type;
        class NamedType;
        class ArrayType;
        class FunctionType;
        class PtrType;

        class Stmt;

        class Expr;

        typedef AnyList<Decl> DeclList;
    } // namespace ast
} // namespace ucc

#endif /* !FWD_HH */
