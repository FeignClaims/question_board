************************************************************************************************************************
模板 (template)
************************************************************************************************************************

========================================================================================================================
函数模板
========================================================================================================================

通过 :doc:`函数 </faq/basic_concepts/function>`, 我们可以用不同的值运行同一段代码:

.. code-block:: cpp
  :linenos:

  int max(int lhs, int rhs) {
    return lhs > rhs ? lhs : rhs;
  }

  max(5, 4) == 5;
  max(1, 4) == 4;

但仅仅是允许同一类型不同的值复用代码是不够的:

.. code-block:: cpp
  :linenos:

  char   max(char   lhs, char   rhs);
  int    max(int    lhs, int    rhs);
  double max(double lhs, double rhs);
  // ...

模板的目的即是为 *任意类型* 或 *编译时可确定的值* 生成可用的代码:

.. code-block:: cpp
  :linenos:

  template <typename T>
  T max(T lhs, T rhs) {
    return lhs > rhs ? lhs : rhs;
  }

  max(5, 4)      == 5;    // 生成 max<int> 函数, 然后调用
  max(1.0, 2.0)  == 2.0;  // 生成 max<double> 函数, 然后调用

此时的传参和传返回值同样可以当作变量声明来理解, 则类型模板参数 :cpp:`T` 对应于 :doc:`/faq/basic_concepts/auto`:

.. code-block:: cpp
  :linenos:
  :caption: 声明变量

  auto lhs    = a;
  auto rhs    = b;
  auto result = lhs > rhs ? lhs : rhs;

.. code-block:: cpp
  :linenos:
  :caption: 传参和传返回值

  template <typename T>
  T max(T lhs, T rhs) {
    return lhs > rhs ? lhs : rhs;
  }
  auto result = max(a, b);

与 :cpp:`auto` 一样, 可以添加 :cpp:`const`、:cpp:`&` 和 :cpp:`*` 等修饰符:

.. code-block:: cpp
  :linenos:

  template <typename T>
  T max(T const& lhs, T const& rhs) {
    return lhs > rhs ? lhs : rhs;
  }
  max(5, 4);  // 推导 T 为 int, 则 lhs 为 int const&

但要注意, 由于我们只写了 :cpp:`<typename T>` 一个模板参数, :cpp:`T` 只能被推导为一种类型:

.. code-block:: cpp
  :linenos:

  template <typename T>
  T max(T const& lhs, T const& rhs) {
    return lhs > rhs ? lhs : rhs;
  }

  max(1.0, 4);  // 错误: T 类型推导发生冲突
                //      - 1.0 -> double
                //      - 4   -> int

这没什么, 我们可以要求多个模板参数:

.. code-block:: cpp
  :linenos:

  template <typename Return, typename T, typename U>
  Return max(T const& lhs, U const& rhs) {
    return lhs > rhs ? lhs : rhs;
  }

可这样一来, 返回值呢? 调用函数时没有参数对应它, 它没法自动推导:

.. code-block:: cpp
  :linenos:

  max(5.0, 4);  // T -> double, U -> int
                // 错误: 无法推导模板参数 Return

我们可以显式地指明它:

.. code-block:: cpp
  :linenos:

  max<double>(5.0, 4);  // Return -> double

或者我们其实不是想让返回值作为独立的模板参数, 只是不知道它的类型到底是什么. 还记得 :cpp:`auto` 吗?

.. code-block:: cpp
  :linenos:

  template <typename T, typename U>
  auto max(T const& lhs, U const& rhs) {
    return lhs > rhs ? lhs : rhs;
  }

  max(5.0, 4);

当然了, 模板的生成要求类型确实支持相应的操作:

.. code-block:: cpp
  :linenos:

  int value    = 5;
  int* pointer = &value;
  max(value, pointer);  // 错误: int 和 int* 不可进行 > 比较

