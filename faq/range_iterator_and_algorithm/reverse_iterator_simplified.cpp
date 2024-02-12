template <typename Iter>
class Reverse_iterator {
 public:
  Reverse_iterator(Iter iter);

  friend bool operator==(Reverse_iterator const& lhs,
                         Reverse_iterator const& rhs);
  friend bool operator!=(Reverse_iterator const& lhs,
                         Reverse_iterator const& rhs);

  auto& operator*() {
    auto temp = iter_;
    --temp;
    return *temp;
  }
  auto const& operator*() const {
    auto temp = iter_;
    --temp;
    return *temp;
  }

  Reverse_iterator& operator++() {
    --iter_;
    return *this;
  }

 private:
  Iter iter_;
};

template <typename Iter>
auto make_reverse_iterator(Iter iter) {
  return Reverse_iterator<Iter>(iter);
}