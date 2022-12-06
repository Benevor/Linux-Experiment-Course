#include "serializable.h"

class Serializer
{
public:
    bool Serialize(const char *pFilePath, A *v)
    {
        FILE *fp = fopen(pFilePath, "w+");
        if (fp == NULL)
            return false;
        v->serialize(fp);
        fclose(fp);
        return true;
    }

    bool Deserialize(const char *pFilePath, A *&v)
    {
        FILE *fp = fopen(pFilePath, "r+");
        if (fp == NULL)
            return false;

        A tmp;
        v = tmp.deserialize(fp);

        fclose(fp);
        return true;
    }
};