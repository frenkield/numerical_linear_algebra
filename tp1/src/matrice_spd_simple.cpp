#include <matrice_spd_simple.hpp>
#include <cassert>
using namespace std;

MatriceSPDSimple::MatriceSPDSimple(int taille) : Matrice(taille) {

    assert(taille > 0);

    for (int i = 0; i < taille; i++) {

        operator()(i, i) = i + 1;

        if (i + 2 < taille) {
            operator()(i, i + 2) = 1;
        }

        if (i - 2 >= 0) {
            operator()(i, i - 2) = 1;
        }
    }
}

