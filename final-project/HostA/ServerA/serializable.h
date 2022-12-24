#include <fcntl.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>

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
    this->name_ = "";
  }

  explicit Food(int32_t price, std::string name) {
    this->price_ = price;
    this->name_ = name;
  }

  virtual ~Food() {
  }

 public:
  class_type get_type() override {
    return CLASS_FOOD;
  }

  std::string get_info() override {
    return "";
  }

  bool serialize(FILE *fp) override {
    if (fp == nullptr) { return false; }
    unsigned long name_size = this->name_.size();
    fwrite(&(this->price_), sizeof(int32_t), 1, fp);
    fwrite(&(name_size), sizeof(unsigned long), 1, fp);
    fwrite(&(this->name_), name_size, 1, fp);
    this->name_.c_str();
    return true;
  }

  SerializableBase *deserialize(FILE *fp) override {
    Food *f = new Food();
    unsigned long name_size = 0;
    fread(&(f->price_), sizeof(int32_t), 1, fp);
    fread(&(name_size), sizeof(unsigned long), 1, fp);
    fread(&(f->name_), name_size, 1, fp);
    return f;
  }

 private:
  int32_t price_;
  std::string name_;
};