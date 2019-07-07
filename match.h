#pragma once
#include "overload.h"
#include <variant>

namespace bs {

template <typename... TVariants>
constexpr auto match(TVariants&&... vs)
{
  return [&](auto&&... fs) -> decltype(auto) {
    auto visitor = overload(std::forward<decltype(fs)>(fs)...);
    return std::visit(visitor, std::forward<TVariants>(vs)...);
  };
}

}  // namespace davinci
