#include <iostream>
#include <string>

#include "tools.h"
#include "calib_liq-vap.h"

using namespace std;

int main()
{
    displayHeader();
    cout << "\n*** Noble-Abel Stiffened Gas EOS Liquid/vapor calibration ***\n\n";

    string run("res/");
    double p0, ro0, c0;
    double cpL(0.), qL(0.), pinfL(0.), cvL(0.), gammaL(0.), qPrimL(0.), bL(0.);
    double cpG(0.), qG(0.), pinfG(0.), cvG(0.), gammaG(0.), qPrimG(0.), bG(0.);
    double mvL(0.), mT(0.), mp(0.), mhL(0.), mTp(0.), diffCl(0.);
    vector<double> Texp, psatExp, vGexp, vLexp, hGexp, hLexp, LvExp; 

    readLiqVapInput(p0,ro0,c0);
    readExpData("input/expData.txt",Texp,psatExp,vGexp,vLexp,hGexp,hLexp,LvExp);

    mvL = meanValue(vLexp);
    mT = meanValue(Texp);
    mp = meanValue(psatExp);
    mhL = meanValue(hLexp);

    // // --- Liquid phase ---
    pinfL = computePinfL(psatExp,Texp,vLexp,hLexp,p0,ro0,c0);
    mTp = computeMeanTp(psatExp,Texp,pinfL);
    diffCl = computeHeatCapDiffL(psatExp,Texp,vLexp,mvL,mTp,pinfL);
    bL = computebL(mvL,mTp,diffCl);
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
    cout << "--- Liquid (L) ---\n";
    cout << "cpL    (J.kg-1.K-1)  : " << cpL << endl;
    cout << "qL     (J.kg-1)      : " << qL << endl;
    cout << "pinfL  (Pa)          : " << pinfL << endl;
    cout << "cvL    (J.kg-1.K-1)  : " << cvL << endl;
    cout << "gammaL (-)           : " << gammaL << endl;
    cout << "q'L    (J.kg-1)      : " << qPrimL << endl;
    cout << "bL     (m3/kg)       : " << bL << endl;
    cout << "\n";

    cout << "--- Gas (G) ---\n";
    cout << "cpG    (J.kg-1.K-1)  : " << cpG << endl;
    cout << "qG     (J.kg-1)      : " << qG << endl;
    cout << "pinfG  (Pa)          : " << pinfG << endl;
    cout << "cvG    (J.kg-1.K-1)  : " << cvG << endl;
    cout << "gammaG (-)           : " << gammaG << endl;
    cout << "q'G    (J.kg-1)      : " << qPrimG << endl;
    cout << "bG     (m3/kg)       : " << bG << endl;
    cout << "\n";
    
    // --- Write theoric curves --- 
    vector<double> hLth, hGth, LvTh, PsatTh, vlTh, vgTh;
    double A(0.),B(0.),C(0.),D(0.),E(0.);
    
    coeffPsatTh(cpG,cpL,cvG,cvL,qG,qL,qPrimG,qPrimL,bG,bL,A,B,C,D,E);

    for (unsigned int i = 0; i < Texp.size(); i++) {
        PsatTh.push_back(computePsatTh(A,B,C,D,E,pinfL,Texp[i]));
        hLth.push_back(computeThEnthalpy(cpL,bL,qL,Texp[i],PsatTh[i]));
        hGth.push_back(computeThEnthalpy(cpG,bG,qG,Texp[i],PsatTh[i]));
        LvTh.push_back(hGth[i]-hLth[i]);
        vlTh.push_back(computeVkTh(cpL,cvL,pinfL,bL,Texp[i],PsatTh[i]));
        vgTh.push_back(computeVkTh(cpG,cvG,pinfG,bG,Texp[i],PsatTh[i]));
    }
    writePlotFile("res/Psat_th.txt",Texp,PsatTh);
    writePlotFile("res/hL_th.txt",Texp,hLth);
    writePlotFile("res/hG_th.txt",Texp,hGth);
    writePlotFile("res/Lv_th.txt",Texp,LvTh);
    writePlotFile("res/vL_th.txt",Texp,vlTh);
    writePlotFile("res/vG_th.txt",Texp,vgTh);

    return 0;
}
