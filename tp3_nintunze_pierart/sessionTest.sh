#/!bin/bash
# Honoré Nintunze et Valentin Pierart

echo -e 'Test : tail simpliste sans argument affiche par défaut les 10 dernières lignes:\n\n'
./mtail1 tailSimpliste.c

echo "------------------------------------------------------------------------------------"

echo -e 'Test : tail simpliste affiche le bon nombre de ligne:\n\n'
./mtail1 tailSimpliste.c 3

echo "------------------------------------------------------------------------------------"

echo -e 'Test : tail efficace sans argument affiche par défaut les 10 dernières lignes:\n\n'
./mtail3 tailEfficace.c

echo "------------------------------------------------------------------------------------"

echo -e 'Test : tail efficace affiche le bon nombre de ligne:\n\n'
./mtail3 tailSimpliste.c 16

echo "------------------------------------------------------------------------------------"

echo -e '\nFin des tests.\n'

