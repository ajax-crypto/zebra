#ifndef ZEBRA_SEMIGROUP
#define ZEBRA_SEMIGROUP

#include "magma.hpp"

namespace zebra
{
    template <typename T>
    class SemiGroup : public Magma<T>
    {
    public:
        using typename Magma<T>::bin_op_type;
        using typename Magma<T>::titer ;
        using typename Magma<T>::param_type;
        using typename Magma<T>::table_type;
        using typename Magma<T>::iter ;
        using Magma<T>::idempotent;
        using Magma<T>::commutative;
        using Magma<T>::associative;
        
        SemiGroup() {}
        SemiGroup(const table_type&, const Set<T>&);
        SemiGroup(iter, iter, const Set<T>&);
        SemiGroup(bin_op_type&&, const Set<T>&);
        
        bool band() const { return idempotent(); }
        bool semilattice() const { return band() && commutative(); }
        bool regular() const ;
        bool separative() const ;
        
        Set<T> principal_left_ideal(T) const ;
        Set<T> principal_right_ideal(T) const ;
        Set<T> principal_ideal(T) const ;
        
        bool L(T, T) const ;
        bool R(T, T) const ;
        bool J(T, T) const ;
        bool H(T a, T b) const { return L(a, b) && R(a, b); }
        bool D(T, T) const ;

        Set<T> Hclass(T, T) const ;
        
    protected:
        using Magma<T>::_set ;
        using Magma<T>::_table ;
        using Magma<T>::_itr ;
        
        void check() throw(Exception);
    };
    
    template <typename T>
    void
    SemiGroup<T>::check() throw(Exception)
    {
        if(!associative())
            throw Exception(NOT_CONFORMANT, "Operation is not associative...");
    }
    
    template <typename T>
    SemiGroup<T>::SemiGroup(const table_type& table, const Set<T>& set)
        : Magma<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    SemiGroup<T>::SemiGroup(iter start, iter end, const Set<T>& set)
        : Magma<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    SemiGroup<T>::SemiGroup(bin_op_type&& func, const Set<T>& set)
        : Magma<T>{std::move(func), set}
    {
        check();
    }

    template <typename T>
    bool
    SemiGroup<T>::regular() const 
    {
        for (auto&& x : _set)
        {
            bool exists = false ;
            for (auto&& y : _set)
                if (this->at(x, this->at(y, x)) == x && this->at(y, this->at(x, y)) == y)
                {
                    exists = true ;
                    break ;
                }
            if (!exists)
                return false;
        }
        return true;
    }

    template <typename T>
    bool
    SemiGroup<T>::L(T a, T b) const
    {
        if (_set.find(a) == _set.end() || _set.find(b) == _set.end())
            return false;
        Set<T> lhs, rhs ;
        lhs.insert(a);
        rhs.insert(b);
        for (auto&& x : _set)
        {
            lhs.insert(this->at(x, a));
            rhs.insert(this->at(x, b));
        }
        return lhs == rhs ;
    }

    template <typename T>
    bool
    SemiGroup<T>::R(T a, T b) const
    {
        if (_set.find(a) == _set.end() || _set.find(b) == _set.end())
            return false;
        Set<T> lhs, rhs ;
        lhs.insert(a);
        rhs.insert(b);
        for (auto&& x : _set)
        {
            lhs.insert(this->at(a, x));
            rhs.insert(this->at(b, x));
        }
        return lhs == rhs ;
    }

    template <typename T>
    bool
    SemiGroup<T>::J(T a, T b) const
    {
        if (_set.find(a) == _set.end() || _set.find(b) == _set.end())
            return false;
        Set<T> lhs, rhs ;
        lhs.insert(a);
        rhs.insert(b);
        for (auto&& x : _set)
        {
            lhs.insert(this->at(x, a));
            lhs.insert(this->at(a, x));
            lhs.insert(this->at(x, this->at(a, x)));
            rhs.insert(this->at(x, b));
            rhs.insert(this->at(b, x));
            rhs.insert(this->at(x, this->at(b, x)));
        }
        return lhs == rhs ;
    }

}

#endif