#include "eval.h"
#include <stdexcept>

double Eval::eval(const ASTNode* node, std::unordered_map<std::string, double>& symbolTable) {
    return evalASTNode(node, symbolTable);
}

double Eval::evalASTNode(const ASTNode* node, std::unordered_map<std::string, double>& symbolTable) {
    if (const auto* numberNode = dynamic_cast<const NumberNode*>(node)) {
        return numberNode->value;
    } else if (const auto* binaryOpNode = dynamic_cast<const BinaryOpNode*>(node)) {
        double left = evalASTNode(binaryOpNode->left.get(), symbolTable);
        double right = evalASTNode(binaryOpNode->right.get(), symbolTable);
        switch (binaryOpNode->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return right != 0 ? left / right : throw std::runtime_error("Division by zero");
            default: throw std::runtime_error("Unknown binary operator");
        }
    } else if (const auto* varDeclNode = dynamic_cast<const VariableDeclarationNode*>(node)) {
        return evalVariableDeclaration(varDeclNode, symbolTable);
    } else if (const auto* varUsageNode = dynamic_cast<const VariableUsageNode*>(node)) {
        return evalVariableUsage(varUsageNode, symbolTable);
    }

    throw std::runtime_error("Unknown AST node type");
}

double Eval::evalVariableDeclaration(const VariableDeclarationNode* node, std::unordered_map<std::string, double>& symbolTable) {
    double value = evalASTNode(node->expression.get(), symbolTable);
    symbolTable[node->name] = value;
    return value;
}

double Eval::evalVariableUsage(const VariableUsageNode* node, std::unordered_map<std::string, double>& symbolTable) {
    if (symbolTable.find(node->name) == symbolTable.end()) {
        throw std::runtime_error("Variable not defined: " + node->name);
    }

    return symbolTable[node->name];
}
