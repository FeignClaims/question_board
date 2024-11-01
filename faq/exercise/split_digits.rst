************************************************************************************************************************
拆分整数的各位数
************************************************************************************************************************

拆分整数的核心在于, 十进制的表示方式是 :math:`d_0 * 10^0 + d_1 * 10^1 + ... + d_n * 10^n`, 因此,

- 利用整数求余 :cpp:`%` 运算, 我们可以 "筛" 掉高位部分: :cpp:`2193 % 100 == 93`.
- 利用整数整除 :cpp:`/` 运算, 我们可以 "筛" 掉低位部分: :cpp:`2193 / 100 == 21`.

这是不是意味着我们要用 :cpp:`2193 % 10的n次方 / 10的n-1次方` 这样的方式来得到各个位? **不需要这么复杂**. 我们可以每次循环时, 将 :cpp:`int value = 2193` 除以 :cpp:`10`.

.. code-block:: cpp
  :linenos:

  int value = 2193
  value     /= 10;  // 219 (value /= 10 相当于 value = value / 10)
  value     /= 10;  // 21
  value     /= 10;  // 2
  value     /= 10;  // 0

这样一来, 我们就能用 :cpp:`value % 10` 得到各个位: :godbolt:`s7Yx7sz3P`

.. code-block:: cpp
  :linenos:

  #include <iostream>
  using namespace std;

  int main() {
    int value;
    cin >> value;

    for (; value != 0; value /= 10) {
      int digit = value % 10;
      // 用当前位的数 digit 做任何你需要的事
    }
  }

- 如果你需要保留 :cpp:`value` 不变呢? :cpp:`for (int i = value; i != 0; i /= 10)`.
- 如果输入的 :cpp:`value` 是 :cpp:`0` 呢? 那就需要你另外考虑了.

例如, 我们可以对整数的各个位数进行求和:

.. code-block:: cpp
  :linenos:

  #include <iostream>
  using namespace std;

  int main() {
    int value;
    cin >> value;

    int sum_of_digits = 0;
    for (; value != 0; value /= 10) {
      int digit      = value % 10;
      sum_of_digits += digit;
    }
  }

========================================================================================================================
不知道为什么新手会想到的复杂方法
========================================================================================================================

对于第 n 位 (第 1 位为个位, 第 2 位为十位...), 我们可以用 :cpp:`2193 % 10的n次方 / 10的n-1次方` 得到.

为此, 我们需要使用 :cpp:`#include <cmath>` 里的 :cpp:`std::pow` 函数来求幂: :cpp:`std::pow(10, 2) == 100.0`. (由于 :cpp:`using namespace std;`, 使用时 :cpp:`std::` 可以省略.)

但是, 请注意 :cpp:`std::pow` 返回的结果是浮点数, 整数不能和浮点数进行求幂运算 (你怎么求 2193 除以 1.5 的余数?). 因此, 我们要用 :cpp:`static_cast<int>(std::pow(10, 2))` 将结果转换为 :cpp:`int` 类型: :godbolt:`8j3E43MPY`

.. code-block:: cpp
  :linenos:

  #include <cmath>  // for std::pow
  #include <iostream>
  using namespace std;

  int main() {
    int value = 0;
    cin >> value;

    int digit_size = 0;
    for (int i = value; i != 0; i /= 10) {
      ++digit_size;
    }

    for (int i = 0; i < digit_size; ++i) {
      int digit =
          value % static_cast<int>(pow(10, i + 1)) / static_cast<int>(pow(10, i));
      // 用当前位的数 digit 做任何你需要的事
    }
  }
