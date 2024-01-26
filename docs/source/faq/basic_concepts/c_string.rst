************************************************************************************************************************
C 风格字符串和字符串字面值 (C-style string and string literal)
************************************************************************************************************************

.. seealso::

  - :doc:`/faq/basic_concepts/c_array`

C 风格字符串是一串以 :cpp:`'\\0'` 结尾的字符. 按照从 C 继承来的约定, :cpp:`char*` 和 :cpp:`char const*` 虽然是指针, 但很多时候会被认为是 C 风格字符串进行处理.

.. code-block:: cpp
  :linenos:

  char array[] = {'a', 'b', 'c', '\0'};

  int const size = std::strlen(array);  // 计数直到遇到终止字符 '\0'
  std::cout << array << '\n';           // 输出直到遇到终止字符 '\0'

而形如 :cpp:`"hello"` 的写法称为字符串字面值, 是书写 C 风格字符串的便携方法, 它实际是将 :cpp:`"hello"` 静态存储在一个 **只读区域**, **因此不能修改它的内容**.

.. code-block:: cpp
  :linenos:

  "hello";  // "hello" 的类型是 char[6], 除了 hello, 之后还有终止字符 '\0'.

  char const* string = "hello";  // 获取它首元素的指针, 按约定这就被认为是一个字符串

  char* string = "hello";  // 警告: 不能修改字符串字面值的内容
  string[1]    = 'a';      // 未定义行为!

你可以用一个字符串字面值初始化字符数组.

.. code-block:: cpp
  :linenos:

  char array[] = "hello";
  sizeof(array) == sizeof(char[6]);
  // 相当于:
  char array[6];
  array[0] = 'h';
  array[1] = 'e';
  array[2] = 'l';
  array[3] = 'l';
  array[4] = 'o';
  array[5] = '\0';

  char array[8] = "hello";
  array[0] = 'h';
  array[1] = 'e';
  array[2] = 'l';
  array[3] = 'l';
  array[4] = 'o';
  array[5] = '\0';
  array[6] = '\0';
  array[7] = '\0';

========================================================================================================================
相关解答
========================================================================================================================

- :doc:`/faq/c_string_output/main`
- :doc:`/faq/pointer_output/main`