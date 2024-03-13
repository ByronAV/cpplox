#ifndef EXPR_HPP
#define EXPR_HPP

#include "Token.hpp"

// Forward Declarations
template <typename T, typename U>
class Assign;
template <typename T, typename U>
class Binary;
template <typename T, typename U>
class Call;
template <typename T, typename U>
class Get;
template <typename T, typename U>
class Grouping;
template <typename T, typename U>
class Literal;
template <typename T, typename U>
class Logical;
template <typename T, typename U>
class Set;
template <typename T, typename U>
class Super;
template <typename T, typename U>
class This;
template <typename T, typename U>
class Unary;
template <typename T, typename U>
class Variable;

// ------------- EXPR CLASS -------------
template <typename T, typename U>
class Expr {
 public:
  class Visitor {
   public:
    virtual T VisitAssignExpr(const Assign<T, U>& expr) const = 0;
    virtual T VisitBinaryExpr(const Binary<T, U>& expr) const = 0;
    virtual T VisitCallExpr(const Call<T, U>& expr) const = 0;
    virtual T VisitGetExpr(const Get<T, U>& expr) const = 0;
    virtual T VisitGroupingExpr(const Grouping<T, U>& expr) const = 0;
    virtual T VisitLiteralExpr(const Literal<T, U>& expr) const = 0;
    virtual T VisitLogicalExpr(const Logical<T, U>& expr) const = 0;
    virtual T VisitSetExpr(const Set<T, U>& expr) const = 0;
    virtual T VisitSuperExpr(const Super<T, U>& expr) const = 0;
    virtual T VisitThisExpr(const This<T, U>& expr) const = 0;
    virtual T VisitUnaryExpr(const Unary<T, U>& expr) const = 0;
    virtual T VisitVariableExpr(const Variable<T, U>& expr) const = 0;
  };

  virtual ~Expr() = default;
  virtual std::unique_ptr<Expr> Clone() = 0;
  virtual T Accept(const Visitor& visitor) const = 0;
};

template <typename T, typename U>
using PtrVecExpr = std::vector<std::unique_ptr<Expr<T, U>>>;

// ------------- ASSIGN CLASS -------------
template <typename T, typename U>
class Assign : virtual public Expr<T, U> {
 public:
  Assign(Token<U>& name, Expr<T, U>& value) noexcept;
  Assign(Assign&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitAssignExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Assign<T, U>>(*_value, *_name);
  }

  [[gnu::always_inline]] const Token<U>* GetName() const { return _name.get(); }

  [[gnu::always_inline]] const Expr<T, U>* GetValue() const {
    return _value.get();
  }

 private:
  std::unique_ptr<Expr<T, U>> _value;
  std::unique_ptr<Token<U>> _name;
};

// ------------- BINARY CLASS -------------
template <typename T, typename U>
class Binary : virtual public Expr<T, U> {
 public:
  Binary(Expr<T, U>& left, Token<U>& oper, Expr<T, U>& right) noexcept;
  Binary(Binary&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitBinaryExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Binary<T, U>>(*_left, *_operator, *_right);
  }

  [[gnu::always_inline]] const Token<U>* GetOperator() const {
    return _operator.get();
  }

  [[gnu::always_inline]] const Expr<T, U>* GetLeft() const {
    return _left.get();
  }

  [[gnu::always_inline]] const Expr<T, U>* GetRight() const {
    return _right.get();
  }

 private:
  std::unique_ptr<Expr<T, U>> _left;
  std::unique_ptr<Token<U>> _operator;
  std::unique_ptr<Expr<T, U>> _right;
};

// ------------- CALL CLASS -------------
template <typename T, typename U>
class Call : public Expr<T, U> {
 public:
  Call(Expr<T, U>& callee, Token<U>& paren,
       PtrVecExpr<T, U>& arguments) noexcept;
  Call(Call&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitCallExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Call<T, U>>(*_callee, *_paren, *_arguments);
  }

  [[gnu::always_inline]] const Expr<T, U>* GetCallee() const {
    return _callee.get();
  }

  [[gnu::always_inline]] const Token<U>* GetParen() const {
    return _paren.get();
  }

  [[gnu::always_inline]] const PtrVecExpr<T, U>* GetArgs() const {
    return _arguments.get();
  }

 private:
  std::unique_ptr<Expr<T, U>> _callee;
  std::unique_ptr<Token<U>> _paren;
  std::unique_ptr<PtrVecExpr<T, U>> _arguments;
};

// ------------- GET CLASS -------------
template <typename T, typename U>
class Get : public Expr<T, U> {
 public:
  Get(Expr<T, U>& object, Token<U>& name) noexcept;
  Get(Get&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitGetExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Get<T, U>>(*_object, *_name);
  }

  [[gnu::always_inline]] const Expr<T, U>* GetObject() const {
    return _object.get();
  }

  [[gnu::always_inline]] const Token<U>* GetName() const { return _name.get(); }

 private:
  std::unique_ptr<Expr<T, U>> _object;
  std::unique_ptr<Token<U>> _name;
};

