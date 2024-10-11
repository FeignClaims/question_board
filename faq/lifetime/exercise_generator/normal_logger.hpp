#ifndef NORMAL_LOGGER_HPP
#define NORMAL_LOGGER_HPP

#include <iostream>

class Normal_logger {
 public:
  void log(char ch) {
    std::cout << ch;
  }
};

inline Normal_logger normal_logger{};

#endif