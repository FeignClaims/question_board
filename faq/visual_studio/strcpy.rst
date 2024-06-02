************************************************************************************************************************
:cpp:`strcpy` 报错了, 让用 :cpp:`strcpy_s`
************************************************************************************************************************

========================================================================================================================
解决方案
========================================================================================================================

在代码最上面加一行代码即可解决:

.. code-block:: cpp
  :linenos:

  #define _CRT_SECURE_NO_DEPRECATE

========================================================================================================================
解释
========================================================================================================================

:cpp:`<cstring>` 中的 :cpp:`strcpy` 等函数并不安全. :doc:`字符串以 '\\0' 作为终止字符 </faq/basic_concepts/c_string>`, 而 :cpp:`strcpy` 等函数仅仅是循环遍历到终止字符才结束, 这意味着黑客即使传入几亿长度的字符串也会被完全拷贝. 但你存储字符串的空间是有限的, 于是超出空间的字符串将影响到你电脑其他部分.

这样的漏洞在 `2023 年 CWE 已知被利用漏洞排行 <https://cwe.mitre.org/top25/archive/2023/2023_kev_list.html>`_ 中排在第 3 位, 因此我们需要有手段避免它. C11 于是允许实现提供这些函数的安全版本, 其要求给出长度参数, 而 Visual Studio 将它拓展到了 C++ 上:

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`strcpy`

  char* strcpy(char* 拷贝目的地, char const* 源字符串);

  char const* input = "hello world";
  char result[100];
  strcpy(result, input);

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`strcpy_s`

  /*略*/ strcpy_s(char* 拷贝目的地, /*略*/ 拷贝目的地的最大长度, char const* 源字符串);

  char const* input = "hello world";
  char result[100];
  strcpy_s(result, 100, input);

通过 :cpp:`#define _CRT_SECURE_NO_DEPRECATE`, 我们将能强行使用 :cpp:`strcpy`.

.. error::

  strcpy_s 的目的是为了限制字符串拷贝的长度, 防止黑客传入的几亿长度的字符串也会被完全拷贝, 所以你不应该像下面这样写代码:
  
  .. code-block:: cpp
    :linenos:
  
    char const* input = "this is a very long string";
    char result[5];
    strcpy_s(result, strlen(input), input);  // strlen(input) 是最大的拷贝长度, 那 strcpy_s 的意义何在？！

  这样的写法和直接用 :cpp:`strcpy(result, input)` 没有区别.
