************************************************************************************************************************
实例分析: 动态数组 (dynamic array)
************************************************************************************************************************

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/object`
  - :doc:`/faq/basic_concepts/initialization_assignment`
  - :doc:`/faq/basic_concepts/resource`
  - :doc:`/faq/basic_concepts/struct`
  - :doc:`/faq/basic_concepts/pointer`
  - :doc:`/faq/basic_concepts/c_array`

========================================================================================================================
动态数组的分配和释放
========================================================================================================================

内置数组 :cpp:`int array[size]` 的长度 :cpp:`size` 必须在编译时已知, 而不能等到程序运行时才确定.

.. tabs::

  .. tab:: 整数字面值

    .. code-block:: cpp
      :linenos:

      int array[100];  // 显然在编译时就知道是 100

  .. tab:: :cpp:`const` 变量

    .. code-block:: cpp
      :linenos:

      int const size = 100;
      int array[size];  // 编译时就知道 size 是 100, 不可改变

  .. tab:: 变量

    .. code-block:: cpp
      :linenos:

      int size = 0;
      std::cin >> size
      int array[size];  // 错误: 程序运行并进行输入后, 才能知道 size 的值

这是因为 :doc:`调用函数将会在栈上创建栈帧来记录数据 </faq/basic_concepts/function>`, 栈帧存储了本次调用的参数、局部变量等, 按设计往往大小是固定的, 因此需要在编译时就能确定局部变量的大小.

但我们有根据运行情况来确定数组长度的需求. 所以我们使用 :cpp:`new[]` 在堆空间上 (而非栈上) 分配空间, 栈帧上仅存储 :cpp:`new[]` 所返回的指针, 用这个指针来操作整个数组:

.. code-block:: cpp
  :linenos:

  int main() {
    int size = 0;
    std::cin >> size;

    // ↓ 局部变量——也就是栈上——只是这一个指针
    int* array = new int[size];
    array[0]   = 0;
    array[1]   = 1;
    array[2]   = 2;
  }

我们可以在 :cpp:`new[]` 时, 直接初始化这个数组:

.. code-block:: cpp
  :linenos:

  int main() {
    int size = 0;
    std::cin >> size;

    // 初始化为 {0, 1, 2, 之后的都为 0}
    int* array0 = new int[size]{0, 1, 2};

    // 初始化所有元素为 0
    int* array1 = new int[size]{};
  }

由于我们不再将数组分配在栈帧内, 当函数调用结束、栈帧被释放时, 随栈帧释放的只有栈帧上的指针, 而数组依然存在, 所以我们需要手动调用 :cpp:`delete[]` 释放它:

.. code-block:: cpp
  :linenos:

  int main() {
    int size = 0;
    std::cin >> size;

    int* array = new int[size]{};

    delete[] array;
  }

反过来说, 只要我们具有指向该数组的指针, 且该数组还没被释放, 就能直接使用该数组:

.. code-block:: cpp
  :linenos:

  int* make_array(int size) {
    int* array = new int[size]{};
    return array;
  }

  int main() {
    int* array0 = make_array(5);   // 获得一个长度为 5 的数组
    int* array1 = make_array(10);  // 获得一个长度为 10 的数组

    delete[] array0;
    delete[] array1;
  }

========================================================================================================================
动态数组的基本操作
========================================================================================================================

:doc:`C 风格数组很容易隐式类型转换为首元素的指针 </faq/basic_concepts/c_array>`, 而我们用 :cpp:`new[]` 请求动态数组返回的也是指针, 所以动态数组的操作除了需要手动释放, 其他部分与正常数组其实并无差异: :godbolt:`jzjnv1vrz`

.. code-block:: cpp
  :linenos:
  :caption: 填充

  void fill_n(int* array, int size, int value) {
    for (int i = 0; i < size; ++i) {
      array[i] = value;
    }
  }

  int main() {
    int* array = new int[100]{};
    fill_n(array, 100, 5);
  }

.. code-block:: cpp
  :linenos:
  :caption: 输出

  void print(int const* array, int size) {
    for (int i = 0; i < size; ++i) {
      std::cout << array[i] << ' ';
    }
    std::cout << '\n';
  }

  int main() {
    int* array = new int[100]{};
    print(array, 100);
  }

========================================================================================================================
让动态数组像 :cpp:`int` 一样
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
直接使用 :cpp:`new[]` 和 :cpp:`delete[]` 的问题
------------------------------------------------------------------------------------------------------------------------

目前我们已经建立了动态数组, 但这真的好用吗?

我们需要手动调用 :cpp:`delete[]` 来释放资源.
  .. code-block:: cpp
    :linenos:

    int main() {
      int* array = new int[1000];
    }  // 没有 delete[] 而内存泄露, 你可能导致发动机停止, 引发了一场空难!

我们拷贝所得新指针仍然指向同一数组.
  .. code-block:: cpp
    :linenos:

    int main() {
      int* array0 = new int[3];
      fill_n(array0, 3, 5);
      print(array0, 3);  // array0: {5, 5, 5}

      int* array1 = array0;
      fill_n(array1, 3, 7);  // 对 array1 填充应该不影响 array0, 对、对吧?

      print(array0, 3);  // array0: {7, 7, 7}😱
    }

长度和数组本身相分离.
  .. code-block:: cpp
    :linenos:

    int main() {
      int size   = 10;
      int* array = new int[10];

      print(array, size);  // 既要传首元素指针, 还要传长度!

      size = 20;  // size == 20, 可是数组长度还是 10!
    }

接下来我们设计动态数组类来进行资源管理, 让动态数组的使用跟 :cpp:`int` 差不多:

- 析构时就释放资源, 不需要手动调用 :cpp:`delete[]`.
- 拷贝得到的新对象与原对象相互独立, 对一个对象操作不会影响另一个对象.
- 数组本身和其长度被存储为一个对象的成员, 它们之间的不变式即逻辑关系对外始终成立.

但在设计之前, 我们先分离一些细节, 并引入一些基本组件.

.. seealso::

  - :doc:`/faq/class_invariant/main`

------------------------------------------------------------------------------------------------------------------------
关注逻辑、忽略数据
------------------------------------------------------------------------------------------------------------------------

动态数组存储什么类型的值跟我们设计动态数组没多大关系, 所以我们首先对数据的存储进行抽象, 用类型别名来替代存储的数据:

.. code-block:: cpp
  :linenos:
  :caption: 类型别名

  using value_type = int;  // value_type 是 int 的别名

  value_type value = 0;  // 相当于 int value = 0;
  value_type array[5];   // 相当于 int array[5];

因此, 我们的动态数组类应该写为:

.. code-block:: cpp
  :linenos:

  using value_type = int;

  class Dynamic_array {
   public:
    /* ... */

   private:
    int size_;
    value_type* data_;
  };

------------------------------------------------------------------------------------------------------------------------
实现动态数组的重要组件
------------------------------------------------------------------------------------------------------------------------

标准库中有很多被教学忽略了的算法和算法基础组件, 实际上很多代码是没必要自己编写的, 自行在算法内编写不仅低效而且影响阅读.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
:cpp:`std::swap`
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

一个重要的组件是, 将 :cpp:`lhs` (left hand side) 和 :cpp:`rhs` 变量的内容进行交换, 课上可能会写为:

.. code-block:: cpp
  :linenos:

  int lhs = 2;
  int rhs = 3;

  int temp = lhs;
  lhs      = rhs;
  rhs      = temp;

  std::cout << lhs;  // 输出 3
  std::cout << rhs;  // 输出 2

不, 你没有自己写的必要:

.. code-block:: cpp
  :linenos:

  #include <utility>  // for std::swap

  int lhs = 2;
  int rhs = 3;
  std::swap(lhs, rhs);
  std::cout << lhs;  // 输出 3
  std::cout << rhs;  // 输出 2

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
:cpp:`std::copy_n`
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

回忆一下, 你有多少次编写拷贝整个数组了?

.. tabs::

  .. tab:: :cpp:`strcpy`

    .. code-block:: cpp
      :linenos:

      #include <cstring>  // for std::strcpy

      char const* input = "hello world";
      int output[100]   = {};

      std::strcpy(output, input);

      std::cout << output;  // 输出 "hello world"

  .. tab:: 手写 :cpp:`int` 数组拷贝

    .. code-block:: cpp
      :linenos:

      int input[10]  = {5, 4, 2, 7};
      int output[20] = {};

      // 拷贝 [input, input + 10) 到 [output, output + 10)
      for (int i = 0; i < 10; ++i) {
        output[i] = input[i];
      }

:cpp:`<algorithm>` 中有上百种算法, 而 :cpp:`std::copy_n` 就是其中一个.

相比于 :cpp:`std::strcpy(output, input)` 只能用于字符串拷贝, :cpp:`std::copy_n(input, size, output)` 能用于任何类型:

.. tabs::

  .. tab:: 拷贝 :cpp:`int` 数组

    .. code-block:: cpp
      :linenos:

      #include <algorithm>  // for std::copy_n

      int input[10]  = {5, 4, 2, 7};
      int output[20] = {};

      // 拷贝 [input, input + 10) 到 [output, output + 10)
      std::copy_n(input, 10, output);

  .. tab:: 拷贝 :cpp:`char` 数组

    .. code-block:: cpp
      :linenos:

      #include <algorithm>  // for std::copy_n

      char const* input = "hello world";
      int output[100]   = {};

      // 长度为 std::strlen(input) + 1, 因为还要拷贝终止字符
      std::copy_n(input, std::strlen(input) + 1, output);

      std::cout << output;  // 输出 "hello world"

你可以自己实现 :cpp:`std::copy_n` 的简单版本: :godbolt:`55d95cbo5`

.. code-block:: cpp
  :linenos:

  using value_type = int;

  // 将 [input, input + size) 从左到右拷贝到 [output, output + size) 中
  //
  // 返回值::
  //   返回 output + size, 即如果继续对 output 进行拷贝, 应该使用的指针.
  value_type* copy_n(value_type const* input, int size, value_type* output) {
    for (int i = 0; i < size; ++i) {
      output[i] = input[i];
    }
    return output + size;
  }

请注意 :cpp:`copy_n` 有一个返回值, 之后你将会看到它的魅力.

------------------------------------------------------------------------------------------------------------------------
资源的获取与释放
------------------------------------------------------------------------------------------------------------------------

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
定义构造函数和析构函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

相比于之前手动调用 :cpp:`new[]` 和 :cpp:`delete[]`, 我们在类中定义构造函数来获取资源, 定义析构函数来释放资源:

.. code-block:: cpp
  :linenos:

  using value_type = int;

  class Dynamic_array {
   public:
    Dynamic_array() {
      size_ = 0;
      data_ = nullptr;
    }

    Dynamic_array(int size) {
      size_ = size;
      data_ = size == 0 ? nullptr : new value_type[size];
    }

    ~Dynamic_array() {
      // ↓ delete[] 本身自带对空指针的检查, 不需要提前判断 data_ == nullptr
      delete[] data_;
    }

   private:
    int size_;
    value_type* data_;
  };

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
用默认参数合并构造情况
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

很明显, 默认构造 :cpp:`Dynamic_array()` 不过是 :cpp:`Dynamic_array(int size)` 中 :cpp:`size == 0` 的情况, 因此我们合并为 :cpp:`Dynamic_array(int size = 0)`, 即当不提供 :cpp:`size` 参数时, 默认 :cpp:`size` 为 :cpp:`0`:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    Dynamic_array(int size = 0) {
      size_ = size;
      data_ = size == 0 ? nullptr : new value_type[size];
    }

    /* ... */

   private:
    int size_;
    value_type* data_;
  };

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
用成员初始化器对成员进行初始化而非赋值
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

但运行到构造函数体内时, 所有成员其实已经构造好了, 我们 :cpp:`size_ = size` 不是在构造时初始化成员, 只是在对已经构造的成员进行赋值: 如果把构造时初始化比喻为修建房屋, 赋值就是你已经住了一段时间后再对房子进行装修.

为了在成员构造进行初始化, 我们在函数体之前使用成员初始化器:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    Dynamic_array(int size = 0)
        : size_(size), data_(size == 0 ? nullptr : new value_type[size]()) {}

    /* ... */

   private:
    int size_;
    value_type* data_;
  };

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
用 :cpp:`explicit` 避免隐式类型转换
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

这样就够了吗? 让我们看两段代码:

.. code-block:: cpp
  :linenos:
  :caption: 奇怪的构造

  int main() {
    Dynamic_array array = 5;  // 5 通过 Dynamic_array(int) 转换为 Dynamic_array
  }

.. code-block:: cpp
  :linenos:
  :caption: 奇怪的传参

  void function(Dynamic_array array) {
    /* ... */
  }

  int main() {
    int value = 0;
    /* ... */
    function(value);  // value 通过 Dynamic_array(int) 转换为 Dynamic_array
  }

所以对于能被单个参数调用的构造函数, 我们应该用 :cpp:`explicit` 要求它只能被显式调用:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    explicit Dynamic_array(int size = 0)
        : size_(size), data_(size == 0 ? nullptr : new value_type[size]()) {}

    /* ... */

   private:
    int size_;
    value_type* data_;
  };

最终得到: :godbolt:`d1YqvP19W`

.. code-block:: cpp
  :linenos:

  /* ... */

  int main() {
    // Dynamic_array array0 = 5;  // 错误: 不能从 int 转换为 Dynamic_array
    Dynamic_array array(5);
  }  // 析构时调用析构函数, 自动释放数组

------------------------------------------------------------------------------------------------------------------------
访问数组相关信息
------------------------------------------------------------------------------------------------------------------------

我们接下来定义公用成员函数, 告知使用者可以如何访问这个数组. 具体地, 我们希望使用者能写出这样的代码:

.. code-block:: cpp
  :linenos:

  void fill(Dynamic_array& array, int value) {
    for (int i = 0; i < array.size(); ++i) {
      array[i] = value;
    }
  }

  void print(Dynamic_array const& array) {
    for (int i = 0; i < array.size(); ++i) {
      std::cout << array[i] << ' ';
    }
    std::cout << '\n';
  }

那么我们需要定义:

- 如何进行下标访问, 即实现 :cpp:`operator[](int index)` 成员函数 (运算符是 :cpp:`[]`, 参数是 :cpp:`int index`).
- 如何查询数组长度, 即实现 :cpp:`size()` 成员函数.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
支持 :cpp:`fill` 函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

:cpp:`size()` 很容易实现, 而对于下标访问操作, 它除了函数名字变成了 :cpp:`operator[]` 以外, 其余的与正常函数没有什么区别.

由于 :cpp:`fill` 需要通过下标访问修改数组元素的内容, 下标访问应该返回对元素的引用: :godbolt:`Y9Tddv3MM`

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    /* ... */

    value_type& operator[](int index) {
      return data_[index];
    }

    int size() {
      return size_;
    }

   private:
    int size_;
    value_type* data_;
  };

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
支持 :cpp:`print` 函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

:cpp:`print` 函数只是用于输出, 因而不应该能修改 :cpp:`Dynamic_array` 的内容——我们按 :cpp:`Dynamic_array const&` 传递参数:

.. code-block:: cpp
  :linenos:

  void print(Dynamic_array const& array) {
    for (int i = 0; i < array.size(); ++i) {  // 错误: size() 不是 const 函数
      std::cout << array[i] << ' ';           // 错误: 下标访问不是 const 函数
    }
    std::cout << '\n';
  }

为什么报错了? 我们没有指出 :cpp:`size()` 和 :cpp:`operator[]` 保证不会修改对象, 因而不能对 const 对象调用它们.

好吧, :cpp:`size()` 只是获取长度, 必然不会修改对象, 我们来标识一下:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    //         ↓ 我保证这个函数不会修改对象
    int size() const {
      return size_;
    }

    /* ... */
  }

但是下标访问呢?

- 对于非 const 对象, 我们要允许通过下标访问修改数据;
- 对于 const 对象, 我们要保证不能通过下标访问修改数据.

其实很简单, 我们写一个非 const 版本的函数和一个 const 版本的函数:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    value_type& operator[](int index) {
      return data_[index];
    }

    // ↓ 返回 value const&, 自然不能进行修改了
    value_type const& operator[](int index) const {
      return data_[index];
    }

    /* ... */
  }

最终得到: :godbolt:`97c5cf7c1`

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    value_type& operator[](int index) {
      return data_[index];
    }

    value_type const& operator[](int index) const {
      return data_[index];
    }

    int size() const {
      return size_;
    }
  };

.. seealso::

  - :doc:`/faq/east_const/main` 中解释了为什么 const 成员函数是将 :cpp:`const` 是放在右边.

------------------------------------------------------------------------------------------------------------------------
拷贝函数
------------------------------------------------------------------------------------------------------------------------

注意到在之前的 :cpp:`fill(Dynamic_array&, int)` 和 :cpp:`print(Dynamic_array const&)` 函数中, 我们都使用的是引用传参而非按值传参 (拷贝传参).

因为我们目前不能进行按值传参. 结构体和类的默认拷贝行为是逐一拷贝所有数据成员, 对于 :cpp:`Dynamic_array` 而言就是拷贝 :cpp:`int size_` 和 :cpp:`value_type* data_`. 但除了这两个成员外, :cpp:`Dynamic_array` 还具有 :cpp:`new[]` 所得数组的所有权, 所以我们才定义了析构函数, 从而指出析构时这个类要负责用 :cpp:`delete[]` 释放数组.

这样对 :cpp:`new[]` 所得数组的所有权是通过 :cpp:`value_type* data_` 所指向的对象来表达的, 但默认的拷贝行为只拷贝 :cpp:`int size_` 和 :cpp:`value_type* data_`, 而指针 :cpp:`data_` 发生拷贝所得新指针与原指针存储同样的地址、指向同一个对象.

因此, 默认拷贝行为下, 拷贝后新得到的 :cpp:`Dynamic_array` 对象与原对象具有同一个数组的所有权, 数组将会被释放两次:

.. code-block:: cpp
  :linenos:

  void print(Dynamic_array parameter) {
    // 通过拷贝得到的形式参数 parameter 与实际参数具有同一个数组的所有权
    /* ... */
  }  // 参数发生析构, 释放数组

  int main() {
    Dynamic_array array(5);

    print(array);  // 传入实际参数, 相当于 Dynamic_array parameter = array;

    array[0] = 1;  // 错误: 访问已经被释放的数组空间
  }  // 错误: 析构时调用 delete[] 释放数组, 但这个数组早就释放了

我们需要自定义拷贝函数, 在拷贝时不仅拷贝成员 :cpp:`size_` 和 :cpp:`data_`, 也对 :cpp:`new[]` 所得数组进行拷贝.

.. hint::

  当类自定义了拷贝函数或析构函数, 往往意味着我们在管理某种特殊资源; 而在管理特殊资源时, 默认的拷贝行为和析构行为往往都不合适, 我们应该定义它们全部. 这称为 :doc:`/faq/rule_of_350/main`.

一种拷贝情况是, 我们用原对象构造一个新对象, 使得已有对象与原对象相等, 这称为拷贝构造.
  .. code-block:: cpp
    :linenos:

    int value = 0;
    int copy  = value;  // 虽然是等号, 但这是构造而非赋值

一种拷贝情况是, 我们用原对象对已有对象赋值, 使得已有对象与原对象相等, 这称为拷贝赋值.
  .. code-block:: cpp
    :linenos:

    int value = 0;
    int copy;
    copy = value;

注意到了吗? :cpp:`=` 根据情况不同, 可能是构造或赋值. **这真的很烦**, 所以我更倾向于用 :cpp:`{}` 进行初始化, 只在赋值时使用 :cpp:`=`:

.. tabs::

  .. tab:: :cpp:`int`

    .. code-block:: cpp
      :linenos:

      int value{0};  // 或 int value{};

      int copy{value};  // 构造
      copy = value;     // 赋值

  .. tab:: 数组

    .. code-block:: cpp
      :linenos:

      int array0[3]{1, 2, 3};

      int* array1{new int[10]{1, 2, 3}};

  .. tab:: 成员初始化器

    .. code-block:: cpp
      :linenos:

      class Dynamic_array {
       public:
        explicit Dynamic_array(int size = 0)
            : size_{size}, data_{size == 0 ? nullptr : new value_type[size]{}} {}
      };

本文之后部分我将采用 :cpp:`{}` 语法进行构造.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
拷贝构造函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

针对用原对象构造新对象的情况, 我们定义拷贝构造函数. 拷贝构造函数以同一类型 :cpp:`Dynamic_array` 为参数, 从中读取内容以得到内容的拷贝.

让我们看看这个参数应该写成什么样子:

:cpp:`Dynamic_array(Dynamic_array other)`
  按值传参? 不, 我们是在定义怎么对 :cpp:`Dynamic_array` 进行拷贝, 可按值传参就是在对 :cpp:`Dynamic_array` 进行拷贝……我们在请山里的老和尚讲山里有座庙的递归故事!

:cpp:`Dynamic_array(Dynamic_array& other)`
  不, 我们只是想读取 :cpp:`other` 的内容, 而不想修改它的内容.

:cpp:`Dynamic_array(Dynamic_array* other)`
  不, 对对象进行拷贝的语法是 :cpp:`int value{other}` 而不是 :cpp:`int value{&other}`.

:cpp:`Dynamic_array(Dynamic_array const* other)`
  同上.

排除这些选项, 我们最终确定应该使用 :cpp:`Dynamic_array(Dynamic_array const& other)`.

动态数组的拷贝构造函数分为两部分:

1. 根据 :cpp:`other` 的长度, 为本数组也分配同样长度的数组.
2. 将 :cpp:`other` 数组的内容拷贝到新数组中.

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    // 拷贝构造函数虽然也是单个参数, 但按约定不用加 explicit
    Dynamic_array(Dynamic_array const& other)
        : size_{other.size_},
          data_{other.size_ == 0 ? nullptr : new value_type[other.size_]{}} {
      for (int i{0}; i < other.size_; ++i) {
        data_[i] = other.data_[i];
      }
    }

    /* ... */
  };

函数体内是在对数组进行拷贝, 对吧? 我们换用组件 :cpp:`copy_n`:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    Dynamic_array(Dynamic_array const& other)
        : size_{other.size_},
          data_{other.size_ == 0 ? nullptr : new value_type[other.size_]{}} {
      copy_n(other.data_, other.size_, data_);
    }

    /* ... */
  };

等等, 怎么感觉成员初始化器部分也有点眼熟? 我们来对比看看:

.. code-block:: cpp
  :linenos:
  :emphasize-lines: 4-5, 8-9

  class Dynamic_array {
   public:
    explicit Dynamic_array(int size = 0)
        : size_{size},
          data_{size == 0 ? nullptr : new value_type[size]{}} {}

    Dynamic_array(Dynamic_array const& other)
        : size_{other.size_},
          data_{other.size_ == 0 ? nullptr : new value_type[other.size_]{}} {
      copy_n(other.data_, other.size_, data_);
    }

    /* ... */
  };

我们可以干脆委托 :cpp:`Dynamic_array(int size)` 来分配合适长度的数组:

.. code-block:: cpp
  :linenos:
  :emphasize-lines: 7

  class Dynamic_array {
   public:
    explicit Dynamic_array(int size = 0)
        : size_{size},
          data_{size == 0 ? nullptr : new value_type[size]{}} {}

    Dynamic_array(Dynamic_array const& other) : Dynamic_array{other.size_} {
      copy_n(other.data_, other.size_, data_);
    }

    /* ... */
  };

最终得到: :godbolt:`44964Wrah`

.. seealso::

  - :doc:`/faq/basic_concepts/function_parameter` 中分析了各种传参方式的用途, 并给出了一个泛用策略.
  - :doc:`/faq/copy_functions_parameter/main` 中介绍了使用 :cpp:`Dynamic_array const&` 而非 :cpp:`Dynamic_array&` 的另一个原因.

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
拷贝赋值函数
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

除了用原对象构造新对象的情况外, 我们还可能用原对象对已有对象进行赋值, 为此需要定义拷贝赋值函数.

但是我们已经定义了如何拷贝构造, 则通过旧对象 :cpp:`other` 可以拷贝得到一个新对象, 那么如果我们能交换这个新对象和已有对象的内容, 岂不是说已有对象就是 :cpp:`other` 的拷贝了?

.. code-block:: cpp
  :linenos:

  Dynamic_array other{/*...*/};

  Dynamic_array 已有对象;

  Dynamic_array copy{other};
  /* 交换已有对象和 copy 的内容 */

  // 此后, 已有对象就是 other 的拷贝

为此我们需要定义 :cpp:`Dynamic_array` 如何进行交换. 显然只需要交换对象的所有成员即可:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    void swap(Dynamic_array& other) {
      using std::swap;           // 先 using std::swap;
      swap(size_, other.size_);  // 再使用没有任何限定的 swap
      swap(data_, other.data_);
    }

    /* ... */
  };

交换的双方地位是对等的, 但 :cpp:`array.swap(other)` 这样的语法则显得 :cpp:`array` 是交换的主动方, 这就显得不太合理, 因此应该将 :cpp:`swap` 作为非成员函数 :cpp:`swap(lhs, rhs)`. 而为了访问私用成员, 我们将 :cpp:`swap` 函数设为友元函数:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    friend void swap(Dynamic_array& lhs, Dynamic_array& rhs) {
      using std::swap;             // 先 using std::swap;
      swap(lhs.size_, rhs.size_);  // 再使用没有任何限定的 swap
      swap(lhs.data_, rhs.data_);
    }

    /* ... */
  };

.. admonition:: 别看: 为什么要先 :cpp:`using std::swap;`
  :class: dontread, dropdown

  别人写的函数叫 :cpp:`print`, 你写的函数也叫 :cpp:`print`, 这可能引起冲突. C++ 为此就引入了名字空间的概念, 将代码用名字空间包裹起来就意味着它属于这个名字空间:

  .. code-block:: cpp
    :linenos:

    namespace fc {
      void print() {  // 这是 FeignClaims 的输出函数
        /* ... */
      }
    }

  所以 :cpp:`std::swap(lhs, rhs)` 这样限定了的函数调用就是说: 我要使用 :cpp:`std`, 即标准库名字空间里的 :cpp:`swap` 函数.

  但别人也可能定义 :cpp:`swap` 函数, 甚至你自己就在定义 :cpp:`swap` 友元函数. 当我们使用不加限定的 :cpp:`swap(lhs, rhs)` 时, 函数除了根据名字空间, 还能根据参数被正确查询到.

  综上两者, 我们先用 :cpp:`using std::swap;` 将标准库中的泛用 :cpp:`swap` 函数引入进来, 再用不加限定的 :cpp:`swap` 是最合适的: 既能使用大伙为自己设计的类自定义的 :cpp:`swap` 函数, 又能以 :cpp:`std::swap` 函数作为备选.

  这也是将 :cpp:`swap` 函数定义为友元函数的一个原因. (当然其实还有几个原因, 这里不再解释.)

  事实上, 我们常写的 :cpp:`using namespace std;` 就是将整个 :cpp:`std` 名字空间里的内容引入进来.

我们于是将拷贝赋值函数定义为: :godbolt:`qb3dqov4v`

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    Dynamic_array& operator=(Dynamic_array const& other) {
      Dynamic_array temp{other};  // 用 other 拷贝一个新对象
      swap(*this, temp);          // 交换 *this 和 temp 的内容
      return *this;
    }  // temp 的析构函数将会清理交换来的内容

    /* ... */
  };

你只需要写好拷贝构造函数和析构函数, 就能直接定义拷贝赋值函数, 这样的方法称为 :doc:`copy-and-swap 惯用法 </faq/copy_functions_parameter/main>`.

========================================================================================================================
重设动态数组的长度
========================================================================================================================

我们希望通过 :cpp:`array.resize(int new_size)` 来重设数组的大小, 但保持数组的内容不变:

- 如果长度变长或不变, 原来 :cpp:`Dynamic_array` 中所有元素内容 (:cpp:`size_` 个) 全部保持, 新元素设为 0.
- 如果长度变短, 原来 :cpp:`Dynamic_array` 中前 :cpp:`new_size` 个元素内容全部保持.

也就是说, 我们申请 :cpp:`new_size` 长度的新数组, 再将原来数组中前 :cpp:`min(new_size, size_)` 个元素拷贝到新数组中.

可以发现, 这依旧能沿用 copy-and-swap 的逻辑, 只是改成了 construct-and-swap: :godbolt:`Ys143Kh79`

.. code-block:: cpp
  :linenos:

  #include <algorithm>  // for std::min

  class Dynamic_array {
   public:
    void resize(int new_size) {
      Dynamic_array temp{new_size};
      copy_n(data_, std::min(size_, new_size), temp.data_);

      swap(*this, temp);
    }

    /* ... */
  };

========================================================================================================================
连接两个动态数组
========================================================================================================================

所谓连接两个动态数组, 即由数组 :cpp:`{0, 1, 2}` 和 :cpp:`{2, 3, 4}` 得到 :cpp:`{0, 1, 2, 2, 3, 4}`. 这和重设动态数组长度的逻辑十分类似, 你甚至可以复用 :cpp:`resize(int new_size)` 来做到.

但此处我不打算复用 :cpp:`resize(int new_size)`, 而向你展示精心设计的 :cpp:`<algorithm>` 算法的魅力.

------------------------------------------------------------------------------------------------------------------------
:cpp:`operator+(lhs, rhs)`
------------------------------------------------------------------------------------------------------------------------

按 :cpp:`int` 行为, :cpp:`lhs + rhs` 是创建一个新对象来保存相加后的结果, 而 :cpp:`lhs` 和 :cpp:`rhs` 不变, 所以我们实现的 :cpp:`operator+` 也不应该修改 :cpp:`lhs` 和 :cpp:`rhs`.

为此我们可以按值传参, 也可以按 :cpp:`const&` 传参; 为了避免对大数组进行拷贝, 我选择按 :cpp:`const&` 传参而非按值传参.

清楚了参数的选择, 我们再来看看函数的实际逻辑:

1. 申请一个动态数组, 它的长度是 :cpp:`lhs.size() + rhs.size()`.
2. 将 :cpp:`lhs` 和 :cpp:`rhs` 的元素依次拷贝到新数组中.

这次要拷贝两个数组, 总不能用 :cpp:`copy_n` 了吧? ……还记得 :cpp:`copy_n` 的返回值吗:

.. code-block:: cpp
  :linenos:
  :emphasize-lines: 4

  // 将 [input, input + size) 从左到右拷贝到 [output, output + size) 中
  //
  // 返回值::
  //   返回 output + size, 即如果继续对 output 进行拷贝, 应该使用的指针.
  value_type* copy_n(value_type const* input, int size, value_type* output) {
    for (int i{0}; i < size; ++i) {
      output[i] = input[i];
    }
    return output + size;
  }

"如果继续对 output 进行拷贝, 应该使用的指针": :godbolt:`eE4Mjh45a`

.. code-block:: cpp
  :linenos:
  :emphasize-lines: 7-9

  class Dynamic_array {
   public:
    friend Dynamic_array operator+(Dynamic_array const& lhs,
                                   Dynamic_array const& rhs) {
      Dynamic_array result(lhs.size() + rhs.size());

      value_type* output{&result.data_[0]};
      output = copy_n(lhs.data_, lhs.size_, output);
      output = copy_n(rhs.data_, rhs.size_, output);

      return result;
    }

    /* ... */
  };

------------------------------------------------------------------------------------------------------------------------
:cpp:`operator+=(other)`
------------------------------------------------------------------------------------------------------------------------

:cpp:`self += other` 与之前所见的 :cpp:`swap` 或 :cpp:`operator+` 不同, 它的左右参数地位不是对等的: 当我们使用 :cpp:`operator+=`, 是达到与 :cpp:`operator=` 即赋值运算符类似的效果, 是将 :cpp:`other` 的内容添加到 :cpp:`self` 上. 因此应该将 :cpp:`operator+=` 定义为成员函数.

但我们仍能复用 :cpp:`operator+(lhs, rhs)` 来实现它: :godbolt:`aKxr34esz`

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    // ↓ 按赋值运算符的惯例, 返回 *this 引用
    Dynamic_array& operator+=(Dynamic_array const& other) {
      *this = *this + other;
      return *this;
    }

    /* ... */
  };

.. seealso::

  - :doc:`/faq/basic_concepts/operator_overloading` 中展示了常见运算符像这样模仿 :cpp:`int` 的行为进行实现的示例.

========================================================================================================================
比较动态数组
========================================================================================================================

我们接下来定义动态数组的比较关系, 从而允许 :cpp:`Dynamic_array` 进行 :cpp:`lhs == rhs` 和 :cpp:`lhs < rhs` 这样的比较.

与 :cpp:`swap` 类似, 比较的双方地位是对等的, 应该定义为友元函数.

------------------------------------------------------------------------------------------------------------------------
相等性: :cpp:`bool operator==(lhs, rhs)`
------------------------------------------------------------------------------------------------------------------------

什么样的两个动态数组才是相等的呢? 首先长度要相等, 其次相同下标下的元素也要相等.

我们应该传递引用传参而非拷贝传参, 为什么呢? 想一想什么叫拷贝: 用原对象构造/赋值一个对象, 使得该对象与原对象 **相等**. 但我们现在就是在定义什么是相等, 没定义之前凭什么说拷贝的结果相等呢? 因此我们不能让相等比较依赖于拷贝行为.

所以相等比较应该是:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    friend bool operator==(Dynamic_array const& lhs, Dynamic_array const& rhs) {
      if (lhs.size() != rhs.size()) {  // 长度是否相等
        return false;
      }

      for (int i{0}; i < lhs.size_; ++i) {
        if (lhs.data_[i] != rhs.data_[i]) {  // 同一下标下的元素是否相等
          return false;
        }
      }
      return true;
    }

    /* ... */
  };

至于 :cpp:`bool operator!=(lhs, rhs)`, 我们复用 :cpp:`operator==`:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    friend bool operator!=(Dynamic_array const& lhs, Dynamic_array const& rhs) {
      return !(lhs == rhs);
    }

    /* ... */
  };

最终得到: :godbolt:`drTPGdsfx`

------------------------------------------------------------------------------------------------------------------------
等价性、偏序关系: :cpp:`bool operator<(lhs, rhs)`
------------------------------------------------------------------------------------------------------------------------

动态数组的偏序关系通常定义为字典序, 即词典排列单词的顺序.

对于 :cpp:`lhs < rhs`:

1. 从左到右依次比较各元素

   - :cpp:`lhs[i] < rhs[i]`: :cpp:`lhs` 更小, 返回 :cpp:`true`.
   - :cpp:`lhs[i] == rhs[i]`: 比较下一对元素.
   - :cpp:`lhs[i] > rhs[i]`: :cpp:`rhs` 更小, 返回 :cpp:`false`.

2. 相同长度部分都比较完毕

   - :cpp:`lhs.size() < rhs.size()`: 说明 :cpp:`lhs` 是 :cpp:`rhs` 的前缀, 想想词典是怎么排列 a 和 ab 的, 返回 :cpp:`true`.
   - :cpp:`lhs.size() == rhs.size()`: 说明两个数组相等, 返回 :cpp:`false`.
   - :cpp:`lhs.size() > rhs.size()`: 说明 :cpp:`rhs` 是 :cpp:`lhs` 的前缀, 想想词典是怎么排列 ab 和 a 的, 返回 :cpp:`false`.

所以小于比较应该是:

.. code-block:: cpp
  :linenos:

  #include <algorithm>  // for std::min

  class Dynamic_array {
   public:
    friend bool operator<(Dynamic_array const& lhs, Dynamic_array const& rhs) {
      // 比较同长部分:
      //  - 小于: lhs 更小, 返回 true
      //  - 等于: 比较下一个字符
      //  - 大于: rhs 更小, 返回 false
      int const min_size{std::min(lhs.size_, rhs.size_)};
      for (int i{0}; i < min_size; ++i) {
        if (lhs.data_[i] < rhs.data_[i]) {
          return true;
        }
        if (lhs.data_[i] > rhs.data_[i]) {
          return false;
        }
      }

      // 同长部分已经比较完毕
      //  - lhs.size_ <  rhs.size_: 说明 lhs 是 rhs 的前缀, 想想词典是怎么排列 a 和 at 的, 返回 true
      //  - lhs.size_ == rhs.size_: 相同, 返回 false
      //  - lhs.size_ >  rhs.size_: 说明 rhs 是 lhs 的前缀, 想想词典是怎么排列 at 和 a 的, 返回 false
      return lhs.size_ < rhs.size_;
    }

    /* ... */
  };

至于 :cpp:`bool operator>(lhs, rhs)` 等比较, 我们复用 :cpp:`operator<`:

.. code-block:: cpp
  :linenos:

  #include <algorithm>  // for std::min

  class Dynamic_array {
   public:
    friend bool operator>(Dynamic_array const& lhs, Dynamic_array const& rhs) {
      return rhs < lhs;
    }
    friend bool operator<=(Dynamic_array const& lhs, Dynamic_array const& rhs) {
      return !(rhs < lhs);
    }
    friend bool operator>=(Dynamic_array const& lhs, Dynamic_array const& rhs) {
      return !(lhs < rhs);
    }

    /* ... */
  };

最终得到: :godbolt:`MMv73G61f`

.. hint::

  当然 :cpp:`<algorithm>` 里也有 :cpp:`equal`、:cpp:`lexicographical_compare`、:cpp:`mismatch` 等比较两范围的算法, 这里为了避免说得太多就没用了.

.. seealso::

  - :doc:`/faq/basic_concepts/operator_overloading` 中展示了常见运算符像这样模仿 :cpp:`int` 的行为进行实现的示例.

========================================================================================================================
输出动态数组
========================================================================================================================

调用 :cpp:`print` 函数实在太麻烦了, 让我们的动态数组也支持 :cpp:`std::cout << value` 吧.

这其实没什么大不了的, 只是重载 :cpp:`operator<<(std::ostream& ostream, Dynamic_array const& array)` 罢了: :godbolt:`5vGqjGsWx`

.. code-block:: cpp
  :linenos:
  :caption: :cpp:`print` 函数

  // 按 [a0, a1, a2, ..., an] 的形式输出数组
  void print(Dynamic_array const& array) {
    std::cout << '[';
    for (int i{0}; i < array.size(); ++i) {
      std::cout << (i == 0 ? "" : ", ") << array[i];
    }
    std::cout << ']';
    return ostream;
  }

.. code-block:: cpp
  :linenos:
  :caption: 重载输出运算符

  #include <ostream>  // for std::ostream

  class Dynamic_array {
   public:
    //     ↓ 按约定返回 ostream 的引用
    friend std::ostream& operator<<(std::ostream& ostream,
                                    Dynamic_array const& array) {
      ostream << '[';
      for (int i{0}; i < array.size(); ++i) {
        ostream << (i == 0 ? "" : ", ") << array[i];
      }
      ostream << ']';
      return ostream;
    }

    /* ... */
  };

.. seealso::

  - :doc:`/faq/basic_concepts/operator_overloading` 中展示了常见运算符像这样模仿 :cpp:`int` 的行为进行实现的示例.

========================================================================================================================
让动态数组能包含其他类型的数据
========================================================================================================================

我们之前使用 :cpp:`using value_type = int;`, 从而淡化了动态数组存储的数据而专注于动态数组的设计. 其实这样做还带来另一个好处: 我们只需更改 :cpp:`using value_type = ...;` 为其他类型, 就能让动态数组包含其他类型的数据!

.. code-block:: cpp
  :linenos:

  using value_type = double;  // 现在, 动态数组存储的是 double 类型数据
  // ...

那么如果我想让动态数组存储学生类呢?

.. code-block:: cpp
  :linenos:

  struct Student {
    std::string id;
    std::string name;
  };

  using value_type = Student;

但当你编译生成会发现这样修改后会报错, 为什么呢? 因为我们对 :cpp:`value_type` 进行了比较、输出等操作, 而 :cpp:`Student` 并不支持这些操作. 你需要真正地去学习 :doc:`运算符重载 </faq/basic_concepts/operator_overloading>` 并为 :cpp:`Student` 重载比较运算符和输出操作等.

========================================================================================================================
整个动态数组类的附解释代码
========================================================================================================================

:godbolt:`Yc6e5Pf4M`

========================================================================================================================
扩展: 让动态数组能包含任何类型的数据
========================================================================================================================

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/template`

