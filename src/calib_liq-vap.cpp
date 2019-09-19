#include "calib_liq-vap.h"
#include "tools.h"

using namespace std;

void readLiqVapInput(double &p0, double &ro0, double &c0)
{
    ifstream strmRefStates("input/refState.txt");
    string line("");
    if (strmRefStates) {
        for (int i=1; i<6; i++) {getline(strmRefStates,line);}
        p0 = stod(line);
        getline(strmRefStates,line); getline(strmRefStates,line);
        ro0 = stod(line);
        getline(strmRefStates,line); getline(strmRefStates,line);
        c0 = stod(line);
    }
    else {
        cout << "Error : reading refState.txt file\n"; exit(0);
    }
}

// **************************************************

double computecpG(vector<double> const& hGexp, vector<double> const& ThGexp)
{
    // Purpose : compute heat capacity at constant pressure of vapor phase with LSM
    // More : the exp. data hG(T) is used
    // See eq. (50)
    double mHg, mThg, num(0.), den(0.);
    mHg = meanValue(hGexp);
    mThg = meanValue(ThGexp);
    for (unsigned int i = 0; i < hGexp.size(); i++) {
        num += ThGexp[i]*(hGexp[i]-mHg);
        den += ThGexp[i]*(ThGexp[i]-mThg);
    }
    return num/den;
}

// **************************************************

double computeQg(vector<double> const& hGexp, vector<double> const& ThGexp, double cpG)
{
    // Purpose : compute formation energy of vapor phase 
    // See eq. (51)
    double mHg, mThg;
    mHg = meanValue(hGexp);
    mThg = meanValue(ThGexp);
    return (mHg-cpG*mThg);
}

// **************************************************

double computecvG(vector<double> const& vGexp, vector<double> const& Texp, vector<double> const& psatExp, double cpG)
{
    // Purpose : commpute heat capacity at constant volum of vapor phase with LSM
    // More : vGexp, Texp and psatExp are concording experimental points
    // See eq. (55)
    double num(0.), den(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        num += vGexp[i]*(Texp[i]/psatExp[i]);
        den += (Texp[i]/psatExp[i])*(Texp[i]/psatExp[i]);
    }
    return (cpG - num/den);
}

// **************************************************

double computeQprimG(vector<double> p, vector<double> T, double cpL, double cpG, double cvL, double cvG, double qL, double qG, double pinfL, double bL)
{
    // Purpose : compute the vapor entropy constant qPrimG with LSM
    // See equation (72) 
    double A,B,C,D,E,sum(0.);
    B = (qL-qG)/(cpG-cvG);
    C = (cpG-cpL)/(cpG-cvG);
    D = (cpL-cvL)/(cpG-cvG);
    E = bL/(cpG-cvG);
    for (unsigned int i = 0; i < p.size(); i++) {
        sum += log(p[i])-(B+E*p[i])/T[i] - C*log(T[i]) - D*log(p[i]+pinfL);
    }
    A = sum/p.size();
    return (A*(cpG-cvG)+cpG-cpL);
}

// **************************************************

double computeGammak(double cpk, double cvk)
{
    // Purpose : compute adiabatic index
    // See equation (25) 
    return cpk/cvk;
}

// **************************************************

double computeMeanTp(vector<double> const& psatExp, vector<double> const& Texp, double pinfL)
{
    // Purpose : compute the mean value seen in (64) and (65)
    double mtp(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        mtp += Texp[i]/(psatExp[i]+pinfL);  
    }
    mtp /= Texp.size(); 
    return mtp;
}

double computeMeanTp2(vector<double> const& psatExp, vector<double> const& Texp, double pinfL)
{
    // Purpose : compute a variation of the mean value seen in (64) and (65)
    double mtp(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        mtp += Texp[i]/((psatExp[i]+pinfL)*(psatExp[i]+pinfL));  
    }
    mtp /= Texp.size(); 
    return mtp;
}

