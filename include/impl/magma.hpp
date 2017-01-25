#ifndef ZEBRA_MAGMA
#define ZEBRA_MAGMA

#include "utils.hpp"
#include "binary_operation.hpp"

namespace zebra
{
    
    template <typename T>
    class Magma : public BinaryOperation<T>
    {
    public:
        using BinaryOperation<T>::BinaryOperation ;
        using BinaryOperation<T>::at ;
        using BinaryOperation<T>::_set;
        
        bool medial() const ;
        bool left_semimedial() const ;
        bool right_semimedial() const ;
        bool semimedial() const { return left_semimedial() && right_semimedial(); }
        bool left_distributive() const ;
        bool right_distributive() const ;
        bool auto_distributive() const { return left_distributive() && right_distributive(); }
        bool commutative() const ;
        bool idempotent() const ;
        bool unipotent() const ;
        bool zeropotent() const ;
        bool alternative() const ;
        bool associative() const ;
        bool left_unar() const ;
        bool right_unar() const ;
        bool unital() const ;
        bool left_cancellative() const ;
        bool right_cancellative() const ;
        bool cancellative() const { return left_cancellative() && right_cancellative(); }
        bool null_semigroup() const ;
        bool left_zero_semigroup() const ;
        bool right_zero_semigroup() const ;
        bool trimedial() const ;
        bool entropic() const ;
        
    protected:
        bool identity(T&) const ;
    };
    
    template <typename T>
    bool
    Magma<T>::medial() const
    {
        return all4(_set, [this] (auto u, auto v, auto x, auto y) {
            return at(at(u, v), at(x, y)) == at(at(u, x), at(v, y));
        });
    }
    
    template <typename T>
    bool
    Magma<T>::left_semimedial() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(at(x, x), at(y, z)) == at(at(x, y), at(x, z));
        });
    }
    
    template <typename T>
    bool
    Magma<T>::right_semimedial() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(at(y, z), at(x, x)) == at(at(y, x), at(z, x));
        });
    }
    
    template <typename T>
    bool
    Magma<T>::left_distributive() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(x, at(y, z)) == at(at(x, y), at(x, z));
        });
    }
    
    template <typename T>
    bool
    Magma<T>::right_distributive() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(at(y, z), x) == at(at(y, x), at(z, x));
        });
    }
    
    template <typename T>
    bool
    Magma<T>::commutative() const
    {
        return all2(_set, [this] (auto x, auto y) {
            return at(x, y) == at(y, x);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::idempotent() const
    {
        return all(_set, [this] (auto x) {
            return at(x, x) == x ;
        });
    }
    
    template <typename T>
    bool
    Magma<T>::unipotent() const
    {
        return all2(_set, [this] (auto x, auto y) {
           return at(x, x) == at(y, y); 
        });
    }
    
    template <typename T>
    bool
    Magma<T>::zeropotent() const
    {
        return all2(_set, [this] (auto x, auto y) {
            auto xx = at(x, x);
            return at(xx, y) == xx && xx == at(y, xx);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::alternative() const
    {
        return all2(_set, [this] (auto x, auto y) {
            auto xx = at(x, x);
            auto yy = at(y, y);
            auto xy = at(x, y);
            return at(xx, y) == at(x, xy) && at(x, yy) == at(xy, y);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::associative() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(at(x, y), z) == at(x, at(y, z));
        });
    }
    
    template <typename T>
    bool
    Magma<T>::left_unar() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(x, y) == at(x, z);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::right_unar() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(y, x) == at(z, x);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::null_semigroup() const
    {
        return all4(_set, [this] (auto w, auto x, auto y, auto z) {
            return at(w, x) == at(y, z);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::unital() const
    {
        T result ;
        return identity(result);
    }
    
    template <typename T>
    bool
    Magma<T>::identity(T& element) const
    {
        HashMap<T, bool> flagged;
        for (auto&& i : _set)
        {
            flagged[i] = true ;
            for (auto&& element : _set)
                if (!(at(element, i) == element && at(i, element) == element))
                    flagged[i] = false ;
        }
        for (auto&& i : _set)
            if (flagged[i])
            {
                element = i ;
                return true;
            }
        return false;
    }
    
    template <typename T>
    bool
    Magma<T>::left_cancellative() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(x, y) == at(x, z) && y == z ;
        });
    }
    
    template <typename T>
    bool
    Magma<T>::right_cancellative() const
    {
        return all3(_set, [this] (auto x, auto y, auto z) {
            return at(y, x) == at(z, x) && y == z ;
        });
    }
    
    template <typename T>
    bool
    Magma<T>::left_zero_semigroup() const 
    {
        return all2(_set, [this] (auto x, auto y) {
            return x == at(x, y);
        });
    }
    
    template <typename T>
    bool
    Magma<T>::right_zero_semigroup() const 
    {
        return all2(_set, [this] (auto x, auto y) {
            return x == at(y, x);
        });
    }
    
}

#endif