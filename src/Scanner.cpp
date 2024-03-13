
#include "includes/Scanner.hpp"

#include "includes/Error.hpp"

Scanner::Scanner(const std::string &in_source) : source(in_source) {}

void Scanner::AddToken(const TokenType &type, const void *literal) {
  TokenVoid::GetTokens()->push_back(
      std::make_unique<TokenVoid>(type, "RESERVED", literal, line));
}

// Overloading for Strings
void Scanner::AddToken(const TokenType &type,
                       std::unique_ptr<const std::string> literal) {
  std::string text = source.substr(start, current - start);
  TokenString::GetTokens()->push_back(std::make_unique<TokenString>(
      type, std::move(text), std::move(literal), line));
}

// // Overloading for Numbers
void Scanner::AddToken(const TokenType &type,
                       std::unique_ptr<const double> literal) {
  std::string text = source.substr(start, current - start);
  TokenDouble::GetTokens()->push_back(std::make_unique<TokenDouble>(
      type, std::move(text), std::move(literal), line));
}

void Scanner::AddToken(const TokenType &type) {
  AddToken(type, static_cast<void *>(nullptr));
}

void Scanner::String() {
  while (Peek() != '"' && !IsAtEnd()) {
    if (Peek() == '\n') {
      line++;
    }
    Advance();
  }

  if (IsAtEnd()) {
    Error::SendError(line, "Unterminated string.");
    return;
  }

  // The closing "
  Advance();

  // Trim the surrounding quotes
  auto value = std::make_unique<std::string>(source.substr(
      start + 1,
      current - start -
          2));  // TODO: Might need to fix the second parameter here
  AddToken(TokenType::STRING, std::move(value));
}

void Scanner::Number() {
  while (IsDigit(Peek())) {
    Advance();
  }

  // Look for the fractional part
  if (Peek() == '.' && IsDigit(PeekNext())) {
    // First consume the .
    Advance();

    while (IsDigit(Peek())) {
      Advance();
    }
  }
  auto number = std::make_unique<double>(
      std::stod(source.substr(start, current - start)));
  AddToken(TokenType::NUMBER, std::move(number));
}

void Scanner::Identifier() {
  while (IsAlphaNumeric(Peek())) {
    Advance();
  }

  std::string text = source.substr(start, current - start);
  auto it_type =
      std::find_if(keywords.begin(), keywords.end(),
                   [&](const auto &entry) { return entry.first == text; });
  if (it_type == keywords.end()) {
    TokenType type = TokenType::IDENTIFIER;
    AddToken(type);
    return;
  }

  AddToken((*it_type).second);
}

void Scanner::ScanToken() {
  char c = Advance();

  switch (c) {
    case '(':
      AddToken(TokenType::LEFT_PAREN);
      break;
    case ')':
      AddToken(TokenType::RIGHT_PAREN);
      break;
    case '{':
      AddToken(TokenType::LEFT_BRACE);
      break;
    case '}':
      AddToken(TokenType::RIGHT_BRACE);
      break;
    case ',':
      AddToken(TokenType::COMMA);
      break;
    case '.':
      AddToken(TokenType::DOT);
      break;
    case '-':
      AddToken(TokenType::MINUS);
      break;
    case '+':
      AddToken(TokenType::PLUS);
      break;
    case ';':
      AddToken(TokenType::SEMICOLON);
      break;
    case '*':
      AddToken(TokenType::STAR);
      break;
    case '!':
      AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
      break;
    case '=':
      AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
      break;
    case '<':
      AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
      break;
    case '>':
      AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
      break;
    case '/':
      if (Match('/')) {
        // A comment goes untill the end of the line
        while (Peek() != '\n' && !IsAtEnd()) {
          Advance();
        }
      } else {
        AddToken(TokenType::SLASH);
      }
      break;
    case ' ':
      [[fallthrough]];
    case '\r':
      [[fallthrough]];
    case '\t':
      // Ignore whitespace
      break;
    case '\n':
      line++;
      break;
    case '"':
      String();
      break;
    default:
      if (IsDigit(c)) {
        Number();
      } else if (IsAlpha(c)) {
        Identifier();
      } else {
        Error::SendError(line, "Unexpected character.");
      }
      break;
  }
}

void Scanner::ScanTokens() {
  while (!IsAtEnd()) {
    start = current;
    ScanToken();
  }

  AddToken(TokenType::TEOF);
  // Push scanner back at the beginning of line
  current = 0;
  start = 0;

  // There's probably a better way to clear it, but we don't
  // care about the type at the point of clearing.
  TokenVoid::ClearTokens();
}
