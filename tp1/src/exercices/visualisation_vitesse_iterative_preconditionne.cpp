#include <outils/catch.hpp>
#include <ctime>
#include <matrice_spd_simple.hpp>
#include <jacobi.hpp>
#include <gauss_seidel.hpp>
#include <relaxation.hpp>
#include <gradient_conjugue.hpp>
#include <gradient_conjugue_preconditionne.hpp>

using namespace std;

typedef vector<pair<int, double>>::iterator HistoristiqueResiduIterator;

TEST_CASE("generer données pour la visualisation des vitesses des méthodes iteratives préconditionnés",
          "[visualisation_vitesse_iterative_preconditionne]") {

    int taille = 1000;
    double tolerance = 0.0001;
    int maxIterations = 1000;

    MatriceSPDSimple H = MatriceSPDSimple(taille);
    Matrice PInverse = H.getDiagonalInverse();
    Matrice HPre = PInverse * H;

    Vecteur b = Vecteur(taille, 1);
    Vecteur bPre = PInverse * b;

//    SECTION("jacobi") {

        cout << "jacobi" << endl;

        Jacobi jacobi = Jacobi(H, b);
        jacobi.setTolerance(tolerance);
        jacobi.setMaxIterations(maxIterations);

        jacobi.solve();
        vector<pair<int, double>> residuJacobi = jacobi.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuJacobi.begin(); it != residuJacobi.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
//    }

//    SECTION("jacobi preconditionne") {

        cout << endl << "jacobi_preconditionne" << endl;

        Jacobi jacobiPre = Jacobi(HPre, bPre);
        jacobiPre.setTolerance(tolerance);
        jacobiPre.setMaxIterations(maxIterations);

        jacobiPre.solve();
        residuJacobi = jacobiPre.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuJacobi.begin(); it != residuJacobi.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
//   }

    // ========================================================================

//    SECTION("gauss seidel") {

        cout << endl << "gauss_seidel" << endl;

        GaussSeidel gaussSeidel = GaussSeidel(H, b);
        gaussSeidel.setTolerance(tolerance);
        gaussSeidel.setMaxIterations(maxIterations);

        gaussSeidel.solve();
        vector<pair<int, double>> residuGaussSeidel = gaussSeidel.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuGaussSeidel.begin(); it != residuGaussSeidel.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
//    }

//    SECTION("gauss seidel preconditionne") {

        cout << endl << "gauss_seidel_preconditionne" << endl;

        GaussSeidel gaussSeidelPre = GaussSeidel(HPre, bPre);
        gaussSeidelPre.setTolerance(tolerance);
        gaussSeidelPre.setMaxIterations(maxIterations);

        gaussSeidelPre.solve();
        residuGaussSeidel = gaussSeidelPre.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuGaussSeidel.begin(); it != residuGaussSeidel.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
//    }

    // ========================================================================

//    SECTION("relaxation") {

        cout << endl << "relaxation" << endl;

        Relaxation relaxation = Relaxation(H, b);
        relaxation.setTolerance(tolerance);
        //relaxation.setOmegaOptimal();
        relaxation.setMaxIterations(maxIterations);

        relaxation.solve();
        vector<pair<int, double>> residuRelaxation = relaxation.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuRelaxation.begin(); it != residuRelaxation.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
 //   }

 //   SECTION("relaxation preconditionne") {

        cout << endl << "relaxation_preconditionne" << endl;

        Relaxation relaxationPre = Relaxation(HPre, bPre);
        relaxationPre.setTolerance(tolerance);
        //relaxationPre.setOmegaOptimal();
        relaxationPre.setMaxIterations(maxIterations);

        relaxationPre.solve();
        residuRelaxation = relaxationPre.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuRelaxation.begin(); it != residuRelaxation.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
 //   }

    // ========================================================================

 //   SECTION("gradient conjugue") {

        cout << endl << "gradient_conjugue" << endl;

        GradientConjugue gradientConjugue = GradientConjugue(H, b);
        gradientConjugue.setTolerance(tolerance);
        gradientConjugue.setMaxIterations(maxIterations);

        gradientConjugue.solve();
        vector<pair<int, double>> residuGradientConjugue = gradientConjugue.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuGradientConjugue.begin(); it != residuGradientConjugue.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
 //   }

 //   SECTION("gradient conjugue preconditionne") {

        cout << endl << "gradient_conjugue_preconditionne" << endl;

        GradientConjuguePreconditionne gradientConjuguePre = GradientConjuguePreconditionne(H, b);
        gradientConjuguePre.setTolerance(tolerance);
        gradientConjuguePre.setMaxIterations(maxIterations);

        gradientConjuguePre.solve();

        residuGradientConjugue = gradientConjuguePre.getHistoriqueResidu();

        for (HistoristiqueResiduIterator it = residuGradientConjugue.begin(); it != residuGradientConjugue.end(); ++it) {
            cout << (*it).first << ", " << (*it).second << endl;
        }
//    }
}
