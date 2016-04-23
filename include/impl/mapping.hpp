#ifndef ZEBRA_FUNCTION
#define ZEBRA_FUNCTION

#include "relation.hpp"

namespace zebra
{
    template <typename D, typename R>
    class Mapping : public BinaryRelation<D, R>
    {
         
    public:
        using BinaryRelation<D, R>::BinaryRelation ;
        using typename BinaryRelation<D, R>::qset_type ;
        
        R at(const D& val) const ;
        R operator()(const D& val) const ;
        qset_type kernel() const; 
        
        using BinaryRelation<D, R>::domain ;
        using BinaryRelation<D, R>::range  ;
        
    protected:
    
        using BinaryRelation<D, R>::_relation ;
        using BinaryRelation<D, R>::_codomain ;
        using BinaryRelation<D, R>::_from ;
    };
    
    template <typename D, typename R>
    typename Mapping<D, R>::qset_type
    Mapping<D, R>::kernel() const
    {
        typename BinaryRelation<D, R>::qset_type result ;
        auto pairs = make_pairs(domain(), [](const auto& set, const auto& first, const auto& second){ 
            return std::find(set.cbegin(), set.cend(), std::pair<D, R>(second, first)) != set.cend() && first != second ;
        });
        for (const auto& pair : pairs)
            if (at(pair.first) == at(pair.second))
                result.insert(pair);
        return result;
    }
    
    template <typename D, typename R>
    R
    Mapping<D, R>::at(const D& val) const 
    {
        return *(_relation.get(val)->cbegin());
    }
    
    template <typename D, typename R>
    R
    Mapping<D, R>::operator()(const D& val) const 
    {
        return at(val);
    }
    
    template <typename A, typename B> 
    std::ostream& 
    operator<<(std::ostream& stream, const Mapping<A, B>& br)
    {
        for (auto it = br.cbegin(); it != br.cend(); ++it)
            for (const auto& element : it->second)
                stream << "(" << it->first << ", " << element << ") ";
        return stream ;
    }
    
    template <typename A, typename B> using Function = Mapping<A, B>;
}

#endif