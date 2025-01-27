#ifndef TOKEN_H
#define TOKEN_H

#include <string>

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
};

// enum TokenCategory
// {
//     EQUALITY // ==, !=
//     ,
//     COMPARISON // > , < , == , != , >= , <=
//     ,
//     TERM // + , -
//     ,
//     FACTOR // '*' , /
//     ,
//     UNARY // '!' , -
//     ,
//     LITERAL // string , number , boolean
// };

std::string TokenTypeToString(TokenType type);

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

#endif // TOKEN_H
