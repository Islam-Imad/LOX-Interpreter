#include "include/token.h"
#include <string>
#include <unordered_map>
#include <stdexcept>

Token::Token(TokenType type, int line, int start, int offset)
    : kType(type), kLine(line), kStart(start), kOffset(offset) {}

TokenType Token::get_type() const
{
    return kType;
}

int Token::get_line() const
{
    return kLine;
}

int Token::get_start() const
{
    return kStart;
}

int Token::get_offset() const
{
    return kOffset;
}

const std::unordered_map<std::string, TokenType> TokenUtilites::string_tokens = {
    {"(", LEFT_PAREN},
    {")", RIGHT_PAREN},
    {"{", LEFT_BRACE},
    {"}", RIGHT_BRACE},
    {",", COMMA},
    {".", DOT},
    {"-", MINUS},
    {"+", PLUS},
    {";", SEMICOLON},
    {"/", SLASH},
    {"//", SLASH_SLASH},
    {"*", STAR},
    {"?", QUESTION},
    {"!", BANG},
    {"=", EQUAL},
    {">", GREATER},
    {"<", LESS},
    {"!=", BANG_EQUAL},
    {"==", EQUAL_EQUAL},
    {">=", GREATER_EQUAL},
    {"<=", LESS_EQUAL},
    {"identifier", IDENTIFIER},
    {"string", STRING},
    {"number", NUMBER},
    {"true", TRUE},
    {"false", FALSE},
    {"and", AND},
    {"&&", AND},
    {"class", CLASS},
    {"else", ELSE},
    {"false", FALSE},
    {"fun", FUN},
    {"for", FOR},
    {"if", IF},
    {"nil", NIL},
    {"or", OR},
    {"||", OR},
    {"print", PRINT},
    {"return", RETURN},
    {"super", SUPER},
    {"this", THIS},
    {"true", TRUE},
    {"var", VAR},
    {"while", WHILE},
    {"**", STAR_STAR},
    {"#", SHARP},
    {"//", SLASH_SLASH},
    {"%", MOD}
    };

const std::unordered_map<int, std::string> TokenUtilites::token_strings = {
    {LEFT_PAREN, "("},
    {RIGHT_PAREN, ")"},
    {LEFT_BRACE, "{"},
    {RIGHT_BRACE, "}"},
    {COMMA, ","},
    {DOT, "."},
    {MINUS, "-"},
    {PLUS, "+"},
    {SEMICOLON, ";"},
    {SLASH, "/"},
    {SLASH_SLASH, "//"},
    {STAR, "*"},
    {QUESTION, "?"},
    {BANG, "!"},
    {EQUAL, "="},
    {GREATER, ">"},
    {LESS, "<"},
    {BANG_EQUAL, "!="},
    {EQUAL_EQUAL, "=="},
    {GREATER_EQUAL, ">="},
    {LESS_EQUAL, "<="},
    {IDENTIFIER, "identifier"},
    {STRING, "string"},
    {NUMBER, "number"},
    {BOOLEAN, "true or false"},
    {AND, "and"},
    {CLASS, "class"},
    {ELSE, "else"},
    {FALSE, "false"},
    {FUN, "fun"},
    {FOR, "for"},
    {IF, "if"},
    {NIL, "nil"},
    {OR, "or"},
    {PRINT, "print"},
    {RETURN, "return"},
    {SUPER, "super"},
    {THIS, "this"},
    {TRUE, "true"},
    {VAR, "var"},
    {WHILE, "while"},
    {eof, "EOF"},
    {SHARP, "#"},
    {SLASH_SLASH, "//"},
    {STAR_STAR, "**"},
    {MOD, "%"}
    };

TokenType TokenUtilites::string_to_token_type(const std::string &token)
{
    auto it = string_tokens.find(token);
    if (it != string_tokens.end())
    {
        return it->second;
    }
    throw std::runtime_error("Unknown token type");
}

std::string TokenUtilites::token_type_to_string(TokenType token_type)
{
    auto it = token_strings.find(token_type);
    if (it != token_strings.end())
    {
        return it->second;
    }
    throw std::runtime_error("Unknown token type");
}

bool TokenUtilites::is_keyword(const std::string &token)
{
    if (string_tokens.find(token) == string_tokens.end())
    {
        return false;
    }
    return is_keyword(string_to_token_type(token));
}

bool TokenUtilites::is_equality(TokenType token_type)
{
    return token_type == EQUAL_EQUAL || token_type == BANG_EQUAL;
}

bool TokenUtilites::is_comparison(TokenType token_type)
{
    return token_type == GREATER || token_type == GREATER_EQUAL || token_type == LESS || token_type == LESS_EQUAL;
}

bool TokenUtilites::is_term(TokenType token_type)
{
    return token_type == PLUS || token_type == MINUS;
}

bool TokenUtilites::is_factor(TokenType token_type)
{
    return token_type == STAR || token_type == SLASH || token_type == SLASH_SLASH || token_type == MOD;
}

bool TokenUtilites::is_power(TokenType token_type)
{
    return token_type == STAR_STAR;
}

bool TokenUtilites::is_unary(TokenType token_type)
{
    return token_type == BANG || token_type == MINUS;
}

bool TokenUtilites::is_literal(TokenType token_type)
{
    return token_type == STRING || token_type == NUMBER || token_type == TRUE || token_type == FALSE || token_type == NIL;
}

bool TokenUtilites::is_primary(TokenType token_type)
{
    return is_literal(token_type) || token_type == LEFT_PAREN || token_type == IDENTIFIER;
}

bool TokenUtilites::is_keyword(TokenType token_type)
{
    return token_type == AND || token_type == CLASS || token_type == ELSE || token_type == FALSE || token_type == FUN || token_type == FOR || token_type == IF || token_type == NIL || token_type == OR || token_type == PRINT || token_type == RETURN || token_type == SUPER || token_type == THIS || token_type == TRUE || token_type == VAR || token_type == WHILE;
}