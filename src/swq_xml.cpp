#include "swq_xml.h"

#include <sstream>

using namespace swq;

xml::xml() : m_name(nullptr), m_text(nullptr), m_children(nullptr), m_attrs(nullptr)
{
}

xml::xml(const char *name) : m_name(nullptr), m_text(nullptr), m_children(nullptr), m_attrs(nullptr)
{
    m_name = new std::string(name);
}

xml::xml(const std::string &name) : m_name(nullptr), m_text(nullptr), m_children(nullptr), m_attrs(nullptr)
{
    m_name = new std::string(name);
}

xml::xml(const std::string &name, const std::string &text) : m_name(nullptr), m_text(nullptr), m_children(nullptr), m_attrs(nullptr)
{
    m_name = new std::string(name);
    m_text = new std::string(text);
}

xml::~xml()
{
    clear();
}

std::string xml::name() const
{
    if (m_name != nullptr)
    {
        return *m_name;
    }
    return std::string();
}

void xml::name(const std::string &name)
{
    if (m_name != nullptr)
    {
        delete m_name;
    }
    m_name = new std::string(name);
}

std::string xml::text() const
{
    if (m_text != nullptr)
    {
        return *m_text;
    }
    return std::string();
}

void xml::text(const std::string &text)
{
    if (m_text != nullptr)
    {
        delete m_text;
    }
    m_text = new std::string(text);
}

std::string xml::attr(const std::string &key)
{
    if (m_attrs == nullptr)
    {
        return std::string();
    }
    return (*m_attrs)[key];
}

void xml::attr(const std::string &key, const std::string &value)
{
    if (m_attrs == nullptr)
    {
        m_attrs = new std::map<std::string, std::string>;
    }
    (*m_attrs)[key] = value;
}

xml &xml::operator[](int index)
{
    if (m_children == nullptr)
    {
        m_children = new std::vector<xml>;
    }
    int size = m_children->size();
    if (index < 0)
    {
        index = size - index;
    }
    if (index >= size)
    {
        for (size_t i = 0; i < index - size; i++)
        {
            m_children->emplace_back(xml());
        }
    }
    return m_children->at(index);
}

xml &xml::operator[](const std::string &name)
{
    if (m_attrs == nullptr)
    {
        m_attrs = new std::map<std::string, std::string>;
    }
    for (auto &ch : (*m_children))
    {
        if (ch.name() == name)
        {
            return ch;
        }
    }
    m_children->emplace_back(xml(name));
    return (*m_children).back();
}

int xml::size()
{
    if (m_children == nullptr)
    {
        return -1;
    }
    return m_children->size();
}

void xml::append(const xml &child)
{
    if (m_children == nullptr)
    {
        m_children = new std::vector<xml>;
    }
    m_children->emplace_back(child);
}

void xml::remove(int index)
{
    if ((m_children != nullptr) && (m_children->size() > index))
    {
        int label = 0;
        for (auto it = m_children->begin(); it != m_children->end(); it++)
        {
            if (label != index)
            {
                label++;
            }
            else
            {
                m_children->erase(it);
                break;
            }
        }
    }
}

void xml::remove(const std::string &name)
{
    if (m_attrs != nullptr)
    {
        auto it = m_attrs->find(name);
        if (it != m_attrs->end())
        {
            m_attrs->erase(it);
        }
    }
}

bool xml::has(int index) const
{
    if ((m_children == nullptr) && (m_children->size() > index))
    {
        return true;
    }
    return false;
}

bool xml::has(const std::string &key) const
{
    if ((m_attrs == nullptr) && (m_attrs->find(key) != m_attrs->end()))
    {
        return true;
    }
    return false;
}

bool xml::has_name() const
{
    if ((m_name == nullptr) && (m_name->size() > 0))
    {
        return true;
    }
    return false;
}

bool xml::has_text() const
{
    if ((m_text == nullptr) && (m_text->size() > 0))
    {
        return true;
    }
    return false;
}

