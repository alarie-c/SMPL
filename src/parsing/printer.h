#ifndef PRINTER_H
#define PRINTER_H

#include "ast.h"
#include "../common/source.h"
#include <stdbool.h>

typedef struct AstPrinter {
    const Source *src;
    const Ast *ast;
    size_t indent;
} AstPrinter;

AstPrinter AstPrinterNew(const Source *src, const Ast *ast);
bool AstPrinterIsValid(const AstPrinter *self);

void AstPrintExpr(AstPrinter *self, ExprId id);

#endif