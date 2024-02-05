class Forward_list_iterator {
 public:
  Forward_list_iterator(Node const* node);

  friend bool operator==(Forward_list_iterator const& lhs,
                         Forward_list_iterator const& rhs);
  friend bool operator!=(Forward_list_iterator const& lhs,
                         Forward_list_iterator const& rhs);

  int const& operator*() const {
    return node_->value;
  }

  Forward_list_iterator& operator++() {
    node_ = node_->next;
    return *this;
  }

 private:
  Node const* node_;
};