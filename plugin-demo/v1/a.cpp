#include <iostream>
#include "a.h"

using namespace std;

void f()
{
    cout << "this is function f()" << endl;
}

extern "C" void g()
{
    cout << "this is function g()" << endl;
}

extern "C" void myprint()
{
    // cout << "Hello World" << endl;
    cout << "Hello China" << endl;
}
