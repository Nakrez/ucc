[34mDeclList[0m
    [34mTypeDecl [37mb[32m 'int[]'[0m
    [34mTypeDecl [37mc[32m 'int*[]'[0m
    [34mTypeDecl [37md[32m 'int* const**[]'[0m
    [34mFunctionDecl [37mfn[32m 'int(void)'[0m
        [34mCompoundStmt[0m
            [34mVarDecl [37ma[32m 'int[]'[0m
            [34mReturnStmt[0m
                [31mImplicitCastExpr [32m 'int'[0m
                    [34mSubscriptExpr [32m'int'[0m
                        [34mVarExpr [37ma[32m 'int[]'[0m
                        [34mIntExpr [37m0[32m 'int'[0m
    [34mFunctionDecl [37mmain[32m 'int(void)'[0m
        [34mCompoundStmt[0m
            [34mReturnStmt[0m
                [31mImplicitCastExpr [32m 'int'[0m
                    [34mIntExpr [37m0[32m 'int'[0m
