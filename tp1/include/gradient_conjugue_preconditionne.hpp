#ifndef TP1_GRADIENT_CONJUGUE_PRECONDITIONNE_H
#define TP1_GRADIENT_CONJUGUE_PRECONDITIONNE_H

#include <methode_iterative.hpp>

class GradientConjuguePreconditionne : public MethodeIterative {

public:
    GradientConjuguePreconditionne(Matrice& A, Vecteur& b) : MethodeIterative(A, b) {}
    Vecteur solve();
};

#endif // TP1_GRADIENT_CONJUGUE_PRECONDITIONNE_H
