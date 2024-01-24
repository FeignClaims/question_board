#include <iostream>

int function() {
  int value = 0;

  return value++, value;
}

int main() {
  std::cout << function();
}