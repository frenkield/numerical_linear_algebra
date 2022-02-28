#ifndef TP1_MATRICE_H
#define TP1_MATRICE_H

#include <iostream>
#include <vector>
#include <vecteur.hpp>

using namespace std;

enum TypeDecomposition {
    PasDecompose, LU, Cholesky
};

class Matrice {

private:
    int taille;
    std::vector<double> coefficients;
    TypeDecomposition typeDecomposition = PasDecompose;
    int calculIndex(int i, int j) const;

public:

    Matrice(int taille);
    Matrice(const Matrice &matrice);
    Matrice(initializer_list<initializer_list<double>> valeurs);
    ~Matrice() = default;

    int size() const;

    double & operator()(int i, int j);
    double operator()(int i, int j) const;

    bool operator==(Matrice& matrice);
    Matrice operator+(Matrice& matrice);
    Matrice operator-(Matrice& matrice);
    Matrice operator*(Matrice& matrice);
    Matrice operator*(double alpha);

    void initialiser(double* valeurs);

    friend Vecteur operator*(const Matrice& matrice, const Vecteur& vecteur);
    friend std::ostream& operator<<(std::ostream& stream, Matrice const& matrice);

    Matrice transpose();

    void decomposeLU();
    void decomposeCholesky();

    Matrice getDecompositionLower();
    Matrice getDecompositionUpper();

    Matrice getDiagonal() const;
    Matrice getDiagonalInverse() const;

    static Matrice genererMatriceAleatoire(int taille);
    static Matrice genererMatriceSPDAleatoire(int taille);
    static Matrice genererMatriceInferieureAleatoire(int taille);
    static Matrice genererMatriceSuperieureAleatoire(int taille);

};

#endif //TP1_MATRICE_H
