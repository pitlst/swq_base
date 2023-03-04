#ifndef SWQ_UTILS
#define SWQ_UTILS

#include <string>
#include <fstream>

namespace swq
{
    // 读取文件转换成字符串，支持string格式路径和char格式路径
    std::string get_file_str(const std::string &load_path);
}

#endif