#ifndef __UTIL_H
#define __UTIL_H

#include "TString.h"
#include "TH1F.h"

//void myText(Double_t x,Double_t y, const char *text, Color_t color=1, float tsize=0.05);
//void h1cosmetic(TH1F* &h1, char* title, int linecolor=kRed, int linewidth=1, int fillcolor=0, TString var="");
void Testing();
double deltaPhi(double phi1, double phi2);
double deltaR(double eta1, double phi1, double eta2, double phi2);
void h1cosmetic(TH1F* &h1, char* title=(char*)"", int linecolor=kRed, int linewidth=2, int fillstyle=0, TString var="",TString yvar="A.U.",bool print=true);
void h2cosmetic(TH2F* &h2, char* title=(char*)"", TString var="",TString yvar="",bool print=true, bool plus=true, bool map=true, int mode=1);
void setLabels(TH2F* &h2, int mode, bool plus);
void myText(Double_t x=0.5,Double_t y=0.5, const char *text=(char*)"" , Color_t color=1,float tsize=0.05);
void set_plot_style();
void setTDRStyle();
#endif
