#!/bin/bash

if [ "$1" = "dense" ]
then
    make visualisation
    bin/visualisation ${@:1} | python3 visualisation/visualisation.py ${@:2}

elif [ "$1" = "csr" ]
then
    make visualisation
    bin/visualisation ${@:1} | python3 visualisation/visualisation.py ${@:2}

else
    echo
    echo "Usage:"
    echo "    ./visualisation.sh dense [-i repertoire_matrices] [-o fichier_image]"
    echo "    ./visualisation.sh csr [-o fichier_image]"
    echo

fi
