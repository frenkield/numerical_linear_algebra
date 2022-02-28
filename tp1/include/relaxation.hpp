#ifndef TP1_RELAXATION_H
#define TP1_RELAXATION_H

#include <iostream>
#include <vector>
#include <vecteur.hpp>
#include <matrice.hpp>

class Relaxation {

private:

    // TODO - coooooooooooooooooooooooonst !!!!!!!!!!!
    Matrice& A;
    Vecteur& b;

    double tolerance = 0.0001;
    int maxIterations = 100000;
    int iterations = 0;
    double omega = 1;
    vector<pair<int, double>> historiqueResidu;

public:

    Relaxation(Matrice& A, Vecteur& b);
    ~Relaxation() = default;

    void setTolerance(const double& tolerance);
    int getIterations();
    void setMaxIterations(const double& maxIterations);

    void setOmega(const double& omega);
    void setOmegaOptimal();

    vector<pair<int, double>> getHistoriqueResidu();

    Vecteur solve();
};

#endif // TP1_RELAXATION_H
