************************************************************************************************************************
虚函数调用的感性理解
************************************************************************************************************************

========================================================================================================================
静态类型和动态类型
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
静态类型
------------------------------------------------------------------------------------------------------------------------

通过分析表达式本身即可确定的类型称为静态类型 (static type), 它跟程序的执行无关.

.. code-block:: cpp
  :linenos:

  int value;             // value 的类型是 int
  int array[5];          // array 的类型是 int[5]
  int* pointer = array;  // pointer 的类型是 int*
  *pointer     = 0;      // *pointer 的类型是 int&

------------------------------------------------------------------------------------------------------------------------
动态类型
------------------------------------------------------------------------------------------------------------------------

引用、指针实际引用的类型称为动态类型 (dynamic type).

当不涉及继承和类层次时, 动态类型通常与静态类型相同.

.. code-block:: cpp
  :linenos:

  int value;
  int& reference = value;   // reference 的静态、动态类型均为 int&
  int* pointer   = &value;  // pointer 的类型是 int*
  *pointer       = 0;       // *pointer 的静态、动态类型均为 int&

但类层次的基类引用和指针可以引用派生类对象, 则动态类型会根据程序执行而变化.

.. code-block:: cpp
  :linenos:

  class A {};
  class B : public A {};

  A a;
  B b;

  A& reference = b;  // reference 的静态类型是 A&, 动态类型是 B&

  A* pointer = &a;   // pointer 的类型是 A*
                     // *pointer 的静态类型是 A&, 动态类型是 A&

  pointer = &b;      // pointer 的类型是 A*
                     // *pointer 的静态类型是 A&, 动态类型是 B&

========================================================================================================================
成员函数的调用
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
成员函数的隐藏参数
------------------------------------------------------------------------------------------------------------------------

一个类可以创建出多个对象, 但成员函数只有一个.
那么当对象调用成员函数时, 成员函数是如何确定对应于哪个对象的?

例如下面的代码中, :cpp:`Widget::print()` 如何知道 :cpp:`value_` 是对应于 :cpp:`a` 对象而非 :cpp:`b` 对象?

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    void set_value(int value) {
      value_ = value;
    }
    void print() const {
      std::cout << value_;
    }

   private:
    int value_;
  };

  int main() {
    Widget a;
    Widget b;
    a.set_value(1);  // 设置 a.value_ 而不是 b.value_
    a.print();       // 输出 a.value_ 而不是 b.value_
  }

事实上成员函数将对象作为隐藏参数传入, 而这个参数就是课上提及的 :cpp:`this` 指针.

.. code-block:: cpp
  :emphasize-lines: 3, 6
  :linenos:

  class Widget {
   public:
    void set_value(Widget* this, int value) {
      (*this).value_ = value;
    }
    void print(Widget const* this) {  // const 成员函数对应于 const 传参
      std::cout << (*this).value_;
    }

   private:
    int value_;
  };

为了便于分析理解, 我之后将采用 C++23 的显式对象参数 (explicit object parameter) 语法, 写明对象是如何传入成员函数中的.

.. code-block:: cpp
  :emphasize-lines: 3, 6
  :linenos:

  class Widget {
   public:
    void set_value(this Widget& self, int value) {
      self.value_ = value;
    }
    void print(this Widget const& self) {
      std::cout << self.value_;
    }

   private:
    int value_;
  };

------------------------------------------------------------------------------------------------------------------------
可供调用的成员函数
------------------------------------------------------------------------------------------------------------------------

当对象进行函数调用时, 可见 (visible) 的成员函数 **由静态类型确定**.

.. margin::

  :cpp:`override` 显式表示该函数重写了一个虚函数, 如果没有重写会报错. 使用这个关键词可以避免明明是打算重写虚函数, 却因为手误写了一个新函数的情况.

.. code-block:: cpp
  :linenos:

  class A {
   public:
    void f(this A&, int value);
    void f(this A&);
    virtual void g(this A&);
  };

  class B : public A {
   private:
    void f(this B&);
    void g(this B&) override;
  };

  class C : public B {
   public:
    void f(this C&);
  };

