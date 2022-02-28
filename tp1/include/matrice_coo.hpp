#ifndef TP1_MATRICE_COO_H
#define TP1_MATRICE_COO_H

#include <vector>
#include <triplet.hpp>
#include <matrice_csr.hpp>

using namespace std;

class MatriceCOO {

private:
    int nr;
    int nc;
    vector<Triplet> triplets = vector<Triplet>();

public:
    MatriceCOO(int nr, int nc);
    void set(int i, int j, double valeur);
    vector<Triplet> getTriplets();

    MatriceCSR toCsr();
};

#endif //TP1_MATRICE_COO_H
