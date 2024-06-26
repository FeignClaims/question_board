************************************************************************************************************************
无法解析的外部符号
************************************************************************************************************************

========================================================================================================================
解决方案
========================================================================================================================

这说明调用了进行了声明但没有定义的函数. 另外要注意的是, 模板必须在头文件里定义, 不能分成头文件和源文件.

.. code-block:: cpp
  :linenos:
  :caption: 声明

  void function();

.. code-block:: cpp
  :linenos:
  :caption: 定义 (同时也是声明)

  void function() {
    /*...*/
  }

========================================================================================================================
解释
========================================================================================================================

C++ 是支持多源文件的. 生成程序时, 各源文件先通过编译器得到编译, 再被链接器链接起来. 如果链接器进行链接时, 发现源文件对于某个声明没有定义, 它就认为会从其他源文件中得到这个声明的定义 (即认为是外部符号); 没找到就报了这个错.