#include "tools.h"

using namespace std;

// **************************************************

void readExpData(string file, vector<double> &Texp, vector<double> &PsatExp, vector<double> &vGexp, vector<double> &vLexp, vector<double> &hGexp, vector<double> &hLexp, vector<double> &LvExp)
{
    // Purpose : read the experimental data with 7 columns and an ignored header
    ifstream strmIn(file.c_str());
    string line; 
    double dat1, dat2, dat3, dat4, dat5, dat6, dat7;
    if (strmIn) {
        while (getline(strmIn,line)) {
            strmIn >> dat1 >> dat2 >> dat3 >> dat4 >> dat5 >> dat6 >> dat7;
            Texp.push_back(dat1);
            PsatExp.push_back(dat2);
            vGexp.push_back(dat3);
            vLexp.push_back(dat4);
            hGexp.push_back(dat6);
            hLexp.push_back(dat5);
            LvExp.push_back(dat7);
        }
    }
    else {
        cout << "Error : reading experimental data file " << file << ".txt\n"; exit(0);
    }
}

// **************************************************

void writePlotFile(string file, vector<double> &x, vector<double> &y)
{
    // Purpose : write file with two columns 
    ofstream strm(file.c_str());
    for (unsigned int i = 0; i < x.size(); i++) {
        strm << x[i] << " " << y[i] << endl;
    }
}

// **************************************************

double meanValue(vector<double> &tab)
{
    // Purpose : compute the mean value of a vector
    double buf(0.);
    for (unsigned int i = 0; i < tab.size(); i++) {
        buf += tab[i];
    }
    return (buf/tab.size());
}

double meanValue(vector<double> const& tab)
{
    // Purpose : compute the mean value of a vector
    double buf(0.);
    for (unsigned int i = 0; i < tab.size(); i++) {
        buf += tab[i];
    }
    return (buf/tab.size());
}

// **************************************************

double residual(std::vector<double> &tabKnow, std::vector<double> &tabEstimated)
{
    // Purpose : compute the residual of an Ordinary Lest Squares (OLS) procedure
    // Linear fn y=f(x) - vector are y values
    double scr(0.), sct(0.);
    if (tabKnow.size() == tabEstimated.size()) {
        for (unsigned int i = 0; i < tabKnow.size(); i++) {
        scr += (tabKnow[i]-tabEstimated[i])*(tabKnow[i]-tabEstimated[i]);
        sct += (tabKnow[i]-meanValue(tabKnow))*(tabKnow[i]-meanValue(tabKnow)); 
        }
    }
    else {
        cout << "Error : residual can not be computed due to different vector size\n";
    }
    return (1.-(scr/sct));
}