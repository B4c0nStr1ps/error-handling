#include <iostream>
#include <string>
#include "result.h"

/*
 * When a function needs to return a value or an error you can use the
 * bs::Result<T, E> type. Interally Result<T, E> use as storage a
 * std::variant<Ok<T>, Err<E>>. Ok<T> and Err<E> are two wrapper objects used to
 * mock rust Ok, Err syntax and to simpy handle the case for Ok<void>. The usage
 * of this two wrapper has the cost of one additional move constructor call.
 * To check if Result has a value T or an error E you can use methods is_ok() or
 * is_err(). Result also implements explicit bool operator() that works as a
 * is_ok() call. To get the value if available use the unwrap() function. If
 * called when Result is an error it will assert and terminate the program.
 * Use unwrap_or(T default_value) to get the value or in case Result is an error
 * to get default_value.
 * Use unwrap_err() to ghe the error. If Result is a valid value will assert and
 * terminate the program.
 * Is also possible to use the match_result function to imitate the pattern
 * matching syntax available in rust.
 */

auto divide(int a, int b) -> bs::Result<int, std::string>
{
  if (b == 0) {
    return bs::Err(std::string("Division by 0 is not defined."));
  }
  else {
    return bs::Ok((a / b));
  }
}

int main()
{
  std::cout << "Error handling demo.\n";

  // Valid division operation.
  {
    auto res = divide(8, 4);
    assert(res.is_ok() == true);
  }
  // Invalid division by 0.
  {
    auto res = divide(8, 0);
    assert(res.is_err() == true);
  }
  // Unwrap value.
  {
    auto res = divide(8, 4);
    int value = res.unwrap();
    assert(value == 2);
  }
  // Unwrap error.
  {
    auto res = divide(8, 0);
    std::string error_message = res.unwrap_err();
  }
  // Unwrap_or invalid result.
  {
    auto res = divide(8, 0);
    int value = res.unwrap_or(-1);
    assert(value == -1);
  }
  // Pattern match a valid result.
  {
    auto res = divide(8, 4);
    bs::match_result(res /***PADDING***/,
                     [](const bs::Ok<int>& val) {
                       std::cout << "result = " << val.value << "\n";
                     },
                     [](const bs::Err<std::string>& err) {
                       std::cout << "Division error: " << err.value << "\n";
                     });
  }
  // Pattern match an invalid result.
  {
    auto res = divide(8, 0);
    bs::match_result(res /***PADDING***/,
                     [](const bs::Ok<int>& val) {
                       std::cout << "result = " << val.value << "\n";
                     },
                     [](const bs::Err<std::string>& err) {
                       std::cout << "Division error: " << err.value << "\n";
                     });
  }

  return 0;
}