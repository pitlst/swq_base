#ifndef SWQ_INI
#define SWQ_INI

#include <string>
#include <map>

#include "swq_utils.h"
using swq::get_file_str;

namespace swq
{
    class ini_section
    {
    public:
        ini_section();
        ~ini_section();

        // 重载函数
        std::string &operator[](const std::string &name);
        // 返回name对应的value
        std::string &value(const std::string &name);
        // 添加对应的参数
        void append(const std::string &name, const std::string &value);
        // 清除指定的value
        void remove(const std::string &name);
        // 清除全部的数据结构
        void clear();
        // 获得该sectiion下的value个数
        int size();
        // 将该srction序列化输出
        std::string str() const;

        // 迭代器，索引value

        typedef std::map<std::string, std::string>::iterator iterator;
        iterator begin();
        iterator end();

    private:
        std::map<std::string, std::string> *m_value;
    };

    class ini_head
    {
    public:
        ini_head();
        ~ini_head();

        // 根据路径打开文件

        bool open(const std::string &load_path);
        bool open(const char *load_path);

        // 重载函数

        ini_section &operator[](int index);
        ini_section &operator[](const std::string &name);

        // 返回section的名字
        std::string &section();
        // 更改section的名字
        void section(const std::string &section);

        // 添加section

        void append(ini_section &y_section);
        void append(const std::string &name);

        // 返回文件路径
        std::string file() const;
        // 根据路径保存

        bool save();
        bool save(const std::string &load_path);
        bool save(const char *load_path);

        // 清除指定的section

        void remove(int index);
        void remove(const std::string &name);

        // 清除全部数据结构
        void clear();
        // 将配置文件序列化输出
        std::string str() const;

        // 迭代器
        typedef std::map<std::string ,ini_section>::iterator iterator;
        iterator begin();
        iterator end();

    private:
        std::string m_path;
        std::map<std::string ,ini_section> *m_section;
    };

    class parser_i
    {
    public:
        parser_i();
        parser_i(const std::string &str);

        void load(const std::string &str);
        ini_head parse();

    private:
    private:
        std::string m_str;
        size_t m_idx;
    };

}

#endif