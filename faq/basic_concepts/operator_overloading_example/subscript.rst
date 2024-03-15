************************************************************************************************************************
数组下标: :cpp:`operator[]`
************************************************************************************************************************

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    int& operator[](int index) {
      return array_[index];
    }
    int const& operator[](int index) const {
      return array_[index];
    }

   private:
    int array_[100];
  };