对于上面的代码, 我们可以画出各个类的可见信息图, 继承在图中表现为嵌套关系:

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`class A`

  class A {
    public: void f(this A&, int value);
    public: void f(this A&);
    public: virtual void g(this A&);
  }

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`class B`

  class A {
    public: void f(this A&, int value);
    public: void f(this A&);
    public: virtual void g(this A&);

    public: class B {
      private: void f(this B&);
      private: void g(this B&) override;
    }
  }

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`class C`

  class A {
    public: void f(this A&, int value);
    public: void f(this A&);
    public: virtual void g(this A&);

    public: class B {
      private: void f(this B&);
      private: void g(this B&) override;

      public: class C {
        public: void f(this C&);
      }
    }
  }

应该注意到, 基类中所有内容对于派生类都是可见的, :cpp:`public` 和 :cpp:`private` 等称为访问控制, 并不影响可见性.

当进行函数调用时, 对象通过可见函数找到最合适的函数, **之后再确认函数是否可访问 (accessible)**.

------------------------------------------------------------------------------------------------------------------------
非虚成员函数的调用
------------------------------------------------------------------------------------------------------------------------

对于非虚成员函数, 对象根据 **静态类型** 的可见信息图找到 *最合适的函数* 和 *确定可达性*:

.. code-block:: cpp
  :linenos:
  :caption: 静态类型 :cpp:`A` 调用非虚成员函数 :cpp:`f()`

  class A {
    public: void f(this A&, int value);
    public: void f(this A&);
    public: virtual void g(this A&);
  }

  C c;
  A& a = c;
  a.f();    // 静态信息为 A&, 找到 A::f
  a.f(10);  // 静态信息为 A&, 找到 A::f

如果存在名字一样的函数, 只会查找最内层的函数:

.. code-block:: cpp
  :linenos:
  :caption: 静态类型 :cpp:`C` 调用非虚成员函数 :cpp:`f()`

  class A {
    // public: void f(this A&, int value);
    // public: void f(this A&);
    // public: virtual void g(this A&);

    public: class B {
      // private: void f(this B&);
      private: void g(this B&) override;

      public: class C {
        public: void f(this C&);
      }
    }
  }

  C c;
  c.f();    // 静态信息为 C&, 找到 C::f
  c.f(10);  // 静态信息为 C&, 错误: 未找到对应的函数

需要注意的是, 是找到最合适的函数后, 再确认函数是否可访问. **如果不可访问则调用直接失败, 而不会继续查找**:

.. code-block:: cpp
  :linenos:
  :caption: 静态类型 :cpp:`B` 调用非虚成员函数 :cpp:`f()`

  class A {
    // public: void f(this A&, int value);
    // public: void f(this A&);
    // public: virtual void g(this A&);

    public: class B {
      private: void f(this B&);
      private: void g(this B&) override;
    }
  }

  B b;
  b.f();  // 找到 B:f,
          // 它处于 private 中, 不可访问, 故调用失败

------------------------------------------------------------------------------------------------------------------------
虚成员函数的调用
------------------------------------------------------------------------------------------------------------------------

对于虚成员函数, 对象同样根据 **静态类型** 的可见信息图找到 *最合适的函数* 和 *确定可达性*:

.. code-block:: cpp
  :linenos:
  :caption: 静态类型 :cpp:`A` 调用虚成员函数 :cpp:`g()`

  class A {
    public: void f(this A&, int value);
    public: void f(this A&);
    public: virtual void g(this A&);
  }

  A a;
  a.g();  // 找到 A::g

.. code-block:: cpp
  :linenos:
  :caption: 静态类型 :cpp:`B` 调用虚成员函数 :cpp:`g()`

  class A {
    // public: void f(this A&, int value);
    // public: void f(this A&);
    // public: virtual void g(this A&);

    public: class B {
      private: void f(this B&);
      private: void g(this B&) override;
    }
  }

  B b;
  b.g();  // 找到 B::g, 不可访问, 故调用失败

区别在于当虚成员函数发生调用时, 将会根据动态类型的可见信息图找到对应的重写函数, 对它进行实际调用:

.. code-block:: cpp
  :linenos:
  :caption: (静态类型 :cpp:`A`, 动态类型 :cpp:`B`) 调用虚成员函数 :cpp:`g()`

  class A {
    public: void f(this A&, int value);
    public: void f(this A&);
    public: virtual void g(this A&);
  }

  class A {
    // public: void f(this A&, int value);
    // public: void f(this A&);
    // public: virtual void g(this A&);

    public: class B {
      private: void f(this B&);
      private: void g(this B&) override;
    }
  }

  B b;
  A& a = b;
  a.g();  // 根据静态类型 A 找到虚成员函数 A::g, 它是可以访问的, 故调用成功
          // 根据动态类型 B 找到最内层的重写函数 B::g, 发生实际调用

