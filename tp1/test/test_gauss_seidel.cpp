#include <outils/catch.hpp>
#include <gauss_seidel.hpp>
#include <matrice.hpp>
#include <vecteur.hpp>

using namespace std;

TEST_CASE("solution par algorithme de gauss-seidel", "[gauss_seidel]") {

    SECTION("tester gauss-seidel avec la matrice du TP") {

        Matrice A = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        Vecteur b = {1, 1, 1, 1, 1};

        GaussSeidel gaussSeidel = GaussSeidel(A, b);
        Vecteur x = gaussSeidel.solve();

        // ===================================

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};

        Vecteur erreur = solution - x;
        REQUIRE((erreur.norme() < 0.001));
    }
}
