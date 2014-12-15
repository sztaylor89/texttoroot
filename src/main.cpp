/** \file main.cpp
 * \brief The main driver to convert text file data to ROOT histograms
 * \author S. V. Paulauskas
 * \date November 17, 2014
 */
#include <iostream>
#include <vector>
#include <TFile.h>

#include <TH1D.h>
#include <TH2D.h>

#include "Tokenizer.hpp"

using namespace std;

int main(){
    TFile f("results/077cu-ban4-lower.root", "RECREATE");
    TH1D *histTof = new TH1D("tof", "", 3000, -100, 900);
    TH1D *histBanTof = new TH1D ("banTof", "", 1200, 0, 300);
    TH1D *histQdc = new TH1D("qdc", "", 64000, 0, 32000);
    TH2D *histQdcTof = new TH2D("qdctof", "", 3000, -100, 900, 32000, 0, 32000);

    Tokenizer tokenQdcTof("tof/077cu-testBan1/test00-tofqdc.dat", " ");
    vector<double> fullTof = tokenQdcTof.GetXVals();
    vector<double> qdc = tokenQdcTof.GetYVals();
    if(fullTof.size() != qdc.size())
        cout << "The sizes don't match" << endl;
    for(unsigned int i = 0; i < qdc.size(); i++) {
        histTof->Fill(fullTof.at(i));
        histQdc->Fill(qdc.at(i));
        histQdcTof->Fill(fullTof.at(i), qdc.at(i));
    }

    Tokenizer tokenBanTof("tof/077cu-ban4-lower/077cu-ban4-lower.dat", " ");
    vector<double> banTof = tokenBanTof.GetXVals();
    for(const auto val : banTof)
        histBanTof->Fill(val);

    histTof->Write();
    histQdc->Write();
    histBanTof->Write();
    histQdcTof->Write();
    f.Close();
}
