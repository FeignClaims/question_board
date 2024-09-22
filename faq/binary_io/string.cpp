#include <iostream>
#include <istream>
#include <ostream>
#include <string>

struct Person {
 public:
  std::string name;
  int age;
};

void serialize(std::ostream& ostream, std::string const& string) {
  // 长度
  int size = string.size();
  ostream.write(reinterpret_cast<char const*>(&size), sizeof(size));

  // 实际内容                     ↓ 单个元素的大小 * 元素数量
  ostream.write(string.c_str(), sizeof(char) * size);
}

void deserialize(std::istream& istream, std::string& string) {
  // 长度
  int size = 0;
  istream.read(reinterpret_cast<char*>(&size), sizeof(size));

  // 根据读取字符串的长度给当前的 string 设置好长度
  string.resize(size);

  // 实际内容
  istream.read(string.data(), sizeof(char) * size);
}

void serialize(std::ostream& ostream, Person const& person) {
  serialize(ostream, person.name);
  ostream.write(reinterpret_cast<char const*>(&person.age), sizeof(person.age));
}

void deserialize(std::istream& istream, Person& person) {
  deserialize(istream, person.name);
  istream.read(reinterpret_cast<char*>(&person.age), sizeof(person.age));
}