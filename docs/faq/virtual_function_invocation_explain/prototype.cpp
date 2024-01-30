class Base {
 public:
  Base() {}
  virtual ~Base() {}
  virtual Base* clone() const = 0;
};

class Derived : public Base {
 public:
  Derived* clone() const override {
    return new Derived(*this);  // Dervied 自己知道如何拷贝自己
  }
};