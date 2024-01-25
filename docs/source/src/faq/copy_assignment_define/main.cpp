#include <utility>  // for std::swap

class Widget {
 public:
  Widget(Widget const& other);

  Widget& operator=(Widget const& other) {
    Widget temp(other);  // 拷贝 other 到 temp
    swap(*this, temp);   // 交换 temp 和 *this 的内容
    return *this;
  }  // temp 的析构函数将会对交换来的 *this 内容完成必要的清理

  ~Widget();

  // 如果是 C++11 及以后, 加上 noexcept 表示不会抛出异常 ↓
  friend void swap(Widget& lhs, Widget& rhs) /*noexcept*/ {
    using std::swap;  // 先 using std::swap, 再使用不加限定的 swap
    swap(lhs.array_, rhs.array_);
    swap(lhs.size_, rhs.size_);
  }

 private:
  int* array_;
  int size_;
};