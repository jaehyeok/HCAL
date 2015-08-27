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
#include "TSystem.h"
#include "TTree.h"
#include<iostream>
#include<fstream>

using namespace std;

//SELF run, 3 long runs

void INT75MAP(int runnum1=3711,int runnum2=0)
{

  int runnum[2]={runnum1,runnum2};
  char canvname[100],label1[100];
  int RoboxN[9];
  TCanvas *c[10];
  int numofruns=1;

  //sprintf (canvname, "c%d",0);
  //c[0] = new TCanvas(canvname,"",0,0,1200,800);

  sprintf (canvname, "events5sigma eta phi");
  c[1] = new TCanvas(canvname,"",0,0,1200,900);
  //c[1]->Divide(1,3);
  sprintf (canvname, "events5sigma robox");
  c[2] = new TCanvas(canvname,"",0,0,1200,900);
  // c[2]->Divide(1,2);
  //c[2]->cd(1)->SetGridy();
  //c[2]->cd(2)->SetGridy();
  sprintf (canvname, "mean rms eta phi");
  c[3] = new TCanvas(canvname,"",0,0,1200,900);
  sprintf (canvname, "mean rms robox");
  c[4] = new TCanvas(canvname,"",0,0,1200,900);
  sprintf (canvname, "event5sigma VS eta");
  c[5] = new TCanvas(canvname,"",0,0,1200,900);
  
  sprintf (canvname, "events5sigma eta phi led");
  c[6] = new TCanvas(canvname,"",0,0,1200,900);
  //c[1]->Divide(1,3);
  sprintf (canvname, "events5sigma robox led");
  c[7] = new TCanvas(canvname,"",0,0,1200,900);
  // c[2]->Divide(1,2);
  //c[2]->cd(1)->SetGridy();
  //c[2]->cd(2)->SetGridy();
  sprintf (canvname, "mean rms eta phi led");
  c[8] = new TCanvas(canvname,"",0,0,1200,900);
  sprintf (canvname, "mean rms robox led");
  c[9] = new TCanvas(canvname,"",0,0,1200,900);
 
  
  TLine *bb_line[9];
  TFile *rootFile[2];

  char filename[100];
  char histname[100],PEDname[100],LEDname[100];
  char spigotname[100],bbname[100],title[100],dirname[100],label[100];
  //string type[2]={"Short","Long"};
  //printf ("%s %s %d %d \n",type[0].c_str(),type[1].c_str(),runnum[0],runnum[1]);


  int BB_MAP[24]={
    2, 3, 3, 3, 3, 2, 2, 3, 3, 3,
    3, 2, 1, 1, 2, 1, 2, 1, 1, 1,
    2, 1, 2, 1
  };

  int PMT_MAP[24]={
  5, 6, 5, 2,  1, 1, 7, 8,
  7, 4, 3, 3,  6, 5, 6, 1,
  2, 2, 8, 7,  8, 3, 4, 4
  };

  int chanMAP1[24]={
    10,8,9,7,11,6,22,20,21,19,23,18,
    4,2,3,1,5,0,16,14,15,13,17,12
  };
  int chanMAP2[24]={
    2,4,1,3,0,5,14,16,13,15,17,12,
    8,10,7,9,6,11,20,22,19,21,23,18
  };
  sprintf(label," ");
  for (int i=0;i<9;i++) {
    //   RoboxN[i]=getROBOX(runnum[i],sp[i]);
    // sprintf(canvname,"%d ",getROBOX(runnum[i],sp[i]));
    //  label=label+canvname;
    // printf("%d\n",RoboxN[i]);
  };
  sprintf(label1,"");
  int chk=0;
  float bin_cont=0;
  float x_coord[1000]={0};
  float y_coord[1000]={0};
  float count=0;
  float min=1000,max=-1;
  float values[2][3][3][8][1000]={0};
  float Ratio[3][3][8][1000]={0};
  float counter_first=0,counter_last=0,counter=0;
  float noise_first=0,noise_last=0,noise=0;
  int real_BB=0,real_PMT=0,real_CH=0,run3=0;
  double parm[10];


  TF1 *fitFunc = new TF1("fitFunc","gaus",4.,15.);
  sprintf(label1,"%d ", runnum1);
  //  sprintf (title, "noise %s",label1);
  //TH2D *noise_merged = new TH2D("noise_merged",title,216,0.0,216.0,20,0.0,20.0);
  //noise_merged->GetYaxis()->SetTitle("time, hours");
  sprintf (title, "PED mean %s",label1);
  TH2D *ped_mean = new TH2D("ped_mean",title,13,0,13,72,0.0,72);
  sprintf (title, "PED mean error%s", label1);
  TH2D *ped_mean_err = new TH2D("ped_mean_err",title,13,0,13,72,0.0,72.0);
  sprintf (title, "PED RMS  %s",label1);
  TH2D *ped_rms = new TH2D("ped_rms",title,13,0,13,72,0.0,72.0);
  sprintf (title, "PED RMS error%s",label1);
  TH2D *ped_rms_err = new TH2D("ped_rms_err",title,13,0,13,72,0.0,72.0);
  // ped_rms ->GetZaxis()->SetRangeUser(0,8);
  sprintf (title, "ped sigma %s",label1);
  TH2D *ped_sigma = new TH2D("ped_sigma",title,13,0,13,72,0.0,72.0);
  sprintf (title, "events out of 5sigma %s",label1);
  TH2D *ped_ev_sigma = new TH2D("ped_ev_sigma",title,13,0,13,72,0.0,72.0);
  
  sprintf(label1,"%d ", runnum2);
  sprintf (title, "led mean %s",label1);
  TH2D *led_mean = new TH2D("led_mean",title,13,0,13,72,0.0,72.0);
  sprintf (title, "led mean error%s",label1);
  TH2D *led_mean_err = new TH2D("led_mean_err",title,13,0,13,72,0.0,72.0);
  sprintf (title, "led rms %s",label1);
  TH2D *led_rms = new TH2D("led_rms",title,13,0,13,72,0.0,72.0);
  sprintf (title, "led rms error%s",label1);
  TH2D *led_rms_err = new TH2D("led_rms_err",title,13,0,13,72,0.0,72.0);
  sprintf (title, "led sigma %s",label1);
  TH2D *led_sigma = new TH2D("led_sigma",title,13,0,13,72,0.0,72.0);
  sprintf (title, "gain OV1 %s",label1);
  TH2D *gain_OV1 = new TH2D("gain_OV1",title,13,0,13,72,0.0,72.0);
  
  sprintf (title, "led mean OV2%s",label1);
  TH2D *led_meanOV2 = new TH2D("led_mean_OV2",title,13,0,13,72,0.0,72.0);
  sprintf (title, "led sigma OV2 %s",label1);
  TH2D *led_sigmaOV2 = new TH2D("led_sigma_OV2",title,13,0,13,72,0.0,72.0);
  sprintf (title, "gain OV2 %s",label1);
  TH2D *gain_OV2 = new TH2D("gain_OV2",title,13,0,13,72,0.0,72.0);
 sprintf(label1,"%d ", runnum1);
  sprintf (title, "PED mean ROBOX %s",label1);
  TH2D *ped_mean_robox = new TH2D("ped_mean_robox",title,24,0,24,36,0.0,36);
  sprintf (title, "PED mean error ROBOX%s", label1);
  TH2D *ped_mean_err_robox = new TH2D("ped_mean_err_robox",title,24,0,24,36,0.0,36.0);
  sprintf (title, "PED RMS ROBOX %s",label1);
  TH2D *ped_rms_robox = new TH2D("ped_rms_robox",title,24,0,24,36,0.0,36.0);
  sprintf (title, "PED RMS error ROBOX %s",label1);
  TH2D *ped_rms_err_robox = new TH2D("ped_rms_err_robox",title,24,0,24,36,0.0,36.0);
  sprintf (title, "ped sigma ROBOX %s",label1);
  TH2D *ped_sigma_robox = new TH2D("ped_sigma_robox",title,24,0,24,36,0.0,36.0);
  sprintf (title, "events out of 5sigma ROBOX%s",label1);
  TH2D *ped_ev_sigma_robox = new TH2D("ped_ev_sigma_robox",title,24,0,24,36,0.0,36.0);
   sprintf (title, "gain OV1 robox%s",label1);
  TH2D *gain_OV1_robox = new TH2D("gain_OV1_robox",title,24,0,24,36,0.0,36.0);
  sprintf(label1,"%d ", runnum2);
  sprintf (title, "LED mean ROBOX %s",label1);
  TH2D *led_mean_robox = new TH2D("led_mean_robox",title,24,0,24,36,0.0,36);
  sprintf (title, "LED mean error ROBOX%s", label1);
  TH2D *led_mean_err_robox = new TH2D("led_mean_err_robox",title,24,0,24,36,0.0,36.0);
  sprintf (title, "LED RMS ROBOX %s",label1);
  TH2D *led_rms_robox = new TH2D("led_rms_robox",title,24,0,24,36,0.0,36.0);
  sprintf (title, "LED RMS error ROBOX %s",label1);
  TH2D *led_rms_err_robox = new TH2D("led_rms_err_robox",title,24,0,24,36,0.0,36.0);
  
  sprintf(label1," %d ", runnum1);
  sprintf (title, "VS graph%s",label1);
  TH2D *ev_graph = new TH2D("ieta_VS_ev",title,13,29,42,25,0.0,1000.0);

  // sprintf (title, "average noise first 10h  %s",label1);
  //TH1D *average_noise_begin = new TH1D("average_noise_begin",title,216,0.0,216.0);
  //sprintf (title, "average noise last 10h  %s",label1);
  //TH1D *average_noise_end   = new TH1D("average_noise_end",title,216,0.0,216.0);
  TH1D *h[2][13][72];
  TH2D *h1[9], *h2[9];

  for (int ch=0;ch<13;ch++){
    sprintf(label,"#scale[1.0]{#color[%d]{ieta_%d}}",(int)(((ch%72)%13)/13)+2,ch+29);
    ped_ev_sigma->GetXaxis()->SetBinLabel(ch+1,label);
    ped_mean->GetXaxis()->SetBinLabel(ch+1,label);
    ped_rms->GetXaxis()->SetBinLabel(ch+1,label);
    ped_mean_err->GetXaxis()->SetBinLabel(ch+1,label);
    ped_rms_err->GetXaxis()->SetBinLabel(ch+1,label);
    ped_sigma->GetXaxis()->SetBinLabel(ch+1,label);
     led_mean->GetXaxis()->SetBinLabel(ch+1,label);
    led_rms->GetXaxis()->SetBinLabel(ch+1,label);
    led_mean_err->GetXaxis()->SetBinLabel(ch+1,label);
    led_rms_err->GetXaxis()->SetBinLabel(ch+1,label);
    //led_sigma->GetXaxis()->SetBinLabel(ch+1,label);
    gain_OV1->GetXaxis()->SetBinLabel(ch+1,label);
    gain_OV2->GetXaxis()->SetBinLabel(ch+1,label);
  }
  for (int ch=0;ch<24;ch++){
    sprintf(label,"#scale[0.7]{#color[%d]{pmt_%d}}",(int)(((ch%72)%24)/8)+1,(ch)%8+1);
    ped_ev_sigma_robox->GetXaxis()->SetBinLabel(ch+1,label);
    ped_mean_robox->GetXaxis()->SetBinLabel(ch+1,label);
    ped_rms_robox->GetXaxis()->SetBinLabel(ch+1,label);
    ped_mean_err_robox->GetXaxis()->SetBinLabel(ch+1,label);
    ped_rms_err_robox->GetXaxis()->SetBinLabel(ch+1,label);
    ped_sigma_robox->GetXaxis()->SetBinLabel(ch+1,label);
    
    led_mean_robox->GetXaxis()->SetBinLabel(ch+1,label);
    led_rms_robox->GetXaxis()->SetBinLabel(ch+1,label);
    led_mean_err_robox->GetXaxis()->SetBinLabel(ch+1,label);
    led_rms_err_robox->GetXaxis()->SetBinLabel(ch+1,label);
    gain_OV1_robox->GetXaxis()->SetBinLabel(ch+1,label);
  }
  for (int ch=1;ch<73;ch+=1){
    sprintf(label,"#scale[1.0]{iphi%d dep%d}",1+((ch-1)%36)*2,int((ch-1)/36)+1);
    ped_ev_sigma->GetYaxis()->SetBinLabel(ch,label);
    ped_mean->GetYaxis()->SetBinLabel(ch,label);
    ped_rms->GetYaxis()->SetBinLabel(ch,label);
    ped_mean_err->GetYaxis()->SetBinLabel(ch,label);
    ped_rms_err->GetYaxis()->SetBinLabel(ch,label);
    ped_sigma->GetYaxis()->SetBinLabel(ch,label);
      led_mean->GetYaxis()->SetBinLabel(ch,label);
    led_rms->GetYaxis()->SetBinLabel(ch,label);
    led_mean_err->GetYaxis()->SetBinLabel(ch,label);
    led_rms_err->GetYaxis()->SetBinLabel(ch,label);
    // led_sigma->GetYaxis()->SetBinLabel(ch,label);
    gain_OV1->GetYaxis()->SetBinLabel(ch,label);
    gain_OV2->GetYaxis()->SetBinLabel(ch,label);
  }
  for (int ch=1;ch<37;ch+=1){
    sprintf(label,"#scale[1.0]{ROBOX %d}",ch);
    ped_ev_sigma_robox->GetYaxis()->SetBinLabel(ch,label);
    ped_mean_robox->GetYaxis()->SetBinLabel(ch,label);
    ped_rms_robox->GetYaxis()->SetBinLabel(ch,label);
    ped_mean_err_robox->GetYaxis()->SetBinLabel(ch,label);
    ped_rms_err_robox->GetYaxis()->SetBinLabel(ch,label);
    ped_sigma_robox->GetYaxis()->SetBinLabel(ch,label);
    led_mean_robox->GetYaxis()->SetBinLabel(ch,label);
    led_rms_robox->GetYaxis()->SetBinLabel(ch,label);
    led_mean_err_robox->GetYaxis()->SetBinLabel(ch,label);
    led_rms_err_robox->GetYaxis()->SetBinLabel(ch,label);
    gain_OV1_robox->GetYaxis()->SetBinLabel(ch,label);
  }

  if (runnum2!=0) numofruns=2;
  	for (int run=0; run<numofruns; run++){
	  	  if (run==0)   sprintf (filename, "Run_%d.root",runnum1);
	  if (run==1) sprintf (filename, "Run_%d.root",runnum2);
	rootFile[run] = new TFile(filename,"READONLY");
	if ( rootFile[run]->IsOpen() )
	  {
	    printf ("%s \n",filename);
	 
	    for(int idepth=0; idepth<2; idepth++){printf("idepth %d\n",idepth);
	      for(int ieta=29; ieta<42; ieta++){printf("ieta %d\n",ieta);
		for(int iphi=0; iphi<71; iphi=iphi+2){printf("iphi %d\n",iphi);
		  // printf ("Histo_for_Depth_%d_Eta_%d_Phi_%d",idepth,ieta,iphi);
		  if ((ieta>39)&&(((iphi)%4)!=2)) {continue;}
		  sprintf (histname,"Histo_for_Depth_%d_Eta_%d_Phi_%d",idepth+1,ieta,iphi+1);
		  printf("%s \n",histname);
		  sprintf (dirname,"/Analyzer/CommonDir/ResPlotDir");
		  rootFile[run]->cd();
		  rootFile[run]->cd(dirname);
		  int irobox=(iphi+2)/2;
		  int bbnum,pmt,channum;
		   if (ieta==40) irobox++; 
		   if (irobox==37) irobox=1;
		   if (((irobox%2)==1)&&(ieta!=41)) {channum=chanMAP1[ieta-29+idepth*12];bbnum=BB_MAP[channum];pmt=PMT_MAP[channum];}
		   if (((irobox%2)==1)&&(ieta==41)) {channum=chanMAP1[ieta-30+idepth*12];bbnum=BB_MAP[channum];pmt=PMT_MAP[channum];}
		   if (((irobox%2)==0)&&(ieta!=41)) {channum=chanMAP2[ieta-29+idepth*12];bbnum=BB_MAP[channum];pmt=PMT_MAP[channum];}
		   if (((irobox%2)==0)&&(ieta==41)) {channum=chanMAP2[ieta-30+idepth*12];bbnum=BB_MAP[channum];pmt=PMT_MAP[channum];}
		   h[idepth][ieta-29][iphi] = (TH1D*)gDirectory->Get(histname)->Clone();
		  //	   sprintf (histname,"LED_HVset_4_sp_%d_BB_%d",sp[run],bbnum);
		  //	  h1[run]=(TH2D*)gDirectory->Get(histname)->Clone();

		   if (run==0){
		     //TH1D *pr= h[idepth][ieta][iphi]->ProjectionX("b",pmt,pmt);
		     h[idepth][ieta-29][iphi] ->GetXaxis()->SetRangeUser(0,10000);
		     printf("Mean=%d RMS=%d\n",h[idepth][ieta-29][iphi]->GetMean(),h[idepth][ieta-29][iphi]->GetRMS());
		     ped_mean->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetMean());
		     ped_rms->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetRMS());
		     ped_mean_err->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetMeanError());
		     ped_rms_err->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetRMSError());
		     ped_mean_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetMean());
		     ped_rms_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetRMS());
		     ped_mean_err_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetMeanError());
		     ped_rms_err_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetRMSError());
		     //  continue;
		     if (h[idepth][ieta-29][iphi]->GetEntries()>500 ){
		       // h[idepth][ieta-29][iphi]->Fit("fitFunc","","",0, 40);
		        h[idepth][ieta-29][iphi]->Fit("fitFunc","","",0, h[idepth][ieta-29][iphi]->GetMean()+5);
		       h[idepth][ieta-29][iphi]->GetFunction("fitFunc")->GetParameters(parm);}else {parm[2]=0,parm[1]=0;}
		     //if(j==1)val=Ptmp->GetRMS();
		     //CH[i-1]->Fill(j,Ptmp->GetRMS()/val);
		     //if(j==1)val=parm[2];
		     
		     ped_sigma->SetBinContent(ieta-28,iphi/2+idepth*36+1,parm[2]);
		     
		     h[idepth][ieta-29][iphi] ->GetXaxis()->SetRangeUser(parm[1]+5*parm[2],10000);
		     ped_ev_sigma->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->Integral());
		     ped_sigma_robox->SetBinContent((bbnum-1)*8+pmt,irobox,parm[2]);

		   
		     ped_ev_sigma_robox->SetBinContent((bbnum-1)*8+pmt,irobox,h[idepth][ieta-29][iphi]->Integral());
		   }
		   	   if (run==1){
		     //TH1D *pr= h[idepth][ieta][iphi]->ProjectionX("b",pmt,pmt);
		     h[idepth][ieta-29][iphi] ->GetXaxis()->SetRangeUser(0,10000);
		     printf("Mean=%d RMS=%d\n",h[idepth][ieta-29][iphi]->GetMean(),h[idepth][ieta-29][iphi]->GetRMS());
		     led_mean->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetMean());
		     led_rms->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetRMS());
		     led_mean_err->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetMeanError());
		     led_rms_err->SetBinContent(ieta-28,iphi/2+idepth*36+1, h[idepth][ieta-29][iphi]->GetRMSError());
		     led_mean_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetMean());
		     led_rms_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetRMS());
		     led_mean_err_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetMeanError());
		     led_rms_err_robox->SetBinContent((bbnum-1)*8+pmt,irobox, h[idepth][ieta-29][iphi]->GetRMSError());
		    
		     }
		    //  TH1D *pr1= h1[run]->ProjectionX("a",pmt,pmt);
		    //	TH1D *pr2= h2[run]->ProjectionX("a",pmt,pmt);
		    //		pr1->Fit("fitFunc","","",0,1000000);
		    //	pr1 ->GetXaxis()->SetRangeUser(50,1000000);
		    //	pr1->GetFunction("fitFunc")->GetParameters(parm);
		    //	led_mean->SetBinContent(8*(bbnum-1)+pmt,run+1,parm[1]);
		    //	led_sigma->SetBinContent(8*(bbnum-1)+pmt,run+1,parm[2]);
		    //  led_mean->SetBinContent(8*(bbnum-1)+pmt,run+1,pr1->GetMean());
		    //  led_rms->SetBinContent(8*(bbnum-1)+pmt,run+1,pr1->GetRMS());
		    //  led_mean_err->SetBinContent(8*(bbnum-1)+pmt,run+1,pr1->GetMeanError());
		    //  led_rms_err->SetBinContent(8*(bbnum-1)+pmt,run+1,pr1->GetRMSError());
		    //  led_sigma->SetBinContent(8*(bbnum-1)+pmt,run+1,pr1->GetRMS());
	
		    // if ((h[idepth][ieta-29][iphi]->Integral()>300)&&(iphi>45)) {c[2]->cd(); h[idepth][ieta-29][iphi]->Draw(); }
		}	
	      } 
	    }
	  }


          delete rootFile[run];	
	}
	
	gStyle->SetOptStat(1111111);
	//gStyle->SetOptStat(0);
       
          ped_mean->GetXaxis()->SetTickLength(0);
          ped_mean->GetYaxis()->SetTickLength(0);
          ped_ev_sigma->GetXaxis()->SetTickLength(0);
          ped_ev_sigma->GetYaxis()->SetTickLength(0);
	  ped_rms->GetYaxis()->SetTickLength(0);
	  ped_sigma->GetYaxis()->SetTickLength(0);
	   led_mean->GetYaxis()->SetTickLength(0);
	   led_rms->GetYaxis()->SetTickLength(0);
       


    

	  gStyle->SetPaintTextFormat(".1f");


	  //TH1D begin

	   sprintf (title, "PED mean  %s",label1);
	   TH1D *ped_mean1 = new TH1D("PED_mean",title,40,ped_mean->GetMinimum()-5,ped_mean->GetMaximum()+5);
	      //TH1D *ped_mean1 = new TH1D("PED_mean",title,100,0,3000);
	   sprintf (title, "PED RMS %s",label1);
	   TH1D *ped_rms1 = new TH1D("ped_rms",title,100,ped_rms->GetMinimum()-5,ped_rms->GetMaximum()+5);
	  sprintf (title, "ped sigma %s",label1);
	  TH1D *ped_sigma1 = new TH1D("ped_sigma",title,40,ped_sigma->GetMinimum()-5,ped_sigma->GetMaximum()+5);
	  sprintf (title, "events out of 5sigma %s",label1);
	  TH1D *ped_ev_sigma1 = new TH1D("ped_ev_sigma",title,40,0,ped_ev_sigma->GetMaximum()+5);
	  	  sprintf (title, "led mean %s",label1);
	  TH1D *led_mean1 = new TH1D("led_mean",title,40,led_mean->GetMinimum()-5,led_mean->GetMaximum()+5);
	  sprintf (title, "led rms %s",label1);
	  TH1D *led_rms1 = new TH1D("led_rms",title,40,led_rms->GetMinimum()-5,led_rms->GetMaximum()+5);
	  sprintf (title, "gain OV1 %s",label1);
	  TH1D *gain_OV11 = new TH1D("gain_OV11",title,25,100000,800000);
	  sprintf (title, "gain OV1 robox %s",label1);
	  TH1D *gain_OV11_robox = new TH1D("gain_OV11_robox",title,100,10000,800000);
	  sprintf (title, "gain OV2 %s",label1);
	  TH1D *gain_OV21 = new TH1D("gain_OV21",title,80,10000,800000);
	  sprintf (title, "PED mean ROBOX %s",label1);
	   TH1D *ped_mean1_robox = new TH1D("PED_mean ROBOX",title,40,ped_mean_robox->GetMinimum()-5,ped_mean_robox->GetMaximum()+5);
	      //TH1D *ped_mean1 = new TH1D("PED_mean",title,100,0,3000);
	   sprintf (title, "PED RMS ROBOX %s",label1);
	   TH1D *ped_rms1_robox = new TH1D("ped_rms_robox",title,100,ped_rms_robox->GetMinimum()-5,ped_rms_robox->GetMaximum()+5);
	  sprintf (title, "ped sigma ROBOX%s",label1);
	  TH1D *ped_sigma1_robox = new TH1D("ped_sigma_robox",title,40,ped_sigma_robox->GetMinimum()-5,ped_sigma_robox->GetMaximum()+5);
	  sprintf (title, "events out of 5sigma ROBOX%s",label1);
	  TH1D *ped_ev_sigma1_robox = new TH1D("ped_ev_sigma_robox",title,40,0,ped_ev_sigma_robox->GetMaximum()+5);
	  	  sprintf (title, "led mean %s",label1);
	  sprintf (title, "LED mean ROBOX %s",label1);
	   TH1D *led_mean1_robox = new TH1D("LED_mean ROBOX",title,40,led_mean_robox->GetMinimum()-5,led_mean_robox->GetMaximum()+5);
	      //TH1D *ped_mean1 = new TH1D("PED_mean",title,100,0,3000);
	   sprintf (title, "LED RMS ROBOX %s",label1);
	   TH1D *led_rms1_robox = new TH1D("led_rms_robox",title,100,led_rms_robox->GetMinimum()-5,led_rms_robox->GetMaximum()+5);
	   sprintf (title, "ped sigma ROBOX%s",label1);
	  //TH1D end
		
	    for(int ieta=29;ieta<42;ieta++){
	      for(int iphi=0;iphi<72;iphi++){
		if ((ieta>39)&&(((iphi)%2)==0)) {continue;}
		ped_mean1->Fill(ped_mean->GetBinContent(ieta-29+1,iphi+1));
		ped_rms1->Fill(ped_rms->GetBinContent(ieta-29+1,iphi+1));
		ped_ev_sigma1->Fill(ped_ev_sigma->GetBinContent(ieta-29+1,iphi+1));
		if (ped_ev_sigma->GetBinContent(ieta-29+1,iphi+1)>50) ev_graph->Fill(ieta,ped_ev_sigma->GetBinContent(ieta-29+1,iphi+1));
		ped_sigma1->Fill(ped_sigma->GetBinContent(ieta-29+1,iphi+1));

			led_mean1->Fill(led_mean->GetBinContent(ieta-29+1,iphi+1));
			led_rms1->Fill(led_rms->GetBinContent(ieta-29+1,iphi+1));
	      }
	    }
	
	    for(int irobox=1;irobox<25;irobox++){
	      for(int ipmt=1;ipmt<37;ipmt++){
	
		ped_mean1_robox->Fill(ped_mean_robox->GetBinContent(irobox,ipmt));
		ped_rms1_robox->Fill(ped_rms_robox->GetBinContent(irobox,ipmt));
		ped_ev_sigma1_robox->Fill(ped_ev_sigma_robox->GetBinContent(irobox,ipmt));
		ped_sigma1_robox->Fill(ped_sigma_robox->GetBinContent(irobox,ipmt));
			led_mean1_robox->Fill(led_mean_robox->GetBinContent(irobox,ipmt));
			led_rms1_robox->Fill(led_rms_robox->GetBinContent(irobox,ipmt));

	      }
	    }
	    if (numofruns==2){
	      for(int Robox=1;Robox<37;Robox++){
		for(int pmt=1;pmt<25;pmt++){
		  double rms2=(led_rms_robox->GetBinContent(pmt,Robox)*led_rms_robox->GetBinContent(pmt,Robox))-(ped_sigma_robox->GetBinContent(pmt,Robox)*ped_sigma_robox->GetBinContent(pmt,Robox));
		  double enf_mean = 1.15*(led_mean_robox->GetBinContent(pmt,Robox)-ped_mean_robox->GetBinContent(pmt,Robox));
		  double gain =(2.6/1.6) * (rms2 / (enf_mean)) * 10000.;
		  gain_OV1_robox->SetBinContent(pmt,Robox,gain/1000);
		  // if ((pmt>0)&&(pmt<9)) 
		  gain_OV11_robox->Fill(gain);
		  
		  
		  
		};
	      };
	    };
	  ped_mean->SetStats(0);
	  ped_ev_sigma->SetStats(0);
	  ped_rms->SetStats(0);
	  ped_sigma->SetStats(0);
	  ped_mean_robox->SetStats(0);
	  ped_ev_sigma_robox->SetStats(0);
	  ped_rms_robox->SetStats(0);
	  ped_sigma_robox->SetStats(0);
	  led_mean->SetStats(0);
	  led_rms->SetStats(0);
	  gain_OV1_robox->SetStats(0);
	  gain_OV2->SetStats(0);
	 
	  //ped_mean->GetZaxis()->SetRangeUser(20,60);
	  //ped_ev_sigma->GetZaxis()->SetRangeUser(0,40);
	  // ped_rms->GetZaxis()->SetRangeUser(0,8);
	  //ped_sigma->GetZaxis()->SetRangeUser(0,8);
	  //	  led_mean->GetZaxis()->SetRangeUser(50,600);
	  //	  led_sigma->GetZaxis()->SetRangeUser(0,600);

	  // ped_mean1->GetXaxis()->SetRangeUser(20,60);
	  //ped_ev_sigma1->GetXaxis()->SetRangeUser(0,40);
	  // ped_rms1->GetXaxis()->SetRangeUser(0,8);
	  //ped_sigma1->GetXaxis()->SetRangeUser(0,8);
	  //	  led_mean1->GetXaxis()->SetRangeUser(100,600);
	  //	  led_sigma1->GetXaxis()->SetRangeUser(0,600);





	  c[3]->Divide(2,2);
          c[3]->cd(1);
	 
          ped_mean->Draw("textcolz");
	  c[3]->cd(2);
	  gPad->SetLogy();
	  ped_mean1->Draw();
	  c[4]->Divide(2,2);
	  c[3]->cd(3);
	  
	  ped_rms->Draw("textcolz");

	  c[3]->cd(4);
	  gPad->SetLogy();
	  ped_rms1->Draw();
	  c[4]->cd(3);
	  ped_rms_robox->Draw("textcolz");
	  //led_mean->Draw("textcolz");
	  c[4]->cd(4);	  
	  gPad->SetLogy();
	  ped_rms1_robox->Draw();
	 

	  c[1]->Divide(2,2);
	  c[1]->cd(1);
	  ped_ev_sigma->Draw("textcolz");
	  c[1]->cd(2);
	  gPad->SetLogy();
	  ped_ev_sigma1->Draw();
	  c[1]->cd(3);
	  ped_sigma->Draw("textcolz");
	  c[1]->cd(4);
	  gPad->SetLogy();
	  ped_sigma1->Draw();
	  //c[2]->Divide(2,2);
	  c[4]->cd(1);
	  ped_mean_robox->Draw("textcolz");
	  // led_mean1->Draw();
	  c[4]->cd(2);
	  gPad->SetLogy();
	  ped_mean1_robox->Draw();


	  c[2]->Divide(2,2);
	   c[2]->cd(1);
	   ped_ev_sigma_robox->Draw("textcolz");
	  // ped_rms_inc->Draw("textcolz");
	   c[2]->cd(2);
	   gPad->SetLogy();
	   ped_ev_sigma1_robox->Draw();

	    c[2]->cd(3);
	    ped_sigma_robox->Draw("textcolz");
	    // gain_OV1->Draw("textcolz");
	  c[2]->cd(4);
	  gPad->SetLogy();
	  ped_sigma1_robox->Draw();
	 
	  // c[2]->cd(1);
	  // gain_OV2->Draw("textcolz");
	  // c[2]->cd(2);
	  // gPad->SetLogy();*/
	  // gain_OV21->Draw();
	  c[5]->cd();
	  ev_graph->Draw();

	  
	  c[6]->Divide(2,2);
	  c[6]->cd(1);
	  led_mean->Draw("textcolz");
	  c[6]->cd(2);
	  gPad->SetLogy();
	  led_mean1->Draw();
	  c[6]->cd(3);
	  led_mean_robox->Draw("textcolz");
	  c[6]->cd(4);
	  gPad->SetLogy();
	  led_mean1_robox->Draw();
	 
	  c[7]->Divide(2,2);
	  c[7]->cd(1);
	  led_rms->Draw("textcolz");
	  c[7]->cd(2);
	  gPad->SetLogy();
	  led_rms1->Draw();
	  c[7]->cd(3);
	  
	  led_rms_robox->Draw("textcolz");
	  c[7]->cd(4);
	  gPad->SetLogy();
	  led_rms1_robox->Draw();
	  c[8]->cd();
	  gain_OV1_robox->Draw("textcolz");
	  c[9]->cd(); 
	  gPad->SetLogy();
	  gain_OV11_robox->Draw();
	  if (chk==1) printf("in this loop %s",canvname);
	

}