double computeHeatCapDiffL(vector<double> const& psatExp, vector<double> const& Texp, vector<double> const& vLexp, double mvL, double mTp, double pinfL)
{
    // Purpose : compute heat capacity cpL - cvL of liquid phase for pinfL iterative process with LSM 
    // More : this fn is also used to solve eq. (68) with Newton-Raphson 
    // Details : input values m'x' are the mean of the corresponding vector 'x'
    // See eq. (64)  
    double num(0.), den(0.), bf(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        bf = Texp[i]/(psatExp[i]+pinfL);
        num += bf*(vLexp[i]-mvL);
        den += bf*(bf-mTp);
    }
    return num/den;
}

double computeDHeatCapDiffL(vector<double> const& psatExp, vector<double> const& Texp, vector<double> const& vLexp, double mvL, double mTp, double mTp2, double pinfL)
{
    // Purpose : compute pinfL derivative of fn computeHeatCapDiffL() for computePinfL Newton-Raphson process
    double m1(0.), m2(0.), m3(0.), m4(0.), bf1(0.), bf2(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        bf1 = Texp[i]/(psatExp[i]+pinfL);
        bf2 = bf1/(psatExp[i]+pinfL);
        m1 += -bf2*(vLexp[i]*mvL);
        m2 += bf1*(bf1 - (1./Texp.size())*mTp);
        m3 += bf1*(vLexp[i]-mvL);
        m4 += -bf2*(bf1-mTp)+bf1*(bf2+mTp2);
    }
    return (m1*m2-m3*m4)/(m2*m2);
}

// **************************************************

double computebL(double mvl, double mTp, double diffC)
{
    // Purpose : compute bl parameter for liquid phase
    // More : input values mvl, mT and mp are (m)ean values and diffC = cpL - cvL
    // Details : input values m'x' are the mean of the corresponding vector 'x'
    // See eq. (65)
    return (mvl-diffC*mTp);
}

double computeDbL(double mTp, double mTp2, double diffC, double dDiffC)
{
    // Purpose : compute pinfL derivative of fn computebL() for computePinfL Newton-Raphson process
    return (-dDiffC*mTp + diffC*mTp2);
}

// **************************************************

double computeCpL(vector<double> const& Texp, vector<double> const& hLexp, vector<double> const& psatExp, double mhL, double mp, double mT, double bL)
{
    // Purpose : compute heat cap. liquid phase at p = cst with LSM
    // More : this fn is used to solve eq. (68) with Newton-Raphson 
    // Details : input values m'x' are the mean of the corresponding vector 'x'
    // See eq. (60)
    double num1(0.), num2(0.), num(0.), den(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        num1 += Texp[i]*(hLexp[i]-mhL);
        num2 += Texp[i]*(psatExp[i]-mp);
        den += Texp[i]*(Texp[i]-mT);
    }
    num = num1 - bL*num2; 
    return num/den;
}

double computeDcpL(vector<double> const& Texp, vector<double> const& psatExp, double mp, double mT, double dbL)
{
    // Purpose : compute pinfL derivative fn of computeCpL() for computePinfL Newton-Raphson process
    double s1(0.), s2(0.);
    for (unsigned int i = 0; i < Texp.size(); i++) {
        s1 += Texp[i]*(psatExp[i]-mp);
        s2 += Texp[i]*(Texp[i]-mT);
    }
    return -dbL*(s1/s2);
}

// **************************************************

double computeQl(double mhL, double mT, double mp, double cpL, double bL)
{
    // Purpose : compute liquid heat cap. at p = cst with mean experimental point values
    // Details : input values m'x' are the mean of the corresponding vector 'x'
    // See eq. (61)   
    return (mhL-cpL*mT-bL*mp);
}

// **************************************************

