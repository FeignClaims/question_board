#ifndef BASE_HPP
#define BASE_HPP

class Base {
 public:
  Base()                       = default;
  Base(Base const&)            = default;
  Base& operator=(Base const&) = default;
  virtual ~Base()              = default;

  virtual void hello() = 0;
};

#endif