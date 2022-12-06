#include "serializer.h"

int main()
{
    {
        A a1(2);
        B b1(3);
        B b2(4);
        A a2(5);

        std::vector<SerializableBase *> v;

        v.push_back(&a1);
        v.push_back(&b1);
        v.push_back(&b2);
        v.push_back(&a2);

        Serializer s;
        s.Serialize("data", v);
    }

    {
        Serializer s;
        A a;
        B b;
        s.Register(&a);
        s.Register(&b);

        std::vector<SerializableBase *> v;
        s.Deserialize("data", v);

        for (int i = 0; i < v.size(); i++)
        {
            A *p = dynamic_cast<A *>(v[i]);
            if (p != NULL)
            {
                p->print_info();
            }

            B *q = dynamic_cast<B *>(v[i]);
            if (q != NULL)
            {
                q->print_info();
            }

            delete v[i];
        }
    }

    return 0;
}