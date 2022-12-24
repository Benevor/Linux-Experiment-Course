#include "serializable.h"

void se(){
    Food f1(3, "shipin1");
    FILE *fp = fopen("data", "w+");
    if (fp == NULL){return;}
    class_type type = f1.get_type();
    fwrite(&type, sizeof(int), 1, fp);
    f1.serialize(fp);
    fclose(fp);
}

void de0(){
    FILE *fp = fopen("data", "r+");
    if (fp == NULL){return;}
    class_type nType = CLASS_NONE;
    int r = fread(&nType, sizeof(int), 1, fp);

    Food t;
    auto *p = (&t)->deserialize(fp);

    Food* f = dynamic_cast<Food *>(p);
    std::cout<< f->get_info() <<std::endl;
    delete f;
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

void de3(){ // 对比 de2()
    FILE *fp = fopen("data", "r+");
    if (fp == NULL){return;}

    Food f;
    f.get_type();

    fclose(fp);
}

void de4(){ // de3()的完善
    FILE *fp = fopen("data", "r+");
    if (fp == NULL){return;}
    class_type nType = CLASS_NONE;
    int r = fread(&nType, sizeof(int), 1, fp);

    Food t;
    auto *p = t.deserialize(fp);

    Food* f = dynamic_cast<Food *>(p);
    std::cout<< f->get_info() <<std::endl;
    delete f;
    fclose(fp);
}

void de5(){ // 对比de4， 可以编译，但是运行时会seg fault
    FILE *fp = fopen("data", "r+");
    if (fp == NULL){return;}
    class_type nType = CLASS_NONE;
    int r = fread(&nType, sizeof(int), 1, fp);

    Food* t;
    auto *p = t->deserialize(fp);

    Food* f = dynamic_cast<Food *>(p);
    std::cout<< f->get_info() <<std::endl;
    delete f;
    fclose(fp);
}

int main()
{
    se();
    de4();

    return 0;
}