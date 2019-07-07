#pragma once

namespace bs {

template <typename TF, typename... TFs>
struct overload_set : TF, overload_set<TFs...> {
  using TF::operator();
  using overload_set<TFs...>::operator();

  template <typename TFFwd, typename... TRest>
  overload_set(TFFwd&& f, TRest&&... rest)
      : TF{std::forward<TFFwd>(f)},
        overload_set<TFs...>{std::forward<TRest>(rest)...}
  {
  }
};

template <typename TF>
struct overload_set<TF> : TF {
  using TF::operator();
  template <typename TFFwd>
  overload_set(TFFwd&& f) : TF{std::move(f)}
  {
  }
};

template <typename... TFs>
auto overload(TFs&&... fs)
{
  return overload_set<std::remove_reference_t<TFs>...>(
      std::forward<TFs>(fs)...);
}

}  // namespace davinci
