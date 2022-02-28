#include <iostream>
#include <json.hpp>
#include <vector>
#include <map>
#include <matrice_laplacien_csr.hpp>
#include <chargeur_matrice.hpp>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>

using namespace std;

const double TOLERANCE = 0.00000000001;
typedef vector<HistoristiqueResidu>::iterator ResiduIterator;
typedef map<string, string>::const_iterator InfosMatricesIterator;

void afficherDonneesJson(string method, vector<HistoristiqueResidu>& historiqueResidu,
                         vector<string> labels, JSON &json);

void afficherJson(string titre, string soustitre, string typeMatrice,
                  vector<HistoristiqueResidu>& historiqueCg,
                  vector<HistoristiqueResidu> historiquePcg, vector<string> labels);

// ==============================================================================================

void genererVisualisationDense(const map<string, string>& infosMatrices) {

    vector<HistoristiqueResidu> historiqueCg = vector<HistoristiqueResidu>();
    vector<HistoristiqueResidu> historiquePcg = vector<HistoristiqueResidu>();
    ChargeurMatrice chargeurMatrice = ChargeurMatrice();
    vector<string> labels = vector<string>();

    for (InfosMatricesIterator infoMatrice = infosMatrices.begin();
         infoMatrice != infosMatrices.end(); ++infoMatrice) {

        string indexFichier = infoMatrice->first;
        string nomFichier = infoMatrice->second;

        clog << "traitement de " << nomFichier << "..." << endl;

        DenseMatrix matrice = chargeurMatrice.chargerDenseMatrix(nomFichier);
        Vecteur b = Vecteur::genererVecteurAleatoire(matrice.getHeight());

        Vecteur xCg = Vecteur(b.size());
        matrice.cg(xCg, b, TOLERANCE);
        historiqueCg.push_back(matrice.getHistoriqueResidu());

        Vecteur xPcg = Vecteur(b.size());
        matrice.pcg(xPcg, b, TOLERANCE);
        historiquePcg.push_back(matrice.getHistoriqueResidu());

        labels.push_back(indexFichier);
    }

    afficherJson("DenseMatrix - Résolution CG et PCG", "$\\\\ell=E(n/2)$, $r=\\\\ell-1$",
                 "dense", historiqueCg, historiquePcg, labels);
}

/**
 * On ne traite pas ici les matrices du projet car elles ne sont pas creuse.
 */
void genererVisualisationCsr() {

    vector<HistoristiqueResidu> historiqueCg = vector<HistoristiqueResidu>();
    vector<HistoristiqueResidu> historiquePcg = vector<HistoristiqueResidu>();
    vector<string> labels = vector<string>();

    for (int taille = 100; taille <= 1000; taille += 100) {

        clog << "traitement de matrice laplacien " << taille << "x" << taille << "..." << endl;

        MatriceCSR matrice = MatriceLaplacienCSR(taille);

        Vecteur b = Vecteur::genererVecteurAleatoire(matrice.getHeight());

        Vecteur xCg = Vecteur(b.size());
        matrice.cg(xCg, b, TOLERANCE);
        historiqueCg.push_back(matrice.getHistoriqueResidu());

        Vecteur xPcg = Vecteur(b.size());
        matrice.pcg(xPcg, b, TOLERANCE);
        historiquePcg.push_back(matrice.getHistoriqueResidu());

        labels.push_back(to_string(taille) + "x" + to_string(taille));
    }

    afficherJson("Matrice Laplacien CSR - Résolution CG et PCG", "$\\\\ell=E(n/2)$, $r=\\\\ell-1$",
                 "csr", historiqueCg, historiquePcg, labels);
}

// ==============================================================================================

void afficherJsonDonnees(string method, vector<HistoristiqueResidu>& historiqueResidu,
                         JSON &json, vector<string> labels) {

    int index = 0;

    for (ResiduIterator rCg = historiqueResidu.begin(); rCg != historiqueResidu.end(); ++rCg) {

        vector<double> residu = vector<double>();

        for (HistoristiqueResiduIterator residuIt = (*rCg).begin(); residuIt != (*rCg).end(); ++residuIt) {
            residu.push_back((*residuIt).second);
        }

        json.start("matrix" + to_string(index) + method)
                .add("type", "residu")
                .add("matrix", labels[index])
                .add("method", method)
                .add("label", labels[index])
                .add("residu", residu)
                .end();

        index++;
    }
}

void afficherJson(string titre, string soustitre, string typeMatrice,
                  vector<HistoristiqueResidu>& historiqueCg,
                  vector<HistoristiqueResidu> historiquePcg, vector<string> labels) {

    JSON json(cout);

    json.start("configuration")
            .add("type", "configuration")
            .add("matrixType", typeMatrice)
            .add("tolerance", TOLERANCE)
            .add("title", titre)
            .add("subtitle", soustitre)
            .end();

    afficherJsonDonnees("cg", historiqueCg, json, labels);
    afficherJsonDonnees("pcg", historiquePcg, json, labels);

    json.close();
}

// ==============================================================================================

bool stringEndsWith(const std::string &str, const std::string &suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

map<string, string> trouverMatrices(string nomRepertoire) {

    map<string, string> matrices = map<string, string>();
    DIR *repertoire = opendir(nomRepertoire.c_str());

    if (repertoire) {

        struct dirent *fichier;
        while ((fichier = readdir(repertoire)) != NULL) {

            string nomFichier = string(fichier->d_name);

            if (stringEndsWith(nomFichier, ".txt")) {

                // désolé windows...
                matrices[fichier->d_name] = nomRepertoire + "/" + fichier->d_name;
            }
        }

        closedir(repertoire);
    }

    return matrices;
}

int main(int argc, char* argv[]) {

    vector<string> arguments = vector<string>();
    for (int i = 0; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    string typeMatrice;

    if (arguments.size() > 1) {
        typeMatrice = arguments[1];
    }

    if (typeMatrice != "dense" && typeMatrice != "csr") {
        cout << "Usage:" << endl;
        cout << "    visualisation dense [-i repertoire]" << endl;
        cout << "    visualisation csr" << endl;
        return(0);
    }

    if (typeMatrice == "dense") {

        string repertoire = "data/matrices2";

        ptrdiff_t optionPosition = find(arguments.begin(), arguments.end(), "-i") - arguments.begin();

        if (optionPosition < arguments.size() - 1) {
            repertoire = argv[optionPosition + 1];
        }

        map<string, string> matrices = trouverMatrices(repertoire);

        if (matrices.empty()) {
            cerr << endl << repertoire << " ne contient pas de matrices (*.txt)" << endl << endl;
        } else {
            genererVisualisationDense(matrices);
        }

    } else if (typeMatrice == "csr") {
        genererVisualisationCsr();
    }
}
