//#include <cmath>
//#include <outils/catch.hpp>
//#include <jacobi.hpp>
//#include <matrice_laplacienne.hpp>
//#include <vecteur.hpp>
//
//using namespace std;
//
//TEST_CASE("évaluation d'erreur de la methode jacobi", "[erreur_jacobi]") {
//
//    SECTION("erreur numérique jacobi avec la matrice de laplace") {
//
//        for (int n = 10; n <= 100; n += 10) {
//
//            MatriceLaplacienne A = MatriceLaplacienne(n);
//            Vecteur b = Vecteur(n, 1);
//
//            Jacobi jacobi = Jacobi(A, b);
//            jacobi.setTolerance(0.1);
//            Vecteur x = jacobi.solve();
//
//            int iterations = jacobi.getIterations();
//            cout << n << " - " << iterations << endl;
//        }
//    }
//
//    SECTION("erreur analytique de jacobi avec la matrice de laplace") {
//
//        cout << endl;
//        double tolerance = 0.1;
//
//        for (int n = 10; n <= 500; n += 10) {
//
//            double iterations = log(tolerance) / log(cos(M_PI / (n + 1)));
//            cout << n << " - " << iterations << endl;
//        }
//    }
//
//    SECTION("erreur développement limité de jacobi avec la matrice de laplace") {
//
//        cout << endl;
//        double tolerance = 0.1;
//
//        for (int n = 10; n <= 500; n += 10) {
//
//            double iterations = -2 * log(tolerance) / pow(M_PI, 2) * pow(n + 1, 2);
//
//            cout << n << " - " << iterations << endl;
//        }
//    }
//}
