import matplotlib.pyplot as plt
import sys
import numpy as np
import re
import math

lignes = sys.stdin.readlines()
lignes = lignes[1:]

taille = []
cholesky = []
lu = []

delimiter = re.compile(" *, *")

for ligne in lignes:
    donnees = delimiter.split(ligne.strip())

    taille.append(math.log(float(donnees[0])))

#    cholesky.append(float(donnees[1]))
#    lu.append(float(donnees[2]))

    cholesky.append(math.log(float(donnees[1])))
    lu.append(math.log(float(donnees[2])))

#    cholesky.append(float(donnees[1]) ** (1/3))
#    lu.append(float(donnees[2]) ** (1/3))


plt.plot(taille, cholesky)
plt.plot(taille, lu)

#plt.yscale('log')
plt.title('vitesse cholesky et lu')

plt.show()
