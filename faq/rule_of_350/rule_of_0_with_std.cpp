#include <fstream>

class Editor {
 public:
  Editor(std::string const& input_file_1,
         std::string const& input_file_2,
         std::string const& output_file)
      : input_file_1_{input_file_1},
        input_file_2_{input_file_2},
        output_file{output_file} {}

 private:
  std::ifstream input_file_1_;
  std::ifstream input_file_2_;
  std::ofstream output_file;
};