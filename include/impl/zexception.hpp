#ifndef ZEBRA_EXCEPT
#define ZEBRA_EXCEPT

#include <string>

namespace zebra
{
    enum ErrorCodes
    {
        NO_ERROR,
        NOT_CLOSED,
        NOT_ASSOCIATIVE,
        NOT_COMMUTATIVE,
        NO_IDENTITY,
        NO_INVERSE,
        NOT_FULFILL_PROPERTY,
        NOT_IN_CODOMAIN,
        NOT_IN_DOMAIN,
        NOT_CONFORMANT,
        DOES_NOT_EXIST,
        NOT_A_MEMBER
    };

    std::string ErrorCodesToString(ErrorCodes code)
    {
        switch(code)
        {
            case NO_ERROR: return "No error occured...";
            case NOT_CLOSED: return "Operation is not closed...";
            case NOT_FULFILL_PROPERTY: return "Some property not fulfilled...";
            case NOT_ASSOCIATIVE: return "Operation is not associative...";
            case NO_IDENTITY: return "There exists no identity for the operation...";
            case NO_INVERSE: return "There exists no inverse for some/all elements...";
            default: return "Unknown error...";
        }
    }

    class Error
    {
        ErrorCodes error_code ;

    public:
        Error(ErrorCodes err) : error_code{err} {}

        operator bool() const { return error_code == NO_ERROR; }
        
        friend std::ostream& operator<<(std::ostream& stream, Error err)
        {
            stream << ErrorCodesToString(err.error_code) ;
            return stream;
        }
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