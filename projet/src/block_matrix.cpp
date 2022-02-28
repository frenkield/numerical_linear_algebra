#include <block_matrix.hpp>
#include <cassert>
#include <numeric>
#include <cmath>
#include <outils/logger.hpp>
#include <dense_matrix.hpp>
#include <matrice_csr.hpp>

using namespace std;

const int MINRES_MAX_ITERATIONS = 1000;
const double MINRES_TOLERANCE = 0.0001;

template <typename M>
BlockMatrix<M>::BlockMatrix(int nr, int nc) {
    this->nr = nr;
    this->nc = nc;
}

template <typename M>
BlockMatrix<M>::BlockMatrix(const BlockMatrix &blockMatrix) {
    nr = blockMatrix.nr;
    nc = blockMatrix.nc;
    val = blockMatrix.val;
}

template <typename M>
void BlockMatrix<M>::operator=(const BlockMatrix& blockMatrix) {
    nr = blockMatrix.nr;
    nc = blockMatrix.nc;
    val = blockMatrix.val;
}

template <typename M>
void BlockMatrix<M>::operator+=(const Block<M>& block) {
    assert(block.getHeight() == nr && block.getWidth() == nc);
    val.push_back(block);
}

template <typename M>
const list<Block<M>> BlockMatrix<M>::getBlocks() {
    return val;
}

template <typename M>
void BlockMatrix<M>::MvProd(const Vecteur& x, Vecteur& b) {

    assert(x.size() == nc && b.size() == nr);
    b.initialiser(0);

    Vecteur temp = b;

    for(typename list<Block<M>>::iterator block = val.begin(); block != val.end(); ++block) {

        (*block).MvProd(x, temp);

        for (int i = 0; i < b.size(); i++) {
            b(i) += temp(i);
        }
    }
}

template <typename M>
void BlockMatrix<M>::MinRes(Vecteur& x, const Vecteur& b) {

    x.initialiser(0);

    double tolerance = MINRES_TOLERANCE * sqrt(b.norme());

    Vecteur r = b;
    Vecteur product = Vecteur(b.size());
    int iterations = 0;

    while(iterations++ < MINRES_MAX_ITERATIONS && sqrt(r.norme()) > tolerance) {
        MvProd(r, product);
        double alpha = (r * product) / (product * product);
        x = x + alpha * r;
        MvProd(x, product);
        r = b - product;
    }
}

template <typename M>
vector<vector<int>> BlockMatrix<M>::generateMatrixVectors(int l, int r, int n) {

    assert(r < l && r + l <= n && n >= 2 * l);
    vector<vector<int>> vectors = vector<vector<int>>();

    // =================================================

    vector<int> vector1 = vector<int>();
    int lPlusR = l + r;

    for (int i = 1; i <= lPlusR; i++) {
        // on commence a zéro !
        vector1.push_back(i - 1);
    }

    vectors.push_back(vector1);

    // =================================================

    int qStar = (n / l) - 1;

    for (int q = 2; q <= qStar; q++) {

        int start = (l * (q - 1)) - r;
        int end = (l * q) + r;

        vector<int> vectorQ = vector<int>();

        for (int i = start; i <= end; i++) {
            // on commence a zéro !
            vectorQ.push_back(i - 1);
        }

        vectors.push_back(vectorQ);
    }

    // =================================================

    vector<int> vectorQStar = vector<int>();
    int start = l * qStar;
    for (int i = start; i <= n; i++) {
        // on commence a zéro !
        vectorQStar.push_back(i - 1);
    }

    vectors.push_back(vectorQStar);

    // =================================================

    validateMatrixVectors(vectors, n);

    return vectors;
}

template <typename M>
void BlockMatrix<M>::validateMatrixVectors(vector<vector<int>> vectors, int n) {

    // confirmer que tous les entiers sont là

    vector<bool> validation = vector<bool>(n, false);

    for(vector<vector<int>>::iterator vecteur = vectors.begin(); vecteur != vectors.end(); ++vecteur) {

        int valeurPrecedent = -1;

        for(vector<int>::iterator valeur = (*vecteur).begin(); valeur != (*vecteur).end(); ++valeur) {
            assert(*valeur > valeurPrecedent);
            validation[*valeur] = true;
            valeurPrecedent = *valeur;
        }
    }

    for(vector<bool>::iterator it = validation.begin(); it != validation.end(); ++it) {
        assert(*it);
    }
}

template <typename M>
void BlockMatrix<M>::Extract(M &matrix, int l, int r) {

    assert(matrix.isSquare());
    int n = matrix.getWidth();

    const vector<vector<int>> vecteurs = generateMatrixVectors(l, r, n);
    Extract(matrix, vecteurs);
}

template <typename M>
void BlockMatrix<M>::Extract(M &matrix, const vector<vector<int>> I) {

    assert(matrix.isSquare());
    int n = matrix.getWidth();

    for(vector<vector<int>>::const_iterator vecteur = I.begin(); vecteur != I.end(); ++vecteur) {

        Block<M> block = Block<M>(n, n, *vecteur, *vecteur);
        M extractedMatrix = matrix(*vecteur, *vecteur);
        block.setCenterMatrix(extractedMatrix);
        val.push_back(block);
    }
}

template <typename M>
M BlockMatrix<M>::reconstructMatrix() {

    M matrix = M(nr, nc);

    for(typename list<Block<M>>::iterator block = val.begin(); block != val.end(); ++block) {
        M matrixFromBlock = (*block).getMatrix();
        matrix = matrix + matrixFromBlock;
    }

    return matrix;
}

template <typename M>
void BlockMatrix<M>::MvProdInv(const Vecteur& x, Vecteur& b) {

    assert(x.size() == nc && b.size() == nr);
    b.initialiser(0);

    Vecteur temp = b;

    for(typename list<Block<M>>::iterator block = val.begin(); block != val.end(); ++block) {

        (*block).MvProdInv(x, temp);

        for (int i = 0; i < b.size(); i++) {
            b(i) += temp(i);
        }
    }
}

// TODO - trouves un moyen de stocker cette galere dans un autre fichier
template class BlockMatrix<DenseMatrix>;
template class BlockMatrix<MatriceCSR>;
