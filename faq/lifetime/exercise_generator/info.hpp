#ifndef INFO_HP
#define INFO_HP

// clang-format off
template <auto = []{}>
// clang-format on
struct Info_impl {
 public:
  char ctor{};
  char copy_ctor{};
  char copy_assign{};
  char dtor{};
};

using Info         = Info_impl<>;
using Derived_info = Info_impl<>;

#endif