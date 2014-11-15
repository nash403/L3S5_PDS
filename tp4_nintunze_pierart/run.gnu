set title "Temps d'execution de mcat en fonction de la taille du buffer"
set logscale x
set xlabel "taille buffer(en octets)"
set logscale y
set ylabel "temps d'execution(en sesc)"
set style data linespoints
plot "mcat-tm.dat" using 1:2 title "real time", \
     "mcat-tm.dat" using 1:3 title "user time", \
     "mcat-tm.dat" using 1:4 title "sys time"
pause -1  "Hit return to continue"
