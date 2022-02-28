#include <block.hpp>
#include <cassert>
#include <outils/logger.hpp>
#include <dense_matrix.hpp>
#include <matrice_csr.hpp>

using namespace std;

template <typename M>
Block<M>::Block(int nr, int nc, const vector<int>& Ir, const vector<int>& Ic) : mat(M(Ir.size(), Ic.size())) {

    // left (I)
    this->nr = nr;

    // right (J)
    this->nc = nc;

    // I ou rowVector
    this->Ir = Ir;

    // J ou columnVector®
    this->Ic = Ic;
}

template <typename M>
Block<M>::Block(const Block& block) : Block(block.getHeight(), block.getWidth(), block.getLeftVector(),
                                         block.getRightVector()) {
    mat = block.mat;
}

template <typename M>
int Block<M>::getHeight() const {
    return nr;
}

template <typename M>
int Block<M>::getWidth() const {
    return nc;
}

template <typename M>
vector<int> Block<M>::getLeftVector() const {
    return Ir;
}

template <typename M>
vector<int> Block<M>::getRightVector() const {
    return Ic;
}

template <typename M>
void Block<M>::operator=(const Block& block) {
    nr = block.nr;
    nc = block.nc;
    Ir = block.Ir;
    Ic = block.Ic;
    mat = block.mat;
}

template <typename M>
void Block<M>::setCenterMatrix(const M &centerMatrix) {
    assert(centerMatrix.getHeight() == mat.getHeight() && centerMatrix.getWidth() == mat.getWidth());
    mat = centerMatrix;
}

template <typename M>
M Block<M>::getCenterMatrix() const {
    return mat;
}

template <typename M>
M Block<M>::getLeftMatrix() const {
    return generateRowMatrix(nr, Ir);
}

template <typename M>
M Block<M>::getRightMatrix() const {
    return generateRowMatrix(nc, Ic);
}

template <typename M>
M Block<M>::generateRowMatrix(int height, const vector<int>& rowVector) {

    M rowMatrix = M(height, rowVector.size());

    for (int k = 0; k < rowVector.size(); k++) {
        int j = rowVector[k];
        rowMatrix.set(j, k, 1);
    }

    return rowMatrix;
}

template <typename M>
M Block<M>::getMatrix() const {

    M matrix = M(nr, nc);

    for (int rowIndex = 0; rowIndex < Ir.size(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < Ic.size(); columnIndex++) {
            matrix.set(Ir[rowIndex], Ic[columnIndex], mat(rowIndex, columnIndex));
        }
    }

    return matrix;
}

// TODO - traiter correctement les matrices csr
template <typename M>
void Block<M>::MvProd(const Vecteur& x, Vecteur& b) {

    assert(nc == x.size() && nr == b.size());
    b.initialiser(0);

    for (int rowIndex = 0; rowIndex < Ir.size(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < Ic.size(); columnIndex++) {

            int row = Ir[rowIndex];
            int column = Ic[columnIndex];

            // c'est lent pour les matrices csr
            double matrixValue = mat(rowIndex, columnIndex);

            b(row) += matrixValue * x(column);
        }
    }
}

template <typename M>
void Block<M>::productLeftMatrix(const Vecteur& x, Vecteur& b) {

    assert(x.size() == Ir.size() && b.size() == nr);
    b.initialiser(0);

    for (int rowIndex = 0; rowIndex < Ir.size(); rowIndex++) {
        int row = Ir[rowIndex];
        b(row) = x(rowIndex);
    }
}

template <typename M>
void Block<M>::productRightMatrixTranspose(const Vecteur& x, Vecteur& b) {

    assert(x.size() == nc && b.size() == Ic.size());
    b.initialiser(0);

    for (int columnIndex = 0; columnIndex < Ic.size(); columnIndex++) {
        int column = Ic[columnIndex];
        b(columnIndex) = x(column);
    }
}

template <typename M>
void Block<M>::MvProdInv(const Vecteur& x, Vecteur& b) {

    assert(nc == x.size() && nr == b.size());
    b.initialiser(0);

    Vecteur y = Vecteur(Ic.size());
    productRightMatrixTranspose(x, y);

    Vecteur z = Vecteur(mat.getWidth());
    mat.solveDefaut(z, y);

    productLeftMatrix(z, b);
}

// TODO - trouves un moyen de stocker cette galere dans un autre fichier
template class Block<DenseMatrix>;
template class Block<MatriceCSR>;
