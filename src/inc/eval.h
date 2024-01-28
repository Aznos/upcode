#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include <unordered_map>
#include <string>

class Eval {
    public:
        static double eval(const ASTNode* node);
    private:
        static std::unordered_map<std::string, double> symbolTable;
        static double evalASTNode(const ASTNode* node);
        static double evalVariableDeclaration(const VariableDeclarationNode* node);
        static double evalVariableUsage(const VariableUsageNode* node);
};

#endif