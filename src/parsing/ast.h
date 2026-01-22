#ifndef AST_H
#define AST_H

#include <stdbool.h>
#include <stdint.h>
#include "../common/list.h"

#define NULL_AST_ID 0

typedef size_t ExprId;
typedef size_t StmtId;
typedef size_t DeclId;

typedef struct Ast {
    List exprs; // `List<Expression>`
    List stmts; // `List<Statement>`
    List decls; // `List<Declaration>`
    List root;  // `List<Declaration>` (ordered)
} Ast;

Ast AstNew();
bool AstIsValid(const Ast *self);

#endif