那有没有一种方法, 让动态数组能包含任意类型的数据呢? 我们代码里也许同时需要 :cpp:`int` 类型的动态数组和 :cpp:`double` 类型的动态数组.

为此我们使用 :doc:`模板 </faq/basic_concepts/template>`, 它将类型作为参数, 基于提供的参数生成对应的代码.

.. code-block:: cpp
  :linenos:

  template <typename T>
  struct Dynamic_array {
   public:
    // 所有的 value_type 都换成 T, 或者:
    using value_type = T;

    /* ... */

   private:
    int size_;
    value_type* data_;
  };

========================================================================================================================
扩展: 让动态数组支持上百种算法
========================================================================================================================

见于 :doc:`/faq/range_iterator_and_algorithm/main`.

========================================================================================================================
扩展: 让动态数组能够列表初始化
========================================================================================================================

数组还有一个很便利的特性——在初始化时列表初始化各个元素:

.. code-block:: cpp
  :linenos:

  int main() {
    int array[4]{0, 1, 2, 3};  // {0, 1, 2, 3}
  }

我们也能让 :cpp:`Dynamic_array` 支持这种功能, 为此需要定义 :cpp:`Dynamic_array(std::initializer_list<value_type>)`:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    // 这个函数和拷贝构造函数一样, 也是不需要加 explicit 的特例
    Dynamic_array(std::initializer_list<value_type> init_list)
        : size_{init_list.size()}
          data_{init_list.size() == 0 ? nullptr : new value_type[init_list.size()]} {
      copy_n(init_list.data(), init_list.size(), data_);
    }

    /* ... */
  };

