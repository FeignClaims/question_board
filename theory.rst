***********************************************************************************************************************
答疑原则和理论依据
***********************************************************************************************************************

=======================================================================================================================
答疑原则
=======================================================================================================================

.. epigraph::

  "你看不懂我这 '优雅' 的代码, 对吧？这说明我很聪明."——这样做不是好的教学.

  —— Bjarne Stroustrup《CppCon 2017: 传授和学习现代 C++》

- 能提供代码辅助回答的地方, 尽量给出代码或启发提问者给出代码.
- 答疑的过程应该是启发式的, 是要辅助提问者自己弄明白这个问题.
- 先解决问题, 再做详细解释.
- 回答时尽量详细但保持简单: 不聪明, 不自作聪明, 不在回答中用复杂的回答显得自己很聪明.
- 如果有更简单的方法, 教给提问者.

=======================================================================================================================
答疑范围
=======================================================================================================================

.. admonition:: 以下是我能回答你的
  :class: dropdown, toggle-shown

  - 大学 C++ 课程的教学内容.
  - C++11~C++23 的部分基础内容 (以《Effective Modern C++》和《A Tour of C++, 3rd Edition》涉及内容为主).
  - 现代 C++ 的使用理念.

.. admonition:: 以下是我会回答你, 但不情愿的
  :class: dropdown

  - 没有格式化的代码.
  - 大量代码, 但又没有描述其中的逻辑.
  - 当存在报错信息时, 以截图形式给出报错信息, 或不给出详细的报错信息.
  - 不会并且 **不愿意** 学习断点调试的提问者的问题.
  - 模糊的问题.
  - 态度不好的提问者的问题.
  - C 风格 C++ 代码.

.. admonition:: 以下是我可能能回答你的
  :class: dropdown

  - C 语言代码. (C 和 C++ 真的是两回事, 我完全不会 C!)
  - 构建工具 CMake 的使用, 不含工具链的配置.
  - 包管理器 conan 的使用, 不含工具链的配置.
  - 部分软件的使用、安装.

.. admonition:: 以下是我不能回答你的
  :class: dropdown

  - 往年考试试卷在哪能找到.
  - 仅有代码图片而没有代码文本的问题.
  - C++ 并发相关内容.
  - 国际化 (i18n) 相关内容.
  - 过于复杂的模板元编程.
  - 语言律师类问题, 即对标准的咬文嚼字.
  - 第三方库的使用.
  - 大多软件的使用或安装.
  - 除 CMake 外的构建工具的使用. (如 Makefile 等.)
  - 除 Conan 外的包管理器的使用. (如 vcpkg 等.)
  - 工具链的配置.
  - 与运行环境强相关的问题.

=======================================================================================================================
答疑室的目的
=======================================================================================================================

.. epigraph::

  社会实践是检验真理的唯一标准.

  —— 1963 年《五评苏共中央的公开信》毛主席加注

当前目标是通过答疑实践,

- 了解东南大学学生在学习 C++ 过程中的痛点.
- 让学生能抛弃 "C++ = C + 面向对象程序设计" "设计模式只能用于面向对象程序设计" 等错误认识, 对 "是什么让 C++ 成为 C++" 这一问题有一定的正确认识.
- 积累 C++ 的传授经验, 总结一些简单的教学示例 (不是语法的堆砌, 而是 "为什么要有这个特性" 的生动解释).

=======================================================================================================================
参考资料
=======================================================================================================================

-----------------------------------------------------------------------------------------------------------------------
答疑方法
-----------------------------------------------------------------------------------------------------------------------

- 《毛主席论教育革命》
- `《人的正确思想是从哪里来的？》`_
- `Stop Teaching C - Kate Gregory - CppCon 2015`_ 及 Kate Gregory 其他公开视频
- `Learning and Teaching Modern C++ - Bjarne Stroustrup - CppCon 2017`_ 及 Bjarne Stroustrup 其他公开视频

-----------------------------------------------------------------------------------------------------------------------
编程思维
-----------------------------------------------------------------------------------------------------------------------

- `C++ Core Guidelines (C++ 核心准则)`_
- 《Elements of Programming》
- `C++ Seasoning - Sean Parent - GoingNative 2013`_ 及 Sean Parent 其他公开视频
- 《Effective Modern C++》
- 《The Design and Evolution of C++》
- 《Thriving in a crowded and changing world - C++ 2006-2020》

-----------------------------------------------------------------------------------------------------------------------
教学方法
-----------------------------------------------------------------------------------------------------------------------

- :doc:`/ppp2_chapter0`