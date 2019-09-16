#include <iostream>
#include <string>

#include "tools.h"
#include "calib_liq-vap.h"

using namespace std;

int main()
{
    cout << "*** Noble-Abel Stiffened Gas EOS Liquid/vapor calibration ***\n\n";

    string run("res/");
    double p0, ro0, c0;
    double cpL, qL, pinfL, cvL, gammaL, qPrimL, bL;
    double cpG, qG, pinfG, cvG, gammaG, qPrimG, bG;
    double mvL, mT, mp, mhL, diffCl;
    vector<double> Texp, psatExp, vGexp, vLexp, hLexp, hGexp, LvExp; 

    readLiqVapInput(p0,ro0,c0);
    readExpData("input/expData.txt",Texp,psatExp,vGexp,vLexp,hLexp,hGexp,LvExp);

    mvL = meanValue(vLexp);
    mT = meanValue(Texp);
    mp = meanValue(psatExp);
    mhL = meanValue(hLexp);

    // --- Liquid phase ---
    pinfL = computePinfL(psatExp,Texp,vLexp,hLexp,p0,ro0,c0);
    diffCl = computeHeatCapDiffL(psatExp,Texp,vLexp,mvL,mT,mp,pinfL);
    bL = computebL(mvL,mT,mp,diffCl);
    cpL = computeCpL(Texp,hLexp,psatExp,mhL,mp,mT,bL);
    cvL = cpL - diffCl;
    gammaL = computeGammak(cpL,cvL);
    qL = computeQl(mhL,mT,mp,cpL,bL);
    qPrimL = 0.; // Ref. energy convention

    // --- Vapor phase ---
    cpG = computecpG(hGexp,Texp);
    qG = computeQg(hGexp,Texp,cpG);
    cvG = computecvG(vGexp,Texp,psatExp,cpG);
    gammaG = computeGammak(cpG,cvG);
    pinfG = 0.;  // Ideal Gas
    bG = 0.;     // Ideal Gas
    qPrimG = computeQprimG(psatExp,Texp,cpL,cpG,cvL,cvG,qL,qG,pinfL,bL);

    // --- Results --- 
    cout << "-- Liquid (L) ---\n";
    cout << "cpL    (J.kg-1.K-1)  : " << cpL << endl;
    cout << "qL     (J.kg-1)      : " << qL << endl;
    cout << "pinfL  (Pa)          : " << pinfL << endl;
    cout << "cvL    (J.kg-1.K-1)  : " << cvL << endl;
    cout << "gammaL (-)           : " << gammaL << endl;
    cout << "q'L    (J.kg-1)      : " << qPrimL << endl;

    cout << "\n";

    cout << "-- Gas (G) ---\n";
    cout << "cpG    (J.kg-1.K-1)  : " << cpG << endl;
    cout << "qG     (J.kg-1)      : " << qG << endl;
    cout << "pinfG  (Pa)          : " << pinfG << endl;
    cout << "cvG    (J.kg-1.K-1)  : " << cvG << endl;
    cout << "gammaG (-)           : " << gammaG << endl;
    cout << "q'G    (J.kg-1)      : " << qPrimG << endl;
    
    // --- Write theoric curves --- 
    vector<double> Tth, hLth, hGth, LvTh, PsatTh, vlTh, vgTh;
    double A(0.),B(0.),C(0.),D(0.), E(0.);
    
    coeffPsatTh(cpG,cpL,cvG,cvL,qG,qL,qPrimG,qPrimL,bG,bL,A,B,C,D,E);

    for (unsigned int i = 0; i < Texp.size(); i++) {
        // PsatTh.push_back(computePsatTh(A,B,C,D,pinfG,pinfL,Texp[i]));
        hLth.push_back(computeThEnthalpy(cpL,bL,qL,Texp[i],PsatTh[i]));
        hGth.push_back(computeThEnthalpy(cpG,bG,qG,Texp[i],PsatTh[i]));
        LvTh.push_back(hGth[i]-hLth[i]);
        vlTh.push_back(computeVkTh(cpL,cvL,pinfL,bL,Texp[i],PsatTh[i]));
        vgTh.push_back(computeVkTh(cpG,cvG,pinfG,bG,Texp[i],PsatTh[i]));
    }
    writePlotFile("res/Psat_th.txt",Tth,PsatTh);
    writePlotFile("res/hL_th.txt",Tth,hLth);
    writePlotFile("res/hG_th.txt",Tth,hGth);
    writePlotFile("res/Lv_th.txt",Tth,LvTh);
    writePlotFile("res/vL_th.txt",Tth,vlTh);
    writePlotFile("res/vG_th.txt",Tth,vgTh);

    return 0;
}