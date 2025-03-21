.. _学习大纲:

************************************************************************************************************************
学习大纲
************************************************************************************************************************

========================================================================================================================
使用提示
========================================================================================================================

先看 :ref:`学习大纲_基础` 之后随意.

阅读顺序上, :ref:`学习大纲_基础` 严格从上到下, 其他可以从上到下.

看书必须看前言, 技术书往往在前言写明了适用人群和阅读方法等.

.. _学习大纲_常用网站资源:

========================================================================================================================
常用网络资源
========================================================================================================================

更多见于 `我的 C++ 浏览器书签 (2024/08/30) (右键另存为再导入到浏览器)`_ 和 `我的 C++ 订阅源 (2024/08/30) (右键另存为再导入浏览器 feedbro 插件)`_.

- `cppreference`_; :doc:`/searching_method/index`.
- `How to Ask For C++ Coding Help <http://www.gregcons.com/KateBlog/HowToAskForCCodingHelp.aspx>`_
- `Bjarne Stroustrup's Homepage`_
- `Standard C++ <https://isocpp.org/>`_
- `C++ Core Guidelines (C++ 核心准则)`_

.. _学习大纲_基础:

========================================================================================================================
基础
========================================================================================================================

严格从上到下.

.. _学习大纲_入门:

------------------------------------------------------------------------------------------------------------------------
入门
------------------------------------------------------------------------------------------------------------------------

**看书记得看前言! 看书记得看前言! 看书记得看前言!**

《Programming: Principles and Practice Using C++, 3rd Edition》(天鹅书, 个人译为《程序设计：使用C++的原理与实践（第3版）》, 第二版译本错译为《C++程序设计：原理与实践（第2版）》) 
  .. hint::

    我为这本好书做了 **一个学习项目文件**: `为天鹅书第三版制作的学习项目文件 (解压以使用)`_, 解压后打开 "请读我" 文件查看使用说明 (例如需要安装 `Git: 通过官网下载`_).

  个人认为最好最优雅的程序设计入门书, 我的 C++ 传授、答疑、学习方法高度基于 :doc:`本书第二版第 0 章 </ppp2_chapter0>` 和 :doc:`本书第三版第 0 章 </ppp3_chapter0>` (强烈推荐阅读!). 请注意我的说法和书名的翻译: 这本书的主题是 **程序设计**, 也就是表达代码意图所需的思想、技术和工具. C++ 语言是我们的主要工具, 因此我们比较详细地描述了很多 C++ 语言的特性. 但请记住, C++ 只是一种工具, 而不是本书的主题. 本书是 “用 C++ 语言进行程序设计”, 而不是 “C++ 和一点程序设计理论”.

  本书 2024 年 4 月 12 日出版, 教授当代 C++ (C++20 和 C++23) 并涵盖众多程序设计思维、方法, 但却相较于第 2 版缩减了一半篇幅!

  在第 0 章, 它会给出书籍配套的资源网站, 其中给出了部分示例代码、部分习题解答、更多参考资料、 `PPP Style Guide (天鹅书风格指南)`_ 等资源.

  **目前本书没有翻译, 但建议使用这本书——哪怕是 DeepL 机翻** (电脑可以用 "沉浸式翻译", 平板可以用 "MarginNote (+ DeepL 插件)"). 如果实在不太习惯英文书, 可以用下方 "以前的入门书三选一" 里的书. **但记得看我附在书名后的短评!**

.. admonition:: 对第二版的书评
  :class: dropdown

  .. include:: swan_book_comment.irst

.. admonition:: 以前的入门书三选一
  :class: dropdown, dontread

  这三门书虽有各自的优点, 但已经被主推的入门书《Programming: Principles and Practice Using C++, 3rd Edition》完全爆杀.

  《Programming: Principles and Practice Using C++, 2nd Edition》(天鹅书, 个人译为《程序设计：使用C++的原理与实践（第2版）》, 译本错译为《C++程序设计：原理与实践（第2版）》) 
    .. hint::

      我为这本好书做了 **一个学习项目文件**: `为天鹅书第二版制作的学习项目文件 (解压以使用)`_, 解压后打开 "请读我" 文件查看使用说明 (例如需要安装 `Git: 通过官网下载`_).

    个人认为最好最优雅的编程入门书, 在原书 17 章之前一直没使用指针! 我的 C++ 传授、答疑、学习方法高度基于 :doc:`本书的第 0 章 </ppp2_chapter0>`.

    在第 0 章, 它会给出书籍配套的资源网站, 其中给出了部分示例代码、部分习题解答、更多参考资料、 `PPP Style Guide (天鹅书风格指南)`_ 等资源.

    目前有两个译本: 清华大学出版社的和机械工业出版社的. 清华大学出版社的 2024 年 7 月才出, **翻译反而更加糟糕, 建议用机械工业出版社的版本**. 但请注意机械工业出版社的中文版印刷导致了一些代码问题问题, 且自以为是地调换了章节顺序拆成了两本书, 把原本分为 4 部分的章节给打乱了 (见书本译者序), 导致如果完全自学不问别人会在初期配置环境时遇到问题.

    .. admonition:: 书评
      :class: dropdown

      .. include:: swan_book_comment.irst

  《C++ How to Program, 11th Edition》(《C++大学教程（第11版）》)
    必须用第11版及以后, 之前是垃圾书.

    从前言、目录和示例代码来看, 虽然有部分不足之处, 但已经非常依据现代 C++ 之哲学和最佳实践, 让我一度怀疑是不是换了作者: 它基于 C++20 版本, 并将新标准的各种特性融汇在初学者教学中, 直接在目录上强调并切实淡化了指针等 C 风格 C++ 内容, 如果不对现代 C++ 有一定理解是不能做到这种程度的.

    然而还是过于偏向语法和自底向上, 导致读者可能在能实际编程前就接受了大量底层细节的干扰.

  《C++ Primer, 5th Edition》
    很好的一本书, 但内容编排存在一定问题, 导致初学者用起来比较难.

