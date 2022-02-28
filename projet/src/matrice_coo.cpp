#include <matrice_coo.hpp>
#include <cassert>

using namespace std;

MatriceCOO::MatriceCOO(int nr, int nc) {
    this->nr = nr;
    this->nc = nc;
}

void MatriceCOO::set(int i, int j, double valeur) {
    assert(i >= 0 && i < nr && j >= 0 && j < nc);
    if (valeur != 0) {
        Triplet triplet = Triplet(i, j, valeur);
        triplets.push_back(triplet);
    }
}

vector<Triplet>& MatriceCOO::getTriplets() {
    return triplets;
}

int MatriceCOO::getHeight() const {
    return nr;
}

int MatriceCOO::getWidth() const {
    return nc;
}
