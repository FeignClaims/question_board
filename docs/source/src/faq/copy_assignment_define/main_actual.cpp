#include <exception>  // for std::terminate
#include <iostream>   // for std::cout
#include <utility>    // for std::swap

class Widget {
 public:
  Widget(int size) : size_(size) {
    if (size_ <= 0) {
      std::terminate();
    }
    array_ = new int[size_];
  }

  Widget(Widget const& other)
      : array_(new int[other.size_]), size_(other.size_) {
    for (int i = 0; i < other.size_; ++i) {
      array_[i] = other.array_[i];
    }
  }

  Widget& operator=(Widget const& other) {
    Widget temp(other);  // 拷贝 other 到 temp
    swap(*this, temp);   // 交换 temp 和 *this 的内容
    return *this;
  }  // temp 的析构函数将会对交换来的 *this 内容完成必要的清理

  ~Widget() {
    delete[] array_;
  }

  // 如果是 C++11 及以后, 加上 noexcept 表示不会抛出异常 ↓
  friend void swap(Widget& lhs, Widget& rhs) /*noexcept*/ {
    using std::swap;  // 先 `using std::swap`, 再使用不加限定的 `swap`
    swap(lhs.array_, rhs.array_);
    swap(lhs.size_, rhs.size_);
  }

  int& at(int index) {
    if (index < 0 || index >= size_) {
      std::terminate();
    }

    return array_[index];
  }

  int at(int index) const {
    if (index < 0 || index >= size_) {
      std::terminate();
    }

    return array_[index];
  }

  int size() const {
    return size_;
  }

 private:
  int* array_;
  int size_;
};

void print(Widget const& widget) {
  for (int i = 0; i < widget.size(); ++i) {
    std::cout << widget.at(i) << ' ';
  }
  std::cout << '\n';
}

int main() {
  Widget widget1(3);
  widget1.at(0) = 0;
  widget1.at(1) = 1;
  widget1.at(2) = 2;
  print(widget1);

  Widget widget2(1);
  widget2 = widget1;
  print(widget2);
}