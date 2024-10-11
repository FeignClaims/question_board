#ifndef NOISY_HPP
#define NOISY_HPP

#include "info.hpp"
#include "logger.hpp"

class Noisy {
 public:
  explicit Noisy(Info const& info) : info_(info) {
    log(info_.ctor);
  }

  Noisy(Noisy const& other) : info_(other.info_) {
    log(info_.copy_ctor);
  }

  Noisy& operator=(Noisy const& other) {
    if (this != &other) {
      info_ = other.info_;
    }
    log(info_.copy_assign);
    return *this;
  }

  virtual ~Noisy() {
    log(info_.dtor);
  }

 private:
  Info info_;
};

class Derived_noisy : public Noisy {
 public:
  Derived_noisy(Info const& info, Derived_info const& derived_info)
      : Noisy(info), derived_info_(derived_info) {
    log(derived_info_.ctor);
  }

  Derived_noisy(Derived_noisy const& other)
      : Noisy(other), derived_info_(other.derived_info_) {
    log(derived_info_.copy_ctor);
  }

  Derived_noisy& operator=(Derived_noisy const& other) {
    if (this == &other) {
      Noisy::operator=(other);
      derived_info_ = other.derived_info_;
    }
    log(derived_info_.copy_assign);
    return *this;
  }

  ~Derived_noisy() override {
    log(derived_info_.dtor);
  }

 private:
  Derived_info derived_info_;
};

#endif