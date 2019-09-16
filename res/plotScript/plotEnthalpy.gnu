# Gnuplot plot file to plot hk(T) with k = L, G

reset
set style data lp

set key bottom right
set xlabel "Temperature T (k)"
set ylabel "Enthalpy (kJ/kg)"

set title "hg"
plot "hG_th.txt" u 1:($2*0.001) title "Theoric", "../input/Liq-vap/hG_exp.txt" u 1:($2*0.001) title "Experimental"
pause(-1)

set title "hl"
plot "hL_th.txt" u 1:($2*0.001) title "Theoric", "../input/Liq-vap/hL_exp.txt" u 1:($2*0.001) title "Experimental"
pause(-1)