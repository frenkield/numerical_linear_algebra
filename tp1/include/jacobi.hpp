#ifndef TP1_JACOBI_H
#define TP1_JACOBI_H

#include <iostream>
#include <vecteur.hpp>
#include <matrice.hpp>

class Jacobi {

private:

    // TODO - coooooooooooooooooooooooonst !!!!!!!!!!!
    Matrice& A;
    Vecteur& b;

    double tolerance = 0.0001;
    int maxIterations = 100000;
    int iterations = 0;
    vector<pair<int, double>> historiqueResidu;

public:

    Jacobi(Matrice& A, Vecteur& b);
    ~Jacobi() = default;

    void setTolerance(const double& tolerance);
    int getIterations();
    void setMaxIterations(const double& maxIterations);

    vector<pair<int, double>> getHistoriqueResidu();

    Vecteur solve();
};

#endif // TP1_JACOBI_H
