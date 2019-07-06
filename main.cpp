#include <iostream>
#include <string>
#include "result.h"

using namespace davinci;

struct My_test {
  My_test() : value(0) { std::cout << "My_test ctor\n"; }
  My_test(const My_test& rhs) : value(rhs.value)
  {
    std::cout << "My_test copy ctor\n";
  }
  My_test(My_test&& rhs) noexcept : value(rhs.value)
  {
    std::cout << "My_test move ctor\n";
  }

  int value = -1;
};

auto get_my_test() -> My_test { return My_test{}; }

auto may_get_err() -> Result<void, int> { return Ok<void>{}; }

auto may_get_err(int value) -> Result<int, std::string>
{
  if (value < 0) {
    return Err(std::string{"Input is less then 0"});
  }
  else {
    return Ok(value * value);
  }
}

int main()
{
  std::cout << ".1\n";
  My_test m1 = get_my_test();
  std::cout << ".2\n";
  std::variant<My_test, int> var1 = My_test{};
  std::cout << ".3\n";
  std::variant<My_test, int> var2 = 101;
  {
    std::cout << ".4\n";
    Ok<My_test> my_test = My_test{};
  }
  {
    std::cout << ".5\n";
    Ok<void> my_test;
  }
  {
    std::cout << ".6\n";
    Result<My_test, int> res = My_test{};
  }
  {
    std::cout << ".7\n";
    Result<My_test, int> res = Ok(My_test{});
    match_result(res, /************/
                 [](Ok<My_test> value) { std::cout << "value!\n"; },
                 [](Err<int> err) { std::cout << "err!\n"; });
  }
  {
    std::cout << ".8\n";
    Result<My_test, int> res = Ok(My_test{});
    match_result(res, /************/
                 [](const Ok<My_test>& value) { std::cout << "value!\n"; },
                 [](const Err<int>& err) { std::cout << "err!\n"; });
  }
  {
    std::cout << ".9\n";
    auto res = may_get_err();
  }
  {
    std::cout << ".10\n";
    match_result(may_get_err() /*******/,
                 [](Ok<void> value) { std::cout << "value!\n"; },
                 [](const Err<int>& err) { std::cout << "err!\n"; });
  }
  {
    std::cout << ".11\n";
    match_result(may_get_err(20) /*******/,
                 [](const Ok<int>& value) {
                   std::cout << "value: " << value.value << "\n";
                 },
                 [](const Err<std::string>& err) {
                   std::cout << "err: " << err.value << "\n";
                 });
  }
  {
    std::cout << ".12\n";
    match_result(may_get_err(-20),
                 [](const Ok<int>& value) {
                   std::cout << "value: " << value.value << "\n";
                 },
                 [](const Err<std::string>& err) {
                   std::cout << "err: " << err.value << "\n";
                 });
  }

  std::cout << "Error handling demo.\n";

  return 0;
}