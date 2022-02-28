#ifndef TP1_GRADIENT_CONJUGUE_H
#define TP1_GRADIENT_CONJUGUE_H

#include <methode_iterative.hpp>

class GradientConjugue : public MethodeIterative {

public:
    GradientConjugue(Matrice& A, Vecteur& b) : MethodeIterative(A, b) {}
    Vecteur solve();
};

#endif // TP1_GRADIENT_CONJUGUE_H
