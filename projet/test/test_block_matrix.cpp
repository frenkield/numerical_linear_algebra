#include <iostream>
#include <block.hpp>
#include <outils/catch.hpp>
#include <vector>
#include <outils/logger.hpp>
#include <block_matrix.hpp>
#include <matrice_laplacien.hpp>

using namespace std;

TEST_CASE("classe BlockMatrix", "[block_matrix]") {

    SECTION("on peut ajouter des blocks") {

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(5, 5);

        vector<int> leftVector = {2, 4};
        vector<int> rightVector = {1, 3};
        Block<DenseMatrix> block = Block<DenseMatrix>(5, 5, leftVector, rightVector);

        blockMatrix += block;
        REQUIRE(blockMatrix.getBlocks().size() == 1);

        blockMatrix += block;
        REQUIRE(blockMatrix.getBlocks().size() == 2);
    }

    SECTION("on peut multiplier un vecteur par un BlockMatrix") {

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(5, 5);

        vector<int> leftVector = {0, 2, 4};
        vector<int> rightVector = {1, 2, 3};
        Block<DenseMatrix> block1 = Block<DenseMatrix>(5, 5, leftVector, rightVector);
        DenseMatrix centerMatrix = {{6, 7, 8}, {9, 10, 11}, {12, 13, 14}};
        block1.setCenterMatrix(centerMatrix);
        blockMatrix += block1;
        DenseMatrix matrix1 = block1.getMatrix();

        leftVector = {1, 2, 3, 4};
        rightVector = {0, 1, 2, 3};
        Block<DenseMatrix> block2 = Block<DenseMatrix>(5, 5, leftVector, rightVector);
        centerMatrix = {{1, 2, 3, 4}, {3, 3, 8, 1}, {6, 7, 8, 1}, {9, 10, 11, 4}};
        block2.setCenterMatrix(centerMatrix);
        blockMatrix += block2;
        DenseMatrix matrix2 = block2.getMatrix();

        REQUIRE(blockMatrix.getBlocks().size() == 2);

        Vecteur x = {1, 0, 3, 4, 2};
        Vecteur b = Vecteur(5);

        blockMatrix.MvProd(x, b);

        Vecteur solution = (matrix1 + matrix2) * x;
        REQUIRE(solution == b);
    }

    SECTION("on peut resoudre un systeme lineaire avec un seule block simople") {

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(3, 3);

        vector<int> leftVector = {0, 1, 2};
        vector<int> rightVector = {0, 1, 2};
        Block<DenseMatrix> block1 = Block<DenseMatrix>(3, 3, leftVector, rightVector);
        DenseMatrix centerMatrix = {{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}};
        block1.setCenterMatrix(centerMatrix);
        blockMatrix += block1;

        Vecteur x = Vecteur(3);
        Vecteur b = {1, 1, 1};

        blockMatrix.MinRes(x, b);

        Vecteur solution = {1.5, 2, 1.5};
        REQUIRE(x == solution);
    }

    SECTION("on peut resoudre un systeme lineaire avec 1 seule block plus grand") {

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(5, 5);

        vector<int> leftVector = {0, 1, 2, 3, 4};
        vector<int> rightVector = {0, 1, 2, 3, 4};
        Block<DenseMatrix> block1 = Block<DenseMatrix>(5, 5, leftVector, rightVector);
        DenseMatrix centerMatrix = {{2, -1, 0, 0, 0}, {-1, 2, -1, 0, 0}, {0, -1, 2, -1, 0},
                                    {0, 0, -1, 2, -1}, {0, 0, 0, -1, 2}};
        block1.setCenterMatrix(centerMatrix);
        blockMatrix += block1;

        Vecteur x = Vecteur(5);
        vector<double> b = {1, 1, 1, 1, 1};

        blockMatrix.MinRes(x, b);

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};
        REQUIRE(x == solution);
    }

    SECTION("on peut resoudre un systeme lineaire avec 2 blocks") {

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(5, 5);

        vector<int> leftVector = {0, 1, 2, 3, 4};
        vector<int> rightVector = {0, 1, 2, 3, 4};
        Block<DenseMatrix> block1 = Block<DenseMatrix>(5, 5, leftVector, rightVector);
        DenseMatrix centerMatrix1 = {{2, -1, 0, 0, 0}, {0, 2, -1, 0, 0}, {0, 0, 2, -1, 0},
                                    {0, 0, 0, 2, -1}, {0, 0, 0, 0, 2}};
        block1.setCenterMatrix(centerMatrix1);
        blockMatrix += block1;

        Block<DenseMatrix> block2 = Block<DenseMatrix>(5, 5, leftVector, rightVector);
        DenseMatrix centerMatrix2 = {{0, 0, 0, 0, 0}, {-1, 0, 0, 0, 0}, {0, -1, 0, 0, 0},
                                    {0, 0, -1, 0, 0}, {0, 0, 0, -1, 0}};
        block2.setCenterMatrix(centerMatrix2);
        blockMatrix += block2;

        REQUIRE(blockMatrix.getBlocks().size() == 2);

        Vecteur x = Vecteur(5);
        Vecteur b = {1, 1, 1, 1, 1};

        blockMatrix.MinRes(x, b);

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};
        REQUIRE(x == solution);
    }

    SECTION("générer la liste des vecteurs row/column") {

        int n = 20;
        int l = 2;
        int r = 1;

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(n, n);

        vector<vector<int>> vecteurs = blockMatrix.generateMatrixVectors(l, r, n);

        // il faut verifier que la reunion des vecteurs contient tous les entiers jusqu'a n
        vector<bool> validation = vector<bool>(n, false);

        for(vector<vector<int>>::iterator vecteur = vecteurs.begin(); vecteur != vecteurs.end(); ++vecteur) {

            for(vector<int>::iterator valeurs = (*vecteur).begin(); valeurs != (*vecteur).end(); ++valeurs) {
                validation[*valeurs] = true;
            }
        }

        for(vector<bool>::iterator it = validation.begin(); it != validation.end(); ++it) {
            REQUIRE(*it);
        }
    }

    SECTION("extraire un BlockMatrix") {

        int n = 5;

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(n, n);
        DenseMatrix matrix = MatriceLaplacien(n);

        blockMatrix.Extract(matrix, 2, 1);

        DenseMatrix reconstructedMatrix = blockMatrix.reconstructMatrix();

        DenseMatrix correctReconstructedMatrix = {
            {2, -1, 0, 0, 0},
            {-1, 4, -2, 0, 0},
            {0, -2, 4, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };
        
         REQUIRE((reconstructedMatrix == correctReconstructedMatrix));
    }

    SECTION("calculer le produit inverse avec 1 seule bloc") {

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(5, 5);

        vector<int> leftVector = {0, 1, 2, 3, 4};
        vector<int> rightVector = {0, 1, 2, 3, 4};
        Block<DenseMatrix> block1 = Block<DenseMatrix>(5, 5, leftVector, rightVector);
        DenseMatrix centerMatrix = {{2, -1, 0, 0, 0}, {-1, 2, -1, 0, 0}, {0, -1, 2, -1, 0},
                                    {0, 0, -1, 2, -1}, {0, 0, 0, -1, 2}};
        block1.setCenterMatrix(centerMatrix);
        blockMatrix += block1;

        Vecteur x = Vecteur(5);
        Vecteur b = {1, 1, 1, 1, 1};

        blockMatrix.MvProdInv(b, x);
        blockMatrix.MvProdInv(b, x);
        blockMatrix.MvProdInv(b, x);

        Vecteur xv = x;
        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};
        REQUIRE(xv == solution);
    }

    SECTION("calculer le produit inverse avec 2 blocs") {

        int n = 5;

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(n, n);
        DenseMatrix matrix = MatriceLaplacien(n);

        vector<int> vector1 = {0, 2, 3, 4};
        Block<DenseMatrix> block1 = Block<DenseMatrix>(n, n, vector1, vector1);
        DenseMatrix extractedMatrix1 = matrix(vector1, vector1);
        block1.setCenterMatrix(extractedMatrix1);
        blockMatrix += block1;

        // ==================================================

        vector<int> vector2 = {1, 2, 3};
        Block<DenseMatrix> block2 = Block<DenseMatrix>(n, n, vector2, vector2);
        DenseMatrix extractedMatrix2 = matrix(vector2, vector2);
        block2.setCenterMatrix(extractedMatrix2);
        blockMatrix += block2;

        REQUIRE(blockMatrix.getBlocks().size() == 2);

        Vecteur solution1 = {5, 3.5, 6, 4.5, 1};

        Vecteur x = {2.5, 4, 4.5, 4, 2.5};
        Vecteur b = vector<double>(5);

        blockMatrix.MvProd(x, b);
        REQUIRE(Vecteur(b) == solution1);

        blockMatrix.MvProd(x, b);
        REQUIRE(Vecteur(b) == solution1);

        // =========================================

        Vecteur solution2  = {2.5, 6.75, 17, 15.25, 4.5};

        Vecteur bb = Vecteur(5);
        Vecteur xx = {5, 3.5, 6, 4.5, 1};

        blockMatrix.MvProdInv(xx, bb);

        REQUIRE(bb == solution2);
    }

    SECTION("calculer le produit inverse") {

        int n = 5;

        BlockMatrix<DenseMatrix> blockMatrix = BlockMatrix<DenseMatrix>(n, n);

        DenseMatrix matrix = MatriceLaplacien(n);

        blockMatrix.Extract(matrix, 2, 1);

        Vecteur x = {1, 2, 3, 4, 5};
        Vecteur b = Vecteur(5);

        blockMatrix.MvProdInv(x, b);

        Vecteur solution = {2.5, 10.0, 13.5, 11.0, 8.0};
        REQUIRE(b == solution);
    }
}
