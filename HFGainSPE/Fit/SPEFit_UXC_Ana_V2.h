#ifndef SPEFIT_UXC_ANA_V2_H
#define SPEFIT_UXC_ANA_V2_H

Int_t Nev;
TFile *_hstFile;
const int NDepth=2;
const int MinDepth = 1;
const int MaxDepth = 2;
const int MinEta = 29; 
const int MaxEta = 41; //41
//const int MinPhi = 41;
//const int MaxPhi = 53;
const int MinPhi = 1;
const int MaxPhi = 71; //71
const int NEta = 1+MaxEta-MinEta;
const int NPhi = 1+MaxPhi-MinPhi;

const int maxNPoints=1;

int robox[MaxPhi+1][MaxEta+1][NDepth+1];
int column[MaxPhi+1][MaxEta+1][NDepth+1];

int eta[37][4][9];
int phi[37][4][9];
int dep[37][4][9];

bool pedmode;

TH2F *Ped_mean[maxNPoints];
TH2F *Ped_mean_err[maxNPoints];
TH2F *Ped_RMS[maxNPoints];
TH2F *Ped_RMS_err[maxNPoints];
TH2F *Gain[maxNPoints];
TH2F *Gain_err[maxNPoints];
TH2F *SPEPeak_RMS[maxNPoints];
TH2F *SPEPeak_RMS_err[maxNPoints];
TH2F *Normalized_Chi2[maxNPoints];
TH2F *MeanPE_fit[maxNPoints];
TH2F *MeanPE_fit_err[maxNPoints];
TH2F *MeanPE_estimate[maxNPoints];
TH2F *Selftrigger_estimate[maxNPoints];
TH2F *Selftrigger_integral[maxNPoints];
TH2F *ShareMap[maxNPoints];

TH1F *proj_Ped_mean[maxNPoints];
TH1F *proj_Ped_mean_err[maxNPoints];
TH1F *proj_Ped_RMS[maxNPoints];
TH1F *proj_Ped_RMS_err[maxNPoints];
TH1F *proj_Gain[maxNPoints];
TH1F *proj_Gain_err[maxNPoints];
TH1F *proj_SPEPeak_RMS[maxNPoints];
TH1F *proj_SPEPeak_RMS_err[maxNPoints];
TH1F *proj_Normalized_Chi2[maxNPoints];
TH1F *proj_MeanPE_fit[maxNPoints];
TH1F *proj_MeanPE_fit_err[maxNPoints];
TH1F *proj_MeanPE_estimate[maxNPoints];
TH1F *proj_Selftrigger_estimate[maxNPoints];
TH1F *proj_Selftrigger_integral[maxNPoints];
TH1F *proj_ShareMap[maxNPoints];


void GetHFPMap(){
  // cout<<"called"<<endl;
  string line;
  int iphi,ieta,depth,rbx,bb,pmt;
  int col;
 ifstream fin("HFP_Map.txt"); 
        if(fin.is_open()) {
	  //cout<<"open"<<endl;
	  // int count = 0;
	  int nextslot=0;
	  getline(fin, line);
            while(fin.good()){
	      //   cout<<"good"<<endl;
                // get a line from fin
                getline(fin, line);
		//  if(count==0) continue;
                // Store each element in the line to the defined variables
                stringstream stream(line);
                stream >> iphi >> ieta >> depth >> rbx >> bb >> pmt;
		//	cout<<"stream "<<iphi<<" "<<ieta<<" "<<depth<<" "<<rbx<<" "<<bb<<" "<<pmt<<endl;
		robox[iphi][ieta][depth] = rbx;
		col = 8*(bb-1)+pmt;
		column[iphi][ieta][depth]=col;
		eta[rbx][bb][pmt] = ieta;
		phi[rbx][bb][pmt] = iphi;
		dep[rbx][bb][pmt] = depth;
		//	count++;
	    }
	}
}
/*
void GetHFMMap(){
  // cout<<"called"<<endl;
  string line;
  int iphi,ieta,depth,rbx,bb,pmt;
  int col;
 ifstream fin("HFM_Map.txt"); 
        if(fin.is_open()) {
	  //cout<<"open"<<endl;
	  // int count = 0;
	  int nextslot=0;
	  getline(fin, line);
            while(fin.good()){
	      //   cout<<"good"<<endl;
                // get a line from fin
                getline(fin, line);
		//  if(count==0) continue;
                // Store each element in the line to the defined variables
                stringstream stream(line);
                stream >> iphi >> ieta >> depth >> rbx >> bb >> pmt;
		//	cout<<"stream "<<iphi<<" "<<ieta<<" "<<depth<<" "<<rbx<<" "<<bb<<" "<<pmt<<endl;
		robox[iphi][ieta][depth] = rbx;
		col = 8*(bb-1)+pmt;
		column[iphi][ieta][depth]=col;
		//	count++;
	    }
	}
}
*/

