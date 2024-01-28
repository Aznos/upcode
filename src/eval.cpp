#include "eval.h"
#include <stdexcept>

double Eval::eval(const ASTNode* node) {
    if(const auto *numberNode = dynamic_cast<const NumberNode*>(node)) {
        return numberNode->value;
    } else if(const auto *binaryOpNode = dynamic_cast<const BinaryOpNode*>(node)) {
        double left = eval(binaryOpNode->left.get());
        double right = eval(binaryOpNode->right.get());
        switch(binaryOpNode->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return right != 0 ? left / right: throw std::runtime_error("Division by zero");
            default: throw std::runtime_error("Unknown binary operator");
        }
    }
    throw std::runtime_error("Unknown AST node type");
}