#ifndef TP1_GAUSS_SEIDEL_H
#define TP1_GAUSS_SEIDEL_H

#include <iostream>
#include <vecteur.hpp>
#include <matrice.hpp>

class GaussSeidel {

private:

    // TODO - coooooooooooooooooooooooonst !!!!!!!!!!!
    Matrice& A;
    Vecteur& b;

    double tolerance = 0.0001;
    int maxIterations = 100000;
    int iterations = 0;
    vector<pair<int, double>> historiqueResidu;

public:

    GaussSeidel(Matrice& A, Vecteur& b);
    ~GaussSeidel() = default;

    void setTolerance(const double& tolerance);
    int getIterations();
    void setMaxIterations(const double& maxIterations);

    vector<pair<int, double>> getHistoriqueResidu();

    Vecteur solve();
};

#endif // TP1_GAUSS_SEIDEL_H
