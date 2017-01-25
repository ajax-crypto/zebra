#ifndef ZEBRA_DEFINES
#define ZEBRA_DEFINES

#define _HOM(X) typename std::enable_if<std::is_same<D, R>::value, X>::type
#define _NHOM(X) typename std::enable_if<!std::is_same<D, R>::value, X>::type 
#define _HOM2(X, Y) typename std::enable_if<std::is_same<D, R>::value, X , Y>::type
#define _HOM3(X, Y, Z) typename std::enable_if<std::is_same<D, R>::value, X , Y , Z>::type
#define _ISB(X) typename std::enable_if<std::is_arithmetic<T>::value, X>::type 
#define _ISNB(X) typename std::enable_if<!std::is_arithmetic<T>::value, X>::type 
#define HOM(X) _HOM(X)
#define NHOM(x) _NHOM(X)
#define HOM2(X, Y) _HOM2(X, Y)
#define HOM3(X, Y, Z) _HOM3(X, Y, Z)
#define ISB(X) _ISB(X)
#define ISNB(X) _ISNB(X)

#define CREATE_ITERATOR_KEYS(type, converter) \
    template <>                                                             \
    struct hash<zebra::Set<type>::const_iterator>                           \
    {                                                                       \
        size_t operator()(const zebra::Set<type>::const_iterator& it) const \
        {                                                                   \
            return converter<type>()(*it);                                  \
        }                                                                   \
    };                                                                     
        
#define CREATE_SET_KEYS(type, converter) \
    template <>                                                            \
    struct hash<zebra::Set<type>>                                          \
    {                                                                      \
        size_t operator()(const zebra::Set<type>& p) const                 \
        {                                                                  \
            size_t val = 0u ;                                               \
            for (const type& element : p)                                  \
                val ^= converter<type>()(element) ;                        \
            return val ;                                                   \
        }                                                                  \
    };
    
#define _CREATE_PAIR_KEYS(type1, type2, converter) \
    template <>                                                            \
    struct hash<pair<type1, type2>>                                        \
    {                                                                      \
        size_t operator()(const pair<type1, type2>& p) const               \
        {                                                                  \
            return converter<type1>()(p.first) ^ converter<type2>()(p.second);         \
        }                                                                  \
    };   
    
#define CREATE_DUAL_PAIR_KEYS(type1, type2, converter) \
    _CREATE_PAIR_KEYS(type1, type2, converter)         \
    _CREATE_PAIR_KEYS(type2, type1, converter)     
    
#define CREATE_SAME_PAIR_KEYS(type, converter) _CREATE_PAIR_KEYS(type, type, converter)

#endif