#include <dense_matrix.hpp>
#include <matrice_laplacien.hpp>
#include <outils/catch.hpp>
#include <vector>
#include <outils/logger.hpp>
#include <matrice_spd_simple.hpp>

using namespace std;

TEST_CASE("création et operateurs de la classe, DenseMatrix", "[dense_matrix]") {

    SECTION("on peut initialiser une matrice avec une liste") {
        DenseMatrix matrix = {
            {1, 2, 3, 2, 8},
            {-1, 23, 3.5, 5.2, 8},
            {1, 52, 3, 2, 8},
            {1, -12, 3, 2, 8},
            {1, 2, 3, 2, 8}
        };
        REQUIRE(matrix.getHeight() == 5);
        REQUIRE(matrix(1, 3) == 5.2);
    }

    SECTION("on peut créer une matrice par recopie avec l'opérateur =") {

        DenseMatrix matrix = {
                {1, 2, 3, 2, 8},
                {-1, 23, 3.5, 5.2, 8},
                {1, 52, 3, 2, 8},
                {1, -12, 3, 2, 8},
                {1, 2, 3, 2, 8}
        };

        DenseMatrix copy = matrix;

        REQUIRE((copy == matrix));
    }

    SECTION("on peut manipuler une matrice avec l'operateur parentheses") {

        DenseMatrix matrix(10, 10);
        REQUIRE(matrix.getHeight() == 10);

        matrix(3, 4) = 5;
        REQUIRE(matrix(3, 4) == 5);
    }

    SECTION("on peut additonner et soustraire des matrices") {

        DenseMatrix matrix1(10, 10);
        DenseMatrix matrix2(10, 10);

        matrix1(0, 0) = 5;
        matrix2(0, 0) = 3;

        matrix1(3, 3) = 9.9;
        matrix2(3, 3) = 7.2;

        DenseMatrix sommeDenseMatrix = matrix1 + matrix2;

        REQUIRE(sommeDenseMatrix.getHeight() == matrix1.getHeight());
        REQUIRE(sommeDenseMatrix(0, 0) == 8);
        REQUIRE(sommeDenseMatrix(1, 1) == 0);
        REQUIRE(sommeDenseMatrix(3, 3) == 17.1);

        DenseMatrix differenceDenseMatrix = matrix1 - matrix2;
        REQUIRE(differenceDenseMatrix.getHeight() == matrix1.getHeight());
        REQUIRE(differenceDenseMatrix(0, 0) == 2);
        REQUIRE(differenceDenseMatrix(1, 1) == 0);
        REQUIRE(differenceDenseMatrix(3, 3) == 2.7);

        differenceDenseMatrix = matrix2 - matrix1;
        REQUIRE(differenceDenseMatrix(3, 3) == -2.7);
    }

    SECTION("on peut multiplier des matrices") {

        DenseMatrix matrix1(10, 10);
        DenseMatrix matrix2(10, 10);

        matrix1(0, 0) = 5;
        matrix1(0, 1) = -6.3;
        matrix2(0, 0) = 3;
        matrix2(0, 5) = 48.4545;
        matrix2(1, 5) = 8.2;

        DenseMatrix produitDenseMatrix = matrix1 * matrix2;
        REQUIRE(produitDenseMatrix(0, 0) == 15);
        REQUIRE(produitDenseMatrix(0, 5) == 5 * 48.4545 + -6.3 * 8.2);
    }

    SECTION("on peut multiplier des matrices rectangulaire") {

        DenseMatrix matrix1 = {{1, 2, 3}, {-2, 0, 1}};
        DenseMatrix matrix2 = {{1, 2}, {2, 0}, {3, -1}};
        DenseMatrix product = matrix1 * matrix2;

        DenseMatrix productCorrect = {{14, -1}, {1, -5}};
        REQUIRE((product == productCorrect));
    }

    SECTION("on peut multiplier une matrice par une scalaire") {

        DenseMatrix matrix(10, 10);

        matrix(0, 0) = 5;
        matrix(3, 3) = 9.9;

        DenseMatrix nouveauDenseMatrix = matrix * 2.2;
        REQUIRE(matrix(0, 0) == 5);
        REQUIRE(nouveauDenseMatrix(0, 0) == (5 * 2.2));
        REQUIRE(nouveauDenseMatrix(3, 3) == (9.9 * 2.2));

        nouveauDenseMatrix = matrix * -3.65;
        REQUIRE(matrix(0, 0) == 5);
        REQUIRE(nouveauDenseMatrix(0, 0) == (5 * -3.65));
        REQUIRE(nouveauDenseMatrix(3, 3) == (9.9 * -3.65));
    }

    SECTION("on peut multiplier une matrice rectangulaire par une scalaire") {

        DenseMatrix matrix = {{1, 2, 3}, {7, -1, 0}};
        DenseMatrix result = matrix * 2.2;

        DenseMatrix correctResult = {{2.2, 4.4, 6.6}, {15.4, -2.2, 0}};
        REQUIRE((result == correctResult));
    }

    SECTION("on peut multiplier un vecteur par une matrice") {

        DenseMatrix matrix(10, 10);
        vector<double> vecteur(10, 0);

        matrix(0, 0) = 5;
        matrix(0, 1) = -6.3;
        matrix(0, 5) = 48.4;
        matrix(1, 5) = 8.2;
        matrix(5, 0) = -7;
        matrix(5, 2) = 48.4;

        vecteur[0] = 2;
        vecteur[2] = 3.7;

        vector<double> resultatVecteur = matrix * vecteur;
        REQUIRE(resultatVecteur[0] == 5 * 2);
        REQUIRE(resultatVecteur[5] == (-7 * 2) + (48.4 * 3.7));
    }

    SECTION("on peut multiplier un vecteur par une matrice rectangulaire") {

        DenseMatrix matrix = {{0, 2, -1}, {4, 1, 1}};
        vector<double> vect = {1, 2, 3};

        vector<double> result = matrix * vect;
        vector<double> correctResult = {1, 9};

        REQUIRE((result == correctResult));
    }

    SECTION("on peut multiplier un vecteur par une autre matrice rectangulaire") {

        DenseMatrix matrix = {{0, 2}, {3, -1}, {1, 3}};
        vector<double> vect = {1, 2};

        vector<double> result = matrix * vect;
        vector<double> correctResult = {4, 1, 7};

        REQUIRE((result == correctResult));
    }

    SECTION("on peut multiplier un vecteur par une matrice rectangulaire et stocker le resultat") {

        DenseMatrix matrix = {{0, 2, -1}, {4, 1, 1}};
        Vecteur x = {1, 2, 3};
        Vecteur b = vector<double>(2);

        matrix.MvProd(x, b);

        vector<double> correctResult = {1, 9};
        REQUIRE((b == correctResult));
    }

    SECTION("on peut generer le transpose d'une matrice") {

        DenseMatrix matrix = {
            {2, -1, 0, 7, 9},
            {-1, 2, -1, -55, 8},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        DenseMatrix matrixTranspose = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {7, -55, -1, 2, -1},
            {9, 8, 0, -1, 2}
        };

        REQUIRE((matrixTranspose == matrix.transpose()));
    }

    SECTION("on peut generer le transpose d'une matrice rectangulaire") {

        DenseMatrix matrix = {
            {2, -1, 0, 7, 9},
            {-1, 2, -1, -55, 8},
            {0, -1, 2, -1, 0}
        };

        DenseMatrix matrixTranspose = {
            {2, -1, 0},
            {-1, 2, -1},
            {0, -1, 2},
            {7, -55, -1},
            {9, 8, 0}
        };

        REQUIRE((matrixTranspose == matrix.transpose()));
    }

    SECTION("on peut extraire le diagonal et le diagonal inverse") {

        DenseMatrix matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        DenseMatrix diagonal = matrix.getDiagonal();
        DenseMatrix diagonalTest = {{1, 0, 0}, {0, 5, 0}, {0, 0, 9}};
        REQUIRE((diagonal == diagonalTest));

        matrix = {{1, 2, 3}, {4, 4, 6}, {7, 8, 8}};
        diagonal = matrix.getDiagonalInverse();
        diagonalTest = {{1, 0, 0}, {0, 0.25, 0}, {0, 0, 0.125}};
        REQUIRE((diagonal == diagonalTest));
    }

    SECTION("on peut décomposer une matrice") {

        DenseMatrix matrix = {
                {2, -1, 0, 0, 0},
                {-1, 2, -1, 0, 0},
                {0, -1, 2, -1, 0},
                {0, 0, -1, 2, -1},
                {0, 0, 0, -1, 2}
        };

        Vecteur b = {1, 1, 1, 1, 1};
        Vecteur x = Vecteur(b.size());

        matrix.LUSolve(x, b);

        DenseMatrix decomposedMatrix = {
            {2, -1, 0, 0, 0},
            {-0.5, 1.5, -1, 0, 0},
            {0, -2.0 / 3.0, 4.0 / 3.0, -1, 0},
            {0, 0, -0.75, 1.25, -1},
            {0, 0, 0, -0.8, 1.2}
        };

        REQUIRE((matrix == decomposedMatrix));
    }

    SECTION("on peut resoudre un systeme linéaire moyennant une decomposition lu") {

        DenseMatrix matrix = {
            {2, -1, 0, 0, 0},
            {-1, 2, -1, 0, 0},
            {0, -1, 2, -1, 0},
            {0, 0, -1, 2, -1},
            {0, 0, 0, -1, 2}
        };

        Vecteur b = {1, 1, 1, 1, 1};
        Vecteur x = vector<double>(b.size());

        matrix.LUSolve(x, b);

        vector<double> solution = {2.5, 4, 4.5, 4, 2.5};

        REQUIRE((x == solution));
    }

    SECTION("on peut resoudre un systeme linéaire moyennant la methode gradient conjugué") {

        MatriceLaplacien A = MatriceLaplacien(5);

        vector<double> x = vector<double>(5);
        vector<double> b = vector<double>(5, 1);

        A.cg(x, b, 0.001);

        Vecteur solution = {2.5, 4, 4.5, 4, 2.5};

        // TODO - pourquoi ça marche ????
        Vecteur erreur = solution - x;

        REQUIRE((erreur.norme() < 0.001));
    }

    SECTION("on peut extraire une matrice par vecteurs row/column") {

        MatriceLaplacien matrice = MatriceLaplacien(5);

        vector<int> rowVector = {0, 1};
        vector<int> columnVector = {1, 2};

        DenseMatrix extractedMatrix = matrice(rowVector, columnVector);
        DenseMatrix correctExtractedMatrix = {{-1, 0}, {2, -1}};

        REQUIRE(extractedMatrix == correctExtractedMatrix);
    }

    SECTION("resoudre un systeme lineaire par la methode schwarz additif") {

        int n = 100;

        DenseMatrix matrice = MatriceLaplacien(n);
        Vecteur b = Vecteur(n);
        b.initialiser(1);

        Vecteur xPcg = Vecteur(n);
        matrice.pcg(xPcg, b, 0.00001);

        Vecteur xCg = Vecteur(n);
        matrice.cg(xCg, b, 0.00001);

        REQUIRE(xPcg == xCg);
    }
}
