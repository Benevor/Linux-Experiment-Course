#include "a.h"
#include <dlfcn.h>
#include <iostream>

using namespace std;

int main()
{
    void *handle = dlopen("./libfunc.so", RTLD_LAZY);
    if (0 == handle)
    {
        cout << "dlopen error" << endl;
        return 0;
    }

    typedef void (*Fun)();

    Fun f1 = (Fun)dlsym(handle, "g");
    Fun f2 = (Fun)dlsym(handle, "_Z1fv");
    Fun myprint = (Fun)dlsym(handle, "myprint");

    if (0 == f1 || 0 == f2 || 0 == myprint)
    {
        cout << "dlsym error" << endl;
        char *str = dlerror();
        cout << str << endl;
    }

    (*f1)();
    (*f2)();
    (*myprint)();

    dlclose(handle);

    return 0;
}
