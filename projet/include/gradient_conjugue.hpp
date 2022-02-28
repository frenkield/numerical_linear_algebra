#ifndef GRADIENT_CONJUGUE_H
#define GRADIENT_CONJUGUE_H

#include <vecteur.hpp>

template <typename M>
class GradientConjugue {

private:
    std::vector<std::pair<int, double>> historiqueResidu;
    double tempsEcoule = 0;

protected:

    double tolerance = 0.0001;
    int maxIterations = 1000;
    int iterations = 0;

public:

    void setTolerance(const double& tolerance);
    int getIterations();

    void setMaxIterations(const double& maxIterations);

    void initialiseHistoriqueResidu();
    void ajouteHistoriqueResidu(int iterations, double residu);
    std::vector<std::pair<int, double>> getHistoriqueResidu();

    void cg(M matrice, Vecteur &x, const Vecteur &b);
    void pcg(M matrice, Vecteur &x, const Vecteur &b, int familleL, int familleR);

    double getTempsEcoule();
};

#endif // GRADIENT_CONJUGUE_H
