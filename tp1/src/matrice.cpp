#include <matrice.hpp>
#include <cassert>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

const static double ERREUR_MAX = 0.000001;

Matrice::Matrice(int taille) {

    // TODO - assurer que toute soit initialiser en 0

    this->taille = taille;
    coefficients.resize(taille * taille, 0);
}

Matrice::Matrice(const Matrice &matrice) {
    taille = matrice.size();
    coefficients = matrice.coefficients;
}

Matrice::Matrice(initializer_list<initializer_list<double>> valeurs) : Matrice(valeurs.size()) {

    int index = 0;

    for (auto &ligne : valeurs) {
        for (double valeur : ligne) {
            coefficients[index++] = valeur;
        }
    }
}

int Matrice::size() const {
    return taille;
}

int Matrice::calculIndex(int i, int j) const {
    int index = i * taille + j;

    // TODO - utiliser unsigned partout ?
    assert(index >= 0 && (unsigned)index < coefficients.size());

    return index;
}

bool Matrice::operator==(Matrice& matrice) {

    return std::equal(coefficients.begin(), coefficients.end(), matrice.coefficients.begin(),
            [](double valeur1, double valeur2) {

        if (valeur2 == 0) {
            return valeur1 < ERREUR_MAX;
        } else {
            return fabs((valeur1 - valeur2) / valeur1) < ERREUR_MAX;
        }
    });
}

double &Matrice::operator()(int i, int j) {
    return coefficients[calculIndex(i, j)];
}

double Matrice::operator()(int i, int j) const {
    return coefficients[calculIndex(i, j)];
}

Matrice Matrice::operator+(Matrice& matrice) {

    assert(size() == matrice.size());
    Matrice sommeMatrice = Matrice(size());

    for(unsigned i = 0; i < matrice.coefficients.size(); i++) {
        sommeMatrice.coefficients[i] = coefficients[i] + matrice.coefficients[i];
    }

    return sommeMatrice;
}

Matrice Matrice::operator-(Matrice& matrice) {

    assert(size() == matrice.size());
    Matrice matriceSomme = Matrice(size());

    for(unsigned i = 0; i < matrice.coefficients.size(); i++) {
        matriceSomme.coefficients[i] = coefficients[i] - matrice.coefficients[i];
    }

    return matriceSomme;
}

Matrice Matrice::operator*(Matrice& matrice) {

    assert(size() == matrice.size());
    Matrice matriceProduit = Matrice(size());

    for(int i = 0; i < matrice.size(); i++) {

        for (int j = 0; j < matrice.size(); j++) {

            for (int index = 0; index < matrice.size(); index++) {
                matriceProduit(i, j) += this->operator()(i, index) * matrice(index, j);
            }
        }
    }

    return matriceProduit;
}

Matrice Matrice::operator*(double alpha) {

    Matrice nouveauMatrice = Matrice(size());

    for(unsigned i = 0; i < nouveauMatrice.coefficients.size(); i++) {
        nouveauMatrice.coefficients[i] = coefficients[i] * alpha;
    }

    return nouveauMatrice;
}

Vecteur operator*(const Matrice& matrice, const Vecteur& vecteur) {

    Vecteur resultatVecteur = Vecteur(vecteur.size());

    for(int j = 0; j < matrice.size(); j++) {
        for (int k = 0; k < matrice.size(); k++) {
            resultatVecteur(j) += matrice(j, k) * vecteur(k);
        }
    }

    return resultatVecteur;
}

ostream& operator<<(ostream& stream, Matrice const& matrice) {

    for(int i = 0; i < matrice.size(); i++) {
        for (int j = 0; j < matrice.size(); j++) {
            stream << setw(10) << matrice(i, j) << " ";
        }
        stream << endl;
    }

    return stream;
}

void Matrice::initialiser(double* valeurs) {
    for(unsigned i = 0; i < coefficients.size(); i++) {
        coefficients[i] = valeurs[i];
    }
}

void Matrice::decomposeLU() {

    assert(typeDecomposition == PasDecompose);

    for(int i = 0; i < size(); i++) {

        // calcul de S
        for(int row = i + 1; row < size(); row++) {
            for(int column = i + 1; column < size(); column++) {

                (*this)(row, column) = (*this)(row, column)
                    - (*this)(row, i) * (*this)(i, column) / (*this)(i, i);
            }
        }

        // L10 = A10 / U00
        for(int row = i + 1; row < size(); row++) {
            (*this)(row, i) = (*this)(row, i) / (*this)(i, i);
        }
    }

    typeDecomposition = LU;
}

