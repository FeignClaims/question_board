#include "all.hpp"

// 使用 C++ 标准里的名词制作习题
// template <> inline auto log_config<>{std_logger};

// 使用四级单词制作习题
template <>
inline auto log_config<>{cet4_logger};

int main() {
  Noisy c1{
      Info{.ctor = "0", .copy_ctor = "1", .copy_assign = "2", .dtor = "3"}};

  Noisy c2{
      Info{.ctor = "4", .copy_ctor = "5", .copy_assign = "6", .dtor = "7"}};

  Noisy c3 = c1;

  c3 = c2;
  c3 = c1;
}