************************************************************************************************************************
解引用
************************************************************************************************************************

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    int* operator->() {
      return &value_;
    }
    int const* operator->() const {
      return &value_;
    }
    int& operator*() {
      return value_;
    }
    int operator*() const {
      return value_;
    }

   private:
    int value_;
  };