std::string xml::str() const
{
    if (m_name == nullptr)
    {
        return std::string();
    }
    std::stringstream os;
    os << "<" << *m_name;
    if (m_attrs != nullptr)
    {
        for (auto &it : *m_attrs)
        {
            os << " " << it.first << "=\"" << it.second << "\"";
        }
    }
    os << ">";
    if (m_children != nullptr)
    {
        for (auto &it : *m_children)
        {
            os << it.str();
        }
    }
    if (m_text != nullptr)
    {
        os << *m_text;
    }
    os << "</" << m_name << ">";
    return os.str();
}

void xml::clear()
{
    if (m_name != nullptr)
    {
        m_name->clear();
        delete m_name;
        m_name = nullptr;
    }
    if (m_text != nullptr)
    {
        m_text->clear();
        delete m_text;
        m_text = nullptr;
    }
    if (m_attrs != nullptr)
    {
        m_attrs->clear();
        delete m_attrs;
        m_attrs = nullptr;
    }
    if (m_children != nullptr)
    {
        m_children->clear();
        delete m_children;
        m_children = nullptr;
    }
}

xml::iterator xml::begin()
{
    if (m_children == nullptr)
    {
        throw std::logic_error("xml children is empty");
    }
    return m_children->begin();
}

xml::iterator xml::end()
{
    if (m_children == nullptr)
    {
        throw std::logic_error("xml children is empty");
    }
    return m_children->end();
}

void xml::parse(const std::string &str)
{
    parser_x p(str);
    *this = p.parse();
}

parser_x::parser_x() : m_idx(0)
{
}

parser_x::parser_x(const std::string &str) : m_idx(0), m_str(str)
{
}

void parser_x::load(const std::string &str)
{
    m_str = str;
}

xml parser_x::parse()
{
    skip_white_spaces();
    if (m_idx == m_str.size() || m_str[m_idx] == '\0')
    {
        throw std::logic_error("xml document is empty");
    }

    // parse xml declaration
    if (m_str[m_idx + 0] == '<' &&
        m_str[m_idx + 1] == '?' &&
        m_str[m_idx + 2] == 'x' &&
        m_str[m_idx + 3] == 'm' &&
        m_str[m_idx + 4] == 'l')
    {
        if (!parse_declaration())
        {
            throw std::logic_error("xml declaration is error");
        }
    }

    skip_white_spaces();

    // parse xml comment
    if (m_str[m_idx + 0] == '<' &&
        m_str[m_idx + 1] == '!' &&
        m_str[m_idx + 2] == '-' &&
        m_str[m_idx + 3] == '-')
    {
        if (!parse_comment())
        {
            throw std::logic_error("xml comment is error");
        }
    }

    skip_white_spaces();

    xml elem;
    std::string name;

    // parse xml element's
    if ((m_str[m_idx + 0] == '<') && (isalpha(m_str[m_idx + 1]) || m_str[m_idx + 1] == '_'))
    {
        m_idx++;

        // parse elem's name
        name = parse_element_name();
        elem.name(name);

        skip_white_spaces();

        while (m_str[m_idx] != '\0')
        {
            // empty tag
            if (m_str[m_idx + 0] == '/')
            {
                if (m_str[m_idx + 1] == '>')
                {
                    m_idx += 2;
                    return elem;
                }
                else
                {
                    throw std::logic_error("xml empty element is error");
                }
            }
            else if (m_str[m_idx + 0] == '<')
            {
                if (m_str[m_idx + 1] == '/')
                {
                    // find the end tag
                    std::string end_tag = "</" + name + ">";
                    size_t pos = m_str.find(end_tag, m_idx);
                    if (pos == std::string::npos)
                    {
                        throw std::logic_error("xml element " + name + " end tag not found");
                    }
                    if (pos == m_idx)
                    {
                        m_idx += end_tag.size();
                        return elem;
                    }
                }
                else if (m_str[m_idx + 0] == '<' &&
                         m_str[m_idx + 1] == '!' &&
                         m_str[m_idx + 2] == '-' &&
                         m_str[m_idx + 3] == '-')
                {
                    // parse xml comment
                    if (!parse_comment())
                    {
                        throw std::logic_error("xml comment is error");
                    }
                }
                else
                {
                    // parse child element
                    xml child = parse();
                    elem.append(child);
                }
            }
            else if (m_str[m_idx] == '>')
            {
                m_idx++;
                std::string text = parse_element_text();
                skip_white_spaces();
                if (text != "")
                {
                    elem.text(text);
                }
                else
                {
                    // parse child element
                    xml child = parse();
                    elem.append(child);
                }
            }
            else
            {
                // parse elem's attr
                std::string key = parse_element_attr_key();

                skip_white_spaces();

                if (m_str[m_idx] != '=')
                {
                    throw std::logic_error("xml element attr is error" + key);
                }
                m_idx++;
                std::string val = parse_element_attr_val();
                elem.attr(key, val);
            }

            skip_white_spaces();
        }
    }
    return elem;
}

