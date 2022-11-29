#include "serializable.h"

class Serializer
{
public:
    bool Serialize(const char *pFilePath, std::vector<SerializableBase *> &v)
    {
        FILE *fp = fopen(pFilePath, "w+");
        if (fp == NULL)
            return false;
        for (int i = 0; i < v.size(); i++)
        {
            class_type type;
            v[i]->get_type(type);
            fwrite(&type, sizeof(int), 1, fp);
            v[i]->serialize(fp);
        }
        fclose(fp);
        return true;
    }

    bool Deserialize(const char *pFilePath, std::vector<SerializableBase *> &v)
    {
        FILE *fp = fopen(pFilePath, "r+");
        if (fp == NULL)
            return false;
        for (;;)
        {
            class_type nType = CLASS_NONE;
            int r = fread(&nType, sizeof(int), 1, fp);

            class_type type;
            for (int i = 0; i < m_vSerialized_.size(); i++)
            {
                m_vSerialized_[i]->get_type(type);
                if (type == nType)
                {
                    SerializableBase *p = m_vSerialized_[i]->deserialize(fp);
                    if (p != NULL)
                        v.push_back(p);
                }
            }
            if (r == 0)
                break;
        }
        fclose(fp);
        return true;
    }

    void Register(SerializableBase *pSerialized)
    {
        m_vSerialized_.push_back(pSerialized);
    }

private:
    std::vector<SerializableBase *> m_vSerialized_;
};