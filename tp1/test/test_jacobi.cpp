#include <outils/catch.hpp>
#include <jacobi.hpp>
#include <matrice.hpp>
#include <vecteur.hpp>

using namespace std;

TEST_CASE("solution par algorithme de jacobi", "[jacobi]") {

    SECTION("tester jacobi avec la matrice du TP") {

        Matrice A = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        Vecteur b = {1, 1, 1, 1, 1};

        Jacobi jacobi = Jacobi(A, b);
        Vecteur x = jacobi.solve();

        // ===================================

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};

        Vecteur erreur = solution - x;
        REQUIRE((erreur.norme() < 0.001));
    }

    SECTION("tester jacobi avec une matrice et seconde membre aléatoire") {

        // TODO - trouver un moyen de generer des matrices bien conditionée
        Matrice A = Matrice::genererMatriceSPDAleatoire(4);
        Vecteur b = Vecteur::genererVecteurAleatoire(4);

        // ===================================

        Jacobi jacobi = Jacobi(A, b);
        Vecteur x = jacobi.solve();

        // ===================================

        Vecteur bCalcul = A * x;

        // cout << b << endl;
        // cout << bCalcul << endl;

        Vecteur erreur = bCalcul - b;
        // REQUIRE((erreur.norme() < 0.001));
    }
}