void parser_x::skip_white_spaces()
{
    while (m_str[m_idx] == ' ' || m_str[m_idx] == '\r' || m_str[m_idx] == '\n' || m_str[m_idx] == '\t')
        m_idx++;
}

bool parser_x::parse_declaration()
{
    size_t pos = m_str.find("?>", m_idx);
    if (pos == std::string::npos)
    {
        return false;
    }
    m_idx = pos + 2;
    return true;
}

bool parser_x::parse_comment()
{
    size_t pos = m_str.find("-->", m_idx);
    if (pos == std::string::npos)
    {
        return false;
    }
    m_idx = pos + 3;
    return true;
}

std::string parser_x::parse_element_name()
{
    skip_white_spaces();

    std::string out;
    if (isalpha(m_str[m_idx]) || (m_str[m_idx] == '_'))
    {
        out += m_str[m_idx];
        m_idx++;
        while ((m_str[m_idx] != '\0') &&
               (isalnum(m_str[m_idx]) || (m_str[m_idx] == '_') || (m_str[m_idx] == '-') || (m_str[m_idx] == ':')))
        {
            out += m_str[m_idx];
            m_idx++;
        }
    }
    return out;
}

std::string parser_x::parse_element_text()
{
    skip_white_spaces();

    std::string out;
    while (m_str[m_idx] != '<')
    {
        out += m_str[m_idx];
        m_idx++;
    }
    return out;
}

std::string parser_x::parse_element_attr_key()
{
    skip_white_spaces();

    std::string out;
    if (isalpha(m_str[m_idx]) || (m_str[m_idx] == '_'))
    {
        out += m_str[m_idx];
        m_idx++;
        while (isalnum(m_str[m_idx]) || (m_str[m_idx] == '_') || (m_str[m_idx] == '-') || (m_str[m_idx] == ':'))
        {
            out += m_str[m_idx];
            m_idx++;
        }
    }
    return out;
}

std::string parser_x::parse_element_attr_val()
{
    skip_white_spaces();

    if (m_str[m_idx] != '"')
    {
        throw std::logic_error("xml element attr value should be in double quotes");
    }
    m_idx++;

    std::string out;
    while (m_str[m_idx] != '"')
    {
        out += m_str[m_idx];
        m_idx++;
    }

    m_idx++;
    return out;
}

std::string xml_head::file() const
{
    return m_path;
}

bool xml_head::open(const std::string &load_path)
{
    m_path = load_path;
    std::string temp_str = get_file_str(load_path);
    parse(temp_str);
    return 0;
}

bool xml_head::open(const char *load_path)
{
    return open(std::string(load_path));
}

bool xml_head::save()
{

}

bool xml_head::save(const std::string &load_path)
{

}
