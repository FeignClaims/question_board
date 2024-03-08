************************************************************************************************************************
3. 动态生命周期 (dynamic lifetime)
************************************************************************************************************************

========================================================================================================================
说明
========================================================================================================================

运行到 :cpp:`new` 时开始, :cpp:`delete` 时结束.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer* c1 = new Printer{Info{.ctor = "0", .dtor = "1"}};
    Printer* c2 = new Printer{Info{.ctor = "2", .dtor = "3"}};
    delete c1;
    delete c2;
  }
  // 最终输出
  // 0: c1 构造
  // 2: c2 构造
  // 1: c1 析构
  // 3: c2 析构

如果不 :cpp:`delete` 则不发生析构而内存泄露.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer* c1 = new Printer{Info{.ctor = "0", .dtor = "1"}};
  }  // 指针本身为自动生命周期而析构, 它指向的对象为动态生命周期而泄露
  // 最终输出
  // 0: c1 构造

========================================================================================================================
题目
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
题 1
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    Printer* c1 = new Printer{Info{.ctor = "s", .dtor = "o"}};
    Printer* c2 = nullptr;
    c2          = new Printer{Info{.ctor = "t", .dtor = "l"}};
    delete c1;
    Printer* c3 = new Printer{Info{.ctor = "i", .dtor = "u"}};
    c2          = c3;
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  4 个字符, 将 :cpp:`std::string` 转换为对应 :cpp:`int` 类型的方法.

.. admonition:: 点击查看答案
   :class: dropdown, solution

   :godbolt:`d3o6rf6hx`, 答案: :cpp:`stoi`.

------------------------------------------------------------------------------------------------------------------------
题 2
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    {
      Printer* c1 = nullptr;
      c1          = new Printer{Info{.ctor = "i", .dtor = "h"}};
      Printer* c2 = new DerivedPrinter{Info{.ctor = "n", .dtor = "_"},
                                      DerivedInfo{.ctor = "n", .dtor = "r"}};
      Printer* c3 = nullptr;
      {
        c3 = new Printer{Info{.ctor = "e", .dtor = "m"}};
        c3 = c2;
        delete c2;
      }
      Printer* c4 = nullptr;
    }
    Printer* c5 = nullptr;
    Printer* c6 = nullptr;
    Printer* c7 = new Printer{Info{.ctor = "p", .dtor = "w"}};
    {
      c5          = new Printer{Info{.ctor = "r", .dtor = "p"}};
      Printer* c8 = new Printer{Info{.ctor = "o", .dtor = "l"}};
    }
    {
      Printer* c9 = new Printer{Info{.ctor = "d", .dtor = "s"}};
      c6          = new Printer{Info{.ctor = "u", .dtor = "c"}};
    }
    delete c6;
    Printer* c10 = new Printer{Info{.ctor = "t", .dtor = "v"}};
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  13 个字符, STL 求两个范围的内积.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`f4q4d117o`, 答案: :cpp:`inner_product`.

------------------------------------------------------------------------------------------------------------------------
题 3
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    {
      Printer c1{
          Info{.ctor = "s", .copy_ctor = "u", .copy_assign = "s", .dtor = "l"}};
      Printer* c2 = new Printer{
          Info{.ctor = "s", .copy_ctor = "o", .copy_assign = "t", .dtor = "r"}};
      Printer* c3 = nullptr;
      c1          = *c2;
    }
    Printer* c4 = new Printer{Info{.ctor = "e", .dtor = "y"}};
    Printer c5{Info{.ctor = "a", .dtor = "m"}};
    Printer* c6 = nullptr;
  }

.. admonition:: 点击查看提示
  :class: dropdown

  7 个字符, 编程题解答参考中所用到的一个头文件.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`aWz5WYjTo`, 答案: :cpp:`sstream`.