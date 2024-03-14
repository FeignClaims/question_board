************************************************************************************************************************
复合赋值和二元算术
************************************************************************************************************************

定义对应的 **复合赋值** 版本, 再基于它定义 **二元算术**:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    // 复合赋值
    Widget& operator+=(Widget const& other) {
      value_ += other.value_;
      return *this;  // 按引用返回 `*this`
    }

    // 二元算术
    friend Widget operator+(Widget const& lhs, Widget const& rhs) {
      Widget result(lhs);  // 拷贝左参数
      result += rhs;       // 执行复合赋值运算
      return result;       // 返回结果
    }

   private:
    int value_;
  };

更简单而且会更高效地:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    friend Widget operator+(Widget const& lhs, Widget const& rhs) {
      return Widget(lhs) += result;
      // 1. Widget(lhs)                 : 用 lhs 拷贝构造一个 Widget 类型的临时对象
      // 2. Widget(lhs) += result       : 对临时对象执行复合赋值运算
      // 3. return Widget(lhs) += result: 返回临时对象
    }
  };

或者你也可以反过来, 用 **二元运算** 定义 **复合赋值**. 但一般来说, 这样会使复合赋值的实现中使用不必要的 *临时对象*:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    // 二元算术
    friend Widget operator+(Widget const& lhs, Widget const& rhs) {
      Widget result;
      result.value_ = lhs.value_ + rhs.value_;
      return result;
    }

    // 复合赋值
    Widget& operator+=(Widget const& other) {
      *this = *this + other;  // *this + other 会产生一个临时对象
      return *this;
    }

   private:
    int value_;
  };