#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "token.h"

class Scanner
{
private:
    const std::string kSource;
    const TokenUtilites kTokenUtilites;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;
    int offset;
    
    bool is_digit(char c) const;
    bool is_alpha(char c) const;
    bool is_alphanumeric(char c) const;
    
    bool match(char expected) const;
    bool is_at_end() const;
    char peek() const;
    char peek_next() const;
    char advance();
    
    void add_token(TokenType type);
    
    void number();
    void string();
    void identifier();
    void single_line_comment();

public:
    Scanner(const std::string &source, const TokenUtilites &tokenUtilites);
    std::vector<Token> scan();
};

#endif // SCANNER_H