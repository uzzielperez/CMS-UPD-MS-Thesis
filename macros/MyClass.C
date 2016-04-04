#define MyClass_cxx
//#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "MyClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TTree.h>
#include <TLatex.h>
#include <TBox.h>
#include <TF1.h>
#include <TPad.h>
#include <stdio.h>
#include <math.h>
#include <TMath.h>
#include <TH1D.h>

/*/TCanvas* headtail() {
  // set default graphics options
   TStyle* edstyle = new TStyle("Plain","Edstyle");
   edstyle->cd();
   edstyle->SetLabelSize(0.05,"XYZ");
   edstyle->SetLabelOffset(0.01,"XYZ");
   edstyle->SetTitleXSize(0.05);
   edstyle->SetTitleYSize(0.05);
   edstyle->SetTitleXOffset(1.2);
   edstyle->SetTitleYOffset(1.4);
   edstyle->SetOptStat(0);}
*/

void MyClass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MyClass.C
//      root> MyClass t
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

   //==== Load Macrosi
   //gROOT->LoadMacro("tdrstyle.C);
  // setTDRStyle();
   //gROOT->LoadMacro("CMS_lumi.C");
    writeExtraText = true;       // if extra text
    //extraText  = "Preliminary";  // default extra text is "Preliminary"
    extraText = "work in progress";
    lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
    lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
    lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

    int iPeriod = 3;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

    // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
    // iPos=11 : top-left, left-aligned
    // iPos=33 : top-right, right-aligned
    // iPos=22 : center, centered
    // mode generally : 
    //     iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)  

 
    //===== Histograms 
   TH1F *h1 = new TH1F("h1", "AllcosThetaStar", 100, -1.1, 1.1);  
   TH1F *h2 = new TH1F("h2", "HighPTcosThetaStar", 100, -1.1, 1.1);
   TH1F *gg = new TH1F("gg", "gg cosThetaStar",100, -1.05,1.05);
   TH1F *qq = new TH1F("qq", "qqbar cosThetaStar",100, -1.05,1.05); 
   TH1F *ggstable = new TH1F("ggstable", "gg genstable", 100, -1.1, 1.1);
   TH1F *qqbarstable = new TH1F("qqbarstable", "qqbar genstable", 100, -1.1, 1.1);  
   TH1F *ggUnstable = new TH1F("ggUnstable", "gg genUnstable", 100, -1.1, 1.1);
   TH1F *qqbarUnstable = new TH1F("qqbarUnstable", "qqbar genUnstable", 100, -1.1, 1.1);  
   TH1F *old1 = new TH1F("old1", "ALLcosThetStarold", 100, -1.05, 1.05 ); 
   TH1F *old2 = new TH1F("old2", "HighPTcosThetaStarold", 100, -1.05, 1.05);
   TH1F *ggold = new TH1F("ggold", "gg cosThetaStarold",100, -1.05,1.05);
   TH1F *qqold = new TH1F("qqold", "qqbar cosThetaStarold",100, -1.05,1.05);   
       //===== Counters
   int N_total = 0;
   int N_diphoton = 0;
   int total_selected = 0;
   int N_photon1 = 0;
   int N_photon2 = 0;
   int N_gluglu = 0;
   int N_qqbar = 0;
   int N_gggenunstable = 0;
   int N_ggstable = 0; 
   int N_qqgenunstable = 0;
   int N_qqstable = 0;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
  //==== Loop over the events
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
     N_total++;
      
     h1->Fill(Diphoton_cosThetaStar, Event_weight);
     old1->Fill(Diphoton_cosThetaStarOld, Event_weight);

     //========GEN UNSTABLE 
        if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){
            ggUnstable->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);  
         }
        else{
             qqbarUnstable->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);
        }

    

     //============== EVENTS WITH 2 RECO PHOTONS
     if ((Photon1_passHighPtID>=1)&& (Photon2_passHighPtID>=1)) continue;  
     h2->Fill(Diphoton_cosThetaStar, Event_weight);
     old2->Fill(Diphoton_cosThetaStarOld, Event_weight);
     N_diphoton++;
     
           
      //============= INTERACTING PARTONS
      //GLUON FUSION
      if ((Photon1_passHighPtID>=1)&& (Photon2_passHighPtID>=1)) continue;
        if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){
           gg->Fill(Diphoton_cosThetaStar, Event_weight);
           ggstable->Fill(GenDiphotonStable_cosThetaStar, Event_weight);
          // ggUnstable->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);
           ggold->Fill(Diphoton_cosThetaStarOld, Event_weight);

           N_gluglu++;
           N_gggenunstable++;
           N_ggstable++; 
         }
      //QUARK ANNIHILATION
        else{
          qq->Fill(Diphoton_cosThetaStar, Event_weight);
          qqbarstable->Fill(GenDiphotonStable_cosThetaStar, Event_weight);
          //qqbarUnstable->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);
          qqold->Fill(Diphoton_cosThetaStarOld, Event_weight);


          N_qqbar++;
          N_qqgenunstable++;
          N_qqstable++;
          cout << "Interacting Partons" << " " << Event_interactingParton1PdgId << " " << Event_interactingParton2PdgId << endl;
          }

     //============= GEN PARTICLE DISTRIBUTION 
     //*********Some notes. Histogram filling done previously.
     //Unstable photons are those that come immediately from the decay of the graviton
     //Stable photons are those that make it to the final state
     

   }//end of event loop 
   

   cout << "number of events" << " " << N_total << endl;
   cout << "number of diphotons" << " " << N_diphoton << endl;
   cout << "number of gluglu initiated events" << " " << Event_interactingParton1PdgId  << " " << N_gluglu << endl;
   cout << "number of qqbar initiated events" << " " << Event_interactingParton2PdgId << " " << N_qqbar << endl;
   cout << "Reco Diphoton" << " " << N_diphoton << " " << "vs " << N_qqbar + N_gluglu << " Sum of gg & qqbar initiated events" << endl;

  
   //===============ALL EVENTS
 /*  TCanvas *cosThetaStar1 = new TCanvas("cosThetaStardistribution", "", 800, 600);
   h1->Draw();
   cosThetaStar1->SetBorderMode(0);
   cosThetaStar1->SetGrid();
   cosThetaStar1->SetLeftMargin(0.15);
   cosThetaStar1->SetBottomMargin(0.15);
   h1->SetFillColor(kOrange-3);
   h1->SetLineColor(kOrange+7);
   
   h1->GetYaxis()->SetTitle("Events");
   h1->GetXaxis()->SetTitle("cos#theta*");
   
   //=============== ALL RECO PHOTONS
   TCanvas *cosThetaStar2 = new TCanvas("cosThetaStardist", "", 800, 600);
   h2->Draw(); 
   cosThetaStar2->SetLeftMargin(0.15);
   cosThetaStar2->SetBottomMargin(0.15);
   h2->SetFillColor(kOrange-3);
   h2->SetLineColor(kOrange+7);
   
   h2->GetYaxis()->SetTitle("Events");
   h2->GetXaxis()->SetTitle("cos#theta*");
*/ 
   //=========== GLUON FUSION 
   TCanvas *ggcosThetaStar = new TCanvas("ggcosThetStar", "", 800, 600);
   gg->Draw();
   ggcosThetaStar->SetLeftMargin(0.15);
   ggcosThetaStar->SetBottomMargin(0.15);
   gg->SetFillColor(kOrange-3);
   gg->GetYaxis()->SetTitle("Events");
   gg->GetXaxis()->SetTitle("cos#theta*");
   gg->SetLineColor(kOrange+7);
  
    //===== Equations
    //TF1 *thcosqq = new TF1("thcosqq","1-pow(cos(x),4)",-TMath::Pi(),TMath::Pi()); 
    //TF1 *thcosgg = new TF1("thcosgg", "1+6*pow(cos(x),2)+pow(cos(x),4)", -TMath::Pi(), TMath::Pi()); 
    //TF1 *ctsgg = new TF1("ctsgg", "1+6*pow(x,2)+pow(x,4)",-1,1);
    TF1 *ctsgg = new TF1("ctsgg", "[0]*(1+6*pow(x,2)+pow(x,4))",-1,1);
   // ctsgg->SetParameters(500, gg->GetMean(), gg->GetRMS());
      //qq->Fit("ctsqq");
      //gg->Fit("ctsgg","R");
      gg->Fit("ctsgg");
      gStyle->SetOptFit(1111);
      //ctsgg->SetParameters(1,1);
      //gg->Fit("gaus");
      ctsgg->SetLineColor(kOrange+10); 
      //ctsgg->SetLineWidth(2);
      ctsgg->Draw("same");
  
   //============ QUARK ANNIHILATION
   TCanvas *qqbarcosThetaStar = new TCanvas("qqbarcosThetaStar", "", 800, 600);
      qqbarcosThetaStar->SetBottomMargin(0.15);
      qq->SetFillColor(kOrange-3);
      qq->GetYaxis()->SetTitle("Events");
      qq->GetXaxis()->SetTitle("cos#theta*");
      qq->SetLineColor(kOrange+7); 
      qq->Draw("same");
    
      TF1 *ctsqq = new TF1("ctsqq", "[0]*(1-pow(x,4))", -1,1);
      ctsqq->SetParameters(500, qq->GetMean(), qq->GetRMS());
      qq->Fit("ctsqq");
      gStyle->SetOptFit(1111);
      ctsqq->SetLineColor(kOrange+10);
      ctsqq->Draw("same");

  
