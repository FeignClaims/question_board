************************************************************************************************************************
比较运算符: :cpp:`operator<`、:cpp:`operator==`
************************************************************************************************************************

========================================================================================================================
等价性
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

.. hint::

  如果定义了 :cpp:`operator<`，你也可以基于它定义 :cpp:`operator==`. 但要注意, 对于某些类, 等价性和相等性是有区别的.