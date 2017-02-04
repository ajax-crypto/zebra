#ifndef ZEBRA_KEYS
#define ZEBRA_KEYS

#include "defines.hpp"
#include "utils.hpp"

namespace std
{

    CREATE_SET_KEYS(int, hash);
    CREATE_SET_KEYS(long int, hash);
    CREATE_SET_KEYS(long long int, hash);
    CREATE_SET_KEYS(float, hash);
    CREATE_SET_KEYS(double, hash);
    CREATE_SET_KEYS(long double, hash);
    
    CREATE_SAME_PAIR_KEYS(int, hash);
    CREATE_SAME_PAIR_KEYS(long long int, hash);
    CREATE_SAME_PAIR_KEYS(float, hash);
    CREATE_SAME_PAIR_KEYS(double, hash);
    CREATE_SAME_PAIR_KEYS(long double, hash);
    
    CREATE_DUAL_PAIR_KEYS(int, float, hash);
    CREATE_DUAL_PAIR_KEYS(int, double, hash);
    CREATE_DUAL_PAIR_KEYS(int, long long int, hash);
    CREATE_DUAL_PAIR_KEYS(unsigned int, float, hash);
    CREATE_DUAL_PAIR_KEYS(unsigned int, double, hash);
    CREATE_DUAL_PAIR_KEYS(unsigned int, long double, hash);
    CREATE_DUAL_PAIR_KEYS(float, double, hash);
    CREATE_DUAL_PAIR_KEYS(float, long double, hash);
    
    CREATE_ITERATOR_KEYS(int, hash);
    CREATE_ITERATOR_KEYS(long int, hash);
    CREATE_ITERATOR_KEYS(long long int, hash);
    CREATE_ITERATOR_KEYS(float, hash);
    CREATE_ITERATOR_KEYS(unsigned int, hash);
    CREATE_ITERATOR_KEYS(double, hash);
    CREATE_ITERATOR_KEYS(long double, hash);

    template <typename T> inline size_t pair_converter(const pair<T, T>& p) 
    { 
        return static_cast<int>(*p.first) ^ static_cast<int>(*p.second); 
    }

    template <typename T> using HashMap_Node = typename zebra::Set<T>::const_iterator;
    template <typename T> using Iterator_Node_Pair = typename zebra::Pair<HashMap_Node<T>, HashMap_Node<T>>;

    CREATE_ITERATOR_KEYS_FOR_MAP(int);
    CREATE_ITERATOR_KEYS_FOR_MAP(long int);
    CREATE_ITERATOR_KEYS_FOR_MAP(long long int);
    CREATE_ITERATOR_KEYS_FOR_MAP(float);
    CREATE_ITERATOR_KEYS_FOR_MAP(unsigned int);
    CREATE_ITERATOR_KEYS_FOR_MAP(double);
    CREATE_ITERATOR_KEYS_FOR_MAP(long double);
    
}

#endif
