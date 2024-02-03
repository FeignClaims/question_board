************************************************************************************************************************
:cpp:`auto`
************************************************************************************************************************

.. warning::

  在教学中你可能学过 :cpp:`auto int value = 0;` 表示声明一个局部变量, 而 :cpp:`auto` 可以省略. 这是已经弃用的用法, 不是此处要解释的内容.

:cpp:`auto` 意在让编译器来推导 (deduce) 类型是什么.

.. code-block:: cpp
  :linenos:

  int value  = 0;
  auto t     = value;  // t 的类型是 int

这其中的逻辑可以从报错信息来解释:

.. code-block:: cpp
  :linenos:

  int value    = 0;
  int* pointer = value;  // 错误: 不能用 int 类型的左值初始化 int*

好吧, 编译器你这么聪明, 报错信息里都能告诉我 :cpp:`value` 的类型是 :cpp:`int`. 我现在想通过 :cpp:`value` 拷贝得到一个新对象, 编译器你自己分析它具体是什么类型吧:

.. code-block:: cpp
  :linenos:

  int value  = 0;
  auto t     = value;  // 编译器分析出 t 的类型应该是 int

我们可以添加 :cpp:`const`、:cpp:`&` 和 :cpp:`*` 等修饰符:

.. code-block:: cpp
  :linenos:

  int value = 0;

  auto const t1  = value;   // t1 的类型是 int const
  auto& t2       = value;   // t2 的类型是 int&
  auto const* t3 = &value;  // t3 的类型是 int const*