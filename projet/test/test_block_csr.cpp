#include <iostream>
#include <block.hpp>
#include <outils/catch.hpp>
#include <vector>
#include <outils/logger.hpp>
#include <matrice_laplacien.hpp>
#include <matrice_laplacien_csr.hpp>
#include <matrice_csr.hpp>
#include <dense_matrix.hpp>

using namespace std;

bool matricesEgales(DenseMatrix& denseMatrix, MatriceCSR matriceCsr) {

    for (int row = 0; row < denseMatrix.getHeight(); row++) {
        for (int column = 0; column < denseMatrix.getWidth(); column++) {
            if (matriceCsr(row, column) != denseMatrix(row, column)) {
                return false;
            }
        }
    }

    return true;
}

TEST_CASE("classe Block avec des matrices csr", "[block_csr]") {

    SECTION("on peut generer des matrices block avec une matrice csr") {

        vector<int> leftVector = {2, 4};
        vector<int> rightVector = {1, 3};
        Block<MatriceCSR> blockCsr = Block<MatriceCSR>(5, 5, leftVector, rightVector);
        MatriceCSR leftMatrixCsr = blockCsr.getLeftMatrix();

        // TODO - euh...
        leftMatrixCsr.populate();

        Block<DenseMatrix> blockDense = Block<DenseMatrix>(5, 5, leftVector, rightVector);

        DenseMatrix leftMatrixDense = blockDense.getLeftMatrix();
        REQUIRE(matricesEgales(leftMatrixDense, leftMatrixCsr));

        MatriceCSR rightMatrixCsr = blockCsr.getRightMatrix();
        rightMatrixCsr.populate();
        DenseMatrix rightMatrixDense = blockDense.getRightMatrix();
        REQUIRE(matricesEgales(rightMatrixDense, rightMatrixCsr));

    }

    SECTION("on peut multiplier un vector par un block") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        Block<DenseMatrix> blockDense = Block<DenseMatrix>(4, 4, leftVector, rightVector);
        DenseMatrix centerDense = {{6, 7, 8}, {9, 10, 11}, {12, 13, 14}};
        blockDense.setCenterMatrix(centerDense);

        Vecteur x = {1, 0, 3, 4};
        Vecteur bCorrect = {38, 0, 53, 68};
        Vecteur bDense = vector<double>(4, 0);
        blockDense.MvProd(x, bDense);
        REQUIRE(bDense == bCorrect);


        Block<MatriceCSR> blockCsr = Block<MatriceCSR>(4, 4, leftVector, rightVector);
        MatriceCSR centerCsr = {{6, 7, 8}, {9, 10, 11}, {12, 13, 14}};

        blockCsr.setCenterMatrix(centerCsr);

        Vecteur bCsr = vector<double>(4, 0);
        blockCsr.MvProd(x, bCsr);

        REQUIRE(bCsr == bCorrect);
    }

    SECTION("calculer le produit inverse") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        // =========================================================

        Block<DenseMatrix> blockDense = Block<DenseMatrix>(4, 4, leftVector, rightVector);
        DenseMatrix centerMatrixDense = MatriceLaplacien(3);
        blockDense.setCenterMatrix(centerMatrixDense);

        Vecteur x = {1, 2, 3, 4};

        Vecteur bDense = Vecteur(4);
        blockDense.MvProdInv(x, bDense);

        // =========================================================

        Block<MatriceCSR> blockCsr = Block<MatriceCSR>(4, 4, leftVector, rightVector);
        MatriceCSR centerMatrixCsr = MatriceLaplacienCSR(3);
        blockCsr.setCenterMatrix(centerMatrixCsr);

        Vecteur bCsr = Vecteur(4);
        blockCsr.MvProdInv(x, bCsr);

        // =========================================================

        REQUIRE(matricesEgales(centerMatrixDense, centerMatrixCsr));
        REQUIRE(bCsr == bDense);
    }
}
