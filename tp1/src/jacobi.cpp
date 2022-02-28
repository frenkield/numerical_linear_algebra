#include <jacobi.hpp>
#include <cassert>

using namespace std;

Jacobi::Jacobi(Matrice& A, Vecteur& b) : A(A), b(b) {
}

Vecteur Jacobi::solve() {

    double normeB = b.norme();
    Vecteur x = Vecteur(b.size());

    iterations = 0;
    Vecteur direction = Vecteur(b.size());
    Vecteur residu = b;

    double normeRSurB = tolerance + 1;

    while (++iterations <= maxIterations && normeRSurB > tolerance) {

        for (int i = 0; i < b.size(); i++) {
            direction(i) = (1 / A(i, i)) * residu(i);
            x(i) += direction(i);
        }

        Vecteur tempVecteur = A * x;

        residu = b - tempVecteur;
        normeRSurB = residu.norme() / normeB;
        historiqueResidu.push_back(pair<int, double>(iterations, normeRSurB));
    }

    // assert(iterations <= maxIterations);
    iterations--;

    return x;
}

void Jacobi::setMaxIterations(const double& maxIterations) {
    this->maxIterations = maxIterations;
}

int Jacobi::getIterations() {
    return iterations;
}

void Jacobi::setTolerance(const double& tolerance) {
    this->tolerance = tolerance;
}

vector<pair<int, double>> Jacobi::getHistoriqueResidu() {
    return historiqueResidu;
}

