************************************************************************************************************************
5. 综合题
************************************************************************************************************************

出不动了, 一道题, 再见.

.. code-block:: cpp
  :linenos:

  auto main() -> int {
    static Printer c1{Info{.ctor = "r", .dtor = "t"}};
    Printer c2{Info{.ctor = "a", .dtor = "o"}};
    {
      Printer* c3 = new Printer{Info{.ctor = "n", .dtor = "t"}};
      Printer* c4 = nullptr;
      static Printer c5{Info{.ctor = "g", .dtor = "l"}};
    }
    {
      Printer* c6 = nullptr;
      { Printer{Info{.ctor = "e", .dtor = "s"}}; }
      { Printer* c8 = nullptr; }
      c6           = new Printer{Info{.ctor = ":", .dtor = "i"}};
      Printer* c9  = nullptr;
      Printer* c10 = new Printer{Info{.ctor = ":", .dtor = "o"}};
      delete c6;
      {
        c9 = new Printer{Info{.ctor = "n", .dtor = "l"}};
        static Printer c11{Info{.ctor = "_", .dtor = "u"}};
        {
          Printer* c12 = new Printer{Info{.ctor = "f", .dtor = "h"}};
          delete c10;
          delete new Printer{Info{.ctor = "u", .dtor = "n"}};
        }
        Printer c14{Info{.ctor = "d", .dtor = "_"}};
        static Printer c15{Info{.ctor = "_", .dtor = "s"}};
        Printer* c16 = new Printer{Info{.ctor = "r", .dtor = ":"}};
        static Printer c17{Info{.ctor = "e", .dtor = "e"}};
        static Printer c18{Info{.ctor = "s", .dtor = "r"}};
        static Printer c19{Info{.ctor = "u", .dtor = "_"}};
        delete c9;
        static Printer c20{Info{.ctor = "t", .dtor = "d"}};
        Printer* c21 = new Printer{Info{.ctor = ":", .dtor = "u"}};
        delete c16;
        delete new Printer{Info{.ctor = "o", .dtor = "p"}};
        Printer{Info{.ctor = "e", .dtor = "r"}};
        static Printer c24{Info{.ctor = "a", .dtor = "n"}};
        Printer* c25 = nullptr;
        c25          = new Printer{Info{.ctor = "t", .dtor = "s"}};
        Printer* c26 = nullptr;
        Printer c27{Info{.ctor = "o", .dtor = "r"}};
      }
      {
        Printer* c28 = new Printer{Info{.ctor = "i", .dtor = "a"}};
        delete new Printer{Info{.ctor = "n", .dtor = "_"}};
      }
      static Printer c30{Info{.ctor = "f", .dtor = "u"}};
    }
  }

.. admonition:: 点击查看……提示？
  :class: dropdown

  49 个字符, ranges 库中用于返回值的结构体, 包含 "输入迭代器" 和 "是否找到" 数据成员.

.. admonition:: 点击查看答案
  :class: dropdown, solution

  :godbolt:`47zEPz81h`, 答案: :cpp:`ranges::in_found_result::operator_in_found_result`.