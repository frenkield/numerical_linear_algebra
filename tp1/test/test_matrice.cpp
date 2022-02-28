#include <matrice.hpp>
#include <outils/catch.hpp>

using namespace std;

TEST_CASE( "création et operateurs de la classe, Matrice", "[matrice]" ) {

    SECTION("on peut initialiser un matrice avec une liste") {
        Matrice matrice = {
            {1, 2, 3, 2, 8},
            {-1, 23, 3.5, 5.2, 8},
            {1, 52, 3, 2, 8},
            {1, -12, 3, 2, 8},
            {1, 2, 3, 2, 8}
        };
        REQUIRE(matrice.size() == 5);
        REQUIRE(matrice(1, 3) == 5.2);
    }

    SECTION("on peut manipuler une matrice avec l'operateur parentheses") {

        Matrice matrice(10);
        REQUIRE(matrice.size() == 10);

        matrice(3, 4) = 5;
        REQUIRE(matrice(3, 4) == 5);
    }

    SECTION("on peut additonner et soustraire des matrices") {

        Matrice matrice1(10);
        Matrice matrice2(10);

        matrice1(0, 0) = 5;
        matrice2(0, 0) = 3;

        matrice1(3, 3) = 9.9;
        matrice2(3, 3) = 7.2;

        Matrice sommeMatrice = matrice1 + matrice2;

        REQUIRE(sommeMatrice.size() == matrice1.size());
        REQUIRE(sommeMatrice(0, 0) == 8);
        REQUIRE(sommeMatrice(1, 1) == 0);
        REQUIRE(sommeMatrice(3, 3) == 17.1);

        Matrice differenceMatrice = matrice1 - matrice2;
        REQUIRE(differenceMatrice.size() == matrice1.size());
        REQUIRE(differenceMatrice(0, 0) == 2);
        REQUIRE(differenceMatrice(1, 1) == 0);
        REQUIRE(differenceMatrice(3, 3) == 2.7);

        differenceMatrice = matrice2 - matrice1;
        REQUIRE(differenceMatrice(3, 3) == -2.7);
    }

    SECTION("on peut multiplier des matrices") {

        Matrice matrice1(10);
        Matrice matrice2(10);

        matrice1(0, 0) = 5;
        matrice1(0, 1) = -6.3;
        matrice2(0, 0) = 3;
        matrice2(0, 5) = 48.4545;
        matrice2(1, 5) = 8.2;

        Matrice produitMatrice = matrice1 * matrice2;
        REQUIRE(produitMatrice(0, 0) == 15);
        REQUIRE(produitMatrice(0, 5) == 5 * 48.4545 + -6.3 * 8.2);
    }

    SECTION("on peut multiplier une matrice par une scalaire") {

        Matrice matrice(10);

        matrice(0, 0) = 5;
        matrice(3, 3) = 9.9;

        Matrice nouveauMatrice = matrice * 2.2;
        REQUIRE(matrice(0, 0) == 5);
        REQUIRE(nouveauMatrice(0, 0) == (5 * 2.2));
        REQUIRE(nouveauMatrice(3, 3) == (9.9 * 2.2));

        nouveauMatrice = matrice * -3.65;
        REQUIRE(matrice(0, 0) == 5);
        REQUIRE(nouveauMatrice(0, 0) == (5 * -3.65));
        REQUIRE(nouveauMatrice(3, 3) == (9.9 * -3.65));
    }

    SECTION("on peut multiplier un vecteur par une matrice") {

        Matrice matrice(10);
        Vecteur vecteur(10);

        matrice(0, 0) = 5;
        matrice(0, 1) = -6.3;
        matrice(0, 5) = 48.4;
        matrice(1, 5) = 8.2;
        matrice(5, 0) = -7;
        matrice(5, 2) = 48.4;

        vecteur(0) = 2;
        vecteur(2) = 3.7;

        Vecteur resultatVecteur = matrice * vecteur;
        REQUIRE(resultatVecteur(0) == 5 * 2);
        REQUIRE(resultatVecteur(5) == (-7 * 2) + (48.4 * 3.7));
    }

    SECTION("on peut generer le transpose d'une matrice") {

        double valeursMatrice[5][5] = {
            {2, -1, 0, 7, 9},
            {-1, 2, -1, -55, 8},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        Matrice matrice = Matrice(5);
        matrice.initialiser((double*)valeursMatrice);

        Matrice transpose = matrice.transpose();

        double valeursMatriceTranspose[5][5] = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {7, -55, -1, 2, -1},
            {9, 8, 0, -1, 2}
        };

        matrice.initialiser((double*)valeursMatriceTranspose);
        REQUIRE((transpose == matrice));
    }

    SECTION("on peut extraire le diagonal et le diagonal inverse") {

        Matrice matrice = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        Matrice diagonal = matrice.getDiagonal();
        Matrice diagonalTest = {{1, 0, 0}, {0, 5, 0}, {0, 0, 9}};
        REQUIRE((diagonal == diagonalTest));

        matrice = {{1, 2, 3}, {4, 4, 6}, {7, 8, 8}};
        diagonal = matrice.getDiagonalInverse();
        diagonalTest = {{1, 0, 0}, {0, 0.25, 0}, {0, 0, 0.125}};
        REQUIRE((diagonal == diagonalTest));
    }
}
