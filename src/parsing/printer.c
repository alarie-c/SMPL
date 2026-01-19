#include "printer.h"
#include "ast.h"
#include "expr.h"
#include "stdio.h"

#define SPACES(k)                                                              \
    for (int _i = 0; _i < (k); _i++)                                           \
        fputc(' ', stdout);

void indent(AstPrinter *self) {
    self += 4;
}

void dedent(AstPrinter *self) {
    if (self->indent < 4) return;
    self -= 4;
}

AstPrinter AstPrinterNew(const Source *src, const Ast *ast) {
    if (!src || !ast) {
        return (AstPrinter) {0};
    }

    return (AstPrinter) {
        .ast = ast,
        .src = src,
        .indent = 0,
    };
}

bool AstPrinterIsValid(const AstPrinter *self) {
    return (self
        && self->ast
        && self->src
        && AstIsValid(self->ast)
    );
}

void AstPrintExpr(AstPrinter *self, ExprId id) {
    //SPACES(self->indent);
    if (!self || !AstPrinterIsValid(self)) {
        printf("<invalid AstPrinter pointer>");
        return;
    }

    Expression *expr = AstExprGet(self->ast, id);

    switch (expr->kind) {
    case EXPR_INT: {
        printf("int(%lli)\n", expr->data.exprInt);
        return;
    }
    case EXPR_FLOAT: {
        printf("float(%f)\n", expr->data.exprFloat);
        return;
    }
    case EXPR_SYMBOL: {
        printf("symbol(");
        SubstringPrint(stdout, &expr->data.exprSymbol);
        printf(")\n");
        return;
    }
    case EXPR_STR: {
        printf("string(");
        SubstringPrint(stdout, &expr->data.exprStr);
        printf(")\n");
        return;
    }
    case EXPR_BINARY: {
        printf("binary(%s,\n", expr->data.exprBinary.op);
        
        indent(self);
        AstPrintExpr(self, expr->data.exprBinary.lhs);
        AstPrintExpr(self, expr->data.exprBinary.rhs);
        dedent(self);

        SPACES(self->indent);
        printf(")\n");
        return;
    }
    default: {
        printf("that expression kind is not yet implemented");
    }
    }
}