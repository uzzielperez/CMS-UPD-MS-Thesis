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
   TH1F *ggold = new TH1F("ggold", "gg cosThetaStarold",100, -1.05,1.05);
   TH1F *qqold = new TH1F("qqold", "qqbar cosThetaStarold",100, -1.05,1.05);   
   TH1F *genall = new TH1F("genall", "ALL GEN", 100, -1.05, 1.05); //no cuts genstable 
   TH1F *genallstable = new TH1F("genallstable", "ALL GEN", 100, -1.05, 1.05);
   TH1F *ggplus = new TH1F("ggplus", "gg pt>0", 100, -1.05, 1.05);
   TH1F *qqbarplus = new TH1F("qqbarplus", "qq pt>0", 100, -1.05, 1.05);

   //===== Counters
   int N_total = 0;
   int N_diphoton = 0;
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
     /////////////
     //
     //NO CUTS 
      genall->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);   

     //GEN     
     //stable cuts
     if ((StablePhoton1_pt>0) && (StablePhoton2_pt>0)){
     genallstable->Fill(GenDiphotonStable_cosThetaStar, Event_weight);
     if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){
     ggstable->Fill(GenDiphotonStable_cosThetaStar, Event_weight);  
     }
     else{
      qqbarstable->Fill(GenDiphotonStable_cosThetaStar, Event_weight);
     }
   }//end stable
        if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){
            ggUnstable->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);  
         }
        else{
             qqbarUnstable->Fill(GenDiphotonUnstable_cosThetaStar, Event_weight);
        }// unstable

     //============== EVENTS WITH 2 RECO PHOTONS
      if ((Photon1_pt>0) && (Photon2_pt>0)){ 
               h1->Fill(Diphoton_cosThetaStar, Event_weight); 
          if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){ 
              ggplus->Fill(Diphoton_cosThetaStar, Event_weight); 
           }//gluon fusion initiated selection 
           else{
              qqbarplus->Fill(Diphoton_cosThetaStar, Event_weight);
           }//end qqbar selection
     }//End pt>0 RECO CUTS 

     if ((Photon1_passHighPtID==true) && (Photon2_passHighPtID==true)) {
            N_diphoton++; 
            h2->Fill(Diphoton_cosThetaStar, Event_weight);
        if (Event_interactingParton1PdgId == 21 && Event_interactingParton2PdgId == 21){ 
             N_gluglu++;
             gg->Fill(Diphoton_cosThetaStar, Event_weight); 
           }//end gluon selection
        else{ 
               N_qqbar++;
               qq->Fill(Diphoton_cosThetaStar, Event_weight);
          cout << "Interacting Partons" << " " << Event_interactingParton1PdgId << " " << Event_interactingParton2PdgId << endl;
          }//end qqbar selection
    }//end passHighPtID RECO

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

   /////////////////////FIT THESE EQUATIONS//////////////////////////
   //
   //
   //
   /////////////////////////////////////////////////////////////////

   TF1 *ctsgg = new TF1("ctsgg", "[0]*(1+6*pow(x,2)+pow(x,4))",-1,1);
   TF1 *ctsqq = new TF1("ctsqq", "[0]*(1-pow(x,4))", -1,1);
    
   //===============ALL EVENTS PT<0 
   TCanvas *cosThetaStar1 = new TCanvas("cosThetaStardistribution", "", 800, 600);
   CMS_lumi(cosThetaStar1, 0, 11);
   h1->Draw();
   cosThetaStar1->SetBorderMode(0);
   cosThetaStar1->SetGrid();
   cosThetaStar1->SetLeftMargin(0.15);
   cosThetaStar1->SetBottomMargin(0.15);
   h1->SetFillColor(kOrange-3);
   h1->SetLineColor(kOrange+7);
   
   h1->GetYaxis()->SetTitle("Events");
   h1->GetXaxis()->SetTitle("cos#theta*");
   
   //=============== ALL RECO PHOTONS HIGH PASS PT 
   TCanvas *cosThetaStar2 = new TCanvas("cosThetaStardist", "", 800, 600);
   
   CMS_lumi(cosThetaStar2, 0, 11);
   h2->Draw(); 
   cosThetaStar2->SetLeftMargin(0.15);
   cosThetaStar2->SetBottomMargin(0.15);
   h2->SetFillColor(kOrange-3);
   h2->SetLineColor(kOrange+7);
   
   h2->GetYaxis()->SetTitle("Events");
   h2->GetXaxis()->SetTitle("cos#theta*");
 
  
  ////////////////RECO PHOTONS////////////////////////// 
  //                                                  //
  /////////////////PLOT HERE////////////////////////////

   //=========== GLUON FUSION
   //---PT>0
   TCanvas *gghigh = new TCanvas("gghigh", "", 800, 600);
  
   CMS_lumi(gghigh, 0, 11);

   ggplus->Draw();
   gghigh->SetLeftMargin(0.15);
   gghigh->SetBottomMargin(0.15);
   ggplus->SetFillColor(kOrange-3);
   ggplus->GetYaxis()->SetTitle("Events");
   ggplus->GetXaxis()->SetTitle("cos#theta*");
   ggplus->SetLineColor(kOrange+7);

   
   //---HIGH PASS
   TCanvas *ggcosThetaStar = new TCanvas("ggcosThetStar", "", 800, 600);
  
   CMS_lumi(ggcosThetaStar, 0, 11);

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
   // ctsgg->SetParameters(500, gg->GetMean(), gg->GetRMS());
      //qq->Fit("ctsqq");
      //gg->Fit("ctsgg","R");

    /////////////////////////
    //
    ///////RECO FIT////////////
     /* gg->Fit("ctsgg");
      gStyle->SetOptFit(1111);
      //ctsgg->SetParameters(1,1);
      //gg->Fit("gaus");
      ctsgg->SetLineColor(kOrange+10); 
      //ctsgg->SetLineWidth(2);
      ctsgg->Draw("same");
  */
   //============ QUARK ANNIHILATION
   //---PT>0 
   TCanvas *qqbarhigh = new TCanvas("qqbarhigh", "", 800, 600);
  
   CMS_lumi(qqbarhigh, 0, 11);

   qqbarplus->Draw();
   qqbarhigh->SetLeftMargin(0.15);
   qqbarhigh->SetBottomMargin(0.15);
   qqbarplus->SetFillColor(kOrange-3);
   qqbarplus->GetYaxis()->SetTitle("Events");
   qqbarplus->GetXaxis()->SetTitle("cos#theta*");
   qqbarplus->SetLineColor(kOrange+7);
 

   //---HIGH PASS
   TCanvas *qqbarcosThetaStar = new TCanvas("qqbarcosThetaStar", "", 800, 600);
      qqbarcosThetaStar->SetBottomMargin(0.15);
      qq->SetFillColor(kOrange-3);
      qq->GetYaxis()->SetTitle("Events");
      qq->GetXaxis()->SetTitle("cos#theta*");
      qq->SetLineColor(kOrange+7); 
      qq->Draw("same");
     
      //////////
      //
      /////////RECO FIT 
      /*ctsqq->SetParameters(500, qq->GetMean(), qq->GetRMS());
      qq->Fit("ctsqq");
      gStyle->SetOptFit(1111);
      ctsqq->SetLineColor(kOrange+10);
      ctsqq->Draw("same");
      */

      ////////END RECO PHOTONS PLOTTING 
      ////////END RECO PHOTONS PLOTTING 

      ////////////////////////////////////////////////////////////////////////
      //scratch
   
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
/////////////////////////////////////////////////////////////////
//
//
//
//
//
////////////////// SEPARATE GEN PHOTON PLOTS ////////////////////
/////////////////
//
//GEN Unstable ALL
    
   TCanvas *GENALL = new TCanvas("GENALL", "", 800, 600);
    
    CMS_lumi(GENALL, 0, 11);
    genall->SetLineColor(kOrange+10);
    genall->Draw();
    GENALL->SetLeftMargin(0.15);
    GENALL->SetBottomMargin(0.15);
    genall->SetFillColor(kOrange-3);
    genall->GetYaxis()->SetTitle("Events");
    genall->GetXaxis()->SetTitle("cos#theta*");

