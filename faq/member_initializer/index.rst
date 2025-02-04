************************************************************************************************************************
成员初始化器: 构造函数的冒号是啥?
************************************************************************************************************************

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/initialization_assignment`
  - :doc:`/faq/class_invariant/index`

为了维护 :doc:`不变式 </faq/class_invariant/index>`, 我们将数据成员设为私用; 为了建立不变式, 我们定义构造函数:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    Widget(int value) {
      value_ = value;  // 用参数 value 赋值数据成员 value_
    }

   private:
    int value_;
  };

注意到, 我将私用数据成员命名为 :cpp:`value_`, 这样就避免了与参数名字 :cpp:`value` 或其他什么产生冲突, 从而不需要采取某些 **糟糕手段**:

.. tabs::

  .. tab:: 随便命名

    .. code-block:: cpp
      :linenos:
      :emphasize-lines: 3

      class Widget {
       public:
        Widget(int a) {  // 鬼知道 a 是啥
          value = a;
        }

       private:
        int value;
      };

  .. tab:: 简写

    .. code-block:: cpp
      :linenos:
      :emphasize-lines: 3

      class Widget {
       public:
        Widget(int v) {  // 鬼知道 v 代表 value
          value = v;
        }

       private:
        int value;
      };

  .. tab:: 显式使用 :cpp:`this` 指针

    .. code-block:: cpp
      :linenos:
      :emphasize-lines: 5

      class Widget {
       public:
        Widget(int value) {
          // ↓ 用 this 来明确是在访问成员
          this->value = value;  // 看着不累吗
        }

       private:
        int value;
      };

但运行到构造函数体内时, 所有成员其实已经构造好了, 我们 :cpp:`value_ = value` 不是在构造时初始化成员, 只是在对已经构造的成员进行赋值: 如果把构造时初始化比喻为修建房屋, 赋值就是你已经住了一段时间后再对房子进行装修.

为了对成员进行构造, 我们在函数体之前使用成员初始化器:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    Widget(int value) : value_{value} {}

   private:
    int value_;
  };