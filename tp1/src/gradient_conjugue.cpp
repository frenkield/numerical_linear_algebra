#include <iostream>
#include <cassert>
#include <cmath>
#include <gradient_conjugue.hpp>
#include <vecteur.hpp>
#include <matrice.hpp>

using namespace std;

Vecteur GradientConjugue::solve() {

    initialiseHistoriqueResidu();

    Vecteur x = Vecteur(b.size());
    Vecteur residu = b - (A * x);

    Vecteur p = residu;

    double normeB = b.norme();
    double toleranceFoisNormeB = tolerance * normeB;
    double normeResidu = toleranceFoisNormeB + 1;

    while (++iterations <= maxIterations && normeResidu > toleranceFoisNormeB) {

        Vecteur dernierResidu = residu;
        double alpha = (dernierResidu * dernierResidu) / (p * (A * p));
        x = x + (alpha * p);
        residu = dernierResidu - (alpha * (A * p));
        double beta = (residu * residu) / (dernierResidu * dernierResidu);
        p = residu + (beta * p);

        normeResidu = residu.norme();
        ajouteHistoriqueResidu(iterations, normeResidu);
    }

    // assert(iterations <= maxIterations);
    iterations--;

    return x;
}
