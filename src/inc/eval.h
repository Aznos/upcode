#ifndef EVAL_H
#define EVAL_H

#include "ast.h"

class Eval {
    public:
        static double eval(const ASTNode* node);
};

#endif