#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <iomanip> // for setw()

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TColor.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TMath.h"

using namespace std;

void SPESummaryOne(const char* infilename="SPEconstants_Run_254743_test_mode_1_Fix3sigma.txt")
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

    // Check if the fit is with fixing Ped peak
    TString outfilename = infilename;
    outfilename.ReplaceAll("txt","pdf");
    bool FitWOFixPed = false;
    if(outfilename.Contains("NoFix")) FitWOFixPed=true;

    // Gain
    TH1D *h1                    = new TH1D("h1",            "Gain",         50,0,16);
    TH1D *h1_highchi2           = new TH1D("h1_highchi2",   "h1_highchi2",  50,0,16);
    TH1D *h1_lowchi2            = new TH1D("h1_lowchi2",    "h1_lowchi2",   50,0,16);
    TH1D *h1_gainsigma          = new TH1D("h1_gainsigma",  "Gain RMS",     50,2.5,5.5);
    TH1D *h1_gainsigma_highchi2 = new TH1D("h1_gainsigma_highchi2","h1_gainsigma_highchi2",50,2.5,5.5);
    TH1D *h1_gainsigma_lowchi2  = new TH1D("h1_gainsigma_lowchi2","h1_gainsigma_lowchi2",50,2.5,5.5);
    TH2D *h2                    = new TH2D("h2",            "Gain", 24,0.5,24.5,36,0.5,36.5); 
    // Other info 
    TH2D *h2_ped                = new TH2D("h2_ped","Pedestal",24,0.5,24.5,36,0.5,36.5);
    TH2D *h2_gainsigma          = new TH2D("h2_gainsigma","h2_gainsigma",24,0.5,24.5,36,0.5,36.5);
    TH2D *h2_chi2ndf            = new TH2D("h2_chi2ndf","#chi^{2}/ndf",24,0.5,24.5,36,0.5,36.5);
    TH2D *h2_depth1             = new TH2D("h2_depth1","h2_depth1",27,0,27,72,0,72);
    TH2D *h2_depth2             = new TH2D("h2_depth2","h2_depth2",27,0,27,72,0,72);
    TH1D *h1_chi2ndf            = new TH1D("h1_chi2ndf","#chi^{2}/ndf",50,0,FitWOFixPed?25:200);
    TH1D *h1_chi2ndf_highchi2   = new TH1D("h1_chi2ndf_highchi2","h1_chi2ndf_highchi2",50,0,FitWOFixPed?25:200);
    TH1D *h1_chi2ndf_lowchi2    = new TH1D("h1_chi2ndf_lowchi2","h1_chi2ndf_lowchi2",50,0,FitWOFixPed?25:200);
    TH1D *h1_ped                = new TH1D("h1_ped","Pedestal",50,8,13);
    TH1D *h1_ped_highchi2       = new TH1D("h1_ped_highchi2","h1_ped_highchi2",50,8,13);
    TH1D *h1_ped_lowchi2        = new TH1D("h1_ped_lowchi2","h1_ped_lowchi2",50,8,13);
    TH1D *h1_pedsigma           = new TH1D("h1_pedsigma","Pedestal RMS",50,1.5,3.5);
    TH1D *h1_pedsigma_highchi2  = new TH1D("h1_pedsigma_highchi2","h1_pedsigma_highchi2",50,1.5,3.5);
    TH1D *h1_pedsigma_lowchi2   = new TH1D("h1_pedsigma_lowchi2","h1_pedsigma_lowchi2",50,1.5,3.5);

    string line;
    ifstream infile (infilename);

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
            h1_gainsigma->Fill(SPEPeak_RMS);
            h2->SetBinContent(Column,Robox,Gain);
            h2_chi2ndf->SetBinContent(Column,Robox,Normalized_Chi2);
            h2_gainsigma->SetBinContent(Column,Robox,Gain_err);
            h2_ped->SetBinContent(Column,Robox,Ped_mean);
            if(iDepth==1) h2_depth1->SetBinContent(iEta>0?iEta-14:iEta+41,iPhi,Gain);
            if(iDepth==2) h2_depth2->SetBinContent(iEta>0?iEta-14:iEta+41,iPhi,Gain);
            h1_chi2ndf->Fill(TMath::Min((Float_t)Normalized_Chi2,(Float_t)199.999));
            h1_ped->Fill(Ped_mean);
            h1_pedsigma->Fill(Ped_RMS); 
            if((Robox>=10 && Robox<=12) || (Robox>=16 && Robox<=18)) 
            { 
                h1_gainsigma_highchi2->Fill(SPEPeak_RMS);
                h1_highchi2->Fill(Gain);
                h1_ped_highchi2->Fill(Ped_mean);
                h1_pedsigma_highchi2->Fill(Ped_RMS); 
                h1_chi2ndf_highchi2->Fill(TMath::Min((Float_t)Normalized_Chi2,(Float_t)199.999)); 
            } 
            else 
            { 
                h1_gainsigma_lowchi2->Fill(SPEPeak_RMS);
                h1_lowchi2->Fill(Gain);
                h1_ped_lowchi2->Fill(Ped_mean);
                h1_pedsigma_lowchi2->Fill(Ped_RMS); 
                h1_chi2ndf_lowchi2->Fill(TMath::Min((Float_t)Normalized_Chi2,(Float_t)199.999)); 
            }

            //cout << iDepth << " " << iPhi << " " << iEta << " " << Ped_mean << endl;

            if( !infile.good() ) continue;
        }
    }
    infile.close();

    TCanvas *c = new TCanvas("c","c",1800,1200);
    c->Divide(3,3);
    c->cd(1);
    h2_ped->SetMaximum(20);
    h2_ped->SetStats(0);
    h2_ped->Draw("colz");
    c->cd(2);
    h2->SetMaximum(16);
    h2->SetStats(0);
    h2->Draw("colz");
    c->cd(3);
    h2_chi2ndf->SetStats(0);
    h2_chi2ndf->Draw("colz");
    c->cd(4);
    h1_ped->SetLineColor(kBlack);
    h1_ped->Draw("hist"); 
    h1_ped_highchi2->SetLineColor(kRed);
    h1_ped_highchi2->Draw("hist same");
    h1_ped_lowchi2->SetLineColor(kBlue);
    h1_ped_lowchi2->Draw("hist same");
    c->cd(5);
    h1->SetLineColor(kBlack);
    h1->Draw("hist"); 
    h1_highchi2->SetLineColor(kRed);
    h1_highchi2->Draw("hist same");
    h1_lowchi2->SetLineColor(kBlue);
    h1_lowchi2->Draw("hist same");
    c->cd(6); 
    h1_chi2ndf->SetLineColor(kBlack);
    h1_chi2ndf->Draw("hist");
    h1_chi2ndf_highchi2->SetLineColor(kRed);
    h1_chi2ndf_highchi2->Draw("hist same");
    h1_chi2ndf_lowchi2->SetLineColor(kBlue);
    h1_chi2ndf_lowchi2->Draw("hist same");
    c->cd(7);
    h1_pedsigma->SetLineColor(kBlack);
    h1_pedsigma->Draw("hist"); 
    h1_pedsigma_highchi2->SetLineColor(kRed);
    h1_pedsigma_highchi2->Draw("hist same");
    h1_pedsigma_lowchi2->SetLineColor(kBlue);
    h1_pedsigma_lowchi2->Draw("hist same");
    c->cd(8);
    h1_gainsigma->SetLineColor(kBlack);
    h1_gainsigma->Draw("hist"); 
    h1_gainsigma_highchi2->SetLineColor(kRed);
    h1_gainsigma_highchi2->Draw("hist same");
    h1_gainsigma_lowchi2->SetLineColor(kBlue);
    h1_gainsigma_lowchi2->Draw("hist same");
    c->cd(9);
    TLegend *l1 = new TLegend(0.1, 0.3, 0.8, 0.7);
    l1->SetBorderSize(0);
    l1->SetFillStyle(0);
    l1->SetFillColor(kWhite);
    l1->SetLineColor(kWhite);
    l1->SetShadowColor(kWhite);
    l1->SetTextSize(0.06);
    l1->AddEntry(h1_gainsigma,          " All Roboxes",                 "l");
    l1->AddEntry(h1_gainsigma_highchi2, " Roboxes=10-12,16-18",         "l");
    l1->AddEntry(h1_gainsigma_highchi2, " (high #chi^{2}/ndf Roboxes)",  "");
    l1->AddEntry(h1_gainsigma_lowchi2,  " Roboxes=1-9,13-15,19-36",     "l");
    l1->AddEntry(h1_gainsigma_lowchi2,  " (low #chi^{2}/ndf Roboxes)",   "");
    l1->Draw();
    
    c->Print(outfilename);
} 

void SPESummary()
{
    SPESummaryOne("SPEconstants_Run_254743_test_mode_1_Fix3sigma.txt");
    SPESummaryOne("SPEconstants_Run_254743_test_mode_1_Fix2sigma.txt");
    SPESummaryOne("SPEconstants_Run_254743_test_mode_1_NoFix2sigma.txt");
}

