#ifndef ZEBRA_QUASIGROUP
#define ZEBRA_QUASIGROUP

#include "magma.hpp"

namespace zebra
{
    template <typename T>
    class QuasiGroup : public Magma<T>
    {
    public:
        using typename Magma<T>::bin_op_type;
        using typename Magma<T>::titer ;
        using typename Magma<T>::param_type;
        using typename Magma<T>::entry_type;
        using typename Magma<T>::table_type;
        using typename Magma<T>::iter ;
        using Magma<T>::unital;
        using Magma<T>::at ;
        using Magma<T>::commutative;
        
        QuasiGroup() {}
        QuasiGroup(const table_type&, const Set<T>&);
        QuasiGroup(iter, iter, const Set<T>&);
        QuasiGroup(bin_op_type&&, const Set<T>&);
        
        bool loop() const { return unital(); }
        bool right_bol_loop() const ;
        bool left_bol_loop() const ;
        bool bol_loop() const { return right_bol_loop() || left_bol_loop(); }
        bool moufang_loop() const { return right_bol_loop() && left_bol_loop(); }
        bool semi_symmetric() const ;
        bool total_symmetric() const { return semi_symmetric() && commutative(); }
        bool total_antisymmetric() const ;
        
    protected:
        void check() throw(Exception);  
        
        using Magma<T>::_set ;
    };
    
    // In order to check divisibility, it is enough to check if the
    // Cayley table of the operation is a Latin square or not!
    template <typename T>
    void
    QuasiGroup<T>::check() throw(Exception)
    {
        for (auto&& x : _set)
        {
            HashMap<T, unsigned> counts1, counts2;
            for (auto&& y : _set)
            {
                counts1[at(x, y)]++;
                counts2[at(y, x)]++;
            }
            for (auto it = counts1.cbegin(); it != counts1.cend(); ++it)
                if (it->second > 1u)
                    throw Exception(NOT_CONFORMANT, "Does not satisfy divisibility property...");
            for (auto it = counts2.cbegin(); it != counts2.cend(); ++it)
                if (it->second > 1u)
                    throw Exception(NOT_CONFORMANT, "Does not satisfy divisibility property...");
        }
    }
    
    template <typename T>
    QuasiGroup<T>::QuasiGroup(const table_type& table, const Set<T>& set)
        : Magma<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    QuasiGroup<T>::QuasiGroup(iter start, iter end, const Set<T>& set)
        : Magma<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    QuasiGroup<T>::QuasiGroup(bin_op_type&& func, const Set<T>& set)
        : Magma<T>{func, set}
    {
        check();
    }
    
    template <typename T>
    bool
    QuasiGroup<T>::left_bol_loop() const
    {
        return all3(_set, [this](auto x, auto y, auto z) -> bool {
            return at(x, at(y, at(x, z))) == at(at(x, at(y, x)), z);
        });
    }
    
    template <typename T>
    bool
    QuasiGroup<T>::right_bol_loop() const
    {
        return all3(_set, [this](auto x, auto y, auto z) -> bool {
            return at(at(at(z, x), y), x) == at(z, at(at(x, y), x));
        });
    }
    
    template <typename T>
    bool
    QuasiGroup<T>::semi_symmetric() const
    {
        return all2(_set, [this](auto x, auto y) -> bool {
            return x == at(at(y, x), y) && x == at(y, at(x, y));
        });
    }
    
    template <typename T>
    bool
    QuasiGroup<T>::total_antisymmetric() const 
    {
        return all3(_set, [this](auto c, auto x, auto y) -> bool {
            return (at(c, at(x, y)) == at(at(c, y), x) && x == y) &&
                   (at(x, y) == at(x, y) && x == y);
        });
    }
}

#endif