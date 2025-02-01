#include <iostream>
#include "parser.h"
#include "expression.h"
#include "token.h"
#include "value.h"
#include <stdexcept>

std::string get_substr(const Token &token, const std::string &source)
{
    return source.substr(token.get_start(), token.get_offset());
}

Value get_value(Token token, const std::string &lexeme)
{
    try
    {
        switch (token.get_type())
        {
        case NUMBER:
            return Value(std::stod(lexeme));
        case STRING:
            return Value(lexeme);
        case TRUE:
            return Value(true);
        case FALSE:
            return Value(false);
        case NIL:
            return Value();
        default:
            throw std::runtime_error("Invalid value");
        }
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Invalid value");
    }
}

Parser::Parser(const std::vector<Token> &tokens, const TokenUtilites &token_utilites, const std::string &source) : tokens(tokens), token_utilites(token_utilites), kSource(source) {}

Token Parser::previous_token() const
{
    if (current == 0)
    {
        throw std::runtime_error("No previous token");
    }
    return tokens[current - 1];
}

Token Parser::peek() const
{
    return tokens[current];
}

Token Parser::advance()
{
    if (!is_at_end())
    {
        current++;
    }
    return previous_token();
}

bool Parser::is_at_end() const
{
    return current >= tokens.size();
}

std::unique_ptr<Expression> Parser::expression()
{
    return assignment();
}

