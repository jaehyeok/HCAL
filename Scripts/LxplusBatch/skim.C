#include "TFile.h"
#include "TTree.h"
#include <iostream>
#include "TString.h"
#include "TROOT.h"

void skim(TString inputFile)
{


    TFile* fin = new TFile(inputFile);
    TTree* ch=(TTree*)fin->Get("hcalTupleTree/tree");
    if (ch==0x0) return;

    TString outputFile = inputFile;
    outputFile.ReplaceAll(".root","_skim.root");
    TFile *newfile= new TFile(outputFile,"recreate");
    TTree* evt_tree=(TTree*) ch->CloneTree(0, "fast");

    // set address of branch you want to use
    unsigned int run_ = 0;
    unsigned int ls_ = 0;
    unsigned int event_ = 0;
    ch->SetBranchAddress( "run"           , &run_     );
    ch->SetBranchAddress( "ls"          , &ls_     );
    ch->SetBranchAddress( "event"         , &event_     );

    for(int ievt = 0; ievt < ch->GetEntries() ;ievt++) {
        ch->GetEntry(ievt);

        // add cut here
        if(ievt%20!=0) continue;

        evt_tree->Fill();
    }

    newfile->cd();
    evt_tree->Write();
    newfile->Close();
}
