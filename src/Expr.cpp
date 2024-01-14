#include "Expr.hpp"

// ------------- ASSIGN CLASS -------------
template<typename T, typename U>
Assign<T, U>::Assign(const Token<U>& name, const Expr<T, U>& value)
: _value(std::make_unique<const Expr<T, U>>(value)),
  _name(std::make_unique<const Token<U>>(name)) {}


// ------------- BINARY CLASS -------------
template<typename T, typename U>
Binary<T, U>::Binary(const Expr<T, U>& left, const Token<U>& oper, const Expr<T, U>& right)
 : _left(std::make_unique<const Expr<T, U>>(left)),
   _operator(std::make_unique<const Token<U>>(oper)),
   _right(std::make_unique<const Expr<T, U>>(right)) {}


// ------------- CALL CLASS -------------
template<typename T, typename U>
Call<T, U>::Call(const Expr<T, U>& callee, const Token<U>& paren, ConstRefVecExpr<T, U>& arguments)
  : _callee(std::make_unique<const Expr<T, U>>(callee)),
    _paren(std::make_unique<const Token<U>>(paren)),
    _arguments(std::make_unique<ConstRefVecExpr<T, U>>(arguments)) {}


// ------------- GET CLASS -------------
template<typename T, typename U>
Get<T, U>::Get(const Expr<T, U>& object, const Token<U>& name)
  : _object(std::make_unique<const Expr<T, U>>(object)),
    _name(std::make_unique<const Token<U>>(name)) {}


// ------------- GROUPING CLASS -------------
template<typename T, typename U>
Grouping<T, U>::Grouping(const Expr<T, U>& expression)
  : _expression(std::make_unique<const Expr<T, U>>(expression)) {}


// ------------- LITERAL CLASS -------------
template<typename T, typename U>
Literal<T, U>::Literal(const void* object)
  : _object(std::make_unique<const void>(object)) {}


// ------------- LOGICAL CLASS -------------
template<typename T, typename U>
Logical<T, U>::Logical(const Expr<T, U>& left, const Token<U>& oper, const Expr<T, U>& right)
 : _left(std::make_unique<const Expr<T, U>>(left)),
   _operator(std::make_unique<const Token<U>>(oper)),
   _right(std::make_unique<const Expr<T, U>>(right)) {}

  
// ------------- SET CLASS -------------
template<typename T, typename U>
Set<T, U>::Set(const Expr<T, U>& object, const Token<U>& name, const Expr<T, U>& value)
  : _object(std::make_unique<const Expr<T, U>>(object)),
    _name(std::make_unique<const Token<U>>(name)),
    _value(std::make_unique<const Expr<T, U>>(value)) {}


// ------------- SUPER CLASS -------------
template<typename T, typename U>
Super<T, U>::Super(const Token<U>& keyword, const Token<U>& method)
  : _keyword(std::make_unique<const Token<U>>(keyword)),
    _method(std::make_unique<const Expr<T, U>>(method)) {}


// ------------- THIS CLASS -------------
template<typename T, typename U>
This<T, U>::This(const Token<U>& keyword)
  : _keyword(std::make_unique<const Token<U>>(keyword)) {}


// ------------- UNARY CLASS -------------
template<typename T, typename U>
Unary<T, U>::Unary(const Token<U>& oper, const Expr<T, U>& right)
  : _operator(std::make_unique<Token<U>>(oper)),
    _right(std::make_unique<const Token<U>>(right)) {}


// ------------- VARIABLE CLASS -------------
template<typename T, typename U>
Variable<T, U>::Variable(const Token<U>& name)
  : _name(std::make_unique<const Token<U>>(name)) {}