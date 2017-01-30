#ifndef ZEBRA_RELATION
#define ZEBRA_RELATION

#include "keys.hpp"

namespace zebra
{
    enum BinaryRelationProperty
    {
        SURJECTIVE           = 0,
        INJECTIVE            = 1, 
        FUNCTIONAL           = 1 << 2,
        LEFT_TOTAL           = 1 << 3,
        DIFUNCTIONAL         = 1 << 4,
        IDEMPOTENT           = 1 << 5,
        REFLEXIVE            = 1 << 6,
        IRREFLEXIVE          = 1 << 7,
        SYMMETRIC            = 1 << 8,
        ASYMMETRIC           = 1 << 9,
        ANTISYMMETRIC        = 1 << 10,
        TOTAL                = 1 << 11,
        TRICHOTOMOUS         = 1 << 12,
        RIGHT_EUCLIDEAN      = 1 << 13,
        LEFT_EUCLIDEAN       = 1 << 14,
        SERIAL               = 1 << 15,
        TRANSITIVE           = 1 << 16,
        SEMIORDER            = 1 << 17,
        TRANSITIVE_NONCOMP   = 1 << 18,
        ACYCLIC              = 1 << 19,
        ONE_TO_ONE           = INJECTIVE | FUNCTIONAL,
        FUNCTION             = FUNCTIONAL | LEFT_TOTAL,
        INJECTIVE_FUNCTION   = FUNCTION | INJECTIVE,
        SURJECTIVE_FUNCTION  = FUNCTION | SURJECTIVE,
        BIJECTION            = SURJECTIVE | ONE_TO_ONE,
        EQUIVALENCE          = REFLEXIVE | SYMMETRIC | TRANSITIVE,
        PARTIAL_EQUIVALENCE  = SYMMETRIC | TRANSITIVE,
        PREORDER             = REFLEXIVE | TRANSITIVE,
        PARTIAL_ORDER        = REFLEXIVE | ANTISYMMETRIC | TRANSITIVE,
        STRICT_PARTIAL_ORDER = IRREFLEXIVE | TRANSITIVE | ASYMMETRIC,
        TOTAL_PREORDER       = TOTAL | TRANSITIVE,
        TOTAL_ORDER          = TOTAL_PREORDER | ANTISYMMETRIC,
        CONNEX               = IRREFLEXIVE | SYMMETRIC,
        STRICT_WEAK_ORDER    = STRICT_PARTIAL_ORDER | TRANSITIVE_NONCOMP,
        STRICT_TOTAL_ORDER   = STRICT_WEAK_ORDER | TRICHOTOMOUS,
        STRICT_ORDER         = IRREFLEXIVE | ANTISYMMETRIC | TRANSITIVE
    };
    
    template <typename, typename> class Mapping ;
    
    template <typename D, typename R>
    class BinaryRelation
    {
    public:
        
        typedef Set<Set<R>>                        qset_type;
        typedef Set<Pair<D, R>>                    pset_type;
        typedef typename pset_type::const_iterator piter ;
        typedef typename Set<D>::const_iterator    diter ;
        typedef typename Set<R>::const_iterator    riter ;
        typedef HashMap<diter, Set<riter>>         rel_type;
        typedef typename rel_type::const_iterator  iter ;
        typedef std::function<bool(D, R)>          membership_type;
        typedef std::function<R(D)>                evaluation_type;
       
        BinaryRelation() {}
        BinaryRelation(piter, piter, diter, diter, riter, riter) ; 
        BinaryRelation(const pset_type&, const Set<D>&, const Set<R>&);
        BinaryRelation(const pset_type&);
        BinaryRelation(membership_type&&, diter, diter, riter, riter);
        BinaryRelation(membership_type&&, const Set<D>&, const Set<R>&);
        BinaryRelation(membership_type&&, diter, diter);
        BinaryRelation(membership_type&&, const Set<D>&);
        BinaryRelation(evaluation_type&&, diter, diter, riter, riter);
        BinaryRelation(evaluation_type&&, const Set<D>&, const Set<R>&);
        BinaryRelation(evaluation_type&&, diter, diter);
        BinaryRelation(evaluation_type&&, const Set<D>&);
        BinaryRelation(const BinaryRelation<D, R>&);
        
