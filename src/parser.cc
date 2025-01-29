#include <iostream>
#include "parser.h"
#include "expression.h"
#include "token.h"
#include "value.h"
#include <stdexcept>

Value get_value(Token token, const std::string &source)
{
    try
    {
        std::string lexeme = source.substr(token.get_start(), token.get_offset());
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
    return logical_or();
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
    if (token_utilites.is_literal(peek().get_type()))
    {
        Token literal = peek();
        advance();
        return std::make_unique<LiteralExpression>(get_value(literal, kSource));
    }
    throw std::runtime_error("Invalid expression");
}

std::vector<std::unique_ptr<Statement>> Parser::parse()
{
    while (!is_at_end())
    {
        try
        {
            statements.push_back(std::move(statement()));
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << std::endl;
            // while (!is_at_end() && peek().get_type() != SEMICOLON)
            // {
            //     advance();
            // }
            throw std::runtime_error("Invalid statement");
        }
    }
    return std::move(statements);
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