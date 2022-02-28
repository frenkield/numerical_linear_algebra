#include <iostream>
#include <matrice_csr.hpp>
#include <cassert>

using namespace std;

void MatriceCSR::populate(const int& nr, const int& nc, vector<Triplet>& triplets) {

    assert(nr > 0 && nc > 0);

    typedef vector <Triplet>::iterator TripletIterator;


    for (TripletIterator triplet = triplets.begin(); triplet != triplets.end(); ++triplet) {

        cout << (*triplet).valeur << endl;
    }
}

/*

MatriceCSR::MatriceCSR(int nr, int nc) {
    this->nr = nr;
    this->nc = nc;
}

void MatriceCOO::set(int i, int j, double valeur) {
    assert(valeur != 0 && i >= 0 && i < nr && j >= 0 && j < nc);
    Triplet triplet = Triplet(i, j, valeur);
    triplets.push_back(triplet);
}

vector<Triplet> MatriceCOO::getTriplets() {
    return triplets;
}
*/
