#include <relaxation.hpp>
#include <cassert>
#include <cmath>
#include <solveurs_directs.hpp>

using namespace std;

Relaxation::Relaxation(Matrice& A, Vecteur& b) : A(A), b(b) {
}

Vecteur Relaxation::solve() {

    historiqueResidu.clear();
    Matrice M = A;

    for (int i = 0; i < M.size(); i++) {
        M(i, i) = M(i, i) / omega;
        for (int j = i + 1; j < M.size(); j++) {
            M(i, j) = 0;
        }
    }

    double normeB = b.norme();
    Vecteur x = Vecteur(b.size());

    iterations = 0;
    Vecteur residu = b;

    double normeRSurB = tolerance + 1;

    while (++iterations <= maxIterations && normeRSurB > tolerance) {

        Vecteur direction = solve_triang_inf(M, residu);
        x = x + direction;

        Vecteur tempVecteur = A * x;

        residu = b - tempVecteur;
        normeRSurB = residu.norme() / normeB;
        historiqueResidu.push_back(pair<int, double>(iterations, normeRSurB));
    }

    // assert(iterations <= maxIterations);
    iterations--;

    return x;
}

int Relaxation::getIterations() {
    return iterations;
}

void Relaxation::setMaxIterations(const double& maxIterations) {
    this->maxIterations = maxIterations;
}

void Relaxation::setTolerance(const double& tolerance) {
    this->tolerance = tolerance;
}

void Relaxation::setOmega(const double& omega) {
    this->omega = omega;
}

void Relaxation::setOmegaOptimal() {
    double rayonSpectrale = pow(cos(M_PI / (A.size() + 1)), 2);
    setOmega(2 / (1 + sqrt(1 - rayonSpectrale)));
}

vector<pair<int, double>> Relaxation::getHistoriqueResidu() {
    return historiqueResidu;
}
