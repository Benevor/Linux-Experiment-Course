#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>

using namespace std;

namespace A
{
    class CSingleton
    {
    private:
        CSingleton() {}

    public:
        static CSingleton *GetInstance()
        {
            if (instance_ == NULL)
            {
                instance_ = new CSingleton();
            }
            return instance_;
        }

    private:
        static CSingleton *instance_;

    public:
        std::mutex latch_;
    };

    CSingleton *CSingleton::instance_ = nullptr;

    void *action1(CSingleton *a)
    {
        std::unique_lock<std::mutex> lk(a->latch_);
        cout << "action--1----1" << endl;
        cout << "action--1----2" << endl;
        cout << "action--1----3" << endl;
        sleep(2);
        cout << "action--1----4" << endl;
        cout << "action--1----5" << endl;
        return NULL;
    }
    void *action2(void *b)
    {
        CSingleton *bc = static_cast<CSingleton *>(b);
        std::unique_lock<std::mutex> lk(bc->latch_);
        cout << "action--2----1" << endl;
        cout << "action--2----2" << endl;
        cout << "action--2----3" << endl;
        cout << "action--2----4" << endl;
        cout << "action--2----5" << endl;
        return NULL;
    }

    int test()
    {
        pthread_t pt;
        CSingleton::GetInstance();
        int tstatus = pthread_create(&pt, NULL, A::action2, (void *)(CSingleton::GetInstance()));
        if (tstatus != 0)
        {
            cout << "Can not create new thread." << endl;
        }
        A::action1(CSingleton::GetInstance());
        sleep(1);

        return 0;
    }
}

int main()
{
    A::test();
}