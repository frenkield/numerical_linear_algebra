import matplotlib.pyplot as plt
import sys
import numpy as np
import re
import math

lignes = sys.stdin.readlines()
lignes = lignes[1:]

jacobi = []
jacobi_preconditionne = []
gauss_seidel = []
gauss_seidel_preconditionne = []
relaxation = []
relaxation_preconditionne = []
gradient_conjugue = []
gradient_conjugue_preconditionne = []

liste_actuelle = jacobi

delimiter = re.compile(" *, *")

for ligne in lignes:

    ligne = ligne.strip()

    if not ligne:
        continue
    elif ligne.startswith("==="):
        break
    elif ligne == "jacobi":
        liste_actuelle = jacobi
        continue
    elif ligne == "jacobi_preconditionne":
        liste_actuelle = jacobi_preconditionne
        continue
    elif ligne == "gauss_seidel":
        liste_actuelle = gauss_seidel
        continue
    elif ligne == "gauss_seidel_preconditionne":
        liste_actuelle = gauss_seidel_preconditionne
        continue
    elif ligne == "relaxation":
        liste_actuelle = relaxation
        continue
    elif ligne == "relaxation_preconditionne":
        liste_actuelle = relaxation_preconditionne
        continue
    elif ligne == "gradient_conjugue":
        liste_actuelle = gradient_conjugue
        continue
    elif ligne == "gradient_conjugue_preconditionne":
        liste_actuelle = gradient_conjugue_preconditionne
        continue

    print(ligne)

    donnees = delimiter.split(ligne.strip())

    liste_actuelle.append([int(donnees[0]), float(donnees[1])])

jacobi = np.array(jacobi)
jacobi_preconditionne = np.array(jacobi_preconditionne)
gauss_seidel = np.array(gauss_seidel)
gauss_seidel_preconditionne = np.array(gauss_seidel_preconditionne)
relaxation = np.array(relaxation)
relaxation_preconditionne = np.array(relaxation_preconditionne)
gradient_conjugue = np.array(gradient_conjugue)
gradient_conjugue_preconditionne = np.array(gradient_conjugue_preconditionne)

plt.plot(jacobi[:, 0], jacobi[:, 1], label = "jacobi")

plt.plot(jacobi_preconditionne[:, 0], jacobi_preconditionne[:, 1],
         label = "jacobi pré")

plt.plot(gauss_seidel[:, 0], gauss_seidel[:, 1], label = "gauss-seidel")

plt.plot(gauss_seidel_preconditionne[:, 0], gauss_seidel_preconditionne[:, 1],
         label = "gauss-seidel pré")

plt.plot(relaxation[:, 0], relaxation[:, 1], label = "relaxation")

plt.plot(relaxation_preconditionne[:, 0], relaxation_preconditionne[:, 1],
         label = "relaxation pré")

plt.plot(gradient_conjugue[:, 0], gradient_conjugue[:, 1],
         label = "gradient conjugue")

plt.plot(gradient_conjugue_preconditionne[:, 0], gradient_conjugue_preconditionne[:, 1],
         label = "gradient conjugue pré")




# plt.plot(jacobi[:, 0], np.log(jacobi[:, 1]), label = "jacobi")
# plt.plot(jacobi_preconditionne[:, 0], np.log(jacobi_preconditionne[:, 1]), label = "jacobi pré")
# plt.plot(gauss_seidel[:, 0], np.log(gauss_seidel[:, 1]), label = "gauss-seidel")
# plt.plot(gauss_seidel_preconditionne[:, 0], np.log(gauss_seidel_preconditionne[:, 1]), label = "gauss-seidel pré")
# plt.plot(relaxation[:, 0], np.log(relaxation[:, 1]), label = "relaxation")
# plt.plot(relaxation_preconditionne[:, 0], np.log(relaxation_preconditionne[:, 1]), label = "relaxation pré")
# plt.plot(gradient_conjugue[:, 0], np.log(gradient_conjugue[:, 1]), label = "gradient conjugue")
# plt.plot(gradient_conjugue_preconditionne[:, 0], np.log(gradient_conjugue_preconditionne[:, 1]), label = "gradient conjugue pré")



plt.yscale('log')
plt.title('Historique Convergence')
plt.legend()

plt.show()
