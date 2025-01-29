#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <unordered_map>    

enum TokenType
{
    // Single-character tokens.
    LEFT_PAREN // "("
    ,
    RIGHT_PAREN // ")"
    ,
    LEFT_BRACE // "{"
    ,
    RIGHT_BRACE // "}"
    ,
    COMMA // ","
    ,
    DOT // "."
    ,
    MINUS // "-"
    ,
    PLUS // "+"
    ,
    SEMICOLON // ";"
    ,
    SLASH // "/"
    ,
    STAR // "*"
    ,
    QUESTION // "?"
    ,
    BANG // "!"
    ,
    EQUAL // "="
    ,
    GREATER // ">"
    ,
    LESS // "<"

    // two character tokens
    ,
    BANG_EQUAL // "!="
    ,
    EQUAL_EQUAL // "=="
    ,
    GREATER_EQUAL // ">="
    ,
    LESS_EQUAL // "<="

    // Literals.
    ,
    IDENTIFIER // "identifier"
    ,
    STRING // "string"
    ,
    NUMBER // "number"
    ,
    BOOLEAN // "true" or "false"

    // Keywords.
    ,
    AND // "and"
    ,
    CLASS // "class"
    ,
    ELSE // "else"
    ,
    FALSE // "false"
    ,
    FUN // "fun"
    ,
    FOR // "for"
    ,
    IF // "if"
    ,
    NIL // "nil"
    ,
    OR // "or"
    ,
    PRINT // "print"
    ,
    RETURN // "return"
    ,
    SUPER // "super"
    ,
    THIS // "this"
    ,
    TRUE // "true"
    ,
    VAR // "var"
    ,
    WHILE // "while"
    ,
    eof // "EOF"
    ,
    SHARP // "#"
    ,
    SLASH_SLASH // "//"
    ,
    STAR_STAR // "**"
};

class Token
{
private:
    const TokenType kType;
    const int kLine;
    const int kStart;
    const int kOffset;

public:
    Token(TokenType type, int line, int start, int offset);
    TokenType get_type() const;
    int get_line() const;
    int get_start() const;
    int get_offset() const;
};

class TokenUtilites
{
private:
    static const std::unordered_map<std::string, TokenType> string_tokens;
    static const std::unordered_map<int, std::string> token_strings;
public:
    static std::string token_type_to_string(TokenType token_type);
    static TokenType string_to_token_type(const std::string &token);
    static bool is_keyword(TokenType token_type);
    static bool is_keyword(const std::string &token);
    static bool is_equality(TokenType token_type);
    static bool is_comparison(TokenType token_type);
    static bool is_term(TokenType token_type);
    static bool is_factor(TokenType token_type);
    static bool is_power(TokenType token_type);
    static bool is_unary(TokenType token_type);
    static bool is_literal(TokenType token_type);
    static bool is_primary(TokenType token_type);
};

#endif // TOKEN_H
