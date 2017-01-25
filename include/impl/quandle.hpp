#ifndef ZEBRA_QUANDLE
#define ZEBRA_QUANDLE

#include "rack.hpp"

namespace zebra
{
    template <typename T>
    class Quandle : public Rack<T>
    {
        
    public:
        bool involutory() const ;
        
    protected:
        
        void check() throw(Exception);
    };
    
    template <typename T>
    void Quandle<T>::check() throw(Exception)
    {
        auto cond = all(_set, [this](auto x) {
            return at(x, x) == x ;
        });
        if (!Rack<T>::check() || !cond)
            throw Exception(NOT_CONFORMANT, "Not a quandle...");
    }
    
    template <typename T>
    bool Quandle<T>::involutory() const
    {
        return all2(_set, [this] (auto x, auto y) {
            return at(a, at(a, b)) == b ;
        });
    }
}

#endif