#ifndef CALIB_LIQVAP_H
#define CALIB_LIQVAP_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

// Reading experimental data files
void readLiqVapInput(double &p0, double &ro0, double &c0);

// --- Vapor phase ---
double computecpG(std::vector<double> const& hGexp, std::vector<double> const& ThGexp);
double computeQg(std::vector<double> const& hGexp, std::vector<double> const& ThGexp, double cpG);
double computecvG(std::vector<double> const& vGexp, std::vector<double> const& Texp, std::vector<double> const& psatExp, double cpG);
double computeQprimG(std::vector<double> p, std::vector<double> T, double cpL, double cpG, double cvL, double cvG, double qL, double qG, double pinfL, double bL);

// --- Liquid phase ---
double computeMeanTp(std::vector<double> const& psatExp, std::vector<double> const& Texp, double pinfL);
double computeMeanTp2(std::vector<double> const& psatExp, std::vector<double> const& Texp, double pinfL);
double computeHeatCapDiffL(std::vector<double> const& psatExp, std::vector<double> const& Texp, std::vector<double> const& vLexp, double mvL, double mTp, double pinfL);
double computeDheatCapDiffL(std::vector<double> const& psatExp, std::vector<double> const& Texp, std::vector<double> const& vLexp, double mvL, double mTp, double mTp2, double pinfL);
double computebL(double mvl, double mTp, double diffC);
double computeDbL(double mTp, double mTp2, double diffC, double dDiffC);
double computeCpL(std::vector<double> const& Texp, std::vector<double> const& hLexp, std::vector<double> const& psatExp, double mhL, double mp, double mT, double bL);
double computeDcpL(std::vector<double> const& Texp, std::vector<double> const& psatExp, double mp, double mT, double dbL);
double computeQl(double mhL, double mT, double mp, double cpL, double bL);
double computePinfL(std::vector<double> const& psatExp, std::vector<double> const& Texp, std::vector<double> const& vLexp, std::vector<double> const& hLexp, double p0, double ro0, double c0);

// --- Both phase ---
double computeGammak(double cpk, double cvk);

// --- Theoric curves --- 
void coeffPsatTh(double cpG, double cpL, double cvG, double cvL, double qG, double qL, double qPrimG, double qPrimL, double bG, double bL, double &A, double &B, double &C, double &D, double &E);
double computePsatTh(double A, double B, double C, double D, double E, double pinfL, double T);
double computeThEnthalpy(double cpk, double bk, double qk, double T, double P);
double computeVkTh(double cpk, double cvk, double pinfk, double bk, double T, double P);


#endif // CALIB_LIQVAP_H