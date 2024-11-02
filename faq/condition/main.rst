************************************************************************************************************************
条件判断 (condition)
************************************************************************************************************************

条件判断所填入的表达式只需要能够 :doc:`类型转换 </faq/basic_concepts/type_conversion>` 为 :cpp:`bool` 类型即可.

:cpp:`bool` 类型只有两个值, :cpp:`true` 为真, :cpp:`false` 为假.

.. code-block:: cpp
  :linenos:

  int value = 1;
  if (value == 1) {  // value == 1 表达式返回 bool 类型, 可以用于条件判断
  }

.. code-block:: cpp
  :linenos:

  bool function();

  if (function()) {  // 返回 bool 类型, 可以用于条件判断
  }

.. code-block:: cpp
  :linenos:

  int value;

  if (value) {  // 隐式类型转换为 bool 类型, 可以用于条件判断
  }

.. code-block:: cpp
  :linenos:

  while (true) {  // true 是 bool 类型, 可以用于条件判断
    // 始终为真, 死循环!
  }
