#include <outils/catch.hpp>
#include <chargeur_matrice.hpp>

using namespace std;

TEST_CASE("classe ChargeurMatrice", "[chargeur_matrice]") {

    SECTION("charger matrix11.txt") {

        ChargeurMatrice chargeurMatrice = ChargeurMatrice();
        DenseMatrix matrice = chargeurMatrice.chargerDenseMatrix("data/matrices2/matrix11.txt");

        REQUIRE((matrice.getWidth() == 140 && matrice.getHeight() == 140));

        REQUIRE(matrice(0, 0) == 2841.11015922);
        REQUIRE(matrice(139, 139) == 2841.11015922);
        REQUIRE(matrice(139, 138) == -1420.0174635);
    }

    SECTION("charger matrix1.txt") {

        ChargeurMatrice chargeurMatrice = ChargeurMatrice();

        DenseMatrix matrice = chargeurMatrice.chargerDenseMatrix("data/matrices1/matrix1.txt");

        REQUIRE((matrice.getWidth() == 100 && matrice.getHeight() == 100));

        REQUIRE(matrice(0, 0) == 12.8546177665);
        REQUIRE(matrice(99, 99) == 12.8546177665);
        REQUIRE(matrice(99, 98) == 0.683926973995);
    }
}
