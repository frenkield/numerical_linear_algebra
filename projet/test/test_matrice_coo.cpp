#include <matrice_coo.hpp>
#include <outils/catch.hpp>

using namespace std;

TEST_CASE("création et manipulation de la classe, MatriceCOO", "[matrice_coo]") {

    SECTION("on peut initialiser un matrice avec une liste") {

        MatriceCOO matrice = MatriceCOO(10, 10);

        matrice.set(1, 2, 4.876);
        matrice.set(6, 3, -6.2);

        vector<Triplet> triplets = matrice.getTriplets();

        REQUIRE(triplets.size() == 2);
        REQUIRE(triplets[1].valeur == -6.2);
    }
}
