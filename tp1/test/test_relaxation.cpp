#include <outils/catch.hpp>
#include <relaxation.hpp>
#include <vecteur.hpp>
#include <matrice_laplacienne.hpp>

using namespace std;

TEST_CASE("solution par algorithme de relaxation", "[relaxation]") {

    SECTION("tester relaxation avec la matrice du TP") {

        MatriceLaplacienne A = MatriceLaplacienne(5);
        Vecteur b = {1, 1, 1, 1, 1};

        Relaxation relaxation = Relaxation(A, b);
        relaxation.setOmega(0.2);
        Vecteur x = relaxation.solve();

        // ===================================

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};

        Vecteur erreur = solution - x;
        REQUIRE((erreur.norme() < 0.001));
    }
}
