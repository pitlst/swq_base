#include <iostream>
#include "swq_json.h"

int main()
{
    swq::json_head test_json;
    test_json.open("../asset/gen_json.json");
    std::cout << "hello json" << std::endl;

    std::cout << test_json.str() << std::endl;
}