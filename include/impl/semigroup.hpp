#ifndef ZEBRA_SEMIGROUP
#define ZEBRA_SEMIGROUP

#include "magma.hpp"

namespace zebra
{
    template <typename T>
    class SemiGroup : public Magma<T>
    {
    public:
        using typename Magma<T>::bin_op_type;
        using typename Magma<T>::titer ;
        using typename Magma<T>::param_type;
        using typename Magma<T>::entry_type;
        using typename Magma<T>::table_type;
        using typename Magma<T>::iter ;
        using Magma<T>::idempotent;
        using Magma<T>::commutative;
        using Magma<T>::associative;
        
        SemiGroup() {}
        SemiGroup(const table_type&, const Set<T>&);
        SemiGroup(iter, iter, const Set<T>&);
        SemiGroup(bin_op_type&&, const Set<T>&);
        
        bool band() const { return idempotent(); }
        bool semilattice() const { return band() && commutative(); }
        bool regular() const ;
        bool separative() const ;
        
        ISB(Set<T>)  principal_left_ideal(T) const ;
        ISNB(Set<T>) principal_left_ideal(const T&) const ;
        ISB(Set<T>)  principal_right_ideal(T) const ;
        ISNB(Set<T>) principal_right_ideal(const T&) const ;
        ISB(Set<T>)  principal_ideal(T) const ;
        ISNB(Set<T>) principal_ideal(const T&) const ;
        
        ISB2(BinaryRelation<T, T>) L(T, T) const ;
        ISB2(BinaryRelation<T, T>) R(T, T) const ;
        ISB2(BinaryRelation<T, T>) J(T, T) const ;
        ISB2(BinaryRelation<T, T>) H(T, T) const ;
        ISB2(BinaryRelation<T, T>) D(T, T) const ;
        
    protected:
        using Magma<T>::_set ;
        using Magma<T>::_table ;
        using Magma<T>::_itr ;
        
        void check() throw(Exception);
    };
    
    template <typename T>
    void
    SemiGroup<T>::check() throw(Exception)
    {
        if(!associative())
            throw Exception(NOT_CONFORMANT, "Operation is not associative...");
    }
    
    template <typename T>
    SemiGroup<T>::SemiGroup(const table_type& table, const Set<T>& set)
        : BinaryOperation<T>{table, set}
    {
        check();
    }
    
    template <typename T>
    SemiGroup<T>::SemiGroup(iter start, iter end, const Set<T>& set)
        : BinaryOperation<T>{start, end, set}
    {
        check();
    }
    
    template <typename T>
    SemiGroup<T>::SemiGroup(bin_op_type&& func, const Set<T>& set)
        : BinaryOperation<T>{func, set}
    {
        check();
    }
}

#endif