注意对象在成员函数内的静态类型:

.. code-block:: cpp
  :linenos:

  class Base {
   public:
    void f(this Base& self) {
      std::cout << "Base::f()\n";
    }
    virtual void g(this Base& self) {
      std::cout << "Base::g()\n";
      self.f();
    }
  };

  class Derived : public Base {
   public:
    void f(this Derived& self) {
      std::cout << "Derived::f()\n";
    }
    void g(this Derived& self) override {
      std::cout <<faq "Derived::g()\n";
      self.f();  // 注意看显式对象参数 self, 此时静态类型是 Derived&!
    }
  };

  Derived derived;
  Base& reference = derived;
  reference.g();  // 调用 Derived::g

------------------------------------------------------------------------------------------------------------------------
习题
------------------------------------------------------------------------------------------------------------------------

这是本问题提问人 `实际询问的问题 <https://gitee.com/cpp_tutorial/question/issues/I7ARBT>`_, 此处作为习题提供来验证理解.

.. literalinclude:: exercise.cpp
  :language: cpp
  :linenos:

.. admonition:: 点此查看答案
  :class: dropdown

  :godbolt:`4WMx8YTWa`

  由于 :cpp:`A a` 动态类型已经是基类 :cpp:`A`, 所有函数都调用 :cpp:`A` 中的. 而 :cpp:`B b` 经历如下调用,

  37 行 :cpp:`b.fun1()`
    静态类型为 :cpp:`B&`, 查找到虚函数 :cpp:`A::fun1()`, 基于动态类型 :cpp:`B&` 调用 :cpp:`A::fun1()`.

  7 行 :cpp:`fun2()`
    静态类型为 :cpp:`A&`, 查找到非虚函数 :cpp:`A::fun2()`, 直接调用 :cpp:`A::fun2()`.

  11 行 :cpp:`fun3()`
    静态类型为 :cpp:`A&`, 查找到虚函数 :cpp:`A::fun3()`, 基于动态类型 :cpp:`B&` 调用 :cpp:`B::fun3()`.

  26 行 :cpp:`fun4()`
    静态类型为 :cpp:`B&`, 查找到非虚函数 :cpp:`B::fun4()`, 直接调用 :cpp:`B::fun4()`.

  .. code-block:: text
    :linenos:

    A::fun1 
    A::fun2 
    A::fun3 
    A::fun4 
    A::fun1 
    A::fun2 
    B::fun3 
    B::fun4

.. _虚函数调用的感性理解_强制使用成员函数:

========================================================================================================================
强制使用成员函数
========================================================================================================================

有时我们需要在派生类中明确调用基类或派生类的函数, 则应该对查找范围进行限定:

.. code-block:: cpp
  :emphasize-lines: 11
  :linenos:

  class Base {
   public:
    void f(this Base& self);
    virtual void g(this Base& self);
  };

  class Derived : public Base {
   public:
    void f(this Derived& self);
    void g(this Derived& self) override {
      self.Base::f();
    }
  };

有时我们想让派生类沿用基类的函数, 同时又定义新的同名函数, 则可以使用 :cpp:`using` 声明引入基类函数:

.. code-block:: cpp
  :emphasize-lines: 8
  :linenos:

  class Base {
   public:
    void f(this Base& self, int value);
  };

  class Derived : public Base {
   public:
    using Base::f;  // 引入 Base::f
    void f(this Derived& self);
  };

========================================================================================================================
类层次与虚析构函数
========================================================================================================================

类层次的一种用法是, 通过 :cpp:`new` 获取堆内存 :doc:`资源 </faq/basic_concepts/resource>` 并构造一个对象, 当使用完毕后, 通过 :cpp:`delete` 调用析构函数并释放堆内存资源.

.. code-block:: cpp
  :linenos:

  int* owner = new int;
  delete owner;

如果将基类的析构函数作为公用非虚函数, 将会发生什么?

.. code-block:: cpp
  :linenos:

  class Base {
   public:
    ~Base() {}
  };
  class Derived : public Base {
   public:
    ~Derived() {}
  };

  Base* base = new Derived();
  delete base;  // 释放资源, 将会调用 Base::~Base();

上面的代码中 :cpp:`base*` 指向了一个派生类 :cpp:`Derived` 对象, 并具有该对象的所有权, 这个对象存在以下信息:

.. code-block:: cpp
  :linenos:

  class Base {
    /* Base 的信息 */
    class Derived {
      /* Derived 的信息 */
    }
  }

