#pragma once
#include "Token.hpp"

// Forward Declarations
template<typename T, typename U>
class Assign;
template<typename T, typename U>
class Binary;
template<typename T, typename U>
class Call;
template<typename T, typename U>
class Get;
template<typename T, typename U>
class Grouping;
template<typename T, typename U>
class Literal;
template<typename T, typename U>
class Logical;
template<typename T, typename U>
class Set;
template<typename T, typename U>
class Super;
template<typename T, typename U>
class This;
template<typename T, typename U>
class Unary;
template<typename T, typename U>
class Variable;

// ------------- EXPR CLASS -------------
template<typename T, typename U>
class Expr {
public:
  class Visitor {
    T VisitAssignExpr(const Assign<T, U>& expr) = 0;
    T VisitBinaryExpr(const Binary<T, U>& expr) = 0;
    T VisitCallExpr(const Call<T, U>& expr) = 0;
    T VisitGetExpr(const Get<T, U>& expr) = 0;
    T VisitGroupingExpr(const Grouping<T, U>& expr) = 0;
    T VisitLiteralExpr(const Literal<T, U>& expr) = 0;
    T VisitLogicalExpr(const Logical<T, U>& expr) = 0;
    T VisitSetExpr(const Set<T, U>& expr) = 0;
    T VisitSuperExpr(const Super<T, U>& expr) = 0;
    T VisitThisExpr(const This<T, U>& expr) = 0;
    T VisitVariableExpr(const Variable<T, U>& expr) = 0;
  };

  T Accept(const Visitor& visitor) = 0; 
};

template<typename T, typename U>
using ConstRefVecExpr = std::vector<const std::reference_wrapper<Expr<T, U>>>;


// ------------- ASSIGN CLASS -------------
template<typename T, typename U>
class Assign: public Expr<T, U> {
public:
  Assign(const Token<U>& name, const Expr<T, U>& value);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitAssignExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _value;
  std::unique_ptr<const Token<U>> _name;
};

// ------------- BINARY CLASS -------------
template<typename T, typename U>
class Binary : public Expr<T, U> {
public:
  Binary(const Expr<T, U>& left, const Token<U>& oper, const Expr<T, U>& right);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitBinaryExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _left;
  std::unique_ptr<const Token<U>> _operator;
  std::unique_ptr<const Expr<T, U>> _right;
};

// ------------- CALL CLASS -------------
template<typename T, typename U>
class Call: public Expr<T, U> {
public:
  Call(const Expr<T, U>& callee, const Token<U>& paren, ConstRefVecExpr<T, U>& arguments);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitCallExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _callee;
  std::unique_ptr<const Token<U>> _paren;
  std::unique_ptr<ConstRefVecExpr<T, U>> _arguments;
};

// ------------- GET CLASS -------------
template<typename T, typename U>
class Get: public Expr<T, U> {
public:
  Get(const Expr<T, U>& object, const Token<U>& name);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitGetExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _object;
  std::unique_ptr<const Token<U>> _name;
};

// ------------- GROUPING CLASS -------------
template<typename T, typename U>
class Grouping: public Expr<T, U> {
public:
  Grouping(const Expr<T, U>& expression);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitGroupingExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _expression;
};

// ------------- LITERAL CLASS -------------
template<typename T, typename U>
class Literal: public Expr<T, U> {
public:
  Literal(const void* object);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitLiteralExpr(this);
  }

private:
  std::unique_ptr<const void*> _object;
};

// ------------- LOGICAL CLASS -------------
template<typename T, typename U>
class Logical : public Expr<T, U> {
public:
  Logical(const Expr<T, U>& left, const Token<U>& oper, const Expr<T, U>& right);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitLogicalExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _left;
  std::unique_ptr<const Token<U>> _operator;
  std::unique_ptr<const Expr<T, U>> _right;
};

// ------------- SET CLASS -------------
template<typename T, typename U>
class Set: public Expr<T, U> {
public:
  Set(const Expr<T, U>& object, const Token<U>& name, const Expr<T, U>& value);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitSetExpr(this);
  }

private:
  std::unique_ptr<const Expr<T, U>> _object;
  std::unique_ptr<const Token<U>> _name;
  std::unique_ptr<const Expr<T, U>> _value;
};

// ------------- SUPER CLASS -------------
template<typename T, typename U>
class Super: public Expr<T, U> {
public:
  Super(const Token<U>& keyword, const Token<U>& method);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitSuperExpr(this);
  }

private:
  std::unique_ptr<const Token<U>> _keyword;
  std::unique_ptr<const Token<U>> _method;
};

// ------------- THIS CLASS -------------
template<typename T, typename U>
class This: public Expr<T, U> {
public:
  This(const Token<U>& keyword);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitThisExpr(this);
  }

private:
  std::unique_ptr<const Token<U>> _keyword;
};

// ------------- UNARY CLASS -------------
template<typename T, typename U>
class Unary: public Expr<T, U> {
public:
  Unary(const Token<U>& oper, const Expr<T, U>& right);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitUnaryExpr(this);
  }

private:
  std::unique_ptr<const Token<U>> _operator;
  std::unique_ptr<const Expr<T, U>> _right;
};

// ------------- VARIABLE CLASS -------------
template<typename T, typename U>
class Variable: public Expr<T, U> {
public:
  Variable(const Token<U>& name);

  inline T Accept(const typename Expr<T, U>::Visitor& visitor) override {
    return visitor.VisitVariableExpr(this);
  }

private:
  std::unique_ptr<const Token<U>> _name;
};