// ------------- GROUPING CLASS -------------
template <typename T, typename U>
class Grouping : public Expr<T, U> {
 public:
  Grouping(Expr<T, U>& expression) noexcept;
  Grouping(Grouping&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitGroupingExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Grouping<T, U>>(*_expression);
  }

  [[gnu::always_inline]] const Expr<T, U>* GetExpr() const {
    return _expression.get();
  }

 private:
  std::unique_ptr<Expr<T, U>> _expression;
};

// ------------- LITERAL CLASS -------------
template <typename T, typename U>
class Literal : public Expr<T, U> {
 public:
  Literal(T& value, size_t size) noexcept;
  Literal(Literal&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitLiteralExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Literal<T, U>>(*_value, _size);
  }

  [[gnu::always_inline]] T* GetValue() const { return _value.get(); }

  [[gnu::always_inline]] size_t GetSize() const { return _size; }

 private:
  std::unique_ptr<T> _value;
  size_t _size;
};

// ------------- LOGICAL CLASS -------------
template <typename T, typename U>
class Logical : public Expr<T, U> {
 public:
  Logical(Expr<T, U>& left, Token<U>& oper, Expr<T, U>& right) noexcept;
  Logical(Logical&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitLogicalExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Logical<T, U>>(*_left, *_operator, *_right);
  }

  [[gnu::always_inline]] const Expr<T, U>* GetLeft() const {
    return _left.get();
  }

  [[gnu::always_inline]] const Token<U>* GetOperator() const {
    return _operator.get();
  }

  [[gnu::always_inline]] const Expr<T, U>* GetRight() const {
    return _right.get();
  }

 private:
  std::unique_ptr<Expr<T, U>> _left;
  std::unique_ptr<Token<U>> _operator;
  std::unique_ptr<Expr<T, U>> _right;
};

// ------------- SET CLASS -------------
template <typename T, typename U>
class Set : public Expr<T, U> {
 public:
  Set(Expr<T, U>& object, Token<U>& name, Expr<T, U>& value) noexcept;
  Set(Set&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitSetExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Set<T, U>>(std::move(*this));
  }

  [[gnu::always_inline]] const Expr<T, U>* GetObject() const {
    return _object.get();
  }

  [[gnu::always_inline]] const Token<U>* GetName() const { return _name.get(); }

  [[gnu::always_inline]] const Expr<T, U>* GetValue() const {
    return _value.get();
  }

 private:
  std::unique_ptr<Expr<T, U>> _object;
  std::unique_ptr<Token<U>> _name;
  std::unique_ptr<Expr<T, U>> _value;
};

// ------------- SUPER CLASS -------------
template <typename T, typename U>
class Super : public Expr<T, U> {
 public:
  Super(Token<U>& keyword, Token<U>& method) noexcept;
  Super(Super&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitSuperExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Super<T, U>>(std::move(*this));
  }

  [[gnu::always_inline]] const Token<U>* GetKeyword() const {
    return _keyword.get();
  }

  [[gnu::always_inline]] const Token<U>* GetMethod() const {
    return _method.get();
  }

 private:
  std::unique_ptr<Token<U>> _keyword;
  std::unique_ptr<Token<U>> _method;
};

// ------------- THIS CLASS -------------
template <typename T, typename U>
class This : public Expr<T, U> {
 public:
  This(Token<U>& keyword) noexcept;
  This(This&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitThisExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<This<T, U>>(std::move(*this));
  }

  [[gnu::always_inline]] const Token<U>* GetKeyword() const {
    return _keyword.get();
  }

 private:
  std::unique_ptr<Token<U>> _keyword;
};

// ------------- UNARY CLASS -------------
template <typename T, typename U>
class Unary : public Expr<T, U> {
 public:
  Unary(Token<U>& oper, Expr<T, U>& right) noexcept;
  Unary(Unary&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitUnaryExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Unary<T, U>>(std::move(*this));
  }

  [[gnu::always_inline]] const Token<U>* GetOperator() const {
    return _operator.get();
  }

  [[gnu::always_inline]] const Expr<T, U>* GetRight() const {
    return _right.get();
  }

 private:
  std::unique_ptr<const Token<U>> _operator;
  std::unique_ptr<const Expr<T, U>> _right;
};

// ------------- VARIABLE CLASS -------------
template <typename T, typename U>
class Variable : public Expr<T, U> {
 public:
  Variable(Token<U>& name) noexcept;
  Variable(Variable&& other) noexcept;

  [[gnu::always_inline]] T Accept(
      const typename Expr<T, U>::Visitor& visitor) const override {
    return visitor.VisitVariableExpr(*this);
  }

  [[gnu::always_inline]] std::unique_ptr<Expr<T, U>> Clone() override {
    return std::make_unique<Variable<T, U>>(std::move(*this));
  }

  [[gnu::always_inline]] const Token<U>* GetName() const { return _name.get(); }

 private:
  std::unique_ptr<Token<U>> _name;
};

#endif