但释放时基于静态类型调用析构函数 :cpp:`Base::~Base()`, 仅仅对 :cpp:`Base` 部分进行析构:

.. code-block:: cpp
  :linenos:

  class Derived {
    /* Derived 的信息 */
  }

我们最终泄露了 :cpp:`Derived` 部分的内存. 更可怕的是这实际上是未定义行为, 程序可以做任何事, 甚至炸掉你的电脑!

------------------------------------------------------------------------------------------------------------------------
将析构函数作为公用虚函数
------------------------------------------------------------------------------------------------------------------------

我们可以将析构函数定义为公用虚函数, 使基类指针 :cpp:`delete` 正确调用 :cpp:`Derived::~Derived()`.

.. code-block:: cpp
  :linenos:

  class Base {
   public:
    virtual ~Base() {}
  };
  class Derived : public Base {
   public:
    ~Derived() override {}
  };

  Base* base = new Derived();
  delete base;  // 释放资源, 将会调用 Derived::~Derived();

当然由于基类已经是虚函数, 派生类中默认生成的析构函数就会是对它的重写.

.. code-block:: cpp
  :linenos:

  class Base {
   public:
    virtual ~Base() {}
  };
  class Derived : public Base {};

  Base* base = new Derived();
  delete base;  // 释放资源, 将会调用 Derived::~Derived();

------------------------------------------------------------------------------------------------------------------------
将析构函数作为保护用非虚函数
------------------------------------------------------------------------------------------------------------------------

我们可以将析构函数定义为保护用非虚函数, 由于析构函数被设置为保护, 用户将无法访问 :cpp:`Base` 的析构函数.

.. code-block:: cpp
  :linenos:

  class Base {
   protected:
    ~Base() {}
  };
  class Derived : public Base {};

  Derived* derived = new Derived();
  Base* base       = derived;
  delete base;     // 错误: 不能调用保护用的析构函数
  delete derived;  // 正确

.. admonition:: 相关核心准则

  - :coreguidelines:`C.35: 基类的析构函数要么是公用虚函数, 要么是保护用非虚函数 <c35-a-base-class-destructor-should-be-either-public-and-virtual-or-protected-and-non-virtual>`
  - :coreguidelines:`C.127: 具有虚函数的类应该有一个公用虚析构函数或一个保护非虚析构函数 <c127-a-class-with-a-virtual-function-should-have-a-virtual-or-protected-destructor>`

.. _虚函数调用的感性理解_类层次与构造函数、析构函数:

========================================================================================================================
类层次与构造函数、析构函数
========================================================================================================================

对象在构造函数中时, 本层的信息正在被构造, 只有上一层才具有完整的类型信息.

.. margin::

  如果需要显式定义默认构造函数, 最好应该使用 :cpp:`= default;` 而不是空括号, 见于 :doc:`/faq/rule_of_350/main`

.. code-block:: cpp
  :emphasize-lines: 14
  :linenos:

  class Base {
   public:
    Base() {}

    virtual void f() {
      std::cout << "Base::f()\n";
    }
  };
  class Derived : public Base {
   public:
    Derived() : Base()  // 调用 Base 的构造函数, 此后 Base 的信息构造完全
    {
      /* 构造函数内 Derived 的信息正在被构造 */
      f();  // 将会调用 Base::f();
    }

    void f() override {
      std::cout << "Derived::f()\n";
    }
  };

对象在析构函数中时, 本层的信息正在被析构, 只有上一层才具有完整的类型信息.

.. margin::

  如果需要显式定义默认析构函数, 最好应该使用 :cpp:`= default;` 而不是空括号, 见于 :doc:`/faq/rule_of_350/main`

.. code-block:: cpp
  :emphasize-lines: 13
  :linenos:

  class Base {
   public:
    ~Base();

    virtual void f() {
      std::cout << "Base::f()\n";
    }
  };
  class Derived : public Base {
   public:
    ~Derived() {
      /* 析构函数内 Derived 的信息正在被析构 */
      f();  // 将会调用 Base::f();
    }  // 结束后继续调用 Base 的析构函数

    void f() override {
      std::cout << "Derived::f()\n";
    }
  };

需要注意的是, 此处都是指构造函数、析构函数内部的虚函数调用:

- 虚函数调用需要完整的类型信息.
- 构造函数、析构函数是对类型信息进行构造和析构.

