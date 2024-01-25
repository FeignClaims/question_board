#include <cstdlib>  // for std::srand, std::rand
#include <ctime>    // for std::time

auto main() -> int {
  std::srand(std::time(0));  // 只在启动程序时设置一次

  double min = 0;   // 预期随机数的最小值
  double max = 10;  // 预期随机数的最大值

  double value =
      // rand() 生成随机数, 转换为 double 与可能最大的随机数相除, 得到一个概率, 取值为 [0, 1]
      (static_cast<double>(std::rand()) / RAND_MAX)
          // 概率 * 区间范围 = 该概率所对应的落在区间中的位置
          * (max - min + 1)  // +1, 因为是要映射到 [min - min, max - min] 这个闭区间,
                             // 如果是 [min - min, max - min) 就不用 +1
      // 加上偏移值
      + min;
}