#include <outils/catch.hpp>
#include <ctime>
#include <matrice_laplacienne.hpp>
#include <jacobi.hpp>
#include <gauss_seidel.hpp>
#include <relaxation.hpp>
#include <gradient_conjugue.hpp>

using namespace std;

typedef vector<pair<int, double>>::iterator HistoristiqueResiduIterator;

TEST_CASE( "generer données pour la visualisation des vitesses des methodes iterative", "[visualisation_vitesse_iterative]" ) {

    // clock_t start, end;
    int taille = 1000;
    double tolerance = 0.1;
    int maxIterations = 1000;

    MatriceLaplacienne A = MatriceLaplacienne(taille);
    Vecteur b = Vecteur(taille, 1);

    // ========================================================================

    cout << "jacobi" << endl << endl;

    Jacobi jacobi = Jacobi(A, b);
    jacobi.setTolerance(tolerance);
    jacobi.setMaxIterations(maxIterations);

    // start = clock();
    Vecteur x = jacobi.solve();
    // end = clock();
    // double tempsJacobi = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    vector<pair<int, double>> residuJacobi = jacobi.getHistoriqueResidu();

    for (HistoristiqueResiduIterator it = residuJacobi.begin(); it != residuJacobi.end(); ++it) {
        cout << (*it).first << ", " << (*it).second << endl;
    }

    // ========================================================================

    cout << endl << "gauss_seidel" << endl << endl;

    GaussSeidel gaussSeidel = GaussSeidel(A, b);
    gaussSeidel.setTolerance(tolerance);
    gaussSeidel.setMaxIterations(maxIterations);

    // start = clock();
    x = gaussSeidel.solve();
    // end = clock();
    // double tempsGaussSeidel = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    vector<pair<int, double>> residuGaussSeidel = gaussSeidel.getHistoriqueResidu();

    for (HistoristiqueResiduIterator it = residuGaussSeidel.begin(); it != residuGaussSeidel.end(); ++it) {
        cout << (*it).first << ", " << (*it).second << endl;
    }

    // ========================================================================

    cout << endl << "relaxation" << endl << endl;

    Relaxation relaxation = Relaxation(A, b);
    relaxation.setTolerance(tolerance);
    relaxation.setOmegaOptimal();
    relaxation.setMaxIterations(maxIterations);

    // start = clock();
    x = relaxation.solve();
    // end = clock();
    // double tempsRelaxation = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    vector<pair<int, double>> residuRelaxation = relaxation.getHistoriqueResidu();

    for (HistoristiqueResiduIterator it = residuRelaxation.begin(); it != residuRelaxation.end(); ++it) {
        cout << (*it).first << ", " << (*it).second << endl;
    }

    // ========================================================================

    cout << endl << "gradient_conjugue" << endl << endl;

    GradientConjugue gradientConjugue = GradientConjugue(A, b);
    gradientConjugue.setTolerance(tolerance);
    gradientConjugue.setMaxIterations(maxIterations);

    x = gradientConjugue.solve();

    vector<pair<int, double>> residuGradientConjugue = gradientConjugue.getHistoriqueResidu();

    for (HistoristiqueResiduIterator it = residuGradientConjugue.begin(); it != residuGradientConjugue.end(); ++it) {
        cout << (*it).first << ", " << (*it).second << endl;
    }
}
