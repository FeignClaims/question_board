************************************************************************************************************************
输入流、输出流
************************************************************************************************************************

一般地, 定义为友元函数.

========================================================================================================================
简易版
========================================================================================================================

.. code-block:: cpp
  :linenos:

  #include <istream>  // for std::istream
  #include <ostream>  // for std::ostream

  class Widget {
   public:
    // 将类成员写入流中
    friend std::ostream& operator<<(std::ostream& ostream, Widget const& widget) {
      ostream << widget.value_;
      return ostream;  // 按引用返回输出流
    }

    // 从流中读取数据
    friend std::istream& operator>>(std::istream& istream, Widget& widget) {
      istream >> widget.value_;
      return istream;  // 按引用返回输入流
    }

   private:
    int value_;
  };

========================================================================================================================
复杂版
========================================================================================================================

.. hint::

  相比于进行这样的复杂实现来序列化, 你可能更想用第三方库进行序列化.

以按 ``(real,imaginary)`` 格式读入复数为例:

.. code-block:: cpp
  :linenos:
  :caption: 定义 :cpp:`operator<<`

  #include <iomanip>  // for std::setprecision
  #include <ostream>  // for std::ostream
  #include <sstream>  // for std::ostringstream

  class Complex {
   public:
    // 将复数以保留两位小数的 (real,imaginary) 写入流中
    friend std::ostream& operator<<(std::ostream& ostream,
                                    Complex const& complex) {
      // 为避免污染 `ostream` 的格式, 新建一个 `std::ostringstream`
      std::ostringstream oss;

      oss << std::fixed << std::setprecision(2);
      oss << '(' << complex.real_ << ',' << complex.imaginary_ << ')';

      return ostream << oss.str();
    }

   private:
    double real_;
    double imaginary_;
  };

.. code-block:: cpp
  :linenos:
  :caption: 定义 :cpp:`operator>>`

  #include <istream>  // for std::istream

  // 从 istream 中读取一个字符, 判断是不是预期字符 expected, 如果不是则放回字符
  //  -> true : 获取到预期字符
  //  -> false: 没获取到预期字符
  bool check_and_ignore(std::istream& istream, char expected) {
    if (istream.get() == expected) {
      return true;
    }
    istream.unget();  // 没获取到预期字符, 将刚刚读取的字符放回
    return false;
  }

  class Complex {
   public:
    // 从流中读取 (real,imaginary) 为复数
    friend std::istream& operator>>(std::istream& istream, Complex& complex) {
      bool is_good = false;  // 记录输入是否成功

      // 从流中读取特定格式的数据, 并暂存在变量中
      double real      = 0;
      double imaginary = 0;
      if (check_and_ignore(istream, '(')) {
        if (istream >> real) {
          if (check_and_ignore(istream, ',')) {
            if (istream >> imaginary) {
              if (check_and_ignore(istream, ')')) {
                is_good = true;  // 输入成功
              }
            }
          }
        }
      }

      if (is_good) {
        // 如果读取完全成功, 更新 complex
        complex.real_      = real;
        complex.imaginary_ = imaginary;
      } else {
        // 如果读取失败, 设置 istream 为失败状态
        istream.setstate(std::ios_base::failbit);
      }

      return istream;
    }

   private:
    double real_;
    double imaginary_;
  };