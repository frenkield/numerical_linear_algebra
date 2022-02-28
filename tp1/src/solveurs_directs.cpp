#include <solveurs_directs.hpp>

Vecteur solve_triang_inf(const Matrice& matrice, const Vecteur& vecteur) {

    Vecteur solutionVecteur = Vecteur(vecteur.size());
   
    for(int j = 0; j < matrice.size(); j++) {

        double somme = 0;

        for(int k = 0; k < j; k++) {
            somme += matrice(j, k) * solutionVecteur(k);
        }
        
        solutionVecteur(j) = (vecteur(j) - somme) / matrice(j, j);
    }
    
    return solutionVecteur;
}

Vecteur solve_triang_sup(const Matrice& matrice, const Vecteur& vecteur) {

    Vecteur solutionVecteur = Vecteur(vecteur.size());
   
    for(int j = matrice.size() - 1; j >= 0; j--) {

        double somme = 0;

        for(int k = matrice.size() - 1; k > j; k--) {
            somme += matrice(j, k) * solutionVecteur(k);
        }
        
        solutionVecteur(j) = (vecteur(j) - somme) / matrice(j, j);
    }
    
    return solutionVecteur;
}

Vecteur solve_triang_inf_id(const Matrice &A, const Vecteur& b) {

    Vecteur solutionVecteur = Vecteur(b.size());
   
    for(int j = 0; j < A.size(); j++) {

        double somme = 0;

        for(int k = 0; k < j; k++) {
            somme += A(j, k) * solutionVecteur(k);
        }
        
        solutionVecteur(j) = b(j) - somme;
    }
    
    return solutionVecteur;
}

Vecteur solve_triang_sup_id(const Matrice &A, const Vecteur& b) {

    Vecteur solutionVecteur = Vecteur(b.size());
   
    for(int j = A.size() - 1; j >= 0; j--) {

        double somme = 0;

        for(int k = A.size() - 1; k > j; k--) {
            somme += A(j, k) * solutionVecteur(k);
        }
        
        solutionVecteur(j) = b(j) - somme;
    }
    
    return solutionVecteur;
}
