#include <iostream>

class Base {
 public:
  virtual ~Base() {}

  int a;
};
class Derived : public Base {
 public:
  int b;
};

void function(Base base) {
  std::cout << base.a;
}

int main() {
  Derived derived;
  derived.a = 1;
  derived.b = 2;

  function(derived);
}