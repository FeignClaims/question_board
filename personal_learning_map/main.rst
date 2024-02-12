************************************************************************************************************************
个人学习大纲
************************************************************************************************************************

========================================================================================================================
使用提示
========================================================================================================================

先看 :ref:`学习大纲_基础` 之后随意.

阅读顺序上, :ref:`学习大纲_基础` 严格从上到下, 其他可以从上到下.

看书必须看前言, 技术书往往在前言写明了适用人群和阅读方法等.

========================================================================================================================
常用网络资源
========================================================================================================================

更多见于 `我的 C++ 浏览器书签 (右键另存为再导入到浏览器)`_.

- `cppreference`_; :doc:`/searching_method/main`.
- `How to Ask For C++ Coding Help <http://www.gregcons.com/KateBlog/HowToAskForCCodingHelp.aspx>`_
- `Bjarne Stroustrup's Homepage`_
- `Standard C++ <https://isocpp.org/>`_
- `C++ Core Guidelines`_

.. _学习大纲_基础:

========================================================================================================================
基础
========================================================================================================================

严格从上到下.

------------------------------------------------------------------------------------------------------------------------
入门三选一
------------------------------------------------------------------------------------------------------------------------

《Programming: Principles and Practices using C++, 2nd Edition》(《C++程序设计：原理与实践（第2版）》, 天鹅书) 
  - 个人认为最好最优雅的编程入门书, 在原书 17 章之前一直没使用指针! 我的 C++ 传授、答疑、学习方法高度基于 :doc:`本书的引言 </swan_preface>`.

    .. admonition:: 书评
      :class: dropdown

      .. include:: swan_book_comment.irst

  - 但中文版印刷存在问题, 且自以为是地调换了章节顺序拆成了两本书, 把原本分为 4 部分的章节给打乱了 (见书本译者序), 导致如果完全自学不问别人会在初期配置环境时遇到问题.
  - 为此我做了一个学习项目文件: `为天鹅书制作的学习项目文件 (解压以使用)`_. 任意支持 CMake 的软件均可使用该项目文件 (VSCode、Visual Studio、Qt Creator、CLion 等).

《C++ How to Program, 11th Edition》(《C++ 大学教程（第11版）》)
  - 必须用第11版及以后, 之前是垃圾书.
  - 从前言、目录和示例代码来看, 虽然有部分不足之处, 但已经非常依据现代 C++ 之哲学和最佳实践, 让我一度怀疑是不是换了作者.
  - 它基于 C++20 版本, 并将新标准的各种特性融汇在初学者教学中, 直接在目录上强调并切实淡化了指针等 C 风格 C++ 内容, 如果不对现代 C++ 有一定理解是不能做到这种程度的.
  - 然而还是过于偏向语法和自底向上, 导致读者可能在能实际编程前就接受了大量底层细节的干扰.

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

========================================================================================================================
工具链
========================================================================================================================

.. _`学习大纲_CMake`:

------------------------------------------------------------------------------------------------------------------------
项目管理: CMake
------------------------------------------------------------------------------------------------------------------------

- 《Modern CMake for C++ - Discover a better approach to building, testing and packaging your software》
- `LLVM: A Modern, Open C++ Toolchain - Chandler Carruth - Pacific++ 2017`_
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

------------------------------------------------------------------------------------------------------------------------
格式化工具: clang-format
------------------------------------------------------------------------------------------------------------------------

- `LLVM: A Modern, Open C++ Toolchain - Chandler Carruth - Pacific++ 2017`_
- `Clang-Format 官方文档`_
- `Clang-Format 配置选项列表`_
- `aminya/project_options`_
   
------------------------------------------------------------------------------------------------------------------------
静态检查工具: clang-tidy
------------------------------------------------------------------------------------------------------------------------

- `LLVM: A Modern, Open C++ Toolchain - Chandler Carruth - Pacific++ 2017`_
- `Clang-Tidy 官方文档`_
- `Clang-Tidy 诊断选项列表`_
- `aminya/project_options`_

========================================================================================================================
抽象思维
========================================================================================================================

- `Abstraction Patterns: Making Code Reliably Better Without Deep Understanding - Kate Gregory - ACCU 2022`_
- `What Has My Compiler Done for Me Lately? Unbolting the Compiler's Lid - Matt Godbolt - CppCon 2017`_
- 《C++ Software Design - Design Principles and Patterns for High-Quality Software》
- `Inheritance Is The Base Class of Evil - Sean Parent - GoingNative 2013`_
- `SOLID, Revisited - Tony Van Eerd - CppNow 2021`_

.. _学习大纲_泛型编程:

========================================================================================================================
泛型编程
========================================================================================================================

- 《Functional Programming in C++ - How to improve your C++ programs using functional techniques》
- `Easy to Use, Hard to Misuse: Declarative Style in C++ - Ben Deane - CppCon 2018`_
- `Documentation in the Era of Concepts and Ranges - Christopher Di Bella & Sy Brand - CppCon 2021`_
- `Better Algorithm Intuition - Conor Hoekstra @code_report - Meeting C++ 2019`_
- `STL and Its Design Principles - Alexander Stepanov`_
- 《Elements of Programming》(《编程原本》)
- 《From Mathematics to Generic Programming》(《从数学到泛型编程》)
- `《Efficient Programming with Components》`_

========================================================================================================================
并发
========================================================================================================================

- 《C++ Concurrency in Action, 2nd Edition》前4章
- `Better Code: Concurrency - Sean Parent - NDC London 2017`_
- `atomic Weapons 1 of 2 - Herb Sutter - C++ and Beyond 2012`_
- `atomic Weapons 2 of 2 - Herb Sutter - C++ and Beyond 2012`_
- 《C++ Concurrency in Action, 2nd Edition》之后部分
- 《Concurrency with Modern C++》

========================================================================================================================
最佳实践
========================================================================================================================

- 《C++ Best Practices》
- 《Effective C++ Digital Collection》

  - 《Effective C++》

  - 《More Effective C++》

  - 《Effective STL》

- 《Effective Modern C++》
- 《Exceptional C++ Collection》

  - 《Exceptional C++》

  - 《More Exceptional C++》

  - 《Exceptional C++ Style》

- 《Beautiful C++ - 30 Core Guidelines for Writing Clean, Safe, and Fast Code, 1st edition》
- 《Embracing Modern C++ Safely》

========================================================================================================================
深入语言
========================================================================================================================

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
- `How C++23 Changes the Way We Write Code - Timur Doumler - CppCon 2022`_
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
- 《Notes on Programming》
- 《The Art of Writing Efficient Programs》
- C++98

  - 《C++ In Action》
  - 《Inside the C++ Object Model》(《深度探索 C++ 对象模型》)
  - 《STL源码剖析》
  - 《C++ Template Metaprogramming - Concepts, Tools, and Techniques from Boost and Beyond》

========================================================================================================================
编码风格
========================================================================================================================

- `Guidelines For snake_case Concept Naming`_
- `C++ Core Guidelines`_
- `Google C++ Style Guide`_
- `SEI CERT C++ Coding Standard`_
- `Chromium C++ style guide`_
- `High Integrity C++ Coding Standard`_
- `C++ Dos and Don'ts`_
- `Modern C++ use in Chromium`_
- `The Chromium Projects For Developers`_