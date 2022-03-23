#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
   capacity_ = capacity;
   data_ = new int [capacity_];

   std::fill(data_, data_ + capacity_, 0);


    // Write your code here ...
  }

  DynamicArray::~DynamicArray() {
   size_ = 0;
   capacity_ = 0;

   delete[] data_;
   data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
   if (size_ == capacity_){
     int *new_data = new int [capacity_ + kCapacityGrowthCoefficient];
     std::fill(new_data, new_data + capacity_ + kCapacityGrowthCoefficient, 0);
     for (int i = 0;i < size_;i++){
       new_data[i] = data_[i];
     }
     data_ = new_data;
     capacity_ += kCapacityGrowthCoefficient;

   }
   data_[size_] = value;
   size_++;
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index < 0 || index > size_){
      return false;
    }
    if (size_ == capacity_) {
      int *new_data = new int[capacity_ + kCapacityGrowthCoefficient];
      std::fill(new_data, new_data + capacity_ + kCapacityGrowthCoefficient, 0);
      for (int i = 0; i < size_; i++) {
        new_data[i] = data_[i];
      }
      data_ = new_data;
      capacity_ += kCapacityGrowthCoefficient;
    }
    data_[size_] = value;
    for(int i = size_;i != index;i--){
      int tmp = data_[i - 1];
      data_[i - 1] = data_[i];
      data_[i] = tmp;
    }
    size_++;
    return true;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (index < 0 || index >= size_){
      return false;
    }
    data_[index] = new_value;
    return true;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (index < 0 || index >= size_){
      return std::nullopt;
    }
    int *new_data = new int [capacity_];
    int removed_elem = data_[index];
    for(int i = 0;i != index;i++){
      new_data[i] = data_[i];
    }
    for(int i = index + 1;i != capacity_;i++){
      new_data[i - 1] = data_[i];
    }
    new_data[capacity_ - 1] = 0;
    data_ = new_data;
    size_--;
    return removed_elem;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index < 0 || index >= size_) {
      return std::nullopt;
    }
    return data_[index];
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for(int i = 0;i != size_;i++){
      if (data_[i] == value){
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for(int i = 0;i != size_;i++){
      if (data_[i] == value){
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity <= capacity_){
      return false;
    }
    int *new_data = new int[new_capacity];
    std::fill(new_data, new_data + new_capacity, 0);
    for(int i = 0;i != size_;i++){
      new_data[i] = data_[i];
    }
    data_ = new_data;
    capacity_ = new_capacity;
    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment