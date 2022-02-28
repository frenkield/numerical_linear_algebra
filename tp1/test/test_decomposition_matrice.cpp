#include <matrice.hpp>
#include <outils/catch.hpp>
#include <solveurs_directs.hpp>

using namespace std;

TEST_CASE( "decomposition LU des Matrices", "[decomposition_matrice]" ) {

    SECTION("tester la decomposition LU avec une matrice spécifique") {

        Matrice lower(5);
        double valeursLower[5][5] = {
                {1, 0, 0, 0, 0},
                {1, 1, 0, 0, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 1, 1, 0},
                {-5, 0, 0, 1, 1}
        };

        lower.initialiser((double*)valeursLower);
//        cout << lower << endl << endl;

        Matrice upper(5);
        double valeursUpper[5][5] = {
                {2, 1, 1, 1, 10},
                {0, 2, 1, 1, 1},
                {0, 0, 2, 1, 1},
                {0, 0, 0, 2, 1},
                {0, 0, 0, 0, 2}
        };

        upper.initialiser((double*)valeursUpper);

        Matrice matrice = lower * upper;
        matrice.decomposeLU();

        REQUIRE((matrice.getDecompositionLower() == lower));
        REQUIRE((matrice.getDecompositionUpper() == upper));
    }

    SECTION("tester la decomposition LU avec une matrice aléatoire") {

        Matrice matriceInferieure = Matrice::genererMatriceInferieureAleatoire(5);
        Matrice matriceSuperieure = Matrice::genererMatriceSuperieureAleatoire(5);

        Matrice matrice = matriceInferieure * matriceSuperieure;
        matrice.decomposeLU();

        REQUIRE((matrice.getDecompositionLower() == matriceInferieure));
        REQUIRE((matrice.getDecompositionUpper() == matriceSuperieure));
    }

    SECTION("tester la decomposition LU et le solveur direct") {

        Matrice matrice = Matrice::genererMatriceAleatoire(3);
        Vecteur solution = Vecteur::genererVecteurAleatoire(3);
        Vecteur produit = matrice * solution;

        matrice.decomposeLU();

        Matrice matriceInferieure = matrice.getDecompositionLower();
        Matrice matriceSuperieure = matrice.getDecompositionUpper();

        Vecteur z = solve_triang_inf(matriceInferieure, produit);
        Vecteur x = solve_triang_sup(matriceSuperieure, z);

        REQUIRE((x == solution));
    }

    SECTION("tester la decomposition LU et le solveur direct avec la matrice du TP") {

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

        matrice.decomposeLU();

//        cout << matrice << endl;


        Matrice matriceInferieure = matrice.getDecompositionLower();
        Matrice matriceSuperieure = matrice.getDecompositionUpper();

        Vecteur z = solve_triang_inf(matriceInferieure, produit);
//        cout << z << endl;
        Vecteur x = solve_triang_sup(matriceSuperieure, z);
//        cout << x << endl;

        // ===================================

        Vecteur solution = Vecteur(5);
        solution.initialiser((double*)new double[5]{2.5, 4, 4.5, 4, 2.5});

        REQUIRE((x == solution));
    }
}
