#ifndef ZEBRA_UTILS
#define ZEBRA_UTILS

#include "includes.hpp"

namespace zebra
{
    template <typename T> using Set = std::unordered_set<T>;
    template <typename A, typename B> using HashMap = std::unordered_map<A, B>;
    template <typename, typename> class BinaryRelation;
    template <typename A, typename B> using Pair = std::pair<A, B>;

    template <typename A, typename B, typename C>
    struct Triple
    {
        A first ;
        B second ;
        C third ;
        
        Triple() {}
        Triple(const A& a, const B& b, const C& c)
            : first{a}, second{b}, third{c}
        {}
    };
    
    template <typename A, typename B, typename C, typename D>
    struct Quadruple
    {
        A first ;
        B second ;
        C third ;
        D fourth ;
        
        Quadruple() {}
        Quadruple(const A& a, const B& b, const C& c, const D& d)
            : first{a}, second{b}, third{c}, fourth{d}
        {}
    };
    
    template <typename A, typename B>
    Pair<B, A> invert(const Pair<A, B>& pair)
    {
        return Pair<B, A>(pair.first, pair.second);
    }
    
    template <typename A, typename B>
    bool operator==(const Pair<A, B>& lhs, const Pair<A, B>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
    
    template <typename T>
    std::ostream& operator<<(std::ostream& stream, const Set<T>& set)
    {
        stream << "{ ";
        for (auto&& element : set)
            stream << element << " ";
        stream << "}";
        return stream;
    }

    template <typename A, typename B>
    Set<Pair<A, B>> make_pairs(const Set<A>& lhs, const Set<B>& rhs)
    {
        Set<Pair<A, B>> result ;
        for (auto&& first : lhs)
            for (auto&& second : rhs)
                result.insert(Pair<A, B>(first, second));
        return std::move(result);
    }
    
    template <typename A, typename B, typename P>
    Set<Pair<A, B>> make_pairs(const Set<A>& lhs, const Set<B>& rhs, P&& predicate)
    {
        Set<Pair<A, B>> result ;
        for (auto&& first : lhs)
            for (auto&& second : rhs)
                if(predicate(first, second))
                    result.insert(Pair<A, B>(first, second));
        return std::move(result);
    }
    
    template <typename A, typename B, typename C>
    Set<Triple<A, B, C>> make_triples(const Set<A>& a, const Set<B>& b, const Set<C>& c)
    {
        Set<Triple<A, B, C>> result ;
        for (auto&& first : a)
            for (auto&& second : b)
                for (auto&& third : c)
                    result.insert(Triple<A, B, C>(first, second, third));
        return std::move(result);
    }
    
    template <typename A, typename B, typename C, typename D>
    Set<Quadruple<A, B, C, D>> make_quads(const Set<A>& a, const Set<B>& b, const Set<C>& c, const Set<D>& d)
    {
        Set<Quadruple<A, B, C, D>> result ;
        for (auto&& first : a)
            for (auto&& second : b)
                for (auto&& third : c)
                    for (auto&& fourth : d)
                        result.insert(Quadruple<A, B, C, D>(first, second, third, fourth));
        return std::move(result);
    }
    
    template <typename A, typename B, typename F>
    void each(const Set<A>& lhs, const Set<B>& rhs, F&& function)
    {
        for (auto&& x : lhs)
            for (auto&& y : rhs)
                function(x, y);
    }
    
    template <typename A, typename B, typename C, typename F>
    void each(const Set<A>& a, const Set<B>& b, const Set<C>& c, F&& function)
    {
        for (auto&& x : a)
            for (auto&& y : b)
                for (auto&& z: b)
                    function(x, y, z);
    }
    
    template <typename A, typename B, typename C, typename D, typename F>
    void each(const Set<A>& a, const Set<B>& b, const Set<C>& c, const Set<D>& d, F&& function)
    {
        for (auto&& w : a)
            for (auto&& x : b)
                for (auto&& y : c)
                    for (auto&& z : d)
                        function(w, x, y, z);
    }
    
    template <typename A, typename B, typename F>
    bool all(const Set<A>& lhs, const Set<B>& rhs, F&& function)
    {
        for (auto&& x : lhs)
            for (auto&& y : rhs)
                if(!function(x, y))
                    return false;   
        return true ;
    }
    
    template <typename A, typename B, typename C, typename F>
    bool all(const Set<A>& a, const Set<B>& b, const Set<C>& c, F&& function)
    {
        for (auto&& x : a)
            for (auto&& y : b)
                for (auto&& z: b)
                    if(!function(x, y, z))
                        return false ;  
        return true ; 
    }
    
    template <typename A, typename B, typename C, typename D, typename F>
    bool all(const Set<A>& a, const Set<B>& b, const Set<C>& c, const Set<D>& d, F&& function)
    {
        for (auto&& w : a)
            for (auto&& x : b)
                for (auto&& y : c)
                    for (auto&& z : d)
                        if(!function(w, x, y, z))
                            return false;
        return true ;
    }
    
    template <typename A, typename B, typename F>
    bool any(const Set<A>& lhs, const Set<B>& rhs, F&& function)
    {
        for (auto&& x : lhs)
            for (auto&& y : rhs)
                if(function(x, y))
                    return true;   
        return false ;
    }
    
    template <typename A, typename B, typename C, typename F>
    bool any(const Set<A>& a, const Set<B>& b, const Set<C>& c, F&& function)
    {
        for (auto&& x : a)
            for (auto&& y : b)
                for (auto&& z: b)
                    if(function(x, y, z))
                        return true ;  
        return false ; 
    }
    
    template <typename A, typename B, typename C, typename D, typename F>
    bool any(const Set<A>& a, const Set<B>& b, const Set<C>& c, const Set<D>& d, F&& function)
    {
        for (auto&& w : a)
            for (auto&& x : b)
                for (auto&& y : c)
                    for (auto&& z : d)
                        if(function(w, x, y, z))
                            return true;
        return false ;
    }

    template <typename A, typename F>
    bool any2(const Set<A>& a, F&& function)
    {
        return any(a, a, function);
    }
    
    template <typename A, typename F>
    bool all(const Set<A>& a, F&& function)
    {
        for (auto&& x : a)
            if(!function(x))
                return false ;
        return true ;
    }
    
    template <typename A, typename F>
    bool all2(const Set<A>& a, F&& function)
    {
        return all(a, a, function);
    }
    
    template <typename A, typename F>
    bool all3(const Set<A>& a, F&& function)
    {
        return all(a, a, a, function);
    }
    
    template <typename A, typename F>
    bool all4(const Set<A>& a, F&& function)
    {
        return all(a, a, a, a, function);
    }
    
    template <typename A, typename B> using RelType = HashMap<typename Set<A>::const_iterator, Set<typename Set<B>::const_iterator>>;
    
    template <typename A, typename F>
    bool all(const A& rel, F&& function)
    {
        for (auto&& x : rel)
             if(!function(*(x.first)))
                return false ;
        return true ;
    }
    
    template <typename A, typename F>
    bool any(const A& rel, F&& function)
    {
        for (auto&& x : rel)
             if(function(*(x.first)))
                return true ;
        return false ;
    }

    template <typename A, typename F>
    bool any2(const A& rel, F&& function)
    {
        for (auto&& x : rel)
            for (auto&& y : x.second)
                if(function(*(x.first), *y))
                    return true;   
        return false ;
    }
    
    template <typename A, typename F>
    bool all2(const A& rel, F&& function)
    {
        for (auto&& x : rel)
            for (auto&& y : x.second)
                if(!function(*(x.first), *y))
                    return false;   
        return true ;
    }
    
    template <typename A, typename F>
    bool all3(const A& rel, F&& function)
    {
        for (auto&& x : rel)
            for (auto&& y : x.second)
                if (rel.count(y) > 0)
                    for (auto z : rel.at(y))
                        if(!function(*(x.first), *y, *z))
                            return false;   
        return true ;
    }
    
    template <typename A, typename B>
    Set<A> all_keys(A start1, A end1, B start2, B end2)
    {
        Set<A> result ;
        for (; start1 != end1; ++start1)
            result.insert(*start1->first);
        for(; start2 != end2; ++start2)
            result.insert(*start2->first);
        return std::move(result);
    }
    
    template <typename A, typename B>
    Set<A> common_keys(A start1, A end1, B start2, B end2)
    {
        Set<A> result ;
        for (; start1 != end1; ++start1)
            for(; start2 != end2; ++start2)
                if (*start1->first == *start2->first)
                    result.insert(*start1->first);
        return std::move(result);
    }
    
    template <typename A, typename E>
    Set<A>
    intersection(const Set<A>& lhs, const Set<A>& rhs, E&& equality)
    {
        Set<A> result ;
        for (auto&& first : lhs)
            for (auto&& second : rhs)
                if (first == second)    
                    result.insert(first);
        return std::move(result);
    }

    template <typename A, typename B>
    Set<Pair<A, B>>
    operator*(const Set<A>& lhs, const Set<B>& rhs)
    {
        Set<Pair<A, B>> product ;
        for (auto&& x : lhs)
            for (auto&& y : rhs)
                product.insert(Pair<A, B>(x, y));
        return product;
    }
    
    template <typename A, typename E>
    Set<A>
    intersection_itr(const Set<A>& lhs, const Set<A>& rhs, E&& equality)
    {
        Set<A> result ;
        for (auto&& first : lhs)
            for (auto&& second : rhs)
                if (*first == *second)    
                    result.insert(*first);
        return std::move(result);
    }
    
    template <typename A>
    Set<A>
    combination(const Set<A>& lhs, const Set<A>& rhs)
    {
        Set<A> result ;
        result.insert(lhs.cbegin(), lhs.cend());
        result.insert(rhs.cbegin(), rhs.cend());
        return std::move(result);
    }
    
    template <typename A>
    Set<A>
    combination_itr(const Set<A>& lhs, const Set<A>& rhs)
    {
        Set<A> result ;
        for (auto&& ele : lhs)
            result.insert(*ele);
        for (auto&& ele : rhs)
            result.insert(*ele);
        return std::move(result);
    }
    
    namespace 
    {
    
        template <typename T>
        Set<Set<T>>
        subset_helper(const Set<T>& set, std::size_t size, Set<typename Set<T>::const_iterator>& skip)
        {
            Set<Set<T>> result ;
            if (size == 2)
                for (auto it = set.cbegin(); it != set.cend(); ++it)
                    for (auto jt = set.cbegin(); jt != set.cend(); ++jt)
                        if (skip.find(it) == skip.cend() &&
                            skip.find(jt) == skip.cend())
                            result.insert(Set<T>({ *it, *jt }));
            else
            {
                for (auto it = set.cbegin(); it != set.cend(); ++it)
                {
                    skip.insert(it);
                    auto tmp = subset_helper(set, size-1, skip);
                    for (auto jt = tmp.cbegin(); jt != tmp.cend(); ++jt)
                    {
                        Set<T> ins({ *it });
                        ins.insert(jt->cbegin(), jt->cend());
                        result.insert(ins);
                    }
                }
            }
            return std::move(result) ;
        }
    
    }
    
    template <typename T>
    Set<Set<T>>
    subsets(const Set<T>& set, std::size_t size)
    {
        Set<typename Set<T>::const_iterator> skips ;
        return subset_helper(set, size, skips);
    }
    
}

#endif