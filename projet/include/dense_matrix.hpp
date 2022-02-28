#ifndef DENSE_MATRIX_H
#define DENSE_MATRIX_H

#include <iostream>
#include <vector>
#include <vecteur.hpp>

typedef std::vector<std::pair<int, double>> HistoristiqueResidu;
typedef HistoristiqueResidu::iterator HistoristiqueResiduIterator;

class DenseMatrix {

private:
    int nr;
    int nc;
    std::vector<double> val;

    // =========================================================================

    bool decomposed = false;
    int computeIndex(int i, int j) const;

    void decomposeLU();
    void solveSuperior(Vecteur& x, const Vecteur& b) const;
    Vecteur solveInferior(const Vecteur& b) const;

    std::vector<std::pair<int, double>> historiqueResidu;

public:

    DenseMatrix(int nr, int nc);
    DenseMatrix(const DenseMatrix &matrix);
    DenseMatrix(const std::initializer_list<std::initializer_list<double>> values);

    void MvProd(const Vecteur& x, Vecteur& b);
    void LUSolve(Vecteur& x, const Vecteur& b);

    void cg(std::vector<double> &x, const std::vector<double> &b, double tolerance);
    void cg(Vecteur &x, const Vecteur &b, double tolerance);

    void pcg(std::vector<double> &x, const std::vector<double> &b, double tolerance);
    void pcg(Vecteur &x, const Vecteur &b, double tolerance, int familleL, int familleR);
    void pcg(Vecteur &x, const Vecteur &b, double tolerance);

    // =========================================================================

    int getHeight() const;
    int getWidth() const;

    void resize(int nr, int nc);

    double& operator()(int i, int j);
    double operator()(int i, int j) const;
    void set(int i, int j, double valeur);

    void operator=(const DenseMatrix& matrix);
    bool operator==(const DenseMatrix& matrix) const;
    bool operator==(const DenseMatrix&& matrix) const;
    DenseMatrix operator+(DenseMatrix& matrix);
    DenseMatrix operator-(DenseMatrix& matrix);
    DenseMatrix operator*(DenseMatrix& matrix);
    DenseMatrix operator*(DenseMatrix&& matrix);
    DenseMatrix operator*(double alpha);

    DenseMatrix operator()(std::vector<int> Ir, std::vector<int> Ic);

    friend std::ostream& operator<<(std::ostream& stream, DenseMatrix const& matrix);

    friend Vecteur operator*(const DenseMatrix& matrix, const Vecteur& vecteur);

    friend std::vector<double> operator*(const DenseMatrix& matrix, const std::vector<double>& vector);

    DenseMatrix transpose();
    bool isSquare();

    DenseMatrix getDecompositionLower();
    DenseMatrix getDecompositionUpper();

    DenseMatrix getDiagonal() const;
    DenseMatrix getDiagonalInverse() const;

    double normeVecteurCarre(Vecteur& x);

    std::vector<std::pair<int, double>> getHistoriqueResidu();

    void solveDefaut(Vecteur& x, const Vecteur& b);
};

#endif // DENSE_MATRIX_H
