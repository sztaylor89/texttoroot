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
//    TFile f("results/test.root", "RECREATE");
//    TH1D *tof = new TH1D("tof", "", 6000, -1000, 1000
//                         );
//    TH1D *qdc = new TH1D("qdc", "", 32000, 0, 16000);
//    TH2D *qdctof = new TH2D("qdctof", "", 4500, -500, 1000, 32000, 0, 32000);

    Tokenizer token("data/077cu-testBan1/test00.dat", " ");
    vector<double> xVals = token.GetXVals();
    vector<double> yVals = token.GetYVals();

//    for(unsigned int i = 0; i < yVals.size(); i++) {
//        tof->Fill(xVals.at(i));
//        qdc->Fill(yVals.at(i));
//        qdctof->Fill(xVals.at(i), yVals.at(i));
//    }

//    tof->Write();
//    qdc->Write();
//    qdctof->Write();
//    f.Close();
}
