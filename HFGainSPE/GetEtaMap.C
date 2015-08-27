#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TGaxis.h"
#include "stdio.h"
#include "time.h"
#include "math.h"
#include "TMath.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TSystem.h"
#include "TTree.h"
#include<iostream>
#include<fstream>



//void getetamap(int ieta, int iphi, int idepth){
void getetamap(){

  //   TFile *file221263 = TFile::Open("EtaPhiMapRun221263FiveSigma.root");
  //   TFile *file221265 = TFile::Open("EtaPhiMapRun221265FiveSigma.root");
  //   TFile *file221267 = TFile::Open("EtaPhiMapRun221267FiveSigma.root");
  //   TFile *file221268 = TFile::Open("EtaPhiMapRun221268FiveSigma.root");  
  //   TFile *file221269 = TFile::Open("EtaPhiMapRun221269FiveSigma.root");

  //   TFile *file221263 = TFile::Open("EtaPhiMapRun221263ThreeSigma.root");
  //   TFile *file221265 = TFile::Open("EtaPhiMapRun221265ThreeSigma.root");
  //   TFile *file221267 = TFile::Open("EtaPhiMapRun221267ThreeSigma.root");
  //   TFile *file221268 = TFile::Open("EtaPhiMapRun221268ThreeSigma.root");  
  //   TFile *file221269 = TFile::Open("EtaPhiMapRun221269ThreeSigma.root");

  TFile *file221548 = TFile::Open("EtaPhiMapRun221548FiveSigma.root");
  //TFile *file221548 = TFile::Open("EtaPhiMapRun221548ThreeSigma.root");

  //TFile* allfiles[5] = {file221263,file221265,file221267,file221268,file221269};
  TFile* allfiles[1] = {file221548};

  TGraph *graph = new TGraph(1);

  for(int i=0;i<1;i++){
    allfiles[i]->cd();

    TH2D *pedevsigma = (TH2D*)allfiles[i]->Get("ped_ev_sigma");
    float contentQ1 = 0.;
    float contentQ2 = 0.;
    float contentQ3 = 0.;
    float contentQ4 = 0.;

    for(int depth=1;depth<=2;depth++){
      for(int eta = 29;eta<=39;eta++){
	for(int phi = 1;phi<=71;phi+=2){

	    if(phi >= 1 && phi <=17) contentQ1+= pedevsigma->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 19 && phi <=35) contentQ2+= pedevsigma->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 37 && phi <=53) contentQ3+= pedevsigma->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 55 && phi <=71) contentQ4+= pedevsigma->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);

	    //content+= pedevsigma->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	  //cout<<pedevsigma->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1)<<content<<endl;
	}
      }
    }

    contentQ1 /= 198.;
    contentQ2 /= 198.;
    contentQ3 /= 198.;
    contentQ4 /= 198.;

    content=content/198.;cout<<content/50000.<<endl;
    graph->SetPoint(i+1,80-i*5,content);
    allfiles[i]->Close();
  }

  graph->Draw("a*");


}



// void makeQ3(){

//   for(int ieta=29;ieta<=41;ieta++){
//     for(int iphi=37;iphi<=53;iphi++){
//       getetamap(ieta,iphi,1);          
//     }
//   }
  

// }









