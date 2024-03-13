#include <gtest/gtest.h>

#include "Token.hpp"

namespace {

TEST(TOKEN_TESTS, Create_Token_from_inputs) {
  auto tok1 = Token(TokenType::VAR, "var", nullptr, 0);
  auto tok2 = Token(TokenType::IDENTIFIER, "car", nullptr, 0);
  auto tok3 = Token(TokenType::EQUAL, "=", nullptr, 0);
  auto tok4 = Token(TokenType::STRING, "car", new std::string("car"), 0);
  auto tok5 = Token(TokenType::SEMICOLON, ";", nullptr, 0);

  EXPECT_EQ("var", tok1.lexeme);
  EXPECT_EQ("car", tok2.lexeme);
  EXPECT_EQ("=", tok3.lexeme);
  EXPECT_EQ("car", tok4.lexeme);
  EXPECT_EQ(";", tok5.lexeme);
}

TEST(TOKEN_TESTS, Create_Token_move_constructor) {
  auto tok1 = Token(TokenType::VAR, "var", nullptr, 0);
  auto tok2 = Token(std::move(tok1));
  ASSERT_EQ("var", tok2.lexeme);
}

TEST(TOKEN_TESTS, Format_to_String) {
  auto tok1 = Token(TokenType::VAR, "var", nullptr, 0);
  auto tok2 = Token(TokenType::IDENTIFIER, "car", nullptr, 0);
  auto tok3 = Token(TokenType::EQUAL, "=", nullptr, 0);
  auto tok4 = Token(TokenType::STRING, "car", new std::string("car"), 0);
  auto tok5 = Token(TokenType::SEMICOLON, ";", nullptr, 0);

  EXPECT_EQ("VAR var", tok1.ToString());
  EXPECT_EQ("IDENTIFIER car", tok2.ToString());
  EXPECT_EQ("= =", tok3.ToString());
  EXPECT_EQ("STRING car car", tok4.ToString());
  EXPECT_EQ("; ;", tok5.ToString());
}

TEST(TOKEN_TESTS, Stream_operator) {
  auto tok1 = Token(TokenType::VAR, "var", nullptr, 0);
  auto tok2 = Token(TokenType::IDENTIFIER, "car", nullptr, 0);
  auto tok3 = Token(TokenType::EQUAL, "=", nullptr, 0);
  auto tok4 = Token(TokenType::STRING, "car", new std::string("car"), 0);
  auto tok5 = Token(TokenType::SEMICOLON, ";", nullptr, 0);

  std::stringstream ss;
  ss << tok1 << std::endl;
  ss << tok2 << std::endl;
  ss << tok3 << std::endl;
  ss << tok4 << std::endl;
  ss << tok5 << std::endl;
  EXPECT_EQ("VAR var\nIDENTIFIER car\n= =\nSTRING car car\n; ;\n", ss.str());
}

}  // namespace