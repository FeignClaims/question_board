#include <iostream>
using namespace std;

template <typename T>
class Cin_iterator {
 public:
  Cin_iterator(bool is_end) : value_() {
    if (!is_end) {
      cin >> value_;
    }
  }

  friend bool operator==(Cin_iterator const&, Cin_iterator const&) {
    return cin.fail();
  }
  friend bool operator!=(Cin_iterator const& lhs, Cin_iterator const& rhs) {
    return !(lhs == rhs);
  }

  T const& operator*() const {
    return value_;
  }

  Cin_iterator& operator++() {
    cin >> value_;
    return *this;
  }

 private:
  T value_;
};