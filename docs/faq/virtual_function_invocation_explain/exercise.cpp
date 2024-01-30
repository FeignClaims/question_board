#include <iostream>

class A {
 public:
  virtual void fun1() {
    std::cout << "A::fun1 " << '\n';
    fun2();
  }
  void fun2() {
    std::cout << "A::fun2 " << '\n';
    fun3();
  }
  virtual void fun3() {
    std::cout << "A::fun3 " << '\n';
    fun4();
  }
  void fun4() {
    std::cout << "A::fun4 " << '\n';
  }
};

class Base : public A {
 public:
  void fun3() override {
    std::cout << "B::fun3 " << '\n';
    fun4();
  }
  void fun4() {
    std::cout << "B::fun4 " << '\n';
  }
};

int main() {
  A a;
  Base b;
  a.fun1();
  b.fun1();
  return 0;
}