//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 11 13:07:13 2016 by ROOT version 6.04/00
// from TTree fTree/DiPhotonTree
// found on file: ExoDiphotonBKG.root
//////////////////////////////////////////////////////////

#ifndef myClassBKG_h
#define myClassBKG_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class myClassBKG {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        Event_run;
   Long64_t        Event_LS;
   Long64_t        Event_evnum;
   Long64_t        Event_processid;
   Long64_t        Event_bx;
   Long64_t        Event_orbit;
   Float_t         Event_ptHat;
   Float_t         Event_alphaqcd;
   Float_t         Event_alphaqed;
   Float_t         Event_qscale;
   Float_t         Event_weight0;
   Float_t         Event_weight;
   Int_t           Event_interactingParton1PdgId;
   Int_t           Event_interactingParton2PdgId;
   Bool_t          Event_beamHaloIDLoose;
   Bool_t          Event_beamHaloIDTight;
   Bool_t          Event_beamHaloIDTight2015;
   Float_t         Jet_jetHT;
   Int_t           Jet_nJets;
   Double_t        Photon1_pt;
   Double_t        Photon1_eta;
   Double_t        Photon1_phi;
   Double_t        Photon1_scEta;
   Double_t        Photon1_scPhi;
   Double_t        Photon1_rho;
   Double_t        Photon1_chargedHadIso03;
   Double_t        Photon1_neutralHadIso03;
   Double_t        Photon1_photonIso03;
   Double_t        Photon1_rhoCorChargedHadIso03;
   Double_t        Photon1_rhoCorNeutralHadIso03;
   Double_t        Photon1_rhoCorPhotonIso03;
   Double_t        Photon1_corPhotonIso03;
   Double_t        Photon1_hadTowerOverEm;
   Double_t        Photon1_r9;
   Double_t        Photon1_sigmaIetaIeta;
   Double_t        Photon1_sigmaIetaIeta5x5;
   Double_t        Photon1_sigmaEtaEta;
   Double_t        Photon1_sigmaIphiIphi;
   Double_t        Photon1_sigmaIphiIphi5x5;
   Double_t        Photon1_sigmaIetaIphi;
   Double_t        Photon1_sigmaIetaIphi5x5;
   Double_t        Photon1_maxEnergyXtal;
   Double_t        Photon1_iEta;
   Double_t        Photon1_iPhi;
   Double_t        Photon1_alphaHighPtID;
   Double_t        Photon1_kappaHighPtID;
   Double_t        Photon1_phoEAHighPtID;
   Double_t        Photon1_chEAegmID;
   Double_t        Photon1_nhEAegmID;
   Double_t        Photon1_phoEAegmID;
   Bool_t          Photon1_passEGMLooseID;
   Bool_t          Photon1_passEGMMediumID;
   Bool_t          Photon1_passEGMTightID;
   Bool_t          Photon1_isEB;
   Bool_t          Photon1_isEE;
   Bool_t          Photon1_isEBEtaGap;
   Bool_t          Photon1_isEBPhiGap;
   Bool_t          Photon1_isEERingGap;
   Bool_t          Photon1_isEEDeeGap;
   Bool_t          Photon1_isEBEEGap;
   Bool_t          Photon1_passElectronVeto;
   Bool_t          Photon1_passHTowOverE;
   Bool_t          Photon1_passChIso;
   Bool_t          Photon1_passCorPhoIso;
   Bool_t          Photon1_passSieie;
   Bool_t          Photon1_passHighPtID;
   Bool_t          Photon1_passChIsoDenom;
   Bool_t          Photon1_passCorPhoIsoDenom;
   Bool_t          Photon1_isFakeable;
   Bool_t          Photon1_isNumeratorObjCand;
   Bool_t          Photon1_isDenominatorObj;
   Bool_t          Photon1_isSaturated;
   Double_t        Photon2_pt;
   Double_t        Photon2_eta;
   Double_t        Photon2_phi;
   Double_t        Photon2_scEta;
   Double_t        Photon2_scPhi;
   Double_t        Photon2_rho;
   Double_t        Photon2_chargedHadIso03;
   Double_t        Photon2_neutralHadIso03;
   Double_t        Photon2_photonIso03;
   Double_t        Photon2_rhoCorChargedHadIso03;
   Double_t        Photon2_rhoCorNeutralHadIso03;
   Double_t        Photon2_rhoCorPhotonIso03;
   Double_t        Photon2_corPhotonIso03;
   Double_t        Photon2_hadTowerOverEm;
   Double_t        Photon2_r9;
   Double_t        Photon2_sigmaIetaIeta;
   Double_t        Photon2_sigmaIetaIeta5x5;
   Double_t        Photon2_sigmaEtaEta;
   Double_t        Photon2_sigmaIphiIphi;
   Double_t        Photon2_sigmaIphiIphi5x5;
   Double_t        Photon2_sigmaIetaIphi;
   Double_t        Photon2_sigmaIetaIphi5x5;
   Double_t        Photon2_maxEnergyXtal;
   Double_t        Photon2_iEta;
   Double_t        Photon2_iPhi;
   Double_t        Photon2_alphaHighPtID;
   Double_t        Photon2_kappaHighPtID;
   Double_t        Photon2_phoEAHighPtID;
   Double_t        Photon2_chEAegmID;
   Double_t        Photon2_nhEAegmID;
   Double_t        Photon2_phoEAegmID;
   Bool_t          Photon2_passEGMLooseID;
   Bool_t          Photon2_passEGMMediumID;
   Bool_t          Photon2_passEGMTightID;
   Bool_t          Photon2_isEB;
   Bool_t          Photon2_isEE;
   Bool_t          Photon2_isEBEtaGap;
   Bool_t          Photon2_isEBPhiGap;
   Bool_t          Photon2_isEERingGap;
   Bool_t          Photon2_isEEDeeGap;
   Bool_t          Photon2_isEBEEGap;
   Bool_t          Photon2_passElectronVeto;
   Bool_t          Photon2_passHTowOverE;
   Bool_t          Photon2_passChIso;
   Bool_t          Photon2_passCorPhoIso;
   Bool_t          Photon2_passSieie;
   Bool_t          Photon2_passHighPtID;
   Bool_t          Photon2_passChIsoDenom;
   Bool_t          Photon2_passCorPhoIsoDenom;
   Bool_t          Photon2_isFakeable;
   Bool_t          Photon2_isNumeratorObjCand;
   Bool_t          Photon2_isDenominatorObj;
   Bool_t          Photon2_isSaturated;
   Int_t           GenPhoton1_status;
   Int_t           GenPhoton1_motherStatus;
   Int_t           GenPhoton1_grandmotherStatus;
   Int_t           GenPhoton1_pdgId;
   Int_t           GenPhoton1_motherPdgId;
   Int_t           GenPhoton1_grandmotherPdgId;
   Double_t        GenPhoton1_pt;
   Double_t        GenPhoton1_eta;
   Double_t        GenPhoton1_phi;
   Int_t           GenPhoton2_status;
   Int_t           GenPhoton2_motherStatus;
   Int_t           GenPhoton2_grandmotherStatus;
   Int_t           GenPhoton2_pdgId;
   Int_t           GenPhoton2_motherPdgId;
   Int_t           GenPhoton2_grandmotherPdgId;
   Double_t        GenPhoton2_pt;
   Double_t        GenPhoton2_eta;
   Double_t        GenPhoton2_phi;
   Double_t        Diphoton_Minv;
   Double_t        Diphoton_qt;
   Double_t        Diphoton_deltaPhi;
   Double_t        Diphoton_deltaEta;
   Double_t        Diphoton_deltaR;
   Double_t        Diphoton_deltaROld;
   Double_t        Diphoton_cosThetaStar;
   Double_t        Diphoton_cosThetaStarOld;
   Double_t        GenDiphoton_Minv;
   Double_t        GenDiphoton_qt;
   Double_t        GenDiphoton_deltaPhi;
   Double_t        GenDiphoton_deltaEta;
   Double_t        GenDiphoton_deltaR;
   Double_t        GenDiphoton_deltaROld;
   Double_t        GenDiphoton_cosThetaStar;
   Double_t        GenDiphoton_cosThetaStarOld;

   // List of branches
   TBranch        *b_Event;   //!
   TBranch        *b_Jet;   //!
   TBranch        *b_Photon1;   //!
   TBranch        *b_Photon2;   //!
   TBranch        *b_GenPhoton1;   //!
   TBranch        *b_GenPhoton2;   //!
   TBranch        *b_Diphoton;   //!
   TBranch        *b_GenDiphoton;   //!

   myClassBKG(TTree *tree=0);
   virtual ~myClassBKG();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef myClassBKG_cxx
myClassBKG::myClassBKG(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ExoDiphotonBKG.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ExoDiphotonBKG.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("ExoDiphotonBKG.root:/diphoton");
      dir->GetObject("fTree",tree);

   }
   Init(tree);
}

myClassBKG::~myClassBKG()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t myClassBKG::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t myClassBKG::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void myClassBKG::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Event", &Event_run, &b_Event);
   fChain->SetBranchAddress("Jet", &Jet_jetHT, &b_Jet);
   fChain->SetBranchAddress("Photon1", &Photon1_pt, &b_Photon1);
   fChain->SetBranchAddress("Photon2", &Photon2_pt, &b_Photon2);
   fChain->SetBranchAddress("GenPhoton1", &GenPhoton1_status, &b_GenPhoton1);
   fChain->SetBranchAddress("GenPhoton2", &GenPhoton2_status, &b_GenPhoton2);
   fChain->SetBranchAddress("Diphoton", &Diphoton_Minv, &b_Diphoton);
   fChain->SetBranchAddress("GenDiphoton", &GenDiphoton_Minv, &b_GenDiphoton);
   Notify();
}

Bool_t myClassBKG::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void myClassBKG::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t myClassBKG::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef myClassBKG_cxx
