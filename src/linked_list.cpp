#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    size_++;
    if (front_ == nullptr){
      front_ = new Node(value);
      back_ = front_;
      return;
    }
    Node *node = front_;
    while (node->next != nullptr){
      node = node->next;
    }
    node->next = new Node(value);
    node = node->next;
    back_ = node;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index < 0 || index > size_) {
      return false;
    }
    Node *inserting_node = new Node(value);
    if (front_ == nullptr){
      front_ = inserting_node;
      back_ = inserting_node;
    }
    else {
      if (index == 0) {
        inserting_node->next = front_;
        front_ = inserting_node;
      } else if (index == size_) {
        back_->next = inserting_node;
        back_ = inserting_node;
      } else {
        Node *prev_node = FindNode(index - 1);
        inserting_node->next = prev_node->next;
        prev_node->next = inserting_node;
      }
    }
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index < 0 || index >= size_) {
      return false;
    }
    Node *node = front_;
    for (int i = 0;i != index;i++){
      node = node->next;
    }
    node->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    int res;
    if (index == 0){
      Node *tmp = front_;
      front_ = front_->next;
      res = tmp->value;;
      delete tmp;

    }
    else {
      Node *node = front_;
      for(int i = 0;i < index - 1;i++){
        node = node->next;
      }
      Node *deleted_node = node->next;
      res = deleted_node->value;
      if (index == size_ - 1){
        back_ = node;
      }
      node->next = deleted_node->next;
      delete deleted_node;
    }
    size_--;
    return res;
  }

  void LinkedList::Clear() {
   for(Node *curr = front_;curr!=nullptr;){
     Node *node_to_remove = curr;
     curr = curr->next;
     delete node_to_remove;
   }
   front_= nullptr;
   back_ = nullptr;
   size_ = 0;

  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    Node *node = front_;
    for (int i = 0;i != index;i++){
      node = node->next;
    }
    return node->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node *node = front_;
    for (int i = 0;i != size_;i++){
      if (node->value == value){
        return i;
      }
      node = node->next;
    }

    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    Node *node = front_;
    for (int i = 0;i != size_;i++){
      if (node->value == value){
        return true;
      }
      node = node->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
   if (front_ == nullptr) {
     return std::nullopt;
   }
   return front_->value;
  }

  std::optional<int> LinkedList::back() const {
   if (back_ == nullptr) {
     return std::nullopt;
   }
   return back_->value;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index < 0 || index > size_) {
      return nullptr;
    }
    Node *node = front_;
    for(int i = 0;i != index;i++){
      node = node->next;
    }
    return node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment