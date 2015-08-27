#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TArrow.h"
#include "Math/ProbFunc.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

#include "SPEFit_UXC_Ana_V2.h"
#include "Util.C"

// filname : output file name 
// pmode : pedestal mode 
// mode :  
void SPEFit_UXC_Ana_V2(int run=254743, TString filname="test", bool pmode=false, int mode=1)
{

    /*mode 1: TH1F * HistoSum[2][72][13];             // integral of TS 2-5
      mode 2: TH1F * HistoFullSum[2][72][13];         // integral of TS 0-9
      mode 3: TH1F * HistoEachTS[2][72][13];          // no sum but each TS 
      mode 4: TH1F * HistoEachTSsub[2][72][13];       // no sum but ecah TS(2-5)
      mode5-15 TH1F * HistoSeparateTS[2][72][13][mode-5] // draw only TS = mode-5
     */
    TString fLEDname = Form("../Run_%i.root",run);
    TString fPEDname = fLEDname;
    TString rootname = filname+"_mode_";
    rootname+=mode;
    rootname+=".root";
    pedmode=pmode;
    int LED_amp=40;
    _hstFile = new TFile(rootname,"recreate");
    BookHistograms();
    GetHFPMap();
    //set plotting styles
    gStyle->SetCanvasColor(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetFrameBorderMode(0);
    gStyle->SetStatColor(0);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);


    //set file names
    stringstream out_fname;
    stringstream out_fname1;
    out_fname<<"SPEconstants_Run_"<<run<<"_"<<filname<<"_mode_"<<mode<<".txt";
    out_fname1<<"SPEspec_Run_"<<run<<"_"<<filname<<".txt";

    ofstream  constants_file(out_fname.str().c_str(),ios_base::trunc); 
    //ofstream  constants_file1(out_fname1.str().c_str(),ios_base::trunc); 
    constants_file<<"Run "<<run<<endl;
    constants_file<<"type SPE"<<endl;
    constants_file<<"LED_amplitude "<<LED_amp<<endl<<endl;

    constants_file<<endl<<"Robox Column iDepth iPhi iEta Ped_mean Ped_mean_err Ped_RMS  Ped_RMS_err SPEPeak_RMS SPEPeak_RMS_err Gain Gain_err Normalized_Chi2 MeanPE_fit MeanPE_fit_err"<<endl;

    out_fname.str("");
    out_fname<<"SPEdistributions_Run_"<<run<<".txt";

    out_fname.str("");
    out_fname<<"SPEextra_Run_"<<run<<".txt";
    //ofstream  extra_file(out_fname.str().c_str(),ios_base::trunc); 


    double scale = 1.0;
    scale = 2.6; //Need to scale up HF charge
    double fC2electrons = 6240.; //convert fC to #electrons

    char spename[128], pedname[128], spehistname[128], numname[128];

    TFile *tfLED = new TFile(fLEDname);
    TFile *tfPED = new TFile(fPEDname);


    //const int NnewBins = 106;
    //double binsX[NnewBins] = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,150,152,154,156,158,160,162,164,166,168,170,180,190,200,210,220,230,240,250,266,282,298,316,336,356,378,404,430,456,482,500};

    //const int NnewBins = 80;//75
    //double binsX[NnewBins] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,102,105,108,111,114,117,120,123,126,129,132,135,138,141,144,147,150,153,156,159,162,165,168,171,174,177,180,190,200,210,220,230,240,250,266,282,298,316,336,356,378,404,430,456,482,500};	  

    const int NnewBins = 101;//75
    double binsX[NnewBins] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
    
    const int NnewBins_single = 57;
    double binsX_single[NnewBins] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,45,51,57,63,69,75,81,87,93,99,105,111,117,123,129,135,141,147,153,159,165,171,177,183,190,200,210,220,230,240,250,266,282,298,316,336,356,378,404,430,456,482,500};	  

    //default: 
    const int NnewBins_ped = 46;//75
    double binsX_ped[NnewBins] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,102,120,138,156,174,200,230,266,316,378,456,500};
    double binsX_ped_single[NnewBins] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,45,51,57,63,69,75,81,87,93,99,120,138,156,174,200,230,266,316,378,456,500};
    const int NnewBins_ped_single = 31;
    //var1
    //  const int NnewBins_ped = 37;//75
    // double binsX_ped[NnewBins_ped] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,200,350,500};

    //double binsX[NnewBins] = {0,6,12,18,24,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93,96,99,102,105,108,111,114,117,120,123,126,129,132,135,138,141,144,147,150,153,156,159,162,165,168,171,174,177,180,190,200,210,220,230,240,250,266,282,298,316,336,356,378,404,430,456,482,500};	 
    TH1F * hspe, *resid;
    if(!pedmode) {
        if(mode<3){ 
            hspe = new TH1F("hspe","hspe",NnewBins-1,binsX);
            resid = new TH1F("resid","resid",NnewBins-1,binsX);
        }
        else{
            hspe = new TH1F("hspe","hspe",NnewBins_single-1,binsX_single);
            resid = new TH1F("resid","resid",NnewBins_single-1,binsX_single);
        }
    }
    else if(pedmode) {
        if(mode<3){ 
            hspe = new TH1F("hspe","hspe",NnewBins_ped-1,binsX);
            resid = new TH1F("resid","resid",NnewBins_ped-1,binsX);
        }
        else{
            hspe = new TH1F("hspe","hspe",NnewBins_ped_single-1,binsX_single);
            resid = new TH1F("resid","resid",NnewBins_ped_single-1,binsX_single);
        }
    }
    hspe->Sumw2();
    resid->Sumw2();




    /* // int NDepth = 2; //number of depths
       int MinDepth = 1;
       int MaxDepth = 2;
       int MinEta = 29; 
       int MaxEta = 33; //41
    //int MinPhi = 41;
    //int MaxPhi = 53;
    int MinPhi = 1;
    int MaxPhi = 5; //71
    int NEta = 1+MaxEta-MinEta;
    int NPhi = 1+MaxPhi-MinPhi;*/

    //TCanvas *Carray[NDepth+1][MaxPhi+1];
    TCanvas *Carray[37][4];
    bool drawflag[37][4];  
    bool badfit[37][4][9];
    TH1F *LED[NDepth+1][MaxEta+1][MaxPhi+1];
    TH1F *PED[NDepth+1][MaxEta+1][MaxPhi+1];
