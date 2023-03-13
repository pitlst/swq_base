#include <iostream>
#include "swq_xml.h"

int main()
{
    swq::xml_head test_xml;
    test_xml.open("../asset/gen_xml.xml");
    std::cout << "hello xml" << std::endl;
    std::cout << test_xml.str() << std::endl;
}