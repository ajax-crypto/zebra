#include "include/zebra.hpp"

void relation_testing()
{
    using namespace zebra;
    std::cout << "\nRelation testing... [START]" << std::endl ;
    Set<int> set({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    BinaryRelation<int, int> relation{[](int x, int y) { return x <= y; }, set};
    std::cout << relation << std::endl ;
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
    std::cout << "Relation testing... [END]\n\n" << std::endl ;
}

void group_testing()
{
    using namespace zebra;
    std::cout << "\nGroup testing... [START]" << std::endl ;
    Set<int> set({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    Group<int> group([](int x, int y){ return (x + y) % 9; }, set);
    std::cout << "Is simple ? " << group.simple() << std::endl ;
    std::cout << "Is trace ? " << group.trace() << std::endl ;
    std::cout << "Is 0-sum free ? " << group.zerosumfree() << std::endl ;
    std::cout << "Is regular ? " << group.regular() << std::endl ;
    std::cout << "Is band ? " << group.band() << std::endl ;
    std::cout << "Is semilattice ? " << group.semilattice() << std::endl ;
    std::cout << "Is medial ? " << group.medial() << std::endl ;
    std::cout << "Is left semimedial ? " << group.left_semimedial() << std::endl ;
    std::cout << "Is right semimedial ? " << group.right_semimedial() << std::endl ;
    std::cout << "Is semi medial ? " << group.semimedial() << std::endl ;
    std::cout << "Is abelian ? " << group.commutative() << std::endl ;
    std::cout << "Is idempotent ? " << group.idempotent() << std::endl ;
    std::cout << "Is unipotent ? " << group.unipotent() << std::endl ;
    std::cout << "Is unital ? " << group.unital() << std::endl ;
    std::cout << "Is cancellative ? " << group.cancellative() << std::endl ;
    std::cout << "Group testing... [END]\n\n" << std::endl ;
}

int main()
{
    std::cout << std::boolalpha ;
    try {
        relation_testing();
        group_testing();
    } 
    catch (const zebra::Exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }
    return 0;
}