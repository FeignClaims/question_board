************************************************************************************************************************
2. 静态存储周期 (static storage duration)
************************************************************************************************************************

========================================================================================================================
说明
========================================================================================================================

对于静态存储周期的对象, 它在第一次从运行到它的定义时被构造, 在 **程序结束时** 销毁. 因此即使多次运行到, 也只会构造一次.

.. code-block:: cpp
  :linenos:

  void function() {
    static Printer c1{Info{.ctor = "0", .dtor = "1"}};
    Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  
  int main() {
    function();
    function();
  }
  // 最终输出
  // 0: 第一次调用时, c1 构造
  // 2: 第一次调用时, c2 构造
  // 3: 第一次调用时, c2 析构
  // 2: 第二次调用时, c2 构造
  // 3: 第二次调用时, c2 析构
  // 1: 程序结束时, c1 析构

程序在执行完 :cpp:`main` 函数后, 才对静态存储周期对象进行销毁. 因此, 它的析构晚于 :cpp:`main` 函数中的自动存储周期对象.

.. code-block:: cpp
  :linenos:

  int main() {
    Printer c1{Info{.ctor = "0", .dtor = "1"}};
    static Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: c1 构造
  // 2: c2 构造
  // 1: c1 析构
  // 3: c2 析构

如果有多个静态存储周期对象要销毁, 它们将按构造的相反顺序销毁.

.. code-block:: cpp
  :linenos:

  int main() {
    { static Printer c1{Info{.ctor = "0", .dtor = "1"}}; }
    static Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: c1 构造
  // 2: c2 构造
  // 3: c2 析构
  // 1: c1 析构

全局变量也是静态存储周期, 它在程序开始、进入 :cpp:`main` 函数之前被构造, 在程序结束时被销毁.

.. code-block:: cpp
  :linenos:

  Printer c1{Info{.ctor = "0", .dtor = "1"}};

  int main() {
    Printer c2{Info{.ctor = "2", .dtor = "3"}};
  }
  // 最终输出
  // 0: 程序开始时, c1 构造
  // 2: c2 构造
  // 3: c2 析构
  // 1: 程序结束时, c1 析构

类模板、函数模板实例化后可能是不同的类、函数, 则有不同的静态局部变量.

.. code-block:: cpp
  :linenos:

  template <typename T>
  void function() {
    static Printer c1{Info{.ctor = "0", .dtor = "1"}};
  }

  int main() {
    function<int>();
    function<double>();
    function<int>();
  }
  // 最终输出
  // 0: function<int>::c1 构造
  // 0: function<double>::c1 构造
  // 1: function<double>::c1 析构
  // 1: function<int>::c1 析构

.. seealso::

  :doc:`/faq/instantiation/main` 中解释了模板的实例化.

========================================================================================================================
题目
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
题 1
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  int main() {
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

  int main() {
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

  int main() {
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
