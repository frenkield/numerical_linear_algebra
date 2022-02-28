#include <matrice_laplacienne.hpp>
#include <cassert>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;


MatriceLaplacienne::MatriceLaplacienne(int taille) : Matrice(taille) {

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

