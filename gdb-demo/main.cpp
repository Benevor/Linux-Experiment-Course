#include "process.h"

int main(int argc, const char *argv[])
{
    int pid;
    pid = fork();

    if (pid != 0) // fork return child pid in parent process
        processParent();
    else // fork return 0 in child process
        processChild();

    return 0;
}