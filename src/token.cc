#include "include/token.h"

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
    default:
        return "Unknown Token Type";
        break;
    }
}