#define myClassBKG_cxx
#include "myClassBKG.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void myClassBKG::Loop()
{
//   In a ROOT session, you can do:
//      root> .L myClassBKG.C
//      root> myClassBKG t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

//////////////////////////
//
////////////CMS PLOTTING STYLE 


///////////////////////////
//
//
//
/////////// HISTOGRAMS //////
  TH1F *h1 = new TH1F("h1", "AllcosThetaStar", 100, -1.1, 1.1);
  TH1F *h2 = new TH1F("h2", "HighPTcosthetastar", 100, -1.1, 1.1);
  TH1F *h3 = new TH1F("h3", "RECOggcosthetastar", 100, -1.1, 1.1);
  TH1F *h4 = new TH1F("h4", "RECOqqbarcosthetastar", 100, -1.1, 1.1);
  TH1F *h5 = new TH1F("h5", "GENALL", 100, -1.1, 1.1);
  TH1F *h6 = new TH1F("h6", "GEN-gg", 100, -1.1, 1.1);
  TH1F *h7 = new TH1F("h7", "GEN-qqbar", 100, -1.1, 1.1);
  TH1F *reco = new TH1F("reco", "RECO", 100, -1.1, 1.1); 
 
 //Counters
 int N_reco = 0; 
 int N_total = 0; 
 int N_diphoton = 0; 
 int N_gluglu = 0;
 int N_qqbar = 0; 
 int N_GENdiphoton = 0; 
 int N_GENgluglu = 0; 
 int N_GENqqbar = 0; 
  //////////////////////////////////
  //
  //
  //
  ////////// LOOP OVER EVENTS///////
  
  if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      N_total++;
      /////////////////////////////////////
      //
      //
      /////////// FILL HISTOGRAMS //////// 
      //RECO no cuts  
      reco->Fill(Diphoton_cosThetaStar, Event_weight);   
      //----- GEN
      //gg
     if ((GenPhoton1_pt>0) && (GenPhoton2_pt>0)){
      N_GENdiphoton++; 
      h5->Fill(GenDiphoton_cosThetaStar, Event_weight);    
   
      if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){
       N_GENgluglu++; 
       h6->Fill(GenDiphoton_cosThetaStar, Event_weight);
       }//gg init 
      else{//qqbar init
       N_GENqqbar++; 
       h7->Fill(GenDiphoton_cosThetaStar, Event_weight);
      }
   }//END GEN 

      //----- RECO
      //*** High_pt == true  
      //if ((Photon1_pt>0) && (Photon2_pt)){
     // h1->Fill(Diphoton_cosThetaStar, Event_weight);
   
      if ((Photon1_passHighPtID==true)&& (Photon2_passHighPtID==1)) continue;
      N_diphoton++;
      h2->Fill(Diphoton_cosThetaStar, Event_weight);
      if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){
        N_gluglu++; 
        h3->Fill(Diphoton_cosThetaStar, Event_weight);
       }// gg init 
      else{
       N_qqbar++;
       h4->Fill(Diphoton_cosThetaStar, Event_weight);
      }//qqbar init
   //   }//end RECO 
   }//end of event loop

////////////////////////
//
////// EVENTS COUNT

   cout << "number of events" << " " << N_total << endl;
   cout << "number of gluglu initiated events" << " " << N_gluglu << endl;
   cout << "number of qqbar initiated events" << " " << N_qqbar << endl;
   cout << "Reco Diphoton" << " " << N_diphoton << " " << "vs " << N_qqbar + N_gluglu << " Sum of gg & qqbar initiated events" << endl;

   cout << "=======================================================================" << endl; 
   cout << "GEN PHOTONS" << "" << N_GENdiphoton << endl;    
   cout << "number of GEN gluglu initiated events" << " " << N_GENgluglu << endl;
   cout << "number of GEN qqbar initiated events" << " " << N_GENqqbar << endl; 
   cout << "GENDiphoton events" << " " << N_GENdiphoton << " " << "vs" << N_GENgluglu + N_GENqqbar << endl;

////////////////////////
//
/////// CANVAS SET-UP

   TCanvas *RECOSMBkg = new TCanvas("RECOSMBkg", "", 800, 600);   
   reco->SetLineColor(kRed-2);
   reco->SetFillColor(kOrange-3);
   reco->Draw(); 
   RECOSMBkg->SetLeftMargin(0.15); 
   RECOSMBkg->SetBottomMargin(0.15);
   reco->GetYaxis()->SetTitle("Events");
   reco->GetXaxis()->SetTitle("cos#theta*"); 

   TCanvas *GENgluon = new TCanvas("GENgluon", "", 800, 600); 
   h6->SetLineColor(kRed-2); 
   h6->SetFillColor(kOrange-3); 
   h6->Draw(); 
   GENgluon->SetLeftMargin(0.15); 
   GENgluon->SetBottomMargin(0.15); 
   h6->GetYaxis()->SetTitle("Events"); 
   h6->GetXaxis()->SetTitle("cos#theta*");
   
   TCanvas *GENqqbar = new TCanvas("GENqqbar", "", 800, 600); 
   h7->SetLineColor(kRed-2);
   h7->SetFillColor(kOrange-3); 
   h7->Draw(); 
   GENqqbar->SetLeftMargin(0.15); 
   GENqqbar->SetBottomMargin(0.15); 
   h7->GetYaxis()->SetTitle("Events"); 
   h7->GetXaxis()->SetTitle("cos#theta*");  

///////////////////////////////////
//
////////SAVE OUTPUT 
//***** Save histograms to root file 
//TFile *f = new TFile("Exodiphbkg.root", "RECREATE");
//***** Save as pdf/.C/.png 
//
//***** Change directory and close directory
//f->cd();
//f->Close();
}//end of method 

