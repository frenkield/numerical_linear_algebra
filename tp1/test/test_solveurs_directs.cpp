#include <matrice.hpp>
#include <solveurs_directs.hpp>
#include <outils/catch.hpp>

bool comparerValeurs(double valeur1, double valeur2) {
    return std::abs(valeur1 - valeur2) < 0.01;
}

TEST_CASE("solveurs directs", "[solveurs-directs]") {

    SECTION("testSolveursDirectsInferieur") {

        Matrice matrice(3);
        Vecteur vecteur(3);

        vecteur(0) = 4;
        vecteur(1) = 2;
        vecteur(2) = 3;

        matrice(0, 0) = 2.1;
        matrice(1, 1) = 5.3;
        matrice(2, 2) = -2.9;

        Vecteur solutionVecteur = solve_triang_inf(matrice, vecteur);
        REQUIRE(solutionVecteur(0) == 4.0 / 2.1);

        // ========================================================

        vecteur(0) = 1;
        vecteur(1) = 2;
        vecteur(2) = 3;

        double valeursMatrice[3][3] = {
                {6, 0, 0},
                {5, 4, 0},
                {3, 2, 1}
        };

        matrice.initialiser((double *) valeursMatrice);
        solutionVecteur = solve_triang_inf(matrice, vecteur);

        REQUIRE(solutionVecteur(0) == 1.0 / 6.0);
        REQUIRE(comparerValeurs(solutionVecteur(1), (2.0 - (5.0 * 1.0 / 6.0)) / 4.0));

        double valeursMatrice2[3][3] = {
                {6.2, 0, 0},
                {-5,  4, 0},
                {3.2, 2, 1}
        };

        matrice.initialiser((double *) valeursMatrice2);
        solutionVecteur = solve_triang_inf(matrice, vecteur);

        REQUIRE(comparerValeurs(solutionVecteur(0), 0.16129));
        REQUIRE(comparerValeurs(solutionVecteur(1), 0.701613));
        REQUIRE(comparerValeurs(solutionVecteur(2), 1.08065));
    }

    SECTION("testSolveursDirectsSuperieur ") {

        Matrice matrice(3);
        Vecteur vecteur(3);

        vecteur(0) = 3;
        vecteur(1) = 2;
        vecteur(2) = 4;

        matrice(0, 0) = -2.9;
        matrice(1, 1) = 5.3;
        matrice(2, 2) = 2.1;

        Vecteur solutionVecteur = solve_triang_sup(matrice, vecteur);
        REQUIRE(solutionVecteur(0) == 3.0 / -2.9);
        REQUIRE(solutionVecteur(1) == 2.0 / 5.3);
        REQUIRE(solutionVecteur(2) == 4.0 / 2.1);

        // ========================================================

        vecteur(0) = 3;
        vecteur(1) = 2;
        vecteur(2) = 1;

        double valeursMatrice[3][3] = {
                {1, 2, 3},
                {0, 4, 5},
                {0, 0, 6}
        };

        matrice.initialiser((double *) valeursMatrice);
        solutionVecteur = solve_triang_sup(matrice, vecteur);

        REQUIRE(solutionVecteur(2) == 1.0 / 6.0);
        REQUIRE(comparerValeurs(solutionVecteur(1), (2.0 - (5.0 * 1.0 / 6.0)) / 4.0));

        // ========================================================

        vecteur(0) = 8;
        vecteur(1) = 6;
        vecteur(2) = 9;

        double valeursMatrice2[3][3] = {
                {2, 7.4, -5.21},
                {0, 1.4, 8},
                {0, 0,   -3.22}
        };

        matrice.initialiser((double *) valeursMatrice2);
        solutionVecteur = solve_triang_sup(matrice, vecteur);

        REQUIRE(comparerValeurs(solutionVecteur(0), -78.2331));
        REQUIRE(comparerValeurs(solutionVecteur(1), 20.2573));
        REQUIRE(comparerValeurs(solutionVecteur(2), -2.79503));
    }

    SECTION("testSolveursDirectsId") {

        Matrice matrice(3);
        Vecteur vecteur(3);

        vecteur(0) = 2.3;
        vecteur(1) = -4.4;
        vecteur(2) = 123;

        double valeursMatrice1[3][3] = {
                {1,    0,   0},
                {8.43, 1,   0},
                {-5.4, 3.1, 1}
        };

        matrice.initialiser((double *) valeursMatrice1);
        Vecteur solutionVecteur = solve_triang_inf_id(matrice, vecteur);

        REQUIRE(comparerValeurs(solutionVecteur(0), 2.3));
        REQUIRE(comparerValeurs(solutionVecteur(1), -23.789));
        REQUIRE(comparerValeurs(solutionVecteur(2), 209.166));

        // ========================================================

        vecteur(0) = 0.999;
        vecteur(1) = -0.999;
        vecteur(2) = 54345.333;

        double valeursMatrice2[3][3] = {
                {1, 21.776, -0.006},
                {0, 1,      0.00123},
                {0, 0,      1}
        };

        matrice.initialiser((double *) valeursMatrice2);
        solutionVecteur = solve_triang_sup_id(matrice, vecteur);

        REQUIRE(comparerValeurs(solutionVecteur(0), 1804.44));
        REQUIRE(comparerValeurs(solutionVecteur(1), -67.8438));
        REQUIRE(comparerValeurs(solutionVecteur(2), 54345.333));
    }
}
