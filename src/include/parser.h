#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>
#include <memory>
#include "expression.h"
#include "object.h"
#include "token.h"
#include "statement.h"

std::shared_ptr<OBJ::Object> get_value(Token token, const std::string &source);

class Parser
{
private:
    const std::string kSource;
    const std::vector<Token> tokens;
    const TokenUtilites token_utilites;
    std::vector<std::unique_ptr<const Statement>> statements;
    int current = 0;

    Token previous_token() const;
    Token peek() const;
    Token advance();

    bool is_at_end() const;

public:
    Parser(const std::vector<Token> &tokens, const TokenUtilites &token_utilites, const std::string &source);
    std::vector<std::unique_ptr<const Statement>> parse();
    std::vector<std::unique_ptr<const Statement>> block();
    std::unique_ptr<Statement> statement();
    std::unique_ptr<Statement> expression_statement();
    std::unique_ptr<Statement> print_statement();
    std::unique_ptr<Statement> var_declaration();
    std::unique_ptr<Statement> if_statement();
    std::unique_ptr<Statement> while_statement();
    std::unique_ptr<Statement> for_statement();
    std::unique_ptr<Statement> compound_statement();
    std::unique_ptr<Statement> declaration();

    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> assignment();
    std::unique_ptr<Expression> logical_or();
    std::unique_ptr<Expression> logical_and();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> term();
    std::unique_ptr<Expression> factor();
    std::unique_ptr<Expression> power();
    std::unique_ptr<Expression> unary();
    std::unique_ptr<Expression> primary();
};

#endif // PARSE_H