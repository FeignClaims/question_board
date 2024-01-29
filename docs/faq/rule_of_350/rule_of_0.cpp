class File {
 public:
  File(std::string const& file_path) : file_(open_file(file_path)) {}
  File(File const&)            = delete;
  File& operator=(File const&) = delete;
  ~File() {
    close_file(file_);
  }

 private:
  file* file_;
};

class Editor {
 public:
  Editor(std::string const& input_file_1,
         std::string const& input_file_2,
         std::string const& output_file)
      : input_file_1_{input_file_1},
        input_file_2_(input_file_2),
        output_file(output_file) {}

 private:
  File input_file_1_;
  File input_file_2_;
  File output_file;
};