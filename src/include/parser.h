#ifndef PARSE_H
#define PARSE_H

#include <string>
#include <vector>
#include <memory>
#include "expression.h"
#include "value.h"
#include "token.h"

Value get_value(Token token, const std::string &source);

class Parser
{
private:
    const std::string kSource;
    const std::vector<Token> tokens;
    const TokenUtilites token_utilites;
    int current = 0;
    Token previous_token() const;
    Token peek() const;
    Token advance();

    bool is_at_end() const;

public:
    Parser(const std::vector<Token> &tokens, const TokenUtilites &token_utilites, const std::string &source);
    std::unique_ptr<Expression> expression();
    std::unique_ptr<Expression> equality();
    std::unique_ptr<Expression> comparison();
    std::unique_ptr<Expression> term();
    std::unique_ptr<Expression> factor();
    std::unique_ptr<Expression> power();
    std::unique_ptr<Expression> unary();
    std::unique_ptr<Expression> primary();
};

#endif // PARSE_H