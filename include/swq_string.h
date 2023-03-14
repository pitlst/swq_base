#ifndef SWQ_STRING
#define SWQ_STRING

#include <string>
#include <list>

namespace swq
{
    class string
    {
    public:
        string();
        string(const std::string & input);
        string(const char * input);

    private:
        std::list<char> * m_char;
    };






}

#endif