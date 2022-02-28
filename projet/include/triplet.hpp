#ifndef TRIPLET_H
#define TRIPLET_H

class Triplet {

public:

    int i = 0;
    int j = 0;
    double valeur = 0;

    Triplet();
    Triplet(int i, int j, double valeur);
    Triplet(const Triplet& triplet);

    friend bool operator<(const Triplet& triplet1, const Triplet& triplet2);
    friend bool operator>(const Triplet& triplet1, const Triplet& triplet2);
    friend bool operator==(const Triplet& triplet1, const Triplet& triplet2);
    void operator=(const Triplet& triplet);
};

#endif //TRIPLET_H
