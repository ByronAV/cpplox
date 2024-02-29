#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <fmt/core.h>

#include <memory>
#include <vector>

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
template <>
struct formatter<TokenType> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) {
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
    return format_to(
        ctx.out(), "{}",
        token_names[static_cast<int>(
            t)]);  // Assuming TokenType can be formatted using "{}"
  }
};
}  // namespace fmt

template <typename T>
class Token {
 public:
  const TokenType type = TokenType::TEOF;
  const std::string lexeme = "";
  T literal;
  const unsigned int line = 0;

  Token(const TokenType &in_token, const std::string &in_lexeme, T in_literal,
        unsigned int in_line)
      : type(in_token),
        lexeme(in_lexeme),
        literal(std::move(in_literal)),
        line(in_line) {}
  Token(const TokenType &in_token, std::string &&in_lexeme, T in_literal,
        unsigned int in_line)
      : type(in_token),
        lexeme(std::move(in_lexeme)),
        literal(std::move(in_literal)),
        line(in_line) {}
  Token(Token &&input)
      : type(std::move(input.type)),
        lexeme(std::move(input.lexeme)),
        literal(std::move(input.literal)),
        line(std::move(input.line)) {}
  Token(const Token& input)
      : type(std::move(input.type)),
        lexeme(std::move(input.lexeme)),
        literal(std::move(input.literal)),
        line(std::move(input.line)) {}
  Token() = default;
  ~Token() = default;

  static inline auto GetTokens() { return &tokens; }

  static inline void ClearTokens() { tokens.clear(); }

  inline std::string ToString() const {
    if constexpr (std::is_same_v<T, const void *>) {
      return fmt::format("{} {}", type, lexeme);
    } else {
      return fmt::format("{} {} {}", type, lexeme, *literal);
    }
  }

  friend std::ostream &operator<<(std::ostream &stream, const Token &data) {
    stream << data.ToString();
    return stream;
  }

  static std::vector<std::unique_ptr<Token<T>>> tokens;
};

template <typename T>
std::vector<std::unique_ptr<Token<T>>> Token<T>::tokens;

#endif