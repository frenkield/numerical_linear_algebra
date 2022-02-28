#ifndef MATRICE_CSR_H
#define MATRICE_CSR_H

#include <triplet.hpp>
#include <vector>
#include <vecteur.hpp>
#include <matrice_coo.hpp>

class MatriceCSR {

private:
    int nr = 0;
    int nc = 0;
    std::vector<int> rowStartIndices;
    std::vector<int> columIndices;
    std::vector<double> values;
    int nombreValeurs;
    MatriceCOO matriceSource = MatriceCOO(1, 1);
    bool populated = false;

    std::vector<std::pair<int, double>> historiqueResidu;

public:

    MatriceCSR();
    MatriceCSR(int nr, int nc);
    MatriceCSR(const std::initializer_list<std::initializer_list<double>> values);

    void populate();
    void populate(MatriceCOO& matriceCoo);
    void populate(int nr, int nc, std::vector<Triplet>& triplets);
    int getHeight() const;
    int getWidth() const;
    bool isSquare();

    double operator()(int i, int j) const;
    void set(int i, int j, double valeur);

    friend std::ostream& operator<<(std::ostream& stream, MatriceCSR const& matrix);

    void MinRes(Vecteur& x, const Vecteur& b);
    void solveDefaut(Vecteur& x, const Vecteur& b);

    void cg(Vecteur& x, const Vecteur& b, double tolerance);
    void MvProd(const Vecteur& x, Vecteur& b);
    friend Vecteur operator*(MatriceCSR& matrice, const Vecteur& vecteur);

    void pcg(Vecteur &x, const Vecteur &b, double tolerance, int familleL, int familleR);
    void pcg(Vecteur &x, const Vecteur &b, double tolerance);

    double normeVecteurCarre(Vecteur& x);
    MatriceCSR operator()(std::vector<int> Ir, std::vector<int> Ic);

    MatriceCSR operator+(MatriceCSR& matrice);
    std::vector<std::pair<int, double>> getHistoriqueResidu();
};

#endif //MATRICE_CSR_H
