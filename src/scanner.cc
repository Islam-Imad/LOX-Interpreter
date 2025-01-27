#include "include/scanner.h"
#include <iostream>
#include <string>
#include <vector>

Scanner::Scanner(const std::string &source) : kSource(source), start(0), current(0), line(1), offset(0) {}

bool Scanner::match(char expected) const
{
    return !is_at_end() && peek() == expected;
}

bool Scanner::is_at_end() const
{
    return current >= kSource.length();
}

char Scanner::peek() const
{
    if (is_at_end())
        return '\0';
    return kSource[current];
}

char Scanner::peek_next() const
{
    if (current + 1 >= kSource.length())
        return '\0';
    return kSource[current + 1];
}

char Scanner::advance()
{
    current++;
    offset++;
    return kSource[current - 1];
}

bool Scanner::is_digit(char c) const
{
    return c >= '0' && c <= '9';
}

bool Scanner::is_alpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::is_alphanumeric(char c) const
{
    return is_alpha(c) || is_digit(c);
}

void Scanner::add_token(TokenType type)
{
    tokens.push_back(Token(type, line, start, offset));
    offset = 0;
}

void Scanner::number()
{
    while (is_digit(peek()))
        advance();

    if (peek() == '.' && is_digit(peek_next()))
    {
        advance();
        while (is_digit(peek()))
            advance();
    }

    add_token(NUMBER);
}

void Scanner::string()
{
    while (peek() != '"' && !is_at_end())
    {
        if (peek() == '\n')
            line++;
        advance();
    }

    if (is_at_end())
    {
        std::cerr << "Unterminated string." << std::endl;
        return;
    }

    advance();

    add_token(STRING);
}

void Scanner::identifier()
{
    while (is_alphanumeric(peek()))
        advance();

    add_token(IDENTIFIER);
}

std::vector<Token> scan()
{
    
}