        std::size_t size() const { return _relation.size(); }
        iter        cbegin() const { return _relation.cbegin(); }
        iter        cend() const { return _relation.cend(); }
        
        bool   exists(const D&, const R&) const ;
        bool   exists(const Pair<D, R>&) const ;
        bool   exists(const D&) const;
        void   process(BinaryRelationProperty) ;
        Set<R> range() const ;
        Set<D> domain() const ;
        Set<Pair<D, R>> allpairs() const ;
        Set<R> afterset(const D&) const ;
        Set<D> foreset(const R&) const ;
        
        BinaryRelation<D, R> complement() const ;
        BinaryRelation<R, D> inverse() const ;
        
        bool  surjective() const ;
        bool  injective() const ;
        bool  functional() const ;
        bool  one_to_one() const { return injective() && functional(); }
        bool  left_total() const ;
        bool  function() const { return functional() && left_total(); }
        bool  injective_function() const { return injective() && function(); }
        bool  surjective_function() const { return surjective() && function(); }
        bool  bijection() const { return surjective() && one_to_one(); }
        bool  difunctional() const ;
        bool  contains(const BinaryRelation<D, R>&) const ;
        
        /* For homogenous BinaryRelations... */
        HOM(bool) idempotent() const { return (*this) * (*this) == (*this); }
        HOM(bool) reflexive() const ;
        HOM(bool) irreflexive() const ;
        HOM(bool) symmetric() const ;
        HOM(bool) asymmetric() const ;
        HOM(bool) antisymmetric() const ;
        HOM(bool) total() const ;
        HOM(bool) trichotomous() const ;
        HOM(bool) right_euclidean() const ; // TODO
        HOM(bool) left_euclidean() const ;  // TODO
        HOM(bool) euclidean() const ;       // TODO
        HOM(bool) serial() const ;
        HOM(bool) transitive() const ;
        HOM(bool) transitive_noncomp() const { complement().transitive(); }
        HOM(bool) equivalence() const { return reflexive() && symmetric() && transitive(); }
        HOM(bool) partial_equivalence() const { return symmetric() && transitive(); }
        HOM(bool) preorder() const { return reflexive() && transitive(); }
        HOM(bool) partial_order() const { return reflexive() && antisymmetric() && transitive(); }
        HOM(bool) poset() const { return partial_order(); }
        HOM(bool) strict_partial_order() const { return irreflexive() && transitive() && asymmetric(); }
        HOM(bool) total_preorder() const { return total() && transitive(); }
        HOM(bool) total_order() const { return antisymmetric() && transitive() && total(); }
        HOM(bool) connex() const { return irreflexive() && symmetric(); }
        HOM(bool) strict_weak_order() const { return irreflexive() && asymmetric() && transitive() && transitive_noncomp(); }
        HOM(bool) strict_total_order() const { return strict_weak_order() && trichotomous(); }
        HOM(bool) strict_order() const { return irreflexive() && antisymmetric() && transitive(); }
        HOM(bool) semi_order() const ;     // TODO
        HOM(bool) acyclic() const { return transitive_closure().antisymmetric(); }
        
        HOM(Set<R>)                 equivalence_class(const D&) const;
        HOM(qset_type)              quotient_set() const ;
        HOM2(Mapping<D, qset_type>) projection() const ;
        HOM2(BinaryRelation<D, R>)  reflexive_closure() const ;
        HOM2(BinaryRelation<D, R>)  reflexive_reduction() const ;
        HOM2(BinaryRelation<D, R>)  transitive_closure() const ;
        HOM2(BinaryRelation<D, R>)  transitive_reduction() const ;
        HOM2(BinaryRelation<D, R>)  preorder_closure() const ;      // TODO
        HOM2(BinaryRelation<D, R>)  equivalence_closure() const ;   // TODO
        HOM2(BinaryRelation<D, R>)  restrict(const Set<D>&) const ;
        
        template <typename A, typename B> friend std::ostream& operator<<(std::ostream&, const BinaryRelation<A, B>&);
        
