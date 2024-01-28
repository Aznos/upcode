#include "eval.h"
#include <stdexcept>

std::unordered_map<std::string, double> Eval::symbolTable;

double Eval::eval(const ASTNode* node) {
    return evalASTNode(node);
}

double Eval::evalASTNode(const ASTNode* node) {
    if(const auto *numberNode = dynamic_cast<const NumberNode*>(node)) {
        return numberNode->value;
    } else if(const auto *binaryOpNode = dynamic_cast<const BinaryOpNode*>(node)) {
        double left = evalASTNode(binaryOpNode->left.get());
        double right = evalASTNode(binaryOpNode->right.get());
        switch(binaryOpNode->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return right != 0 ? left / right: throw std::runtime_error("Division by zero");
            default: throw std::runtime_error("Unknown binary operator");
        }
    } else if(const auto* varDeclNode = dynamic_cast<const VariableDeclarationNode*>(node)) {
        return evalVariableDeclaration(varDeclNode);
    } else if(const auto* varUsageNode = dynamic_cast<const VariableUsageNode*>(node)) {
        return evalVariableUsage(varUsageNode);
    }

    throw std::runtime_error("Unknown AST node type");
}

double Eval::evalVariableDeclaration(const VariableDeclarationNode* node) {
    double value = evalASTNode(node->expression.get());
    symbolTable[node->name] = value;
    return value;
}

double Eval::evalVariableUsage(const VariableUsageNode* node) {
    if(symbolTable.find(node->name) == symbolTable.end()) {
        throw std::runtime_error("Variable not defined: " + node->name);
    }

    return symbolTable[node->name];
}