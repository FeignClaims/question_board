************************************************************************************************************************
为什么字符指针不输出地址值, 而其他指针输出地址值?
************************************************************************************************************************

按照从 C 继承来的约定, :cpp:`char*` 和 :cpp:`char const*` 虽然是指针, 但很多时候会被认为是 :doc:`字符串 </faq/basic_concepts/c_string>` 进行处理 (若区别于 :cpp:`std::string`, 则称为 C 风格字符串).

:cpp:`cout` 即认为 :cpp:`char const*` 是字符串, 提供了以下函数重载:

.. hint::

  所谓 :cpp:`cout << value` 不过是定义了一个名为 :cpp:`operator<<` 的函数.

  例如 :cpp:`ostream& operator<<(ostream& cout, int value);`

:cpp:`ostream& operator<<(ostream& cout, char const*)`: 作为字符串进行输出.
  :cpp:`char*` 和 :cpp:`char const*`, 可以转换/直接传参为 :cpp:`char const*`, 都优先采用这个版本.

:cpp:`ostream& operator<<(ostream& cout, void const*)`: 输出指针所存储的地址.
  所有指针均能隐式类型转换为 :cpp:`void const*` 指针, 故其他指针均采用这个版本.

如果确实需要输出字符指针的地址, 可以显式进行类型转换, 从而采用输出指针所存储地址的版本:

.. code-block:: cpp
  :linenos:

  char ch = 'a';
  std::cout << static_cast<void const*>(&ch);

  char* pointer = &ch;
  std::cout << static_cast<void const*>(pointer);