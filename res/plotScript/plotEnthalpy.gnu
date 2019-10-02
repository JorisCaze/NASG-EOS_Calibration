# Gnuplot plot file to plot hk(T) with k = L, G

reset
# set style data lp
set style line 1 lw 3 lc rgb "blue"

set key bottom right
set xlabel "Temperature T (K)"
set ylabel "Enthalpy (kJ/kg)"

set title "h_g"
plot "hG_th.txt" u 1:($2*0.001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($5*0.001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
pause(-1)

set title "h_l"
plot "hL_th.txt" u 1:($2*0.001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($6*0.001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
pause(-1)