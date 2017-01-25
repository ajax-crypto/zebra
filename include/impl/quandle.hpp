#ifndef ZEBRA_QUANDLE
#define ZEBRA_QUANDLE

#include "rack.hpp"

namespace zebra
{
    template <typename T>
    class Quandle : public Rack<T>
    {
        
        bool involutory() const ;
        
    protected:
        
        void check() throw(std::exception);
    };
    
    template <typename T>
    void Quandle<T>::check() throw(std::exception)
    {
        auto cond = all(_set, [this](auto x) {
            return at(x, x) == x ;
        });
        if (!Rack<T>::check() || !cond)
            throw std::exception("Not a quandle...");
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