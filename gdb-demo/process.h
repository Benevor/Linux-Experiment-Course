#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>

void *processParentworker(void *arg);
void processParent();
void processChild();