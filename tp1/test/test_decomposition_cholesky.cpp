#include <matrice.hpp>
#include <outils/catch.hpp>
#include <solveurs_directs.hpp>

using namespace std;

TEST_CASE( "decomposition Cholesky des Matrices", "[decomposition_cholesky]" ) {

    SECTION("tester la decomposition Cholesky avec matrice du tp") {

        double valeursMatrice[5][5] = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        Matrice matrice = Matrice(5);
        matrice.initialiser((double*)valeursMatrice);

        matrice.decomposeCholesky();

        Matrice matriceSuperieure = matrice.getDecompositionUpper();
        Matrice matriceInferieure = matrice.getDecompositionLower();
        Matrice matriceSuperieureTranspose = matriceSuperieure.transpose();
        REQUIRE((matriceInferieure == matriceSuperieureTranspose));

        Matrice produit = matriceInferieure * matriceSuperieure;

        matrice.initialiser((double*)valeursMatrice);
        REQUIRE((produit == matrice));
    }

    SECTION("tester la decomposition Choleksy avec une matrice symétrique aléatoire") {

        Matrice matrice = Matrice::genererMatriceSPDAleatoire(5);
        Matrice matriceClone = matrice;

        matrice.decomposeCholesky();

        Matrice matriceSuperieure = matrice.getDecompositionUpper();
        Matrice matriceSuperieureTranspose = matriceSuperieure.transpose();

        Matrice produit = matriceSuperieureTranspose * matriceSuperieure;
        REQUIRE((produit == matriceClone));
    }

    SECTION("tester la decomposition Choleksy avec une matrice symétrique aléatoire et le solveur direct") {

        Matrice matrice = Matrice::genererMatriceSPDAleatoire(5);
        Vecteur solution = Vecteur::genererVecteurAleatoire(5);
        Vecteur produit = matrice * solution;

        matrice.decomposeCholesky();

        Matrice matriceInferieure = matrice.getDecompositionLower();
        Matrice matriceSuperieure = matrice.getDecompositionUpper();

        Vecteur z = solve_triang_inf(matriceInferieure, produit);
        Vecteur x = solve_triang_sup(matriceSuperieure, z);

        REQUIRE((x == solution));
    }

    SECTION("tester la decomposition Cholesky et le solveur direct avec la matrice du TP") {

        double valeursMatrice[5][5] = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        Matrice matrice = Matrice(5);
        matrice.initialiser((double*)valeursMatrice);

        // ===================================

        Vecteur produit = Vecteur(5);

        double valeursVecteur[5] = {1, 1, 1, 1, 1};
        produit.initialiser((double*)&valeursVecteur);

        // ===================================

        matrice.decomposeCholesky();

        Matrice matriceInferieure = matrice.getDecompositionLower();
        Matrice matriceSuperieure = matrice.getDecompositionUpper();

        Vecteur z = solve_triang_inf(matriceInferieure, produit);
        Vecteur x = solve_triang_sup(matriceSuperieure, z);

        // ===================================

        Vecteur solution = Vecteur(5);
        solution.initialiser((double*)new double[5]{2.5, 4, 4.5, 4, 2.5});

        REQUIRE((x == solution));
    }
}
