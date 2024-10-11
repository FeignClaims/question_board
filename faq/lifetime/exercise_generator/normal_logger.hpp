#ifndef NORMAL_LOGGER_HPP
#define NORMAL_LOGGER_HPP

#include <iostream>
#include <string_view>

class Normal_logger {
 public:
  void log(std::string_view string) {
    std::cout << string;
  }
};

inline Normal_logger normal_logger{};

#endif