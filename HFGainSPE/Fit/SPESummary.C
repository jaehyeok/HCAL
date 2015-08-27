#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip> // for setw()

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"

using namespace std;

void SPESummary()
{ 

//Robox Column iDepth iPhi iEta Ped_mean Ped_mean_err Ped_RMS  Ped_RMS_err SPEPeak_RMS SPEPeak_RMS_err Gain Gain_err Normalized_Chi2 MeanPE_fit MeanPE_fit_err

    int Robox;
    int Column;
    int iDepth;
    int iPhi;
    int iEta;
    float Ped_mean;
    float Ped_mean_err;
    float Ped_RMS;
    float Ped_RMS_err;
    float SPEPeak_RMS;
    float SPEPeak_RMS_err;
    float Gain;
    float Gain_err;
    float Normalized_Chi2;
    float MeanPE_fit;
    float MeanPE_fit_err;

    TH1D *h1 = new TH1D("h1","h1",50,0,16);
    TH2D *h2 = new TH2D("h2","h2",24,0,24,36,0,36);
    TH2D *h2_gainsigma = new TH2D("h2_gainsigma","h2_gainsigma",24,0,24,36,0,36);
    TH2D *h2_chi2ndf = new TH2D("h2_chi2ndf","h2_chi2ndf",24,0,24,36,0,36);
    TH2D *h2_depth1 = new TH2D("h2_depth1","h2_depth1",27,0,27,72,0,72);
    TH2D *h2_depth2 = new TH2D("h2_depth2","h2_depth2",27,0,27,72,0,72);

    string line;
    ifstream infile ("SPEconstants_Run_254743_test_mode_1.txt");

    if (infile.is_open())
    {
        while ( infile.good() )
        {
            // get a line from input file
            getline (infile,line); 

            if( line.find("#")!=string::npos ) continue;

            stringstream stream(line);
            stream >> Robox;
            stream >> Column;
            stream >> iDepth;
            stream >> iPhi;
            stream >> iEta;
            stream >> Ped_mean;
            stream >> Ped_mean_err;
            stream >> Ped_RMS;
            stream >> Ped_RMS_err;
            stream >> SPEPeak_RMS;
            stream >> SPEPeak_RMS_err;
            stream >> Gain;
            stream >> Gain_err;
            stream >> Normalized_Chi2;
            stream >> MeanPE_fit; 

            h1->Fill(Gain);
            h2->SetBinContent(Column,Robox,Gain);
            h2_chi2ndf->SetBinContent(Column,Robox,Normalized_Chi2);
            h2_gainsigma->SetBinContent(Column,Robox,Gain_err);
            if(iDepth==1) h2_depth1->SetBinContent(iEta>0?iEta-14:iEta+41,iPhi,Gain);
            if(iDepth==2) h2_depth2->SetBinContent(iEta>0?iEta-14:iEta+41,iPhi,Gain);

            //cout << iDepth << " " << iPhi << " " << iEta << " " << Ped_mean << endl;

            if( !infile.good() ) continue;
        }
    }
    infile.close();

    TCanvas *c = new TCanvas("c","c",1200,800);
    c->Divide(3,2);
    c->cd(1);
    h2->SetMaximum(16);
    h2->SetStats(0);
    h2->Draw("colz");
    c->cd(2);
    h2_chi2ndf->SetStats(0);
    h2_chi2ndf->Draw("colz");
    //c->cd(5);
    //h2_gainsigma->SetMaximum(5);
    //h2_gainsigma->SetStats(0);
    //h2_gainsigma->Draw("colz");
    c->cd(3);
    h1->Draw("hist");
    c->cd(4);
    h2_depth1->SetMaximum(16);
    h2_depth1->SetStats(0);
    h2_depth1->Draw("colz");
    c->cd(5);
    h2_depth2->SetMaximum(16);
    h2_depth2->SetStats(0);
    h2_depth2->Draw("colz");

}
