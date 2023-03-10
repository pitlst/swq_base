#ifndef SWQ_INI
#define SWQ_INI

#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "swq_utils.h"
using swq::get_file_str;

namespace swq
{
    class ini_section
    {
    public:
        ini_section();

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

        // 根据路径打开文件

        bool open(const std::string &load_path);
        bool open(const char *load_path);

        // 重载函数

        ini_section &operator[](int index);
        ini_section &operator[](const std::string &name);

        // 添加section

        void append(const std::string &name);
        void append(const std::string &name, ini_section &y_section);

        // 根据路径保存

        bool save();
        bool save(const std::string &load_path);
        bool save(const char *load_path);

        // 清除指定的section

        void remove(int index);
        void remove(const std::string &name);

        // 根据section的名字进行索引
        ini_section &section(const std::string &name);
        // 返回文件路径
        std::string file() const;
        // 清除全部数据结构
        void clear();
        // 将配置文件序列化输出
        std::string str() const;
        // 获取当前有多少个section
        int size() const;

        // 迭代器
        typedef std::map<std::string, ini_section>::iterator iterator;
        iterator begin();
        iterator end();

    private:
        std::string m_path;
        std::map<std::string, ini_section> *m_section;
    };

    class parser_i
    {
    public:
        parser_i();
        parser_i(const std::string &str);

        void load(const std::string &str);
        ini_head parse();

    private:
        std::string &ClearHeadTailSpace(std::string &str);

        std::string m_str;
        size_t m_idx;
    };

    //--------------------------------声明实现分界线--------------------------------

    ini_section::ini_section() : m_value(nullptr)
    {
    }

    std::string &ini_section::operator[](const std::string &name)
    {
        return this->value(name);
    }

    std::string &ini_section::value(const std::string &name)
    {
        if (m_value == nullptr)
        {
            m_value = new std::map<std::string, std::string>();
        }
        auto it = m_value->find(name);
        if (it == m_value->end())
        {
            auto it_pair = m_value->emplace(name, std::string());
            it = it_pair.first;
        }
        return (*it).second;
    }

    void ini_section::append(const std::string &name, const std::string &value)
    {
        if (m_value == nullptr)
        {
            m_value = new std::map<std::string, std::string>();
        }
        auto it = m_value->find(name);
        if (it == m_value->end())
        {
            m_value->emplace(name, value);
        }
        else
        {
            (*m_value).at(name) = value;
        }
    }

    void ini_section::remove(const std::string &name)
    {
        if (m_value == nullptr)
        {
            m_value = new std::map<std::string, std::string>();
            return;
        }
        auto it = m_value->find(name);
        if (it == m_value->end())
        {
            return;
        }
        m_value->erase(name);
    }

    void ini_section::clear()
    {
        if (m_value != nullptr)
        {
            m_value->clear();
            delete m_value;
            m_value = nullptr;
        }
    }

    int ini_section::size()
    {
        if (m_value == nullptr)
        {
            m_value = new std::map<std::string, std::string>();
        }
        return m_value->size();
    }

    std::string ini_section::str() const
    {
        std::stringstream ss;
        if (m_value != nullptr)
        {
            for (auto it = m_value->cbegin(); it != m_value->cend(); it++)
            {
                ss << (*it).first << " = " << (*it).second << "\n";
            }
        }
        return ss.str();
    }

    ini_section::iterator ini_section::begin()
    {
        if (m_value == nullptr)
        {
            m_value = new std::map<std::string, std::string>();
        }
        return m_value->begin();
    }

    ini_section::iterator ini_section::end()
    {
        if (m_value == nullptr)
        {
            m_value = new std::map<std::string, std::string>();
        }
        return m_value->end();
    }

    ini_head::ini_head() : m_section(nullptr)
    {
    }

    bool ini_head::open(const std::string &load_path)
    {
        m_path = load_path;
        std::string file_str = get_file_str(load_path);
        parser_i temp_i(file_str);
        *this = temp_i.parse();
        return 0;
    }

    bool ini_head::open(const char *load_path)
    {
        return this->open(std::string(load_path));
    }

