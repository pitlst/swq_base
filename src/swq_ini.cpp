#include "swq_ini.h"

using namespace swq;

ini::ini() : m_section(nullptr), m_value(nullptr)
{
}

ini::ini(const char *name) : m_section(nullptr), m_value(nullptr)
{
    m_section = new std::string(name);
}

ini::ini(const std::string &name) : m_section(nullptr), m_value(nullptr)
{
    m_section = new std::string(name);
}

ini::~ini()
{
    clear();
}

void ini::clear()
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
