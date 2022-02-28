#include <matrice_laplacien_csr.hpp>
#include <cassert>

using namespace std;

MatriceLaplacienCSR::MatriceLaplacienCSR(int taille) : MatriceCSR(taille, taille) {

    assert(taille > 0);

    for (int i = 0; i < taille; i++) {
        set(i, i, 2);

        if (i > 0) {
            set(i, i - 1, -1);
        }

        if (i < taille - 1) {
            set(i, i + 1, -1);
        }
    }

    populate();
}
