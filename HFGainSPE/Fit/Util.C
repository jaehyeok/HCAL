#include <iostream>
#include <cmath>

#include "Util.h"
#include "TLine.h"
#include "TLatex.h"
#include "TMarker.h"
#include "TPave.h"
#include "TH1.h"
#include "TH1F.h"
#include "TMath.h"
#include "TStyle.h"
#include "TColor.h"

using namespace std;

/*void myText(Double_t x,Double_t y, const char *text, Color_t color,float tsize) {

//Double_t tsize=0.05;
TLatex l; //l.SetTextAlign(12); 
l.SetTextSize(tsize); 
l.SetNDC();
l.SetTextColor(color);
l.DrawLatex(x,y,text);
}*/

/*void h1cosmetic(TH1F* &h1, char* title, int linecolor, int linewidth, int fillcolor, TString var){

  h1->SetLineColor(linecolor);
  h1->SetLineWidth(linewidth);
  h1->SetFillColor(fillcolor);
  h1->SetTitle(title);
  h1->SetXTitle(var);
  h1->SetStats(0);
  h1->SetMinimum(0.1);

  }*/

void Testing(){
  cout<<"hello world"<<endl;
}

double deltaPhi(double phi1, double phi2){
  //assumes both are -pi<phi<pi
  double delphi = TMath::Abs(phi1 - phi2);
  if(delphi>TMath::Pi()) delphi -= TMath::Pi();
  return delphi;
  
}

double deltaR(double eta1, double phi1, double eta2, double phi2){
  double dr = sqrt( pow((eta1-eta2),2) + pow(deltaPhi(phi1,phi2),2) );
  return dr;
}

void h1cosmetic(TH1F* &h1, char* title, int linecolor, int linewidth, int fillstyle, TString var,TString yvar,bool print){

  h1->SetLineColor(linecolor);
  h1->SetLineWidth(linewidth);
  h1->SetFillColor(linecolor);
  //h1->SetFillColorAlpha((Color_t)linecolor,fillalpha);
  h1->SetFillStyle(fillstyle);
  h1->SetTitle(title);
  h1->SetXTitle(var);
  h1->SetYTitle(yvar);
  if(!print) h1->SetStats(111111);
  if(print) h1->SetStats(0);
  //h1->SetMinimum(0.1);
  //h1->SetMaximum(1.1*h1->GetMaximum());
  h1->GetXaxis()->SetTitleSize(0.05); 
  h1->GetXaxis()->SetTitleOffset(0.9);
  h1->GetYaxis()->SetTitleSize(0.05); 
  h1->GetYaxis()->SetTitleOffset(1.0); 
  int min = h1->FindFirstBinAbove(0);
  int max = h1->FindLastBinAbove(0);
  h1->GetXaxis()->SetRange(0.9*min,1.1*max);
}

void setLabels(TH2F* &h2, int mode , bool plus)
{
  if(mode ==1){
    for(int i=0;i<24;i++){
      int bb = i/8 +1;
      TString label = Form("%i",(i % 8)+1);
      h2->GetXaxis()->SetBinLabel(i+1,label);
      
    }
    
    // h2->GetXaxis()->LabelsOption("v");
    h2->GetYaxis()->SetTitleOffset(1.28);
    //h2->GetXaxis()->SetTitleOffset(1.1);
    gPad->SetLeftMargin(0.14);
    //gPad->SetRightMargin(0.12);
    for(int j=1;j<37;j++){
      TString label;
      if(plus) label = Form("HFP %i",j);
      else label = Form("HFM %i",j);
      h2->GetYaxis()->SetBinLabel(j,label);
        

    }
    
    
			
  }


}


void h2cosmetic(TH2F* &h2, char* title, TString var,TString yvar,bool print, bool plus, bool map, int mode){
  
  /* h2->SetLineColor(linecolor);
     h2->SetLineWidth(linewidth);
     h2->SetFillColor(linecolor);
     //h2->SetFillColorAlpha((Color_t)linecolor,fillalpha);
     h2->SetFillStyle(fillstyle);*/
  h2->SetTitle(title);
  h2->SetTitleSize(0.05);
  h2->SetXTitle(var);
  h2->SetYTitle(yvar);
  if(!print) h2->SetStats(111111);
  if(print) h2->SetStats(0);
  //h2->SetMinimum(0.1);
  //h2->SetMaximum(1.1*h2->GetMaximum());
  h2->GetXaxis()->SetTitleSize(0.05); 
  h2->GetXaxis()->SetTitleOffset(1.0);
  h2->GetYaxis()->SetTitleSize(0.05); 
  h2->GetYaxis()->SetTitleOffset(0.9); 
  float min = h2->GetMinimum(0.000000001); //FIX THIS
  h2->SetAxisRange(min,h2->GetMaximum(),"Z");

  if(map) {setLabels(h2,mode,plus);
  }
}

void myText(Double_t x,Double_t y, const char *text, Color_t color,float tsize) {

  //Double_t tsize=0.05;
  TLatex l; //l.SetTextAlign(12); 
  l.SetTextSize(tsize); 
  l.SetNDC();
  l.SetTextColor(color);
  l.DrawLatex(x,y,text);
}

void set_plot_style()
{
  const Int_t NRGBs = 5;
  const Int_t NCont = 100;

  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
}



void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

  // For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

  // For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

  // For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

  // For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  //tdrStyle->SetErrorMarker(20);
  tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

  //For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

  // For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

  // Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.13);
  tdrStyle->SetPadRightMargin(0.05);

  // For the Global title:

  //  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

  // For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.05);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

  // For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

  // For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

  // Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);
  tdrStyle->SetPalette(1);
  // Postscript options:
  // tdrStyle->SetPaperSize(15.,15.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();
}
