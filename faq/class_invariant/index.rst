.. _invariant:

************************************************************************************************************************
不变式: 类和结构体的区别 (class invariant)
************************************************************************************************************************

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/struct`

类 (:cpp:`class`) 和结构体 (:cpp:`struct`) 到底有什么区别? 

从语法上, 它们没有区别, 写 :cpp:`struct Widget` 或者 :cpp:`class Widget` 都是自定义了类型 :cpp:`Widget`.

那么为什么要专门分成两个关键词呢? 这就要引入 C++ 的一个核心概念, **类的不变式 (class invariant)**.

========================================================================================================================
示例: 最简分式
========================================================================================================================

`C++ Core Guidelines (C++ 核心准则)`_ 将不变式定义为 "程序某一时刻或某一段时间里必须得到满足的条件", 对于类而言, 就是 **类的数据成员自己和之间的逻辑关系**.

例如我们打算实现最简分式类, 则根据最简分式的数学定义, 可以将分子、分母作为数据成员, 并且分子分母应该满足下列关系:

- 分子和分母之间不应该具有除 1 以外的公因数.
- 分母不为 0.

------------------------------------------------------------------------------------------------------------------------
最简分式结构体
------------------------------------------------------------------------------------------------------------------------

假如我们将该类型作为一个结构体, 按照结构体的习惯, 将分子分母作为公用 (:cpp:`public`) 数据成员, 可以简单地实现为以下代码:

.. code-block:: cpp
  :linenos:

  struct Irreducible_fraction {
   public:
    int numerator;    // 分子
    int denominator;  // 分母
  };

完成了!

可是, 如何保证使用者不破坏 "最简分式" 的定义? 他可以对数据成员做任何事!

.. code-block:: cpp
  :linenos:

  int main() {
    Irreducible_fraction fraction1 = {1, 3};  // 1/3, 是最简分式
    fraction1.numerator             = 3;       // 3/3, 分子和分母之间有公因数 3, 这不是最简分式!
    fraction1.denominator           = 0;       // 3/0, 分母为 0, 这不是最简分式!

    Irreducible_fraction fraction2 = {3, 3};  // 3/3, 从构造起就不是最简分式了!
  }

使用者为什么要破坏我们的最简分式? 因为我们让分子分母是公用数据成员, 而公用就是开放给他们任意使用的.

------------------------------------------------------------------------------------------------------------------------
阻止使用者破坏最简分式
------------------------------------------------------------------------------------------------------------------------

上面的例子中, 使用者有两处地方可以破坏我们的最简分式:

- 对象构造时: :cpp:`Irreducible_fraction fraction2 = {3, 3};`. 这意味着我们应该规定如何构造对象——我们应该定义构造函数.
- 对象使用时: :cpp:`fraction1.numerator = 3;`. 这意味着我们应该规定如何使用对象——我们应该将数据设为私用成员 (:cpp:`private`), 用公用成员函数告知使用者应该怎么访问.

即,

.. literalinclude:: class.cpp
  :language: cpp
  :linenos:

------------------------------------------------------------------------------------------------------------------------
最简分式类
------------------------------------------------------------------------------------------------------------------------

C++ 因此特意引入了新的关键字 :cpp:`class`, 当使用关键字 :cpp:`class`, 我们就是在告诉未来的代码读者 (可能是别人, 也可能是你自己) 这个类具有不变式.

.. code-block:: cpp
  :linenos:

  // ↓使用 class 而非 struct, 语法上没有任何区别, 但告诉读者这个类具有不变式
  class Irreducible_fraction {
    /* 与上面的代码完全相同 */
  };

综上所述, :cpp:`class` 和 :cpp:`struct` 在语法上没有区别, 我们基于语义上有无不变式来进行选择:

- 如果有不变式, 使用 :cpp:`class` 而非 :cpp:`struct`.
- 如果有不变式, 则需要使用构造函数来建立不变式.
- 如果有不变式, 则默认的拷贝行为可能无法维护该不变式, 我们也许需要自定义拷贝构造/赋值函数和析构函数.
- 如果有不变式, 则需要将数据设为私用并定义公用成员函数, 从而限制使用者如何使用.

因为类存在不变式, 才有了构造函数、拷贝构造/赋值函数、析构函数, 才有了公用、私用等访问说明, 才有了成员函数…… **理解了类的不变式, 就能据此推导理解类的其他特性**.

========================================================================================================================
语法上的区别
========================================================================================================================

虽然前面一直说 :cpp:`class` 和 :cpp:`struct` 在语法上没有区别, 但还有细微的差异:

- :cpp:`class` 默认访问说明符为 :cpp:`private`, 这其实隐含了它应该将数据设为私用, 即拥有不变式.
- :cpp:`struct` 默认访问说明符为 :cpp:`public`, 这其实隐含了它应该将数据设为公用, 即没有不变式.

但干嘛要记忆这种默认如何如何呢? 不直接写明访问说明符是啥就好了!

.. code-block:: cpp
  :linenos:

  struct Widget {
   public:  // 管它默认是什么, 我直接写明不就好了
  };

所以这里说 :cpp:`class` 和 :cpp:`struct` 在语法上没有区别, 唯一的区分在于是否有不变式.

========================================================================================================================
最佳实践
========================================================================================================================

如果类具有不变式, 则使用 :cpp:`class`; 如果数据成员相互独立, 则使用 :cpp:`struct`. 即,

- 要么 :cpp:`class` + 构造函数 (+ 私用数据成员).
- 要么 :cpp:`struct` + 无构造函数 (+ 公用数据成员).

.. admonition:: 相关核心准则
  :class: coreguidelines

  - :doc:`/faq/coreguidelines/c_2`
  - :doc:`/faq/coreguidelines/c_40`

========================================================================================================================
一个教学的黑点
========================================================================================================================

教学里完全没有不变式这个知识点: "这是类的语法, 这是我们怎么定义构造函数, 这是我们怎么定义成员函数, 这是公用私用的区别……", 但从来不会解释为什么要有这些.
