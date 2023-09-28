#include "includes/Token.hpp"

Token::Token(const TokenType& in_type, const std::string& in_lexeme, const void* in_literal, unsigned int in_line): 
    type(in_type),
    lexeme(in_lexeme),
    literal(in_literal),
    line(in_line) {}