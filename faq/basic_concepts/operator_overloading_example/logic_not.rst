************************************************************************************************************************
逻辑非: :cpp:`operator!`
************************************************************************************************************************

内置的 :cpp:`operator!` 适用于在某些语境下, 将类型转换为 :cpp:`bool`.

如果用户自定义类型需要用于这些语境, 只需要提供类型转换 :cpp:`operator bool` 即可, 而无需重载 :cpp:`operator!`:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    // Widget -> bool 的转换函数
    //  -> true : value_ == 5
    //  -> false: value_ != 5
    explicit operator bool() {
      return value_ == 5;
    }

   private:
    int value_;
  };