void BookHistograms(){
  TString plotname;
  const int nHV = maxNPoints; //Npoints;
  
  for(int iHV=0; iHV<nHV; iHV++){
    //rename in main body with actual HV values
  
    plotname = Form("Ped_mean_%i",iHV);
    Ped_mean[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Ped_mean_err_%i",iHV);
    Ped_mean_err[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Ped_RMS_%i", iHV);
    Ped_RMS[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Ped_RMS_err_%i",iHV);
    Ped_RMS_err[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Gain_%i",iHV);
    Gain[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Gain_err_%i",iHV);
    Gain_err[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("SPEPeak_RMS_%i",iHV);
    SPEPeak_RMS[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("SPEPeak_RMS_err_%i",iHV);
    SPEPeak_RMS_err[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Normalized_Chi2_%i",iHV);
    Normalized_Chi2[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("MeanPE_fit_%i",iHV);
    MeanPE_fit[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("MeanPE_fit_err_%i",iHV);
    MeanPE_fit_err[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("MeanPE_estimate_%i",iHV);
    MeanPE_estimate[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
     plotname = Form("Selftrigger_estimate_%i",iHV);
    Selftrigger_estimate[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
     plotname = Form("Selftrigger_integral_%i",iHV);
    Selftrigger_integral[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    plotname = Form("Charge_Share_%i",iHV);
    ShareMap[iHV] = new TH2F(plotname,plotname,24,0.5,24.5,36,0.5,36.5);
    
    //if(pedmode){
    //1d hists
    plotname = Form("proj_Ped_mean_%i",iHV);
    proj_Ped_mean[iHV] = new TH1F(plotname,plotname,160,0,80);
    plotname = Form("proj_Ped_mean_err_%i",iHV);
    proj_Ped_mean_err[iHV] = new TH1F(plotname,plotname,100,0,0.2);
    plotname = Form("proj_Ped_RMS_%i", iHV);
    proj_Ped_RMS[iHV] = new TH1F(plotname,plotname,100,0,5);
    plotname = Form("proj_Ped_RMS_err_%i",iHV);
    proj_Ped_RMS_err[iHV] = new TH1F(plotname,plotname,100,0,0.15);
    plotname = Form("proj_Gain_%i",iHV);
    proj_Gain[iHV] = new TH1F(plotname,plotname,100,0,50);
    plotname = Form("proj_Gain_err_%i",iHV);
    proj_Gain_err[iHV] = new TH1F(plotname,plotname,100,0,20);
    plotname = Form("proj_SPEPeak_RMS_%i",iHV);
    proj_SPEPeak_RMS[iHV] = new TH1F(plotname,plotname,100,0,50);
    plotname = Form("proj_SPEPeak_RMS_err_%i",iHV);
    proj_SPEPeak_RMS_err[iHV] = new TH1F(plotname,plotname,100,0,20);
    plotname = Form("proj_Normalized_Chi2_%i",iHV);
    proj_Normalized_Chi2[iHV] = new TH1F(plotname,plotname,200,0,7);
    plotname = Form("proj_MeanPE_fit_%i",iHV);
    proj_MeanPE_fit[iHV] = new TH1F(plotname,plotname,100,-7,0);
    plotname = Form("proj_MeanPE_fit_err_%i",iHV);
    proj_MeanPE_fit_err[iHV] = new TH1F(plotname,plotname,100,-7,0);
    plotname = Form("proj_MeanPE_estimate_%i",iHV);
    proj_MeanPE_estimate[iHV] = new TH1F(plotname,plotname,100,-7,0);
    plotname = Form("proj_Selftrigger_estimate_%i",iHV);
    proj_Selftrigger_estimate[iHV] = new TH1F(plotname,plotname,500,0,20);
    plotname = Form("proj_Selftrigger_integral_%i",iHV);
    proj_Selftrigger_integral[iHV] = new TH1F(plotname,plotname,500,0,20);
    plotname = Form("proj_Charge_Share_%i",iHV);
    proj_ShareMap[iHV] = new TH1F(plotname,plotname,20,0,1);

    // }
    /*else{
    plotname = Form("proj_Ped_mean_%i",iHV);
    proj_Ped_mean[iHV] = new TH1F(plotname,plotname,160,0,80);
    plotname = Form("proj_Ped_mean_err_%i",iHV);
    proj_Ped_mean_err[iHV] = new TH1F(plotname,plotname,100,0,0.02);
    plotname = Form("proj_Ped_RMS_%i", iHV);
    proj_Ped_RMS[iHV] = new TH1F(plotname,plotname,100,0,5);
    plotname = Form("proj_Ped_RMS_err_%i",iHV);
    proj_Ped_RMS_err[iHV] = new TH1F(plotname,plotname,100,0,0.15);
    plotname = Form("proj_Gain_%i",iHV);
    proj_Gain[iHV] = new TH1F(plotname,plotname,100,0,50);
    plotname = Form("proj_Gain_err_%i",iHV);
    proj_Gain_err[iHV] = new TH1F(plotname,plotname,100,0,5);
    plotname = Form("proj_SPEPeak_RMS_%i",iHV);
    proj_SPEPeak_RMS[iHV] = new TH1F(plotname,plotname,100,0,50);
    plotname = Form("proj_SPEPeak_RMS_err_%i",iHV);
    proj_SPEPeak_RMS_err[iHV] = new TH1F(plotname,plotname,100,0,5);
     const int nbins=25;
    Double_t xbins[nbins+1];
    double dx = 5./nbins;
    double l10 = TMath::Log(10);
    for (int i=0;i<=nbins;i++) {
      xbins[i] = TMath::Exp(l10*i*dx);
   }
    plotname = Form("proj_Normalized_Chi2_%i",iHV);
    proj_Normalized_Chi2[iHV] = new TH1F(plotname,plotname,nbins,xbins);

    const int nbins2=30;
    Double_t xbins2[nbins2+1];
    double dx2 = 7./nbins2;
    for (int i=0;i<=nbins2;i++) {
      xbins2[i] = TMath::Exp(l10*(i*dx2-6.5));
   }

    plotname = Form("proj_MeanPE_fit_%i",iHV);
    proj_MeanPE_fit[iHV] = new TH1F(plotname,plotname,nbins2,xbins2);
    plotname = Form("proj_MeanPE_fit_err_%i",iHV);
    proj_MeanPE_fit_err[iHV] = new TH1F(plotname,plotname,nbins2,xbins2);
    plotname = Form("proj_MeanPE_estimate_%i",iHV);
    proj_MeanPE_estimate[iHV] = new TH1F(plotname,plotname,nbins2,xbins2);
   

    }*/
  }
} 

Double_t FitFun(Double_t *x, Double_t *par){
        
  Double_t sum,xx,A0,C0,r0,sigma0,mean1,sigma1,A1,C1,r1,mean2,sigma2,A2,C2,r2,mean3,sigma3,A3,C3,r3,mean4,sigma4,A4,C4,r4;
  Double_t k0=100.;
  const Double_t k1=1.6, k2=2.0, k3=2.0, k4=2.0;
  if(!pedmode) k0=2.0;
  /*Double_t k2=par[5];
   Double_t k3=par[5];
   Double_t k4=par[5];*/
  
  xx=x[0];  
  sigma0 = par[2]; // par[2] : width of ped peak   
  A0 = Nev/TMath::Exp(par[0]); // par[0] : poisson mean or log of this
  r0 = ((xx-par[1])/sigma0); // par[1] : location of ped peak
  C0 = 1/(sigma0* TMath::Exp(-k0*k0/2)/k0 +
          sigma0*sqrt(2*3.14159)*0.5*(1+TMath::Erf(k0/1.41421))); // norm correction for adding exp tail
  //sum = 1/(sqrt(2*3.14159)*par[2])*A0*TMath::Exp(-0.5*r0*r0);
  if(r0 < k0) sum = C0*A0*TMath::Exp(-0.5*r0*r0); // k0 : cutoff to switch to exp funtion
  else sum = C0*A0*TMath::Exp(0.5*k0*k0-k0*r0);
        
  mean1 = par[1]+par[3]; // par[3] : single SPE gain
  sigma1 = par[4]; // par[4] : width of single SPE peak
  A1 = A0*par[0];
  C1 = 1/(sigma1* TMath::Exp(-k1*k1/2)/k1 +
          sigma1*sqrt(2*3.14159)*0.5*(1+TMath::Erf(k1/1.41421)));
  r1 = ((xx-mean1)/sigma1);
  if(r1 < k1 && xx>par[1]-3.0*par[2]) sum += C1*A1*TMath::Exp(-0.5*r1*r1);
  //else if(r1 < k1 && xx<par[1]) sum += C1*A1*TMath::Exp(-0.5*r1*r1);
  else if(r1 < k1 && xx<par[1]) sum += 0;
  else sum += C1*A1*TMath::Exp(0.5*k1*k1-k1*r1);
  
  if(!pedmode){          
  mean2 = 2*par[3]+par[1];
  sigma2 = sqrt(2*sigma1*sigma1 - pow(par[2],2));
  A2 = A0*par[0]*par[0]/2;
  C2 = 1/(sigma2* TMath::Exp(-k2*k2/2)/k2 +
          sigma2*sqrt(2*3.14159)*0.5*(1+TMath::Erf(k2/1.41421)));
  r2 = ((xx-mean2)/sigma2);
  if(r2 < k2 && xx>par[1]-3.0*par[2]) sum += C2*A2*TMath::Exp(-0.5*r2*r2);
  //else if(r2 < k2 && xx<par[1]) sum += C1*A1*TMath::Exp(-0.5*r1*r1);
  else if(r2 < k2 && xx<par[1]) sum += 0;
  else sum += C2*A2*TMath::Exp(0.5*k2*k2-k2*r2);

 
  mean3 = 3*par[3]+par[1];
  sigma3 = sqrt(3*sigma1*sigma1 - 2*pow(par[2],2));
  A3 = A0*par[0]*par[0]*par[0]/6;
  //C3 = 1/(sigma3*sqrt(2*3.14159));
  C3 = 1/(sigma3* TMath::Exp(-k3*k3/2)/k3 + 
	  sigma3*sqrt(2*3.14159)*0.5*(1+TMath::Erf(k3/1.41421)));
  r3 = ((xx-mean3)/sigma3);
  if(r3 < k3 && xx>par[1]-3.0*par[2]) sum += C3*A3*TMath::Exp(-0.5*r3*r3);
  else if(r3 < k3 && xx<par[1]) sum += 0;
  else sum += C3*A3*TMath::Exp(0.5*k3*k3-k3*r3); 
  

  mean4 = 4*par[3]+par[1];
  sigma4 = sqrt(4*sigma1*sigma1 - 3*pow(par[2],2));
  A4 = A0*par[0]*par[0]*par[0]*par[0]/24;
  //C4 = 1/(sigma4*sqrt(2*3.14159));
  C4 = 1/(sigma4* TMath::Exp(-k4*k4/2)/k4 + 
	  sigma4*sqrt(2*3.14159)*0.5*(1+TMath::Erf(k4/1.41421)));
  r4 = ((xx-mean4)/sigma4);
  if(r4 < k4 && xx>par[1]-3.0*par[2]) sum += C4*A4*TMath::Exp(-0.5*r4*r4);
  else if(r4 < k4 && xx<par[1]) sum += 0;
  else sum += C4*A4*TMath::Exp(0.5*k4*k4-k4*r4);
  }
  
  return sum;
}


#endif
