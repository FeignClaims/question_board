#ifndef INFO_HP
#define INFO_HP

#include <string>

// clang-format off
template <auto = []{}>
// clang-format on
struct Info_impl {
 public:
  std::string ctor{};
  std::string copy_ctor{};
  std::string copy_assign{};
  std::string dtor{};
};

using Info         = Info_impl<>;
using Derived_info = Info_impl<>;

#endif