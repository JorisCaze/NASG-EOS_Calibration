# Gnuplot plot file to plot Psat(T)

reset
set style data lp

set key autotitle columnhead
set key bottom left
set xlabel "Temperature T (K)"
set title "Saturated pressure Psat (bar)"

plot "Psat_th.txt" u 1:($2*0.00001) title "Theoric", "../input/expData.txt" u 1:($2*0.00001) title "Experimental"
pause(-1)