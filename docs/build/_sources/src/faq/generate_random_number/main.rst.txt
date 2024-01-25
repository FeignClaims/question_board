************************************************************************************************************************
随机数的生成 (random number generation)
************************************************************************************************************************

通常我们生成的随机数并不是真正的随机数, 而是基于一个种子 (seed), 以一定算法生成的伪随机数 (pseudo-random number). 这意味着 **如果使用相同的种子和算法, 将会生成一模一样的数.**

.. _C随机数:

========================================================================================================================
C 随机数
========================================================================================================================

首先需要设置随机数的种子, 这需要调用函数 :cpp:`std::srand(seed)` 将 :cpp:`seed` 作为种子, 习惯上我们用 :cpp:`std::time(0)` 获取当前时间作为种子.

由于使用相同的种子和算法, 将会生成一模一样的随机数, **我们应该只在程序运行开始时设置一次随机数种子**.

.. code-block:: cpp
  :linenos:

  #include <cstdlib>  // for std::srand
  #include <ctime>    // for std::time

  int main() {
    std::srand(std::time(0));  // 只在启动程序时设置一次
  }

此后即可调用 :cpp:`std::rand()` 生成随机数, 其生成的随机数为 :math:`[0, RAND\_MAX]` 区间的整数, 故建议用下面的方式生成 **对应区间的随机数 (整数、浮点数通用)**:

.. code-block:: cpp

  #include <cstdlib>  // for std::rand

  double min = 0;   // 预期随机数的最小值
  double max = 10;  // 预期随机数的最大值

  double value =
      // rand() 生成随机数，转换为 double 与可能最大的随机数相除，得到一个概率，取值为 [0, 1]
      (static_cast<double>(std::rand()) / RAND_MAX)
          // 概率 * 区间范围 = 该概率所对应的落在区间中的位置
          * (max - min + 1)  // +1，因为是要映射到 [min - min, max - min] 这个闭区间，
                             // 如果是 [min - min, max - min) 就不用 +1
      // 加上偏移值
      + min;

:godbolt:`bx7WfKd7r`

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

.. code-block:: cpp
  :linenos:

  #include <random>

  // 将随机数映射到 [1, 100] 之间 int 的均匀分布
  std::uniform_int_distribution<int> dist1(1, 100);
  int value1 = dist1(generator);  // 产生一个随机数
  int value2 = dist1(generator);

  // 将随机数映射到 [1, 100] 之间 double 的均匀分布
  std::uniform_real_distribution<double> dist2(1, 100);
  double value3 = dist2(generator);

  // 将随机数映射为 0.8 概率为真, 0.2 概率为假的贝努利分布
  std::bernoulli_distribution dist3(0.8);
  bool value4 = dist3(generator);

  // 将随机数映射为均值为 5.0, 标准查为 2.0 的 double 正态分布
  std::normal_distribution<double> dist4(5.0, 2.0);
  double value5 = dist4(generator);

:godbolt:`fPvGdsfT5`