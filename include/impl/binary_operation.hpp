#ifndef ZEBRA_BINARY_OP
#define ZEBRA_BINARY_OP

#include "utils.hpp"

namespace zebra
{
    template <typename T>
    class PartialOperation
    {
    public:
        
        typedef typename Set<T>::const_iterator         titer ;
        typedef Pair<titer, titer>                      param_type;
        typedef HashMap<param_type, titer>              table_type;
        typedef typename table_type::const_iterator     iter ;
        
        PartialOperation() {}
        PartialOperation(const table_type&, const Set<T>&);
        PartialOperation(iter, iter, const Set<T>&);
        
        T     operator()(T, T) const ;
        T     at(T x, T y) const { return *_table.at(param_type(_itr(x), _itr(y))); }
        iter  cbegin() const { return _table.cbegin(); }
        iter  cend() const { return _table.cend(); }
        bool  exists(T x, T y) const { return _table.count(param_type(_itr(x), _itr(y))) > 0; }
        
    protected:
        
        titer      _itr(const T& val) const { return _set.find(val); }
         
        Set<T>     _set;
        table_type _table;
        
    };
    
    template <typename T>
    PartialOperation<T>::PartialOperation(const table_type& table, const Set<T>& set)
        : _table{table}, _set{set}
    {}
    
    template <typename T>
    PartialOperation<T>::PartialOperation(iter start, iter end, const Set<T>& set)
        : _set{set}
    {
        _table = table_type(start, end);
    }
    
    template <typename T>
    T
    PartialOperation<T>::operator()(T first, T second) const
    {
        if (_set.find(first) == _set.cend() || _set.find(second) == _set.cend())
            throw Exception(DOES_NOT_EXIST, "Parameters not in codomain...");
        if (!exists(first, second))
            throw Exception(DOES_NOT_EXIST, "No result exists...");
        return at(first, second);
    }
    
    template <typename T> using PartialMagma = PartialOperation<T> ;
    template <typename T> using PartialGroupoid = PartialOperation<T> ;
    
    template <typename T>
    class BinaryOperation : public PartialOperation<T>
    {
    public:
        typedef typename std::conditional<
            std::is_arithmetic<T>::value, 
            std::function<T(T, T)>, 
            std::function<T(const T&, const T&)>>::type bin_op_type;
        using typename PartialOperation<T>::titer ;
        using typename PartialOperation<T>::param_type;
        using typename PartialOperation<T>::table_type;
        using typename PartialOperation<T>::iter ;
        
        BinaryOperation() {}
        BinaryOperation(const table_type&, const Set<T>&);
        BinaryOperation(iter, iter, const Set<T>&);
        BinaryOperation(bin_op_type&&, const Set<T>&);
        
    protected:
    
        using PartialOperation<T>::_set ;
        using PartialOperation<T>::_table ;
        using PartialOperation<T>::_itr ;
        
        void check() throw(Exception);
        
    };
    
    template <typename T>
    void
    BinaryOperation<T>::check() throw(Exception)
    {
        auto pairs = make_pairs(_set, _set);
        for (auto&& pair : pairs)
            if (_table.count(pair) == 0)
                throw Exception(NOT_CONFORMANT, "Given function is partial in nature...");
    }
    
    template <typename T>
    BinaryOperation<T>::BinaryOperation(const table_type& table, const Set<T>& set)
        : PartialOperation<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    BinaryOperation<T>::BinaryOperation(iter start, iter end, const Set<T>& set)
        : PartialOperation<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    BinaryOperation<T>::BinaryOperation(bin_op_type&& func, const Set<T>& set)
        : PartialOperation<T>{}
    {
        _set = set ;
        auto pairs = make_pairs(_set, _set);
        for (auto&& pair : pairs)
        {
            auto result = func(pair.first, pair.second);
            if (_set.find(result) == _set.cend())
                throw Exception(NOT_CONFORMANT, "Given function is not closed...");
             _table[param_type(_itr(pair.first), _itr(pair.second))] = _itr(result);
        }
    }
    
}

#endif