//    TH1F *NumAbove[NDepth+1][MaxEta+1][MaxPhi+1];




    for(int iDepth = MinDepth; iDepth <= MaxDepth; iDepth++){
        for(int iPhi = MinPhi; iPhi <= MaxPhi; iPhi++){

            bool nonNull = false;

            for(int iEta = MinEta; iEta <= MaxEta; iEta++){

                if(mode==1) sprintf(spename,"Analyzer/CommonDir/ResPlotDir/Histo_for_Depth_%d_Eta_%d_Phi_%d",iDepth,iEta,iPhi);
                if(mode==2) sprintf(spename,"Analyzer/CommonDir/ResPlotDir/Histo_for_Depth_%d_Eta_%d_Phi_%d_FullSum",iDepth,iEta,iPhi);
                if(mode==3) sprintf(spename,"Analyzer/CommonDir/ResPlotDir/Histo_for_Depth_%d_Eta_%d_Phi_%d_eachTS",iDepth,iEta,iPhi);
                if(mode==4) sprintf(spename,"Analyzer/CommonDir/ResPlotDir/Histo_for_Depth_%d_Eta_%d_Phi_%d_eachTSsub",iDepth,iEta,iPhi);
                if(mode>4) sprintf(spename,"Analyzer/CommonDir/ResPlotDir/Histo_for_Depth_%d_Eta_%d_Phi_%d_TS_%i",iDepth,iEta,iPhi,mode-5);


                LED[iDepth][iEta][iPhi]=(TH1F *)tfLED->Get(spename);
                if(LED[iDepth][iEta][iPhi]) nonNull = true;
                //else cout<<"failed reg"<<endl;

                //sprintf(spename,"Analyzer/CommonDir/ResPlotDir/Histo_for_Depth_%d_Eta_%d_Phi_%d",iDepth,iEta,iPhi);
                PED[iDepth][iEta][iPhi]=(TH1F *)tfPED->Get(spename);

                sprintf(numname,"Analyzer/CommonDir/ResPlotDir/Num_Above_Depth_%d_Eta_%d_Phi_%d",iDepth,iEta,iPhi);
                //	cout<<"Getting numAbove"<<endl;
//                NumAbove[iDepth][iEta][iPhi]=(TH1F *)tfLED->Get(numname);
                //	if(!NumAbove[iDepth][iEta][iPhi]) cout<<"Failed"<<endl;

            }



            if(nonNull){ //only create canvas if distributions exist

            }

        }
    }



    int HV=0;
    int iEta, iPhi,iDepth;
    /*for(int iDepth = MinDepth; iDepth <= MaxDepth; iDepth++){
      for(int iPhi = MinPhi; iPhi <= MaxPhi; iPhi++){
      for(int iEta = MinEta; iEta <= MaxEta; iEta++){*/
    for(int irbx = 1; irbx<37; irbx++){
        for(int ibb= 1; ibb<4;ibb++){
            drawflag[irbx][ibb] = false;
            char canvname[16];
            sprintf(canvname, "c_%d_%d", irbx,ibb);
            Carray[irbx][ibb] = new TCanvas(canvname,canvname,1800,800);
            Carray[irbx][ibb]->Divide(4,2);
            for(int ipmt=1; ipmt<9;ipmt++){
                badfit[irbx][ibb][ipmt] = false;
                iEta = eta[irbx][ibb][ipmt];
                iPhi = phi[irbx][ibb][ipmt];
                iDepth = dep[irbx][ibb][ipmt];
                //cout<<iDepth<<" "<<iPhi<<" "<<iEta<<endl;
                // if(iEta!=38 || iPhi !=33 || iDepth !=1) continue;
                if(!LED[iDepth][iEta][iPhi]) {cout<<"Fail depth eta phi "<<iDepth<<" "<<iEta<<" "<<iPhi<<endl; continue;}

                sprintf(spehistname,"led %d %d %d",iDepth,iEta,iPhi);
                TH1F *hspe_temp = (TH1F *)LED[iDepth][iEta][iPhi]->Clone(spehistname);
                //	cout<<"post clone depth eta phi pmt int "<<iDepth<<" "<<iEta<<" "<<iPhi<<" "<<ipmt<<" "<<hspe_temp->Integral()<<endl;
                sprintf(spehistname,"ped %d %d %d",iDepth,iEta,iPhi);
                TH1F *hped = (TH1F *)PED[iDepth][iEta][iPhi]->Clone(spehistname);
                hspe->Reset();
                resid->Reset();
                sprintf (spehistname, "SumLED_Depth_%d_Eta_%d_Phi_%d",iDepth,iEta,iPhi);
                hspe->SetTitle(spehistname);
                sprintf(spehistname,"cp_Num_Above_Depth_%i_Eta_%i_Phi_%i",iDepth,iEta,iPhi);
//                TH1F *chg_share = new TH1F(spehistname,spehistname,10,0,10);

//                for(int ix=2;ix<=10;ix++){
//                    chg_share->SetBinContent(ix,NumAbove[iDepth][iEta][iPhi]->GetBinContent(ix));
//                } 
//                chg_share->SetBinContent(1,0);
//                float chg_frac = chg_share->Integral(3,10)/chg_share->Integral();

                //cout<<"preloop check"<<ipmt<<" integral "<<hspe_temp->Integral()<<endl;
                //combine bins of original SPE histogram
                for(int ib=1; ib<=hspe_temp->GetNbinsX(); ib++) {
                    double bin_center = hspe_temp->GetBinCenter(ib);

                    if(bin_center>hspe->GetXaxis()->GetXmax()) continue;
                    int newbin = hspe->FindBin(bin_center);
                    double new_content = hspe->GetBinContent(newbin) + hspe_temp->GetBinContent(ib);
                    double new_error = sqrt(pow(hspe->GetBinError(newbin),2)+pow(hspe_temp->GetBinError(ib),2));
                    hspe->SetBinContent(newbin,new_content);
                    hspe->SetBinError(newbin,new_error);
                }
                TH1F* hspe_unscaled = (TH1F*)hspe->Clone("hspe_unscaled");
                //renormalize bins of new SPE histogram
                for(int ib=1; ib<=hspe->GetNbinsX(); ib++) {
                    double new_content = hspe->GetBinContent(ib)/hspe->GetXaxis()->GetBinWidth(ib)*hspe_temp->GetXaxis()->GetBinWidth(1);
                    double new_error = hspe->GetBinError(ib)/hspe->GetXaxis()->GetBinWidth(ib)*hspe_temp->GetXaxis()->GetBinWidth(1);
                    hspe->SetBinContent(ib,new_content);
                    hspe->SetBinError(ib,new_error);
                }
                //	cout<<"pre temp check "<<ipmu<<" integral "<<hspe_temp->Integral()<<endl; 

                // ------------------------------
                // FIT 
                // ------------------------------
                if(hspe_temp->Integral()==0) continue;
                else drawflag[irbx][ibb] = true;	  
                Nev = hspe_temp->Integral()*hspe_temp->GetXaxis()->GetBinWidth(1);  

                //
                // Pedestal fit 
                //
                //TF1 *fped = new TF1("fped","gaus",0, 80);
                TF1 *fped;
                if(mode<3) fped= new TF1("fped","gaus",0, 20);
                else fped= new TF1("fped","gaus",0,15);
                hped->Fit(fped,"NQR");
                double pploc = fped->GetParameter(1), ppwidth = fped->GetParameter(2);
                // DEBUG	
                cout<<"depth "<<iDepth<<" ieta "<<iEta<<" iphi "<<iPhi <<" pploc "<<pploc<<" ppwidth "<<ppwidth<<endl;
                //hspe->Fit(fped, "NQ", "", pploc - 3*ppwidth, pploc + ppwidth);  
                hspe->Fit(fped, "NQ", "", pploc - 3*ppwidth, pploc + 3*ppwidth);  

                // 
                //estimate SPE peak location
                // 
                int max_SPE_bin, maxbin, Nbins;
                double max_SPE_height=0, minheight, max_SPE_location;
                bool minflag = false;
                maxbin=hspe->FindBin(fped->GetParameter(1)); //location of pedestal peak
                minheight=hspe->GetBinContent(maxbin); //initialize minheight
                Nbins = hspe->GetNbinsX();
                for(int j=maxbin+1; j<Nbins-1; j++) { //start from pedestal peak and loop through bins
                    if(hspe->GetBinContent(j) > minheight && !minflag) minflag=true; //only look for SPE peak when minflag=true
                    if(hspe->GetBinContent(j) < minheight )  minheight = hspe->GetBinContent(j);
                    if(minflag && hspe->GetBinContent(j) > max_SPE_height){
                        max_SPE_bin = j;
                        max_SPE_location = hspe->GetBinCenter(max_SPE_bin);
                        max_SPE_height = hspe->GetBinContent(j);
                    }
                } //start from pedestal peak and loop through bins
                //find minimum bin between pedestal and SPE peaks
                hspe->GetXaxis()->SetRange(maxbin,max_SPE_bin);
                int minbin = hspe->GetMinimumBin(); 
                double minbin_location = hspe->GetBinCenter(minbin);
                hspe->GetXaxis()->SetRange(1,Nbins);	    

                TF1 *fit = new TF1("fit", FitFun, 0, 50, 5);

                double mu = - log(fped->Integral(0,100)/Nev); // f(0)  = exp(-par[0])
                if(mu<0 && pedmode ) mu=0.00001;
                if( mu<0 && !pedmode) mu=0.01;
                double gain_est = max_SPE_location-1.0*fped->GetParameter(1);
                //if(max_SPE_bin > (minbin+1)) fit->SetParameters(mu, 20, 1, gain_est, gain_est*0.5);
                if(max_SPE_bin > (minbin+1)) fit->SetParameters(mu, fped->GetParameter(1), fped->GetParameter(2), gain_est, gain_est*0.5);
                else fit->SetParameters(mu, fped->GetParameter(1), fped->GetParameter(2), 2.1*fped->GetParameter(2), 10); //case of no clear minimum; start looking for SPE peak at 2sigma away from pedestal peak
                if(pedmode && (mode==1 || mode==4)) fit->SetParLimits(0, 0, 0.000316);
                if(pedmode && mode!=1 && mode!=4) fit->SetParLimits(0, 0, 0.00005);
                else fit->SetParLimits(0, 0, 10);
                fit->FixParameter(1, fped->GetParameter(1));
                fit->FixParameter(2, fped->GetParameter(2));
                fit->SetParLimits(3, fped->GetParameter(2)*2, 350);
                fit->SetParLimits(4, fped->GetParameter(2)*1.01, 250);

                fit->SetParLimits(5, 1.0, 4.0);

                double maxfitrange = 100.;    
                double minfitrange = 0.;
                hspe->Fit(fit, "MNQLB", "", minfitrange, maxfitrange);
                //cout<<"initial p: "<<fped->GetParameter(1)<<" "<<fped->GetParError(1)<<" "<<fped->GetParameter(2)<<" "<<fped->GetParError(2)<<" "<<fit->GetParameter(4)<<" "<<fit->GetParError(4)<<" "<<fit->GetParameter(3)<<" "<<fit->GetParError(3)<<endl;
                maxfitrange = fped->GetParameter(1)+4*fit->GetParameter(3)+fit->GetParameter(4);
                if(maxfitrange<30) maxfitrange=30;
                 cout<<"new min ="<<minfitrange<<endl;
                 cout<<"new max ="<<maxfitrange<<endl;
                if(100<maxfitrange) maxfitrange = 100;
                hspe->Fit(fit, "MNQLB", "", minfitrange, maxfitrange);
                //cout<<"chi2 = "<<fit->GetChisquare()<<endl;
                //calculate NDOF of fit excluding bins with 0 entries
                int myNDOF=-3; //three free parameters
                for(int j=hspe->FindBin(minfitrange); j<=hspe->FindBin(maxfitrange); j++) { //loop through fitted spe bins
                    if(hspe->GetBinContent(j)) myNDOF++;
                } //loop through fitted spe bins

                //cout<<"ndf= "<<myNDOF<<endl;
                //calculate means and integrals of the fit and data
                double fint, fint_error, hint, favg, havg;
                int temp_lowbin, temp_highbin;
                temp_lowbin = hspe->FindBin(minfitrange);
                temp_highbin = hspe->FindBin(maxfitrange);
                hspe_unscaled->GetXaxis()->SetRangeUser(minfitrange, maxfitrange);
                havg = hspe_unscaled->GetMean();
                hint = hspe->Integral(temp_lowbin,temp_highbin,"width");
                double min_frange = hspe->GetBinLowEdge(temp_lowbin);
                favg = fit->Mean(min_frange, maxfitrange);
                fint = fit->Integral(min_frange, maxfitrange);
                //fint_error = fit->IntegralError(min_frange, maxfitrange);

                double PE5int = 0; //integral of events with >=5 PE
                double PE5loc =  fped->GetParameter(1)+ 5*fit->GetParameter(3);
                if(PE5loc>500) PE5int = 0;
                else {
                    int PE5bin =  hspe_temp->FindBin(PE5loc);
                    temp_highbin = hspe_temp->FindBin(maxfitrange)-1;
                    PE5int =  hspe_temp->Integral(PE5bin,temp_highbin,"width");
                }
                int PE5flag = 0;
                if(PE5int/hint>0.05) PE5flag = 1; //set flag if more than 5% of events in the fit correspond to >=5PE
                //=========================================    
                //for(int i1=1;i1<hspe->GetNbinsX();i1++){
                //constants_file1<<HV<<"\t"<<iDepth<<"\t"<<iEta<<"\t"<<iPhi<<"\t"<<2.6*hspe->GetBinCenter(i1)<<"\t"<<hspe->GetBinContent(i1)<<"\t"<<fit->Eval(hspe->GetBinCenter(i1))<<"\n";
                //}
                //=========================================    

                //printf("%d\n",myNDOF);
                //output calibrations constants
                //constants_file<<endl<<"LED_amplitude HV Spigot Channel Ped_mean Ped_mean_err Ped_RMS  Ped_RMS_err SPEPeak_RMS SPEPeak_RMS_err Gain Gain_err Normalized_Chi2 MeanPE_fit MeanPE_fit_err MeanPE_estimate PE5flag"<<endl;
                //constants_file<<LED_amp<<" "<<iDepth<<" "<<iPhi<<" "<<iEta<<" "<<scale*fped->GetParameter(1)<<" "<<scale*fped->GetParError(1)<<" "<<scale*fped->GetParameter(2)<<" "<<scale*fped->GetParError(2)<<" "<<scale*fit->GetParameter(4)<<" "<<scale*fit->GetParError(4)<<" "<<scale*fit->GetParameter(3)*fC2electrons<<" "<<scale*fit->GetParError(3)*fC2electrons<<" "<<fit->GetChisquare()/myNDOF/*fit->GetNDF()*/<<" "<<fit->GetParameter(0)<<" "<<fit->GetParError(0)<<" "<<mu<<" "<<PE5flag<<endl;


                /* Ped_mean[iDepth]->Fill(iEta,iPhi,fped->GetParameter(1));
                   Ped_mean_err[iDepth]->Fill(iEta,iPhi,fped->GetParError(1));
                   Ped_RMS[iDepth]->Fill(iEta,iPhi,fped->GetParameter(2));
                   Ped_RMS_err[iDepth]->Fill(iEta,iPhi,fped->GetParError(2));
                   Gain[iDepth]->Fill(iEta,iPhi,fit->GetParameter(3));
                   Gain_err[iDepth]->Fill(iEta,iPhi,fit->GetParError(3));
                   SPEPeak_RMS[iDepth]->Fill(iEta,iPhi,fit->GetParameter(4));
                   SPEPeak_RMS_err[iDepth]->Fill(iEta,iPhi,fit->GetParError(4));
                   Normalized_Chi2[iDepth]->Fill(iEta,iPhi,fit->GetChisquare()/myNDOF);
                   MeanPE_fit[iDepth]->Fill(iEta,iPhi,fit->GetParameter(0));
                   MeanPE_fit_err[iDepth]->Fill(iEta,iPhi,fit->GetParError(0));
                   MeanPE_estimate[iDepth]->Fill(iEta,iPhi,mu);
                //constants_file<<fit->GetParameter(3)<<" "<<fit->GetParError(3)<<endl;
                 */
                /*
                   if(iDepth==2 && iPhi==53 && iEta==36){
                   cout<<iDepth<<" "<<iPhi<<" "<<iEta<<" "<<gain_est<<" "<<fit->GetParameter(3)<<endl;
                   cout<<LED_amp<<" "<<iDepth<<" "<<iPhi<<" "<<iEta<<" "<<scale*fped->GetParameter(1)<<" "<<scale*fped->GetParError(1)<<" "<<scale*fped->GetParameter(2)<<" "<<scale*fped->GetParError(2)<<" "<<scale*fit->GetParameter(4)<<" "<<scale*fit->GetParError(4)<<" "<<scale*fit->GetParameter(3)*fC2electrons<<" "<<scale*fit->GetParError(3)*fC2electrons<<" "<<fit->GetChisquare()/myNDOF<<" "<<fit->GetParameter(0)<<" "<<fit->GetParError(0)<<" "<<mu<<" "<<PE5flag<<endl;
                   }
                 */
                int col = column[iPhi][iEta][iDepth];
                int rbx = robox[iPhi][iEta][iDepth];


                //orig	constants_file<<LED_amp<<" "<<iDepth<<" "<<iPhi<<" "<<iEta<<" "<<fped->GetParameter(1)<<" "<<fped->GetParError(1)<<" "<<fped->GetParameter(2)<<" "<<fped->GetParError(2)<<" "<<fit->GetParameter(4)<<" "<<fit->GetParError(4)<<" "<<fit->GetParameter(3)<<" "<<fit->GetParError(3)<<" "<<fit->GetChisquare()/myNDOF/*fit->GetNDF()*/<<" "<<fit->GetParameter(0)<<" "<<fit->GetParError(0)<<" "<<mu<<" "<<PE5flag<<endl;
                constants_file<<rbx<<" "<<col<<" "<<iDepth<<" "<<iPhi<<" "<<iEta<<" "<<fped->GetParameter(1)<<" "<<fped->GetParError(1)<<" "<<fped->GetParameter(2)<<" "<<fped->GetParError(2)<<" "<<fit->GetParameter(4)<<" "<<fit->GetParError(4)<<" "<<fit->GetParameter(3)<<" "<<fit->GetParError(3)<<" "<<fit->GetChisquare()/fit->GetNDF()/*myNDOF*/<<" "<<fit->GetParameter(0)<<" "<<fit->GetParError(0)<<endl;

                //cout<<"irbx ibb ipmt"<<irbx<<" "<<ibb<<" "<<ipmt<<endl;
                //cout<<"iPhi iEta iDepth "<<iPhi<<" "<<iEta<<" "<<iDepth<<" col RBX "<<col<<" "<<rbx<<endl;
                Ped_mean[0]->Fill(col,rbx,fped->GetParameter(1));
                Ped_mean_err[0]->Fill(col,rbx,fped->GetParError(1));
                Ped_RMS[0]->Fill(col,rbx,fped->GetParameter(2));
                Ped_RMS_err[0]->Fill(col,rbx,fped->GetParError(2));
                Gain[0]->Fill(col,rbx,fit->GetParameter(3));
                Gain_err[0]->Fill(col,rbx,fit->GetParError(3));
                SPEPeak_RMS[0]->Fill(col,rbx,fit->GetParameter(4));
                SPEPeak_RMS_err[0]->Fill(col,rbx,fit->GetParError(4));
                Normalized_Chi2[0]->Fill(col,rbx,fit->GetChisquare()/myNDOF);
                MeanPE_fit[0]->Fill(col,rbx,fit->GetParameter(0));
                MeanPE_fit_err[0]->Fill(col,rbx,fit->GetParError(0));
                MeanPE_estimate[0]->Fill(col,rbx,mu);
                //ShareMap[0]->Fill(col,rbx,chg_frac);


                proj_Ped_mean[0]->Fill(fped->GetParameter(1));
                proj_Ped_mean_err[0]->Fill(fped->GetParError(1));
                proj_Ped_RMS[0]->Fill(fped->GetParameter(2));
                proj_Ped_RMS_err[0]->Fill(fped->GetParError(2));
                proj_Gain[0]->Fill(fit->GetParameter(3));
                proj_Gain_err[0]->Fill(fit->GetParError(3));
                proj_SPEPeak_RMS[0]->Fill(fit->GetParameter(4));
                proj_SPEPeak_RMS_err[0]->Fill(fit->GetParError(4));
                proj_Normalized_Chi2[0]->Fill(TMath::Log10(fit->GetChisquare()/myNDOF));
                proj_MeanPE_fit[0]->Fill(TMath::Log10(fit->GetParameter(0)));
                proj_MeanPE_fit_err[0]->Fill(TMath::Log10(fit->GetParError(0)));
                proj_MeanPE_estimate[0]->Fill(TMath::Log10(mu));
                //proj_ShareMap[0]->Fill(chg_frac);
                /*float frac = ROOT::Math::gaussian_cdf_c(100.,sqrt(pow(fit->GetParameter(4),2)+pow(fped->GetParameter(2),2)) , fit->GetParameter(3)+fped->GetParameter(1));
                  float trig = frac*fit->GetParameter(0)*pow(10,9)/(25.);*/
                float frac = hspe->Integral(hspe->FindBin(100),hspe->FindBin(499),"width")/ hspe->Integral(hspe->FindBin(0),hspe->FindBin(499),"width");
                float trig = frac*pow(10,9)/(100.);
                Selftrigger_estimate[0]->Fill(col,rbx,trig);
                proj_Selftrigger_estimate[0]->Fill(trig);

                frac = fit->Integral(100,499)/fit->Integral(0,499);
                trig = frac*pow(10,9)/(100.);
                Selftrigger_integral[0]->Fill(col,rbx,trig);
                proj_Selftrigger_integral[0]->Fill(trig);



                if(!pedmode){
                    if(fit->GetChisquare()/myNDOF > 20 || fit->GetParError(3) > 0.6){
                        badfit[irbx][ibb][ipmt] = true;
                    }
                }
                else if(pedmode){
                    if(fit->GetChisquare()/myNDOF > 400 || fit->GetParError(3) > 20){
                        badfit[irbx][ibb][ipmt] = true;
                    }
                }
                //cout<<"eta phi depth pmt "<<iEta<<" "<<iPhi<<" "<<iDepth<<" "<<ipmt<<endl;
                Carray[irbx][ibb]->cd(ipmt);
                // TCanvas *c1 = new TCanvas("c1","c1",800,800);
                TPad *pad1 = new TPad("pad1","pad1",0,0.33,1,1);
                TPad *pad2 = new TPad("pad2","pad2",0,0.05,1,0.33);
                pad1->SetBottomMargin(0.00001);
                pad1->SetBorderMode(0);
                pad1->SetLogy();
                pad2->SetTopMargin(0.00001);
                pad2->SetBottomMargin(0.3);
                pad2->SetBorderMode(0);
                pad1->Draw();
                pad2->Draw();
                pad1->cd();
                /*gPad->SetBorderMode(0);
                  gPad->SetBorderSize(0);
                  gPad->SetRightMargin(0.01);
                  gPad->SetBottomMargin(0.1);
                  gPad->SetLogy(true);*/
                hspe->GetXaxis()->SetRangeUser(0, 100 /*200*/ /*300*//*508*/);
                hspe->SetLineColor(kBlue);
                //hspe->SetLineColor(kBlack);
                hspe->SetMarkerColor(kBlack);
                hspe->SetMarkerSize(1);
                hspe->SetMarkerStyle(20);
                hspe->SetStats(false);

                hspe->DrawClone("HIST");

                fit->SetLineWidth(1);
                fit->SetLineColor(kRed);
                fit->SetRange(minfitrange,maxfitrange);
                fit->Draw("same");
                myText(0.5,0.85,Form("Gain = %.1f +/- %.1f",fit->GetParameter(3),fit->GetParError(3)),1,0.04);
                myText(0.5,0.8,Form("SPE RMS = %.1f +/- %.1f",fit->GetParameter(4),fit->GetParError(4)),1,0.04);
                if(pedmode) myText(0.5,0.75,Form("Log(Mean PE) = %.1f",TMath::Log10(fit->GetParameter(0))),1,0.04);
                else myText(0.5,0.75,Form("Mean PE = %.2f",fit->GetParameter(0)),1,0.04);
                myText(0.5,0.7,Form("Chi^{2}/ndf =  %.1f",fit->GetChisquare()/fit->GetNDF()),1,0.04);
                /*	TArrow first = TArrow(maxfitrange,2,maxfitrange,0.1,0.04,"");
                    first.DrawLine(maxfitrange,2,maxfitrange,0.1);*/
                pad2->cd();



                for(int k=0;k<=hspe->FindBin(maxfitrange);k++){
                    Double_t diff = hspe->GetBinContent(k)/fit->Eval(hspe->GetBinCenter(k));
                    Double_t error = hspe->GetBinError(k)/fit->Eval(hspe->GetBinCenter(k));
                    resid->SetBinContent(k,diff);
                    resid->SetBinError(k,error);
                }

                resid->GetXaxis()->SetRangeUser(0, 100 /*200*/);
                //	resid->SetMaximum(10);
                //	resid->SetMinimum(-10);
                resid->SetLineColor(kBlack);
                resid->SetMarkerStyle(20);
                resid->SetMarkerSize(1);
                resid->SetLabelSize(0.15);
                resid->SetLabelSize(0.15,"Y");
                resid->SetStats(false);
                resid->SetTitle("");
                resid->SetXTitle("Charge [fC]");
                resid->GetXaxis()->SetTitleSize(0.15);
                resid->DrawClone("PE");
                //resid->Delete();
            }

            if(drawflag[irbx][ibb]) { //draw plots of fit if data for the HV is present
                stringstream plot_name;
                plot_name<<"Plots/SPEFits_Run_"<<run<<"_mode_"<<mode<<"_Robox"<<irbx<<"_BB"<<ibb<<"_"<<filname<<".pdf";
                Carray[irbx][ibb]->SaveAs(plot_name.str().c_str());
                plot_name.str( std::string() );
            }

        }


    }

/*
    for(int irbx = 1; irbx<37; irbx++){
        for(int ibb= 1; ibb<4;ibb++){
            for(int ipmt=1; ipmt<9;ipmt++){
            }
        }
    }
*/
    _hstFile->Write();
    _hstFile->Close();
    constants_file.close();
    //constants_file1.close();

}



