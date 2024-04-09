#include "includes/Parser.hpp"

template <typename T, typename U>
Expr<T, U>* Parser<T, U>::Expression() {
    return Equality();
}

template <typename T, typename U>
Expr<T, U>* Parser<T, U>::Equality()
{
    Expr<T, U>* expr = Comparison();

    while (Match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL)) {
        Token<T>* oper = Previous();
        Expr<T, U>* right = Comparison();
        expr = std::make_unique<Binary<T, U>>(expr, oper, right);
    }

    return expr;
}