#include <outils/catch.hpp>
#include <ctime>
#include <matrice_laplacienne.hpp>
#include <gradient_conjugue.hpp>

using namespace std;

typedef vector<pair<int, double>>::iterator HistoristiqueResiduIterator;

TEST_CASE( "mesurer le temps cpu de la méthode gradient conjugué", "[temps_cpu_gradient_conjugue]" ) {

    clock_t start, end;
    double tolerance = 0.001;
    int maxIterations = 1000;

    for (int taille = 100; taille <= 1000; taille += 100) {

        MatriceLaplacienne A = MatriceLaplacienne(taille);
        Vecteur b = Vecteur(taille, 1);

        GradientConjugue gradientConjugue = GradientConjugue(A, b);
        gradientConjugue.setTolerance(tolerance);
        gradientConjugue.setMaxIterations(maxIterations);

        start = clock();
        gradientConjugue.solve();
        end = clock();
        double temps = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        double iterations = gradientConjugue.getIterations();

        cout << taille << ", " << iterations << ", " << temps << endl;
    }
}
