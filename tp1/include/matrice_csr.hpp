#ifndef TP1_MATRICE_CSR_H
#define TP1_MATRICE_CSR_H

#include <matrice.hpp>
#include <triplet.hpp>

using namespace std;

class MatriceCSR : public Matrice {

private:
    int nr = 0;
    int nc = 0;
    vector<int> rows;
    vector<int> colums;
    vector<double> values;

public:
    void populate(const int& nr, const int& nc, vector<Triplet>& triplets);

};

#endif //TP1_MATRICE_CSR_H
