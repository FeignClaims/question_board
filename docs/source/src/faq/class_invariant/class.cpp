#include <exception>  // std::terminate()
#include <numeric>    // C++17 提供了求最大公因数函数 gcd

struct Lowest_terms_fraction {
 public:
  Lowest_terms_fraction(int numerator, int denominator) {
    if (denominator == 0) {  // 分母为 0
      std::terminate();  // 进行错误处理，此处选择直接终止程序
    }

    numerator_   = numerator;
    denominator_ = denominator;
    revert_to_lowest_terms();
  }

  void add_by(Lowest_terms_fraction const& other) {
    /* 进入成员函数时, 不变式成立 */

    /* 经过函数内的运算, 不变式可能被打破了 */
    numerator_
        = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    denominator_ *= other.denominator_;

    /* 退出成员函数前, 恢复不变式 */
    revert_to_lowest_terms();
  }

 private:
  void revert_to_lowest_terms() {  // 化简分式从而恢复不变式
    int const gcd  = std::gcd(numerator_, denominator_);
    numerator_    /= gcd;
    denominator_  /= gcd;
  }

  int numerator_;    // 分子
  int denominator_;  // 分母
};

int main() {
  Lowest_terms_fraction lhs(2, 6);  // 1/3, 是最简分式!
  Lowest_terms_fraction rhs(3, 6);  // 1/2, 是最简分式!
  lhs.add_by(rhs);                  // 5/6, 是最简分式!
}