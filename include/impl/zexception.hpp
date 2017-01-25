#ifndef ZEBRA_EXCEPT
#define ZEBRA_EXCEPT

#include <string>

namespace zebra
{
    enum ErrorCodes
    {
        NOT_CLOSED,
        NOT_FULFILL_PROPERTY,
        NOT_IN_CODOMAIN,
        NOT_IN_DOMAIN,
        NOT_CONFORMANT,
        DOES_NOT_EXIST
    };

    class Exception
    {
        int error_code;
        std::string message;

    public:

        Exception(int code, const std::string& str) 
            : error_code{code}, message{str} {}

        std::string what() const { return message; }
        int         code() const { return error_code; }

    };
}

#endif