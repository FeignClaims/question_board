************************************************************************************************************************
rule of 3/5/0: 要么不定义任何特殊函数, 要么定义它们全部
************************************************************************************************************************

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/initialization_assignment`
  - :doc:`/faq/basic_concepts/resource`
  - :doc:`/faq/class_invariant/index`
  - :doc:`/faq/member_initializer/index`

========================================================================================================================
特殊函数
========================================================================================================================

有一些成员函数在不定义时会自动以默认行为定义, 称为特殊函数:

- 默认构造函数: :cpp:`Widget()`
- 拷贝构造函数: :cpp:`Widget(Widget const&)`
- 拷贝赋值函数: :cpp:`Widget& operator=(Widget const&)`
- 移动构造函数: :cpp:`Widget(Widget&&)`
- 移动赋值函数: :cpp:`Widget& operator=(Widget&&)`
- 析构函数: :cpp:`~Widget()`

这些特殊函数和构造函数共同实现了对象的生命期语义: 如何构造、拷贝、移动和析构.

------------------------------------------------------------------------------------------------------------------------
默认构造的行为
------------------------------------------------------------------------------------------------------------------------

默认构造函数会对类的基类和所有非静态成员进行默认初始化: 对于内置类型不进行初始化, 对于用户自定义类调用默认构造函数; 如果某个基类或非静态成员不能默认构造, 则该类也不能默认构造.

.. code-block:: cpp
  :linenos:

  class Widget {
   private:
    std::string string_;
    int value_;
  };

  int main() {
    Widget widget;  // string_ 默认构造为 "", value_ 不进行初始化则值不确定
  }

我们可以在成员后面添加默认初始化器改变它的行为:

.. code-block:: cpp
  :linenos:

  class Widget {
   private:
    std::string string_{"hello"};
    int value_{0};
  };

  int main() {
    Widget widget;  // string_ 初始化为 "hello", value_ 初始化为 0
  }

当存在其他构造函数时, 默认构造函数不会自动生成, 可以使用 :cpp:`=default` 显式要求生成:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    Widget() = default;  // 显式要求生成默认函数
    Widget(std::string string);

   private:
    std::string string_{};
    int value_{};
  };

  int main() {
    Widget widget;
  }

.. admonition:: 相关核心准则
  :class: coreguidelines

  - :coreguidelines:`C.80: 如果必须明确使用默认语义, 使用 =default <c80-use-default-if-you-have-to-be-explicit-about-using-the-default-semantics>`

.. admonition:: 别看: 关于成员默认初始化器
  :class: dontread, dropdown

  成员后加的默认初始化器改变的是成员的默认构造行为: 只要构造函数没有显式写出该成员如何构造, 它都会按这个行为进行构造.

  .. code-block:: cpp
    :linenos:

    class Widget {
     public:
      Widget(std::string string) : string_(string) {}

     private:
      std::string string_{"hello"};
      int value_{5};
    };

    int main() {
      Widget widget("world");  // string_ == "world"; value_ == 5
    }

  由于成员默认初始化器像这样一致地对待所有构造函数, 我们应该倾向于使用成员默认初始化器, 而非在默认构造函数处定义如何构造.

  .. admonition:: 相关核心准则
    :class: coreguidelines

    - :coreguidelines:`C.45: 不要定义仅仅初始化数据成员的默认构造函数; 作为替代, 使用默认成员初始化器 <c45-dont-define-a-default-constructor-that-only-initializes-data-members-use-default-member-initializers-instead>`
    - :coreguidelines:`C.48: 对于常量初始化, 倾向于默认成员初始化器而非在构造函数中进行成员初始化 <c48-prefer-default-member-initializers-to-member-initializers-in-constructors-for-constant-initializers>`

------------------------------------------------------------------------------------------------------------------------
析构的默认行为
------------------------------------------------------------------------------------------------------------------------

默认情况下, 析构操作按顺序对类的基类和所有非静态成员逐一进行析构:

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    Widget(int value) : value_(value) {}

   private:
    int value_;
  };

  int main() {
    Widget widget(1);
  }  // widget 发生析构时 value_ 发生析构

但要注意 **指针指向的对象不是类的成员**, 所以对于指针而言, 是指针对象本身发生析构:

.. code-block:: cpp
  :linenos:

  #include <cstdio>  // for std::fopen

  class Input_file {
   public:
    //                                          ↓ 以只读形式打开文件, 需要之后用 std::fopen 释放
    Input_file(char const* file_path) : handle_(std::fopen(file_path, "r")) {}

   private:
    FILE* handle_;
  };

  int main() {
    Input_file input_file("text.txt");
  }  // input_file 发生析构时 file_ 发生析构, 但不意味着 file_ 指向的文件资源被释放

如果默认行为不能满足需要, 应该自定义析构函数:

.. code-block:: cpp
  :linenos:

  #include <cstdio>  // for std::fopen, std::fopen

  class Input_file {
   public:
    Input_file(char const* file_path) : handle_(std::fopen(file_path, "r")) {}
    ~Input_file() { std::fopen(handle_); }

   private:
    FILE* handle_;
  };

  int main() {
    Input_file input_file("text.txt");
  }  // input_file 析构时调用 fopen 释放文件资源

.. admonition:: 相关核心准则
  :class: coreguidelines

  - :coreguidelines:`C.30: 如果类在对象析构时需要显式操作, 定义析构函数 <c30-define-a-destructor-if-a-class-needs-an-explicit-action-at-object-destruction>`
  - :coreguidelines:`C.31: 类获取的所有资源必须由类的析构函数释放 <c31-all-resources-acquired-by-a-class-must-be-released-by-the-classs-destructor>`
  - :coreguidelines:`C.32: 如果类有一个裸指针 (T*) 或裸引用 (T&), 考虑它是否具有所有权 <c32-if-a-class-has-a-raw-pointer-t-or-reference-t-consider-whether-it-might-be-owning>`
  - :coreguidelines:`C.33: 如果类有一个所有权指针, 定义析构函数 <c33-if-a-class-has-an-owning-pointer-member-define-a-destructor>`

------------------------------------------------------------------------------------------------------------------------
拷贝的默认行为
------------------------------------------------------------------------------------------------------------------------

默认情况下, 拷贝操作按顺序对类的基类和所有非静态成员逐一进行拷贝; 如果某个基类或非静态成员不能拷贝, 则该类也不能拷贝.

.. code-block:: cpp
  :linenos:

  class Widget {
   public:
    Widget(int value);

   private:
    int value_;
  };

  int main() {
    Widget a(1);
    Widget b(a);  // 复制构造, b.value_ == 1;
  }

但要注意 **指针指向的对象不是类的成员**, 所以对于指针而言, 是指针对象本身发生拷贝:

.. code-block:: cpp
  :linenos:

  class Input_file {
   public:
    Input_file(char const* file_path) : handle_(std::fopen(file_path, "r")) {}

   private:
    FILE* handle_;
  };

  int main() {
    Input_file a("text.txt");
    Input_file b(a);  // b 拷贝 a 的 file_ 指针
    /* a、b 均占有 "text.txt" 文件资源 */
  }

这样拷贝后两个变量实际是指向同一个对象的语义, 称为引用语义; 与之相对地, 像 :cpp:`int` 那样拷贝后得到确确实实的新对象, 与原来的对象完全独立, 称为值语义. **尽量避免引用语义.**

我们需要自己定义拷贝行为. 针对此处, 我们认为文件资源的所有权是独占的 (unique)——仅允许一个对象占有该文件, 因此应该禁止拷贝行为:

.. code-block:: cpp
  :linenos:

  class Input_file {
  public:
    Input_file(char const* file_path) : handle_(std::fopen(file_path, "r")) {}
    Input_file(Input_file const&)            = delete;  // 显式地删除该函数
    Input_file& operator=(Input_file const&) = delete;

  private:
    FILE* handle_;
  };

.. admonition:: 相关核心准则
  :class: coreguidelines

  - :coreguidelines:`C.81: 如果想要禁用默认行为且没有替代方案, 使用 =delete <c81-use-delete-when-you-want-to-disable-default-behavior-without-wanting-an-alternative>`

------------------------------------------------------------------------------------------------------------------------
移动的默认行为
------------------------------------------------------------------------------------------------------------------------

.. warning::

  这是进阶内容, 可以跳过继续往下阅读.

.. seealso::

  在 :doc:`/faq/dynamic_array/index` 和 :doc:`/faq/forward_list/index` 的扩展部分, 我都有介绍如何为它们定义移动函数.

假设小明、小刚合租房子而只有一把钥匙, 移动就是小明将钥匙交给小刚, 而拷贝则是小刚拿小明的钥匙再去配一把钥匙. 我们在上方定义的文件资源由于其所有权独占性而不能拷贝, 但可以用移动 (move) 将它交给另一个 :cpp:`Input_file` 对象.

.. code-block:: cpp
  :linenos:
  :emphasize-lines: 5

  #include <utility>  // for std::move

  int main() {
    Input_file file1("text.txt");
    //                    ↓ 指明我们要移动 file1
    Input_file file2(std::move(file1));
    // 移动后预期:
    // - file2 占有 "text.txt"
    // - file1 不清楚有什么但至少不占有 "text.txt" 了
  }

默认情况下, 移动操作按顺序对类的基类和所有非静态成员逐一进行移动; 如果某个基类或非静态成员不能移动, 则该类也不能移动而将尝试拷贝.

需要注意的是, 设计移动除了表达资源所有权的转移外, 还在于有的资源拷贝起来代价太高 (类比地想想你下载 100GB 文件花的时间!), 而 :cpp:`int`、:cpp:`int*` 等内置类型拷贝代价很低, 反而移动代价很高, 因而 **默认情况下即便我们在移动, 内置类型也会进行拷贝**.

.. code-block:: cpp
  :linenos:

  int main() {
    int value = 0;

    int* pointer1 = &value;
    int* pointer2 = std::move(pointer1);
    /* pointer1 和 pointer2 均指向 value */
  }

为此我们可以使用 :cpp:`result = std::exchange(object, new_value)` 函数. 它就像水流一样, 将数据从右边流到左边:

- ``result <- object <- new_value``

  - :cpp:`new_value` 的值移动给 :cpp:`object`.
  - :cpp:`object` 原来的值移动给 :cpp:`result`.

.. code-block:: cpp
  :linenos:

  #include <utility>  // for std::exchange

  int main() {
    int value = 0;

    int* pointer1 = &value;
    int* pointer2 = std::exchange(pointer1, nullptr);
    /* pointer1 为空, pointer2 指向 value */
  }

而 :cpp:`Input_file` 中的 :cpp:`FILE*` 是一个指针. 作为内置类型, 它移动时进行拷贝. 因此我们需要自己定义 :cpp:`Input_file` 的移动行为:

.. code-block:: cpp
  :linenos:
  :emphasize-lines: 6-7

  #include <utility>  // for std::exchange, std::move, std::swap

  class Input_file {
   public:
    Input_file(char const* file_path) : handle_(std::fopen(file_path, "r")) {}
    Input_file(Input_file&& other) : handle_(std::exchange(other.handle_, nullptr)) {}
    Input_file& operator=(Input_file&& other) {
      Input_file temp(std::move(other));  // 利用移动构造将资源传给临时对象 temp
      swap(*this, temp);                  // 交换当前对象和 temp 的内容从而将资源换给当前对象
      return *this;
    }  // 如果当前对象原本有资源, temp 的析构函数将会负责它的释放

    friend void swap(Input_file& lhs, Input_file& rhs) {
      using std::swap;
      swap(lhs.handle_, rhs.handle_);
    }

  private:
    FILE* handle_;
  };

========================================================================================================================
rule of 3/5: 定义全部特殊函数
========================================================================================================================

如果一个类需要自定义拷贝构造函数、拷贝赋值函数、(移动构造函数、移动赋值函数、) 析构函数, 那么它几乎肯定需要所有 3 (5) 个函数.

回想一下刚刚我们进行的自定义析构和自定义拷贝, 如果只定义其中一个会发生什么?

.. tabs::

  .. tab:: 只定义析构函数

    .. code-block:: cpp
      :linenos:
      :emphasize-lines: 13

      class Input_file {
      public:
        Input_file(char const* file_path) : handle_(std::fopen(file_path, "r")) {}
        ~Input_file() { std::fopen(handle_); }

      private:
        FILE* handle_;
      };

      int main() {
        Input_file a("text.txt");
        Input_file b(a);  // 拷贝后, a、b 均占有 "text.txt" 文件资源
      }  // 错误: a、b 析构时均调用 fopen, 因而关闭文件两次!

  .. tab:: 只定义拷贝函数

    .. code-block:: cpp
      :linenos:
      :emphasize-lines: 13

      class Input_file {
      public:
        Input_file(char const* handle_path) : handle_(std::fopen(handle_path, "r")) {}
        Input_file(Input_file const&)            = delete;
        Input_file& operator=(Input_file const&) = delete;

      private:
        FILE* handle_;
      };

      int main() {
        Input_file input_file("text.txt");
      }  // 错误: input_file 析构时没有释放所占有的资源

这正是 `本问题的提问人所犯的错误 <https://gitee.com/cpp_tutorial/question/issues/I7GJ0R>`_!

