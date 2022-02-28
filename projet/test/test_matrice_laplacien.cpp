#include <matrice_laplacien.hpp>
#include <outils/catch.hpp>

using namespace std;

TEST_CASE("Matrice Laplacien", "[matrice_laplacien]") {

    SECTION("on peut manipuler une matrice avec l'operateur parentheses") {

        int taille = 10;
        MatriceLaplacien matriceLaplacien(taille);

        REQUIRE((matriceLaplacien.getHeight() == taille));
        REQUIRE((matriceLaplacien.getWidth() == taille));

        for (int i = 0; i < taille; i++) {
            REQUIRE(matriceLaplacien(i, i) == 2);

            if (i > 0) {
                REQUIRE(matriceLaplacien(i, i - 1) == -1);
            }

            if (i < taille - 1) {
                REQUIRE(matriceLaplacien(i, i + 1) == -1);
            }
        }
    }
}
