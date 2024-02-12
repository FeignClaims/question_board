#ifndef CONCRETE_HPP
#define CONCRETE_HPP

#include "base.hpp"

class Concrete : public Base {
 public:
  void hello() override;
};

#endif