        template <typename A, typename B> friend BinaryRelation<A, B> combination(const BinaryRelation<A, B>&, const BinaryRelation<A, B>&);
        template <typename A, typename B> friend BinaryRelation<A, B> intersection(const BinaryRelation<A, B>&, const BinaryRelation<A, B>&);
        template <typename A, typename B, typename C> friend BinaryRelation<A, C> composition(const BinaryRelation<A, B>&, const BinaryRelation<B, C>&);
        
    protected:
    
        rel_type _relation;
        Set<D>   _from ;
        Set<R>   _codomain ;
        
        HOM(Set<D>) all() const ;
        void      add(const D&, const R&);
        void      add(const Pair<D, R>&);
        void      add(const D&, riter, riter);       
        diter     _ditr(const D&) const ;
        riter     _ritr(const R&) const ;
        bool      _exists(diter, riter) const ;
        
    };

    template <typename T> using HomogenousBinaryRelation = BinaryRelation<T, T>;
    
    template <typename D, typename R>
    void
    BinaryRelation<D, R>::add(const D& first, const R& second)
    {
        auto ritr = _ritr(second);
        auto ditr = _ditr(first);
        if (ritr != _codomain.cend() && ditr != _from.cend())
            _relation[ditr].insert(ritr);
    }
    
    template <typename D, typename R>
    void
    BinaryRelation<D, R>::add(const D& first, riter start, riter end)
    {
        auto ditr = _ditr(first);
        if (ditr != _from.cend())
            _relation[ditr].insert(start, end);
    }
    
    template <typename D, typename R>
    void
    BinaryRelation<D, R>::add(const Pair<D, R>& pair)
    {
        add(pair.first, pair.second);
    }
    
    template <typename D, typename R>
    typename BinaryRelation<D, R>::riter
    BinaryRelation<D, R>::_ritr(const R& val) const
    {
        return _codomain.find(val);
    }
    
