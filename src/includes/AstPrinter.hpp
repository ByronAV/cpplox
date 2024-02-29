#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "Expr.hpp"

#include <sstream>
#include <iostream>

template<typename T, typename U>
class AstPrinter: public Expr<T, U>::Visitor {
public:
    [[gnu::always_inline]] void Print(const Expr<T, U>& expr) const {
        std::cout << expr.Accept(*this) << std::endl;
    }

private:

    template<typename K, typename = void>
    struct has_accept : std::false_type {};

    template<typename K>
    struct has_accept<K, std::void_t<decltype(std::declval<K>().Accept(std::declval<typename Expr<T, U>::Visitor>()))>> : std::true_type {};

    template<typename K>
    [[gnu::always_inline]] void Parenthesize(std::stringstream& ss, K&& expr) const
    {
        if constexpr (has_accept<K>::value) {
            ss << " " << expr.Accept(*this);
        } else if constexpr (std::is_same_v<K, Token<U>>) {
            ss << " " << expr.GetName()->lexeme;
        } else if constexpr (std::is_same_v<K, PtrVecExpr<T, U>>){
            for (auto&& arg: expr) {
                ss << " " << *arg.Accept(*this);
            }
        } else if constexpr (std::is_same_v<K, std::string>) {
            ss << " " << expr;
        }
    }

    template<typename... Args>
    [[gnu::always_inline]] std::string Parenthesize(const std::string& name, Args&&... exprs) const
    {
        std::stringstream ss;
        ss << "(" << name;
        (Parenthesize(ss, std::forward<Args>(exprs)), ...);
        ss << ")";
        return ss.str();
    }

    [[gnu::always_inline]] std::string VisitAssignExpr(const Assign<T, U>& expr) const override {
        return Parenthesize("=", expr.GetName()->lexeme, *expr.GetValue());
    }

    [[gnu::always_inline]] std::string VisitBinaryExpr(const Binary<T, U>& expr) const override {
        return Parenthesize(expr.GetOperator()->lexeme, *expr.GetLeft(), *expr.GetRight());
    }

    [[gnu::always_inline]] std::string VisitCallExpr(const Call<T, U>& expr) const override {
        return Parenthesize("call", *expr.GetCallee(), *expr.GetArgs());
    }

    [[gnu::always_inline]] std::string VisitGetExpr(const Get<T, U>& expr) const override {
        return Parenthesize(".", *expr.GetObject(), *expr.GetName());
    }

    [[gnu::always_inline]] std::string VisitGroupingExpr(const Grouping<T, U>& expr) const override {
        return Parenthesize("group", *expr.GetExpr());
    }

    [[gnu::always_inline]] std::string VisitLiteralExpr(const Literal<T, U>& expr) const override {
        return std::string(*expr.GetValue());
    }

    [[gnu::always_inline]] std::string VisitLogicalExpr(const Logical<T, U>& expr) const override {
        return Parenthesize(expr.GetOperator()->lexeme, *expr.GetLeft(), *expr.GetRight());
    }

    [[gnu::always_inline]] std::string VisitSetExpr(const Set<T, U>& expr) const override {
        return Parenthesize("=", *expr.GetObject(), expr.GetName()->lexeme, *expr.GetValue());
    }

    [[gnu::always_inline]] std::string VisitSuperExpr(const Super<T, U>& expr) const override {
        return Parenthesize("super", *expr.GetMethod());
    }

    [[gnu::always_inline]] std::string VisitThisExpr([[maybe_unused]] const This<T, U>& expr) const override {
        return "this";
    }

    [[gnu::always_inline]] std::string VisitUnaryExpr(const Unary<T, U>& expr) const override {
        return Parenthesize(expr.GetOperator()->lexeme, *expr.GetRight());
    }

    [[gnu::always_inline]] std::string VisitVariableExpr(const Variable<T, U>& expr) const override {
        return expr.GetName()->lexeme;
    }
};

#endif