但要注意, 使用 :cpp:`{}` 进行初始化时会优先考虑 :cpp:`Dynamic_array(std::initializer_list<value_type>)` 而非其他同样可用的构造函数, 如果需要其他构造函数, 应该在合适时候使用 :cpp:`()` 进行初始化: (这就是生活😭)

.. code-block:: cpp
  :linenos:

  int main() {
    Dynamic_array array0{5};  // {5}
    Dynamic_array array1(5);  // {0, 0, 0, 0, 0}
  }

知道了这一点, 我们就能再委托 :cpp:`Dynamic_array(int size)` 分配数组:

.. code-block:: cpp
  :linenos:

  class Dynamic_array {
   public:
    Dynamic_array(std::initializer_list<value_type> init_list)
        : Dynamic_array(init_list.size()) {
      copy_n(init_list.data(), init_list.size(), data_);
    }

    Dynamic_array(Dynamic_array const& other) : Dynamic_array(other.size_) {
      copy_n(other.data_, other.size_, data_);
    }

    /* ... */
  };

========================================================================================================================
扩展: 让动态数组支持高效的移动
========================================================================================================================

定义拷贝函数后, 我们不再能高效地返回动态数组:

.. code-block:: cpp
  :linenos:
  :caption: 未定义拷贝函数时

  value_type* make_array() {
    value_type* array{new value_type[1000]{}};
    /* ... */
    return array;  // 返回只需要拷贝指向数组首元素的指针
  }  // 局部变量 array 被析构, 这没什么, 它只是指向数组首元素的指针

