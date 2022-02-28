#include <iostream>
#include <matrice_csr.hpp>
#include <cassert>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <block_matrix.hpp>
#include <gradient_conjugue.hpp>

using namespace std;
typedef vector <Triplet>::iterator TripletIterator;

const int MINRES_MAX_ITERATIONS = 1000;
const double MINRES_TOLERANCE = 0.0001;

// TODO - on fait quoi avec ça ?
const double CG_TOLERANCE = 0.00000000001;

MatriceCSR::MatriceCSR() {
}

MatriceCSR::MatriceCSR(int nr, int nc) {
    this->nr = nr;
    this->nc = nc;
    matriceSource = MatriceCOO(nr, nc);
}

void MatriceCSR::populate() {
    populate(this->matriceSource);
}

void MatriceCSR::populate(MatriceCOO& matriceCoo) {
    populate(matriceCoo.getHeight(), matriceCoo.getWidth(), matriceCoo.getTriplets());
}

void MatriceCSR::populate(int nr, int nc, vector<Triplet>& triplets) {

    assert(nr > 0 && nc > 0);
    this->nr = nr;
    this->nc = nc;

    nombreValeurs = triplets.size();

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(unique(triplets.begin(), triplets.end()), triplets.end());

    // on a bien nettoyé la liste de triplets mais on ne permet pas du tout des doublons !!!
    assert(triplets.size() == nombreValeurs);

    rowStartIndices = vector<int>(nr, 0);
    columIndices = vector<int>(nombreValeurs);
    values = vector<double>(nombreValeurs);

    int columnIndex = 0;

    for (TripletIterator triplet = triplets.begin(); triplet != triplets.end(); ++triplet) {

        int row = (*triplet).i;
        int column = (*triplet).j;
        double value = (*triplet).valeur;

        if (row < nr - 1) {
            rowStartIndices[row + 1] = columnIndex + 1;
        }

        columIndices[columnIndex] = column;
        values[columnIndex++] = value;
    }

    for (int i = 1; i < nr; i++) {
        if (rowStartIndices[i] < rowStartIndices[i - 1]) {
            rowStartIndices[i] = rowStartIndices[i - 1];
        }
    }

    populated = true;
}

MatriceCSR::MatriceCSR(const initializer_list<initializer_list<double>> values) {

    nr = values.size();
    nc = 0;
    int row = 0;
    int column = 0;

    for (auto &line : values) {

        if (nc == 0) {
            nc = line.size();
            matriceSource = MatriceCOO(nr, nc);
        }

        assert(line.size() == nc);

        for (double value : line) {
            matriceSource.set(row, column++, value);
        }

        row++;
        column = 0;
    }

    populate();
}

int MatriceCSR::getHeight() const {
    return nr;
}

int MatriceCSR::getWidth() const {
    return nc;
}

bool MatriceCSR::isSquare() {
    return nr == nc;
}

double MatriceCSR::operator()(int i, int j) const {

    assert(populated && i >= 0 && i < nr && j >= 0 && j < nc);

    double valeur = 0;
    int startIndex = rowStartIndices[i];
    int endIndex = i < nr - 1 ? rowStartIndices[i + 1] : nombreValeurs;

    for (int i = startIndex; i < endIndex; i++) {
        if (columIndices[i] == j) {
            valeur = values[i];
            break;
        }
    }

    return valeur;
}

void MatriceCSR::set(int i, int j, double valeur) {
    assert(!populated);
    matriceSource.set(i, j, valeur);
}

ostream& operator<<(ostream& stream, MatriceCSR const& matrix) {

    assert(matrix.populated);

    for(int i = 0; i < matrix.getHeight(); i++) {
        for (int j = 0; j < matrix.getWidth(); j++) {
            stream << setw(10) << matrix(i, j) << " ";
        }
        stream << endl;
    }

    return stream;
}

void MatriceCSR::MinRes(Vecteur& x, const Vecteur& b) {

    assert(populated);
    x.initialiser(0);

    double tolerance = MINRES_TOLERANCE * sqrt(b.norme());

    Vecteur r = b;
    Vecteur product = Vecteur(b.size());
    int iterations = 0;

    while(iterations++ < MINRES_MAX_ITERATIONS && sqrt(r.norme()) > tolerance) {
        MvProd(r, product);
        double alpha = (r * product) / (product * product);
        x = x + alpha * r;
        MvProd(x, product);
        r = b - product;
    }
}

void MatriceCSR::solveDefaut(Vecteur& x, const Vecteur& b) {
    cg(x, b, CG_TOLERANCE);
}

void MatriceCSR::MvProd(const Vecteur& x, Vecteur& b) {

    assert(populated && nc == x.size() && b.size() == nr);
    b.initialiser(0);

    for (int row = 0; row < nr; row++) {

        int startIndex = rowStartIndices[row];
        int endIndex = row < nr - 1 ? rowStartIndices[row + 1] : nombreValeurs;

        for (int columnIndex = startIndex; columnIndex < endIndex; columnIndex++) {

            int column = columIndices[columnIndex];
            b(row) += x(column) * values[columnIndex];
        }
    }
}

void MatriceCSR::cg(Vecteur &x, const Vecteur &b, double tolerance) {

    assert(populated);
    GradientConjugue<MatriceCSR> gradientConjugue = GradientConjugue<MatriceCSR>();
    gradientConjugue.setTolerance(tolerance);
    gradientConjugue.cg(*this, x, b);

    historiqueResidu = gradientConjugue.getHistoriqueResidu();
}

Vecteur operator*(MatriceCSR& matrice, const Vecteur& vecteur) {
    assert(matrice.populated && matrice.getWidth() == vecteur.size());
    Vecteur resultatVecteur = Vecteur(vecteur.size());
    matrice.MvProd(vecteur, resultatVecteur);
    return resultatVecteur;
}

vector<pair<int, double>> MatriceCSR::getHistoriqueResidu() {
    return historiqueResidu;
}

void MatriceCSR::pcg(Vecteur& x, const Vecteur& b, double tolerance) {
    int l = nr / 2;
    pcg(x, b, tolerance, l, 1);
}

void MatriceCSR::pcg(Vecteur& x, const Vecteur& b, double tolerance, int familleL, int familleR) {

    assert(populated);
    GradientConjugue<MatriceCSR> gradientConjugue = GradientConjugue<MatriceCSR>();
    gradientConjugue.setTolerance(tolerance);
    gradientConjugue.pcg(*this, x, b, familleL, familleR);

    historiqueResidu = gradientConjugue.getHistoriqueResidu();
}

double MatriceCSR::normeVecteurCarre(Vecteur& x) {
    return ((*this) * x) * x;
}

MatriceCSR MatriceCSR::operator()(vector<int> Ir, vector<int> Ic) {

    MatriceCSR extractedMatrix = MatriceCSR(Ir.size(), Ic.size());

    for (int rowIndex = 0; rowIndex < Ir.size(); rowIndex++) {
        for (int columnIndex = 0; columnIndex < Ic.size(); columnIndex++) {
            extractedMatrix.set(rowIndex, columnIndex, operator()(Ir[rowIndex], Ic[columnIndex]));
        }
    }

    extractedMatrix.populate();
    return extractedMatrix;
}

MatriceCSR MatriceCSR::operator+(MatriceCSR &matrice) {
    throw "pas implémnté";
    return MatriceCSR();
}
