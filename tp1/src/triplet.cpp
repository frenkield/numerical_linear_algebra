#include <triplet.hpp>

Triplet::Triplet() {
}

Triplet::Triplet(int i, int j, double valeur) {
    this->i = i;
    this->j = j;
    this->valeur = valeur;
}

Triplet::Triplet(const Triplet& triplet) : Triplet(triplet.i, triplet.j, triplet.valeur) {
}

void Triplet::operator=(const Triplet& triplet) {
    i = triplet.i;
    j = triplet.j;
    valeur = triplet.valeur;
}

bool Triplet::operator<(const Triplet& triplet) {
    if (i < triplet.i || i == triplet.i && j < triplet.j) {
        return true;
    }
    return false;
}

bool Triplet::operator>(const Triplet& triplet) {
    if (i > triplet.i || i == triplet.i && j > triplet.j) {
        return true;
    }
    return false;
}

bool Triplet::operator==(const Triplet& triplet) {
    return i == triplet.i && j == triplet.j;
}
