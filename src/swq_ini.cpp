#include "swq_ini.h"

using namespace swq;

ini_section::ini_section() : m_section(nullptr), m_value(nullptr)
{
}

ini_section::ini_section(const char *name) : m_section(nullptr), m_value(nullptr)
{
    m_section = new std::string(name);
}

ini_section::ini_section(const std::string &name) : m_section(nullptr), m_value(nullptr)
{
    m_section = new std::string(name);
}

ini_section::~ini_section()
{
    clear();
}

std::string ini_section::section() const
{

}

void ini_section::section(const std::string &section)
{

}

std::string ini_section::value(const std::string &name) const
{

}

std::string ini_section::name(const std::string &value) const
{

}

void ini_section::append(const std::string &name, const std::string &value)
{

}

int ini_section::size()
{

}

std::string ini_section::str() const
{

}

void ini_section::clear()
{
    if (m_section != nullptr)
    {
        m_section->clear();
        delete m_section;
        m_section = nullptr;
    }

    if (m_value != nullptr)
    {
        m_value->clear();
        delete m_value;
        m_value = nullptr;
    }
}
