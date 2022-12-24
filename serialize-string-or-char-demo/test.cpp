#include "serializable.h"

void se() {
  Food f1(3, "food1");
  Product p1(5, "product1");
  Record r1("user1", "food1", 2, 6);
  FILE *fp = fopen("data", "w+");
  if (fp == NULL) { return; }

  class_type type = f1.get_type();
  fwrite(&type, sizeof(int), 1, fp);
  f1.serialize(fp);

  type = p1.get_type();
  fwrite(&type, sizeof(int), 1, fp);
  p1.serialize(fp);

  type = r1.get_type();
  fwrite(&type, sizeof(int), 1, fp);
  r1.serialize(fp);

  fclose(fp);
}

void de0() {
  FILE *fp = fopen("data", "r+");
  if (fp == NULL) { return; }
  class_type nType = CLASS_NONE;

  int r = fread(&nType, sizeof(int), 1, fp);
  Food t;
  auto tmp = (&t)->deserialize(fp);
  Food *f = dynamic_cast<Food *>(tmp);
  std::cout << f->get_info() << std::endl;
  delete f;

  r = fread(&nType, sizeof(int), 1, fp);
  Product e;
  auto temp = (&e)->deserialize(fp);
  Product *p = dynamic_cast<Product *>(temp);
  std::cout << p->get_info() << std::endl;
  delete p;

  fclose(fp);
}

// void de1(){ // 编译不过？？？？
//     FILE *fp = fopen("data", "r+");
//     if (fp == NULL){return;}
//     class_type nType = CLASS_NONE;
//     int r = fread(&nType, sizeof(int), 1, fp);

//     Food t();
//     auto *p = (&t)->deserialize(fp);

//     Food* f = dynamic_cast<Food *>(p);
//     std::cout<< f->get_info() <<std::endl;
//     delete f;
//     fclose(fp);
// }

// void de2(){ // 编译不过？？？？
//     FILE *fp = fopen("data", "r+");
//     if (fp == NULL){return;}

//     Food f();
//     f.get_type();
//     f.deserialize(fp)

//     fclose(fp);
// }

void de3() { // 对比 de2()
  FILE *fp = fopen("data", "r+");
  if (fp == NULL) { return; }

  Food f;
  f.get_type();

  fclose(fp);
}

void de4() { // de3()的完善
  FILE *fp = fopen("data", "r+");
  if (fp == NULL) { return; }
  class_type nType = CLASS_NONE;
  int r = fread(&nType, sizeof(int), 1, fp);

  Food t;
  auto tmp = t.deserialize(fp);
  Food *f = dynamic_cast<Food *>(tmp);
  std::cout << f->get_info() << std::endl;
  delete f;

  r = fread(&nType, sizeof(int), 1, fp);
  Product e;
  auto temp = e.deserialize(fp);
  Product *p = dynamic_cast<Product *>(temp);
  std::cout << p->get_info() << std::endl;
  delete p;

  r = fread(&nType, sizeof(int), 1, fp);
  Record m;
  auto teemp = m.deserialize(fp);
  Record *r1 = dynamic_cast<Record *>(teemp);
  std::cout << r1->get_info() << std::endl;
  delete r1;

  fclose(fp);
}

void de5() { // 对比de4， 可以编译，但是运行时会seg fault
  FILE *fp = fopen("data", "r+");
  if (fp == NULL) { return; }
  class_type nType = CLASS_NONE;
  int r = fread(&nType, sizeof(int), 1, fp);

  Food *t;
  auto *p = t->deserialize(fp);

  Food *f = dynamic_cast<Food *>(p);
  std::cout << f->get_info() << std::endl;
  delete f;
  fclose(fp);
}

int main() {
  se();
  de4();

  return 0;
}