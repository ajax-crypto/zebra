#ifndef ZEBRA_POSET
#define ZEBRA_POSET

namespace zebra
{
    
    namespace orders
    {
        template <typename A, typename B>
        bool lexicographical(const Pair<A, B>& lhs, const Pair<A, B>& rhs)
        {
            return lhs.first < rhs.first || lhs.first == rhs.first && (rhs.first < rhs.second || rhs.first == rhs.second);
        }
        
        template <typename A, typename B>
        bool product(const Pair<A, B>& lhs, const Pair<A, B>& rhs)
        {
            return lhs.first < rhs.first && lhs.second < rhs.second ;
        }
        
        template <typename A, typename B>
        bool direct(const Pair<A, B>& lhs, const Pair<A, B>& rhs)
        {
            return (lhs.first < rhs.first && lhs.second < rhs.second) || (lhs == rhs) ;
        }
    }
    
    template <typename T>
    class Poset
    {
         
    public:
        using typename BinaryRelation<T, T>::pset_type;
        using typename BinaryRelation<T, T>::membership_type;
        typedef Pair<T, bool> element_type ;
        typedef typename Set<T>::const_iterator iter ;
        
        Poset() {}
        Poset(iter, iter);
        Poset(const Set<T>&);
        Poset(membership_type&&, iter, iter);
        Poset(membership_type&&, const Set<T>&);
        Poset(const Poset<T>&);
        
        element_type greatest() const ;
        element_type least() const ;
        Set<T>       maximal() const ;
        Set<T>       minimal() const ;
        Set<T>       upperbound(const Set<T>&) const ;
        Set<T>       lowerbound(const Set<T>&) const ;
        bool         well_ordered() const ;
        
        template <typename A> friend std::ostream& operator<<(std::ostream&, const Poset<A>&);
        template <typename A> friend Poset<T> operator!(const Poset<T>&);
        template <typename A> friend Poset<T> operator+(const Poset<T>&, const Poset<T>&);
        
    protected:
        
        Set<T>          _set;
        membership_type _order;
    };
    
    template <typename T>
    Poset<T>::Poset(iter start, iter end)
    {
        _set = Set<T>{start, end};
        _order = [](const T& a, const T& b) 
        {
            return a < b || a == b ;
        };
    }
    
    template <typename T>
    Poset<T>::Poset(const Set<T>& set)
        : _set{set}
    {
        _order = [](const T& a, const T& b) 
        {
            return a < b || a == b ;
        };
    }
    
    template <typename T>
    Poset<T>::Poset(membership_type&& order,
                    iter start, iter end)
        : _order{order}
    { 
        _set = Set<T>{start, end};
    }
    
    template <typename T>
    Poset<T>::Poset(membership_type&& order, const Set<T>& set)
        : _order{order}, _set{set}
    { }
    
    template <typename T>
    typename Poset<T>::element_type
    Poset<T>::greatest() const
    {
        element_type g(T{}, false);
        for (auto&& x : _set)
            for (auto&& y : _set)
                if (!(x = y) && !_order(y, x))
                    g = Pair<T, bool>(x, true);
                else
                {
                    g = Pair<T, bool>(T{}, false);
                    break;
                }
        return g;
    }
    
    template <typename T>
    typename Poset<T>::element_type
    Poset<T>::least() const
    {
        element_type g(T{}, false);
        for (auto&& x : _set)
            for (auto&& y : _set)
                if (!(x == y) && !_order(x, y))
                    g = Pair<T, bool>(x, true);
                else
                {
                    g = Pair<T, bool>(T{}, false);
                    break;
                }
        return g;
    }
    
    template <typename T>
    Set<T>
    Poset<T>::maximal() const
    {
        Set<T> max ;
        for (auto&& x : _set)
        {
            Set<T> tmp ;
            bool flagged = false ;
            for (auto&& y : _set)
                if (!(x == y) && _order(y, x))
                    tmp.insert(x);
                else
                {
                    flagged = true ;
                    break;
                }
            if (!flagged)
                max = tmp ;
        }
        return std::move(max);
    }
    
    template <typename T>
    Set<T>
    Poset<T>::minimal() const
    {
        Set<T> min ;
        for (auto&& x : _set)
        {
            Set<T> tmp ;
            bool flagged = false ;
            for (auto&& y : _set)
                if (!(x == y) && _order(x, y))
                    tmp.insert(x);
                else
                {
                    flagged = true ;
                    break;
                }
            if (!flagged)
                min = tmp ;
        }
        return std::move(min);
    }
    
    template <typename T>
    Set<T>
    Poset<T>::upperbound(const Set<T>& set) const
    {
        Set<T> result ;
        for (auto&& x : _set)
            for (auto&& a : set)
                if (!(x == a) && _order(a, x))
                    result.insert(x);
        return std::move(result) ;
    }
    
    template <typename T>
    Set<T>
    Poset<T>::lowerbound(const Set<T>& set) const
    {
        Set<T> result ;
        for (auto&& x : _set)
            for (auto&& a : set)
                if (!(x == a) && _order(x, a))
                    result.insert(x);
        return std::move(result) ;
    }
    
    template <typename T>
    bool
    Poset<T>::well_ordered() const
    {
        for (auto i = 1u; i < _set.size(); ++i)
            if (!Poset<T>(_order, subsets(_set, i)).least().second)
                return false ;
        return BinaryRelation<T, T>(_order, _set).total();
    }
}

#endif