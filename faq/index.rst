.. _faq:

#######################################################################################################################
常见问题解答
#######################################################################################################################

.. admonition:: 别看: 免争议声明
  :class: dontread, dropdown

  以下所有问题都是有人实际问我的. 由于主要面向应试学生, 解答会大量基于课内 C 风格 C++ 教学, 所以必然有无法描述清楚或没有扩展的内容.

  常见问题解答确实只是为了解答该问题才写的, 且由于大量基于课内 C 风格 C++ 教学, 很难用作现代 C++ 知识点整理, 自学请参考 :doc:`/cpp/main`.

.. admonition:: 阅读方法
  :class: dropdown

  .. admonition:: 前置内容
    :class: precontent

    这是阅读本部分所需的前置内容.

  .. hint::

    这是对思维的进一步启发.

  .. warning::

    这是对内容的警告性说明.

  .. danger::

    这是指出内容的危险性.

  .. seealso::

    这是可用的扩展资料.

  .. admonition:: 相关核心准则
    :class: coreguidelines

    这是与内容明确相关的 C++ 核心准则, 阅读标题就已经能带来启发, 你没有点击阅读的必要.

  .. admonition:: 别看
    :class: dontread

    这是与解答相关性不大的补充性内容.

***********************************************************************************************************************
基本概念
***********************************************************************************************************************

基本概念部分仅对这些内容进行简述, 并给出相关解答的跳转.

.. warning::

  对于更下面的基本概念, 我不得不假定读者已经阅读上面的基本概念, 否则难以用教学大纲涉及的内容给出好的解释.

.. toctree::
  :maxdepth: 1

  basic_concepts/object
  basic_concepts/initialization_assignment
  basic_concepts/struct
  basic_concepts/resource
  basic_concepts/type_conversion
  basic_concepts/const
  basic_concepts/reference
  basic_concepts/pointer
  basic_concepts/function
  basic_concepts/function_parameter
  basic_concepts/value_category
  basic_concepts/auto
  basic_concepts/sizeof
  basic_concepts/c_array
  basic_concepts/c_string
  basic_concepts/operator_overloading
  basic_concepts/template

***********************************************************************************************************************
表达式和语句
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  east_const/main
  variable_decleration_reading/main
  condition/main
  md_c_array/main
  escape_character/main
  newline_character/main
  comma_operator/main
  exception_throwing/index

***********************************************************************************************************************
类与类层次
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  class_invariant/main
  member_initializer/main
  access_specifiers/main

=======================================================================================================================
构造函数、赋值函数、析构函数
=======================================================================================================================

这些函数控制了对象的生命周期: 创建、复制和销毁.

其中有一些函数在不定义时会自动以默认行为定义, 称为特殊函数:

- 默认构造函数: :cpp:`Widget()`
- 拷贝构造函数: :cpp:`Widget(Widget const&)`
- 拷贝赋值函数: :cpp:`Widget& operator=(Widget const&)`
- 移动构造函数: :cpp:`Widget(Widget&&)`
- 移动赋值函数: :cpp:`Widget& operator=(Widget&&)`
- 析构函数: :cpp:`~Widget()`

.. toctree::
  :maxdepth: 1

  storage_duration/index
  rule_of_350/main
  copy_functions_parameter/main
  copy_assignment_define/main

=======================================================================================================================
类层次 (面向对象程序设计, Object-Oriented Programming, OOP)
=======================================================================================================================

只是使用类不是面向对象程序设计, 使用继承和类层次才是.

.. toctree::
  :maxdepth: 1

  virtual_function_invocation_explain/main

***********************************************************************************************************************
输入输出
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  input_methods/main
  pointer_output/main
  c_string_output/main
  ascii_output/main
  newline_character/main
  binary_io/main

***********************************************************************************************************************
模板
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  instantiation/main

***********************************************************************************************************************
标准库、算法、数据结构
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  generate_random_number/main
  range_iterator_and_algorithm/main
  forward_list/main
  dynamic_array/main