------------------------------------------------------------------------------------------------------------------------
入门之后
------------------------------------------------------------------------------------------------------------------------

- 《A Tour of C++, 3rd Edition》(《C++之旅（第3版）》)

  - 中文翻译非常非常糟糕, 建议用英文 + DeepL 机翻.

  .. admonition:: 对翻译的书评
    :class: dropdown

    .. include:: a_tour_of_cpp_translation_comment.irst

- `Learning and Teaching Modern C++ - Bjarne Stroustrup - CppCon 2017`_
- 《The C++ Programming Language, 4th Edition》(《C++程序设计语言（第4版）》)

  - `配套习题 <https://www.stroustrup.com/4thExercises.pdf>`_

- 《Effective Modern C++》
- `105 STL Algorithms in Less Than an Hour - Jonathan Boccara - CppCon 2018`_
- `Stop Teaching C - Kate Gregory - CppCon 2015`_
- `C++ Seasoning - Sean Parent - GoingNative 2013`_
- `Simplicity: Not Just For Beginners - Kate Gregory - CppCon 2018`_
- `What Has My Compiler Done for Me Lately? Unbolting the Compiler's Lid - Matt Godbolt - CppCon 2017`_
- `Want fast C++? Know your hardware! - Timur Doumler - CppCon 2016`_
- `STL and Its Design Principles - Alexander Stepanov`_ (粗略感觉一遍, 到 :ref:`学习大纲_泛型编程` 再深入理解)

========================================================================================================================
工具链
========================================================================================================================

.. _`学习大纲_CMake`:

------------------------------------------------------------------------------------------------------------------------
终端使用
------------------------------------------------------------------------------------------------------------------------

- `计算机教育中缺失的一课 - 课程`_
- `计算机教育中缺失的一课 - 讲义`_
- `Learn Git Branching`_

------------------------------------------------------------------------------------------------------------------------
项目管理: CMake
------------------------------------------------------------------------------------------------------------------------

- 《Modern CMake for C++ - Discover a better approach to building, testing and packaging your software》
- `LLVM: A Modern, Open C++ Toolchain - Chandler Carruth - Pacific++ 2017`_
- `FeignClaims/cpp_conan_template`_
- `aminya/project_options`_
- `Effective CMake - Daniel Pfeifer - C++Now 2017`_
- `CMake 2022 C++ Modules and More - Bill Hoffman - CppNow 2022`_

.. admonition:: 更多推荐读物
  :class: dropdown

  .. include:: even_more_cmake.irst

------------------------------------------------------------------------------------------------------------------------
包管理: Conan
------------------------------------------------------------------------------------------------------------------------

- `Conan 2.0 Documentation`_
- `Adding Packages to ConanCenter`_
- `FeignClaims/cpp_conan_template`_
- `FeignClaims/customized_conan_recipes`_

------------------------------------------------------------------------------------------------------------------------
格式化工具: clang-format
------------------------------------------------------------------------------------------------------------------------

- `LLVM: A Modern, Open C++ Toolchain - Chandler Carruth - Pacific++ 2017`_
- `Clang-Format 官方文档`_
- `Clang-Format 配置选项列表`_
- `FeignClaims/cpp_conan_template`_
- `aminya/project_options`_
   
------------------------------------------------------------------------------------------------------------------------
静态检查工具: clang-tidy
------------------------------------------------------------------------------------------------------------------------

- `LLVM: A Modern, Open C++ Toolchain - Chandler Carruth - Pacific++ 2017`_
- `Clang-Tidy 官方文档`_
- `Clang-Tidy 诊断选项列表`_
- `FeignClaims/cpp_conan_template`_
- `aminya/project_options`_

========================================================================================================================
抽象思维
========================================================================================================================

- `Abstraction Patterns: Making Code Reliably Better Without Deep Understanding - Kate Gregory - ACCU 2022`_
- 《C++ Software Design - Design Principles and Patterns for High-Quality Software》
- `Inheritance Is The Base Class of Evil - Sean Parent - GoingNative 2013`_
- `SOLID, Revisited - Tony Van Eerd - CppNow 2021`_

