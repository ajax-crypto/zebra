#ifndef ZEBRA_GROUP
#define ZEBRA_GROUP

#include "monoid.hpp"

namespace zebra
{
    template <typename T>
    class Group : public Monoid<T>
    {
    public:
        using typename Magma<T>::table_type;
        using typename Magma<T>::bin_op_type;
        using typename Magma<T>::iter;
        using Monoid<T>::_set;
        using Monoid<T>::at;
        using Monoid<T>::_identity;
        
        Group() {}
        Group(const table_type&, const Set<T>&);
        Group(iter, iter, const Set<T>&);
        Group(bin_op_type&&, const Set<T>&);
        
        Set<T> right_coset(const Set<T>&, const T&) const ;
        Set<T> right_coset(const Group<T>&, const T&) const ;
        Set<T> left_coset(const Set<T>&, const T&) const ;
        Set<T> left_coset(const Group<T>&, const T&) const ;
        bool   subgroup(const Set<T>&) const ;
        bool   subgroup(const Group<T>&) const ;
        bool   normal_subgroup(const Set<T>&) const ;
        bool   normal_subgroup(const Group<T>&) const ;
        Group<T> quotient_group(const Group<T>&) const ;
        
    protected:
        
        void check();
        
        template <typename A> friend Set<A> operator*(const A&, const Group<A>&);
        template <typename A> friend Set<A> operator*(const Group<A>&, const A&);
        template <typename A> friend Group<A> operator/(const Group<A>&, const Group<A>&);
    };
    
    template <typename T>
    Group<T>::Group(const table_type& table, const Set<T>& set)
        : Monoid<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    Group<T>::Group(iter start, iter end, const Set<T>& set)
        : Monoid<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    Group<T>::Group(bin_op_type&& func, const Set<T>& set)
        : Monoid<T>{func, set}
    {
        check();
    }
    
    template <typename T>
    void
    Group<T>::check() 
    {
        Monoid<T>::check();
        for (auto&& x : _set)
        {
            bool flag = false;
            for (auto&& y : _set)
                flag = flag || (at(x, y) == _identity && at(y, x) == _identity);
            if (!flag)
                throw Exception(NOT_CONFORMANT, "Not all elements have an inverse...");
        }
    }
    
    template <typename T>
    class AbelianGroup : public Group<T>
    {
    public:
        using typename Group<T>::table_type;
        using typename Group<T>::bin_op_type;
        using typename Group<T>::iter;
        using Group<T>::_set;
        using Group<T>::at;
        using Group<T>::_identity;

        AbelianGroup() {}
        AbelianGroup(const table_type&, const Set<T>&);
        AbelianGroup(iter, iter, const Set<T>&);
        AbelianGroup(bin_op_type&&, const Set<T>&);
           
    protected:
        
        void check();
    };
    
    template <typename T>
    AbelianGroup<T>::AbelianGroup(const table_type& table, const Set<T>& set)
        : Group<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    AbelianGroup<T>::AbelianGroup(iter start, iter end, const Set<T>& set)
        : Group<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    AbelianGroup<T>::AbelianGroup(bin_op_type&& func, const Set<T>& set)
        : Group<T>{func, set}
    {
        check();
    }
    
    template <typename T>
    void AbelianGroup<T>::check()
    {
        Group<T>::check();
        if (!Magma<T>::commutative())
            throw Exception(NOT_CONFORMANT, "Not all pairs are commutative");
    }
    
}

#endif