基于这两点, 其内部所执行的虚函数调用自然会产生这样的行为, 与构造函数、析构函数本身如何被调用无关.

对于构造函数、析构函数本身是否可以是虚函数, 我们也可以根据类型信息的构造和析构来推理:

- 构造函数不能被设置为虚函数, 毕竟构造函数之前不存在任何类型信息.
- 析构函数可以是虚函数, 毕竟构造函数已经完成了, 而析构函数执行前类型信息是完整的, 只是开始执行后逐渐对信息进行析构.

.. admonition:: 相关核心准则

  - :coreguidelines:`C.82: 不要在构造函数和析构函数中调用虚函数 <c82-dont-call-virtual-functions-in-constructors-and-destructors>`

========================================================================================================================
类层次与拷贝构造函数、拷贝赋值函数
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
拷贝函数的问题
------------------------------------------------------------------------------------------------------------------------

默认的拷贝行为也是基于静态类型进行的.
通过 :cpp:`Derived` 拷贝构造 :cpp:`Base` 时, 将只会拷贝 :cpp:`Derived` 的 :cpp:`Base` 部分, 这称为对象切片 (object slicing).

.. literalinclude:: object_slicing.cpp
  :language: cpp
  :emphasize-lines: 14, 23
  :linenos:

.. hint::

  你也可以通过断点调试查看该参数的数据, 自己验证一下结果如何. 断点调试非常有用, 请学习 :doc:`/debugger/main` 并完成习题.

  .. figure:: object_slicing.png

    断点调试查看拷贝结果

引用或指针只是引用对象, 自然不存在拷贝的问题.

.. literalinclude:: referencing.cpp
  :language: cpp
  :emphasize-lines: 14, 23
  :linenos:

.. hint::

  你也可以通过断点调试查看该参数的数据, 自己验证一下结果如何. 断点调试非常有用, 请学习 :doc:`/debugger/main` 并完成习题.

  .. figure:: referencing.png

    断点调试查看引用结果

好吧, 我们需要利用动态类型, 换句话说, 我们需要使用虚函数. 但问题是在 :ref:`虚函数调用的感性理解_类层次与构造函数、析构函数` 中我们已经分析过, 构造函数不能设置为虚函数, 所以拷贝构造函数不能设置为虚函数. 难道我们抛开拷贝构造函数不管, 将拷贝赋值函数定义为虚函数吗?

不, 我们应该保持拷贝构造函数和拷贝赋值函数的行为一致. 想象一下这样一种 :cpp:`int`, 当发生拷贝构造时它创建一个新的 :cpp:`int`, 当发生拷贝赋值时它指向同一个 :cpp:`int`:

.. code-block:: cpp
  :linenos:
  :caption: 发生拷贝构造时为值语义, 发生拷贝赋值时为引用语义

  int value1 = 0;
  int value2 = value1;  // 拷贝构造, value2 是新的 int
  int value3;
  value3 = value1;      // 拷贝赋值, value1 和 value3 指向同一个 int

  value3 = 5;
  std::cout << value1 << '\n';  // 输出 5
  std::cout << value2 << '\n';  // 输出 0
  std::cout << value3 << '\n';  // 输出 5

这太可怕了!

既然拷贝构造函数不能是虚函数, 那么拷贝赋值函数为了一致性, 也应该是非虚函数.

.. admonition:: 相关核心准则

  - :coreguidelines:`C.22: 让特殊函数保持一致 <c22-make-default-operations-consistent>`
  - :coreguidelines:`C.60: 拷贝赋值函数应该是非虚函数, 按 const& 传参, 并按 & 返回自身 <c60-make-copy-assignment-non-virtual-take-the-parameter-by-const-and-return-by-non-const>`

------------------------------------------------------------------------------------------------------------------------
但我想通过基类引用拷贝派生类!
------------------------------------------------------------------------------------------------------------------------

.. danger::

  这是比较进阶的内容, 添加进来只是为了提示有可解决方案.

那应该如何拷贝类层次呢? 有一种已有的设计模式可以解决这个问题, 它称为原型 (prototype) 设计模式.

.. literalinclude:: prototype.cpp
  :language: cpp
  :linenos:

.. admonition:: 相关核心准则

  - :coreguidelines:`C.130: 要进行多态类的深拷贝, 倾向于使用 clone 函数而不是公用拷贝构造/赋值函数 <c130-for-making-deep-copies-of-polymorphic-classes-prefer-a-virtual-clone-function-instead-of-public-copy-constructionassignment>`