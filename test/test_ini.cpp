#include <iostream>
#include "swq_ini.h"

int main()
{
    swq::ini_head test_ini;
    test_ini.open("../asset/gen_ini.ini");
    std::cout << "hello ini" << std::endl;
    std::cout << test_ini.str() << std::endl;
}