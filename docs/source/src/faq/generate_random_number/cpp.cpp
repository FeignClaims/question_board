#include <random>

int main() {
  std::mt19937 generator{std::random_device{}()};

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
}