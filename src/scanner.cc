#include "include/scanner.h"
#include <iostream>
#include <string>
#include <vector>

Scanner::Scanner(const std::string &source, const TokenUtilites &tokenUtilites) : kTokenUtilites(tokenUtilites), kSource(source), start(0), current(0), line(1), offset(0) {}

bool Scanner::match(char expected)
{
    if (is_at_end())
        return false;
    if (peek() != expected)
        return false;
    advance();
    return true;
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
        advance();
    }

    if (is_at_end())
    {
        std::cerr << "Unterminated string." << std::endl;
        return;
    }

    advance();
    start++;
    offset -= 2;
    add_token(STRING);
}

void Scanner::identifier()
{
    while (is_alphanumeric(peek()))
        advance();
    const std::string text = kSource.substr(start, offset);
    TokenType token_type = IDENTIFIER;
    std::cout << text << std::endl;
    std::cout << kTokenUtilites.is_keyword(text) << std::endl;
    if (kTokenUtilites.is_keyword(text))
    {
        token_type = kTokenUtilites.string_to_token_type(text);
    }

    add_token(token_type);
}

void Scanner::single_line_comment()
{
    while (peek() != '\n' && !is_at_end())
        advance();
}

std::vector<Token> Scanner::scan()
{
    while (!is_at_end())
    {
        start = current;
        char c = advance();
        switch (c)
        {
        case '(':
            add_token(LEFT_PAREN);
            break;
        case ')':
            add_token(RIGHT_PAREN);
            break;
        case '{':
            add_token(LEFT_BRACE);
            break;
        case '}':
            add_token(RIGHT_BRACE);
            break;
        case ',':
            add_token(COMMA);
            break;
        case '.':
            add_token(DOT);
            break;
        case '-':
            add_token(MINUS);
            break;
        case '+':
            add_token(PLUS);
            break;
        case ';':
            add_token(SEMICOLON);
            break;
        case '*':
            add_token(match('*') ? STAR_STAR : STAR);
            break;
        case '?':
            add_token(QUESTION);
            break;
        case '!':
            add_token(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            add_token(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            add_token(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            add_token(match('=') ? GREATER_EQUAL : GREATER);
            break;
        case '/':
            add_token(match('/') ? SLASH_SLASH : SLASH);
            break;
        case '#':
            single_line_comment();
            line++;
            offset = 0;
            break;
        case '\"':
            string();
            break;
        case ' ':
        case '\r':
        case '\t':
            offset = 0;
            break;
        case '\n':
            offset = 0;
            line++;
            break;
        default:
            if (is_digit(c))
                number();
            else if (is_alpha(c))
                identifier();
            else
            {
                throw std::runtime_error("Unexpected character.");
                break;
            }
        }
    }
    return tokens;
}