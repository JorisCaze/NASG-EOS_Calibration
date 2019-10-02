# Gnuplot plot file to plot Psat(T)

reset
# set style data lp
set style line 1 lw 3 lc rgb "blue"

set key autotitle columnhead
set key bottom left
set xlabel "Temperature T (K)"
set title "Saturated pressure Psat (bar)"

plot "Psat_th.txt" u 1:($2*0.00001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($2*0.00001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
pause(-1)