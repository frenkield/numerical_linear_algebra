#include <vecteur.hpp>
#include <assert.h>
#include <random>
#include <chrono>
#include <cmath>

using namespace std;

const static double ERREUR_MAX = 0.000001;

Vecteur::Vecteur() {
}

Vecteur::Vecteur(int taille) {
    coefficients.resize(taille, 0);
}

Vecteur::Vecteur(const Vecteur &vecteur) {
    coefficients = vecteur.coefficients;
}

Vecteur::Vecteur(initializer_list<double> valeurs) : coefficients(valeurs) {
}

Vecteur::Vecteur(const vector<double>& coefficients) {
    this->coefficients = coefficients;
}

void Vecteur::initialiser(double valeur) {
    fill(coefficients.begin(), coefficients.end(), valeur);
}

int Vecteur::size() const {
    return coefficients.size();
}

vector<double> Vecteur::getCoefficients() {
    return coefficients;
}

double & Vecteur::operator()(int index) {
    assert(index >= 0 && (unsigned)index < coefficients.size());
    return coefficients[index];
}

double Vecteur::operator()(int index) const {
    assert(index >= 0 && (unsigned)index < coefficients.size());
    return coefficients[index];
}

ostream& operator<<(ostream& stream, Vecteur const& vecteur) {

    for(int j = 0; j < vecteur.size(); j++) {
        stream << vecteur(j) << endl;
    }

    return stream;
}

Vecteur Vecteur::genererVecteurAleatoire(int taille) {

    typedef vector<double>::iterator VectorIterator;
    Vecteur vecteur = Vecteur(taille);

    std::uniform_real_distribution<double> unif(-10, 10);
    default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());

    for(VectorIterator it = vecteur.coefficients.begin(); it != vecteur.coefficients.end(); ++it) {
        *it = unif(randomEngine);
    }

    return vecteur;
}

bool Vecteur::operator==(const Vecteur& vecteur) const {
    return operator==(vecteur.coefficients);
//    return std::equal(coefficients.begin(), coefficients.end(), vecteur.coefficients.begin(),
//        [](double valeur1, double valeur2) {
//
//            if (valeur2 == 0) {
//                return valeur1 < ERREUR_MAX;
//            } else {
//                return fabs((valeur1 - valeur2) / valeur1) < ERREUR_MAX;
//            }
//        });
}

bool Vecteur::operator==(const vector<double> &vect) const {

    return std::equal(coefficients.begin(), coefficients.end(), vect.begin(),
        [](double valeur1, double valeur2) {

          if (valeur2 == 0) {
              return valeur1 < ERREUR_MAX;
          } else {
              return fabs((valeur1 - valeur2) / valeur1) < ERREUR_MAX;
          }
    });
}

double Vecteur::norme() const {
    return sqrt(normeCarre());
}

double Vecteur::normeCarre() const {
    double norme = 0;
    for(unsigned i = 0; i < coefficients.size(); i++) {
        norme += pow(coefficients[i], 2);
    }
    return norme;
}

Vecteur Vecteur::operator+(const Vecteur& vecteur) {

    assert(size() == vecteur.size());
    Vecteur sommeVecteur = Vecteur(size());

    for(int i = 0; i < vecteur.size(); i++) {
        sommeVecteur(i) = coefficients[i] + vecteur(i);
    }

    return sommeVecteur;
}

Vecteur Vecteur::operator+(const Vecteur&& vecteur) {
    return operator+(vecteur);
}

Vecteur Vecteur::operator-(const Vecteur& vecteur) const {

    assert(size() == vecteur.size());
    Vecteur sommeVecteur = Vecteur(size());

    for(int i = 0; i < vecteur.size(); i++) {
        sommeVecteur(i) = coefficients[i] - vecteur(i);
    }

    return sommeVecteur;
}

Vecteur Vecteur::operator-(const Vecteur&& vecteur) const {
    return operator-(vecteur);
}

double operator*(const Vecteur& vecteur1, const Vecteur& vecteur2) {
    assert(vecteur1.size() == vecteur2.size());
    double produitScalaire = 0;
    for(int i = 0; i < vecteur1.size(); i++) {
        produitScalaire += vecteur1(i) * vecteur2(i);
    }
    return produitScalaire;
}

double operator*(const Vecteur& vecteur1, const Vecteur&& vecteur2) {
    return vecteur1 * vecteur2;
}

Vecteur operator*(const Vecteur& vecteur, const double alpha) {

    Vecteur resultatVecteur = Vecteur(vecteur.size());

    for(int i = 0; i < resultatVecteur.size(); i++) {
        resultatVecteur(i) = vecteur.coefficients[i] * alpha;
    }

    return resultatVecteur;
}

Vecteur operator*(const double alpha, const Vecteur& vecteur) {
    return vecteur * alpha;
}

Vecteur operator*(const Vecteur&& vecteur, const double alpha) {
    return vecteur * alpha;
}

Vecteur operator*(const double alpha, const Vecteur&& vecteur) {
    return vecteur * alpha;
}


