class Editor {
 public:
  Editor(std::string const& input_file_1,
         std::string const& input_file_2,
         std::string const& output_file)
      : input_file_1_(open_file(input_file_1)),
        input_file_2_(open_file(input_file_2)),
        output_file_(open_file(output_file)) {}
  Editor(Editor const&)            = delete;
  Editor& operator=(Editor const&) = delete;
  ~Editor() {
    close(input_file_1_);
    close(input_file_2_);
    close(output_file_);
  }

 private:
  file* input_file_1_;
  file* input_file_2_;
  file* output_file_;
};