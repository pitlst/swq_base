#include "swq_utils.h"

std::string swq::get_file_str(const std::string &load_path)
{
    std::ifstream ifs;
    ifs.open(load_path);
    if (!ifs.is_open())
    {
        throw std::logic_error("read filure");
    }
    std::istreambuf_iterator<char> beg(ifs), end;
    std::string strdata(beg, end);
    ifs.close();
    return strdata;
}