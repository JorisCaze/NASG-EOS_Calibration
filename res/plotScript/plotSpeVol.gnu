# Gnuplot plot file to plot vk(T) with k = L, G

reset
set style data lp

set key bottom right
set xlabel "Temperature T (k)"
set ylabel "Specific volume (m3/kg)"

set title "vg"
plot "vG_th.txt" u 1:2 title "Theoric", "../input/Liq-vap/vG_exp.txt" u 1:2 title "Experimental"
pause(-1)

set title "vl"
plot "vL_th.txt" u 1:2 title "Theoric", "../input/Liq-vap/vL_exp.txt" u 1:2 title "Experimental"
pause(-1)