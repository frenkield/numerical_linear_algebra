#ifndef CHARGEUR_MATRICE_H
#define CHARGEUR_MATRICE_H

#include <iostream>
#include <dense_matrix.hpp>

class ChargeurMatrice {

private:
    DenseMatrix creerDenseMatrice(std::istream& stream);
    std::string chercherProchaineLigne(std::istream& stream);
    void ajouterEntrees(DenseMatrix& matrice, std::istream& stream);
    std::string& trimString(std::string& str);

public:
    DenseMatrix chargerDenseMatrix(std::string nomFichier);
};

#endif // CHARGEUR_MATRICE_H
