#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include <unordered_map>
#include <string>

class Eval {
public:
    static double eval(const ASTNode* node, std::unordered_map<std::string, double>& symbolTable);

private:
    static double evalASTNode(const ASTNode* node, std::unordered_map<std::string, double>& symbolTable);
    static double evalVariableDeclaration(const VariableDeclarationNode* node, std::unordered_map<std::string, double>& symbolTable);
    static double evalVariableUsage(const VariableUsageNode* node, std::unordered_map<std::string, double>& symbolTable);
};

#endif