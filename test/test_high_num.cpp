#include <iostream>
#include "limits.h"
#include "swq_high_num.h"

using namespace swq;

int main()
{
    std::cout << "hello high num" << std::endl;
    // 初始化测试
    double i = 198.1;
    double j = -1.321;
    high_float tempi(i);
    high_float tempj(j);
    auto temp = tempi + tempj;
    std::cout << tempj.str() << std::endl;
    std::cout << i << "+" << j << "=" << (i+j) << std::endl;
    std::cout << tempi << "+" << tempj << "=" << temp.str() << std::endl;
    // i++;
    // j++;
}