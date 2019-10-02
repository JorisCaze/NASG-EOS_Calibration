# Gnuplot eps plot all files ready for a LaTex document

# ----------

reset
set size 1, 1
set terminal eps color enhanced font "14"
set style line 1 lw 3 lc rgb "blue"

set key bottom right
set xlabel "Temperature T (K)"
set ylabel "Enthalpy (kJ/kg)"

set output "hG.eps"
set title "h_g"
plot "hG_th.txt" u 1:($2*0.001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($5*0.001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"

set output "hL.eps"
set title "h_l"
plot "hL_th.txt" u 1:($2*0.001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($6*0.001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"

# ----------

reset
set size 1, 1
set terminal eps color enhanced font "14"
set style line 1 lw 3 lc rgb "blue"

set key bottom left
set xlabel "Temperature T (K)"
set title "Latent Heat Lv (kJ/kg)"

set output "Lv.eps"
plot "Lv_th.txt" u 1:($2*0.001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($7*0.001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"

# ----------

reset
set size 1, 1
set terminal eps color enhanced font "14"
set style line 1 lw 3 lc rgb "blue"

set key bottom right
set xlabel "Temperature T (K)"
set ylabel "Specific volume (m3/kg)"

set output "vG.eps"
set title "v_g"
plot "vG_th.txt" u 1:2 title "Theoric" w l ls 1, "../input/expData.txt" u 1:3 title "Experimental" w points pt 1 ps 1.2 lc rgb "red"

set output "vL.eps"
set title "v_l"
plot "vL_th.txt" u 1:2 title "Theoric" w l ls 1, "../input/expData.txt" u 1:4 title "Experimental" w points pt 1 ps 1.2 lc rgb "red"

# ----------

reset
set size 1, 1
set terminal eps color enhanced font "14"
set style line 1 lw 3 lc rgb "blue"

set key autotitle columnhead
set key bottom left
set xlabel "Temperature T (K)"
set title "Saturated pressure Psat (bar)"

set output "Psat.eps"
plot "Psat_th.txt" u 1:($2*0.00001) title "Theoric" w l ls 1, "../input/expData.txt" u 1:($2*0.00001) title "Experimental" w points pt 1 ps 1.2 lc rgb "red"
