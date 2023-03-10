#ifndef SWQ_XML
#define SWQ_XML

#include <vector>
#include <string>
#include <map>

#include "swq_utils.h"
using swq::get_file_str;

namespace swq
{
    class xml
    {
    public:
        // 构造函数

        xml();
        xml(const char *name);
        xml(const std::string &name);
        xml(const std::string &name, const std::string &text);
        ~xml();

        //重载函数

        xml & operator [] (int index);
        xml & operator [] (const std::string & name);

        // 解析函数

        void parse(const std::string &str);

        // 常用函数

        std::string name() const;
        void name(const std::string &name);
        std::string text() const;
        void text(const std::string &text);
        std::string attr(const std::string & key);
        void attr(const std::string & key, const std::string & value);

        void append(const xml & child);
        void remove(int index);
        void remove(const std::string & name);
        void clear();
        bool has(int index) const;
        bool has(const std::string &key) const;
        bool has_name() const;
        bool has_text() const;
        int size();
        std::string str() const;
        

        // 迭代器

        typedef std::vector<xml>::iterator iterator;
        iterator begin();
        iterator end();

    private:
        std::string *m_name;
        std::string *m_text;
        std::vector<xml> *m_children;
        std::map<std::string, std::string> *m_attrs;
    };

    class xml_head : public xml
    {
    public:
        // 返回文件路径

        std::string file() const;

        // 根据路径打开文件

        bool open(const std::string &load_path);
        bool open(const char *load_path);

        //根据路径保存文件

        bool save();
        bool save(const std::string &load_path);


    private:
        std::string m_path;
    };

    class parser_x
    {
    public:
        parser_x();
        parser_x(const std::string &str);

        void load(const std::string &str);
        xml parse();
    private:
        void skip_white_spaces();
        bool parse_declaration();
        bool parse_comment();
        std::string parse_element_name();
        std::string parse_element_text();
        std::string parse_element_attr_key();
        std::string parse_element_attr_val();
    private:
        std::string m_str;
        size_t m_idx;
    };

}

#endif