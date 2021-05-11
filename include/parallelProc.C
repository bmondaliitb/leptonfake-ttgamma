#include <iostream>
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include "TSystem.h"
#include <filesystem>
#include "TLorentzVector.h"
#include "EffTree.h"
#include <omp.h>

using namespace std;

namespace fs = filesystem;

void debug_message(int debug_level, std::string function_name, TString message)
{
  if(debug_level==0){
    std::cout<<"===INFO         "<<function_name<<"    "<<message<<std::endl;
  }
}

double mt(double lep_pt, double met_met, double lep_phi, double met_phi){

  return sqrt(2*lep_pt*met_met*(1-cos(lep_phi-met_phi)))/1000.;
}


double dPhi(double mt, double lep_pt, double met){

    return acos(1.-pow(mt,2)/(2*lep_pt*met));
}

int main(int argc, char* argv[]){

  //string path = getenv("LFAKEDIR");
  string stype = argv[1];
  string campaign = argv[2];
  string selection = argv[3];
  string channel = argv[4];
  TString sample = argv[5];
  int mcID = stoi(argv[6]);
  string suffix = argv[7];
  TString treename = TString(selection)+"/MuonProbes";
  if(channel == "el") treename=TString(selection)+"/ElectronProbes";
  if(stype == "real"){
     treename=TString(selection)+"_mumu"+"/MuonProbes";
     if(channel == "el") treename=TString(selection)+"_ee"+"/ElectronProbes";
  }

  TH1F * mtHistTight = new TH1F();
  TH1F * mtHist = new TH1F();
  mtHist->SetName("mt");
  mtHist->SetTitle("#it{m}_{T_{W}} [GeV]");
  mtHistTight->SetName("mt_Tight");
  mtHistTight->SetTitle("#it{m}_{T_{W}} [GeV]");

  TH1F * lptHist = new TH1F();
  TH1F * lptHistTight = new TH1F();
  lptHist->SetName("lpt");
  lptHist->SetTitle("#it{p}_{T}^{l} [GeV]");
  lptHistTight->SetName("lpt_Tight");
  lptHistTight->SetTitle("#it{p}_{T}^{l} [GeV]");

  TH1F * letaHist = new TH1F();
  TH1F * letaHistTight = new TH1F();
  letaHist->SetName("leta");
  letaHist->SetTitle("|#eta^{l}|");
  letaHistTight->SetName("leta_Tight");
  letaHistTight->SetTitle("|#eta^{l}|");

  TH1F * dPhiHist = new TH1F();
  TH1F * dPhiHistTight = new TH1F();
  dPhiHist->SetName("dPhi");
  dPhiHist->SetTitle("#Delta #phi(l,#nu)");
  dPhiHistTight->SetName("dPhi_Tight");
  dPhiHistTight->SetTitle("#Delta #phi(l,#nu)");

  TH2F * ptmtHist = new TH2F();
  TH2F * ptmtHistTight = new TH2F();
  ptmtHist->SetName("pt_mt_2D");
  ptmtHist->SetXTitle("#it{p}_{T}^{l} [GeV]");
  ptmtHist->SetYTitle("#it{m}_{T_{W}} [GeV]");
  ptmtHistTight->SetName("pt_mt_2D_Tight");
  ptmtHistTight->SetXTitle("#it{p}_{T}^{l} [GeV]");
  ptmtHistTight->SetYTitle("#it{m}_{T_{W}} [GeV]");

  TH2F * ptetaHist = new TH2F();
  TH2F * ptetaHistTight = new TH2F();
  ptetaHist->SetName("pt_eta_2D");
  ptetaHist->SetXTitle("#it{p}_{T}^{l} [GeV]");
  ptetaHist->SetYTitle("|#eta^{l}|");
  ptetaHistTight->SetName("pt_eta_2D_Tight");
  ptetaHistTight->SetXTitle("#it{p}_{T}^{l} [GeV]");
  ptetaHistTight->SetYTitle("|#eta^{l}|");

  TH2F * ptphiHist = new TH2F();
  TH2F * ptphiHistTight = new TH2F();
  ptphiHist->SetName("pt_phi_2D");
  ptphiHist->SetXTitle("#it{p}_{T}^{l} [GeV]");
  ptphiHist->SetYTitle("#Delta #phi(l,#nu)");
  ptphiHistTight->SetName("pt_phi_2D_Tight");
  ptphiHistTight->SetXTitle("#it{p}_{T}^{l} [GeV]");
  ptphiHistTight->SetYTitle("#Delta #phi(l,#nu)");

  if(channel == "mu"){
    const Int_t ptbins = 5; const Int_t mtbins = 5;const Int_t phibins = 5; const Int_t etabins = 5;
    Double_t mtEdges[mtbins + 1] = {0.,7.,15., 25., 40.,100.};
    Double_t ptEdges[ptbins + 1] = {27.,35.,45., 52., 60.,100.};
    Double_t phiEdges[phibins + 1] = {0., 0.5, 1.0, 1.5, 2.0, 3.2};
    Double_t etaEdges[etabins + 1] = {0.,0.5,1.,1.5,2.0,2.5};
    mtHist->SetBins(mtbins,mtEdges);
    mtHistTight->SetBins(mtbins,mtEdges);
    lptHist->SetBins(ptbins,ptEdges);
    lptHistTight->SetBins(ptbins,ptEdges);
    letaHist->SetBins(etabins,etaEdges);
    letaHistTight->SetBins(etabins,etaEdges);
    dPhiHist->SetBins(phibins,phiEdges);
    dPhiHistTight->SetBins(phibins,phiEdges);

    ptmtHist->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptmtHistTight->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptetaHist->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptetaHistTight->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptphiHist->SetBins(ptbins,ptEdges,phibins,phiEdges);
    ptphiHistTight->SetBins(ptbins,ptEdges,phibins,phiEdges);

  }

  if(channel == "el"){
    const Int_t ptbins = 4; const Int_t mtbins = 4;const Int_t phibins = 5; const Int_t etabins = 5;
    Double_t ptEdges[ptbins + 1] = {27.,35., 45., 62., 100.};
    Double_t mtEdges[mtbins + 1] = {0.,40.,60.,80., 140.};
    Double_t phiEdges[phibins + 1] = {0., 0.5, 1.0, 1.5, 2.0, 3.2};
    Double_t etaEdges[etabins + 1] = {0.,0.5,1.,1.5,2.0,2.5};
    mtHist->SetBins(mtbins,mtEdges);
    mtHistTight->SetBins(mtbins,mtEdges);
    lptHist->SetBins(ptbins,ptEdges);
    lptHistTight->SetBins(ptbins,ptEdges);
    letaHist->SetBins(etabins,etaEdges);
    letaHistTight->SetBins(etabins,etaEdges);
    dPhiHist->SetBins(phibins,phiEdges);
    dPhiHistTight->SetBins(phibins,phiEdges);

    ptmtHist->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptmtHistTight->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptetaHist->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptetaHistTight->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptphiHist->SetBins(ptbins,ptEdges,phibins,phiEdges);
    ptphiHistTight->SetBins(ptbins,ptEdges,phibins,phiEdges);
  }

  TH1F * metHist = new TH1F("met", "", 32,0,160);
  TH1F * metHistTight = new TH1F("met_Tight", "", 32,0,160);
  TH1F * mtHist_kin = new TH1F("mt_kin", "", 40,0,200);
  TH1F * mtHistTight_kin = new TH1F("mt_kin_Tight", "", 40,0,200);
  TH1F * metHist_kin = new TH1F("met_kin", "", 32,0,160);
  TH1F * metHistTight_kin = new TH1F("met_kin_Tight", "", 32,0,160);
  TH1F * lptHist_kin = new TH1F("lpt_kin", "", 32,0,160);
  TH1F * lptHistTight_kin = new TH1F("lpt_kin_Tight", "", 32,0,160);
  TH1F * letaHist_kin = new TH1F("leta_kin", "", 25,0,2.5);
  TH1F * letaHistTight_kin = new TH1F("leta_kin_Tight", "", 25,0,2.5);
  //TH1F * dPhiHist = new TH1F("dPhi", "", 17,-3.20,3.20);
  //TH1F * dPhiHistTight = new TH1F("dPhi_Tight", "", 17,-3.20,3.20);
  TH1F * MCLumiHist = new TH1F("MCLumi","", 1,0,1);


  bool isData = false;
  if(mcID==0 || mcID == 1) isData=true;
  debug_message(0, "tfile", sample);
  TFile * tfile = new TFile(sample);
  MCLumiHist->SetBinContent(1,((TH1F*)tfile->Get("MCLumiHist"))->GetBinContent(1));
  cout << treename << endl;
  EffTree * looseTree = new EffTree((TTree*)tfile->Get(treename));
  int nEntries = looseTree->fChain->GetEntries();
  cout << "###########################################" << endl;
  cout << "Processing "<<mcID <<" with " <<nEntries << " Entries" << endl;
  cout << "###########################################" << endl;

  for (int entry(0); entry < nEntries; entry++){
        looseTree->fChain->GetEntry(entry);
        if((entry%100000)==0) cout << "Processed " <<entry<<"/"<<nEntries <<" Entries" << endl;
        if(stype == "fake" && channel == "mu" && (looseTree->met < 30 || looseTree->met > 50)) continue;
        if(stype == "fake" && channel == "el" && (looseTree->met < 30 || looseTree->met > 50)) continue;

    //if(stype == "fake" && channel == "mu" && looseTree->met > 30 ) continue;
        //if(stype == "fake" && channel == "el" && looseTree->met > 30 ) continue;
        if(!isData){
            if(channel == "mu" && !(looseTree->mc_truthIFFClass == 4)) continue;
            else if(channel == "el" && !(looseTree->mc_truthIFFClass == 2 || looseTree->mc_truthIFFClass == 3)) continue;
        }

        //if(fabs(looseTree->mu_phi->at(0)-looseTree->met_phi) > 1.0) continue;

        double mtval = looseTree->mt;
        double dPhival = dPhi(mtval,looseTree->pt_probe, looseTree->met);
        double weight = 1.;

        if(!isData){
            weight = looseTree->eventWeightLoose;
            if(fabs(weight)>10E7) cout << weight << endl;
        }
        mtHist->Fill(mtval, weight);
        metHist->Fill(looseTree->met, weight);
        lptHist->Fill(looseTree->pt_probe, weight);
        letaHist->Fill(fabs(looseTree->eta_probe), weight);

        mtHist_kin->Fill(mtval, weight);
        metHist_kin->Fill(looseTree->met, weight);
        lptHist_kin->Fill(looseTree->pt_probe, weight);
        letaHist_kin->Fill(fabs(looseTree->eta_probe), weight);

        dPhiHist->Fill(dPhival, weight);
        ptmtHist->Fill(looseTree->pt_probe,mtval,weight);
        ptetaHist->Fill(looseTree->pt_probe,fabs(looseTree->eta_probe),weight);

        ptphiHist->Fill(looseTree->pt_probe, dPhival,weight);
        if(looseTree->isTight==1){
            mtHistTight->Fill(mtval, weight);
            metHistTight->Fill(looseTree->met, weight);
            lptHistTight->Fill(looseTree->pt_probe, weight);
            letaHistTight->Fill(fabs(looseTree->eta_probe), weight);

            mtHistTight_kin->Fill(mtval, weight);
            metHistTight_kin->Fill(looseTree->met, weight);
            lptHistTight_kin->Fill(looseTree->pt_probe, weight);
            letaHistTight_kin->Fill(fabs(looseTree->eta_probe), weight);

            dPhiHistTight->Fill(dPhival, weight);
            ptmtHistTight->Fill(looseTree->pt_probe,mtval,weight);
            ptetaHistTight->Fill(looseTree->pt_probe,fabs(looseTree->eta_probe),weight);
            ptphiHistTight->Fill(looseTree->pt_probe, dPhival,weight);

        }

      }
  tfile->Close();

  string ostring = "../ohists/"+stype+"/"+campaign+"/"+selection+"_"+channel+"/"+to_string(mcID)+"/"+suffix+".root";
  //string ostring = "test.root";
  //if(mcID == 0) ostring = "ohists/"+selection+"_"+channel+"/data/"+suffix+".root";
  TFile * ofile = new TFile(ostring.c_str(), "RECREATE");
  mtHist->Write();
  metHist->Write();
  lptHist->Write();
  letaHist->Write();

  mtHistTight->Write();
  metHistTight->Write();
  lptHistTight->Write();
  letaHistTight->Write();

  mtHist_kin->Write();
  metHist_kin->Write();
  lptHist_kin->Write();
  letaHist_kin->Write();

  mtHistTight_kin->Write();
  metHistTight_kin->Write();
  lptHistTight_kin->Write();
  letaHistTight_kin->Write();

  dPhiHist->Write();
  dPhiHistTight->Write();
  ptmtHist->Write();
  ptmtHistTight->Write();
  ptetaHist->Write();
  ptetaHistTight->Write();
  ptphiHist->Write();
  ptphiHistTight->Write();
  MCLumiHist->Write();
  ofile->Write();
  ofile->Close();

  return 0;

}
