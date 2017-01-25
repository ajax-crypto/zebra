#ifndef ZEBRA_FUNCTION
#define ZEBRA_FUNCTION

#include "relation.hpp"

namespace zebra
{
    template <typename D, typename R>
    class Mapping : public BinaryRelation<D, R>
    {
         
    public:
        using typename BinaryRelation<D, R>::qset_type;
        using typename BinaryRelation<D, R>::pset_type;
        using typename BinaryRelation<D, R>::piter ;
        using typename BinaryRelation<D, R>::diter ;
        using typename BinaryRelation<D, R>::riter ;
        using typename BinaryRelation<D, R>::rel_type;
        using typename BinaryRelation<D, R>::iter ;
        using typename BinaryRelation<D, R>::membership_type;
        using typename BinaryRelation<D, R>::evaluation_type;
        
        Mapping() {}
        Mapping(piter, piter, diter, diter, riter, riter) ; 
        Mapping(const pset_type&, const Set<D>&, const Set<R>&);
        Mapping(const pset_type&);
        Mapping(membership_type&&, diter, diter, riter, riter);
        Mapping(membership_type&&, const Set<D>&, const Set<R>&);
        Mapping(membership_type&&, diter, diter);
        Mapping(membership_type&&, const Set<D>&);
        Mapping(evaluation_type&&, diter, diter, riter, riter);
        Mapping(evaluation_type&&, const Set<D>&, const Set<R>&);
        Mapping(evaluation_type&&, diter, diter);
        Mapping(evaluation_type&&, const Set<D>&);
        Mapping(const Mapping<D, R>&);
        
        R at(const D& val) const ;
        R operator()(const D& val) const ;
        Mapping<R, D> inverse() const ;
        qset_type kernel() const; 
        
        using BinaryRelation<D, R>::domain ;
        using BinaryRelation<D, R>::range  ;
        using BinaryRelation<D, R>::function ;
        
    protected:
    
        using BinaryRelation<D, R>::_relation ;
        using BinaryRelation<D, R>::_codomain ;
        using BinaryRelation<D, R>::_from ;
        
    private:
        void check() throw(Exception); 
    };
    
    template <typename D, typename R>
    void
    Mapping<D, R>::check() throw(Exception)
    {
        if (!function())
            throw Exception(NOT_CONFORMANT, "Given parameters do not form a function/mapping...");
    }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(piter pstart, piter pend, diter dstart, diter dend, riter rstart, riter rend)
        : BinaryRelation<D, R>{pstart, pend, dstart, dend, rstart, rend}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(const pset_type& pairs, const Set<D>& from, const Set<R>& codomain)
        : BinaryRelation<D, R>{pairs, from, codomain}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(const pset_type& pairs)
        : BinaryRelation<D, R>{pairs}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(membership_type&& relation,
                                         diter dstart, 
                                         diter dend, 
                                         riter rstart, 
                                         riter rend)
        : BinaryRelation<D, R>{relation, dstart, dend, rstart, rend}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(membership_type&& relation,
                                         diter dstart, 
                                         diter dend)
        : BinaryRelation<D, R>{relation, dstart, dend}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(membership_type&& relation, const Set<D>& from, const Set<R>& codomain)
        : BinaryRelation<D, R>{relation, from, codomain}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(membership_type&& relation, const Set<D>& set)
        : BinaryRelation<D, R>{relation, set}
    { check(); }
    
    template <typename D, typename R>
    Mapping<D, R>::Mapping(evaluation_type&& relation,
                                         diter dstart, 
                                         diter dend, 
                                         riter rstart, 
                                         riter rend)
        : BinaryRelation<D, R>{relation, dstart, dend, rstart, rend}
    { check(); }
    
    template <typename D, typename R>
    typename Mapping<D, R>::qset_type
    Mapping<D, R>::kernel() const
    {
        typename BinaryRelation<D, R>::qset_type result ;
        auto pairs = make_pairs(domain(), [](const auto& set, const auto& first, const auto& second){ 
            return std::find(set.cbegin(), set.cend(), Pair<D, R>(second, first)) != set.cend() && first != second ;
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
        if (_codomain.find(val) == _codomain.cend())
            throw Exception(DOES_NOT_EXIST, "Parameter not in codomain...");
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
        {
            stream << *it->first << " : [ ";
            for (const auto& element : it->second)
                stream << *element << " ";
            stream << "]\n";
        }
        return stream ;
    }
    
    template <typename A, typename B> using Function = Mapping<A, B>;
}

#endif