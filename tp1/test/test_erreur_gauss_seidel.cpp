#include <cmath>
#include <outils/catch.hpp>
#include <gauss_seidel.hpp>
#include <matrice_laplacienne.hpp>
#include <vecteur.hpp>

using namespace std;

TEST_CASE("évaluation d'erreur de la methode gauss-seidel", "[erreur_gauss_seidel]") {


    SECTION("erreur numérique gauss-seidel avec la matrice de laplace") {

        // TODO - mets tout ça sous exercices

//        for (int n = 10; n <= 100; n += 10) {
//
//            MatriceLaplacienne A = MatriceLaplacienne(n);
//            Vecteur b = Vecteur(n, 1);
//
//            GaussSeidel gaussSeidel = GaussSeidel(A, b);
//            gaussSeidel.setTolerance(0.1);
//            Vecteur x = gaussSeidel.solve();
//
//            int iterations = gaussSeidel.getIterations();
//            cout << n << " - " << iterations << endl;
//        }
//    }
//
//    SECTION("erreur analytique de gauss-seidel avec la matrice de laplace") {
//
//        cout << endl;
//        double tolerance = 0.1;
//
//        for (int n = 10; n <= 100; n += 10) {
//
//            double iterations = log(tolerance) / log(cos(M_PI / (n + 1)));
//            iterations /= 2;
//            cout << n << " - " << iterations << endl;
//        }
//    }
//
//    SECTION("erreur développement limité de gauss-seidel avec la matrice de laplace") {
//
//        cout << endl;
//        double tolerance = 0.1;
//
//        for (int n = 10; n <= 100; n += 10) {
//
//            double iterations = -2 * log(tolerance) / pow(M_PI, 2) * pow(n + 1, 2);
//            iterations /= 2;
//
//            cout << n << " - " << iterations << endl;
//        }
    }
}
