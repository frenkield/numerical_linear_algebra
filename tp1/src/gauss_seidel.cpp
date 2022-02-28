#include <gauss_seidel.hpp>
#include <cassert>
#include <solveurs_directs.hpp>

using namespace std;

GaussSeidel::GaussSeidel(Matrice& A, Vecteur& b) : A(A), b(b) {
}

Vecteur GaussSeidel::solve() {

    Matrice M = A;

    for (int i = 0; i < M.size(); i++) {
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

int GaussSeidel::getIterations() {
    return iterations;
}

void GaussSeidel::setMaxIterations(const double& maxIterations) {
    this->maxIterations = maxIterations;
}

void GaussSeidel::setTolerance(const double& tolerance) {
    this->tolerance = tolerance;
}

vector<pair<int, double>> GaussSeidel::getHistoriqueResidu() {
    return historiqueResidu;
}