***********************************************************************************************************************
术语和惯用法
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  getter_setter/main
  separate_interface_from_implementation/main
  copy_assignment_define/main

***********************************************************************************************************************
Visual Studio 特定问题
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  visual_studio/strcpy
  visual_studio/unresovable_external_symbol

***********************************************************************************************************************
非答疑范畴问题
***********************************************************************************************************************

.. toctree::
  :maxdepth: 1

  twos_complement/main

***********************************************************************************************************************
核心准则
***********************************************************************************************************************

为了配合常见问题解答, 对 `C++ Core Guidelines`_ 中的部分准则进行调整并翻译.

.. toctree::
  :maxdepth: 1

  coreguidelines/c_2
  coreguidelines/c_40
  coreguidelines/c_131
  coreguidelines/es_45

***********************************************************************************************************************
废弃资料
***********************************************************************************************************************

.. admonition:: 常见答疑类型
  :class: dropdown

  - 表达式和语句

  - 标准库

    - 标准库.容器和 `算法 <https://www.bilibili.com/video/BV1VU4y1U7rL>`_

    - 标准库.时间

    - 标准库.随机数

  - 编程思维

    - 编程思维.不要重复代码

    - 编程思维.抽象

    - 编程思维.单一职责

    - 编程思维.类型安全

    - 编程思维.设计模式

    - 编程思维.资源安全

  - C 风格 CPP: 这里的 C 风格不是诋毁 C 语言, C 风格 C++ 是一种杂糅了 C 和 C++ 的恶心东西, 先学它只会让学生讨厌 C++.

    - C 风格 CPP.手动 new 与 delete

    - C 风格 CPP.数组

    - C 风格 CPP.指针运算

    - C 风格 CPP.字符串

  - C 语言问题

  - `const <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_01/doc/>`_

  - 错误处理

    - 错误处理.异常

  - `函数和函数对象 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_00/doc/#concept-function>`_

    - 函数和函数对象. `参数传递 <https://weekly-questions.readthedocs.io/core_guidelines/function_parameter_decision/>`_

    - 函数和函数对象. `返回值 <https://weekly-questions.readthedocs.io/core_guidelines/function_return_decision/>`_

    - 函数和函数对象. `函数类型决策 <https://weekly-questions.readthedocs.io/core_guidelines/function_type_decision/>`_

  - 面向对象编程

  - 类型与对象: 这里的对象不是面向对象编程中所指的 "对象", `一个非正式的解释见此 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_00/doc/#object>`_.

    - 类型与对象. `初始化 <https://weekly-questions.readthedocs.io/core_guidelines/ES/ES_20/>`_

    - 类型与对象.存储周期

  - 类与 `结构体 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_04/doc/>`_

    - 类与结构体. `不变式 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_05/doc/>`_

    - 类与结构体. `特殊函数 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_09/doc/>`_

    - 类与结构体.友元函数

    - 类与结构体. `运算符重载 <https://weekly-questions.readthedocs.io/2021_2022_spring/week_02/doc/>`_

  - `模板 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_06/doc/>`_

  - 输入输出

    - 输入输出.二进制

    - 输入输出.格式化

    - 输入输出.文件

  - 术语和惯用法

  - 算法与数据结构: 这里的算法是一般意义上的算法

    - 算法与数据结构.递归

    - 算法与数据结构.排序

    - 算法与数据结构.链表

  - 项目管理: 也包含多文件编译、包含头文件相关内容

    - 项目管理.包管理

    - 项目管理.构建工具

  - `引用 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_00/doc/#concept-reference>`_

  - `指针 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_00/doc/#concept-pointer>`_

  - `资源 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_00/doc/#resource>`_ 管理

  - `作用域 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_03/doc/>`_ 与 `声明方式 <https://weekly-questions.readthedocs.io/2022_2023_autumn/week_02/doc/>`_
