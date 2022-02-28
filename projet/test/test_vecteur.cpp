#include <vecteur.hpp>
#include <dense_matrix.hpp>
#include <outils/catch.hpp>

TEST_CASE("création et opérateurs de la classe, Vecteur", "[vecteur]") {

    SECTION("on peut initialiser un vecteur avec une liste") {
        Vecteur vecteur = {1, 2, 3, 2, 8};
        REQUIRE(vecteur.size() == 5);
        REQUIRE(vecteur(1) == 2);
    }

    SECTION("on peut manipuler un vecteur avec l'operateur parentheses") {

        Vecteur vecteur(10);
        REQUIRE(vecteur.size() == 10);

        vecteur(1) = 5;
        REQUIRE(vecteur(1) == 5);
    }

    SECTION("on peut additonner et soustraire des vecteurs") {

        Vecteur vecteur1(10);
        Vecteur vecteur2(10);

        vecteur1(0) = 5;
        vecteur2(0) = 3;

        vecteur1(3) = 9.9;
        vecteur2(3) = 7.2;

        Vecteur sommeVecteur = vecteur1 + vecteur2;

        REQUIRE(sommeVecteur.size() == vecteur1.size());
        REQUIRE(sommeVecteur(0) == 8);
        REQUIRE(sommeVecteur(1) == 0);
        REQUIRE(sommeVecteur(3) == 17.1);

        Vecteur differenceVecteur = vecteur1 - vecteur2;
        REQUIRE(differenceVecteur.size() == vecteur1.size());
        REQUIRE(differenceVecteur(0) == 2);
        REQUIRE(differenceVecteur(1) == 0);
        REQUIRE(differenceVecteur(3) == 2.7);

        differenceVecteur = vecteur2 - vecteur1;
        REQUIRE(differenceVecteur(3) == -2.7);

    }

    SECTION("on peut multiplier un vecteur par un scalaire") {

        Vecteur vecteur(10);

        vecteur(0) = 5;
        vecteur(3) = 9.9;

        Vecteur nouveauVecteur = vecteur * 2.2;
        REQUIRE(vecteur(0) == 5);
        REQUIRE(nouveauVecteur(0) == (5 * 2.2));
        REQUIRE(nouveauVecteur(3) == (9.9 * 2.2));

        nouveauVecteur = vecteur * -3.65;
        REQUIRE(vecteur(0) == 5);
        REQUIRE(nouveauVecteur(0) == (5 * -3.65));
        REQUIRE(nouveauVecteur(3) == (9.9 * -3.65));

        nouveauVecteur = 2.2 * vecteur;
        REQUIRE(vecteur(0) == 5);
        REQUIRE(nouveauVecteur(0) == (5 * 2.2));
        REQUIRE(nouveauVecteur(3) == (9.9 * 2.2));

        nouveauVecteur = -3.65 * vecteur;
        REQUIRE(vecteur(0) == 5);
        REQUIRE(nouveauVecteur(0) == (5 * -3.65));
        REQUIRE(nouveauVecteur(3) == (9.9 * -3.65));
    }

    SECTION("on peut calculer la norme d'une vecteur") {

        Vecteur vecteur(10);

        vecteur(0) = 3;
        vecteur(3) = 4;

        REQUIRE(vecteur.norme() == 5);
    }

    SECTION("on peut faire un produit scalaier") {

        Vecteur vecteur1 = {1, 2, 3};
        Vecteur vecteur2 = {2, 0, -3};
        double produitScalaire = vecteur1 * vecteur2;
        REQUIRE(produitScalaire == -7);
    }

    SECTION("on peut enchainer des operations") {

        DenseMatrix matrice = {{1, 2, 3}, {2, 3, 1}, {0, 0, 1}};
        Vecteur vecteur = {1, 2, 3};

        Vecteur mv = matrice * vecteur;

        double mvm = vecteur * mv;
        double produit = vecteur * (matrice * vecteur);

        REQUIRE(produit == 45);
        REQUIRE(produit == mvm);
    }
}
