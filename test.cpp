#include "include/zebra.hpp"

int main()
{
    using namespace zebra;
    Set<int> set({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    BinaryRelation<int, int> less{[](int x, int y) { return x <= y; }, set};
    std::cout << less << std::endl ;
    std::cout << std::boolalpha << std::endl ;
    std::cout << "Is reflexive ? " << less.reflexive() << std::endl ;
    std::cout << "Is symmetric ? " << less.symmetric() << std::endl ;
    std::cout << "Is transitive ? " << less.transitive() << std::endl ;
    std::cout << "Is equivalence ? " << less.equivalence() << std::endl ;
    std::cout << "Is surjective ? " << less.surjective() << std::endl ;
    std::cout << "Is injective ? " << less.injective() << std::endl ;
    std::cout << "Is functional ? " << less.functional() << std::endl ;
    std::cout << "Quotient set : " << less.quotient_set() << std::endl ;
    return 0;
}