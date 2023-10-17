#pragma once

#include <string>
#include <fmt/core.h>

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    // User specific EOF because it's a macro in stdio
    TEOF
};

namespace fmt {
  template <>
  struct formatter<TokenType> {
    template <typename ParseContext>
    constexpr auto parse(ParseContext& ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const TokenType& t, FormatContext& ctx) {
        const char* token_names[] = {
                "(", ")", "{", "}",
                ",", ".", "-", "+", ";", "/", "*",
                "!", "!=", "=", "==",
                ">", ">=", "<", "<=",
                "identifier", "string", "int",
                "&&", "class", "else", "false", "fun", "for", "if", "nil", "||",
                "print", "return", "super", "this", "true", "var", "while"
            };
      return format_to(ctx.out(), "{}", token_names[static_cast<int>(t)]); // Assuming TokenType can be formatted using "{}"
    }
  };
}

// TODO: Maybe make it template and avoid the void* and have a type of T there.
class Token {
  public:
    const TokenType type;
    const std::string lexeme;
    const void* literal;
    const unsigned int line;

    Token(const TokenType& in_token, const std::string& in_lexeme, const void* in_literal, unsigned int in_line);
    ~Token() = default;

    inline std::string ToString()
    {
        return fmt::format("{} {} {}", type, lexeme, literal);
    }

    friend std::ostream& operator<<(std::ostream& stream, const Token& data)
    {
        stream << fmt::format("{} {} {}", data.type, data.lexeme, data.literal);
        return stream;
    }

};