#include "serializer.h"

int main()
{
    {
        A a1(10);
        Serializer s;
        s.Serialize("data", &a1);
    }

    {
        Serializer s;

        A *v;
        s.Deserialize("data", v);
        
        if (v != NULL)
        {
            v->print_info();
        }
        delete v;
    }

    return 0;
}