/*    TCanvas *functions = new TCanvas("functions", "", 800, 600);
    ctsqq->Draw();
   // ctsgg->Draw("same");   
   
    TCanvas *func = new TCanvas("func", "", 800, 600);
    ctsgg->Draw();   
  */           
    //============ GEN PHOTONS
  
  /* TCanvas *gen_qqstable = new TCanvas("gen_qqstable","", 800, 600); 
     qqbarstable->Draw();

   TCanvas *gen_qqUnstable = new TCanvas("gen_qqUnstable", "", 800, 600);
     qqbarUnstable->Draw();

   TCanvas *gen_ggstable = new TCanvas("gen_ggstable", "", 800, 600);
      ggstable->Draw();

   TCanvas *gen_ggUnstable = new TCanvas("gen_ggUnstable", "", 800, 600);
      ggUnstable->Draw();
*/
 /*  TCanvas *GluonFusion = new TCanvas("GluonFusion", "", 800, 600);
    //  gPad->SetLogy();
     
      gg->Draw("same");
     
      Float_t rightmax4 = 1.1*ggstable->GetMaximum();
      Float_t scale4 = gPad->GetUymax()/rightmax4;

      Float_t rightmax3 = 1.1*ggUnstable->GetMaximum();
      Float_t scale3 = gPad->GetUymax()/rightmax3;
     
//      ggstable->Scale(scale4);
  //    ggUnstable->Scale(scale3);

     ggstable->SetLineColor(kBlue+1);
      ggUnstable->SetLineColor(kRed-2);
      ggstable->Draw("same");
      ggUnstable->Draw("same");
  
      leg1 = new TLegend(0.1, 0.7, 0.48, 0.9);
      //TPad* leg1 = new TPad("leg1","leg1", 0.1,0.7,0.48, 0.9 );
      leg1->SetBorderSize(0);
      leg1->SetHeader("Legend - gg events");
      leg1->AddEntry(qq, "RecoPhotons", "f" );
      leg1->AddEntry(qqbarstable, "GenStablePhotons", "l");
      leg1->AddEntry(qqbarUnstable, "GenUnstablePhotons", "l");
      leg1->SetFillStyle(4000);
      leg1->Draw(); 
 //     leg1->cd();

    TCanvas *quark_annihilation = new TCanvas("quark_annihilation", "", 800, 600);
     // gPad->SetLogy();  

      qq->Draw("same");

      quark_annihilation->Update();
      
      Float_t rightmax = 1.1*qqbarstable->GetMaximum();
      Float_t scale = gPad->GetUymax()/rightmax;

      Float_t rightmax2 = 1.1*qqbarUnstable->GetMaximum();
      Float_t scale2 = gPad->GetUymax()/rightmax2;

      qqbarstable->Scale(scale);
      qqbarUnstable->Scale(scale2);
      
      qqbarstable->SetLineColor(kBlue+1);
      qqbarUnstable->SetLineColor(kRed-2);
      
      qqbarstable->Draw("same");
      qqbarUnstable->Draw("same");
 
      leg = new TLegend(0.1, 0.7, 0.48, 0.9);
      leg->SetBorderSize(0);
      leg->SetHeader("Legend - qqbar events");
      leg->AddEntry(qq, "RecoPhotons", "f" );
      leg->AddEntry(qqbarstable, "GenStablePhotons", "l");
      leg->AddEntry(qqbarUnstable, "GenUnstablePhotons", "l");
      leg->SetFillStyle(4000);
      leg->Draw();
//      leg->cd();

*/

