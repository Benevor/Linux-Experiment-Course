#include "lazy.h"
#include "hungry.h"

int main()
{
    std::cout << "--------------- test lazy singleton lock ---------------" << std::endl;
    lazy::test();
    std::cout << "--------------- test hungry singleton lock ---------------" << std::endl;
    hungry::test();
}