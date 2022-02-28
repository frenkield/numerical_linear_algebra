#ifndef MATRICE_COO_H
#define MATRICE_COO_H

#include <vector>
#include <triplet.hpp>

class MatriceCOO {

private:
    int nr;
    int nc;
    std::vector<Triplet> triplets = std::vector<Triplet>();

public:
    MatriceCOO(int nr, int nc);
    void set(int i, int j, double valeur);
    std::vector<Triplet>& getTriplets();

    int getHeight() const;
    int getWidth() const;
};

#endif //MATRICE_COO_H