    ini_section &ini_head::operator[](int index)
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
        }
        int size = m_section->size();
        if (index < 0)
        {
            index = size - index;
        }
        if (index >= size)
        {
            throw std::logic_error("ini is small, so no required value");
        }
        auto it = m_section->begin();
        for (size_t i = 0; i < index; i++)
        {
            it++;
        }
        return (*it).second;
    }

    ini_section &ini_head::operator[](const std::string &name)
    {
        if (m_section == nullptr)
        {
            throw std::logic_error("ini is empty, so no required value");
        }
        for (auto it = m_section->begin(); it != m_section->end(); it++)
        {
            if ((*it).first == name)
            {
                return (*it).second;
            }
        }
        auto it_pair = m_section->emplace(name, ini_section());
        // 这里逻辑有点绕，标注一下
        // 首先是pair返回值第一个是ini_head的迭代器，索引获得ini_head的引用，ini_head实际上是map。而map的第二个存储的是我们要的ini_section
        return (*(it_pair.first)).second;
    }

    void ini_head::append(const std::string &name)
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
            m_section->emplace(name, ini_section());
        }
        else
        {
            auto it = m_section->find(name);
            if (it == m_section->end())
            {
                m_section->emplace(name, ini_section());
            }
        }
    }

    void ini_head::append(const std::string &name, ini_section &y_section)
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
            m_section->emplace(name, y_section);
        }
        else
        {
            auto it = m_section->find(name);
            if (it == m_section->end())
            {
                m_section->emplace(name, y_section);
            }
            else
            {
                (*it).second = y_section;
            }
        }
    }

    bool ini_head::save()
    {
        std::fstream fs;
        fs.open(m_path, std::ios::out | std::ios::trunc);
        fs << this->str();
        fs.close();
        return 0;
    }

    bool ini_head::save(const std::string &load_path)
    {
        std::fstream fs;
        fs.open(load_path, std::ios::out | std::ios::trunc);
        fs << this->str();
        fs.close();
        return 0;
    }

    bool ini_head::save(const char *load_path)
    {
        std::fstream fs;
        fs.open(load_path, std::ios::out | std::ios::trunc);
        fs << this->str();
        fs.close();
        return 0;
    }

    void ini_head::remove(int index)
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
        }
        else
        {
            int size = m_section->size();
            if (index < 0)
            {
                index = size - index;
            }
            if (index < size)
            {
                auto it = m_section->begin();
                for (size_t i = 0; i < index; i++)
                {
                    it++;
                }
                m_section->erase(it);
            }
        }
    }

    void ini_head::remove(const std::string &name)
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
        }
        else
        {
            auto it = m_section->find(name);
            if (it != m_section->end())
            {
                m_section->erase(it);
            }
        }
    }

    ini_section &ini_head::section(const std::string &name)
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
        }
        auto it = m_section->find(name);
        if (it == m_section->end())
        {
            auto it_pair = m_section->emplace(name, ini_section());
            return (*(it_pair.first)).second;
        }
        else
        {
            return (*it).second;
        }
    }

    std::string ini_head::file() const
    {
        return m_path;
    }

    void ini_head::clear()
    {
        if (m_section != nullptr)
        {
            for (auto &ch : (*m_section))
            {
                ch.second.clear();
            }
            m_section->clear();
            delete m_section;
            m_section = nullptr;
        }
    }

    std::string ini_head::str() const
    {
        if (m_section == nullptr)
        {
            return std::string();
        }
        std::stringstream ss;
        for (auto &ch : (*m_section))
        {
            ss << "[" << ch.first << "]\n";
            ss << ch.second.str();
        }
        return ss.str();
    }

    int ini_head::size() const
    {
        if (m_section == nullptr)
        {
            return 0;
        }
        return m_section->size();
    }

    ini_head::iterator ini_head::begin()
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
        }
        return m_section->begin();
    }

    ini_head::iterator ini_head::end()
    {
        if (m_section == nullptr)
        {
            m_section = new std::map<std::string, ini_section>();
        }
        return m_section->end();
    }

    parser_i::parser_i() : m_idx(0), m_str("")
    {
    }

    parser_i::parser_i(const std::string &str) : m_idx(0), m_str(str)
    {
    }

    void parser_i::load(const std::string &str)
    {
        m_str = str;
    }

    ini_head parser_i::parse()
    {
        // 获取的字符串为空就直接输出空
        if (m_idx == m_str.size() || m_str[m_idx] == '\0')
        {
            return ini_head();
        }
        ini_head elem;
        char ch;
        std::string last_name;
        auto limit = m_str.size();
        while (m_idx < limit)
        {
            ch = m_str[m_idx];
            switch (ch)
            {
            // 如果遇到注释就跳过直到下一行
            case ';':
            {
                do
                {
                    m_idx++;
                    ch = m_str[m_idx];
                } while ((ch != '\n') && (ch != '\r'));
                m_idx++;
            }
            break;
            // 如果遇到空行跳过
            case '\r':
            case '\n':
            {
                m_idx++;
            }
            break;
            // 如果遇到seection
            case '[':
            {
                // 获取section的名字
                m_idx++;
                auto temp_label = m_idx;
                while (ch != ']')
                {
                    m_idx++;
                    ch = m_str[m_idx];
                }
                std::string name = m_str.substr(temp_label, m_idx - temp_label);
                name = ClearHeadTailSpace(name);
                last_name = name;
                elem.append(name);
                m_idx++;
            }
            break;
            // 如果遇到其他字符默认为一条参数
            default:
            {
                // 检查一下当前是否有section
                if (elem.size() > 0)
                {
                    auto temp_label = m_idx;
                    while (ch != '=')
                    {
                        m_idx++;
                        ch = m_str[m_idx];
                    }
                    std::string name = m_str.substr(temp_label, m_idx - temp_label);
                    name = ClearHeadTailSpace(name);
                    m_idx++;
                    temp_label = m_idx;
                    while ((ch != '\r') && (ch != '\n'))
                    {
                        m_idx++;
                        ch = m_str[m_idx];
                    }
                    std::string value = m_str.substr(temp_label, m_idx - temp_label);
                    value = ClearHeadTailSpace(value);
                    elem[last_name].append(name, value);
                }
                // 没有section还有非法字符直接停止解析
                else
                {
                    throw std::logic_error("unexpected end of input in string");
                }
            }
            break;
            }
        }
        return elem;
    }

    // 去掉收尾空格
    std::string &parser_i::ClearHeadTailSpace(std::string &str)
    {
        if (str.empty())
        {
            return str;
        }

        str.erase(0, str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
        return str;
    }

}

#endif