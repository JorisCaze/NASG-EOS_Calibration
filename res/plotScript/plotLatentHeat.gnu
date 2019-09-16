# Gnuplot plot file to plot Lv(T)

reset
set style data lp

set key bottom left
set xlabel "Temperature T (k)"
set title "Latent Heat Lv (kJ/kg)"

plot "Lv_th.txt" u 1:($2*0.001) title "Theoric", "../input/Liq-vap/Lv_exp.txt" u 1:($2*0.001) title "Experimental"
pause(-1)