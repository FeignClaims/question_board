************************************************************************************************************************
1. 自动生命周期 (automatic lifetime)
************************************************************************************************************************

========================================================================================================================
说明
========================================================================================================================

自动对象的生命周期在运行到它的名字时开始, 在它名字不可见后结束 (到达了 :cpp:`}`).

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer c1{Info{.ctor = "0", .dtor = "1"}};
  }
  // 最终输出
  // 0: c1 构造
  // 1: c1 析构

对象的生命周期按它开始的相反顺序结束.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer c1{Info{.ctor = "0", .dtor = "1"}};
    Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: c1 构造
  // 2: c2 构造
  // 3: c2 析构
  // 1: c1 析构

可以引入作用域, 来缩小对象的生命周期.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    {
      Printer c1{Info{.ctor = "0", .dtor = "1"}};
    }
    Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: c1 构造
  // 1: c1 析构
  // 2: c2 构造
  // 3: c2 析构

C风格数组的元素按下标顺序构造, 按逆序析构.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer c1[] = {Printer{Info{.ctor = "0", .dtor = "1"}},
                    Printer{Info{.ctor = "2", .dtor = "3"}},
                    Printer{Info{.ctor = "4", .dtor = "5"}}};
  }
  // 0: 第 0 个元素构造
  // 2: 第 1 个元素构造
  // 4: 第 2 个元素构造
  // 5: 第 2 个元素析构
  // 3: 第 1 个元素析构
  // 1: 第 0 个元素析构

========================================================================================================================
题目
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
题 1
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer c1{
        Info{.ctor = "s", .copy_ctor = "t", .copy_assign = "o", .dtor = "l"}};

    Printer c2 = c1;

    Printer c3{
        Info{.ctor = "r", .copy_ctor = "a", .copy_assign = "t", .dtor = "u"}};

    c2 = c3;
    c2 = c1;
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  7 个字符, 将 C 字符串转换为对应的 :cpp:`unsigned long long` 类型整数的方法.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`qM87cz5aE`, 答案: :cpp:`strtoull`.

------------------------------------------------------------------------------------------------------------------------
题 2
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    {
      {
        Printer c1{Info{.ctor = "i", .dtor = "r"}};
        { Printer c2{Info{.ctor = "s", .dtor = "_"}}; }
        Printer c3{Info{.ctor = "p", .dtor = "a"}};
      }
      Printer c4{Info{.ctor = "t", .dtor = "i"}};
    }
    Printer c5{Info{.ctor = "t", .dtor = "d"}};
    Printer c6{Info{.ctor = "i", .dtor = "e"}};
    Printer c7{Info{.ctor = "o", .dtor = "n"}};
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  14 个字符, STL 判断范围是否已经划分.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`EPscshb6d`, 答案: :cpp:`is_partitioned`.

------------------------------------------------------------------------------------------------------------------------
题 3
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    DerivedPrinter c1{
        Info{.ctor = "l", .copy_ctor = "g", .copy_assign = "i", .dtor = "r"},
        DerivedInfo{
            .ctor = "e", .copy_ctor = "m", .copy_assign = "h", .dtor = "o"}};

    Printer c2{Info{.ctor = "n", .dtor = "r"}};

    {
      Printer c3{c1};  // Printer c3 = c1;
      {
        Printer c4{Info{.ctor = "t", .dtor = "e"}};
        { Printer c5{Info{.ctor = "h", .dtor = "_"}}; }
      }
    }
  }

.. admonition:: 点击查看提示
  :class: dropdown

  12 个字符, 超出实现支持的长度限制时抛出的异常. 如当新容量大于 :cpp:`std::vector::max_size()` 时, :cpp:`std::vector::reserve` 会抛出此异常.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`T6acTT4vv`, 答案: :cpp:`length_error`.