#include "process.h"

void *processParentworker(void *arg)
{
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    char prefix[] = "Parent-Process-Thread:";
    char tprefix[] = "thread";

    std::cout << prefix << " " << pid << " " << tprefix << " " << tid << " step2" << std::endl;
    std::cout << prefix << " " << pid << " " << tprefix << " " << tid << " step3" << std::endl;
    return nullptr;
}

void processParent()
{
    pid_t pid = getpid();
    char prefix[] = "Parent-Process:";
    int tstatus;
    pthread_t pt;

    std::cout << prefix << " " << pid << " "
              << "step1" << std::endl;

    tstatus = pthread_create(&pt, NULL, processParentworker, NULL);
    if (tstatus != 0)
    {
        std::cout << "Parent-Process: Can not create new thread." << std::endl;
    }

    processParentworker(NULL);
    sleep(1);
}

void processChild()
{
    pid_t pid = getpid();
    char prefix[] = "Child-Process:";
    std::cout << prefix << " " << pid << " "
              << "step1" << std::endl;
    std::cout << prefix << " " << pid << " "
              << "step2" << std::endl;
    std::cout << prefix << " " << pid << " "
              << "step3" << std::endl;
}