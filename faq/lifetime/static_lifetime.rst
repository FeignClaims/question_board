************************************************************************************************************************
2. 静态生命周期 (static lifetime)
************************************************************************************************************************

========================================================================================================================
说明
========================================================================================================================

此处专指静态局部变量和全局变量.

运行到它的名字时开始,  **程序结束时** 结束, 因此即使多次运行到, 也只会构造一次. 它的析构晚于自动生命周期对象.

.. code-block:: cpp
  :linenos:

  void function() {
    static Printer c1{Info{.ctor = "0", .dtor = "1"}};
    Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  
  auto main() -> int {
    function();
    function();
  }
  // 最终输出
  // 0: c1 构造
  // 2: 第一次调用时, c2 构造
  // 3: 第一次调用时, c2 析构
  // 2: 第二次调用时, c2 构造
  // 3: 第二次调用时, c2 析构
  // 1: c1 析构

对象的生命周期按它开始的相反顺序结束.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    { static Printer c1{Info{.ctor = "0", .dtor = "1"}}; }
    static Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: c1 构造
  // 2: c2 构造
  // 3: c2 析构
  // 1: c1 析构

全局变量也是静态生命周期, 它在程序开始时开始, 在程序结束时结束.

.. code-block:: cpp
  :linenos:

  Printer c1{Info{.ctor = "0", .dtor = "1"}};

  auto main() -> int {
    Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: 程序开始时, c1 构造
  // 2: c2 构造
  // 3: c2 析构
  // 1: 程序结束时, c1 析构

函数模板实例化后可能是不同的函数, 则有不同的静态局部变量.

.. code-block:: cpp
  :linenos:

  template <typename T>
  void function() {
    static Printer c1{Info{.ctor = "0", .dtor = "1"}};
  }

  auto main() -> int {
    function<int>();
    function<double>();
    function<int>();
  }
  // 最终输出
  // 0: function<int>::c1 构造
  // 0: function<double>::c1 构造
  // 1: function<double>::c1 析构
  // 1: function<int>::c1 析构

========================================================================================================================
题目
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
题 1
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    static Printer c1{Info{.ctor = "v", .dtor = "r"}};
    { static Printer c2{Info{.ctor = "e", .dtor = "o"}}; }
    static Printer c3{Info{.ctor = "c", .dtor = "t"}};
  }

.. admonition:: 点击查看提示
   :class: dropdown
  
   6 个字符, 标准库中可变长度的数组.

.. admonition:: 点击查看答案
   :class: dropdown, solution

   :godbolt:`ssPdneKo4`, 答案: :cpp:`vector`.

------------------------------------------------------------------------------------------------------------------------
题 2
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  void function(Printer const& printer) { static Printer c1 = printer; }

  Printer c1{Info{.ctor = "d", .copy_ctor = "m", .dtor = "r"}};

  auto main() -> int {
    {
      static Printer c2{Info{.ctor = "o", .copy_ctor = "l", .dtor = "o"}};
      function(c1);
      { static Printer c3{Info{.ctor = "a", .dtor = "r"}}; }
      static Printer c4{Info{.ctor = "i", .dtor = "e"}};
      function(c2);
    }

    static Printer c6{Info{.ctor = "n", .dtor = "_"}};
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  12 个字符, 输入参数超出函数的定义域时抛出的异常.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`xc19YrYTY`, 答案: :cpp:`domain_error`.

------------------------------------------------------------------------------------------------------------------------
题 3
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    {
      { static Printer c1{Info{.ctor = "f", .dtor = "f"}}; }
      static Printer c2{Info{.ctor = "i", .dtor = "o"}};
    }
    {
      { static Printer c3{Info{.ctor = "n", .dtor = "_"}}; }

      static Printer c4{Info{.ctor = "d", .dtor = "t"}};
      {
        static Printer c5{Info{.ctor = "_", .dtor = "o"}};
        { static Printer c6{Info{.ctor = "l", .dtor = "n"}}; }
        static Printer c7{Info{.ctor = "a", .dtor = "_"}};
      }
      static Printer c8{Info{.ctor = "s", .dtor = "t"}};
    }
  }

.. admonition:: 点击查看提示
  :class: dropdown

  16 个字符, 在 :cpp:`std::string` 中查找最后一个不等于给定字符序列中任何字符的字符.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`67Kjb5c6s`, 答案: :cpp:`find_last_not_of`.
