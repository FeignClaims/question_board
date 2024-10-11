.. _lifetime:

########################################################################################################################
生命期 (lifetime): 带输出的构造、析构如何阅读?
########################################################################################################################

.. admonition:: 前置内容
  :class: precontent

  - :doc:`/faq/basic_concepts/object`

考试中这类题目所关注的是构造函数和析构函数的调用时机, 即对象的生命期什么时候开始、什么时候结束.

对象的生老病死为:

对象被创建/构造 (created/constructed)
  1. 对象所需的存储空间 (storage) 被分配 (allocated).
  2. 对象被初始化 (initialized) [#1]_, 进而开始 (begins) 其生命期 (lifetime). 这个过程中, 自定义类型的构造函数将被调用.

对象被使用
  3. 在对象的生命期期间, 它可以根据其类型被合法使用.

对象被销毁 (destroyed)
  4. 对象被销毁 (destroyed), 进而结束 (ends) 其生命期. 这个过程中, 自定义类型的析构函数将被调用.
  5. 对象所用的存储空间被解分配 (deallocated).

.. [#1] 这里的初始化包括默认初始化 (如 :cpp:`std::string string;`) 中实际不进行初始化的情况 (如 :cpp:`int value;`).

由此, 对象具有两个属性: 生命期 (lifetime) 和存储周期 (storage duration).

生命期
  只有在对象的生命期期间, 对象才被认为是合法的, 可以根据其类型被合法使用.

  .. code-block:: cpp
    :linenos:
    :emphasize-lines: 9

    int* function() {
      int value;  // value 被创建 (分配存储空间 + 开始生命期)
      value = 0;  // 生命期内, int 类型的 value 可以被赋值
      return &value;
    }  // value 被销毁 (结束生命期 + 解分配存储空间)

    int main() {
      int* pointer = function();
      *pointer     = 10;  // 未定义行为: 对象的生命期已经结束
    }

存储周期
  存储周期描述什么时候为对象分配存储空间和初始化对象, 以及该存储空间会存在多久. 显然, 在对象的生命期期间其存储空间必须存在, 所以存储周期决定了对象的生命期最长能持续多久.

  在课程范围内, 对象的生命期总是与存储空间的持续时间等同.

  .. admonition:: 别看: 对象的生命期可以短于存储空间的持续时间
    :class: dontread, dropdown

    .. code-block:: cpp
      :linenos:

      // 假设 sizeof(int) == sizeof(float)
      int main() {
        int i;  // i 被创建 (分配存储空间 + 开始生命期)
        i = 1;

        float* f = new (&i) float;  // i 结束生命期, f 开始生命期
        f = 1.5;

        // i = 1;  // 未定义行为: i 的生命期已经结束
      }  // f 被销毁 (结束生命期 + 解分配存储空间)

.. warning::

  由于不清楚考试如何给的答案, 练习题中没有涉及一些模糊的和强制禁止优化也会被优化掉的地方 (例如用函数返回值构造具名对象).

.. toctree::
  :maxdepth: 1
  :caption: 目录

  preface.rst
  automatic_storage_duration.rst
  static_storage_duration.rst
  dynamic_storage_duration.rst
  thread_local_storage_duration.rst
  temporary_object.rst
  mix.rst