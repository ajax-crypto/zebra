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
        typedef typename Magma<T>::param_type key_t;
        using Monoid<T>::_set;
        using Monoid<T>::_table;
        using Monoid<T>::at;
        using Monoid<T>::_identity;
        
        Group() {}
        Group(const table_type&, const Set<T>&);
        Group(iter, iter, const Set<T>&);
        Group(bin_op_type&&, const Set<T>&);
        
        Set<T>   right_coset(const Set<T>&, const T&) const ;
        Set<T>   right_coset(const Group<T>&, const T&) const ;
        Set<T>   left_coset(const Set<T>&, const T&) const ;
        Set<T>   left_coset(const Group<T>&, const T&) const ;
        bool     subgroup(const Set<T>&) const ;
        bool     subgroup(const Group<T>&) const ;
        bool     normal_subgroup(const Set<T>&) const ;
        bool     normal_subgroup(const Group<T>&) const ;
        Set<Set<T>> quotient(const Group<T>&) const ;
        
    protected:
        
        void check();
        
        template <typename A> friend Set<A> operator*(const A&, const Group<A>&);
        template <typename A> friend Set<A> operator*(const Group<A>&, const A&);
        template <typename A> friend Set<Set<A>> operator/(const Group<A>&, const Group<A>&);
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
    Set<T>
    Group<T>::right_coset(const Set<T>& set, const T& value) const 
    {
        if (_set.find(value) == _set.cend())
            throw Exception(NOT_A_MEMBER, "The value is not a member of the group set...");
        if (!subgroup(set))
            throw Exception(NOT_CONFORMANT, "The set does not form a subgroup...");
        Set<T> result ;
        for (auto&& x : set)
            result.insert(*_table[key_t(_set.find(value), _set.find(x))]);
        return std::move(result);
    }

    template <typename T>
    Set<T>
    Group<T>::right_coset(const Group<T>& group, const T& value) const 
    {
        if (_set.find(value) == _set.cend())
            throw Exception(NOT_A_MEMBER, "The value is not a member of the group set...");
        if (!subgroup(group))
            throw Exception(NOT_CONFORMANT, "The group does not form a subgroup...");
        Set<T> result ;
        for (auto&& x : group._set)
            result.insert(*_table[key_t(_set.find(value), _set.find(x))]);
        return std::move(result);
    }

    template <typename T>
    Set<T>
    Group<T>::left_coset(const Set<T>& set, const T& value) const 
    {
        if (_set.find(value) == _set.cend())
            throw Exception(NOT_A_MEMBER, "The value is not a member of the group set...");
        if (!subgroup(set))
            throw Exception(NOT_CONFORMANT, "The set does not form a subgroup...");
        Set<T> result ;
        for (auto&& x : set)
            result.insert(*_table[key_t(_set.find(x), _set.find(value))]);
        return std::move(result);
    }

    template <typename T>
    Set<T>
    Group<T>::left_coset(const Group<T>& group, const T& value) const 
    {
        if (_set.find(value) == _set.cend())
            throw Exception(NOT_A_MEMBER, "The value is not a member of the group set...");
        if (!subgroup(group))
            throw Exception(NOT_CONFORMANT, "The group does not form a subgroup...");
        Set<T> result ;
        for (auto&& x : group._set)
            result.insert(*_table[key_t(_set.find(x), _set.find(value))]);
        return std::move(result);
    }

    template <typename T>
    bool
    Group<T>::subgroup(const Set<T>& set) const
    {
        for (auto&& x : set)
            if (_set.find(x) == _set.cend())
                return false;
        return true;
    }

    template <typename T>
    bool
    Group<T>::subgroup(const Group<T>& group) const
    {
        if (group._set.size() > _set.size())
            return false;
        for (auto&& pair : group._table)
        {
            if (_table.count(pair.first) == 0 || _table[pair.first] != pair.second)
                return false;
        }
        return true;
    }

    template <typename T>
    bool
    Group<T>::normal_subgroup(const Set<T>& set) const
    {
        if (!subgroup(set))
            throw Exception(NOT_CONFORMANT, "The set does not form a subgroup...");
        for (auto&& x : _set)
        {
            if (left_coset(set, x) != right_coset(set, x))
                return false;
        }
        return true;
    }

    template <typename T>
    bool
    Group<T>::normal_subgroup(const Group<T>& group) const
    {
        if (!subgroup(group))
            throw Exception(NOT_CONFORMANT, "The group does not form a subgroup...");
        for (auto&& x : group._set)
        {
            if (left_coset(group, x) != right_coset(group, x))
                return false;
        }
        return true;
    }

    template <typename T>
    Set<Set<T>>
    Group<T>::quotient(const Group<T>& group) const 
    {
        Set<Set<T>> quotient;
        Set<T> temp;
        if (!normal_subgroup(group))
            throw Exception(NOT_CONFORMANT, "The group as argument is not a normal subgroup...");
        for (auto&& x : _set)
        {
            for (auto&& y : group._set)
                temp.insert(*_table[key_t(_set.find(x), _set.find(y))]);
            quotient.insert(temp);
            temp.clear();
        }   
        return std::move(quotient);
    }

    template <typename A> Set<Set<A>> operator/(const Group<A>& lhs, const Group<A>& rhs)
    {
        return lhs.quotient(rhs);
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