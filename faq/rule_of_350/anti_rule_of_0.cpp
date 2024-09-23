#include <cstdio>

class Editor {
 public:
  Editor(char const* input_file_1,
         char const* input_file_2,
         char const* output_file)
      : input_file_1_(fopen(input_file_1, "r")),
        input_file_2_(fopen(input_file_2, "r")),
        output_file_(fopen(output_file, "w")) {}
  Editor(Editor const&)            = delete;
  Editor& operator=(Editor const&) = delete;
  ~Editor() {
    fclose(input_file_1_);
    fclose(input_file_2_);
    fclose(output_file_);
  }

 private:
  FILE* input_file_1_;
  FILE* input_file_2_;
  FILE* output_file_;
};