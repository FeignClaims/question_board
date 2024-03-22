************************************************************************************************************************
copy-and-swap: 拷贝赋值函数的简单实现
************************************************************************************************************************

首先明确一点: :doc:`如果没有必要定义拷贝构造函数/拷贝赋值函数/析构函数, 就不要定义 </faq/rule_of_350/main>`, 让编译器为你声明甚至定义.

如果有定义的需求, 且拷贝仅仅是拷贝, 不是因为题目而有输出之类的特殊要求, 则可以先定义拷贝构造函数、析构函数, 然后利用它们定义拷贝赋值函数, 这称为 copy-and-swap 惯用法.

.. code-block:: cpp
  :linenos:
  :caption: 拷贝赋值函数

  Widget& operator=(Widget const& other) {
    Widget temp(other);  // 拷贝 other 到 temp
    swap(*this, temp);   // 交换 temp 和 *this 的内容; 该函数怎么来的见下文
    return *this;
  }  // temp 的析构函数将会对交换来的 *this 内容完成必要的清理

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`swap` 函数

  // 如果是 C++11 及以后, 加上 noexcept 表示不会抛出异常 ↓
  friend void swap(Widget& lhs, Widget& rhs) noexcept {
    /* 交换 lhs 和 rhs 的所有成员 */
  }

.. hint::

  注意到, 这样一来没有必要判断自赋值情况 :cpp:`widget = widget`——自赋值单纯就是得到一份自己的拷贝, 然后与该拷贝发生交换, 最终得到内容仍然是自己.

.. admonition:: 相关核心准则
  :class: coreguidelines

  - :coreguidelines:`C.22: 让特殊函数保持一致 <c22-make-default-operations-consistent>`
  - :coreguidelines:`C.60: 拷贝赋值函数应该是非虚函数, 按 const& 传参, 并按 & 返回自身 <c60-make-copy-assignment-non-virtual-take-the-parameter-by-const-and-return-by-non-const>`

========================================================================================================================
示例
========================================================================================================================

:godbolt:`fjcjKMGce`

.. literalinclude:: main.cpp
  :language: cpp
  :linenos:
