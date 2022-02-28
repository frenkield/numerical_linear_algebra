#ifndef TP1_SOLVEURS_DIRECTS_H
#define TP1_SOLVEURS_DIRECTS_H

#include <iostream>
#include <assert.h>
#include <vecteur.hpp>
#include <matrice.hpp>

// TODO - on veut utiliser peut-etre A et b ?
Vecteur solve_triang_inf(const Matrice& matrice, const Vecteur& vecteur);

// TODO - on veut utiliser peut-etre A et b ?
Vecteur solve_triang_sup(const Matrice& matrice, const Vecteur& vecteur);

Vecteur solve_triang_inf_id(const Matrice &A, const Vecteur& b);
Vecteur solve_triang_sup_id(const Matrice &A, const Vecteur& b);

#endif // TP1_SOLVEURS_DIRECTS_H