//GEN Stable ALL

    TCanvas *GENALLST = new TCanvas("GENALLST", "", 800, 600);
    
    CMS_lumi(GENALLST, 0, 11);
    genallstable->SetLineColor(kOrange+10);
    genallstable->Draw();
    GENALLST->SetLeftMargin(0.15);
    GENALLST->SetBottomMargin(0.15);
    genallstable->SetFillColor(kOrange-3);
    genallstable->GetYaxis()->SetTitle("Events");
    genallstable->GetXaxis()->SetTitle("cos#theta*");

//////////////
//
//GLUON FUSION 
    TCanvas *GENggstable = new TCanvas("GENggstable", "", 800, 600); 
   
      TF1 *gg_st = new TF1("gg_st", "[3]*(1+6*pow(x,2)+pow(x,4))",-1,1); 
      CMS_lumi(GENggstable, 0, 11);
      ggstable->SetLineColor(kBlue+1);
      ggstable->Draw();
      
      ggstable->Fit("gg_st");
      gStyle->SetOptFit(1111);
      gg_st->SetLineColor(kOrange+10);
      gg_st->Draw("same");
/*
      ggstable->Fit("ctsgg");
*/
      GENggstable->SetLeftMargin(0.15);
      GENggstable->SetBottomMargin(0.15);
      ggstable->SetFillColor(kOrange-3);
      ggstable->GetYaxis()->SetTitle("Events");
      ggstable->GetXaxis()->SetTitle("cos#theta*");
////////////
//
//
 
    TCanvas *GENggUnstable = new TCanvas("GENggUnstable", "", 800, 600); 
         
      TF1 *gg_uns = new TF1("gg_unstable", "[0]*(1+6*pow(x,2)+pow(x,4))",-1,1);
      CMS_lumi(GENggUnstable, 0, 11);
      
      ggUnstable->SetLineColor(kRed-2);
      ggUnstable->Draw();
    //  ggUnstable->Fit("gg_uns");
/// GOOD FIT 
      ggUnstable->Fit("ctsgg");
      gStyle->SetOptFit(1111);
      ctsgg->SetLineColor(kOrange+10);
      ctsgg->Draw("same");
 
      GENggUnstable->SetLeftMargin(0.15);
      GENggUnstable->SetBottomMargin(0.15);
      ggUnstable->SetFillColor(kOrange-3);
      ggUnstable->GetYaxis()->SetTitle("Events");
      ggUnstable->GetXaxis()->SetTitle("cos#theta*");
//////////
//
//QQBAR 
    TCanvas *GENqqbarstable = new TCanvas("GENqqbarstable", "", 800, 600);
     
      CMS_lumi(GENqqbarstable, 0, 11);      
      TF1 *qq_st = new TF1("qq_st", "[2]*(1-pow(x,4))", -1,1);
      qqbarstable->SetLineColor(kBlue+1); 
      qqbarstable->Draw();
      qqbarstable->Fit("qq_st");
     // qqbarstable->Fit("ctsqq");
      gStyle->SetOptFit(1111);
      //ctsqq->SetLineColor(kOrange+10);
     // ctsqq->Draw("same");
      GENqqbarstable->SetLeftMargin(0.15);
      GENqqbarstable->SetBottomMargin(0.15);
      qqbarstable->SetFillColor(kOrange-3);
      qqbarstable->GetYaxis()->SetTitle("Events");
      qqbarstable->GetXaxis()->SetTitle("cos#theta*");
