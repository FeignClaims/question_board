#include <iostream>

template <typename T>
class Widget {
 public:
  Widget(T value) : value_(value) {}

  friend void function(Widget widget);

 private:
  T value_;
};

template <typename T>
void function(Widget<T> widget) {
  std::cout << widget.value_;
}

int main() {
  Widget<int> widget(10);
  function(widget);
}