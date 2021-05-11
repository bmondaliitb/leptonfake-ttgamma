//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Dec  7 22:39:36 2020 by ROOT version 6.18/04
// from TTree nominal_Loose/tree
// found on file: /ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.410658.PhPy8EG.DAOD_TOPQ1.e6671_s3126_r10201_p4174.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455301._000010.output.root
//////////////////////////////////////////////////////////

#ifndef nominal_h
#define nominal_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
// Header file for the classes stored in the TTree if any.
#include "vector"
using namespace std;

class nominal {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         weight_mc;
   Float_t         weight_pileup;
   Float_t         weight_photonSF;
   Float_t         weight_globalLeptonTriggerSF;
   Float_t         weight_oldTriggerSF;
   Float_t         weight_bTagSF_DL1r_60;
   Float_t         weight_bTagSF_DL1r_70;
   Float_t         weight_bTagSF_DL1r_77;
   Float_t         weight_bTagSF_DL1r_85;
   Float_t         weight_jvt;
   ULong64_t       eventNumber;
   UInt_t          runNumber;
   UInt_t          randomRunNumber;
   UInt_t          mcChannelNumber;
   Float_t         mu;
   Float_t         mu_actual;
   UInt_t          backgroundFlags;
   UInt_t          hasBadMuon;
   vector<float>   *el_pt;
   vector<float>   *el_eta;
   vector<float>   *el_cl_eta;
   vector<float>   *el_phi;
   vector<float>   *el_e;
   vector<float>   *el_charge;
   vector<float>   *el_topoetcone20;
   vector<float>   *el_ptvarcone20;
   vector<char>    *el_isTight;
   vector<char>    *el_CF;
   vector<float>   *el_d0sig;
   vector<float>   *el_delta_z0_sintheta;
   vector<int>     *el_true_type;
   vector<int>     *el_true_origin;
   vector<int>     *el_true_firstEgMotherTruthType;
   vector<int>     *el_true_firstEgMotherTruthOrigin;
   vector<int>     *el_true_firstEgMotherPdgId;
   vector<char>    *el_true_isPrompt;
   vector<char>    *el_true_isChargeFl;
   vector<float>   *mu_pt;
   vector<float>   *mu_eta;
   vector<float>   *mu_phi;
   vector<float>   *mu_e;
   vector<float>   *mu_charge;
   vector<float>   *mu_topoetcone20;
   vector<float>   *mu_ptvarcone30;
   vector<char>    *mu_isTight;
   vector<float>   *mu_d0sig;
   vector<float>   *mu_delta_z0_sintheta;
   vector<int>     *mu_true_type;
   vector<int>     *mu_true_origin;
   vector<char>    *mu_true_isPrompt;
   vector<float>   *ph_pt;
   vector<float>   *ph_eta;
   vector<float>   *ph_phi;
   vector<float>   *ph_e;
   vector<float>   *ph_iso;
   Float_t         met_met;
   Float_t         met_phi;
   Int_t           Basic;
   Int_t           Basic_Fake1L;
   Int_t           Selection_1j1b70;
   Int_t           Selection_1j1b701b85;
   Int_t           Selection_1j1b702b85;
   Int_t           Selection_1j0b701b85;
   Int_t           Selection_1j1b701y;
   Int_t           Selection_1j1b701b851y;
   Int_t           Selection_1j1b702b851y;
   Int_t           Selection_1j0b701b851y;
   Char_t          HLT_mu26_ivarmedium;
   Char_t          HLT_mu50;
   Char_t          HLT_e60_lhmedium_nod0;
   Char_t          HLT_e140_lhloose_nod0;
   Char_t          HLT_e26_lhtight_nod0_ivarloose;
   vector<char>    *el_trigMatch_HLT_e60_lhmedium_nod0;
   vector<char>    *el_trigMatch_HLT_e140_lhloose_nod0;
   vector<char>    *el_trigMatch_HLT_e26_lhtight_nod0_ivarloose;
   vector<char>    *mu_trigMatch_HLT_mu50;
   vector<char>    *mu_trigMatch_HLT_mu26_ivarmedium;
   Float_t         averageIntPerXing;
   Float_t         averageIntPerXing_corr;
   Float_t         m_numVtx;
   Int_t           nEl;
   Int_t           nMu;
   Int_t           nJets;
   Int_t           RunNumber;
   Int_t           EventInOverlap;

