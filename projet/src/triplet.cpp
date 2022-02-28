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

bool operator<(const Triplet& triplet1, const Triplet& triplet2) {
    if (triplet1.i < triplet2.i || (triplet1.i == triplet2.i && triplet1.j < triplet2.j)) {
        return true;
    }
    return false;
}

bool operator>(const Triplet& triplet1, const Triplet& triplet2) {
    if (triplet1.i > triplet2.i || (triplet1.i == triplet2.i && triplet1.j > triplet2.j)) {
        return true;
    }
    return false;
}

bool operator==(const Triplet& triplet1, const Triplet& triplet2) {
    return triplet1.i == triplet2.i && triplet1.j == triplet2.j;
}
