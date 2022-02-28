//#include <cmath>
//#include <outils/catch.hpp>
//#include <relaxation.hpp>
//#include <matrice_laplacienne.hpp>
//#include <vecteur.hpp>
//
//using namespace std;
//
//TEST_CASE("évaluation d'erreur de la méthode relaxation", "[erreur_relaxation]") {
//
//    SECTION("erreur numérique relaxation avec la matrice de laplace") {
//
//        for (int n = 10; n <= 100; n += 10) {
//
//            MatriceLaplacienne A = MatriceLaplacienne(n);
//            Vecteur b = Vecteur(n, 1);
//
//            Relaxation relaxation = Relaxation(A, b);
//            relaxation.setTolerance(0.1);
//
//            double rayonSpectrale = pow(cos(M_PI / (n + 1)), 2);
//            double omega = 2 / (1 + sqrt(1 - rayonSpectrale));
//            // cout << "omega = " << omega << endl;
//            relaxation.setOmega(omega);
//
//            Vecteur x = relaxation.solve();
//
//            int iterations = relaxation.getIterations();
//            cout << n << " - " << iterations << endl;
//        }
//    }
//
///*
//    SECTION("erreur analytique de relaxation avec la matrice de laplace") {
//
//     //   cout << endl;
//        double tolerance = 0.1;
//
//        for (int n = 10; n <= 100; n += 10) {
//
//            double iterations = log(tolerance) / log(cos(M_PI / (n + 1)));
//         //   cout << n << " - " << iterations << endl;
//        }
//    }
//*/
//
//    SECTION("erreur développement limité de relaxation avec la matrice de laplace") {
//
//        cout << endl;
//        double tolerance = 0.1;
//
//        for (int n = 10; n <= 100; n += 10) {
//
//            double iterations = -log(tolerance) / pow(M_PI, 2) * (n + 1);
//
//            cout << n << " - " << iterations << endl;
//        }
//    }
//}
