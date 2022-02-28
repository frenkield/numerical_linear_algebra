#include <outils/catch.hpp>
#include <gradient_conjugue_preconditionne.hpp>
#include <vecteur.hpp>
#include <matrice_laplacienne.hpp>

using namespace std;

TEST_CASE("solution par algorithme de gradient conjugué preconditionné", "[gradient_conjugue_preconditionne]") {

    SECTION("tester gradient conjugué preconditionne avec la matrice laplacienne") {

        MatriceLaplacienne A = MatriceLaplacienne(5);
        Vecteur b = Vecteur(5, 1);

        GradientConjuguePreconditionne gradientConjuguePreconditionne = GradientConjuguePreconditionne(A, b);

        gradientConjuguePreconditionne.setTolerance(0.0001);

        Vecteur x = gradientConjuguePreconditionne.solveAvecTiming();

        // ===================================

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};

        Vecteur erreur = solution - x;
        REQUIRE((erreur.norme() < 0.001));
    }
}
