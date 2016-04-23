#ifndef ZEBRA_UTILS
#define ZEBRA_UTILS

#include "includes.hpp"

namespace zebra
{
    template <typename T> using Set = std::unordered_set<T>;
    template <typename A, typename B> using HashMap = std::unordered_map<A, B>;
    template <typename, typename> class BinaryRelation;
    
    template <typename A, typename B>
    std::pair<B, A> invert(const std::pair<A, B>& pair)
    {
        return std::pair<B, A>(pair.first, pair.second);
    }
    
    template <typename A, typename B>
    bool operator==(const std::pair<A, B>& lhs, const std::pair<A, B>& rhs)
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
    Set<std::pair<A, B>> make_pairs(const Set<A>& lhs, const Set<B>& rhs)
    {
        Set<std::pair<A, B>> result ;
        for (auto&& first : lhs)
            for (auto&& second : rhs)
                result.insert(std::pair<A, B>(first, second));
        return std::move(result);
    }
    
    template <typename A, typename B, typename P>
    Set<std::pair<A, B>> make_pairs(const Set<A>& lhs, const Set<B>& rhs, P&& predicate)
    {
        Set<std::pair<A, B>> result ;
        for (auto&& first : lhs)
            for (auto&& second : rhs)
                if(predicate(first, second))
                    result.insert(std::pair<A, B>(first, second));
        return std::move(result);
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
    
     
}

#endif