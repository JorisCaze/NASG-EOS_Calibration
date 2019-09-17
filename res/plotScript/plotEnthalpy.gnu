# Gnuplot plot file to plot hk(T) with k = L, G

reset
set style data lp

set key bottom right
set xlabel "Temperature T (k)"
set ylabel "Enthalpy (kJ/kg)"

set title "hg"
plot "hG_th.txt" u 1:($2*0.001) title "Theoric", "../input/expData.txt" u 1:($5*0.001) title "Experimental"
pause(-1)

set title "hl"
plot "hL_th.txt" u 1:($2*0.001) title "Theoric", "../input/expData.txt" u 1:($6*0.001) title "Experimental"
pause(-1)