//==== SEPARATE GEN PHOTON PLOTS   
    TCanvas *GENggstable = new TCanvas("GENggstable", "", 800, 600); 
     
      ggstable->SetLineColor(kBlue+1);
      ggstable->Draw();
  
    
    TCanvas *GENggUnstable = new TCanvas("GENggUnstable", "", 800, 600); 
      
      ggUnstable->SetLineColor(kRed-2);
      ggUnstable->Draw();
  
    TCanvas *GENqqbarstable = new TCanvas("GENqqbarstable", "", 800, 600);
      
      qqbarstable->SetLineColor(kBlue+1); 
      qqbarstable->Draw();
    
    TCanvas *GENqqbarunstable = new TCanvas("GENqqbarunstable", "", 800, 600);
  
      qqbarUnstable->SetLineColor(kRed-2); 
      qqbarUnstable->Draw();


//==== CosThetaStarOld 
     TCanvas *old = new TCanvas("ALLcosthetaStarOld", "", 800, 600); 
     
      old1->SetLineColor(kBlue+1);
      old1->Draw();
    
    TCanvas *old_theta = new TCanvas("HighPTcosthetaStarOld", "", 800, 600); 
      
      old2->SetLineColor(kRed-2);
      old2->Draw();
  
    TCanvas *gg_old = new TCanvas("gg_costhetastarold", "", 800, 600);
      
      ggold->SetLineColor(kBlue+1); 
      ggold->Draw();
    
    TCanvas *qq_old = new TCanvas("qq_costhetastarold", "", 800, 600);
  
      qqold->SetLineColor(kRed-2); 
      qqold->Draw();

//============== CMS Logo and Lumi
   //CMS_lumi(canvas, iPeriod, iPos);
   CMS_lumi(qqbarcosThetaStar, 0, 11); 
   CMS_lumi(ggcosThetaStar, 0, 11); 
 //  CMS_lumi(cosThetaStar2, 0,11);
 //  CMS_lumi(cosThetaStar1, 0,11);
   CMS_lumi(old, 0, 11);
   CMS_lumi(old_theta, 0, 11);
   CMS_lumi(gg_old, 0, 11);
   CMS_lumi(qq_old, 0, 11);

   TFile *f = new TFile("RSGSpinAnalysis.root","RECREATE");
  
   //Write new histograms into root file  
   h1->Write();
   h2->Write();
   gg->Write();
   qq->Write();
   qqbarstable->Write();
   qqbarUnstable->Write();
   ggstable->Write();
   ggUnstable->Write();
   old1->Write();
   old2->Write();
   ggold->Write();
   ggold->Write();

   f->cd();
   f->Close();
}//end of method
