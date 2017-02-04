#ifndef ZEBRA_MONOID
#define ZEBRA_MONOID

#include "semigroup.hpp"

namespace zebra
{
    template <typename T>
    class Monoid : public SemiGroup<T>
    {
    public:
        using typename SemiGroup<T>::bin_op_type;
        using typename SemiGroup<T>::titer ;
        using typename SemiGroup<T>::param_type;
        using typename SemiGroup<T>::table_type;
        using typename SemiGroup<T>::iter ;
        using SemiGroup<T>::identity_extract ;
        
        Monoid() {}
        Monoid(const table_type&, const Set<T>&);
        Monoid(iter, iter, const Set<T>&);
        Monoid(bin_op_type&&, const Set<T>&);
        
        bool trace() const ;
        bool zerosumfree() const ;
        bool inverse_monoid() const ;
        T    identity() const { return _identity; }
        
    protected:
        using SemiGroup<T>::_set ;
        T     _identity ;      
          
        void check() throw(Exception);
    };
    
    template <typename T>
    void
    Monoid<T>::check() throw(Exception)
    {
         if (!identity_extract(_identity))
            throw Exception(NOT_CONFORMANT, "No identity element exists...");
    }
    
    template <typename T>
    Monoid<T>::Monoid(const table_type& table, const Set<T>& set)
        : SemiGroup<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    Monoid<T>::Monoid(iter start, iter end, const Set<T>& set)
        : SemiGroup<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    Monoid<T>::Monoid(bin_op_type&& func, const Set<T>& set)
        : SemiGroup<T>{std::move(func), set}
    {
        check();
    }
    
    template <typename T>
    bool
    Monoid<T>::trace() const
    {
        return !any2(_set, [this](auto x, auto y) -> bool {
            return this->at(x, y) == this->at(y, x);
        }); 
    }
}

#endif