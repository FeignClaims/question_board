#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string_view>

class Default_logger {
 public:
  void log(std::string_view /*string*/) {}
};

template <typename...>
inline auto log_config{Default_logger{}};

template <typename... Dummy_args>
void log(std::string_view string) {
  log_config<Dummy_args...>.log(string);
}

#endif