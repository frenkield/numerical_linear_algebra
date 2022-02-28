#include <iostream>
#include <cassert>
#include <cmath>
#include <gradient_conjugue_preconditionne.hpp>
#include <vecteur.hpp>
#include <matrice.hpp>

using namespace std;

Vecteur GradientConjuguePreconditionne::solve() {

    initialiseHistoriqueResidu();

    Vecteur x = Vecteur(b.size());
    Vecteur residu = b - (A * x);

    Matrice PInverse = A.getDiagonalInverse();
    Vecteur z = PInverse * residu;
    Vecteur p = z;

    double normeB = b.norme();
    double toleranceFoisNormeB = tolerance * normeB;
    double normeResidu = toleranceFoisNormeB + 1;

    while (++iterations <= maxIterations && normeResidu > toleranceFoisNormeB) {

        Vecteur dernierResidu = residu;
        Vecteur dernierZ = z;

        double alpha = (dernierResidu * z) / (p * (A * p));
        x = x + (alpha * p);
        residu = dernierResidu - (alpha * (A * p));
        z = PInverse * residu;
        double beta = (z * residu) / (dernierZ * dernierResidu);
        p = z + (beta * p);

        normeResidu = residu.norme();
        ajouteHistoriqueResidu(iterations, normeResidu);
    }

    // assert(iterations <= maxIterations);
    iterations--;

    return x;
}
