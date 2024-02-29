#include "Expr.hpp"

// ------------- ASSIGN CLASS -------------
template<typename T, typename U>
Assign<T, U>::Assign(Token<U>& name, Expr<T, U>& value) noexcept
: _value(value.Clone()),
  _name(std::make_unique<Token<U>>(name)) {}


template<typename T, typename U>
Assign<T, U>::Assign(Assign&& other) noexcept : _value(std::move(other._value)), _name(std::move(other._name)) {}

// ------------- BINARY CLASS -------------
template<typename T, typename U>
Binary<T, U>::Binary(Expr<T, U>& left, Token<U>& oper, Expr<T, U>& right) noexcept
 : _left(left.Clone()),
   _operator(std::make_unique<Token<U>>(oper)),
   _right(right.Clone()) {}

template<typename T, typename U>
Binary<T, U>::Binary(Binary&& other) noexcept : _left(std::move(other._left)), _operator(std::move(other._operator)), _right(std::move(other._right)) {}


// ------------- CALL CLASS -------------
template<typename T, typename U>
Call<T, U>::Call(Expr<T, U>& callee, Token<U>& paren, PtrVecExpr<T, U>& arguments) noexcept
  : _callee(callee.Clone()),
    _paren(std::make_unique<Token<U>>(paren)) {
      _arguments = std::make_unique<PtrVecExpr<T, U>>();
      for(auto&& arg: arguments) {
        _arguments->push_back(arg->Clone());
      }
    }

template<typename T, typename U>
Call<T, U>::Call(Call&& other) noexcept : _callee(std::move(other._callee)), _paren(std::move(other._paren)), _arguments(std::move(other._arguments)) {}


// ------------- GET CLASS -------------
template<typename T, typename U>
Get<T, U>::Get(Expr<T, U>& object, Token<U>& name) noexcept
  : _object(object.Clone()),
    _name(std::make_unique<Token<U>>(name)) {}

template<typename T, typename U>
Get<T, U>::Get(Get&& other) noexcept : _object(std::move(other._object)), _name(std::move(other._name)) {}


// ------------- GROUPING CLASS -------------
template<typename T, typename U>
Grouping<T, U>::Grouping(Expr<T, U>& expression) noexcept
  : _expression(expression.Clone()) {}

template<typename T, typename U>
Grouping<T, U>::Grouping(Grouping&& other) noexcept : _expression(std::move(other._expression)) {}


// ------------- LITERAL CLASS -------------
template<typename T, typename U>
Literal<T, U>::Literal(T& value, size_t size) noexcept
  : _value(std::make_unique<T>(value)), _size(size) {}

template<typename T, typename U>
Literal<T, U>::Literal(Literal&& other) noexcept : _value(std::move(other._value)), _size(std::move(other._size)) {}


// ------------- LOGICAL CLASS -------------
template<typename T, typename U>
Logical<T, U>::Logical(Expr<T, U>& left, Token<U>& oper, Expr<T, U>& right) noexcept
 : _left(std::move(left)),
   _operator(std::move(oper)),
   _right(std::move(right)) {}

template<typename T, typename U>
Logical<T, U>::Logical(Logical&& other) noexcept : _left(other._left), _operator(std::move(other._operator)), _right(std::move(other._right)) {}
  
// ------------- SET CLASS -------------
template<typename T, typename U>
Set<T, U>::Set(Expr<T, U>& object, Token<U>& name, Expr<T, U>& value) noexcept
  : _object(std::move(object)),
    _name(std::move(name)),
    _value(std::move(value)) {}

template<typename T, typename U>
Set<T, U>::Set(Set&& other) noexcept : _object(std::move(other._object)), _name(std::move(other._name)), _value(std::move(other._value)) {}


// ------------- SUPER CLASS -------------
template<typename T, typename U>
Super<T, U>::Super(Token<U>& keyword, Token<U>& method) noexcept
  : _keyword(std::move(keyword)),
    _method(std::move(method)) {}

template<typename T, typename U>
Super<T, U>::Super(Super&& other) noexcept : _keyword(std::move(other._keyword)), _method(std::move(other._method)) {}


// ------------- THIS CLASS -------------
template<typename T, typename U>
This<T, U>::This(Token<U>& keyword) noexcept
  : _keyword(std::move(keyword)) {}

template<typename T, typename U>
This<T, U>::This(This&& other) noexcept : _keyword(std::move(other._keyword)) {}



// ------------- UNARY CLASS -------------
template<typename T, typename U>
Unary<T, U>::Unary(Token<U>& oper, Expr<T, U>& right) noexcept
  : _operator(std::make_unique<Token<U>>(oper)),
    _right(right.Clone()) {}

template<typename T, typename U>
Unary<T, U>::Unary(Unary&& other) noexcept : _operator(std::move(other._operator)), _right(std::move(other._right)) {}


// ------------- VARIABLE CLASS -------------
template<typename T, typename U>
Variable<T, U>::Variable(Token<U>& name) noexcept
  : _name(std::move(name)) {}


template<typename T, typename U>
Variable<T, U>::Variable(Variable&& other) noexcept : _name(std::move(other._name)) {}