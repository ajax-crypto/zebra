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
    CREATE_SET_KEYS(unsigned int, hash);
    CREATE_SET_KEYS(size_t, hash);
    CREATE_SET_KEYS(double, hash);
    CREATE_SET_KEYS(long double, hash);
    
    CREATE_SAME_PAIR_KEYS(int, hash);
    CREATE_SAME_PAIR_KEYS(long long int, hash);
    CREATE_SAME_PAIR_KEYS(float, hash);
    CREATE_SAME_PAIR_KEYS(unsigned int, hash);
    CREATE_SAME_PAIR_KEYS(size_t, hash);
    CREATE_SAME_PAIR_KEYS(double, hash);
    CREATE_SAME_PAIR_KEYS(long double, hash);
    
    CREATE_DUAL_PAIR_KEYS(int, unsigned int, hash);
    CREATE_DUAL_PAIR_KEYS(int, size_t, hash);
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
    CREATE_ITERATOR_KEYS(size_t, hash);
    CREATE_ITERATOR_KEYS(double, hash);
    CREATE_ITERATOR_KEYS(long double, hash);
    
}

#endif