.. code-block:: cpp
  :linenos:
  :caption: 定义拷贝函数时

  Dynamic_array make_array() {
    Dynamic_array array(1000);
    /* ... */
    return array;  // 返回时拷贝整个数组
  }  // 局部变量 array 被析构, 我们平白无故拷贝了它一份作为返回, 又析构它本身

发现了吗? 对于有的情况 (尤其是当我们在函数内构造了动态数组, 且想要返回这个数组时), 我们只想拷贝指针, 从而复用这个数组. C++11 为此添加了移动语义, 它表达对资源的转移而非对资源进行拷贝.

要想让类支持移动语义, 我们需要定义移动构造函数和移动赋值函数; 但在定义之前, 让我们学习另一个组件函数.

------------------------------------------------------------------------------------------------------------------------
:cpp:`std::exchange` 组件
------------------------------------------------------------------------------------------------------------------------

:cpp:`exchange(object, new_value)` 将 :cpp:`new_value` 赋给 :cpp:`object`, 并返回 :cpp:`object` 的旧值:

.. code-block:: cpp
  :linenos:

  #include <utility>  // for std::exchange

  int value = 5;
  std::cout << std::exchange(value, 3);  // 输出 5
  std::cout << value;  // 输出 3

这让数据像是水流一样, 从右边流向左边:

