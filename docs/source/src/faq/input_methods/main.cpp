#include <fstream>
#include <sstream>
#include <string>

int main() {
  std::ifstream ifile("输入文件路径");
  std::string line;
  while (std::getline(ifile, line)) {  // ifile 输入流非格式化输入一行到 line 中
    std::istringstream iss(line);  // 将 line 中内容作为另一个输入流
    int value = 0;
    iss >> value;  // iss 输入流进行格式化输入
  }
}