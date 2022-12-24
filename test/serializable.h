#include <fcntl.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include<sstream>

enum class_type {
  CLASS_NONE,
  CLASS_FOOD,
  CLASS_RECORD
};

class SerializableBase {
 public:
  virtual bool serialize(FILE *fp) = 0;
  virtual SerializableBase *deserialize(FILE *fp) = 0;
  virtual class_type get_type() = 0;
  virtual std::string get_info() = 0;

 public:
  SerializableBase() = default;
  virtual ~SerializableBase() = default;
};

class Food : public SerializableBase {
 public:
  Food() {
    this->price_ = 0;
    this->name_size_ = 0;
    this->name_ = nullptr;
  }

  explicit Food(int32_t price, std::string name) {
    this->price_ = price;
    this->name_size_ = name.size();
    this->name_ = new char[this->name_size_];
    strcpy(this->name_, name.c_str());
  }

  virtual ~Food() {
    delete this->name_;
  }

 public:
  class_type get_type() override {
    return CLASS_FOOD;
  }

  std::string get_info() override {
    std::stringstream ss;
    ss << "name: " << this->name_ << "  |  price: " << price_;
    std::string str = ss.str();
    return str;
  }

  bool serialize(FILE *fp) override {
    if (fp == nullptr) { return false; }
    fwrite(&(this->price_), sizeof(int32_t), 1, fp);
    fwrite(&(this->name_size_), sizeof(unsigned long), 1, fp);
    fwrite(this->name_, this->name_size_, 1, fp);
    return true;
  }

  // 错误
  SerializableBase *deserialize(FILE *fp) override {
    Food *f = new Food();
    fread(&(f->price_), sizeof(int32_t), 1, fp);
    fread(&(f->name_size_), sizeof(unsigned long), 1, fp);
    f->name_ = new char[f->name_size_];
    fread(f->name_, f->name_size_, 1, fp);
    return f;
  }

 private:
  int32_t price_;
  unsigned long name_size_;
  char *name_;
};