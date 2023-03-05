#ifndef SWQ_INI
#define SWQ_INI

#include <vector>
#include <string>
#include <map>

#include "swq_utils.h"
using swq::get_file_str;

namespace swq
{
    class ini
    {
    public:
        ini();
        ini(const char *name);
        ini(const std::string &name);
        ~ini();

        // 根据顺序索引键值对
        const ini &operator[](int index);
        // 根据名称索引键值对
        const ini &operator[](const std::string &name);

        // 返回section的名字
        std::string section() const;
        // 更改section的名字
        void section(const std::string &section);
        // 返回name对应的value
        std::string get_value(const std::string &name) const;
        // 返回value对应的name
        std::string get_name(const std::string &value) const;

        void append(const std::string &name, const std::string &value);
        void clear();
        int size();
        std::string str() const;

        void parse(const std::string &str);

    private:
        std::string *m_section;
        std::map<std::string, std::string> *m_value;
    };
}

#endif