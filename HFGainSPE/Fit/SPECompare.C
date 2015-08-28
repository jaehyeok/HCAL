#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip> // for setw()
#include <algorithm> 

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TMathBase.h"

using namespace std;

float Min(float a, float b) { return a <= b ? a : b; }

void SPECompare()
{ 
    //
    // Get jae numbers
    //

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

    TH1D *h1_jae = new TH1D("h1_jae","h1_jae",50,0,240000);
    TH2D *h2_jae = new TH2D("h2_jae","h2_jae",24,0,24,36,0,36);

    string line_jae;
    ifstream infile_jae ("SPEconstants_Run_254743_test_mode_1.txt");

    if (infile_jae.is_open())
    {
        while ( infile_jae.good() )
        {
            // get a line from input file
            getline (infile_jae,line_jae); 

            if( line_jae.find("#")!=string::npos ) continue;

            stringstream stream(line_jae);
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

            h1_jae->Fill(Min((float)Gain*2.78/1.6*10000,(float)(240000-0.0001)));
            h2_jae->SetBinContent(Column,Robox,Gain*2.78/1.6*10000);

            if( !infile_jae.good() ) continue;
        }
    }
    infile_jae.close();

    //
    // Get Katrina's numbers
    //

    //ROBOX   BB    PMT   OV1 Gain OV2 Gain OV1+100
    int ROBOX;
    int BB;
    int PMT;
    float OV1Gain;
    float OV2Gain;
    float OV1plus100Gain;

    TH1D *h1_katrina = new TH1D("h1_katrina","h1_katrina",50,0,240000);
    TH2D *h2_katrina = new TH2D("h2_katrina","h2_katrina",24,0,24,36,0,36);

    string line_katrina;
    ifstream infile_katrina ("Led_Gain_Map_HFP.txt");

    if (infile_katrina.is_open())
    {
        while ( infile_katrina.good() )
        {
            // get a line_katrina from input file
            getline (infile_katrina,line_katrina); 

            if( line_katrina.find("#")!=string::npos ) continue;

            stringstream stream(line_katrina);
            stream >> ROBOX; 
            stream >> BB; 
            stream >> PMT; 
            stream >> OV1Gain; 
            stream >> OV2Gain; 
            stream >> OV1plus100Gain; 

            h1_katrina->Fill(Min((float)OV2Gain,(float)(240000-0.0001)));
            h2_katrina->SetBinContent((BB-1)*8+PMT,ROBOX,OV2Gain);

            if( !infile_katrina.good() ) continue;
        }
    }
    infile_katrina.close();

    // Difference 
    TH2D* h2_diff = (TH2D*) h2_jae->Clone("h2_diff"); 
    h2_diff->Add(h2_katrina,-1);
    h2_diff->Divide(h2_katrina);
    h2_diff->SetTitle("jae-katrina/katrina");
    // Difference 1D
    TH1D *h1_diff = new TH1D("h1_diff","h1_diff",50,-1,1); 
    for(int x=1; x<=24; x++)  
    { 
        for(int y=1; y<=36; y++)  
        { 
            h1_diff->Fill(h2_diff->GetBinContent(x,y));
            if(h2_jae->GetBinContent(x,y)==0) h2_diff->SetBinContent(x,y,-1.1);
        } 
    }
    h1_diff->SetTitle("jae-katrina/katrina");


    TCanvas *c = new TCanvas("c","c",1200,800);
    c->Divide(3,2);
    c->cd(1);
    h2_jae->SetMinimum(0);
    h2_jae->SetMaximum(240000);
    h2_jae->SetStats(0);
    h2_jae->Draw("colz");
    c->cd(2);
    h2_katrina->SetMinimum(0);
    h2_katrina->SetMaximum(240000);
    h2_katrina->SetStats(0);
    h2_katrina->Draw("colz");
    c->cd(3);
    h2_diff->SetMinimum(-1);
    h2_diff->SetMaximum(1);
    h2_diff->SetStats(0);
    h2_diff->Draw("colz");
    c->cd(4); 
    h1_jae->Draw("hist");
    c->cd(5); 
    h1_katrina->Draw("hist");
    c->cd(6); 
    h1_diff->Draw("hist");

    c->Print("~/www/tmp/SPEcompare.pdf");
}
