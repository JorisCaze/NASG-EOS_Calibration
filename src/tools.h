#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// --- Read/Write files --- 
void readExpData(std::string file, std::vector<double> &Texp, std::vector<double> &PsatExp, std::vector<double> &vGexp, std::vector<double> &vLexp, std::vector<double> &hLexp, std::vector<double> &hGexp, std::vector<double> &LvExp);
void writePlotFile(std::string file, std::vector<double> &x, std::vector<double> &y);

// Least Square Method tools
double meanValue(std::vector<double> &tab);
double meanValue(std::vector<double> const& tab);
double residual(std::vector<double> &tabKnow, std::vector<double> &tabEstimated);

#endif // TOOLS_H