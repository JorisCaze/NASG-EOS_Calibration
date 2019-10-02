#!/bin/bash

# Run all gnuplot files for liquid and its vapor calibration

gnuplot plotScript/plotEnthalpy.gnu
gnuplot plotScript/plotLatentHeat.gnu
gnuplot plotScript/plotSpeVol.gnu
gnuplot plotScript/plotPsat.gnu

gnuplot plotScript/epsPlotAll.gnu

exit 1
