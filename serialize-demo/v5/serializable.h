#include <fcntl.h>
#include <iostream>
#include <vector>
#include <stdio.h>

enum class_type
{
    CLASS_NONE,
    CLASS_A,
    CLASS_B
};

class SerializableBase
{
public:
    virtual bool serialize(FILE *fp) = 0;
    virtual SerializableBase *deserialize(FILE *fp) = 0;
    virtual bool get_type(class_type &type) = 0;
    virtual void print_info() = 0;

public:
    SerializableBase()
    {
    }

    virtual ~SerializableBase()
    {
    }
};

class A : public SerializableBase
{
public:
    A()
    {
        this->i_ = 0;
    }

    explicit A(int i)
    {
        this->i_ = i;
    }

    virtual ~A()
    {
    }

public:
    virtual bool get_type(class_type &type)
    {
        type = CLASS_A;
        return true;
    }

    virtual void print_info()
    {
        std::cout << "i: " << i_ << std::endl;
    }

    virtual bool serialize(FILE *fp)
    {
        if (fp == NULL)
            return false;
        fwrite(&(this->i_), sizeof(int), 1, fp);
        return true;
    }

    virtual SerializableBase *deserialize(FILE *fp)
    {
        A *p = new A();
        fread(&(p->i_), sizeof(int), 1, fp);
        return p;
    }

private:
    int i_;
};

class B : public SerializableBase
{
public:
    B()
    {
        this->i_ = 0;
        this->j_ = 0;
    }

    explicit B(int k)
    {
        this->i_ = k;
        this->j_ = k + 1;
    }

    virtual ~B()
    {
    }

public:
    virtual bool get_type(class_type &type)
    {
        type = CLASS_B;
        return true;
    }

    void print_info()
    {
        std::cout << "i: " << i_ << "  j: " << j_ << std::endl;
    }

    virtual bool serialize(FILE *fp)
    {
        if (fp == NULL)
            return false;
        fwrite(&(this->i_), sizeof(int), 1, fp);
        fwrite(&(this->j_), sizeof(int), 1, fp);
        return true;
    }

    virtual SerializableBase *deserialize(FILE *fp)
    {
        B *p = new B();
        fread(&(p->i_), sizeof(int), 1, fp);
        fread(&(p->j_), sizeof(int), 1, fp);
        return p;
    }

private:
    int i_;
    int j_;
};