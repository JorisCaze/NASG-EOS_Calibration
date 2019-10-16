#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void displayHeader();

// --- Read/Write files --- 
void readExpData(std::string file, std::vector<double> &Texp, std::vector<double> &PsatExp, std::vector<double> &vGexp, std::vector<double> &vLexp, std::vector<double> &hGexp, std::vector<double> &hLexp, std::vector<double> &LvExp);
void readFile(std::string const &file, std::vector<double> &tab_x, std::vector<double> &tab_y);
void writePlotFile(std::string file, std::vector<double> &x, std::vector<double> &y);
void writeResults(double cpL, double qL, double pinfL, double cvL, double gammaL, double qPrimL, double bL, double cpG, double qG, double pinfG, double cvG, double gammaG, double qPrimG, double bG);

// Least Square Method tools
double meanValue(std::vector<double> &tab);
double meanValue(std::vector<double> const& tab);
double residual(std::vector<double> &tabKnow, std::vector<double> &tabEstimated);

#endif // TOOLS_H