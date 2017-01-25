#ifndef ZEBRA_GROUP
#define ZEBRA_GROUP

#include "monoid.hpp"
#include <limits>

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
        bool     simple() const ;
        uint64_t order() const { return _set.size(); }
        uint64_t order(const T&) const ;
        bool     pgroup(int64_t) const ;
        bool     direct_sum(const Group<T>&, const Group<T>&) const ;
        Set<Set<T>> quotient(const Group<T>&) const ;
        
    protected:
        
        void check();
        
        template <typename A> friend Set<Set<A>> operator/(const Group<A>&, const Group<A>&);
        template <typename A> friend Group<A> operator*(const Group<A>&, const Group<A>&);
        template <typename A> friend bool is_homomorphism(const Group<A>&, const Group<A>&, const Mapping<A, A>&);

        template <typename A> friend class GroupHomomorphism; 
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
            result.insert(at(x, value));
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
            result.insert(at(x, value));
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
            result.insert(at(value, x));
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
            result.insert(at(value, x));
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
    bool
    Group<T>::simple() const 
    {
        if (!normal_subgroup(*this))
            return false;
        if (at(_identity, _identity) != _identity)
            return false;
        auto subs = subsets(_set);
        for (auto&& sub : subs)
            if (normal_subgroup(sub))
                return false ;
        return true;
    }

    template <typename T>
    bool
    Group<T>::direct_sum(const Group<T>& lhs, const Group<T>& rhs) const
    {
        if (!normal_subgroup(lhs) || !normal_subgroup(rhs))
            return false;
        auto result = intersection(lhs._set, rhs._set);
        if (result.size() != 1 || *result.cbegin() != _identity)
            return false;
        result = combination(lhs._set, rhs._set);
        HashMap<T, unsigned> count ;
        for (auto&& c : _set)
            count[c] = 0u;
        for (auto&& x : result)
            for (auto&& y : result)
                count[at(x, y)]++ ;
        for (auto&& c : _set)
            if (count[c] == 0u)
                return false;
        return true;
    }

    template <typename T>
    uint64_t
    Group<T>::order(const T& element) const
    {
        uint64_t period = 0u;
        while (period < std::numeric_limits<uint64_t>::max())
        {
            element = at(element, element);
            if (element == _identity)
                return period ;
            ++period;
        }
        return std::numeric_limits<uint64_t>::max();
    }

    template <typename T>
    bool
    Group<T>::pgroup(int64_t prime) const 
    {
        for (auto&& element : _set)
        {
            int64_t product = prime, exp = 0u ;
            while (product < std::numeric_limits<uint64_t>::max())
            {
                for (; exp < product; ++exp)
                    element = at(element, element);
                if (element != _identity)
                    product *= prime ;
            }
            if (product >= std::numeric_limits<uint64_t>::max())
                return false ;
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
                temp.insert(at(x, y));
            quotient.insert(temp);
            temp.clear();
        }   
        return std::move(quotient);
    }

    template <typename A> Set<Set<A>> operator/(const Group<A>& lhs, const Group<A>& rhs)
    {
        return lhs.quotient(rhs);
    }

    template <typename A> Group<A> operator*(const Group<A>& lhs, const Group<A>& rhs)
    {
        Group<Pair<A, A>> group ;
        typedef typename Set<Pair<A, A>>::const_iterator itr;
        group._set = lhs._set * rhs._set ;
        for (auto&& pair1 : group._set)
            for (auto&& pair2 : group._set)
            {
                auto g = lhs.at(pair1.first, pair2.first);
                auto h = rhs.at(pair1.second, pair2.second);
                auto index = Pair<itr, itr>(group._set.find(pair1.first, pair2.first), 
                    group._set.find(pair1.second, pair2.second));
                group._table[index] = group._set.find(Pair<A, A>(g, h));
            }
        return group;
    }

    template <typename A> bool is_homomorphism(const Group<A>& lhs, const Group<A>& rhs, const Mapping<A, A>& map)
    {
        for (auto&& x : lhs._set)
            for (auto&& y : lhs._set)
            {
                if (map.exists(lhs.at(x, y)) && map.exists(x) && map.exists(y))
                    if (map(lhs.at(x, y)) != rhs.at(map(x), map(y)))
                        return false;
            }
        return true;
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
    
    template <typename T>
    class GroupHomomorphism
    {
    public:
        GroupHomomorphism(const Group<T>& lhs, const Group<T>& rhs, const Mapping<T, T>& map)
            : _domain{lhs}, _codomain{rhs}, _mapping{map} { check(); }

        Set<T> kernel() const ;
        Set<T> image()  const ;
        bool   monomorphism() const { return _mapping.injective(); }
        bool   epimorphism() const { return _mapping.surjective(); }
        bool   isomorphism() const { return _mapping.bijection(); }
        bool   endomorphism() const { return _domain == _codomain; }
        bool   automorphism() const { return endomorphism() && isomorphism(); }

    protected:

        void check();

        Group<T> _domain, _codomain ;
        Mapping<T, T> _mapping ;
    };

    template <typename T>
    void
    GroupHomomorphism<T>::check()
    {
        for (auto&& x : _domain._set)
            for (auto&& y : _codomain._set)
            {
                if (_mapping.exists(_domain.at(x, y)) && _mapping.exists(x) && _mapping.exists(y))
                    if (_mapping(_domain.at(x, y)) != _codomain.at(_mapping(x), _mapping(y)))
                        throw Exception(NOT_CONFORMANT, "It is not a homomorphism...");
            }
    }

    template <typename T>
    Set<T>
    GroupHomomorphism<T>::kernel() const
    {
        Set<T> result;
        for (auto&& x : _domain._set)
            if (_mapping.exists(x) && _mapping(x) == _codomain._identity)
                result.insert(x);
        return result;
    }

    template <typename T>
    Set<T>
    GroupHomomorphism<T>::image() const
    {
        Set<T> result;
        for (auto&& x : _domain._set)
            if (_mapping.exists(x))
                result.insert(x);
        return result;
    }

}

#endif