#include <cstdio>

class File {
 public:
  File(char const* file_path, char const* open_mode)
      : handle_(std::fopen(file_path, open_mode)) {}
  File(File const&)            = delete;
  File& operator=(File const&) = delete;
  ~File() {
    std::fclose(handle_);
  }

 private:
  FILE* handle_;
};

class Editor {
 public:
  Editor(char const* input_file_1,
         char const* input_file_2,
         char const* output_file)
      : input_file_1_{input_file_1, "r"},
        input_file_2_{input_file_2, "r"},
        output_file{output_file, "w"} {}

 private:
  File input_file_1_;
  File input_file_2_;
  File output_file;
};