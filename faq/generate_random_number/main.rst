************************************************************************************************************************
随机数的生成 (random number generation)
************************************************************************************************************************

通常我们生成的随机数并不是真正的随机数, 而是基于一个种子 (seed), 以一定算法生成的伪随机数 (pseudo-random number). 这意味着 **如果使用相同的种子和算法, 将会生成一模一样的数.**

.. hint::

  更建议学习 :ref:`C++随机数`, 它更直接; 不过 Visual Studio 2010 不支持.

.. _C随机数:

========================================================================================================================
C 随机数
========================================================================================================================

我们可以通过 :cpp:`#include <cstdlib>` 中的 :cpp:`rand()` 来生成随机数:

.. code-block:: cpp
  :linenos:

  #include <cstdlib>
  using namespace std;

  int main() {
    cout << (rand() % 10 + 5);  // 输出 [5, 15) 的随机整数.
  }

------------------------------------------------------------------------------------------------------------------------
设置种子
------------------------------------------------------------------------------------------------------------------------

但是当你重新运行程序, 你会发现程序输出了一模一样的结果. 这是因为就像开头说的, 通常我们生成的随机数并不是真正的随机数, 而是基于一个种子 (seed), 以一定算法生成的伪随机数 (pseudo-random number). 这意味着 **如果使用相同的种子和算法, 将会生成一模一样的数.**

所以, 我们需要在程序开始时, 为 :cpp:`rand()` 设置一个种子, 这需要用到 :cpp:`srand()`:

.. code-block:: cpp
  :linenos:

  #include <cstdlib>
  using namespace std;

  int main() {
    srand(5);  // 设置一个种子
    cout << (rand() % 10 + 5);  // 输出 [5, 15) 的随机整数.
  }

但这样的设置显然是不行的: 每次运行所使用的种子都相同, 随机结果也相同. 所以我们需要在每次运行时设置不同的种子, 而每次运行程序, 有什么不同呢? 当前时间.

.. code-block:: cpp
  :linenos:

  int main() {
    time_t current_time = time(nullptr);  // 或 time(0)
    srand(current_time);
    /* 或者 srand(time(nullptr)) */
  }

但要注意, **我们应该只在程序运行开始时设置一次随机数种子**. 程序运行很快, 如果我们在循环内反复获取当前时间作为种子, 那么可能几次循环的种子相同.

.. code-block:: cpp
  :linenos:

  int main () {
    for (int i = 0; i < 10; ++i) {
      srand(time(nullptr));  // 可能设置一样的种子!
      cout << (rand() % 10 + 5);
    }
  }

综上, 正确的方式是:

1. 在程序开始时用 :cpp:`srand` 设置随机数种子为当前时间;
2. 之后按你的需求使用 `rand` 获取随机数.

.. code-block:: cpp
  :linenos:

  int main () {
    srand(time(nullptr));
    for (int i = 0; i < 10; ++i) {
      cout << (rand() % 10 + 5);
    }
  }

------------------------------------------------------------------------------------------------------------------------
随机浮点数
------------------------------------------------------------------------------------------------------------------------

好了, 我们现在生成了整数的随机数, 那么浮点数呢? 浮点数可不能求余.

因此, :cpp:`rand()` 生成的随机数为 :cpp:`[0, RAND_MAX]` 区间的整数, 因此可以采用下面的通用方案 **对应区间的随机数 (整数、浮点数通用)**:

:godbolt:`5d5fsnc8h`

.. tabs::

  .. tab:: 浮点数

    .. code-block:: cpp
      :linenos:

      #include <cstdlib>  // for std::rand

      double min = 0;   // 预期随机数的最小值
      double max = 10;  // 预期随机数的最大值

      // rand() 生成随机数, 转换为 double 与可能最大的随机数相除, 得到一个概率, 取值为 [0, 1]
      double posibility = static_cast<double>(std::rand()) / RAND_MAX;

      // 概率 [0, 1] * 区间长度 = [0, 区间长度]
      double temp = posibility * (max - min);  // 映射到 [0, max - min]

      // [0, max - min] + min = [min, max]
      double value = temp + min;

  .. tab:: 整数

    .. code-block:: cpp
      :linenos:

      #include <cstdlib>  // for std::rand

      double min = 0;   // 预期随机数的最小值
      double max = 10;  // 预期随机数的最大值

      // rand() 生成随机数, 转换为 double 与可能最大的随机数相除, 得到一个概率, 取值为 [0, 1]
      double posibility = static_cast<double>(std::rand()) / RAND_MAX;

      // 概率 [0, 1] * (区间长度 + 1) = [0, 区间长度 + 1]
      double temp = posibility * (max - min + 1);  // +1, 映射到 [0, max - min + 1] 这个区间才是均匀分布
                                                   // 这样 [0, 1) 取整为 0, [max, max + 1) 取整为 max 才是均匀的, 而 max + 1 的概率非常小

      // [0, 区间长度 + 1] + min = [min, max + 1]
      int value = temp + min;

.. warning::

  事实上, C 标准中明确指出, :cpp:`rand()` 不保证生成的随机数列质量. 故对于重要的随机数生成需求不推荐 :ref:`C随机数`, 推荐使用 :ref:`C++随机数`.

.. _C++随机数:

========================================================================================================================
C++11 随机数
========================================================================================================================

实际中要生成随机数最好是用 C++11 的 :cpp:`<random>`, 但教学内不涉及.

首先我们获取一个真正的、但有限的随机数作为种子:

.. code-block:: cpp
  :linenos:

  #include <random>

  std::random_device random_device{};
  auto seed = random_device();

用这个种子构造一个随机数生成器, 以梅森缠绕器为例:

.. code-block:: cpp
  :linenos:

  #include <random>

  std::mt19937 generator(seed);

.. hint::

  你也可以合为一句 :cpp:`std::mt19937 generator{std::random_device{}()};` 来构造随机数生成器.

该随机数生成器就会生成一个随机数, 但我们需要的是一个特定的分布, 所以要将它传递给分布器来生成随机数:

.. tabs::

  .. tab:: :cpp:`[1, 100]` 间 :cpp:`int` 均匀分布

    .. code-block:: cpp
      :linenos:

      #include <random>

      std::mt19937 generator{std::random_device{}()};

      std::uniform_int_distribution<int> dist(1, 100);
      int value1 = dist(generator);
      int value2 = dist(generator);

  .. tab:: :cpp:`[1, 100]` 间 :cpp:`double` 均匀分布

    .. code-block:: cpp
      :linenos:

      #include <random>

      std::mt19937 generator{std::random_device{}()};

      std::uniform_real_distribution<double> dist(1, 100);
      double value1 = dist(generator);
      double value2 = dist(generator);

  .. tab:: :cpp:`0.8` 概率的贝努利分布

    .. code-block:: cpp
      :linenos:

      #include <random>

      std::mt19937 generator{std::random_device{}()};

      std::bernoulli_distribution dist(0.8);
      bool value1 = dist(generator);
      bool value2 = dist(generator);

:godbolt:`fPvGdsfT5`

.. hint::

  更多随机数生成器和分布 (正态分布、泊松分布、柯西分布等) 见于 `cppreference: 随机数分布`_.
