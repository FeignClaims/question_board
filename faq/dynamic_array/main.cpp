#include <algorithm>  // for std::min
#include <iostream>   // for std::cout
#include <ostream>    // for std::ostream
#include <utility>    // for std::swap, std::exchange

using value_type = int;

// 将 [input, input + size) 从左到右拷贝到 [output, output + size) 中
// 前置条件::
//   - 对 [input,  input + size)  区间进行读取是有效的.
//   - 对 [output, output + size) 区间进行赋值是有效的.
//   - output 不处于 [input, input + size] 范围内.
//     (否则: 由于从左到右拷贝, 到需要对 output 进行读取时, 它已经被赋值成了 input 处的值.)
//
// 返回值::
//   返回 output + size, 即如果继续对 output 进行拷贝, 应该使用的指针.
//
// 示例::
//   char const* string1{"hello"};
//   char const* string2{"world"};
//   char data[100]{};
//
//   char* output{&data[0]};
//   output  = copy(string1, strlen(string1), output);
//   output  = copy(string2, strlen(string2), output);
//   *output = '\0';
//
//   cout << data;  // 输出 "hello world"
//
// 注意到, 我们直接解决了拷贝问题, 还解决了连接问题——连续 copy 多次就是了
value_type* copy_n(value_type const* input, int size, value_type* output) {
  for (int i{0}; i < size; ++i) {
    *output = *input;
    ++input;
    ++output;
  }
  return output;
}

class Dynamic_array {
 public:
  explicit Dynamic_array(int size = 0)
      : size_{size}, data_{size == 0 ? nullptr : new value_type[size]{}} {}

  Dynamic_array(Dynamic_array const& other) : Dynamic_array{other.size_} {
    copy_n(other.data_, other.size_, data_);
  }

  ~Dynamic_array() {
    // ↓ delete[] 本身自带对空指针的检查, 不需要提前判断 data_ == nullptr
    delete[] data_;
  }

  // 用定义好的拷贝构造函数、析构函数来实现拷贝赋值函数
  Dynamic_array& operator=(Dynamic_array const& other) {
    Dynamic_array temp{other};  // 用 other 拷贝一个新对象
    swap(*this, temp);          // 交换 *this 和 temp 的内容
    return *this;
  }  // temp 的析构函数将会清理交换来的内容

  friend void swap(Dynamic_array& lhs, Dynamic_array& rhs) {
    using std::swap;             // 先 using std::swap;
    swap(lhs.size_, rhs.size_);  // 再使用没有任何限定的 swap
    swap(lhs.data_, rhs.data_);
  }

  // 调整 Dynamic_array 的长度
  // - new_size >= size_: 长度变长了, 原来 Dynamic_array 中所有元素内容 (size_ 个) 全部保持, 新元素设 0
  // - new_size <  size_: 长度变短了, 原来 Dynamic_array 中前 new_size 个元素内容全部保持
  //
  // 所以说白了, 就是原来 Dynamic_array 中前 min(new_size, size_) 个元素内容全部保持
  void resize(int new_size) {
    /* 依然可以用类似 copy-and-swap 的逻辑, 不过这里是 construct-and-swap */
    Dynamic_array temp{new_size};
    copy_n(data_, std::min(size_, new_size), temp.data_);

    swap(*this, temp);
  }

  value_type& operator[](int index) {
    return data_[index];
  }

  // const 函数不该允许对对象的修改, 返回的数组元素应该是 const& 的
  //
  // 示例::
  //  Dynamic_array const array(5);
  //  array[1] = 3;  // 错误: value_type const& 不可修改
  value_type const& operator[](int index) const {
    return data_[index];
  }

  int size() const {
    return size_;
  }

  // 得到一个新的 Dynamic_array 对象, 它的内容是 lhs 和 rhs 连接起来
  //
  // 示例::
  //  Dynamic_array lhs(1);
  //  lhs[0] = 1;
  //  Dynamic_array rhs(2);
  //  rhs[0] = 2;
  //  rhs[1] = 3;
  //
  //  Dynamic other = lhs + rhs;  // 得到 {1, 2, 3}
  friend Dynamic_array operator+(Dynamic_array const& lhs,
                                 Dynamic_array const& rhs) {
    Dynamic_array result(lhs.size() + rhs.size());

    value_type* output{&result.data_[0]};
    output = copy_n(lhs.data_, lhs.size_, output);
    output = copy_n(rhs.data_, rhs.size_, output);

    return result;
  }

  // ↓ 按赋值运算符的惯例, 返回 *this 引用
  Dynamic_array& operator+=(Dynamic_array const& other) {
    *this = *this + other;
    return *this;
  }

  friend bool operator==(Dynamic_array const& lhs, Dynamic_array const& rhs) {
    if (lhs.size() != rhs.size()) {  // 长度是否相等
      return false;
    }

    for (int i{0}; i < lhs.size_; ++i) {
      if (lhs.data_[i] != rhs.data_[i]) {  // 同一下标下的元素是否相等
        return false;
      }
    }
    return true;
  }
  friend bool operator!=(Dynamic_array const& lhs, Dynamic_array const& rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(Dynamic_array const& lhs, Dynamic_array const& rhs) {
    // 比较同长部分:
    //  - 小于: lhs 更小, 返回 true
    //  - 等于: 比较下一个字符
    //  - 大于: rhs 更小, 返回 false
    int const min_size{std::min(lhs.size_, rhs.size_)};
    for (int i{0}; i < min_size; ++i) {
      if (lhs.data_[i] < rhs.data_[i]) {
        return true;
      }
      if (lhs.data_[i] > rhs.data_[i]) {
        return false;
      }
    }

    // 同长部分已经比较完毕
    //  - lhs.size_ <  rhs.size_: 说明 lhs 是 rhs 的前缀, 想想词典是怎么排列 a 和 at 的, 返回 true
    //  - lhs.size_ == rhs.size_: 相同, 返回 false
    //  - lhs.size_ >  rhs.size_: 说明 rhs 是 lhs 的前缀, 想想词典是怎么排列 at 和 a 的, 返回 false
    return lhs.size_ < rhs.size_;
  }
  friend bool operator>(Dynamic_array const& lhs, Dynamic_array const& rhs) {
    return rhs < lhs;
  }
  friend bool operator<=(Dynamic_array const& lhs, Dynamic_array const& rhs) {
    return !(rhs < lhs);
  }
  friend bool operator>=(Dynamic_array const& lhs, Dynamic_array const& rhs) {
    return !(lhs < rhs);
  }

  //     ↓ 按约定返回 ostream 的引用
  friend std::ostream& operator<<(std::ostream& ostream,
                                  Dynamic_array const& array) {
    ostream << '[';
    for (int i{0}; i < array.size(); ++i) {
      ostream << (i == 0 ? "" : ", ") << array[i];
    }
    ostream << ']';
    return ostream;
  }

 private:
  int size_;
  int* data_;
};

int main() {
  Dynamic_array array(5);
  array[2] = 3;

  std::cout << array << '\n';
}