.. code-block:: cpp
  :linenos:

  #include <utility>  // for std::exchange

  // value1 == 0, value2 == 1
  int value1 = 0;
  int value2 = 1;

  // 返回 0, value1 == 1, value2 == 2
  std::exchange(value1, std::exchange(value2, 2));

------------------------------------------------------------------------------------------------------------------------
定义移动构造和移动赋值函数
------------------------------------------------------------------------------------------------------------------------

由此, 我们可以这样定义移动构造函数和移动赋值函数:

.. code-block:: cpp
  :linenos:

  #include <utility>  // for std::move

  class Dynamic_array {
   public:
    // 移动构造函数将资源从 other 转移到本对象中
    //  因此将 other.data_ 的值赋给 data_, 并将 other.data_ 设为 nullptr
    //  而 other.size_ 同理
    Dynamic_array(Dynamic_array&& other)
        : size_{std::exchange(other.size_, 0)},
          data_{std::exchange(other.data_, nullptr)} {}

    // 用定义好的移动构造函数、析构函数来实现移动赋值函数
    Dynamic_array& operator=(Dynamic_array&& other) {
      Dynamic_array temp{std::move(other)};  // 移动构造
      swap(*this, temp);
      return *this;
    }
  };

此后, 当我们将局部动态数组对象作为返回值时, 它将调用移动函数而非拷贝函数:

.. code-block:: cpp
  :linenos:

  Dynamic_array make_array() {
    Dynamic_array array(1000);
    /* ... */
    return array;  // 返回时移动整个动态数组
  }  // 局部变量 array 被析构, 没事, 它的 array.data_ 已经是 nullptr 了
