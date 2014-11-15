#/!bin/bash
# Honoré Nintunze

echo -e 'Test do.\n'

echo -e '\n\tor est positionné.\n'
echo  '1.On a 1 si toutes commandes vraies'
./do --or "emacs -u phm" "xclock -update 1" xterm
echo $?
echo  '2.On a 1 même si une commande est fausse'
./do --or "emacs -u phm" "xclockfr -update 1" xterm
echo $?
echo  '3.On a 0 si toutes les commandes sont fausses'
./do --or "emacsves -u phm" "xclockfz -update 1" xtermfz
echo $?

echo -e '\n\tor et cc sont positionnés.\n'
echo  "1.On a le résultat 1 si elles sont toutes vraies"
./do --or "emacs -u phm" "xclock -update 1" xterm
echo $?
echo  "1.On a le résultat 1 si une commande est fausse"
./do --or "emacs -u phm" "xclockfr -update 1" xterm
echo $?
echo  '3.On a 0 si toutes les commandes sont fausses'
./do --or "emacsves -u phm" "xclockfz -update 1" xtermfz
echo $?

echo -e '\n\tand est positionné.\n'
echo  '1.On a 1 si toutes commandes vraies'
./do --and "emacs -u phm" "xclock -update 1" xterm
echo $?
echo  '2.On a 0 si une commande est fausse'
./do --and "emacsd -u phm" "xclock -update 1" xterm
echo $?
echo  '3.On a 0 si toutes les commandes sont fausses'
./do --and "emacsves -u phm" "xclockfz -update 1" xtermfz
echo $?

echo -e '\n\tand et cc sont positionnés.\n'
echo  "1.On a le résultat 1 si elles sont toutes vraies"
./do --or "emacs -u phm" "xclock -update 1" xterm
echo $?
echo  "1.On a le résultat 0 si une commande est fausse"
./do --or "emacs -u phm" "xclockfr -update 1" xterm
echo $?
echo  "3.On a 0 si toutes les commandes sont fausses"
./do --or "emacsves -u phm" "xclockfz -update 1" xtermfz
echo $?

echo "---------------------------------------------------"

echo -e '\nFin des tests.\n'

