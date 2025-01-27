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

std::string TokenTypesToString(int tokenType)
{
    switch (tokenType)
    {
    case RIGHT_PAREN:
        return ")";
        break;
    case LEFT_BRACE:
        return "{";
        break;
    case RIGHT_BRACE:
        return "}";
        break;
    case COMMA:
        return ",";
        break;
    case DOT:
        return ".";
        break;
    case MINUS:
        return "-";
        break;
    case PLUS:
        return "+";
        break;
    case SEMICOLON:
        return ";";
        break;
    case SLASH:
        return "/";
        break;
    case STAR:
        return "*";
        break;
    case QUESTION:
        return "?";
        break;
    case BANG:
        return "!";
        break;
    case EQUAL:
        return "=";
        break;
    case GREATER:
        return ">";
        break;
    case LESS:
        return "<";
        break;
    case BANG_EQUAL:
        return "!=";
        break;
    case EQUAL_EQUAL:
        return "==";
        break;
    case GREATER_EQUAL:
        return ">=";
        break;
    case LESS_EQUAL:
        return "<=";
        break;
    case IDENTIFIER:
        return "identifier";
        break;
    case STRING:
        return "string";
        break;
    case NUMBER:
        return "number";
        break;
    case BOOLEAN:
        return "true or false";
        break;
    case AND:
        return "and";
        break;
    case CLASS:
        return "class";
        break;
    case ELSE:
        return "else";
        break;
    case FALSE:
        return "false";
        break;
    case FUN:
        return "fun";
        break;
    case FOR:
        return "for";
        break;
    case IF:
        return "if";
        break;
    case NIL:
        return "nil";
        break;
    case OR:
        return "or";
        break;
    case PRINT:
        return "print";
        break;
    case RETURN:
        return "return";
        break;
    case SUPER:
        return "super";
        break;
    case THIS:
        return "this";
        break;
    case TRUE:
        return "true";
        break;
    case VAR:
        return "var";
        break;
    case WHILE:
        return "while";
        break;
    case eof:
        return "EOF";
        break;
    case SHARP:
        return "#";
        break;
    case SLASH_SLASH:
        return "//";
        break;
    default:
        return "Unknown Token Type";
        break;
    }
}

const std::unordered_map<std::string, TokenType> TokenUtilites::string_tokens = {
    {"and", AND},
    {"class", CLASS},
    {"else", ELSE},
    {"false", FALSE},
    {"fun", FUN},
    {"for", FOR},
    {"if", IF},
    {"nil", NIL},
    {"or", OR},
    {"print", PRINT},
    {"return", RETURN},
    {"super", SUPER},
    {"this", THIS},
    {"true", TRUE},
    {"var", VAR},
    {"while", WHILE}};

const std::unordered_map<int, std::string> TokenUtilites::token_strings = {
    {RIGHT_PAREN, ")"},
    {LEFT_BRACE, "{"},
    {RIGHT_BRACE, "}"},
    {COMMA, ","},
    {DOT, "."},
    {MINUS, "-"},
    {PLUS, "+"},
    {SEMICOLON, ";"},
    {SLASH, "/"},
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
    {SLASH_SLASH, "//"}};

bool TokenUtilites::is_keyword(TokenType token_type)
{
    return string_tokens.find(token_type_to_string(token_type)) != string_tokens.end();
}

bool TokenUtilites::is_keyword(const std::string &token)
{
    return string_tokens.find(token) != string_tokens.end();
}

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