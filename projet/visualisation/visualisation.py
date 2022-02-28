import sys
import json
import getopt


# ========================================================================================

output_filename = ""
json_data_filename = ""

try:
    opts, args = getopt.getopt(sys.argv[1:], "d:i:o:")

except getopt.GetoptError as err:
    print(err)
    sys.exit(2)

for option, value in opts:
    if option == "-o":
        output_filename = value
    elif option == "-d":
        json_data_filename = value

# comme ça on peut générer des images sur des machines sans écran
# il faut faire cet import avant l'import de matplotlib
if output_filename:
    import matplotlib as mpl
    mpl.use('Agg')

import matplotlib.pyplot as plt
from matplotlib.pyplot import figure

# ========================================================================================

def generateTitle(configuration, method):

    title = ""

    if configuration["matrixType"] == "dense":
        title = "Matrice Dense"
    else:
        title = "Matrice CSR (Laplacien)"

    if method == "cg":
        title += " - Méthode CG"
    else:
        title += " - Méthode PCG"

    if method == "pcg" and configuration["subtitle"] != "":
        title += "\n" + item["subtitle"]

    return title

# ========================================================================================

def fetch_visualisation_data():

    if json_data_filename:
        with open(json_data_filename, encoding='utf-8') as json_file:
            json_data = json.load(json_file)
            return sorted(json_data.items())
    else:
        print("chargement des donnees json depuis stdin...")
        json_data = json.load(sys.stdin)
        return sorted(json_data.items())

# ========================================================================================

visualisation_data = fetch_visualisation_data()

figure(num=None, figsize=(11, 5), dpi=120)
plt.subplots_adjust(left=0.1, right=0.95, wspace=0.3)

plt.subplot(121)

for key, item in visualisation_data:

    if key == "configuration":
        title = generateTitle(item, "cg")
        plt.title(title)

    elif item["method"] == "cg":
        plt.plot(item["residu"], label=item["label"])

plt.legend(loc="best")
plt.xlabel("Iteration")
plt.ylabel("$\log_{10}(\|r\|)$")
plt.yscale("log")

# ========================================================================================

plt.subplot(122)

for key, item in visualisation_data:

    if key == "configuration":
        title = generateTitle(item, "pcg")
        plt.title(title)

    elif item["method"] == "pcg":
        plt.plot(item["residu"], label=item["label"])

plt.legend(loc="best")
plt.xlabel("Iteration")
plt.ylabel("$\log_{10}(\|r\|)$")
plt.yscale("log")

# ========================================================================================

if output_filename:
    print("stockage de l'image dans", output_filename)
    plt.savefig(output_filename)

else:
    plt.show()
