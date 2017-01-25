#ifndef ZEBRA_RACK
#define ZEBRA_RACK

#include "groupoid.hpp"

namespace zebra
{
    template <typename T>
    class Rack : public Groupoid<T>
    {
        
        
    protected:
        
        void check() throw(Exception);
    };
    
    template <typename T>
    void Rack<T>::check() throw(Exception)
    {
        bool assoc = all3(_set, [this](auto a, auto b, auto c) {
            return at(a, at(b, c)) == at(at(a, b), at(a, c));
        });
        bool uniq = true ;
        HashMap<T, unsigned> result ;
        all2(_set, [this, &result] (auto x, auto y) { 
            auto res = at(x, y);
            result[res]++ ;
        });
        for (auto&& pair : result)
            if (pair.second > 1u)
            {
                uniq = false;
                break;
            }
        if (!assoc || !uniq)
            throw Exception(NOT_CONFORMANT, "Not a rack...");
    }
}

#endif