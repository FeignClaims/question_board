************************************************************************************************************************
C 风格数组: :cpp:`T array[size]` (C-style array)
************************************************************************************************************************

有时候我们不止需要一个对象, 而需要一组同类型的对象.

由此有了 C 风格数组 :cpp:`T array[size]`, 它连续存储一组同类型的对象 (称为数组中的元素), 并允许以 :cpp:`array[index]` 方式访问对应位置的元素.

.. code-block:: cpp
  :linenos:

  int array[5] = {0, 1, 2, 3, 4};
  sizeof(array)    == sizeof(int) * 5;  // 连续存储了 5 个元素, 自然大小是 sizeof(int) * 5 了
  sizeof(array[0]) == sizeof(int);      // array[0] 访问第一个位置的元素

  for (int i = 0; i < 5; ++i) {  // 输出数组内元素
    std::cout << array[i] << ' ';
  }
  std::cout << '\n';

需要注意的是, C++ 标准下 C 风格数组的长度必须是一个常量.

.. code-block:: cpp
  :linenos:

  int size;
  std::cin >> size;
  int array[size];  // 错误: size 在编译时未知, 运行时才输入了值

你可以省略长度而在声明时初始化, 编译器会根据初始化列表推测数组长度.

.. code-block:: cpp
  :linenos:

  int array[]    = {1, 2, 3, 4, 5};
  int const size = sizeof(array) / sizeof(array[0]);  // 长度为 5

========================================================================================================================
记录数组的长度
========================================================================================================================

在上面的代码中, 我们直接在需要用到数组的位置, 填入它的长度 :cpp:`5`, 但我们凭什么说代码里遇到的 :cpp:`5` 都是数组的长度呢? 想象一下, 你用 :cpp:`int array[5]` 编写了一千行代码, 后来需要将数组的长度 :cpp:`5` 改为 :cpp:`10`, **你需要仔细地查看一千行代码, 一个个改动.**

更好的方法是, 使用一个变量存储数组的长度, 以后只需要改变这个变量的值.

.. code-block:: cpp
  :linenos:

  int const size  = 5;  // 这和 const int size 是等价的
  int array[size] = {0, 1, 2, 3, 4};

  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << ' ';
  }
  std::cout << '\n';

.. seealso::

  - :doc:`/faq/coreguidelines/es_45`

========================================================================================================================
C 风格数组很容易隐式类型转换为指向首元素的指针
========================================================================================================================

C 风格数组 **很容易很容易很容易** 隐式类型转换为指向首元素的指针, 

比如参与运算时,

.. code-block:: cpp
  :linenos:

  int array[5] = {0, 1, 2, 3, 4};
  sizeof(array)     == sizeof(int) * 5;  // 数组本身的大小
  sizeof(+array)    == sizeof(int*);     // 算术运算时转换为首元素的指针
  sizeof(array + 0) == sizeof(int*);     // 算术运算时转换为首元素的指针
  sizeof(array + 1) == sizeof(int*);     // 算术运算时转换为首元素的指针, +1 后为第二个元素的指针

比如发生拷贝时,

.. code-block:: cpp
  :linenos:

  int array[5] = {0, 1, 2, 3, 4};
  // ↓ auto: 我不知道它的类型是啥, 但我是通过拷贝 array 得到的 value, 编译器你自己分析类型是啥
  auto value = array;  // 拷贝时转换为首元素的指针
  sizeof(value) == sizeof(int*);

  int* pointer = array;  // 与上面等价
  sizeof(pointer) == sizeof(int*);  

  sizeof(array) == sizeof(int) * 5;  // 隐式类型转换是产生了新的对象或引用, 原对象或引用不会发生变化

如果是在一个函数中, 这样做没有什么影响, 毕竟指针也可以以下标访问内容,

