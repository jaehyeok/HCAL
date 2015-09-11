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
#include "TColor.h"
#include "TStyle.h"

using namespace std;

float Min(float a, float b) { return a <= b ? a : b; }

void SPECompare()
{ 
    // Palette Color scheme -------------------------------------------
    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs] = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs] = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    // ----------------------------------------------------------------
    
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
    ifstream infile_jae ("SPEconstants_Run_254743_test_mode_1_NoFix2sigma.txt");

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
    // Get kathrina's numbers
    //

    //ROBOX   BB    PMT   OV1 Gain OV2 Gain OV1+100
    int ROBOX;
    int BB;
    int PMT;
    float OV1Gain;
    float OV2Gain;
    float OV1plus100Gain;

    TH1D *h1_kathrina = new TH1D("h1_kathrina","h1_kathrina",50,0,240000);
    TH2D *h2_kathrina = new TH2D("h2_kathrina","h2_kathrina",24,0,24,36,0,36);

    string line_kathrina;
    ifstream infile_kathrina ("PMTGainDB/Led_Gain_Map_HFP.txt");

    if (infile_kathrina.is_open())
    {
        while ( infile_kathrina.good() )
        {
            // get a line_kathrina from input file
            getline (infile_kathrina,line_kathrina); 

            if( line_kathrina.find("#")!=string::npos ) continue;

            stringstream stream(line_kathrina);
            stream >> ROBOX; 
            stream >> BB; 
            stream >> PMT; 
            stream >> OV1Gain; 
            stream >> OV2Gain; 
            stream >> OV1plus100Gain; 

            h1_kathrina->Fill(Min((float)OV2Gain,(float)(240000-0.0001)));
            h2_kathrina->SetBinContent((BB-1)*8+PMT,ROBOX,OV2Gain);

            if( !infile_kathrina.good() ) continue;
        }
    }
    infile_kathrina.close();

    // Difference 
    TH2D* h2_diff = (TH2D*) h2_jae->Clone("h2_diff"); 
    h2_diff->Add(h2_kathrina,-1);
    h2_diff->Divide(h2_kathrina);
    h2_diff->SetTitle("jae-kathrina/kathrina");
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
    h1_diff->SetTitle("jae-kathrina/kathrina");


    TCanvas *c = new TCanvas("c","c",1800,800);
    c->Divide(3,2);
    c->cd(1);
    h2_jae->SetMinimum(0);
    h2_jae->SetMaximum(240000);
    h2_jae->SetStats(0);
    h2_jae->Draw("colz");
    c->cd(2);
    h2_kathrina->SetMinimum(0);
    h2_kathrina->SetMaximum(240000);
    h2_kathrina->SetStats(0);
    h2_kathrina->Draw("colz");
    c->cd(3);
    h2_diff->SetMinimum(-1);
    h2_diff->SetMaximum(1);
    h2_diff->SetStats(0);
    h2_diff->Draw("colz");
    c->cd(4); 
    h1_jae->Draw("hist");
    c->cd(5); 
    h1_kathrina->Draw("hist");
    c->cd(6); 
    h1_diff->Draw("hist");
    c->Print("SPEcompare.pdf");
  
    // 
    TH2D *h2_scatter = new TH2D("h2_scatter","h2_scatter",100,0,240000,100,0,240000);
    TCanvas *cscatter = new TCanvas("cscatter","cscatter",600,400);
    for(int x=1; x<=24; x++)  
    { 
        for(int y=1; y<=36; y++)  
        { 
            if(h2_jae->GetBinContent(x,y)!=0) h2_scatter->Fill(h2_jae->GetBinContent(x,y),h2_kathrina->GetBinContent(x,y));
        } 
    }
    cscatter->cd(1);  
    h2_scatter->SetStats(0);
    h2_scatter->SetTitle("Gain (x:Jae y:Kathrina)");
    h2_scatter->SetXTitle("Jae");
    h2_scatter->SetYTitle("Kathrina");
    h2_scatter->Draw("colz");
    cscatter->Print("SPEscatter.pdf");

}