void Matrice::decomposeCholesky() {

    assert(typeDecomposition == PasDecompose);

    for(int i = 0; i < size(); i++) {

        // calcul de S
        for(int row = i + 1; row < size(); row++) {
            for(int column = row; column < size(); column++) {

                (*this)(row, column) = (*this)(row, column)
                    - (*this)(row, i) * (*this)(i, column) / (*this)(i, i);

                (*this)(column, row) = (*this)(row, column);
            }
        }

        (*this)(i, i) = sqrt((*this)(i, i));

        // L10 (et L10T) = A10 / L00
        for(int row = i + 1; row < size(); row++) {
            (*this)(row, i) = (*this)(i, row) = (*this)(row, i) / (*this)(i, i);
        }
    }

    typeDecomposition = Cholesky;
}

Matrice Matrice::getDecompositionLower() {

    assert(typeDecomposition != PasDecompose);
    Matrice lower = Matrice(*this);

    for(int i = 0; i < taille; i++) {

        if (typeDecomposition == LU) {
            lower(i, i) = 1;
        }

        for(int j = i + 1; j < taille; j++) {
            lower(i, j) = 0;
        }
    }

    return lower;
}

Matrice Matrice::getDecompositionUpper() {

    assert(typeDecomposition != PasDecompose);
    Matrice upper = Matrice(*this);

    for(int i = 0; i < taille; i++) {
        for(int j = 0; j < i; j++) {
            upper(i, j) = 0;
        }
    }

    return upper;
}

Matrice Matrice::genererMatriceAleatoire(int taille) {

    typedef vector <double>::iterator VectorIterator;
    Matrice matrice = Matrice(taille);

    uniform_real_distribution<double> unif(-10, 10);
    default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());

    for (VectorIterator it = matrice.coefficients.begin(); it != matrice.coefficients.end(); ++it) {
        *it = unif(randomEngine);
    }

    return matrice;
}

Matrice Matrice::genererMatriceSPDAleatoire(int taille) {

    Matrice matriceAleatoire = genererMatriceAleatoire(taille);
    Matrice matriceAleatoireTranspose = matriceAleatoire.transpose();

    Matrice matriceDiagonale = Matrice(taille);
    uniform_real_distribution<double> unif(0.1, 10);
    default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());

    for (int row = 0; row < matriceDiagonale.size(); ++row) {
        matriceDiagonale(row, row) = unif(randomEngine);
    }

    return matriceAleatoire * matriceDiagonale * matriceAleatoireTranspose;
}

Matrice Matrice::genererMatriceInferieureAleatoire(int taille) {

    Matrice matrice = Matrice(taille);
    uniform_real_distribution<double> unif(-10, 10);
    default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());

    for (int row = 0; row < matrice.size(); ++row) {
        matrice(row, row) = 1;
        for (int column = 0; column < row; ++column) {
            matrice(row, column) = unif(randomEngine);
        }
    }

    return matrice;
}

Matrice Matrice::genererMatriceSuperieureAleatoire(int taille) {

    Matrice matrice = Matrice(taille);
    uniform_real_distribution<double> unif(-10, 10);
    default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());

    for (int row = 0; row < matrice.size(); ++row) {
        for (int column = row; column < matrice.size(); ++column) {
            matrice(row, column) = unif(randomEngine);
        }
    }

    return matrice;
}

Matrice Matrice::transpose() {

    Matrice matrice = Matrice(taille);

    for (int row = 0; row < matrice.size(); ++row) {
        for (int column = 0; column < matrice.size(); ++column) {
            matrice(row, column) = (*this)(column, row);
            matrice(column, row) = (*this)(row, column);
        }
    }

    return matrice;
}

Matrice Matrice::getDiagonal() const {
    Matrice diagonal = Matrice(size());
    for (int i = 0; i < size(); ++i) {
        diagonal(i, i) = operator()(i, i);
    }
    return diagonal;
}

Matrice Matrice::getDiagonalInverse() const {
    Matrice diagonal = getDiagonal();
    for (int i = 0; i < size(); ++i) {
        diagonal(i, i) = 1 / diagonal(i, i);
    }
    return diagonal;
}
