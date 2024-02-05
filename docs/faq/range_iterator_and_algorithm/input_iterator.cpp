class Iter {
 public:
  Iter(int const* pointer) : pointer_(pointer) {}
  // Iter(Iter const&);  // 隐式生成的拷贝函数即可满足需要

  friend bool operator==(Iter const& lhs,
                         Iter const& rhs) {  // iter == end
    return lhs.pointer_ == rhs.pointer_;
  }
  friend bool operator!=(Iter const& lhs,
                         Iter const& rhs) {  // iter != end
    return !(lhs == rhs);
  }

  int const& operator*() const {  // *iter
    return *pointer_;
  }

  Iter& operator++() {  // ++iter
    ++pointer_;
    return *this;
  }

 private:
  int const* pointer_;
};