#include <iostream>
#include <utility>

using value_type = int;
//----------------------------------------------------------------------------------------------------------------------

struct Node {
  value_type value;
  Node* next;
};

// 在 position 之后插入 new_node
// 前置条件:：
//  position != nullptr, 即 position 是确实存在的结点.
//
// 返回值::
//  返回指向新插入结点的指针.
//
// 示例::
//  Node left  = {1, nullptr};
//  Node right = {2, nullptr};
//  insert_after(&left, &right);  // 得到 left -> right
//
Node* insert_after(Node* position, Node* new_node) {
  new_node->next = std::exchange(position->next, new_node);
  return new_node;
}

// 输出 begin 及其连接的后续结点, 直到遇到空指针
void print(Node const* begin) {
  for (Node const* node = begin; node != nullptr; node = node->next) {
    std::cout << node->value << " -> ";
  }
  std::cout << "nullptr\n";
}
//----------------------------------------------------------------------------------------------------------------------

class Forward_list {
 public:
  Forward_list() : dummy_(new Node{0, nullptr}), tail_(dummy_) {}
  Forward_list(Forward_list const& other)
      : Forward_list()  // 委托默认构造函数构造好占位结点
  {
    // 插入占位结点之后所有结点的值, 即链表中所有实际的结点
    for (Node* node = other.dummy_->next; node != nullptr; node = node->next) {
      push_back(node->value);
    }
  }

  Forward_list(Forward_list&& other)
      : dummy_(std::exchange(other.dummy_, nullptr)),
        tail_(std::exchange(other.tail_, nullptr)) {}

  // 用定义好的拷贝构造函数、析构函数来实现拷贝赋值函数
  Forward_list& operator=(Forward_list const& other) {
    Forward_list temp(other);  // 用 other 拷贝一个新对象
    swap(*this, temp);         // 交换 *this 和 temp 的内容
    return *this;
  }  // temp 的析构函数将会清理交换来的内容

  // 用定义好的移动构造函数、析构函数来实现移动赋值函数
  Forward_list& operator=(Forward_list&& other) {
    Forward_list temp(std::move(other));  // 移动构造
    swap(*this, temp);
    return *this;
  }

  ~Forward_list() {
    while (dummy_ != nullptr) {
      delete std::exchange(dummy_, dummy_->next);
    }
  }

  friend void swap(Forward_list& lhs, Forward_list& rhs) {
    using std::swap;
    swap(lhs.dummy_, rhs.dummy_);
  }

  void push_front(value_type value) {
    insert_after(dummy_, new Node{value, nullptr});
  }

  void push_back(value_type value) {
    tail_ = insert_after(tail_, new Node{value, nullptr});
  }

  void print() const {
    ::print(dummy_->next);
  }

 private:
  Node* dummy_;
  Node* tail_;
};

int main() {
  Forward_list list;
  list.push_back(1);
  list.push_back(2);
  list.push_front(0);
  list.push_back(3);
  // 0 -> 1 -> 2 -> 3 -> nullptr
  list.print();

  Forward_list copy;
  copy.print();

  copy = list;
  list.print();
  copy.print();
}