************************************************************************************************************************
:cpp:`sizeof`
************************************************************************************************************************

:cpp:`sizeof` 用于获取类型或表达式对应类型的大小, 返回该类型占多少字节, 跟实际存储的值没有任何关系. 如果类型为引用, 则返回被引用类型的大小.

.. code-block:: cpp
  :linenos:

  int value;
  sizeof(value) == sizeof(int);

  int& reference = value;
  sizeof(reference) == sizeof(int);

  int* pointer;
  sizeof(pointer)     == sizeof(int*);
  sizeof(pointer + 1) == sizeof(int*);

  int array[5];
  sizeof(array)     == sizeof(int) * 5;  // 数组本身的大小
  sizeof(array[0])  == sizeof(int);      // 数组元素的大小
  sizeof(array + 0) == sizeof(int*);     // C风格数组非常容易隐式类型转换为首元素的指针!
  sizeof(+array)    == sizeof(int*);

.. danger::

  标准并没有规定一个字节占多少位, 更没有规定大多数基础类型的具体大小, 例如 :cpp:`sizeof(int)` 并不一定是 4. 以下是一些固定的值,

  - :cpp:`1 == sizeof(char) == sizeof(signed char) == sizeof(unsigned char)`.
  - :cpp:`4 == sizeof(float)`.
  - :cpp:`8 == sizeof(double)`.

  如果实在需要固定大小的整数, 请使用 :cpp:`<cstdint>` 中的定长整数别名, 例如 :cpp:`std::int64_t`.