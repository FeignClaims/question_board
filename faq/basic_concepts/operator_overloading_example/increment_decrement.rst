************************************************************************************************************************
自增自减
************************************************************************************************************************

一般地, 先定义 **前置** 版本, 再基于前置版本定义后置版本:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    // 前置自增
    Widget& operator++() {
      ++value_;
      return *this;
    }

    // 后置自增
    Widget operator++(int) {
      Widget old(*this);  // 复制旧值
      ++*this;            // 调用前置自增
      return old;         // 返回旧值
    }

   private:
    int value_;
  };

如果你定义了 :cpp:`operator+=`, 可以用它定义前置自增:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    Widget& operator+=(int value) {
      value_ += value;
      return *this;
    }

    Widget& operator++() {
      *this += 1;
      return *this;
    }

    Widget operator++(int) {
      Widget old(*this);  // 复制旧值
      ++*this;            // 调用前置递增
      return old;         // 返回旧值
    }

   private:
    int value_;
  };