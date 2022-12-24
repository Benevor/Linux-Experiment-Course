#include <fcntl.h>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <sstream>

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

// 食品类
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

// 交易记录类
class Record : public SerializableBase {
 public:
  Record() {
    this->user_name_ = nullptr;
    this->user_name_size_ = 0;
    this->food_name_ = nullptr;
    this->food_name_size_ = 0;
    this->num_ = 0;
    this->total_price_ = 0;
  }

  explicit Record(std::string user_name, std::string food_name, int32_t num, int32_t total_price) {
    this->user_name_size_ = user_name.size();
    this->food_name_size_ = food_name.size();
    this->user_name_ = new char[this->user_name_size_];
    strcpy(this->user_name_, user_name.c_str());
    this->food_name_ = new char[this->food_name_size_];
    strcpy(this->food_name_, food_name.c_str());
    this->num_ = num;
    this->total_price_ = total_price;
  }

  virtual ~Record() {
    delete this->user_name_;
    delete this->food_name_;
  }

 public:
  class_type get_type() override {
    return CLASS_RECORD;
  }

  std::string get_info() override {
    std::stringstream ss;
    ss << "user: " << this->user_name_ << "  |  food: " << this->food_name_ << "  |  num: " << this->num_
       << "  |  total_price: " << this->total_price_;
    std::string str = ss.str();
    return str;
  }

  bool serialize(FILE *fp) override {
    if (fp == nullptr) { return false; }
    fwrite(&(this->user_name_size_), sizeof(unsigned long), 1, fp);
    fwrite(this->user_name_, this->user_name_size_, 1, fp);

    fwrite(&(this->food_name_size_), sizeof(unsigned long), 1, fp);
    fwrite(this->food_name_, this->food_name_size_, 1, fp);

    fwrite(&(this->num_), sizeof(int32_t), 1, fp);
    fwrite(&(this->total_price_), sizeof(int32_t), 1, fp);
    return true;
  }

  SerializableBase *deserialize(FILE *fp) override {
    auto r = new Record();
    fread(&(r->user_name_size_), sizeof(unsigned long), 1, fp);
    r->user_name_ = new char[r->user_name_size_];
    fread(r->user_name_, r->user_name_size_, 1, fp);

    fread(&(r->food_name_size_), sizeof(unsigned long), 1, fp);
    r->food_name_ = new char[r->food_name_size_];
    fread(r->food_name_, r->food_name_size_, 1, fp);

    fread(&(r->num_), sizeof(int32_t), 1, fp);
    fread(&(r->total_price_), sizeof(int32_t), 1, fp);

    return r;
  }

 private:
  char *user_name_;
  unsigned long user_name_size_;
  char *food_name_;
  unsigned long food_name_size_;
  int32_t num_;
  int32_t total_price_;
};