如果需要自定义拷贝构造函数、拷贝赋值函数、(移动构造函数、移动赋值函数、) 析构函数, **总是定义它们所有**. 此外, 你可以 :doc:`用拷贝构造函数来实现拷贝赋值函数 </faq/copy_assignment_define/index>`.
如果默认的行为仍然可行, 用 :cpp:`=default` 明确定义; 如果该行为不成立, 用 :cpp:`=delete` 明确删除.

.. admonition:: 相关核心准则
  :class: coreguidelines 

  - :coreguidelines:`C.21: 如果定义或 =delete 了任何复制、移动、析构函数, 定义或 =delete 它们全部 <c21-if-you-define-or-delete-any-copy-move-or-destructor-function-define-or-delete-them-all>`

========================================================================================================================
rule of 0: 不定义任何特殊函数
========================================================================================================================

如果一个类自定义了特殊函数, 说明它就是专门管理资源的所有权的 (单一职责原则); 其他的类则不应该自定义特殊函数再进行资源管理, 而应该使用已经进行资源管理的类.

假设我们打算设计一个文本合成器, 它读入两个输入文件和一个输出文件, 将两个输入文件的内容混合地输出到输出文件中.

.. literalinclude:: anti_rule_of_0.cpp
  :language: cpp
  :linenos:

此处不谈这样做与异常相关的问题, 一个简单的问题是: 连续写三次重复的东西不累吗, 如果之后又有地方要获取文件资源呢?

因此更好地是, 将资源管理专门使用一个类管理, 其他地方直接使用已经进行资源管理的类.

.. literalinclude:: rule_of_0.cpp
  :language: cpp
  :linenos:
  :emphasize-lines: 3, 27-29

事实上, :cpp:`std::fopen` 和 :cpp:`std::fopen` 是 C 语言标准库的内容, 而 C++ 标准库内已经有了自动管理文件资源的类——当然它还定义了移动操作.

.. literalinclude:: rule_of_0_with_std.cpp
  :language: cpp
  :linenos:

.. admonition:: 相关核心准则
  :class: coreguidelines

  - `cppreference: rule of 3/5/0 <https://en.cppreference.com/w/cpp/language/rule_of_three>`_
  - :coreguidelines:`C.20: 尽量避免定义任何特殊函数 <c20-if-you-can-avoid-defining-default-operations-do>`