.. _学习大纲_泛型编程:

========================================================================================================================
泛型编程
========================================================================================================================

- 《Functional Programming in C++ - How to improve your C++ programs using functional techniques》
- `《Efficient Programming with Components》`_
- `Better Algorithm Intuition - Conor Hoekstra @code_report - Meeting C++ 2019`_
- 《Elements of Programming》(《编程原本》)
- 《From Mathematics to Generic Programming》(《从数学到泛型编程》, 译本名为《数学与泛型编程：高效编程的奥秘》)
- 《Notes on Programming》
- `STL and Its Design Principles - Alexander Stepanov`_
- `Easy to Use, Hard to Misuse: Declarative Style in C++ - Ben Deane - CppCon 2018`_
- `Documentation in the Era of Concepts and Ranges - Christopher Di Bella & Sy Brand - CppCon 2021`_

========================================================================================================================
并发
========================================================================================================================

- `Cpu Caches and Why You Care - Scott Meyers - code::dive conference 2014`_
- 《C++ Concurrency in Action, 2nd Edition》前4章
- `Better Code: Concurrency - Sean Parent - NDC London 2017`_
- `atomic Weapons 1 of 2 - Herb Sutter - C++ and Beyond 2012`_
- `atomic Weapons 2 of 2 - Herb Sutter - C++ and Beyond 2012`_
- 《C++ Concurrency in Action, 2nd Edition》之后部分
- 《Concurrency with Modern C++》

========================================================================================================================
最佳实践
========================================================================================================================

- 《Effective Modern C++》
- 《Beautiful C++ - 30 Core Guidelines for Writing Clean, Safe, and Fast Code, 1st edition》
- 《C++ Best Practices》
- 《Embracing Modern C++ Safely》

- C++98

  - 《Effective C++ Digital Collection》

    - 《Effective C++》

    - 《More Effective C++》

    - 《Effective STL》

  - 《Exceptional C++ Collection》

    - 《Exceptional C++》

    - 《More Exceptional C++》

    - 《Exceptional C++ Style》

========================================================================================================================
深入语言
========================================================================================================================

显然, 这部分内容不是几个资料就能学全的 (其他部分也不是!), 因此此处仅选择了一些内容列出, 更多见于 :ref:`学习大纲_常用网站资源`.

- `Undefined Behavior is Not an Error - Barbara Geller & Ansel Sermersheim - CppCon 2018`_
- `Back to Basics: Move Semantics - Nicolai Josuttis - CppCon 2021`_
- 《C++ Move Semantics - The Complete Guide》
- 《The C++ Standard Library, 2nd Edition》by Nicolai M. Josuttis (《C++标准库（第2版）》)

  - `《The C++ Standard Library》补充章节`_

- 《C++17 - The Complete Guide》
- 《C++ Templates - The Complete Guide, 2nd Edition》
- `How C++20 Changes the Way We Write Code - Timur Doumler - CppCon 2020`_
- 《C++20 - The Complete Guide》
- `*(char*)0 = 0: What Does the C++ Programmer Intend With This Code? - JF Bastien - C++ on Sea 2023`_
- `Type punning in modern C++ - Timur Doumler - CppCon 2019`_
- `How C++23 Changes the Way We Write Code - Timur Doumler - CppCon 2022`_
- `An (In-)Complete Guide to C++ Object Lifetimes - Jonathan Müller - ACCU 2024`_
- 《C++ Lambda Story - Everything you need to know about Lambda Expressions in Modern C++》

========================================================================================================================
设计与演化
========================================================================================================================

- 《The Design and Evolution of C++》(《C++语言的设计与演化》)
- 《A History of C++ - 1979-1991》
- 《Evolving a Language in and for the Real World - C++ 1991-2006》
- 《Thriving in a crowded and changing world - C++ 2006-2020》

========================================================================================================================
扩展阅读
========================================================================================================================

难以分类和未分类的.

- 《Large-Scale C++ Volume I - Process and Architecture》
- 《The Art of Writing Efficient Programs》
- C++98

  - 《C++ In Action》
  - 《Inside the C++ Object Model》(《深度探索 C++ 对象模型》)
  - 《STL源码剖析》
  - 《C++ Template Metaprogramming - Concepts, Tools, and Techniques from Boost and Beyond》

========================================================================================================================
程序设计风格
========================================================================================================================

更多见于 :ref:`学习大纲_常用网站资源`.

- `PPP Style Guide (天鹅书风格指南)`_
- `C++ Core Guidelines (C++ 核心准则)`_
- `Guidelines For snake_case Concept Naming`_
- `Google C++ Style Guide`_
- `SEI CERT C++ Coding Standard`_
- `Chromium C++ style guide`_
- `High Integrity C++ Coding Standard`_
- `C++ Dos and Don'ts`_
- `Modern C++ use in Chromium`_
- `The Chromium Projects For Developers`_
