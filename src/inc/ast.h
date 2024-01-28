#ifndef AST_H
#define AST_H

#include <memory>
#include <vector>
#include <string>

class ASTNode {
    public:
        virtual ~ASTNode() = default;
};

class NumberNode : public ASTNode {
    public:
        double value;
        explicit NumberNode(double value) : value(value) {}
};

class BinaryOpNode : public ASTNode {
    public:
        char op;
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;

        BinaryOpNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
            : op(op), left(std::move(left)), right(std::move(right)) {}
};

class VariableDeclarationNode : public ASTNode {
    public:
        std::string name;
        std::unique_ptr<ASTNode> expression;

        VariableDeclarationNode(const std::string &name, std::unique_ptr<ASTNode> expression)
            : name(name), expression(std::move(expression)) {}
};

class VariableUsageNode : public ASTNode {
    public:
        std::string name;

        explicit VariableUsageNode(const std::string &name) : name(name) {}
};

#endif