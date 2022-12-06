#include "serializable.h"

class Serializer
{
public:
    bool Serialize(const char *pFilePath, std::vector<A *> &v)
    {
        FILE *fp = fopen(pFilePath, "w+");
        if (fp == NULL)
            return false;
        for (int i = 0; i < v.size(); i++)
        {
            v[i]->serialize(fp);
        }
        fclose(fp);
        return true;
    }

    bool Deserialize(const char *pFilePath, std::vector<A *> &v)
    {
        FILE *fp = fopen(pFilePath, "r+");
        if (fp == NULL)
            return false;
        for (;;)
        {
            A tmp;
            A *p = tmp.deserialize(fp);
            if (p != NULL)
            {
                v.push_back(p);
            }
            else
            {
                break;
            }
        }
        fclose(fp);
        return true;
    }
};