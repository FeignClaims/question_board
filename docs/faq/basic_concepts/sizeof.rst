************************************************************************************************************************
:cpp:`sizeof`
************************************************************************************************************************

:cpp:`sizeof` 用于获取类型或表达式对应类型的大小, 返回该类型占多少字节, 跟值是多少没有任何关系.

如果类型为引用, 则返回被引用类型的大小. 这是可以理解的, 因为引用只需要作为别名而非对象, 不要求被实际存储.

.. tabs::

  .. tab:: :cpp:`int`

    .. code-block:: cpp
      :linenos:

      int value;
      sizeof(value) == sizeof(int);

  .. tab:: 引用

    .. code-block:: cpp
      :linenos:

      int value;
      int& reference = value;
      sizeof(reference) == sizeof(int);   // 返回被引用类型的大小
      sizeof(int&)      == sizeof(int);   // 返回被引用类型的大小

  .. tab:: 指针

    .. code-block:: cpp
      :linenos:

      int* pointer;
      sizeof(pointer)     == sizeof(int*);
      sizeof(pointer + 1) == sizeof(int*);

  .. tab:: 数组

    .. code-block:: cpp
      :linenos:

      int array[5];
      sizeof(array)     == sizeof(int) * 5;  // 数组本身的大小
      sizeof(array[0])  == sizeof(int);      // 数组元素的大小

      /* C风格数组非常容易隐式类型转换为首元素的指针! */
      sizeof(array + 0) == sizeof(int*);
      sizeof(+array)    == sizeof(int*);

.. danger::

  标准并没有规定一个字节占多少位, 更没有规定大多数基础类型的具体大小, 例如 :cpp:`sizeof(int)` 并不一定是 4. 以下是一些固定的值,

  - :cpp:`1 == sizeof(char) == sizeof(signed char) == sizeof(unsigned char)`.
  - :cpp:`4 == sizeof(float)`.
  - :cpp:`8 == sizeof(double)`.

  如果实在需要固定大小的整数, 请使用 :cpp:`<cstdint>` 中的定长整数别名, 例如 :cpp:`std::int64_t`.