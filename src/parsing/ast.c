#include "ast.h"
#include "expr.h"

#define INIT_EXPR_CAPACITY 512
#define INIT_STMT_CAPACITY 128
#define INIT_DECL_CAPACITY 64
#define INIT_ROOT_CAPACITY 64

Ast AstNew() {
    // Allocate the 4 lists
    List exprList = ListNew(sizeof(Expression), INIT_EXPR_CAPACITY);
    List stmtList = ListNew(sizeof(Expression), INIT_STMT_CAPACITY);
    List declList = ListNew(sizeof(Expression), INIT_DECL_CAPACITY);
    List rootList = ListNew(sizeof(Expression), INIT_ROOT_CAPACITY);

    Ast ast = {
        .exprs = exprList,
        .stmts = stmtList,
        .decls = declList,
        .root  = rootList,
    };

    // Make sure these are all valid
    if (!(ListIsValid(&ast.exprs)
        && ListIsValid(&ast.stmts)
        && ListIsValid(&ast.decls)
        && ListIsValid(&ast.root))
    ) {
        return (Ast) {0};
    }

    // Seed each list with the sentinel node, this will take the place of
    // the "null index" for each AST node id.
    Expression sentinelExpr = (Expression) {0};
    // Statement sentinelStmt = (Statement) {0};
    // Declration sentinelDecl = (Declaration) {0};

    /* discard */ ListPush(&ast.exprs, &sentinelExpr);
    /* discard */ ListPush(&ast.stmts, &sentinelExpr);
    /* discard */ ListPush(&ast.decls, &sentinelExpr);
    /* discard */ ListPush(&ast.root, &sentinelExpr);
    // /* discard */ ListPush(&ast.stmts, &sentinelStmt);
    // /* discard */ ListPush(&ast.decls, &sentinelDecl);

    // Should this be a program node?
    // /* discard */ ListPush(&ast.root, &sentinelDecl);

    // Return the seeded AST
    return ast;
}

bool AstIsValid(const Ast *self) {
    if (!self) return false;
    
    bool listsValid = (
        ListIsValid(&self->exprs)
        && ListIsValid(&self->stmts)
        && ListIsValid(&self->decls)
        && ListIsValid(&self->root)
    );
    
    bool listsHaveSentinels = (
        self->exprs.count >= 1
        && self->stmts.count >= 1
        && self->decls.count >= 1
        && self->root.count >= 1
    );

    return (listsValid && listsHaveSentinels);
}