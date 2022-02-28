#ifndef TP1_METHODE_ITERATIVE_H
#define TP1_METHODE_ITERATIVE_H

#include <vecteur.hpp>
#include <matrice.hpp>

class MethodeIterative {

private:
    vector<pair<int, double>> historiqueResidu;
    double tempsEcoule = 0;

protected:

    const Matrice& A;
    const Vecteur& b;

    double tolerance = 0.1;
    int maxIterations = 100000;
    int iterations = 0;

public:

    MethodeIterative(const Matrice& A, const Vecteur& b);

    void setTolerance(const double& tolerance);
    int getIterations();

    void setMaxIterations(const double& maxIterations);

    void initialiseHistoriqueResidu();
    void ajouteHistoriqueResidu(int iterations, double residu);
    vector<pair<int, double>> getHistoriqueResidu();

    virtual Vecteur solve() = 0;

    Vecteur solveAvecTiming();
    double getTempsEcoule();
};

#endif // TP1_METHODE_ITERATIVE_H
