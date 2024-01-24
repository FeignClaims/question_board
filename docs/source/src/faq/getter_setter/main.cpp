class Widget {
 public:
  void set_value(int value) {
    value_ = value;
  }
  int get_value() const {
    return value_;
  }

 private:
  int value_;
};