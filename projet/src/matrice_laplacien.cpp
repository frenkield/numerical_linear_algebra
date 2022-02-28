#include <matrice_laplacien.hpp>
#include <cassert>

using namespace std;

MatriceLaplacien::MatriceLaplacien(int taille) : DenseMatrix(taille, taille) {

    assert(taille > 0);

    for (int i = 0; i < taille; i++) {
        operator()(i, i) = 2;

        if (i > 0) {
            operator()(i, i - 1) = -1;
        }

        if (i < taille - 1) {
            operator()(i, i + 1) = -1;
        }
    }
}
