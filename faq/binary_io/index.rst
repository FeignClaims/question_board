***********************************************************************************************************************
二进制输入输出 (binary I/O)
***********************************************************************************************************************

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/object`
  - :doc:`/faq/basic_concepts/type_conversion`
  - :doc:`/faq/basic_concepts/pointer`

这是一种序列化方式. 所谓序列化就是将对象转换为一种特定的格式 (序列化), 从而可以传输或存储, 而又能从这种特定格式转换为程序中的对象 (反序列化).

一般只是简单考一下, 记住怎么做即可.

=======================================================================================================================
二进制输出
=======================================================================================================================

:cpp:`ofile.write(char const* string, streamsize count)`
  将 :cpp:`[string, string + count)` 字符数组输出到 :cpp:`ofile` 中, 所以我们要将对象强行转换为字符数组.

.. code-block:: cpp
  :linenos:

  #include <fstream>

  int value = 0;

  // ofstream 会自动为打开方式加上 std::ios_base::out, 因此直接写 std::ios_base::binary 就行了
  std::ofstream ofile("输出文件路径", std::ios_base::binary);
  ofile.write(reinterpret_cast<char const*>(&value), sizeof(value));

=======================================================================================================================
二进制输入
=======================================================================================================================

:cpp:`ifile.read(char* string, streamsize count)`
  从 :cpp:`ifile` 读入字符到 :cpp:`[string, string + count)` 字符数组中, 所以我们要将对象强行转换为字符数组.

.. code-block:: cpp
  :linenos:

  #include <fstream>

  int value = 0;

  // ifstream 会自动为打开方式加上 std::ios_base::in, 因此直接写 std::ios_base::binary 就行了
  std::ifstream ifile("输入文件路径", std::ios_base::binary);
  ifile.read(reinterpret_cast<char*>(&value), sizeof(value));

========================================================================================================================
:cpp:`std::string` 二进制输出到文件后不能正常读取?
========================================================================================================================

现在, 假设我们要编写 :cpp:`Person` 类, 它会有一个名字数据成员和一个年龄数据成员. 名字的长度很难确定, 所以我们用 :cpp:`std::string` 作为名字的类型:

.. code-block:: cpp
  :linenos:

  struct Person {
   public:
    std::string name;
    int age;
  };

而题目要求我们以二进制形式将 :cpp:`Person` 输出到文件, 再从文件中读取它:

.. code-block:: cpp
  :linenos:

  void serialize(std::ostream& ostream, Person const& person) {
    ostream.write(reinterpret_cast<char const*>(&person), sizeof(person));
  }

  void deserialize(std::istream& istream, Person& person) {
    istream.read(reinterpret_cast<char*>(&person), sizeof(person));
  }

然而, 当我们使用这个序列化函数将 :cpp:`Person` 输出到文件, 关闭程序, 再用反序列化函数从文件中读取 :cpp:`Person` 时, 发现读取的内容并不正常, 甚至在之后使用时可能直接报错了!

这是因为与 :cpp:`int` 等类型不同, :cpp:`std::string` 除了栈上的指针还有堆上的字符数组, 而这样的 :cpp:`ostream.write` 仅仅输出了 :cpp:`std::string` 成员的指针部分.

栈? 堆? 如果还不了解它们也没关系, 让我们把这个问题转换为更熟悉的情况:

.. code-block:: cpp
  :linenos:

  struct Widget {
   public:
    int* pointer;
  };

  int main() {
    int value = 0;

    Widget widget;
    widget.pointer = &value;  // pointer 指向 value

    std::ofstream ofile("输出文件路径", std::ios_base::binary);
    ofile.write(reinterpret_cast<char const*>(&widget), sizeof(widget));
  };

对 :cpp:`widget` 进行二进制输出, 会连同 :cpp:`value` 一起输出出去吗? 不是的, :cpp:`Widget` 类只有 :cpp:`pointer` 是数据成员; :cpp:`value` 虽然被 :cpp:`pointer` 指向, 但不是 :cpp:`Widget` 类的数据成员.

这样有远程 (remote) 部分 [#1]_ 的类都不能直接进行二进制输入输出. 如果实在需要二进制输入输出它们, 你需要根据其数据的逻辑关系 (:doc:`类的不变式 </faq/class_invariant/index>`) 为它定义如何二进制输入输出.

.. [#1] 这个说法出自《Elements of Programming》

.. hint::

  如果只是为了做作业, 请使用 :cpp:`std::array<char, 100>` 或 :cpp:`char array[100]` 这种没有远程部分的数组解决.

  **这种写法只有考试喜欢.** 项目如果需要序列化, 会选择用 `序列化库 <https://github.com/fffaraz/awesome-cpp?tab=readme-ov-file#serialization>`_ 将数据序列化为更高效的结构, 而不是折腾这样直接的二进制输入输出.

例如, 对于 :cpp:`std::string`, 你可以输出其长度和实际内容:

.. code-block:: cpp
  :linenos:

  void serialize(std::ostream& ostream, std::string const& string) {
    // 长度
    int size = string.size();
    ostream.write(reinterpret_cast<char const*>(&size), sizeof(size));

    // 实际内容                     ↓ 单个元素的大小 * 元素数量
    ostream.write(string.c_str(), sizeof(char) * size);
  }

  void deserialize(std::istream& istream, std::string& string) {
    // 长度
    int size = 0;
    istream.read(reinterpret_cast<char*>(&size), sizeof(size));

    // 根据读取字符串的长度给当前的 string 设置好长度
    string.resize(size);

    // 实际内容
    istream.read(string.data(), sizeof(char) * size);
  }

  void serialize(std::ostream& ostream, Person const& person) {
    serialize(ostream, person.name);
    ostream.write(reinterpret_cast<char const*>(&person.age), sizeof(person.age));
  }

  void deserialize(std::istream& istream, Person& person) {
    deserialize(istream, person.name);
    istream.read(reinterpret_cast<char*>(&person.age), sizeof(person.age));
  }