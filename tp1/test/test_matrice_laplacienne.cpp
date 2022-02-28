#include <matrice_laplacienne.hpp>
#include <outils/catch.hpp>

using namespace std;

TEST_CASE( "Matrice Laplacienne", "[matrice_laplacienne]" ) {

    SECTION("on peut manipuler une matrice avec l'operateur parentheses") {

        int taille = 10;
        MatriceLaplacienne matriceLaplacienne(taille);

        REQUIRE((matriceLaplacienne.size() == taille));

        for (int i = 0; i < taille; i++) {
            REQUIRE(matriceLaplacienne(i, i) == 2);

            if (i > 0) {
                REQUIRE(matriceLaplacienne(i, i - 1) == -1);
            }

            if (i < taille - 1) {
                REQUIRE(matriceLaplacienne(i, i + 1) == -1);
            }
        }
    }
}