double computePinfL(vector<double> const& psatExp, vector<double> const& Texp, vector<double> const& vLexp, vector<double> const& hLexp, double p0, double ro0, double c0)
{
    // Purpose : compute pinfL parameter of liquid phase using the Newton-Raphson procedure
    // More : liquid reference state and experimental data are used
    // See eq. (68)
    double fp, dfp, dfp1, dfp2, pinf1(1.e5), pinf2(0.), err(1.);
    double mp, mT, mvL, mhL, mTp, mTp2;
    double diffC, bL, cpL, dDiffC, dbL, dcpL;
    int count(0);

    mp = meanValue(psatExp);
    mT = meanValue(Texp);
    mvL = meanValue(vLexp);
    mhL = meanValue(hLexp);

    while (err > 1.e-5 && count < 50) {
        mTp = computeMeanTp(psatExp,Texp,pinf1);
        mTp2 = computeMeanTp2(psatExp,Texp,pinf1);

        diffC = computeHeatCapDiffL(psatExp,Texp,vLexp,mvL,mTp,pinf1);
        bL = computebL(mvL,mTp,diffC);
        cpL = computeCpL(Texp,hLexp,psatExp,mhL,mp,mT,bL);
        
        dDiffC = computeDHeatCapDiffL(psatExp,Texp,vLexp,mvL,mTp,mTp2,pinf1);
        dbL = computeDbL(mTp,mTp2,diffC,dDiffC); 
        dcpL = computeDcpL(Texp,psatExp,mp,mT,dbL); 
        
        dfp1 = -ro0*dbL;
        dfp2 = (dDiffC*cpL-diffC*dcpL)/(cpL*cpL);

        fp = p0 + pinf1 - (1.-diffC/cpL)*ro0*c0*c0*(1.-bL*ro0);
        dfp = 1. - ro0*c0*c0*dfp1 + dfp2*ro0*c0*c0*(1.-bL*ro0) + (diffC/cpL)*ro0*c0*c0*dfp1;

        pinf2 = pinf1 - fp/dfp;
        err = fabs(pinf2-pinf1)/(0.5*(pinf1+pinf2));
        pinf1 = pinf2;
        count++;
        if (count >= 50) {
            cout << "Warning : newton-raphson of Psat(T) function not converged\n"; exit(0);
        }
    }
    cout << count;
    // if (pinf2 < 1.e-6)
    //     return 0.;
    // else 
        return pinf1;
}

// **************************************************

void coeffPsatTh(double cpG, double cpL, double cvG, double cvL, double qG, double qL, double qPrimG, double qPrimL, double bG, double bL, double &A, double &B, double &C, double &D, double &E)
{
    // Purpose : compute coeff. of theoric saturation curve Psat(T)
    // See eq. (41)
    A = (cpL-cpG+qPrimG-qPrimL)/(cpG-cvG);
    B = (qL-qG)/(cpG-cvG);
    C = (cpG-cpL)/(cpG-cvG);
    D = (cpL-cvL)/(cpG-cvG);
    E = (bL-bG)/(cpG-cvG);
}

double computePsatTh(double A, double B, double C, double D, double E, double pinfL, double T)
{
    // Purpose : compute saturated pressure Psat at a given temperature
    // See eq. (41), fp is obtained with exp((41))
    // More : Newton-Raphson algo. is used
    double fp, dfp, p1(1.e5), p2(0.), err(1.), k(0.);
    int count(0);

    while (err > 1.e-5 && count < 50) {
        k = exp(A+B/T+C*log(T));
        fp = p1 - k*exp(E*p1/T)*pow((p1+pinfL),D);
        dfp = 1. - k*exp(E*p1/T)*((E/T)*pow((p1+pinfL),D) + D*pow((p1+pinfL),(D-1.)));
        p2 = p1 - fp/dfp;
        err = fabs(p2-p1)/(0.5*(p1+p2));
        p1 = p2;
        count++;
        if (count >= 50) 
            cout << "Warning : newton-raphson of Psat(T) function not converged\n";
    }
    if (p2 < 1.e-6)
        return 0.;
    else
        return p2;
}

double computeThEnthalpy(double cpk, double bk, double qk, double T, double P)
{
    // Purpose : compute phasic theoric enthalpy 
    // See eq. (36)
    return (cpk*T+bk*P+qk);
}

double computeVkTh(double cpk, double cvk, double pinfk, double bk, double T, double P)
{
    // Purpose : compute theoric specific vol. of phase k
    // See eq. (35) 
    return (((cpk-cvk)*T)/(P+pinfk)+bk);
}


