************************************************************************************************************************
实例化: 对类模板写友元函数出现问题? (instantiation)
************************************************************************************************************************

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/template`

========================================================================================================================
解决方案 1: 在类内定义友元函数
========================================================================================================================

请重新阅读 :doc:`/faq/basic_concepts/operator_overloading`, 尤其注意最佳实践中对于友元函数怎么定义的建议 (当然那里是针对运算符重载说的).

========================================================================================================================
问题
========================================================================================================================

.. literalinclude:: problem.cpp
  :language: cpp
  :linenos:
  :caption: 问题代码

这段代码不能通过编译, Visual Studio 会说有 "无法解析的外部符号", 其他软件可能提示类似下面的内容:

.. code-block:: text
  :linenos:

  Undefined symbols for architecture arm64:
    "function(Widget<int>)", referenced from:
        _main in main.cpp.o
  ld: symbol(s) not found for architecture arm64

问题在于, 在类内声明的友元函数 :cpp:`function` 和类外定义的函数模板 :cpp:`function` 是两个不同的函数: 我们并没有定义那个友元函数.

写出这样的代码反映出对模板的理解存在偏差.

========================================================================================================================
解释
========================================================================================================================

类模板不是类: 类模板作为偏正短语, "类" 是修饰语, 而 "模板" 才是中心语.

我们编写了类模板 :cpp:`template <typename T> class Widget` 后, 会以 :cpp:`Widget<int>` 的形式使用它. 在编译时, 编译器将会从类模板的代码生成对应的类的代码, 因而有了我们所使用的 :cpp:`Widget<int>` 类. 而这个从类模板代码生成类代码的过程称为实例化 (instantiation).

.. code-block:: cpp
  :linenos:

  template <typename T>
  class Widget {
   public:
    Widget<T>() {}
  };

  int main() {
    Widget<int> widget1;     // 实例化为 Widget<int>
    Widget<double> widget2;  // 实例化为 Widget<double>
  }

注意到, 我在第 4 行定义构造函数时写明了 :cpp:`Widget<T>`. 这是根据实例化可推断出的写法: 类模板最终会根据给它的模板参数实例化, 那么我们在定义类模板时, 自然可以假装我们在写 :cpp:`Widget<T>`.

此外, 类模板最终 **仅** 会根据它的模板参数实例化, 因此即便我们在类内不写明 :cpp:`Widget<T>` 而写 :cpp:`Widget`, 也是在指最终通过实例化得到的类 :cpp:`Widget<T>`:

.. code-block:: cpp
  :linenos:

  template <typename T>
  class Widget {
   public:
    // ↓ 这也是指最终用模板参数 T 实例化得到的 Widget<T>
    Widget() {}
  };

  int main() {
    Widget<int> widget1;     // 第 5 行指的是 Widget<int>
    Widget<double> widget2;  // 第 5 行指的是 Widget<double>
  }

由此回顾之前的问题代码, 将模板参数 T 显式写出来:

.. code-block:: cpp
  :emphasize-lines: 6
  :linenos:

  template <typename T>
  class Widget {
   public:
    Widget<T>(T value) : value_(value) {}

    friend void function(Widget<T> widget);

   private:
    T value_;
  };

我们并不是让一个函数模板作为友元函数, 而是 **分别地**,

- 让 :cpp:`void function(Widget<int> widget)` 作为 :cpp:`Widget<int>` 的友元函数;
- 让 :cpp:`void function(Widget<double> widget)` 作为 :cpp:`Widget<double>` 的友元函数!

然而我们之前是尝试怎样定义它们? 我们以为它们是一个函数模板, 在类外以函数模板的形式定义它们:

.. code-block:: cpp
  :linenos:

  // 这不是 Widget 里声明的友元函数!
  template <typename T>
  void function(Widget<T> widget) {
    std::cout << widget.value_;
  }

"等等, 如果它不是我所声明的友元函数, 为什么我在它里面用私用数据成员 :cpp:`widget.value_` 没有报错?" 因为你没有实例化这个函数模板. 前面说过, 我们使用模板时, 是由编译器通过模板实例化出了我们实际的代码, 那么既然我们没使用这个模板, 编译器又何必费力去实例化它呢?

这是件坏事
  这意味着我们很难知道模板出错了. 甚至哪怕模板被实例化, 由于它不得不发生在编译晚期, 软件很难在不编译的情况下就检测出它的错误.

这更是件好事
  这意味着我们无需为自己没有使用的代码付出代价.

  它还使模板有了应用的可能. 例如, 还记得我们为什么要进行运算符重载吗? 一个原因是为了让自定义类型支持加减乘除:

  .. code-block:: cpp
    :linenos:

    template <typename T>
    T square(T value) {
      return value * value;
    }

  如果编译器贪婪地检查所有模板, 我们将不能定义任何模板.

此外, 虽然不同的类型 :cpp:`T` 和 :cpp:`U` 都可以由类模板 :cpp:`Widget` 实例化为 :cpp:`Widget<T>` 和 :cpp:`Widget<U>`, 但实例化得到的类 :cpp:`Widget<T>` 和 :cpp:`Widget<U>` 之间并无关系: 它们的实例化过程是独立地使用不同组模板参数, 且类模板代码里也没有定义它们之间的联系.

那该如何定义它们之间的联系呢? 我们现在的问题是, :cpp:`template <typename T> class Widget` 只在类里有 :cpp:`Widget<T>` 这一个类, 而我们需要在类里用 :cpp:`Widget<U>` 表达另一个类进而让 :cpp:`Widget<T>` 和 :cpp:`Widget<U>` 之间产生联系. 也就是说, 我们需要在定义 :cpp:`Widget<T>` 时引入另一组模板参数 :cpp:`U` 到类中.

这太绕了! **但别害怕.** 前面说过, "类模板最终会根据给它的模板参数实例化, 那么我们在定义类模板时, 自然可以假装我们在写 :cpp:`Widget<T>`". 换而言之, 我们可以假装 :cpp:`Widget<T>` 已经实例化出来了, 叫做 :cpp:`class Other`, 而我们需要在 :cpp:`Other` 类中引入一组模板参数 :cpp:`U` 用于表达 :cpp:`Other` 和 :cpp:`Widget<U>` 之间的联系.

我们可以用函数模板:

.. code-block:: cpp
  :linenos:

  template <typename T>
  class Widget;

  //    ↓ 假设这就是我们的 Widget<T>
  class Other {
   public:
    template <typename U>
    void add(Other lhs, Widget<U> rhs) {
      /* ... */
    }
  };

现在把 :cpp:`class Other` 替换回 :cpp:`class Widget<T>`.

.. code-block:: cpp
  :linenos:

  template <typename T>
  class Widget {
   public:
    template <typename U>
    void add(Widget<T> lhs, Widget<U> rhs) {
      /* ... */
    }
  };

  int main() {
    Widget<int> widget1;
    Widget<double> widget2;

    add(widget1, widget1);  // 正确
    add(widget1, widget2);  // 正确
    add(widget2, widget1);  // 正确
    add(widget2, widget2);  // 正确
  }

========================================================================================================================
解决方案 2: 让友元函数是函数模板
========================================================================================================================

由此有了问题的第二个解决方案: 让友元函数是函数模板.

.. literalinclude:: solution_2.cpp
  :emphasize-lines: 8
  :language: cpp
  :linenos:

========================================================================================================================
不算解决方案的解决方案: 定义每个友元函数
========================================================================================================================

既然问题中的 :cpp:`Widget<int>`、:cpp:`Widget<double>` 等是分别以 :cpp:`void function(Widget<int>)`、:cpp:`void function(Widget<double>)` 等为友元函数, 那我们当然能分别定义它们:

.. literalinclude:: solution_3.cpp
  :emphasize-lines: 14
  :language: cpp
  :linenos:
  :caption: 问题代码
