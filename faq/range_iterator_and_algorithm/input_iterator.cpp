class Iter {
 public:
  Iter(int const* pointer) : pointer_(pointer) {}
  // Iter(Iter const&);  // 隐式生成的拷贝函数即可满足需要

  friend bool operator==(Iter const& lhs, Iter const& rhs) {
    return lhs.pointer_ == rhs.pointer_;
  }

  friend bool operator!=(Iter const& lhs, Iter const& rhs) {
    return !(lhs == rhs);
  }

  int const& operator*() const {
    return *pointer_;
  }

  Iter& operator++() {
    ++pointer_;
    return *this;
  }

 private:
  int const* pointer_;
};