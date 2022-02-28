import matplotlib.pyplot as plt
import sys
import numpy as np
import re
import math

lignes = sys.stdin.readlines()
lignes = lignes[1:]

jacobi = []
gauss_seidel = []
relaxation = []
gradient_conjugue = []

liste_actuelle = jacobi

delimiter = re.compile(" *, *")

for ligne in lignes:

    ligne = ligne.strip()

    if not ligne:
        continue
    elif ligne.startswith("==="):
        break
    elif ligne == "gauss_seidel":
        liste_actuelle = gauss_seidel
        continue
    elif ligne == "relaxation":
        liste_actuelle = relaxation
        continue
    elif ligne == "gradient_conjugue":
        liste_actuelle = gradient_conjugue
        continue

    print(ligne)

    donnees = delimiter.split(ligne.strip())

    liste_actuelle.append([int(donnees[0]), float(donnees[1])])

# print(jacobi)
# print(gauss_seidel)
# print(relaxation)

jacobi = np.array(jacobi)
gauss_seidel = np.array(gauss_seidel)
relaxation = np.array(relaxation)
gradient_conjugue = np.array(gradient_conjugue)

plt.plot(jacobi[:, 0], np.log(jacobi[:, 1]))
plt.plot(gauss_seidel[:, 0], np.log(gauss_seidel[:, 1]))
plt.plot(relaxation[:, 0], np.log(relaxation[:, 1]))
plt.plot(gradient_conjugue[:, 0], np.log(gradient_conjugue[:, 1]))

#plt.yscale('log')
plt.title('Historique Convergence')

plt.show()