//unstable qqbar    
    TCanvas *GENqqbarunstable = new TCanvas("GENqqbarunstable", "", 800, 600);
  
      CMS_lumi(GENqqbarunstable, 0, 11);
      TF1 *qq_uns = new TF1("qq_unstable", "[0]*(1-pow(x,4))",-1,1);
      qqbarUnstable->SetLineColor(kRed-2); 
      qqbarUnstable->Draw();
      //qqbarUnstable->Fit("qq_uns");
      qqbarUnstable->Fit("ctsqq");
      gStyle->SetOptFit(1111);
      ctsqq->SetLineColor(kOrange+10);
      ctsqq->Draw("same");
      GENqqbarunstable->SetLeftMargin(0.15);
      GENqqbarunstable->SetBottomMargin(0.15);
      qqbarUnstable->SetFillColor(kOrange-3);
      qqbarUnstable->GetYaxis()->SetTitle("Events");
      qqbarUnstable->GetXaxis()->SetTitle("cos#theta*");

/////////////////END OF GEN DIPHOTONS PLOT
//
//
//
//
//=============================================================

///////////////////////COSTHETASTAROLD
//
//
//
/////////////////////////////////////////////////////////////////////

//==== CosThetaStarOld
/* 
     TCanvas *old = new TCanvas("ALLcosthetaStarOld", "", 800, 600); 
     
      old1->SetLineColor(kBlue+1);
      old1->Draw();

      old->SetLeftMargin(0.15);
      old->SetBottomMargin(0.15);
      old1->SetFillColor(kOrange-3);
      old1->GetYaxis()->SetTitle("Events");
      old1->GetXaxis()->SetTitle("cos#theta*");
    
    TCanvas *old_theta = new TCanvas("HighPTcosthetaStarOld", "", 800, 600); 
      
      old2->SetLineColor(kRed-2);
      old2->Draw();
 
      old_theta->SetLeftMargin(0.15);
      old_theta->SetBottomMargin(0.15);
      old2->SetFillColor(kOrange-3);
      old2->GetYaxis()->SetTitle("Events");
      old2->GetXaxis()->SetTitle("cos#theta*");

    TCanvas *gg_old = new TCanvas("gg_costhetastarold", "", 800, 600);
       
      ggold->SetLineColor(kBlue+1); 
      ggold->Draw();

      gg_old->SetLeftMargin(0.15);
      gg_old->SetBottomMargin(0.15);
      ggold->SetFillColor(kOrange-3);
      ggold->GetYaxis()->SetTitle("Events");
      ggold->GetXaxis()->SetTitle("cos#theta*");

    TCanvas *qq_old = new TCanvas("qq_costhetastarold", "", 800, 600);
  
      qqold->SetLineColor(kRed-2); 
      qqold->Draw();

      qq_old->SetLeftMargin(0.15);
      qq_old->SetBottomMargin(0.15);
      qqold->SetFillColor(kOrange-3);
      qqold->GetYaxis()->SetTitle("Events");
      qqold->GetXaxis()->SetTitle("cos#theta*");
*/


////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////
//============== CMS Logo and Lumi
   //CMS_lumi(canvas, iPeriod, iPos);
   //CMS_lumi(qqbarcosThetaStar, 0, 11); 
   //CMS_lumi(ggcosThetaStar, 0, 11); 
 //  CMS_lumi(cosThetaStar2, 0,11);
 //  CMS_lumi(cosThetaStar1, 0,11);
   //CMS_lumi(old, 0, 11);
  // CMS_lumi(old_theta, 0, 11);

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
   genall->Write();
   genallstable->Write();
   ggplus->Write();
   qqbarplus->Write();

   /*
   //save as pdf 
   h1->SaveAs("C1.pdf");
   h2->SaveAs("C2.pdf"); 
   gg->SaveAs("C3.pdf");
   qq->SaveAs("C4.pdf");
   ggplus->SaveAs("C5.pdf");
   qqbarplus->SaveAs("C6.pdf");
 
   genallstable->SaveAs("B1.pdf");
   qqbarstable->SaveAs("B2.pdf");
   ggstable->SaveAs("B3.pdf");

   genall->SaveAs("A1.pdf");
   qqbarUnstable->SaveAs("A2.pdf");
   ggUnstable->SaveAs("A3.pdf");
   */
   f->cd();
   f->Close();
}//end of method
