#ifndef LOGGER_HPP
#define LOGGER_HPP

class Default_logger {
 public:
  void log(char /*ch*/) {}
};

template <typename...>
inline auto log_config{Default_logger{}};

template <typename... Dummy_args>
void log(char ch) {
  log_config<Dummy_args...>.log(ch);
}

#endif