.. code-block:: cpp
  :emphasize-lines: 5
  :linenos:

  int array[5] = {0, 1, 2, 3, 4};
  int* pointer = array;

  for (int i = 0; i < 5; ++i) {
    pointer[i] = 0;
  }

你可以认为, :cpp:`pointer[i]` 与 :cpp:`*(pointer + i)` 等价, 是按照被指向类型的大小发生偏移, 然后解引用,

.. figure:: begin_size.gif

  指针的偏移

.. code-block:: cpp
  :emphasize-lines: 5
  :linenos:

  int array[5] = {0, 1, 2, 3, 4};
  int* pointer = array;

  for (int i = 0; i < 5; ++i) {
    *(pointer + i) = 0;
  }

========================================================================================================================
数组的传参
========================================================================================================================

------------------------------------------------------------------------------------------------------------------------
问题
------------------------------------------------------------------------------------------------------------------------

我们需要向函数传递数组, 而有时候函数并不应该改变数组的内容, 所以我们应该拷贝数组, 对吧?

.. code-block:: cpp
  :emphasize-lines: 2, 10
  :linenos:

  void function(int array[5]) {
    array[0] = 5;
  }

  int main() {
    int array[5] = {0, 1, 2, 3, 4};

    function(array);

    for (int i = 0; i < 5; ++i) {  // 注意: 输出 5 1 2 3 4
      std::cout << i << ' ';
    }
    std::cout << '\n';
  }

这怎么会影响到 :cpp:`main` 函数里的 :cpp:`array`? 我们在 :doc:`/faq/basic_concepts/function` 中得知, 传参可以当作声明变量来理解, 回顾一下, 我们刚刚用数组拷贝创建新变量时发生了什么?

.. code-block:: cpp
  :linenos:

  int array[5] = {0, 1, 2, 3, 4};
  auto value = array;  // 这个 value 是指向数组首元素的指针!

所以, 我们看起来是拷贝了数组, 实际上只是获取了指向数组首元素的指针.

这样拷贝后两个变量实际是指向同一个对象的语义, 称为引用语义; 与之相对地, 像 :cpp:`int` 那样拷贝后得到确确实实的新对象, 与原来的对象完全独立, 称为值语义. **尽量避免引用语义.**

.. hint::

  你也可以使用断点调试自己验证一下函数内 :cpp:`array` 的实际类型. 断点调试非常有用, 请学习 :doc:`/debugger/main` 并完成习题.

甚至, 以下函数实际是同样的函数:

.. code-block:: cpp
  :linenos:

  // 实际都是 void function(int* array)
  void function(int* array);
  void function(int array[]);
  void function(int array[5]);

好吧, 为了避免对不知道这条规则的人的欺骗, 让我们将函数直接写成 :cpp:`void function(int* array)`, 由此可推测, 如果我们确实不想改动数组, 我们可以用 :cpp:`void function(int const* array)`.

但现在的问题是, 仅仅传入指向数组首元素的指针就够了吗?

.. code-block:: cpp
  :emphasize-lines: 2, 8
  :linenos:

  void function(int* array) {
    for (int i = 0; i < 5; ++i) {  // 长度为 5
      array[i] = 0;
    }
  }

  int main() {
    int array[3] = {1, 2, 3};  // 长度为 3
    function(array);
  }

我们在函数内不知道数组的长度是多少, 更具体地, 我们不知道什么时候结束!

------------------------------------------------------------------------------------------------------------------------
解决方案: :cpp:`(int* array, int size)`
------------------------------------------------------------------------------------------------------------------------

不知道数组的长度是多少, 那么我们就传入数组的长度.

.. code-block:: cpp
  :linenos:

  void print(int const* array, int size) {
    for (int i = 0; i < size; ++i) {
      std::cout << array[i] << ' ';
    }
    std::cout << '\n';
  }

.. figure:: begin_size.gif

如何确定传入的数组长度为 :cpp:`0` 呢?

.. code-block:: cpp
  :linenos:

  bool is_empty(int const* array, int size) {
    return size == 0;
  }

