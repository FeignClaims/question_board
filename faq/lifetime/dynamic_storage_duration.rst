************************************************************************************************************************
3. 动态存储周期 (dynamic storage duration)
************************************************************************************************************************

========================================================================================================================
说明
========================================================================================================================

对于动态存储周期的对象, 它在运行到 :cpp:`new` 时被构造, 在运行到 :cpp:`delete` 时被销毁.

.. code-block:: cpp
  :linenos:

  int main() {
    Noisy* c1 = new Noisy{Info{.ctor = "0", .dtor = "1"}};
    Noisy* c2 = new Noisy{Info{.ctor = "2", .dtor = "3"}};
    delete c1;
    delete c2;
  }
  // 最终输出
  // 0: c1 构造
  // 2: c2 构造
  // 1: c1 析构
  // 3: c2 析构

如果不 :cpp:`delete` 则动态存储周期对象不会被销毁, 将会发生内存泄露.

.. code-block:: cpp
  :linenos:

  int main() {
    Noisy* c1 = new Noisy{Info{.ctor = "0", .dtor = "1"}};
  }  // 指针本身为自动存储周期而析构, 它指向的对象为动态存储周期而泄露
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

  int main() {
    Noisy* c1 = new Noisy{Info{.ctor = "s", .dtor = "o"}};
    Noisy* c2 = nullptr;
    c2        = new Noisy{Info{.ctor = "t", .dtor = "l"}};
    delete c1;
    Noisy* c3 = new Noisy{Info{.ctor = "i", .dtor = "u"}};
    c2        = c3;
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  4 个字符. 将 :cpp:`std::string` 转换为对应 :cpp:`int` 类型的方法.

.. admonition:: 点击查看答案
   :class: dropdown, solution

   :godbolt:`s6MG9b9Wq`, 答案: :cpp:`stoi`.

------------------------------------------------------------------------------------------------------------------------
题 2
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  int main() {
    {
      Noisy* c1 = nullptr;
      c1        = new Noisy{Info{.ctor = "o", .dtor = "a"}};
      Noisy* c2 = new Derived_noisy{Info{.ctor = "s", .dtor = "n"},
                                    Derived_info{.ctor = "t", .dtor = "i"}};
      Noisy* c3 = nullptr;
      {
        c3 = new Noisy{Info{.ctor = "r", .dtor = "b"}};
        c3 = c2;
        delete c2;
      }
      Noisy* c4 = nullptr;
    }
    Noisy* c5 = nullptr;
    Noisy* c6 = nullptr;
    Noisy* c7 = new Noisy{Info{.ctor = "g", .dtor = "q"}};
    {
      c5        = new Noisy{Info{.ctor = "s", .dtor = "n"}};
      Noisy* c8 = new Noisy{Info{.ctor = "t", .dtor = "u"}};
    }
    {
      Noisy* c9 = new Noisy{Info{.ctor = "r", .dtor = "o"}};
      c6        = new Noisy{Info{.ctor = "e", .dtor = "a"}};
    }
    delete c6;
    Noisy* c10 = new Noisy{Info{.ctor = "m", .dtor = "p"}};
  }

.. admonition:: 点击查看提示
  :class: dropdown
  
  13 个字符. 像 :cpp:`cout` 一样使用, 但是将输出结果存储为 :cpp:`string` 的类.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`d9vjff7xx`, 答案: :cpp:`ostringstream`.

------------------------------------------------------------------------------------------------------------------------
题 3
------------------------------------------------------------------------------------------------------------------------

.. code-block:: cpp
  :linenos:

  int main() {
    {
      Noisy c1{
          Info{.ctor = "s", .copy_ctor = "u", .copy_assign = "s", .dtor = "l"}};
      Noisy* c2 = new Noisy{
          Info{.ctor = "s", .copy_ctor = "o", .copy_assign = "t", .dtor = "r"}};
      Noisy* c3 = nullptr;
      c1        = *c2;
    }
    Noisy* c4 = new Noisy{Info{.ctor = "e", .dtor = "y"}};
    Noisy c5{Info{.ctor = "a", .dtor = "m"}};
    Noisy* c6 = nullptr;
  }

.. admonition:: 点击查看提示
  :class: dropdown

  7 个字符. 上一题答案所要用的头文件.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`G61bEMeTa`, 答案: :cpp:`sstream`.