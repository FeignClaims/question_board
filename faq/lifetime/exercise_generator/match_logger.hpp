#ifndef MATCH_LOGGER_HPP
#define MATCH_LOGGER_HPP

#include <filesystem>
#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

namespace detail {
[[nodiscard]] inline auto read_lines(std::filesystem::path const& file)
    -> std::vector<std::string> {
  std::vector<std::string> data;

  std::ifstream ifile{file};
  for (std::string line; std::getline(ifile, line);) {
    data.emplace_back(std::move(line));
  }

  return data;
}

[[nodiscard]] inline auto match(std::string_view pattern,
                                std::string_view string)
    -> std::map<char, char> {
  if (pattern.size() != string.size()) {
    return {};
  }

  std::map<char, char> map;
  for (int i : std::views::iota(0UZ, pattern.size())) {
    char const dummy_char{pattern[i]};

    auto const iter{map.find(dummy_char)};
    if (iter == map.end()) {
      map.emplace_hint(iter, dummy_char, string[i]);
    } else {
      if (iter->second != string[i]) {
        return {};
      }
    }
  }

  return map;
}
}  // namespace detail

class Match_logger {
 public:
  explicit Match_logger(std::filesystem::path const& name_file)
      : names{detail::read_lines(name_file)} {}

  ~Match_logger() {
    for (std::string name : names) {
      auto match_result{detail::match(pattern, name)};
      if (!match_result.empty()) {
        std::println("{} {}", name, name.size());
        std::println("{:: >2}", std::views::keys(match_result));
        std::println("{:: >2}", std::views::values(match_result));
        std::println("");
      }
    }
  }

  void log(char ch) {
    pattern += ch;
  }

 private:
  std::string pattern{};
  std::vector<std::string> names;
};

namespace detail {
inline std::filesystem::path directory_of_this_file{
    std::filesystem::path{__FILE__}.parent_path()};
}  // namespace detail

inline Match_logger std_logger{detail::directory_of_this_file / "std.txt"};

inline Match_logger cet4_logger{detail::directory_of_this_file / "cet4.txt"};

#endif