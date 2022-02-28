#include <dense_matrix.hpp>
#include <cassert>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <block_matrix.hpp>
#include <outils/logger.hpp>
#include <gradient_conjugue.hpp>

using namespace std;

const static double MAX_ERROR = 0.000001;

DenseMatrix::DenseMatrix(int nr, int nc) {
    this->nr = nr;
    this->nc = nc;
    val.resize(nr * nc, 0);
}

DenseMatrix::DenseMatrix(const DenseMatrix& matrix) : DenseMatrix(matrix.getHeight(), matrix.getWidth()) {
    val = matrix.val;
}

DenseMatrix::DenseMatrix(const initializer_list<initializer_list<double>> values) {
    
    nr = values.size();
    nc = 0;
    int index = 0;

    for (auto &line : values) {
        
        if (nc == 0) {
            nc = line.size();
            val.resize(nr * nc, 0);
        }

        assert(line.size() == nc);
        
        for (double value : line) {
            val[index++] = value;
        }
    }
}

int DenseMatrix::getHeight() const {
    return nr;
}

int DenseMatrix::getWidth() const {
    return nc;
}

void DenseMatrix::resize(int nr, int nc) {
    this->nr = nr;
    this->nc = nc;
    val.resize(nr * nc, 0);
}

int DenseMatrix::computeIndex(int i, int j) const {
    int index = i * nc + j;
    assert(index >= 0 && (unsigned)index < val.size());
    return index;
}

void DenseMatrix::operator=(const DenseMatrix& matrix) {
    nr = matrix.nr;
    nc = matrix.nc;
    val = matrix.val;
}

bool DenseMatrix::operator==(const DenseMatrix& matrix) const {

    return std::equal(val.begin(), val.end(), matrix.val.begin(),
            [](double value1, double value2) {

        if (value2 == 0) {
            return value1 < MAX_ERROR;
        } else {
            return fabs((value1 - value2) / value1) < MAX_ERROR;
        }
    });
}

bool DenseMatrix::operator==(const DenseMatrix&& matrix) const {
    return operator==(matrix);
}

double &DenseMatrix::operator()(int i, int j) {
    return val[computeIndex(i, j)];
}

double DenseMatrix::operator()(int i, int j) const {
    return val[computeIndex(i, j)];
}

void DenseMatrix::set(int i, int j, double valeur) {
    operator()(i, j) = valeur;
}

DenseMatrix DenseMatrix::operator+(DenseMatrix& matrix) {

    assert(nr == matrix.getHeight() && nc == matrix.getWidth());
    DenseMatrix sum = DenseMatrix(nr, nc);

    for(unsigned i = 0; i < matrix.val.size(); i++) {
        sum.val[i] = val[i] + matrix.val[i];
    }

    return sum;
}

DenseMatrix DenseMatrix::operator-(DenseMatrix& matrix) {

    assert(nr == matrix.getHeight() && nc == matrix.getWidth());
    DenseMatrix difference = DenseMatrix(nr, nc);

    for(unsigned i = 0; i < matrix.val.size(); i++) {
        difference.val[i] = val[i] - matrix.val[i];
    }

    return difference;
}

DenseMatrix DenseMatrix::operator*(DenseMatrix& matrix) {

    assert(nc == matrix.getHeight());
    DenseMatrix product = DenseMatrix(nr, matrix.getWidth());

    for(int i = 0; i < product.getHeight(); i++) {

        for (int j = 0; j < product.getWidth(); j++) {

            for (int index = 0; index < nc; index++) {
                product(i, j) += this->operator()(i, index) * matrix(index, j);
            }
        }
    }

    return product;
}

DenseMatrix DenseMatrix::operator*(DenseMatrix&& matrix) {
    return operator*(matrix);
}

DenseMatrix DenseMatrix::operator*(double alpha) {

    DenseMatrix product = DenseMatrix(nr, nc);

    for(unsigned i = 0; i < product.val.size(); i++) {
        product.val[i] = val[i] * alpha;
    }

    return product;
}

vector<double> operator*(const DenseMatrix& matrix, const vector<double>& vect) {

    assert(matrix.getWidth() == vect.size());

    vector<double> result = vector<double>(matrix.getHeight());

    for(int j = 0; j < matrix.getHeight(); j++) {
        for (int k = 0; k < matrix.getWidth(); k++) {
            result[j] += matrix(j, k) * vect[k];
        }
    }

    return result;
}

Vecteur operator*(const DenseMatrix& matrix, const Vecteur& vecteur) {

    assert(matrix.getWidth() == vecteur.size());
    Vecteur resultatVecteur = Vecteur(vecteur.size());

    for(int j = 0; j < matrix.getHeight(); j++) {
        for (int k = 0; k < matrix.getWidth(); k++) {
            resultatVecteur(j) += matrix(j, k) * vecteur(k);
        }
    }

    return resultatVecteur;
}

ostream& operator<<(ostream& stream, DenseMatrix const& matrix) {

    for(int i = 0; i < matrix.getHeight(); i++) {
        for (int j = 0; j < matrix.getWidth(); j++) {
            stream << setw(10) << matrix(i, j) << " ";
        }
        stream << endl;
    }

    return stream;
}

DenseMatrix DenseMatrix::getDecompositionLower() {

    assert(!decomposed);
    DenseMatrix lower = DenseMatrix(*this);

    for(int i = 0; i < nr; i++) {

        lower(i, i) = 1;

        for(int j = i + 1; j < nr; j++) {
            lower(i, j) = 0;
        }
    }

    return lower;
}

