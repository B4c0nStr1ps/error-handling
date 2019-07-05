#include <intrin.h>
#include <iostream>

#ifdef _DEBUG
// define some inline assembly that causes a break
// into the debugger -- this will be different on each
// target CPU
#define debug_break() \
  {                   \
    __debugbreak();   \
  }
#else
// define some inline assembly that causes a break
// into the debugger -- this will be different on each
// target CPU
#define debug_break() \
  {                   \
  }
#endif  // DEBUG

#define _do_panic(msg)                                               \
  {                                                                  \
    debug_break();                                                   \
    std::cerr << msg << ", " << __FILE__ << " " << __LINE__ << "\n"; \
    std::terminate();                                                \
  }

#define panic()                                    \
  {                                                \
    _do_panic("app terminated at explicit panic"); \
  }

// dv_assert are always enabled also in optimized release build. Use
// dv_debug_asssert for debug only assertions.
#define dv_assert(expr)                                \
  {                                                    \
    if (!(expr)) {                                     \
      _do_panic("app terminated at assertion failed"); \
    }                                                  \
  }

#ifdef _DEBUG
// dv_debug_asssert assertion is only enabled in non optimized debug build.
#define dv_debug_asssert(expr) \
  {                            \
    dv_assert(expr);           \
  }
#else
// dv_debug_asssert assertion is only enabled in non optimized debug build.
#define dv_debug_asssert(expr) \
  {                            \
  }
#endif

#include "types.h"
#include "match.h"
#include <variant>

namespace davinci {

template <typename T>
struct Ok {
  Ok() = delete;
  Ok(const T& rhs) : value(rhs) { }
  Ok(T&& rhs) : value(std::move(rhs)) {}

  T value;
};

template <>
struct Ok<void> {
};

template <typename E>
struct Err {
  Err() = delete;
  Err(const E& rhs) : value(rhs) {}
  Err(E&& rhs) : value(std::move(rhs)) {}

  E value;
};

template <typename T, typename E>
class Result {
 public:
  using ok_type = Ok<T>;
  using err_type = Err<E>;

  Result() = delete;
  Result(ok_type ok_value) : is_ok_(true), res_(std::move(ok_value)) {}
  Result(err_type err_value) : is_ok_(true), res_(std::move(err_value))
  {
  }

   template <typename... TFs>
  auto do_match(TFs&&... funcs) -> void
  {
    match(res_)(std::forward<TFs>(funcs)...);
  }

 private:
  bool is_ok_;
  std::variant<ok_type, err_type> res_;
};

template <typename Result, typename... TFs>
auto match_result(Result&& result, TFs&&... funcs) -> void
{
  result.do_match(std::forward<TFs>(funcs)...);
}

}  // namespace davinci