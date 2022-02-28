#ifndef TP1_TRIPLET_H
#define TP1_TRIPLET_H

class Triplet {

public:

    int i = 0;
    int j = 0;
    double valeur = 0;

    Triplet();
    Triplet(int i, int j, double valeur);
    Triplet(const Triplet& triplet);

    bool operator<(const Triplet& triplet);
    bool operator>(const Triplet& triplet);
    bool operator==(const Triplet& triplet);
    void operator=(const Triplet& triplet);
};

#endif //TP1_TRIPLET_H
