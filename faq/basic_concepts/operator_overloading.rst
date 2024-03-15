.. _faq_运算符重载:

************************************************************************************************************************
运算符重载 (operator overloading)
************************************************************************************************************************

假设我们定义了数学上的复数类, 则很可能需要复数类的加法等运算:

.. code-block:: cpp
  :linenos:

  class Complex {
   public:
    Complex(int real, int imaginary);
    Complex(Complex const&);

    Complex& add_by(Complex const& other) {
      real_      += other.real_;
      imaginary_ += other.imaginary_;
      return *this;
    }
    friend Complex add(Complex lhs, Complex rhs) {
      Complex result(lhs);
      result.add_by(rhs);
      return result;
    }

   private:
    int real_;
    int imaginary_;
  };

.. code-block:: cpp
  :linenos:

  Complex lhs(1, 5);
  Complex rhs(2, 3);
  add(add(lhs, lhs), add(lhs, rhs));  // 😱

这太恶心了, 谁会有耐心去读 :cpp:`add(add(lhs, lhs), add(lhs, rhs));` 到底做了啥呢?

但是 :cpp:`int` 不是这样的:

.. code-block:: cpp
  :linenos:

  int lhs = 1;
  int rhs = 3;
  (lhs + lhs) + (lhs + rhs);

我们可以让复数类也这样吗? C++ 的一个目标是 *让用户自定义类型和内置类型拥有同等程度的支持*, 自然提供了让用户自定义类型支持运算符的方法, 这称为运算符重载 (operator overloading).

很简单, 将 :cpp:`add_by` 改为 :cpp:`operator+=`, 将 :cpp:`add` 改为 :cpp:`operator+`:


.. code-block:: cpp
  :linenos:

  class Complex {
   public:
    Complex(int real, int imaginary);
    Complex(Complex const&);

    Complex& operator+=(Complex const& other) {
      real_      += other.real_;
      imaginary_ += other.imaginary_;
      return *this;
    }
    friend Complex operator+(Complex lhs, Complex rhs) {
      Complex result(lhs);
      result += rhs;
      return result;
    }

   private:
    int real_;
    int imaginary_;
  };

.. code-block:: cpp
  :linenos:

  Complex lhs(1, 5);
  Complex rhs(2, 3);
  (lhs + lhs) + (lhs + rhs);  // 😋

这就是运算符重载: 函数名字是对应的运算符, 函数的参数个数是对应的参数个数, 并且参数中有自定义类型.

========================================================================================================================
第一节课里的运算符重载
========================================================================================================================

我们在最开始就见过运算符重载:

.. code-block:: cpp
  :linenos:

  int value = 0;
  std::cin  >> value;
  std::cout << value;

:cpp:`<<` 和 :cpp:`>>` 原本是位运算的移位运算符 (如 :cpp:`5 << 1`), 但由于它形状上是箭头, 标准库将它用于输入输出, 这可以对应于:

.. code-block:: cpp
  :linenos:

  std::istream& operator>>(std::istream& istream, int& value) {
    /* 从 istream 中读入值到 value */
    return istream;
  }

  std::ostream& operator<<(std::ostream& ostream, int value) {
    /* 将 value 值输出到 ostream */
    return ostream;
  }

========================================================================================================================
最佳实践
========================================================================================================================

运算符重载的方式可能基于应用, 你完全可以用运算符重载在 C++ 代码内部创造一种新的语言.

如果你目的是让自定义类型模拟内置类型 (如 :cpp:`int`) 的行为, 则可以参考以下要求:

函数类型
  - 对于 **一元运算符**, 实现为 *成员函数*.
  - 对于 **二元运算符**:

    - :cpp:`=` (赋值)、:cpp:`[]` (下标访问)、:cpp:`->` (成员访问) 和 :cpp:`()` (函数调用), 总是实现为 *成员函数*.

    - 如果 **它不对等地对待它的两个参数** (通常会改变左侧实参的内容, 并且需要访问私用成员), 则实现为其 *左参数的成员函数*.

    - 如果 **它对等地对待它的两个参数**, 实现为 *友元函数并在类内定义* (hidden friend 惯用法).

函数参数和返回值
  同样地, 模拟内置类型的行为, 具体参考以下示例.

  此外, 如果参数不会被修改, 应该用 :cpp:`const&` 而不是 :cpp:`&`, :doc:`求求你这么做吧😭😭😭, 教材不这么做是因为它是垃圾教材 </faq/copy_functions_parameter/main>`.

:cpp:`class Widget` 各种运算符模拟内置类型的实现示例 (C++98)
  .. toctree::
    :maxdepth: 1

    operator_overloading_example/copy_assignment
    operator_overloading_example/istream_ostream
    operator_overloading_example/increment_decrement
    operator_overloading_example/compund_assignment_and_binary_operation
    operator_overloading_example/comparison
    operator_overloading_example/subscript
    operator_overloading_example/dereference
    operator_overloading_example/logic_not
    operator_overloading_example/rarely_overloaded

========================================================================================================================
相关解答
========================================================================================================================

- :doc:`/faq/range_iterator_and_algorithm/main`