   // List of branches
   TBranch        *b_weight_mc;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_weight_photonSF;   //!
   TBranch        *b_weight_globalLeptonTriggerSF;   //!
   TBranch        *b_weight_oldTriggerSF;   //!
   TBranch        *b_weight_bTagSF_DL1r_70;   //!
   TBranch        *b_weight_bTagSF_DL1r_77;   //!
   TBranch        *b_weight_bTagSF_DL1r_85;   //!
   TBranch        *b_weight_jvt;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_randomRunNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mu;   //!
   TBranch        *b_mu_actual;   //!
   TBranch        *b_backgroundFlags;   //!
   TBranch        *b_hasBadMuon;   //!
   TBranch        *b_el_pt;   //!
   TBranch        *b_el_eta;   //!
   TBranch        *b_el_cl_eta;   //!
   TBranch        *b_el_phi;   //!
   TBranch        *b_el_e;   //!
   TBranch        *b_el_charge;   //!
   TBranch        *b_el_topoetcone20;   //!
   TBranch        *b_el_ptvarcone20;   //!
   TBranch        *b_el_isTight;   //!
   TBranch        *b_el_CF;   //!
   TBranch        *b_el_d0sig;   //!
   TBranch        *b_el_delta_z0_sintheta;   //!
   TBranch        *b_el_true_type;   //!
   TBranch        *b_el_true_origin;   //!
   TBranch        *b_el_true_firstEgMotherTruthType;   //!
   TBranch        *b_el_true_firstEgMotherTruthOrigin;   //!
   TBranch        *b_el_true_firstEgMotherPdgId;   //!
   TBranch        *b_el_true_isPrompt;   //!
   TBranch        *b_el_true_isChargeFl;   //!
   TBranch        *b_mu_pt;   //!
   TBranch        *b_mu_eta;   //!
   TBranch        *b_mu_phi;   //!
   TBranch        *b_mu_e;   //!
   TBranch        *b_mu_charge;   //!
   TBranch        *b_mu_topoetcone20;   //!
   TBranch        *b_mu_ptvarcone30;   //!
   TBranch        *b_mu_isTight;   //!
   TBranch        *b_mu_d0sig;   //!
   TBranch        *b_mu_delta_z0_sintheta;   //!
   TBranch        *b_mu_true_type;   //!
   TBranch        *b_mu_true_origin;   //!
   TBranch        *b_mu_true_isPrompt;   //!
   TBranch        *b_ph_pt;   //!
   TBranch        *b_ph_eta;   //!
   TBranch        *b_ph_phi;   //!
   TBranch        *b_ph_e;   //!
   TBranch        *b_ph_iso;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_Basic;   //!
   TBranch        *b_Basic_Fake1L;   //!
   TBranch        *b_Selection_1j1b70;   //!
   TBranch        *b_Selection_1j1b701b85;   //!
   TBranch        *b_Selection_1j1b702b85;   //!
   TBranch        *b_Selection_1j0b701b85;   //!
   TBranch        *b_Selection_1j1b701y;   //!
   TBranch        *b_Selection_1j1b701b851y;   //!
   TBranch        *b_Selection_1j1b702b851y;   //!
   TBranch        *b_Selection_1j0b701b851y;   //!
   TBranch        *b_HLT_mu26_ivarmedium;   //!
   TBranch        *b_HLT_mu50;   //!
   TBranch        *b_HLT_e60_lhmedium_nod0;   //!
   TBranch        *b_HLT_e140_lhloose_nod0;   //!
   TBranch        *b_HLT_e26_lhtight_nod0_ivarloose;   //!
   TBranch        *b_el_trigMatch_HLT_e60_lhmedium_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e140_lhloose_nod0;   //!
   TBranch        *b_el_trigMatch_HLT_e26_lhtight_nod0_ivarloose;   //!
   TBranch        *b_mu_trigMatch_HLT_mu50;   //!
   TBranch        *b_mu_trigMatch_HLT_mu26_ivarmedium;   //!
   TBranch        *b_averageIntPerXing;   //!
   TBranch        *b_averageIntPerXing_corr;   //!
   TBranch        *b_m_numVtx;   //!
   TBranch        *b_nEl;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventInOverlap;   //!

