#ifndef TP1_VECTEUR_H
#define TP1_VECTEUR_H

#include <vector>
#include <iostream>

class Vecteur {

private:
    std::vector<double> coefficients;

public:
    Vecteur();

    Vecteur(int taille);
    Vecteur(int taille, const double& valeurInitiale);
    Vecteur(const Vecteur &vecteur);
    Vecteur(std::initializer_list<double> valeurs);
    ~Vecteur() = default;

    int size() const;
    void initialiser(double* valeurs);

    void operator=(int a[]);

    bool operator==(const Vecteur& vecteur);
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
    friend std::ostream& operator<<(std::ostream& stream, Vecteur const& vecteur);

    static Vecteur genererVecteurAleatoire(int taille);
};

#endif //TP1_VECTEUR_H
