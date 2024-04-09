#ifndef PARSER_HPP
#define PARSER_HPP

#include "Token.hpp"
#include "Expr.hpp"

template <typename T, typename U>
class Parser {
public:

private:

    [[gnu::always_inline]] bool Match(TokenType&& type) {
        if (Check(type)) {
            Advance();
            return true;
        }
    }

    template <typename... Args>
    [[gnu::always_inline]] bool Match(Args&&... token_types) {
        return (Match(std::forward<Args>(token_types)), ...) || false;
    }

    [[gnu::always_inline]] bool Check(TokenType type) {
        if (IsAtEnd()) return false;
        return Peek()->type == type;
    }

    [[gnu::always_inline]] Token<T>* Advance() {
        if (!IsAtEnd()) current++;
        return Previous();
    }


    [[gnu::always_inline]] bool IsAtEnd() {
        return Peek()->type == TokenType::TEOF;
    }

    [[gnu::always_inline]] Token<T>* Peek() {
        return Token<T>::GetTokens()->at(current);
    }

    [[gnu::always_inline]] Token<T>* Previous() {
        return Token<T>::GetTokens()->at(current - 1);
    }

    Expr<T, U>* Expression();
    Expr<T, U>* Equality();
    inline static int current = 0;
};

#endif