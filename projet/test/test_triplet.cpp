#include <triplet.hpp>
#include <outils/catch.hpp>

TEST_CASE("création et opérateurs de la classe, Triplet", "[triplet]") {

    SECTION("on peut créer des Triplets") {

        Triplet triplet1 = Triplet(0, 5, -4.54);
        REQUIRE(triplet1.i == 0);
        REQUIRE(triplet1.j == 5);
        REQUIRE(triplet1.valeur == -4.54);

        Triplet triplet2 = triplet1;
        REQUIRE(triplet2.i == 0);
        REQUIRE(triplet2.j == 5);
        REQUIRE(triplet2.valeur == -4.54);
    }

    SECTION("on peut comparer des Triplets") {

        Triplet triplet1 = Triplet(0, 5, 1);
        Triplet triplet2 = Triplet(0, 5, 1);
        Triplet triplet3 = Triplet(0, 6, 1);
        Triplet triplet4 = Triplet(1, 2, 1);

        REQUIRE((triplet1 == triplet2));
        REQUIRE((triplet1 < triplet3));
        REQUIRE((triplet3 > triplet2));
        REQUIRE((triplet3 < triplet4));
        REQUIRE((triplet4 > triplet3));
    }
}
