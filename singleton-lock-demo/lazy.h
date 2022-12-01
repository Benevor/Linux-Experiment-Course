#pragma once

#include <iostream>
#include <mutex>
#include <pthread.h>
#include <unistd.h>

namespace lazy
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
        std::cout << "action--1----1" << std::endl;
        std::cout << "action--1----2" << std::endl;
        std::cout << "action--1----3" << std::endl;
        sleep(2);
        std::cout << "action--1----4" << std::endl;
        std::cout << "action--1----5" << std::endl;
        return NULL;
    }
    void *action2(void *b)
    {
        CSingleton *bc = static_cast<CSingleton *>(b);
        std::unique_lock<std::mutex> lk(bc->latch_);
        std::cout << "action--2----1" << std::endl;
        std::cout << "action--2----2" << std::endl;
        std::cout << "action--2----3" << std::endl;
        std::cout << "action--2----4" << std::endl;
        std::cout << "action--2----5" << std::endl;
        return NULL;
    }

    int test()
    {
        pthread_t pt;
        CSingleton::GetInstance();
        int tstatus = pthread_create(&pt, NULL, action2, (void *)(CSingleton::GetInstance()));
        if (tstatus != 0)
        {
            std::cout << "Can not create new thread." << std::endl;
        }
        action1(CSingleton::GetInstance());
        sleep(1);

        return 0;
    }
}