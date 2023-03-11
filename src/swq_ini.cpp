#include "swq_ini.h"

#include <sstream>

using namespace swq;

ini_section::ini_section() : m_value(nullptr)
{
}

ini_section::~ini_section()
{
    this->clear();
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
    (*m_value).at(name) = value;
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

ini_head::~ini_head()
{
    this->clear();
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
        m_section = new std::map<std::string ,ini_section>();
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
        it++;
    return (*it).second;

}

ini_section &ini_head::operator[](const std::string &name)
{
    if (m_section == nullptr)
    {
        throw std::logic_error("ini is empty, so no required value");
    }
    for (auto it = m_section->begin();it != m_section->end(); it++)
    {
        if ((*it).first == name)
        {
            return (*it).second;
        }
    }
    auto it_pair = m_section->emplace(name, ini_section());
    
}

ini_head::iterator ini_head::begin()
{
    if (m_section == nullptr)
    {
        m_section = new std::map<std::string ,ini_section>();
    }
    return m_section->begin();
}

ini_head::iterator ini_head::end()
{
    if (m_section == nullptr)
    {
        m_section = new std::map<std::string ,ini_section>();
    }
    return m_section->end();
}