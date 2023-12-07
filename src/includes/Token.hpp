#pragma once

#include <fmt/core.h>

#include <string>
#include <variant>

enum class TokenType {
  // Single-character tokens.
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  // User specific EOF because it's a macro in stdio
  TEOF
};

namespace fmt {
template <> struct formatter<TokenType> {
  template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const TokenType &t, FormatContext &ctx) {
    const char *token_names[] = {
        "(",      ")",   "{",     "}",     ",",      ".",          "-",
        "+",      ";",   "/",     "*",     "!",      "!=",         "=",
        "==",     ">",   ">=",    "<",     "<=",     "IDENTIFIER", "STRING",
        "NUMBER", "&&",  "CLASS", "ELSE",  "FALSE",  "FUN",        "FOR",
        "IF",     "NIL", "||",    "PRINT", "RETURN", "SUPER",      "THIS",
        "TRUE",   "VAR", "WHILE", "TEOF"};
    return format_to(ctx.out(), "{}",
                     token_names[static_cast<int>(
                         t)]); // Assuming TokenType can be formatted using "{}"
  }
};
} // namespace fmt

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  std::variant<const void *, std::unique_ptr<const double>,
               std::unique_ptr<const std::string>>
      literal;
  // const void* literal;
  const unsigned int line;

  template <typename T>
  Token(const TokenType &in_token, const std::string &in_lexeme, T in_literal,
        unsigned int in_line)
      : type(in_token), lexeme(in_lexeme), literal(std::move(in_literal)),
        line(in_line) {}
  template <typename T>
  Token(const TokenType &in_token, std::string &&in_lexeme, T in_literal,
        unsigned int in_line)
      : type(in_token), lexeme(std::move(in_lexeme)),
        literal(std::move(in_literal)), line(in_line) {}
  ~Token() = default;

  inline std::string ToString() const {
    if (type == TokenType::NUMBER)
    // std::get_if returns a pointer if the value stored is of type otherwise
    // null because we store pointers in the variant, to get the underlying we
    // need double reference
    {
      return fmt::format("{} {} {}", type, lexeme,
                         *std::get<std::unique_ptr<const double>>(literal));
    } else if (type == TokenType::STRING) {
      return fmt::format(
          "{} {} {}", type, lexeme,
          *std::get<std::unique_ptr<const std::string>>(literal));
    } else {
      return fmt::format("{} {}", type, lexeme);
    }
  }

  friend std::ostream &operator<<(std::ostream &stream, const Token &data) {
    stream << data.ToString();
    return stream;
  }
};