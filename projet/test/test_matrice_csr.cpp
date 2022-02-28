#include <iostream>
#include <matrice_coo.hpp>
#include <matrice_csr.hpp>
#include <matrice_laplacien_csr.hpp>
#include <outils/catch.hpp>

using namespace std;

TEST_CASE("création et manipulation de la classe, MatriceCSR", "[matrice_csr]") {

    SECTION("on peut créer une matrice csr à partir d'une matrice coo") {

        int nr = 5;
        int nc = 5;

        MatriceCOO matrice = MatriceCOO(nr, nc);

        matrice.set(1, 2, 4.876);
        matrice.set(0, 4, -6.2);
        matrice.set(4, 4, 123);

        vector<Triplet> triplets = matrice.getTriplets();

        REQUIRE(triplets.size() == 3);

        MatriceCSR matriceCsr = MatriceCSR();
        matriceCsr.populate(matrice);

        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                double valeur = 0;
                if (i == 1 && j == 2) {
                    valeur = 4.876;
                } else if (i == 0 && j == 4) {
                    valeur = -6.2;
                } else if (i == 4 && j == 4) {
                    valeur = 123;
                }
                REQUIRE(matriceCsr(i, j) == valeur);
            }
        }
    }

    SECTION("on peut faire un produit matrice-vecteur") {

        MatriceCSR matrice = MatriceLaplacienCSR(5);

        Vecteur b = Vecteur(5);
        Vecteur x = {2.5, 4, 4.5, 4, 2.5};

        matrice.MvProd(x, b);

        Vecteur solution = {1, 1, 1, 1, 1};
        REQUIRE(b == solution);
    }

    SECTION("on peut resoudre un systeme lineaire par minres") {

        MatriceCSR matrice = MatriceLaplacienCSR(5);

        Vecteur x = Vecteur(5);
        Vecteur b = {1, 1, 1, 1, 1};

        matrice.MinRes(x, b);

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};
        REQUIRE(x == solution);
    }

    SECTION("resoudre un systeme lineaire par la methode schwarz additif") {

        int n = 10;

        MatriceCSR matrice = MatriceLaplacienCSR(n);
        Vecteur b = Vecteur(n);
        b.initialiser(1);

        Vecteur xPcg = Vecteur(n);
        matrice.pcg(xPcg, b, 0.00001);

        Vecteur xCg = Vecteur(n);
        matrice.cg(xCg, b, 0.00001);

        REQUIRE(xPcg == xCg);
    }

    SECTION("resoudre un systeme lineaire par la methode schwarz additif avec une matrice plus grosse") {

        int n = 50;

        MatriceCSR matrice = MatriceLaplacienCSR(n);
        Vecteur b = Vecteur(n);
        b.initialiser(1);

        Vecteur xPcg = Vecteur(n);
        matrice.pcg(xPcg, b, 0.00001);

        Vecteur xCg = Vecteur(n);
        matrice.cg(xCg, b, 0.00001);

        REQUIRE(xPcg == xCg);
    }
}
