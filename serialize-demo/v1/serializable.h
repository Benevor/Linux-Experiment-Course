#include <fcntl.h>
#include <iostream>
#include <vector>
#include <stdio.h>

enum class_type
{
    CLASS_NONE,
    CLASS_A,
};

class A
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

    virtual A *deserialize(FILE *fp)
    {
        A *p = new A();
        if (0 == (fread(&(p->i_), sizeof(int), 1, fp)))
        {
            return NULL;
        }

        return p;
    }

private:
    int i_;
};