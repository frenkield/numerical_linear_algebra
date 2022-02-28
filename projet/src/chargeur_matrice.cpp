#include <chargeur_matrice.hpp>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

DenseMatrix ChargeurMatrice::chargerDenseMatrix(string nomFichier) {

    ifstream fichier(nomFichier);

    if (!fichier) {
        throw "le fichier, " + nomFichier + ", n'existe pas";
    }

    DenseMatrix matrice = creerDenseMatrice(fichier);
    assert(matrice.getWidth() > 0 && matrice.getHeight() > 0);

    ajouterEntrees(matrice, fichier);

    return matrice;
}

DenseMatrix ChargeurMatrice::creerDenseMatrice(istream& stream) {

    int nr;
    int nc;

    string ligne = chercherProchaineLigne(stream);
    stringstream stringstream(ligne);
    stringstream >> nr >> nc;

    DenseMatrix matrice = DenseMatrix(nr, nc);
    return matrice;
}

void ChargeurMatrice::ajouterEntrees(DenseMatrix& matrice, istream &stream) {

    string ligne;
    int row = 0;
    int column = 0;

    while (!(ligne = chercherProchaineLigne(stream)).empty()) {

        stringstream entrees(ligne);

        while (!entrees.eof()) {

            double valeur;
            entrees >> valeur;

            matrice(row, column++) = valeur;

            if (column >= matrice.getWidth()) {
                column = 0;
                row++;
            }
        }
    }
}

string ChargeurMatrice::chercherProchaineLigne(istream& stream) {

    string ligne;

    while (stream && (ligne.empty() || ligne.find("#") != string::npos)) {
        getline(stream, ligne);
    }

    return trimString(ligne);
}

// les regular expressions ne compilent pas sur les machines de l'utes...
string& ChargeurMatrice::trimString(string& ligne) {
    ligne.erase(0, ligne.find_first_not_of("\t\n\v\f\r "));
    ligne.erase(ligne.find_last_not_of("\t\n\v\f\r ") + 1);
    return ligne;
}
