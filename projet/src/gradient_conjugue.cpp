#include <gradient_conjugue.hpp>
#include <cassert>
#include <ctime>
#include <block_matrix.hpp>
#include <dense_matrix.hpp>
#include <matrice_csr.hpp>
using namespace std;

template <typename M>
int GradientConjugue<M>::getIterations() {
    return iterations;
}

template <typename M>
void GradientConjugue<M>::setTolerance(const double& tolerance) {
    this->tolerance = tolerance;
}

template <typename M>
void GradientConjugue<M>::setMaxIterations(const double& maxIterations) {
    this->maxIterations = maxIterations;
}

template <typename M>
void GradientConjugue<M>::initialiseHistoriqueResidu() {
    historiqueResidu.clear();
}

template <typename M>
void GradientConjugue<M>::ajouteHistoriqueResidu(int iterations, double residu) {
    historiqueResidu.push_back(pair<int, double>(iterations, residu));
}

template <typename M>
vector<pair<int, double>> GradientConjugue<M>::getHistoriqueResidu() {
    return historiqueResidu;
}

template <typename M>
double GradientConjugue<M>::getTempsEcoule() {
    return tempsEcoule;
}

template<typename M>
void GradientConjugue<M>::cg(M matrice, Vecteur &x, const Vecteur &b) {

    initialiseHistoriqueResidu();

    Vecteur residu = b - (matrice * x);
    Vecteur p = residu;

    double normeB = b.norme();
    double toleranceFoisNormeB = tolerance * normeB;

    double normeResidu = toleranceFoisNormeB + 1;
    int iterations = 0;

    while (++iterations <= maxIterations && normeResidu > toleranceFoisNormeB) {

        Vecteur dernierResidu = residu;
        double alpha = (dernierResidu * dernierResidu) / (p * (matrice * p));
        x = x + (alpha * p);
        residu = dernierResidu - (alpha * (matrice * p));
        double beta = (residu * residu) / (dernierResidu * dernierResidu);
        p = residu + (beta * p);

        normeResidu = residu.norme();
        ajouteHistoriqueResidu(iterations, normeResidu);
    }
}

template<typename M>
void GradientConjugue<M>::pcg(M matrice, Vecteur &x, const Vecteur &b, int familleL, int familleR) {

    initialiseHistoriqueResidu();

    BlockMatrix<M> P = BlockMatrix<M>(matrice.getHeight(), matrice.getWidth());
    P.Extract(matrice, familleL, familleR);

    // ======================================================

    // 1) e = e_tol * |b|
    double toleranceFoisNormeB = tolerance * b.norme();

    // 3) r = b
    Vecteur r = b;

    Vecteur z = Vecteur(b.size());

    // 4) z = P*r
    P.MvProdInv(r, z);

    // 5) p = z
    Vecteur p = z;

    double normeResidu = toleranceFoisNormeB + 1;
    int iterations = 0;

    while (++iterations <= maxIterations && normeResidu >= toleranceFoisNormeB) {

        // 6) gamma = r*z
        double gamma = r * z;

        // 7) alpha = gamma / norme carreé matrice p
        double alpha = gamma / matrice.normeVecteurCarre(p);

        // 8) x = x + alpha*p
        x = x + (alpha * p);

        // 9) r = r - alpha * A * p
        r = r - ((matrice * p) * alpha);

        // 10) z = P*r
        P.MvProdInv(r, z);

        // 11) beta = r * z / gamma
        double beta = (r * z) / gamma;

        // 12) p = z + beta * p
        p = z + (beta * p);

        normeResidu = r.norme();
        ajouteHistoriqueResidu(iterations, normeResidu);
    }
}

// TODO - trouves un moyen de stocker cette galere dans un autre fichier
template class GradientConjugue<DenseMatrix>;
template class GradientConjugue<MatriceCSR>;
