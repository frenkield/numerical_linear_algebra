#include <methode_iterative.hpp>
#include <cassert>
#include <ctime>

using namespace std;

MethodeIterative::MethodeIterative(const Matrice& A, const Vecteur& b) : A(A), b(b) {
}

int MethodeIterative::getIterations() {
    return iterations;
}

void MethodeIterative::setTolerance(const double& tolerance) {
    this->tolerance = tolerance;
}

void MethodeIterative::setMaxIterations(const double& maxIterations) {
    this->maxIterations = maxIterations;
}

void MethodeIterative::initialiseHistoriqueResidu() {
    historiqueResidu.clear();
}

void MethodeIterative::ajouteHistoriqueResidu(int iterations, double residu) {
    historiqueResidu.push_back(pair<int, double>(iterations, residu));
}

vector<pair<int, double>> MethodeIterative::getHistoriqueResidu() {
    return historiqueResidu;
}

Vecteur MethodeIterative::solveAvecTiming() {
    clock_t debut = clock();
    Vecteur solution = solve();
    tempsEcoule = static_cast<double>(clock() - debut) / CLOCKS_PER_SEC;
    return solution;
}

double MethodeIterative::getTempsEcoule() {
    return tempsEcoule;
}
