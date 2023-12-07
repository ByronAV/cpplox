#pragma once

#include <string>
#include <vector>
#include <robin_hood.h>
#include "Token.hpp"
#include "Error.hpp"

class Scanner {
public:
    explicit Scanner(const std::string& in_source);
    ~Scanner() = default;
    std::vector<std::unique_ptr<Token>> const& ScanTokens();
    inline bool IsAtEnd()
    {
        return static_cast<size_t>(current) >= source.size();
    }

private:
    inline char Advance()
    {
        return source.at(current++);
    }
    inline char Peek()
    {
        if (IsAtEnd()) { return '\0'; }
        return source.at(current);
    }
    inline char PeekNext()
    {
        if (static_cast<size_t>(current) + 1 >= source.size())
            { return '\0'; }
        return source.at(current + 1);
    }
    inline bool Match(char expected)
    {
        if (IsAtEnd()) { return false; }
        if (source.at(current) != expected) { return false; }

        current++;
        return true;
    }
    inline bool IsDigit(char c)
    {
        return c >= '0' && c <= '9';
    }
    inline bool IsAlpha(char c)
    {
        return ((c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z') ||
                c == '_');
    }
    inline bool IsAlphaNumeric(char c)
    {
        return (IsAlpha(c) || IsDigit(c));
    }

    void ScanToken();
    void AddToken(const TokenType& type);
    void AddToken(const TokenType& type, const void* literal);
    void AddToken(const TokenType& type, std::unique_ptr<const std::string> literal);
    void AddToken(const TokenType& type, std::unique_ptr<const double> literal);
    void String();
    void Number();
    void Identifier();

private:

    inline static int start = 0;
    inline static int current = 0;
    inline static int line = 1;

    inline static robin_hood::unordered_flat_map<std::string, TokenType> keywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}
    };
    std::string source;
    std::vector<std::unique_ptr<Token>> tokens;
};
