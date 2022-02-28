#include <outils/catch.hpp>
#include <ctime>
#include <matrice_laplacienne.hpp>
#include <solveurs_directs.hpp>

using namespace std;

TEST_CASE("vitesse des decompositions LU et Cholesky des Matrices",
          "[vitesse_decomposition_lu_cholesky]" ) {

    SECTION("tester la vitesse des décomposition LU et Choleksy avec une matrice laplacienne") {

        // TODO - mets tout ça sous exercices

//        clock_t start, end;
//        int taille = 50;
//
////        cout << "taille, temps_cholesky, temps_lu" << endl;
//
//        while (taille < 0) {
//
//            MatriceLaplacienne matrice = MatriceLaplacienne(taille);
//
//            start = clock();
//            matrice.decomposeCholesky();
//            end = clock();
//
//            double temps_cholesky = static_cast<double>(end - start) / CLOCKS_PER_SEC;
//
//            // ===================================================
//
//            matrice = MatriceLaplacienne(taille);
//
//            start = clock();
//            matrice.decomposeLU();
//            end = clock();
//
//            double temps_lu = static_cast<double>(end - start) / CLOCKS_PER_SEC;
//
//            cout << taille << ", " << temps_cholesky << ", " << temps_lu << endl;
//
//            taille += 50;
//        }
    }
}
