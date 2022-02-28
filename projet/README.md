=====================================================================

4M053 - Calcul scientifique pour les grands systèmes linéaires
Projet 2018/2019

David Frenkiel
27/04/2019

=====================================================================

Genérér l'exécutable des tests unitaires et les lancer :

    make test
    bin/test

Notez que les tests unitaires utilisent le framework, Catch2 :

    https://github.com/catchorg/Catch2

Catch2 fichier include :

    incude/outils/catch.hpp

=====================================================================

Genérér l'exécutable de la visualisation et le lancer en un seul étape :

Matrice dense :

    ./visualisation.sh dense

Matrice CSR :

    ./visualisation.sh csr

Matrice dense avec des matrices quelconques situés dans le répertoire spécifié :

    ./visualisation.sh dense -i [répertoire_matrices]

Par exemple,

    ./visualisation.sh dense -i data/matrices1

Génerér l'image de la visualisation et la sauvegarder dans [fichier_image] :

    ./visualisation.sh dense -o [fichier_image]

Ou :

    ./visualisation.sh csr -o [fichier_image]

=====================================================================

Genérér l'exécutable de la visualisation à la main :

    make visualisation

Genérér les données de la visualisation :

Matrice dense :

    bin/visualisation dense [-i répertoire_matrices]

Matrice CSR :

    bin/visualisation csr

=====================================================================

Visualiser les données à la main :

    bin/visualisation dense [-i répertoire_matrices] | python3 visualisation/visualisation.py [-o fichier_image]

Ou pour la matrice dense :

    bin/visualisation csr | python3 visualisation/visualisation.py [-o fichier_image]

Sauvegarder les données et afficher la visualisation séparément :

    bin/visualisation dense [-i répertoire_matrices] > donnees_dense.json
    python3 visualisation/visualisation.py -d donnees_dense.json [-o fichier_image]

Ou pour la matrice CSR :

    bin/visualisation csr > donnees_csr.json
    python3 visualisation/visualisation.py -d donnees_csr.json [-o fichier_image]

=====================================================================

Question 1 :

    include/dense_matrix.hpp
    src/dense_matrix.cpp
    test/test_dense_matrix.cpp

Question 2 :

    include/block.hpp
    src/block.cpp
    test/test_block.cpp

Question 3 :

    include/block_matrix.hpp
    src/block_matrix.cpp
    test/test_block_matrix.cpp

Question 4 :

    src/block_matrix.cpp : generateMatrixVectors()
    test/test_block_matrix.cpp : ligne 129

Question 5 :

    src/dense_matrix.cpp : operator() - ligne 394
    test/test_dense_matrix.cpp : ligne 299

Question 6 :

    src/block_matrix.cpp : Extract() - lignes 162, 172
    test/test_block_matrix.cpp : ligne 154

Question 7 :

    src/block.cpp : MvProdInv() - ligne 154
    test/test_block.cpp : ligne 153

    src/block_matrix.cpp : MvProdInv() - lignes 200
    test/test_block_matrix.cpp : lignes 176, 200, 246

Question 8 :

    src/gradient_conjugue.cpp : pcg() - ligne 73

    src/dense_matrix.cpp : pcg() - ligne 365, 374
    test/test_dense_matrix.cpp : ligne 312

Question 9 :

    src/visualisation/visualisation_main.cpp
    visualisation/visualisation.py

Question subsidiaire :

    include/triplet.hpp
    src/triple.cpp
    test_triplet.cpp

    include/matrice_coo.hpp
    src/matrice_coo.cpp
    test/test_matrice_coo.cpp

    include/matrice_csr.hpp
    src/matrice_csr.cpp
    test/test_matrice_csr.cpp

    src/visualisation/visualisation_main.cpp
    visualisation/visualisation.py
