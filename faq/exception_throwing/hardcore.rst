************************************************************************************************************************
硬核题: 抛出一个构造函数和析构函数会输出的类
************************************************************************************************************************

大概率不考, 但理论很简单, 建议了解一下.

========================================================================================================================
异常抛出的对象
========================================================================================================================

异常抛出时是要抛出一个对象的, 那么这个对象应该存放在哪？

显然不能存放在栈上, 因为 :doc:`normal` 中已经指出, 在栈回溯的过程中, 这些栈上的自动存储对象都需要被析构.
所以当以 :cpp:`throw object;` 抛出时, 会调用拷贝构造函数创建一个新的对象, 它不存放在栈中.

直到异常处理完成, 这个异常抛出的对象才会被析构.

.. code-block:: cpp
  :linenos:

  void function() {
    try {
      Printer printer{Info{.ctor = "i", .copy_ctor = "n", .dtor = "t"}};
      throw printer;
    } catch (Printer& printer) {
      Printer another{Info{.ctor = "8", .dtor = "_"}};
    }
  }

  auto main() -> int {
    function();
  }

.. admonition:: 点击查看提示
  :class: dropdown

  6 个字符, 大小固定为 8 位的有符号整数类型.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`E1dezb8eP`, 答案: :code:`int8_t`.

========================================================================================================================
异常捕获时
========================================================================================================================

假设抛出了类型 :cpp:`Printer`,

- 如果 :cpp:`catch` 中写的是 :cpp:`catch (Printer printer)`, 则还需要发生拷贝.
- 如果 :cpp:`catch` 中写的是 :cpp:`catch (Printer& printer)`, 则直接引用异常抛出的对象.

.. code-block:: cpp
  :linenos:

  void function() {
    try {
      Printer printer{Info{.ctor = "i", .copy_ctor = "n", .dtor = "t"}};
      throw printer;
    } catch (Printer& printer) {
      Printer another{Info{.ctor = "8", .dtor = "_"}};
    }
  }

  auto main() -> int {
    function();
  }

.. admonition:: 点击查看提示
  :class: dropdown

  8 个字符, 没能编出什么有意义的词了😭.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`7Wz5f4jvY`, 答案: :code:`intn8_tt`.