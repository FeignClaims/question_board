#include "base.hpp"
#include "concrete.hpp"

int main() {
  Concrete concrete;
  Base& base = concrete;
  base.hello();
}