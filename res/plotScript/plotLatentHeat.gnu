# Gnuplot plot file to plot Lv(T)

reset
# set style data lp
set style line 1 lw 3 lc rgb "blue"

set key bottom left
set xlabel "Temperature T (K)"
set title "Latent Heat Lv (kJ/kg)"

plot "Lv_th.txt" u 1:($2*0.001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($7*0.001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
pause(-1)