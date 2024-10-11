************************************************************************************************************************
6. 综合题
************************************************************************************************************************

出不动了, 一道题, 再见.

.. code-block:: cpp
  :linenos:

  int main() {
    static Noisy c1{Info{.ctor = "r", .dtor = "t"}};
    Noisy c2{Info{.ctor = "a", .dtor = "o"}};
    {
      Noisy* c3 = new Noisy{Info{.ctor = "n", .dtor = "t"}};
      Noisy* c4 = nullptr;
      static Noisy c5{Info{.ctor = "g", .dtor = "l"}};
    }
    {
      Noisy* c6 = nullptr;
      {
        Noisy{Info{.ctor = "e", .dtor = "s"}};
      }
      {
        Noisy* c8 = nullptr;
      }
      c6         = new Noisy{Info{.ctor = ":", .dtor = "i"}};
      Noisy* c9  = nullptr;
      Noisy* c10 = new Noisy{Info{.ctor = ":", .dtor = "o"}};
      delete c6;
      {
        c9 = new Noisy{Info{.ctor = "n", .dtor = "l"}};
        static Noisy c11{Info{.ctor = "_", .dtor = "u"}};
        {
          Noisy* c12 = new Noisy{Info{.ctor = "f", .dtor = "h"}};
          delete c10;
          delete new Noisy{Info{.ctor = "u", .dtor = "n"}};
        }
        Noisy c14{Info{.ctor = "d", .dtor = "_"}};
        static Noisy c15{Info{.ctor = "_", .dtor = "s"}};
        Noisy* c16 = new Noisy{Info{.ctor = "r", .dtor = ":"}};
        static Noisy c17{Info{.ctor = "e", .dtor = "e"}};
        static Noisy c18{Info{.ctor = "s", .dtor = "r"}};
        static Noisy c19{Info{.ctor = "u", .dtor = "_"}};
        delete c9;
        static Noisy c20{Info{.ctor = "t", .dtor = "d"}};
        Noisy* c21 = new Noisy{Info{.ctor = ":", .dtor = "u"}};
        delete c16;
        delete new Noisy{Info{.ctor = "o", .dtor = "p"}};
        Noisy{Info{.ctor = "e", .dtor = "r"}};
        static Noisy c24{Info{.ctor = "a", .dtor = "n"}};
        Noisy* c25 = nullptr;
        c25        = new Noisy{Info{.ctor = "t", .dtor = "s"}};
        Noisy* c26 = nullptr;
        Noisy c27{Info{.ctor = "o", .dtor = "r"}};
      }
      {
        Noisy* c28 = new Noisy{Info{.ctor = "i", .dtor = "a"}};
        delete new Noisy{Info{.ctor = "n", .dtor = "_"}};
      }
      static Noisy c30{Info{.ctor = "f", .dtor = "u"}};
    }
  }

.. admonition:: 点击查看……提示？
  :class: dropdown

  49 个字符, ranges 库中用于返回值的结构体, 包含 "输入迭代器" 和 "是否找到" 数据成员.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`qz8jn3s9j`, 答案: :cpp:`ranges::in_found_result::operator_in_found_result`.