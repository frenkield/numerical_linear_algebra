#include <outils/catch.hpp>
#include <gradient_conjugue.hpp>
#include <vecteur.hpp>
#include <matrice_laplacienne.hpp>

using namespace std;

TEST_CASE("solution par algorithme de gradient conjugué", "[gradient_conjugue]") {

    SECTION("tester gradient conjugué avec la matrice laplacienne") {

        MatriceLaplacienne A = MatriceLaplacienne(5);
        Vecteur b = Vecteur(5, 1);

        GradientConjugue gradientConjugue = GradientConjugue(A, b);

        gradientConjugue.setTolerance(0.0001);

        Vecteur x = gradientConjugue.solveAvecTiming();

        // ===================================

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};

        Vecteur erreur = solution - x;
        REQUIRE((erreur.norme() < 0.001));
    }

    /*
    SECTION("tester performance du gradient conjugué avec la matrice laplacienne") {

        for (int taille = 100; taille <= 1000; taille += 100) {

            MatriceLaplacienne A = MatriceLaplacienne(taille);
            Vecteur b = Vecteur(taille, 1);

            GradientConjugue gradientConjugue = GradientConjugue(A, b);
            gradientConjugue.setTolerance(0.001);

            Vecteur x = gradientConjugue.solveAvecTiming();

            cout << gradientConjugue.getTempsEcoule();
        }
    }
    */
}
