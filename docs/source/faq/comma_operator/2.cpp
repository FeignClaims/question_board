#include <iostream>

int value = 1;

void f() {
  value += 1;
  std::cout << value;
}

void g() {
  value *= 10;
  std::cout << value;
}

int main() {
  f(), g();
}