std::unique_ptr<Expression> Parser::assignment()
{
    std::unique_ptr<Expression> expr = logical_or();
    if (peek().get_type() == EQUAL)
    {
        VariableExpression *variable = dynamic_cast<VariableExpression *>(expr.get());
        if (variable == nullptr)
        {
            throw std::runtime_error("Invalid assignment target");
        }
        advance();
        std::string name = variable->name;
        std::unique_ptr<Expression> initialization = assignment();
        expr = std::make_unique<AssignExpression>(name, std::move(initialization));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::logical_or()
{
    std::unique_ptr<Expression> expr = logical_and();

    while (peek().get_type() == OR)
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = logical_and();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::logical_and()
{
    std::unique_ptr<Expression> expr = equality();

    while (peek().get_type() == AND)
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = equality();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::equality()
{
    std::unique_ptr<Expression> expr = comparison();

    while (token_utilites.is_equality(peek().get_type()))
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = comparison();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::comparison()
{
    std::unique_ptr<Expression> expr = term();

    while (token_utilites.is_comparison(peek().get_type()))
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = term();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::term()
{
    std::unique_ptr<Expression> expr = factor();

    while (token_utilites.is_term(peek().get_type()))
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = factor();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::factor()
{
    std::unique_ptr<Expression> expr = power();

    while (token_utilites.is_factor(peek().get_type()))
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = power();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::power()
{
    std::unique_ptr<Expression> expr = unary();

    while (token_utilites.is_power(peek().get_type()))
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = unary();
        expr = std::make_unique<BinaryExpression>(std::move(expr), std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::unary()
{
    if (token_utilites.is_unary(peek().get_type()))
    {
        Token op = peek();
        advance();
        std::unique_ptr<Expression> right = unary();
        return std::make_unique<UnaryExpression>(std::move(right), token_utilites.token_type_to_string(op.get_type()));
    }

    return primary();
}

std::unique_ptr<Expression> Parser::primary()
{
    if (token_utilites.is_primary(peek().get_type()))
    {
        Token primary = peek();
        advance();
        if (primary.get_type() == LEFT_PAREN)
        {
            std::unique_ptr<Expression> expr = expression();
            if (peek().get_type() != RIGHT_PAREN)
            {
                throw std::runtime_error("Expected ')'");
            }
            advance();
            return std::make_unique<GroupingExpression>(std::move(expr));
        }
        else if (primary.get_type() == IDENTIFIER)
        {
            return std::make_unique<VariableExpression>(get_substr(primary, kSource));
        }
        return std::make_unique<LiteralExpression>(get_value(primary, get_substr(primary, kSource)));
    }

    throw std::runtime_error("Invalid expression");
}

std::unique_ptr<Statement> Parser::statement()
{
    if (peek().get_type() == PRINT)
    {
        advance();
        return print_statement();
    }
    return expression_statement();
}

std::unique_ptr<Statement> Parser::expression_statement()
{
    std::unique_ptr<Expression> expr = expression();
    if (peek().get_type() != SEMICOLON)
    {
        throw std::runtime_error("Expected ';'");
    }
    advance();
    return std::make_unique<ExpressionStatement>(std::move(expr));
}

std::unique_ptr<Statement> Parser::print_statement()
{
    std::unique_ptr<Expression> expr = expression();
    if (peek().get_type() != SEMICOLON)
    {
        throw std::runtime_error("Expected ';'");
    }
    advance();
    return std::make_unique<PrintStatement>(std::move(expr));
}

std::unique_ptr<Statement> Parser::var_declaration()
{
    if (peek().get_type() != IDENTIFIER)
    {
        throw std::runtime_error("Expected identifier");
    }
    Token name = peek();
    advance();

    std::unique_ptr<Expression> expr = nullptr;
    if (peek().get_type() == EQUAL)
    {
        advance();
        expr = expression();
    }
    if (peek().get_type() != SEMICOLON)
    {
        throw std::runtime_error("Expected ';'");
    }
    advance();
    return std::make_unique<VarDeclarationStatement>(get_substr(name, kSource), std::move(expr));
}

std::unique_ptr<Statement> Parser::if_statement()
{
    if (peek().get_type() != LEFT_PAREN)
    {
        throw std::runtime_error("Expected '('");
    }
    advance();

    std::unique_ptr<Expression> condition = expression();

    if (peek().get_type() != RIGHT_PAREN)
    {
        throw std::runtime_error("Expected ')'");
    }
    advance();

    std::vector<std::unique_ptr<const Statement>> block;
    if (peek().get_type() != LEFT_BRACE)
    {
        throw std::runtime_error("Expected '{'");
    }
    advance();
    while (peek().get_type() != RIGHT_BRACE)
    {
        block.push_back(declaration());
    }
    advance();

    std::unique_ptr<Statement> else_branch = nullptr;
    if (peek().get_type() == ELSE)
    {
        advance();
        if (peek().get_type() == IF)
        {
            advance();
            std::unique_ptr<Statement> else_if = if_statement();
            StatementTypeVisitor visitor;
            else_if->accept(visitor);
            if (visitor.get_result() != StatementType::IF_STATEMENT)
            {
                throw std::runtime_error("Expected if statement");
            }
            else_branch = std::move(else_if);
        }
        else if (peek().get_type() == LEFT_BRACE)
        {
            advance();
            std::unique_ptr<const Expression> nested_condition = std::make_unique<LiteralExpression>(Value(true));
            std::vector<std::unique_ptr<const Statement>> nested_block;
            while (peek().get_type() != RIGHT_BRACE)
            {
                nested_block.push_back(declaration());
            }
            advance();
            else_branch = std::make_unique<IfStatement>(std::move(nested_condition), std::move(nested_block), nullptr);
        }
        else
        {
            throw std::runtime_error("Expected '{' or 'if'");
        }
    }
    return std::make_unique<IfStatement>(std::move(condition), std::move(block), std::move(else_branch));
}

std::unique_ptr<Statement> Parser::while_statement()
{
    if (peek().get_type() != LEFT_PAREN)
    {
        throw std::runtime_error("Expected '('");
    }
    advance();

    std::unique_ptr<Expression> condition = expression();

    if (peek().get_type() != RIGHT_PAREN)
    {
        throw std::runtime_error("Expected ')'");
    }
    advance();

    std::vector<std::unique_ptr<const Statement>> block;
    if (peek().get_type() != LEFT_BRACE)
    {
        throw std::runtime_error("Expected '{'");
    }
    advance();
    while (peek().get_type() != RIGHT_BRACE)
    {
        block.push_back(declaration());
    }
    advance();

    return std::make_unique<WhileStatement>(std::move(condition), std::move(block));
}



std::unique_ptr<Statement> Parser::declaration()
{
    if (peek().get_type() == VAR)
    {
        advance();
        return var_declaration();
    }
    else if (peek().get_type() == IF)
    {
        advance();
        return if_statement();
    }
    else if (peek().get_type() == WHILE)
    {
        advance();
        return while_statement();
    }
    return statement();
}

std::vector<std::unique_ptr<const Statement>> Parser::parse()
{
    while (!is_at_end())
    {
        try
        {
            statements.push_back(declaration());
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
            throw std::runtime_error("Invalid statement");
        }
    }
    return std::move(statements);
}