    template <typename D, typename R>
    typename BinaryRelation<D, R>::diter
    BinaryRelation<D, R>::_ditr(const D& val) const
    {
        return _from.find(val);
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::_exists(diter dit, riter rit) const
    {
        return _relation.count(dit) > 0 && _relation.at(dit).count(rit) > 0 ;
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(piter pstart, piter pend, 
                                         diter dstart, diter dend, 
                                         riter rstart, riter rend) 
    {
        _from = Set<D>{dstart, dend};
        _codomain = Set<R>{rstart, rend};
        for(; pstart != pend; ++pstart)
            add(*pstart);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(const pset_type& pairs, const Set<D>& from, const Set<R>& codomain)
        : _from{from}, _codomain{codomain}
    {
        for (auto it = pairs.cbegin(); it != pairs.cend(); ++it)
            add(*it);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(const pset_type& pairs)
    {
        for (auto&& pair : pairs)
        {
            _from.insert(pair.first);
            _codomain.insert(pair.second);
        }
        for (auto&& pair : pairs)
            add(pair);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(membership_type&& relation,
                                         diter dstart, 
                                         diter dend, 
                                         riter rstart, 
                                         riter rend)
    {
        _from = Set<D>{dstart, dend};
        _codomain = Set<R>{rstart, rend};
        auto pairs = make_pairs(_from, _codomain);
        for (const auto& pair : pairs)
            if (relation(pair.first) == pair.second)
                add(pair);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(membership_type&& relation,
                                         diter dstart, 
                                         diter dend)
    {
        static_assert(std::is_same<D, R>::value, "Relation must be on S -> S");
        _from = Set<D>{dstart, dend};
        _codomain = Set<R>{dstart, dend};
        auto pairs = make_pairs(_from, _from);
        for (const auto& pair : pairs)
            if (relation(pair.first, pair.second))
                add(pair);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(membership_type&& relation, const Set<D>& from, const Set<R>& codomain)
        : _from{from}, _codomain{codomain}
    {
        auto pairs = make_pairs(_from, _codomain);
        for (const auto& pair : pairs)
            if (relation(pair.first, pair.second))
                add(pair);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(membership_type&& relation, const Set<D>& set)
        : _from{set}, _codomain{set}
    {
        static_assert(std::is_same<D, R>::value, "Relation must be on S -> S");
        auto pairs = make_pairs(_from, _from);
        for (const auto& pair : pairs)
            if (relation(pair.first, pair.second))
                add(pair);
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(evaluation_type&& relation,
                                         diter dstart, 
                                         diter dend, 
                                         riter rstart, 
                                         riter rend)
    {
        _from = Set<D>{dstart, dend};
        _codomain = Set<R>{rstart, rend};
        for (auto&& x : _from)
            if (_codomain.find(relation(x)) != _codomain.cend())
                add(x, relation(x));
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>::BinaryRelation(const BinaryRelation<D, R>& copy)
    {
        _codomain = copy._codomain;
        _from = copy._from;
        for (auto&& pair : copy._relation)
            add(pair);
    }
    
    template <typename D, typename R>
    Set<R>
    BinaryRelation<D, R>::range() const
    {
        Set<R> result ;
        for (auto&& pair : _relation)
            for (auto&& element : pair.second)
                result.insert(*element);
        return std::move(result);
    }
    
    template <typename D, typename R>
    Set<D>
    BinaryRelation<D, R>::domain() const
    {
        Set<D> result ;
        for (auto it = cbegin(); it != cend(); ++it)
            result.insert(*it->first);
        return std::move(result);
    }
    
    template <typename D, typename R>
    Set<D>
    BinaryRelation<D, R>::foreset(const R& val) const
    {
        Set<D> result ;
        auto pos = _codomain.find(val);
        for (auto it = cbegin(); it != cend(); ++it)
            if (it->second.find(pos) != it->second.cend())
                result.insert(*it->first);
        return std::move(result);
    }
    
    template <typename D, typename R>
    Set<R>
    BinaryRelation<D, R>::afterset(const D& val) const
    {
        Set<R> result ;
        for (auto&& it : _relation.at(_ditr(val)))
            result.insert(*it);
        return std::move(result);
    }
    
    template <typename D, typename R>
    typename BinaryRelation<D, R>::pset_type
    BinaryRelation<D, R>::allpairs() const
    {
        Set<Pair<D, R>> result ;
        for (auto&& pair : _relation)
            for (auto&& element : pair.second)
                result.insert(Pair<D, R>(*pair.first, *element));
        return std::move(result);
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::exists(const D& dval, const R& rval) const
    {
        return _exists(_ditr(dval), _ritr(rval));
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::exists(const Pair<D, R>& pair) const
    {
        return exists(pair.first, pair.second);
    }

    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::exists(const D& dval) const
    {
        return _relation.count(_ditr(dval)) > 0;
    }
    
    template <typename D, typename R>
    BinaryRelation<D, R>
    BinaryRelation<D, R>::complement() const
    {
        BinaryRelation<D, R> comp ;
        comp._codomain = _codomain ;
        comp._from = _from ;
        for (auto&& keyval : _from)
            if (_relation.count(_ditr(keyval)) > 0)
                for (auto it = _codomain.cbegin(); it != _codomain.cend(); ++it)
                    if (!exists(keyval, *it))
                        comp.add(keyval, *it);
            else
                comp.add(keyval, comp._codomain.cbegin(), comp._codomain.cend());
        return std::move(comp);
    }
    
    template <typename D, typename R>
    BinaryRelation<R, D>
    BinaryRelation<D, R>::inverse() const
    {
        BinaryRelation<R, D> comp ;
        comp._codomain = _from ;
        comp._from = _codomain ;
        for (auto&& pair : _relation)
            for (auto&& element : pair.second)
                comp.add(*element, *pair);
        return std::move(comp);
    }
    
    template <typename D, typename R>
    HOM(Set<D>) 
    BinaryRelation<D, R>::all() const 
    {
        Set<D> result ;
        for (const auto& pair : _relation)
        {
            result.insert(*pair.first);
            for (const auto& it : pair.second)
                result.insert(*it);
        }
        return result;
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::contains(const BinaryRelation<D, R>& subset) const
    {
        if (subset.size() <= size())
        {
            if (_codomain != subset._codomain || _from != subset._from)
                return false ;
            for (auto&& pair : subset._relation)
                for (auto&& element : pair.second)
                    if (!exists(*pair.first, *element))
                        return false;
            return true;
        }
        return false;
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::injective() const
    {
        return zebra::all(_from, _from, _codomain, [this](auto x, auto y, auto z) -> bool {
            return (this->exists(x, z) && this->exists(y, z)) ? x == y : true;
        });
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::functional() const
    {
        return zebra::all(_codomain, _codomain, _from, [this](auto x, auto y, auto z) -> bool {
            return (this->exists(x, y) && this->exists(x, z)) ? z == y : true;
        });
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::surjective() const
    {
        return _codomain == range() ;
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::left_total() const
    {
        return _from == domain() ;
    }
    
    template <typename D, typename R>
    bool
    BinaryRelation<D, R>::difunctional() const
    {
        if(functional())
            return true ;
        auto d = domain();
        auto pairs = make_pairs(d, d);
        for (const auto& pair: pairs)
        {
            auto afterset1 = afterset(pair.first);
            auto afterset2 = afterset(pair.second);
            decltype(afterset1) output ;
            std::set_intersection(afterset1.begin(), afterset1.end(), afterset2.begin(), afterset2.end(), output.begin());
            if (output.size() > 0 && afterset1 != afterset2)
                return false;
        }
        return true;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::reflexive() const 
    {
        if (_from == _codomain)
        {
            return zebra::all(_relation, [this](auto x) -> bool {
                return this->exists(x, x);
            });
        }
        return false;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::irreflexive() const 
    {
        if (_from == _codomain)
        {
            return !zebra::any(_relation, [this](auto x) {
                return this->exists(x, x);
            });
        }
        return false;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::symmetric() const
    {
        if (_from == _codomain)
        {
            return zebra::all2(_relation, [this](auto x, auto y) -> bool {
                return this->exists(y, x);
            });
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::asymmetric() const
    {
        if (_from == _codomain)
        {
            return !zebra::any2(_relation, [this](auto x, auto y) -> bool {
                return this->exists(y, x);
            });
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::antisymmetric() const
    {
        if (_from == _codomain)
        {
            return zebra::all2(_relation, [this](auto x, auto y) -> bool {
                return this->exists(y, x) ? x == y : true;
            });
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::total() const
    {
        if (_from == _codomain)
        {
            return zebra::all2(_from, [this](auto x, auto y) -> bool {
                return this->exists(x, y) || this->exists(y, x);
            });
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::trichotomous() const
    {
        if (_from == _codomain)
        {
            return zebra::all2(_from, [this](auto x, auto y) -> bool {
                return this->exists(x, y) || this->exists(y, x) || x == y;
            });
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::serial() const
    {
        if (_from == _codomain)
        {
            return domain() == _from ;
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM(bool)
    BinaryRelation<D, R>::transitive() const
    {
        if (_from == _codomain)
        {
            return zebra::all3(_relation, [this](auto x, auto y, auto z) -> bool {
                return this->exists(x, y) && this->exists(y, z) && this->exists(x, z);
            });
        }
        return false ;
    }
    
    template <typename D, typename R>
    HOM2(typename BinaryRelation<D, R>::qset_type)
    BinaryRelation<D, R>::quotient_set() const
    {
        Set<Set<R>> qs ;
        if (equivalence())
            for (const auto& element : domain())
                qs.insert(afterset(element));
        return qs ;
    }
    
    template <typename D, typename R>
    HOM2(BinaryRelation<D, R>)
    BinaryRelation<D, R>::transitive_closure() const 
    {
        BinaryRelation<D, R> result = *this ;
        for (auto&& pair : result._relation)
            for (auto&& element : pair.second)
                if (result._relation.count(element) > 0)
                {
                    auto add = result._relation.at(element);
                    result.add(*pair.first, add.cbegin(), add.cend());
                }
        return std::move(result);
    }
    
    template <typename D, typename R>
    HOM2(BinaryRelation<D, R>)
    BinaryRelation<D, R>::reflexive_closure() const 
    {
        BinaryRelation<D, R> result = *this ;
        for (auto&& pair : result._relation)
            result.add(*pair.first, pair.first);
        return std::move(result);
    }
    
    template <typename D, typename R>
    HOM2(BinaryRelation<D, R>)
    BinaryRelation<D, R>::reflexive_reduction() const 
    {
        BinaryRelation<D, R> result = *this ;
        for (auto&& pair : result._relation)
        {
            auto next = result._relation[pair.first];
            next.erase(std::find(result._codomain.cbegin(), result._codomain.cend(), pair.first));
            result._relation[pair.first] = next ;
        }
        return std::move(result);
    }
    
    template <typename D, typename R>
    HOM3(Mapping<D, typename BinaryRelation<D, R>::qset_type>)
    BinaryRelation<D, R>::projection() const 
    {
        Mapping<D, qset_type> project ;
        project._codomain = quotient_set();
        project._from = domain();
        for (auto&& element : project._from)
            project.add(element, equivalence_class(element));
        return std::move(project);
    }

    template <typename D, typename R>
    HOM(Set<R>)
    BinaryRelation<D, R>::equivalence_class(const D& element) const
    {
        Set<R> result ;
        if (equivalence())
            return afterset(element);
        return std::move(result);
    }
    
    template <typename A, typename B> 
    std::ostream& 
    operator<<(std::ostream& stream, const BinaryRelation<A, B>& br)
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
    
    template <typename D, typename R> BinaryRelation<D, R> intersection(const BinaryRelation<D, R>& lhs, const BinaryRelation<D, R>& rhs)
    {
        BinaryRelation<D, R> result ;
        result._codomain = lhs._codomain;
        result._from = lhs._from ;
        auto ck = common_keys<D, decltype(lhs.cbegin())>(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
        for (auto&& key : ck)
        {
            auto set = intersection_itr(lhs.at(key), rhs.at(key));
            for (auto&& element : set)
                result.add(key, element);
        }     
        return result;
    }
    
    template <typename D, typename R> BinaryRelation<D, R> combination(const BinaryRelation<D, R>& lhs, const BinaryRelation<D, R>& rhs)
    {
        BinaryRelation<D, R> result ;
        result._codomain = lhs._codomain;
        result._from = lhs._from ;
        auto ck = all_keys<D, decltype(lhs.cbegin())>(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
        for (auto&& key : ck)
        {
            auto set = combination_itr(lhs.at(key), rhs.at(key));
            for (auto&& element : set)
                result.add(key, element);
        }
        return result;
    }
    
    template <typename A, typename B, typename C> BinaryRelation<A, C> composition(const BinaryRelation<A, B>& lhs, const BinaryRelation<B, C>& rhs)
    {
        BinaryRelation<A, C> result ;
        result._from = lhs._from ;
        result._codomain = rhs._codomain ;
        for (auto&& pair : lhs._relation)
            for (auto&& element : pair.second)
                if (rhs._relation.count(rhs._itr(*element)) > 0)
                    for (auto&& ans : rhs._relation.at(element))
                        result.add(result._itr(pair.first), ans);
        return result ;
    }
    
    template <typename A, typename B, typename C> BinaryRelation<A, C> operator*(const BinaryRelation<A, B>& lhs, const BinaryRelation<B, C>& rhs)
    {
        return composition(lhs, rhs);
    }
    
    template <typename D, typename R> BinaryRelation<D, R> operator|(const BinaryRelation<D, R>& lhs, const BinaryRelation<D, R>& rhs)
    {
        return combination(lhs, rhs);
    }
    
    template <typename D, typename R> BinaryRelation<D, R> operator&(const BinaryRelation<D, R>& lhs, const BinaryRelation<D, R>& rhs)
    {
        return intersection(lhs, rhs);
    }
    
    template <typename D, typename R> BinaryRelation<D, R> operator^(const BinaryRelation<D, R>& lhs, std::size_t power)
    {
        decltype(lhs) result = lhs ;
        for (auto i = 2; i <= power; ++i)
            result = result * lhs ;
        return result ;
    }
    
    template <typename A, typename B> BinaryRelation<A, B> operator~(const BinaryRelation<A, B>& lhs)
    {
        return lhs.complement();
    }
    
    template <typename A, typename B> BinaryRelation<A, B> operator!(const BinaryRelation<A, B>& lhs)
    {
        return lhs.inverse();
    }
        

}

#endif