DenseMatrix DenseMatrix::getDecompositionUpper() {

    assert(!decomposed);
    DenseMatrix upper = DenseMatrix(*this);

    for(int i = 0; i < nr; i++) {
        for(int j = 0; j < i; j++) {
            upper(i, j) = 0;
        }
    }

    return upper;
}

DenseMatrix DenseMatrix::transpose() {

    DenseMatrix transpose = DenseMatrix(nc, nr);

    for (int row = 0; row < nc; ++row) {
        for (int column = 0; column < nr; ++column) {
            transpose(row, column) = (*this)(column, row);
        }
    }

    return transpose;
}

bool DenseMatrix::isSquare() {
    return nr == nc;
}

DenseMatrix DenseMatrix::getDiagonal() const {
    DenseMatrix diagonal = DenseMatrix(nr, nc);
    for (int i = 0; i < nr && i < nc; ++i) {
        diagonal(i, i) = operator()(i, i);
    }
    return diagonal;
}

DenseMatrix DenseMatrix::getDiagonalInverse() const {
    DenseMatrix diagonal = getDiagonal();
    for (int i = 0; i < nr && i < nc; ++i) {
        diagonal(i, i) = 1 / diagonal(i, i);
    }
    return diagonal;
}

void DenseMatrix::decomposeLU() {

    assert(!decomposed && isSquare());

    for(int i = 0; i < nr; i++) {

        for(int row = i + 1; row < nr; row++) {
            for(int column = i + 1; column < nc; column++) {

                (*this)(row, column) =
                    (*this)(row, column) - (*this)(row, i) * (*this)(i, column) / (*this)(i, i);
            }
        }

        for(int row = i + 1; row < nr; row++) {
            (*this)(row, i) = (*this)(row, i) / (*this)(i, i);
        }
    }

    decomposed = true;
}

void DenseMatrix::MvProd(const Vecteur& x, Vecteur& b) {
    assert(nc == x.size() && b.size() == nr);
    for(int j = 0; j < nr; j++) {
        for (int k = 0; k < nc; k++) {
            b(j) += operator()(j, k) * x(k);
        }
    }
}

void DenseMatrix::solveSuperior(Vecteur& x, const Vecteur& b) const {

    assert(decomposed);

    for(int j = nr - 1; j >= 0; j--) {

        double somme = 0;

        for(int k = nc - 1; k > j; k--) {
            somme += operator()(j, k) * x(k);
        }

        x(j) = (b(j) - somme) / operator()(j, j);
    }
}

Vecteur DenseMatrix::solveInferior(const Vecteur& b) const {

    assert(decomposed);

    Vecteur y = Vecteur(b.size());

    for(int j = 0; j < nr; j++) {

        double somme = 0;

        for(int k = 0; k < j; k++) {
            somme += operator()(j, k) * y(k);
        }

        y(j) = b(j) - somme;
    }

    return y;
}

void DenseMatrix::LUSolve(Vecteur& x, const Vecteur& b) {

    assert(isSquare());

    if (!decomposed) {
        decomposeLU();
    }

    Vecteur y = solveInferior(b);
    solveSuperior(x, y);

    x = x.getCoefficients();
}

void DenseMatrix::cg(vector<double> &x, const vector<double> &b, double tolerance) {

    Vecteur xv = Vecteur(x);
    Vecteur bv = Vecteur(b);

    cg(xv, bv, tolerance);
    x = xv.getCoefficients();
}

void DenseMatrix::cg(Vecteur &x, const Vecteur &b, double tolerance) {

    assert(isSquare() && !decomposed);

    GradientConjugue<DenseMatrix> gradientConjugue = GradientConjugue<DenseMatrix>();
    gradientConjugue.setTolerance(tolerance);
    gradientConjugue.cg(*this, x, b);

    historiqueResidu = gradientConjugue.getHistoriqueResidu();
}

void DenseMatrix::pcg(vector<double>& x, const vector<double>& b, double tolerance) {

    Vecteur xv = Vecteur(x);
    Vecteur bv = Vecteur(b);

    pcg(xv, bv, tolerance);
    x = xv.getCoefficients();
}

void DenseMatrix::pcg(Vecteur& x, const Vecteur& b, double tolerance) {

    // ces valeurs fonctionnent plutot bien...

    int l = nr / 2;
    int r = l - 1;
    pcg(x, b, tolerance, l, r);
}

void DenseMatrix::pcg(Vecteur& x, const Vecteur& b, double tolerance, int familleL, int familleR) {

    assert(isSquare() && !decomposed);

    GradientConjugue<DenseMatrix> gradientConjugue = GradientConjugue<DenseMatrix>();
    gradientConjugue.setTolerance(tolerance);
    gradientConjugue.pcg(*this, x, b, familleL, familleR);

    historiqueResidu = gradientConjugue.getHistoriqueResidu();
}

DenseMatrix DenseMatrix::operator()(vector<int> Ir, vector<int> Ic) {

    DenseMatrix extractedMatrix = DenseMatrix(Ir.size(), Ic.size());

    for (int rowIndex = 0; rowIndex < Ir.size(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < Ic.size(); columnIndex++) {
            extractedMatrix(rowIndex, columnIndex) = operator()(Ir[rowIndex], Ic[columnIndex]);
        }
    }

    return extractedMatrix;
}

double DenseMatrix::normeVecteurCarre(Vecteur& x) {
    return ((*this) * x) * x;
}

vector<pair<int, double>> DenseMatrix::getHistoriqueResidu() {
    return historiqueResidu;
}

void DenseMatrix::solveDefaut(Vecteur &x, const Vecteur &b) {
    LUSolve(x, b);
}