.. figure:: begin_size_empty.png

------------------------------------------------------------------------------------------------------------------------
更好的解决方案: :cpp:`(int* begin, int* end)`
------------------------------------------------------------------------------------------------------------------------

不知道什么时候结束, 那么我们就告知什么时候结束, 把指向结束位置的指针——也就是指向末尾元素之后一个位置 (逾尾位置) 的指针——传给函数.

.. code-block:: cpp
  :linenos:

  void print(int const* begin, int const* end) {
    for (; begin != begin; ++begin) {
      std::cout << *begin << ' ';
    }
    std::cout << '\n';
  }

.. figure:: begin_end.gif

你可以简单转换得到数组的长度.

.. code-block:: cpp
  :linenos:

  int size(int const* begin, int const* end) {
    return end - begin;
  }

如何确定传入的数组长度为 :cpp:`0` 呢? 长度为 :cpp:`0` 意味着指向开始位置的指针也指向逾尾位置.

.. code-block:: cpp
  :linenos:

  bool is_empty(int const* begin, int const* end) {
    return begin == end;
  }

.. figure:: begin_end_empty.png

------------------------------------------------------------------------------------------------------------------------
特殊方案: 在数组末尾用一个特殊值表示结束
------------------------------------------------------------------------------------------------------------------------

比如我们以 :cpp:`-1` 作为终止值.

.. code-block:: cpp
  :linenos:

  void print(int const* array) {
    for (; *array != -1; ++array) {
      std::cout << *array << ' ';
    }
    std::cout << '\n';
  }

  int main() {
    int array[6] = {1, 2, 3, 4, 5, -1};
    print(array);
  }

你可以简单遍历得到数组的有效长度.

.. code-block:: cpp
  :linenos:

  void size(int const* array) {
    int count = 0;
    for (; *array != -1; ++array) {
      ++count;
    }
    return count;
  }

  int main() {
    int array[6] = {1, 2, 3, 4, 5, -1};
    int size     = size(array);  // 有效长度为 5
  }

.. hint::

  有没有感觉眼熟? 字符串就是这么做的!
  
  :cpp:`std::strlen(string)` 是怎么获取字符串长度的? 从左到右一直数到 :cpp:`'\\0'`.

  .. code-block:: cpp
    :linenos:

    int my_strlen(char const* string) {
      int count = 0;
      for (; *string != '\0'; ++string) {
        ++count;
      }
      return count;
    }

.. warnings::

  需要注意的是, 这种方式因为需要定义终止值而并不能泛用; 别人要是用你的函数必须也采用同样的终止值.

  想想你的 :cpp:`char array[3] = {'a', 'b', 'c'}` 为什么输出出奇怪的内容! 因为你没有加上终止字符 :cpp:`'\\0'`.

------------------------------------------------------------------------------------------------------------------------
思维启发: 我一定要传入整个数组吗?
------------------------------------------------------------------------------------------------------------------------

请思考以下代码:

.. code-block:: cpp
  :linenos:

  void print(int const* begin, int const* end);

  int main() {
    int array[5] = {0, 1, 2, 3, 4};
    print(array + 1, array + 3);  // 输出 1 2
    print(array + 2, array + 5);  // 输出 2 3 4
  }

========================================================================================================================
最佳实践
========================================================================================================================

- 用另外的变量 (如 :cpp:`int const size`) 记录数组的长度.
- 传参时使用 :cpp:`(int* array, int size)` 或 :cpp:`(int* begin, int* end)`.

更好地, 去学习使用 :cpp:`std::array<T, size>` 和 :cpp:`std::vector<T>`.

========================================================================================================================
相关解答
========================================================================================================================

- :doc:`/faq/variable_decleration_reading/main`
- :doc:`/faq/md_c_array/main`
- :doc:`/faq/c_string_output/main`
- :doc:`/faq/pointer_output/main`
