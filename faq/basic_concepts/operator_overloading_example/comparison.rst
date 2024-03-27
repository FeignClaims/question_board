************************************************************************************************************************
比较运算符: :cpp:`operator<`、:cpp:`operator==`
************************************************************************************************************************

========================================================================================================================
等价性 (偏序关系)
========================================================================================================================

定义 :cpp:`operator<`, 然后用它定义其他.

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    // 定义 operator< 以获得严格弱序
    friend bool operator<(Widget const& lhs, Widget const& rhs) {
      return lhs.value_ < rhs.value_;
    }

    // 通过 operator< 定义其他关系运算符
    friend bool operator>(Widget const& lhs, Widget const& rhs) {
      return rhs < lhs;
    }
    friend bool operator<=(Widget const& lhs, Widget const& rhs) {
      return !(lhs > rhs);
    }
    friend bool operator>=(Widget const& lhs, Widget const& rhs) {
      return !(lhs < rhs);
    }

   private:
    int value_;
  };

========================================================================================================================
相等性
========================================================================================================================

定义 :cpp:`operator==`, 然后用它定义 :cpp:`operator!=`.

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    // 定义 operator==
    friend bool operator==(Widget const& lhs, Widget const& rhs) {
      return lhs.value_ == rhs.value_;
    }

    // 通过 operator== 定义 operator!=
    friend bool operator!=(Widget const& lhs, Widget const& rhs) {
      return !(lhs == rhs);
    }

   private:
    int value_;
  };

注意传参应该传 :cpp:`Widget const& widget` 而非 `Widget widget`. 为什么呢? 所谓拷贝, 是得到与原对象相等的对象, 而我们此处正是在定义什么是相等.

.. hint::

  如果定义了 :cpp:`operator<`，你也可以基于它定义 :cpp:`operator==`.

  .. admonition:: 别看: 但等价性和相等性是有区别的
    :class: dontread, dropdown

    以 :cpp:`int i` 和 :cpp:`int j` 为例:

    - :cpp:`!(i < j) && !(j < i)` 为等价性, 则 :cpp:`i` 既不小于、也不大于 :cpp:`j`.
    - :cpp:`i == j` 为相等性, 则对于函数 :cpp:`f(int value)`, :cpp:`f(i)` 与 :cpp:`f(j)` 相同.

    .. code-block:: cpp
      :linenos:

      bool is_square_less(int i, int j) {
        return i * i < j * j;
      }

      void print(int value) {
        std::cout << value << '\n';
      }

      int main() {
        int i = -1;
        int j = 1;

        !is_square_less(i, j);  // 在平方小于偏序关系下, i 和 j 等价
        !is_square_less(j, i);

        print(i);  // 但 i 和 j 并不相等
        print(j);
      }