//void getetamap(int ieta, int iphi, int idepth){
void correlplotsOV1vsOV1plus100(){

  TCanvas *canvas = new TCanvas("canvas","canvas",200,200,500,500);
  canvas->cd();
  canvas->Divide(1,2);

  TFile *file5sig221244 = TFile::Open("EtaPhiMapRun221244FiveSigma.root");
  TFile *file5sig221256 = TFile::Open("EtaPhiMapRun221256FiveSigma.root");
  TFile *file5sig221258 = TFile::Open("EtaPhiMapRun221258FiveSigma.root");
  TFile *file5sig221260 = TFile::Open("EtaPhiMapRun221260FiveSigma.root");
  TFile *file5sig221261 = TFile::Open("EtaPhiMapRun221261FiveSigma.root");

  TFile *file5sig221269 = TFile::Open("EtaPhiMapRun221269FiveSigma.root");
  TFile *file5sig221268 = TFile::Open("EtaPhiMapRun221268FiveSigma.root");
  TFile *file5sig221267 = TFile::Open("EtaPhiMapRun221267FiveSigma.root");
  TFile *file5sig221265 = TFile::Open("EtaPhiMapRun221265FiveSigma.root");
  TFile *file5sig221263 = TFile::Open("EtaPhiMapRun221263FiveSigma.root");

  TFile *file3sig221244 = TFile::Open("EtaPhiMapRun221244ThreeSigma.root");
  TFile *file3sig221256 = TFile::Open("EtaPhiMapRun221256ThreeSigma.root");
  TFile *file3sig221258 = TFile::Open("EtaPhiMapRun221258ThreeSigma.root");
  TFile *file3sig221260 = TFile::Open("EtaPhiMapRun221260ThreeSigma.root");
  TFile *file3sig221261 = TFile::Open("EtaPhiMapRun221261ThreeSigma.root");

  TFile *file3sig221269 = TFile::Open("EtaPhiMapRun221269ThreeSigma.root");
  TFile *file3sig221268 = TFile::Open("EtaPhiMapRun221268ThreeSigma.root");
  TFile *file3sig221267 = TFile::Open("EtaPhiMapRun221267ThreeSigma.root");
  TFile *file3sig221265 = TFile::Open("EtaPhiMapRun221265ThreeSigma.root");
  TFile *file3sig221263 = TFile::Open("EtaPhiMapRun221263ThreeSigma.root");


  TFile* allfiles5sigOV1plus100[5] = {file5sig221244,file5sig221256,file5sig221258,file5sig221260,file5sig221261};
  TFile* allfiles5sigOV1[5] = {file5sig221269,file5sig221268,file5sig221267,file5sig221265,file5sig221263};

  TFile* allfiles3sigOV1plus100[5] = {file3sig221244,file3sig221256,file3sig221258,file3sig221260,file3sig221261};
  TFile* allfiles3sigOV1[5] = {file3sig221269,file3sig221268,file3sig221267,file3sig221265,file3sig221263};

  for(int k=0;k<=1;k++){

    TGraph *graphQ1 = new TGraph(5);
    TGraph *graphQ2 = new TGraph(5);
    TGraph *graphQ3 = new TGraph(5);
    TGraph *graphQ4 = new TGraph(5);

    for(int i=0;i<5;i++){

      float contentOV1[4] = {0.,0.,0.,0.};
      float contentOV1plus100[4] = {0.,0.,0.,0.};

      TH2D *pedevsigmaOV1;

      if(k==0){
	allfiles5sigOV1[i]->cd();
	pedevsigmaOV1 = (TH2D*)allfiles5sigOV1[i]->Get("ped_ev_sigma");
      }

      if(k==1){
	allfiles3sigOV1[i]->cd();
	pedevsigmaOV1 = (TH2D*)allfiles3sigOV1[i]->Get("ped_ev_sigma");
      }

      for(int depth=1;depth<=2;depth++){
	for(int eta = 29;eta<=39;eta++){
	  for(int phi = 1;phi<=71;phi+=2){

	    if(phi >= 1 && phi <=17) contentOV1[0]= contentOV1[0]+pedevsigmaOV1->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 19 && phi <=35) contentOV1[1]= contentOV1[1]+pedevsigmaOV1->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 37 && phi <=53) contentOV1[2]= contentOV1[2]+pedevsigmaOV1->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 55 && phi <=71) contentOV1[3]= contentOV1[3]+pedevsigmaOV1->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	  
	  }
	}
      }
    
      for(int j=0;j<4;j++){contentOV1[j]=contentOV1[j]/(198.*100000);cout<<contentOV1[j]<<" ";}
      cout<<""<<endl;
      if(k==0) allfiles5sigOV1[i]->Close();
      if(k==1) allfiles3sigOV1[i]->Close();



      TH2D *pedevsigmaOV1plus100;

      if(k==0){
	allfiles5sigOV1plus100[i]->cd();
	pedevsigmaOV1plus100 = (TH2D*)allfiles5sigOV1plus100[i]->Get("ped_ev_sigma");
      }

      if(k==1){
	allfiles3sigOV1plus100[i]->cd();
	pedevsigmaOV1plus100 = (TH2D*)allfiles3sigOV1plus100[i]->Get("ped_ev_sigma");
      }

      for(int depth=1;depth<=2;depth++){
	for(int eta = 29;eta<=39;eta++){
	  for(int phi = 1;phi<=71;phi+=2){

	    if(phi >= 1 && phi <=17) contentOV1plus100[0]= contentOV1plus100[0]+pedevsigmaOV1plus100->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 19 && phi <=35) contentOV1plus100[1]= contentOV1plus100[1]+pedevsigmaOV1plus100->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 37 && phi <=53) contentOV1plus100[2]= contentOV1plus100[2]+pedevsigmaOV1plus100->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	    if(phi >= 55 && phi <=71) contentOV1plus100[3]= contentOV1plus100[3]+pedevsigmaOV1plus100->GetBinContent(eta-28,(phi-1)/2+(depth-1)*36+1);
	  
	  }
	}
      }
    
      for(int j=0;j<4;j++){contentOV1plus100[j]=contentOV1plus100[j]/(198.*100000);cout<<contentOV1plus100[j]<<" ";}
      cout<<""<<endl;
      if(k==0) allfiles5sigOV1plus100[i]->Close();
      if(k==1) allfiles3sigOV1plus100[i]->Close();

      graphQ1->SetPoint(i+1,contentOV1[0],contentOV1plus100[0]);
      graphQ2->SetPoint(i+1,contentOV1[1],contentOV1plus100[1]);
      graphQ3->SetPoint(i+1,contentOV1[2],contentOV1plus100[2]);
      graphQ4->SetPoint(i+1,contentOV1[3],contentOV1plus100[3]);


    }

    graphQ1->SetMarkerColor(kBlack);
    graphQ1->SetLineColor(kBlack);
  
    graphQ2->SetMarkerColor(kBlue);
    graphQ2->SetLineColor(kBlue);
  
    graphQ3->SetMarkerColor(kRed);
    graphQ3->SetLineColor(kRed);
  
    graphQ4->SetMarkerColor(kGreen);
    graphQ4->SetLineColor(kGreen);
  
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(graphQ1);
    mg->Add(graphQ2);
    mg->Add(graphQ3);
    mg->Add(graphQ4);

    canvas->cd(k+1);
    mg->Draw("a*");
  
  }
  
}

