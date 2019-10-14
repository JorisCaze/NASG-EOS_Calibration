# Gnuplot plot file to plot vk(T) with k = L, G

reset
# set style data lp
set style line 1 lw 3 lc rgb "blue"

set xlabel "Temperature T (K)"
set ylabel "Specific volume (m3/kg)"

set key top right
set title "v_g"
plot "vG_th.txt" u 1:2 title "Theoric" w l ls 1, "../input/expData.txt" u 1:3 title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
pause(-1)

set key top left
set title "v_l"
plot "vL_th.txt" u 1:2 title "Theoric" w l ls 1, "../input/expData.txt" u 1:4 title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
pause(-1)