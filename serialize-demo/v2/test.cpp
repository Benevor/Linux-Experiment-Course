#include "serializer.h"

int main()
{
    {
        A a1(2);
        A a2(5);

        std::vector<A *> v;

        v.push_back(&a1);
        v.push_back(&a2);

        Serializer s;
        s.Serialize("data", v);
    }

    {
        Serializer s;
        std::vector<A *> v;
        s.Deserialize("data", v);

        for (int i = 0; i < v.size(); i++)
        {
            if (v[i] != NULL)
            {
                v[i]->print_info();
            }
            delete v[i];
        }
    }

    return 0;
}