.. admonition:: 解释上的遗憾
  :class: dropdown

  你可能会想, 既然返回值能使用 :cpp:`auto`, 那参数呢?

  .. code-block:: cpp
    :linenos:

    auto max(auto const& lhs, auto const& rhs) {
      return lhs > rhs ? lhs : rhs;
    }

    // 相当于:
    template <typename T, typename U>
    auto max(T const& lhs, U const& rhs) {
      return lhs > rhs ? lhs : rhs;
    }

  我更倾向的解释思路其实是先使用 :cpp:`auto` 让新手能使用模板, 再在合适时候引入 :cpp:`template <...>` 这样的语法. 遗憾的是, 这是 C++20 才有的语法, 与教学使用的 C++98 和你通过 Visual Studio 默认能用的 C++11 相比太超前了.

========================================================================================================================
类模板
========================================================================================================================

我们除了可以为函数编写模板, 也可以为类编写模板.

例如要实现数学上的复数, 我们可能需要不同的精度.

.. code-block:: cpp
  :linenos:

  template <typename T>
  class Complex {
   public:
    Complex(T real, T imaginary);
    // ...

   private:
    T real_;
    T imaginary_;
  };

  Complex<double> value;

遗憾的是, 在 C++17 以前, 我们没办法根据构造函数推导类模板的模板参数:

.. code-block:: cpp
  :linenos:

  Complex value(10.0, 5.0);  // C++17 以前错误: 无法推导类模板的参数类型
                             // C++17 及以后正确: T -> double

为此你可以编写一个函数模板来进行推导:

.. code-block:: cpp
  :linenos:

  template <typename T>
  Complex make_complex(T real, T imaginary) {
    Complex<T> result(real, imaginary);
    return result;
  }

  auto value1 = make_complex(1, 0);       // Complex<int>
  auto value2 = make_complex(10.0, 5.0);  // Complex<double>

而模板参数除了是类型外, 还可以是编译时可确定的值.

.. code-block:: cpp
  :linenos:

  template <typename T, int Size>
  class Array {
  public:
    T& operator[](int index) {
      return data_[index];
    }
    T const& operator[](int index) const {
      return data_[index];
    }
    int size() const {
      return Size;
    }

    T data_[Size];
  };

这不就是包装了一下数组吗, 能有什么用? :cpp:`Array` 是一个新的类型而不是数组类型, 它不会隐式类型转换为首元素的指针.

不会隐式类型转换为首元素的指针, 所以跟 :cpp:`int` 没什么区别, 是值语义.
  .. code-block:: cpp
    :linenos:

    void by_copy(Array<int, 3> array);
    void by_reference(Array<int, 3>& array);

    Array<int, 3> array      = {0, 1, 2};
    Array<int, 3> another    = array;  // 拷贝得一个新的对象
    Array<int, 3>& reference = array;  // 引用对象

    by_copy(array);       // 拷贝传参
    by_reference(array);  // 引用传参

不会隐式类型转换为首元素的指针, 所以始终知道自己的长度.
  .. code-block:: cpp
    :linenos:

    template <typename T, int Size>
    void print(Array<T, Size> const& array) {
      for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << ' ';
      }
      std::cout << '\n';
    }

不会隐式类型转换为首元素的指针, 所以没有 :cpp:`array + 0` 这种恶心的运算.
  .. code-block:: cpp
    :linenos:

    Array<int, 3> array = {0, 1, 2};
    auto value          = array + 0;  // 错误: 不支持 Array<int, 3> + int

事实上, C++11 后即在 :cpp:`<array>` 中提供了这样的一个类 :cpp:`std::array<T, Size>`.

.. code-block:: cpp
  :linenos:

  #include <array>

  template <typename T, int Size>
  void print(std::array<T, Size> const& array) {
      for (int i = 0; i < array.size(); ++i) {
        std::cout << array[i] << ' ';
      }
      std::cout << '\n';
  }

  int main() {
    std::array<int, 3> array = {0, 1, 2};
    print(array);
  }

========================================================================================================================
相关解答
========================================================================================================================

- :doc:`/faq/range_iterator_and_algorithm/main`