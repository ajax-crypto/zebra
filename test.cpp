#include "include/zebra.hpp"

int main()
{
    using namespace zebra;
    Set<int> set({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    try {
        BinaryRelation<int, int> relation{[](int x, int y) { return x <= y; }, set};
        std::cout << relation << std::endl ;
        std::cout << std::boolalpha << std::endl ;
        std::cout << "Is reflexive ? " << relation.reflexive() << std::endl ;
        std::cout << "Is symmetric ? " << relation.symmetric() << std::endl ;
        std::cout << "Is asymmetric ? " << relation.asymmetric() << std::endl ;
        std::cout << "Is antisymmetric ? " << relation.antisymmetric() << std::endl ;
        std::cout << "Is transitive ? " << relation.transitive() << std::endl ;
        std::cout << "Is equivalence ? " << relation.equivalence() << std::endl ;
        std::cout << "Is surjective ? " << relation.surjective() << std::endl ;
        std::cout << "Is injective ? " << relation.injective() << std::endl ;
        std::cout << "Is functional ? " << relation.functional() << std::endl ;
        std::cout << "Is trichotomous ? " << relation.trichotomous() << std::endl ; 
        std::cout << "Quotient set : " << relation.quotient_set() << std::endl ;
    } 
    catch (const zebra::Exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }
    return 0;
}