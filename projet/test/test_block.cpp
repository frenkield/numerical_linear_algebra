#include <iostream>
#include <block.hpp>
#include <outils/catch.hpp>
#include <vector>
#include <outils/logger.hpp>
#include <matrice_laplacien.hpp>

using namespace std;

TEST_CASE("classe Block", "[block]") {

    SECTION("on peut generer des matrices block") {

        vector<int> leftVector = {2, 4};
        vector<int> rightVector = {1, 3};

        Block<DenseMatrix> block = Block<DenseMatrix>(5, 5, leftVector, rightVector);

        DenseMatrix leftMatrix = block.getLeftMatrix();
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();

        DenseMatrix leftMatrixCorrect = {{0, 0}, {0, 0}, {1, 0}, {0, 0}, {0, 1}};
        DenseMatrix rightMatrixTransposeCorrect = {{0, 1, 0, 0, 0}, {0, 0, 0, 1, 0}};

        REQUIRE((leftMatrix == leftMatrixCorrect));
        REQUIRE((rightMatrixTranspose == rightMatrixTransposeCorrect));
    }

    SECTION("on peut encore generer des matrices block") {

        vector<int> leftVector = {0, 1};
        vector<int> rightVector = {0, 1};

        Block<DenseMatrix> block = Block<DenseMatrix>(3, 5, leftVector, rightVector);

        DenseMatrix leftMatrix = block.getLeftMatrix();
        DenseMatrix centerMatrix = block.getCenterMatrix();
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();

        DenseMatrix leftMatrixCorrect = {{1, 0}, {0, 1}, {0, 0}};
        DenseMatrix centerMatrixCorrect = {{0, 0}, {0, 0}, {0, 0}};
        DenseMatrix rightMatrixTransposeCorrect = {{1, 0, 0, 0, 0}, {0, 1, 0, 0, 0}};

        REQUIRE((leftMatrix == leftMatrixCorrect));
        REQUIRE((centerMatrix == centerMatrixCorrect));
        REQUIRE((rightMatrixTranspose == rightMatrixTransposeCorrect));
    }

    SECTION("on peut generer la matrice produit") {

        vector<int> leftVector = {0, 2};
        vector<int> rightVector = {1, 2};

        Block<DenseMatrix> block = Block<DenseMatrix>(3, 3, leftVector, rightVector);

        DenseMatrix centerMatrix = {{6, 7}, {8, 9}};
        block.setCenterMatrix(centerMatrix);

        DenseMatrix leftMatrix = block.getLeftMatrix();
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();

        DenseMatrix correctMatrix =  leftMatrix * centerMatrix * rightMatrixTranspose;
        DenseMatrix matrix =  block.getMatrix();

        REQUIRE((matrix == correctMatrix));
    }

    SECTION("on peut encore generer la matrice produit") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        Block<DenseMatrix> block = Block<DenseMatrix>(4, 4, leftVector, rightVector);

        DenseMatrix centerMatrix = {{6, 7, 8}, {9, 10, 11}, {12, 13, 14}};
        block.setCenterMatrix(centerMatrix);

        DenseMatrix leftMatrix = block.getLeftMatrix();
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();

        DenseMatrix correctMatrix =  leftMatrix * centerMatrix * rightMatrixTranspose;
        DenseMatrix matrix =  block.getMatrix();

        REQUIRE((matrix == correctMatrix));
    }

    SECTION("on peut multiplier un vector par un block") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        Block<DenseMatrix> block = Block<DenseMatrix>(4, 4, leftVector, rightVector);

        DenseMatrix centerMatrix = {{6, 7, 8}, {9, 10, 11}, {12, 13, 14}};
        block.setCenterMatrix(centerMatrix);

        DenseMatrix leftMatrix = block.getLeftMatrix();
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();

        DenseMatrix correctMatrix = leftMatrix * centerMatrix * rightMatrixTranspose;
        DenseMatrix matrix =  block.getMatrix();
        REQUIRE((matrix == correctMatrix));

        Vecteur x = {1, 0, 3, 4};
        Vecteur b = vector<double>(4, 0);

        block.MvProd(x, b);
        Vecteur correctB = correctMatrix * x;

        REQUIRE((b == correctB));
    }

    SECTION("calculer le produit matrice row/left fois x") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        Block<DenseMatrix> block = Block<DenseMatrix>(4, 4, leftVector, rightVector);

        DenseMatrix centerMatrix = MatriceLaplacien(3);
        block.setCenterMatrix(centerMatrix);
        DenseMatrix leftMatrix = block.getLeftMatrix();

        Vecteur x = {1, 2, 3};
        Vecteur b = Vecteur(4);

        block.productLeftMatrix(x, b);

        vector<double> solution = {1, 0, 2, 3};
        REQUIRE(b == solution);
    }

    SECTION("calculer le produit matrice column/right transpose fois x") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        Block<DenseMatrix> block = Block<DenseMatrix>(4, 4, leftVector, rightVector);

        DenseMatrix centerMatrix = MatriceLaplacien(3);
        block.setCenterMatrix(centerMatrix);
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();

        Vecteur x = {1, 2, 3, 4};
        Vecteur b = Vecteur(3);

        block.productRightMatrixTranspose(x, b);

        vector<double> solution = {1, 2, 4};
        REQUIRE(b == solution);
    }

    SECTION("calculer le produit inverse") {

        vector<int> leftVector = {0, 2, 3};
        vector<int> rightVector = {0, 1, 3};

        Block<DenseMatrix> block = Block<DenseMatrix>(4, 4, leftVector, rightVector);

        DenseMatrix centerMatrix = MatriceLaplacien(3);
        block.setCenterMatrix(centerMatrix);

        Vecteur x = {1, 2, 3, 4};
        Vecteur b = Vecteur(4);

        block.MvProdInv(x, b);

        DenseMatrix leftMatrix = block.getLeftMatrix();
        DenseMatrix rightMatrixTranspose = block.getRightMatrix().transpose();
        DenseMatrix laplacienInverse = {{3, 2, 1}, {2, 4, 2}, {1, 2, 3}};
        laplacienInverse = laplacienInverse * 0.25;
        DenseMatrix leftBInverseRightTranspose = leftMatrix * laplacienInverse * rightMatrixTranspose;
        Vecteur correctProduct = leftBInverseRightTranspose * x;

        REQUIRE(b == correctProduct);
    }
}
