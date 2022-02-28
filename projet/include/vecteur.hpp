#ifndef VECTEUR_H
#define VECTEUR_H

#include <vector>
#include <iostream>

class Vecteur {

private:
    std::vector<double> coefficients;

public:

    Vecteur();
    Vecteur(int taille);
    Vecteur(const Vecteur &vecteur);
    Vecteur(std::initializer_list<double> valeurs);
    Vecteur(const std::vector<double>& coefficients);
    ~Vecteur() = default;

    void initialiser(double valeur);

    int size() const;
    std::vector<double> getCoefficients();

    bool operator==(const Vecteur& vecteur) const;
    bool operator==(const std::vector<double>& vect) const;
    double& operator()(int index);
    double operator()(int index) const;

    Vecteur operator+(const Vecteur& vecteur);
    Vecteur operator+(const Vecteur&& vecteur);
    Vecteur operator-(const Vecteur& vecteur) const;
    Vecteur operator-(const Vecteur&& vecteur) const;

    friend double operator*(const Vecteur& vecteur1, const Vecteur& vecteur2);
    friend double operator*(const Vecteur& vecteur1, const Vecteur&& vecteur2);

    friend Vecteur operator*(const double alpha, const Vecteur& vecteur);
    friend Vecteur operator*(const Vecteur& vecteur, const double alpha);
    friend Vecteur operator*(const double alpha, const Vecteur&& vecteur);
    friend Vecteur operator*(const Vecteur&& vecteur, const double alpha);

    double norme() const;
    double normeCarre() const;
    friend std::ostream& operator<<(std::ostream& stream, Vecteur const& vecteur);

    static Vecteur genererVecteurAleatoire(int taille);
};

#endif // VECTEUR_H