   nominal(TTree *tree=0);
   virtual ~nominal();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef nominal_cxx
nominal::nominal(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.410658.PhPy8EG.DAOD_TOPQ1.e6671_s3126_r10201_p4174.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455301._000010.output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.410658.PhPy8EG.DAOD_TOPQ1.e6671_s3126_r10201_p4174.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455301._000010.output.root");
      }
      f->GetObject("nominal_Loose",tree);

   }
   Init(tree);
}

nominal::~nominal()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t nominal::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t nominal::LoadTree(Long64_t entry)
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

void nominal::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   el_pt = 0;
   el_eta = 0;
   el_cl_eta = 0;
   el_phi = 0;
   el_e = 0;
   el_charge = 0;
   el_topoetcone20 = 0;
   el_ptvarcone20 = 0;
   el_isTight = 0;
   el_CF = 0;
   el_d0sig = 0;
   el_delta_z0_sintheta = 0;
   el_true_type = 0;
   el_true_origin = 0;
   el_true_firstEgMotherTruthType = 0;
   el_true_firstEgMotherTruthOrigin = 0;
   el_true_firstEgMotherPdgId = 0;
   el_true_isPrompt = 0;
   el_true_isChargeFl = 0;
   mu_pt = 0;
   mu_eta = 0;
   mu_phi = 0;
   mu_e = 0;
   mu_charge = 0;
   mu_topoetcone20 = 0;
   mu_ptvarcone30 = 0;
   mu_isTight = 0;
   mu_d0sig = 0;
   mu_delta_z0_sintheta = 0;
   mu_true_type = 0;
   mu_true_origin = 0;
   mu_true_isPrompt = 0;
   ph_pt = 0;
   ph_eta = 0;
   ph_phi = 0;
   ph_e = 0;
   ph_iso = 0;
   el_trigMatch_HLT_e60_lhmedium_nod0 = 0;
   el_trigMatch_HLT_e140_lhloose_nod0 = 0;
   el_trigMatch_HLT_e26_lhtight_nod0_ivarloose = 0;
   mu_trigMatch_HLT_mu50 = 0;
   mu_trigMatch_HLT_mu26_ivarmedium = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("weight_mc", &weight_mc, &b_weight_mc);
   fChain->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain->SetBranchAddress("weight_photonSF", &weight_photonSF, &b_weight_photonSF);
   fChain->SetBranchAddress("weight_globalLeptonTriggerSF", &weight_globalLeptonTriggerSF, &b_weight_globalLeptonTriggerSF);
   fChain->SetBranchAddress("weight_oldTriggerSF", &weight_oldTriggerSF, &b_weight_oldTriggerSF);
   fChain->SetBranchAddress("weight_bTagSF_DL1r_70", &weight_bTagSF_DL1r_70, &b_weight_bTagSF_DL1r_70);
   fChain->SetBranchAddress("weight_bTagSF_DL1r_77", &weight_bTagSF_DL1r_77, &b_weight_bTagSF_DL1r_77);
   fChain->SetBranchAddress("weight_bTagSF_DL1r_85", &weight_bTagSF_DL1r_85, &b_weight_bTagSF_DL1r_85);
   fChain->SetBranchAddress("weight_jvt", &weight_jvt, &b_weight_jvt);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("randomRunNumber", &randomRunNumber, &b_randomRunNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mu", &mu, &b_mu);
   fChain->SetBranchAddress("mu_actual", &mu_actual, &b_mu_actual);
   fChain->SetBranchAddress("backgroundFlags", &backgroundFlags, &b_backgroundFlags);
   fChain->SetBranchAddress("hasBadMuon", &hasBadMuon, &b_hasBadMuon);
   fChain->SetBranchAddress("el_pt", &el_pt, &b_el_pt);
   fChain->SetBranchAddress("el_eta", &el_eta, &b_el_eta);
   fChain->SetBranchAddress("el_cl_eta", &el_cl_eta, &b_el_cl_eta);
   fChain->SetBranchAddress("el_phi", &el_phi, &b_el_phi);
   fChain->SetBranchAddress("el_e", &el_e, &b_el_e);
   fChain->SetBranchAddress("el_charge", &el_charge, &b_el_charge);
   fChain->SetBranchAddress("el_topoetcone20", &el_topoetcone20, &b_el_topoetcone20);
   fChain->SetBranchAddress("el_ptvarcone20", &el_ptvarcone20, &b_el_ptvarcone20);
   fChain->SetBranchAddress("el_isTight", &el_isTight, &b_el_isTight);
   fChain->SetBranchAddress("el_CF", &el_CF, &b_el_CF);
   fChain->SetBranchAddress("el_d0sig", &el_d0sig, &b_el_d0sig);
   fChain->SetBranchAddress("el_delta_z0_sintheta", &el_delta_z0_sintheta, &b_el_delta_z0_sintheta);
   fChain->SetBranchAddress("el_true_type", &el_true_type, &b_el_true_type);
   fChain->SetBranchAddress("el_true_origin", &el_true_origin, &b_el_true_origin);
   fChain->SetBranchAddress("el_true_firstEgMotherTruthType", &el_true_firstEgMotherTruthType, &b_el_true_firstEgMotherTruthType);
   fChain->SetBranchAddress("el_true_firstEgMotherTruthOrigin", &el_true_firstEgMotherTruthOrigin, &b_el_true_firstEgMotherTruthOrigin);
   fChain->SetBranchAddress("el_true_firstEgMotherPdgId", &el_true_firstEgMotherPdgId, &b_el_true_firstEgMotherPdgId);
   fChain->SetBranchAddress("el_true_isPrompt", &el_true_isPrompt, &b_el_true_isPrompt);
   fChain->SetBranchAddress("el_true_isChargeFl", &el_true_isChargeFl, &b_el_true_isChargeFl);
   fChain->SetBranchAddress("mu_pt", &mu_pt, &b_mu_pt);
   fChain->SetBranchAddress("mu_eta", &mu_eta, &b_mu_eta);
   fChain->SetBranchAddress("mu_phi", &mu_phi, &b_mu_phi);
   fChain->SetBranchAddress("mu_e", &mu_e, &b_mu_e);
   fChain->SetBranchAddress("mu_charge", &mu_charge, &b_mu_charge);
   fChain->SetBranchAddress("mu_topoetcone20", &mu_topoetcone20, &b_mu_topoetcone20);
   fChain->SetBranchAddress("mu_ptvarcone30", &mu_ptvarcone30, &b_mu_ptvarcone30);
   fChain->SetBranchAddress("mu_isTight", &mu_isTight, &b_mu_isTight);
   fChain->SetBranchAddress("mu_d0sig", &mu_d0sig, &b_mu_d0sig);
   fChain->SetBranchAddress("mu_delta_z0_sintheta", &mu_delta_z0_sintheta, &b_mu_delta_z0_sintheta);
   fChain->SetBranchAddress("mu_true_type", &mu_true_type, &b_mu_true_type);
   fChain->SetBranchAddress("mu_true_origin", &mu_true_origin, &b_mu_true_origin);
   fChain->SetBranchAddress("mu_true_isPrompt", &mu_true_isPrompt, &b_mu_true_isPrompt);
   fChain->SetBranchAddress("ph_pt", &ph_pt, &b_ph_pt);
   fChain->SetBranchAddress("ph_eta", &ph_eta, &b_ph_eta);
   fChain->SetBranchAddress("ph_phi", &ph_phi, &b_ph_phi);
   fChain->SetBranchAddress("ph_e", &ph_e, &b_ph_e);
   fChain->SetBranchAddress("ph_iso", &ph_iso, &b_ph_iso);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("Basic", &Basic, &b_Basic);
   fChain->SetBranchAddress("Basic_Fake1L", &Basic_Fake1L, &b_Basic_Fake1L);
   fChain->SetBranchAddress("Selection_1j1b70", &Selection_1j1b70, &b_Selection_1j1b70);
   fChain->SetBranchAddress("Selection_1j1b701b85", &Selection_1j1b701b85, &b_Selection_1j1b701b85);
   fChain->SetBranchAddress("Selection_1j1b702b85", &Selection_1j1b702b85, &b_Selection_1j1b702b85);
   fChain->SetBranchAddress("Selection_1j0b701b85", &Selection_1j0b701b85, &b_Selection_1j0b701b85);
   fChain->SetBranchAddress("Selection_1j1b701y", &Selection_1j1b701y, &b_Selection_1j1b701y);
   fChain->SetBranchAddress("Selection_1j1b701b851y", &Selection_1j1b701b851y, &b_Selection_1j1b701b851y);
   fChain->SetBranchAddress("Selection_1j1b702b851y", &Selection_1j1b702b851y, &b_Selection_1j1b702b851y);
   fChain->SetBranchAddress("Selection_1j0b701b851y", &Selection_1j0b701b851y, &b_Selection_1j0b701b851y);
   fChain->SetBranchAddress("HLT_mu26_ivarmedium", &HLT_mu26_ivarmedium, &b_HLT_mu26_ivarmedium);
   fChain->SetBranchAddress("HLT_mu50", &HLT_mu50, &b_HLT_mu50);
   fChain->SetBranchAddress("HLT_e60_lhmedium_nod0", &HLT_e60_lhmedium_nod0, &b_HLT_e60_lhmedium_nod0);
   fChain->SetBranchAddress("HLT_e140_lhloose_nod0", &HLT_e140_lhloose_nod0, &b_HLT_e140_lhloose_nod0);
   fChain->SetBranchAddress("HLT_e26_lhtight_nod0_ivarloose", &HLT_e26_lhtight_nod0_ivarloose, &b_HLT_e26_lhtight_nod0_ivarloose);
   fChain->SetBranchAddress("el_trigMatch_HLT_e60_lhmedium_nod0", &el_trigMatch_HLT_e60_lhmedium_nod0, &b_el_trigMatch_HLT_e60_lhmedium_nod0);
   fChain->SetBranchAddress("el_trigMatch_HLT_e140_lhloose_nod0", &el_trigMatch_HLT_e140_lhloose_nod0, &b_el_trigMatch_HLT_e140_lhloose_nod0);
   fChain->SetBranchAddress("el_trigMatch_HLT_e26_lhtight_nod0_ivarloose", &el_trigMatch_HLT_e26_lhtight_nod0_ivarloose, &b_el_trigMatch_HLT_e26_lhtight_nod0_ivarloose);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu50", &mu_trigMatch_HLT_mu50, &b_mu_trigMatch_HLT_mu50);
   fChain->SetBranchAddress("mu_trigMatch_HLT_mu26_ivarmedium", &mu_trigMatch_HLT_mu26_ivarmedium, &b_mu_trigMatch_HLT_mu26_ivarmedium);
   fChain->SetBranchAddress("averageIntPerXing", &averageIntPerXing, &b_averageIntPerXing);
   fChain->SetBranchAddress("averageIntPerXing_corr", &averageIntPerXing_corr, &b_averageIntPerXing_corr);
   fChain->SetBranchAddress("m_numVtx", &m_numVtx, &b_m_numVtx);
   fChain->SetBranchAddress("nEl", &nEl, &b_nEl);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventInOverlap", &EventInOverlap, &b_EventInOverlap);
   Notify();
}

Bool_t nominal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void nominal::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t nominal::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef nominal_cxx
