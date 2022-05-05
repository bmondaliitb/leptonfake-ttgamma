//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Dec  8 12:32:24 2020 by ROOT version 6.18/04
// from TTree MuonProbes/MuonProbes
// found on file: /ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.364167.Sherpa.DAOD_TOPQ1.e5340_s3126_r10201_p4172.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455371._000003.output.root
//////////////////////////////////////////////////////////

#ifndef EffTree_h
#define EffTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class EffTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           mc_channel_number;
   Int_t           mc_truthOrigin;
   Int_t           mc_truthType;
   Int_t           mc_truthIFFClass;
   Int_t           run_number;
   Int_t           event_number;
   Int_t           nMu;
   Int_t           nEl;
   Int_t           nJets;
   Int_t           nBJets;
   Int_t           nPh;
   Double_t        eventWeight;
   Double_t        pt_probe;
   Double_t        eta_probe;
   Double_t        phi_probe;
   Double_t        met;
   Double_t        mt;
   Float_t         pt_ph;
   Double_t        isoEt;
   Double_t        isoPt;
   Double_t        d0sig;
   Double_t        z0sinTheta;
   Int_t           isTight;
   Int_t           EventInOverlap;

   // List of branches
   TBranch        *b_mc_channel_number;   //!
   TBranch        *b_mc_truthOrigin;   //!
   TBranch        *b_mc_truthType;   //!
   TBranch        *b_mc_truthIFFClass;   //!
   TBranch        *b_run_number;   //!
   TBranch        *b_event_number;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_nEl;   //!
   TBranch        *b_nJets;   //!
   TBranch        *b_nBJets;   //!
   TBranch        *b_nPh;   //!
   TBranch        *b_eventWeight;   //!
   TBranch        *b_pt_probe;   //!
   TBranch        *b_eta_probe;   //!
   TBranch        *b_phi_probe;   //!
   TBranch        *b_met;   //!
   TBranch        *b_mt;   //!
   TBranch        *b_pt_ph;   //!
   TBranch        *b_isoEt;   //!
   TBranch        *b_isoPt;   //!
   TBranch        *b_d0sig;   //!
   TBranch        *b_z0sinTheta;   //!
   TBranch        *b_isTight;   //!
   TBranch        *b_EventInOverlap;   //!

   EffTree(TTree *tree=0);
   virtual ~EffTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef EffTree_cxx
EffTree::EffTree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.364167.Sherpa.DAOD_TOPQ1.e5340_s3126_r10201_p4172.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455371._000003.output.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.364167.Sherpa.DAOD_TOPQ1.e5340_s3126_r10201_p4172.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455371._000003.output.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/ceph/groups/e4/users/bwendland/private/SgTopGamma_lfakes_Nov2020/files_lfakes_05Dec/mc16d/user.wendlanb.364167.Sherpa.DAOD_TOPQ1.e5340_s3126_r10201_p4172.tqgamma_lfakes_v2.05_Dec_20_output_root/user.wendlanb.23455371._000003.output.root:/Efficiencies_Selection_1j1b701b85");
      dir->GetObject("MuonProbes",tree);

   }
   Init(tree);
}

EffTree::~EffTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EffTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EffTree::LoadTree(Long64_t entry)
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

void EffTree::Init(TTree *tree)
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

   fChain->SetBranchAddress("mc_channel_number", &mc_channel_number, &b_mc_channel_number);
   fChain->SetBranchAddress("mc_truthOrigin", &mc_truthOrigin, &b_mc_truthOrigin);
   fChain->SetBranchAddress("mc_truthType", &mc_truthType, &b_mc_truthType);
   fChain->SetBranchAddress("mc_truthIFFClass", &mc_truthIFFClass, &b_mc_truthIFFClass);
   fChain->SetBranchAddress("run_number", &run_number, &b_run_number);
   fChain->SetBranchAddress("event_number", &event_number, &b_event_number);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("nEl", &nEl, &b_nEl);
   fChain->SetBranchAddress("nJets", &nJets, &b_nJets);
   fChain->SetBranchAddress("nBJets", &nBJets, &b_nBJets);
   fChain->SetBranchAddress("nPh", &nPh, &b_nPh);
   fChain->SetBranchAddress("eventWeight", &eventWeight, &b_eventWeight);
   fChain->SetBranchAddress("pt_probe", &pt_probe, &b_pt_probe);
   fChain->SetBranchAddress("eta_probe", &eta_probe, &b_eta_probe);
   fChain->SetBranchAddress("phi_probe", &phi_probe, &b_phi_probe);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("mt", &mt, &b_mt);
   fChain->SetBranchAddress("pt_ph", &pt_ph, &b_pt_ph);
   fChain->SetBranchAddress("isoEt", &isoEt, &b_isoEt);
   fChain->SetBranchAddress("isoPt", &isoPt, &b_isoPt);
   fChain->SetBranchAddress("d0sig", &d0sig, &b_d0sig);
   fChain->SetBranchAddress("z0sinTheta", &z0sinTheta, &b_z0sinTheta);
   fChain->SetBranchAddress("isTight", &isTight, &b_isTight);
   fChain->SetBranchAddress("EventInOverlap", &EventInOverlap, &b_EventInOverlap);
   Notify();
}

Bool_t EffTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EffTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EffTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef EffTree_cxx
