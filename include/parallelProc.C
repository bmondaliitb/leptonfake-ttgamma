#include <iostream>
#include <vector>
#include <TH2.h>
#include <TH3.h>
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

// class leptonfake scale factor
class LeptonFakeEfficiencyRetriever{
public:
	LeptonFakeEfficiencyRetriever(const std::string& realEffRootFileElelctron,
	                              const std::string& fakeEffRootFileElectron);
	
	// channel l+jet or dilep
	//void setChannel(std::string channel);
	
	/**
	 * @brief calculate event weight from the efficiency
	 *
	 */
	 double getEventWeight(double eta, double pt, bool isTight );
	
public:
	TH1F* m_realEfficiency2D_el_pt_eta = nullptr;
	TH1F* m_fakeEfficiency2D_el_pt_eta = nullptr;
};

LeptonFakeEfficiencyRetriever::LeptonFakeEfficiencyRetriever(const std::string& realEffRootFileElelctron, const std::string& fakeEffRootFileElectron){
		TFile* realEffRootFileEl = TFile::Open(realEffRootFileElelctron.c_str(), "READ");
    TFile* fakeEffRootFileEl = TFile::Open(fakeEffRootFileElectron.c_str(), "READ");

    // get the objects
    //m_realEfficiency2D_el_pt_eta = (TH1F*)fakeEffRootFileEl->Get("real_pt_eta_2D_Tight");
    m_realEfficiency2D_el_pt_eta = (TH1F*)realEffRootFileEl->Get("real_pt_eta_2D_Tight");
    //m_realEfficiency2D_el_pt_eta = (TH1F*)realEffRootFileEl->Get("RealEfficiency2D_el_pt_eta");
    m_fakeEfficiency2D_el_pt_eta = (TH1F*)fakeEffRootFileEl->Get("lfake_pt_eta_2D_Tight");
}

double LeptonFakeEfficiencyRetriever::getEventWeight(double eta, double pt, bool isTight){
			double weight=0;
			double fake_eff = m_fakeEfficiency2D_el_pt_eta->GetBinContent(m_fakeEfficiency2D_el_pt_eta->FindFixBin(pt,eta));
      double real_eff = m_realEfficiency2D_el_pt_eta->GetBinContent(m_realEfficiency2D_el_pt_eta->FindFixBin(pt,eta));
      //std::cout<<"pt  "<<pt<<" eta  "<<eta<<" fake_eff "<<fake_eff<<" "<<"real_eff  "<<real_eff<<std::endl;
      if(isTight){
        if(real_eff != fake_eff) weight = fake_eff*(real_eff - 1)/(real_eff - fake_eff);
      }
      else{
        if(real_eff != fake_eff) weight = fake_eff*(real_eff)/(real_eff - fake_eff);
      }
		 return weight;
}

/*
// lets keep it globally
std::string realEffRootFile="/eos/user/b/bmondal/tty/lfakeEff/pt_eta_2D.root";
std::string fakeEffRootFile="/eos/user/b/bmondal/tty/lfakeEff/pt_eta_2D.root";

LeptonFakeEfficiencyRetriever lfakeObj(realEffRootFile, fakeEffRootFile);

double getLeptonFakeWeight(double eta, double pt, bool isTight){
	return lfakeObj.getEventWeight(eta, pt, isTight);
}
*/

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
std::cout<<"stype: "<<stype<<" campaign: "<<campaign<<" selection: "<<selection<<" channel: "<<channel<<" sample: "<<sample<<" mcID: "<<mcID<<std::endl;
  TString treename = TString(selection)+"/MuonProbes";
  if(channel == "el") treename=TString(selection)+"/ElectronProbes";
  if(stype == "real"){
     //treename=TString(selection)+"_mumu"+"/MuonProbes";
     treename=TString(selection)+"/MuonProbes";
     //if(channel == "el") treename=TString(selection)+"_ee"+"/ElectronProbes";
     if(channel == "el") treename=TString(selection)+"/ElectronProbes";
  }

  TH1F * mtHistTight = new TH1F();
  TH1F * mtHist = new TH1F();
  mtHist->SetName("mt");
  mtHist->SetTitle("#it{m}_{T_{W}} [GeV]");
  mtHistTight->SetName("mt_Tight");
  mtHistTight->SetTitle("#it{m}_{T_{W}} [GeV]");

  // p_T of leading jet
  TH1F * leadingJetPtTight = new TH1F();
  TH1F * leadingJetPt = new TH1F();
  leadingJetPt->SetName("leadingJetPt");
  leadingJetPt->SetTitle("#it{p}_{T}^{l} [GeV]");
  leadingJetPtTight->SetName("leadingJetPt_Tight");
  leadingJetPtTight->SetTitle("#it{p}_{T}^{l} [GeV]");


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

  // deltaR(lepton and the closest jet)
  TH1F * dRHist = new TH1F();
  TH1F * dRHistTight = new TH1F();
  dRHist->SetName("dR");
  dRHist->SetTitle("#Delta #R(l,#closestjet)");
  dRHistTight->SetName("dR_Tight");
  dRHistTight->SetTitle("#Delta #R(l,#closestjet)");

  // number of bjets
  TH1F * nbjets = new TH1F();
  TH1F * nbjetsTight = new TH1F();
  nbjets->SetName("nbjets");
  nbjets->SetTitle("nbjets");
  nbjetsTight->SetName("nbjets_Tight");
  nbjetsTight->SetTitle("nbjets_Tight");

  // number of jets
  TH1F * njets = new TH1F();
  TH1F * njetsTight = new TH1F();
  njets->SetName("njets");
  njets->SetTitle("njets");
  njetsTight->SetName("njets_Tight");
  njetsTight->SetTitle("njets_Tight");


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

  // 3D histos
  TH3F * nJetnBJetEtaHist = new TH3F();
  TH3F * nJetnBJetEtaHistTight = new TH3F();
  nJetnBJetEtaHist->SetName("njet_nbjet_eta_3D");
  nJetnBJetEtaHist->SetXTitle("njet ");
  nJetnBJetEtaHist->SetYTitle("nbjet");
  nJetnBJetEtaHist->SetZTitle("eta");
  nJetnBJetEtaHistTight->SetName("njet_nbjet_eta_3D_Tight");
  nJetnBJetEtaHistTight->SetXTitle("njetTight");
  nJetnBJetEtaHistTight->SetYTitle("nbjetTight");
  nJetnBJetEtaHistTight->SetZTitle("etaTight");

  TH3F * nJetnBJetPtHist = new TH3F();
  TH3F * nJetnBJetPtHistTight = new TH3F();
  nJetnBJetPtHist->SetName("njet_nbjet_pt_3D");
  nJetnBJetPtHist->SetXTitle("njet ");
  nJetnBJetPtHist->SetYTitle("nbjet");
  nJetnBJetPtHist->SetZTitle("pt");
  nJetnBJetPtHistTight->SetName("njet_nbjet_pt_3D_Tight");
  nJetnBJetPtHistTight->SetXTitle("njetTight");
  nJetnBJetPtHistTight->SetYTitle("nbjetTight");
  nJetnBJetPtHistTight->SetZTitle("ptTight");

  TH3F * nJetnBJetdPhiHist = new TH3F();
  TH3F * nJetnBJetdPhiHistTight = new TH3F();
  nJetnBJetdPhiHist->SetName("njet_nbjet_dphi_3D");
  nJetnBJetdPhiHist->SetXTitle("njet ");
  nJetnBJetdPhiHist->SetYTitle("nbjet");
  nJetnBJetdPhiHist->SetZTitle("dphi");
  nJetnBJetdPhiHistTight->SetName("njet_nbjet_dphi_3D_Tight");
  nJetnBJetdPhiHistTight->SetXTitle("njetTight");
  nJetnBJetdPhiHistTight->SetYTitle("nbjetTight");
  nJetnBJetdPhiHistTight->SetZTitle("dphiTight");

  if(channel == "mu"){
    const Int_t ptbins = 5; const Int_t mtbins = 5;const Int_t phibins = 5; const Int_t etabins = 5; const Int_t nobjbins = 20;
    Double_t mtEdges[mtbins + 1] = {0.,7.,15., 25., 40.,100.};
    Double_t ptEdges[ptbins + 1] = {27.,35., 45.,52, 60.,100.};
    Double_t phiEdges[phibins + 1] = {0., 0.5, 1.0, 1.5, 2.0, 3.2};
    Double_t etaEdges[nobjbins + 1] = {0.,0.5,1.,1.5,2.0,2.5};
    Double_t nobjEdges[nobjbins + 1] = {0.,1.,2.0,3, 4, 5, 6,7, 8, 9, 10, 11,  12, 13, 14, 15, 16, 17, 18, 19, 20};
    mtHist->SetBins(mtbins,mtEdges);
    mtHistTight->SetBins(mtbins,mtEdges);
    lptHist->SetBins(ptbins,ptEdges);
    lptHistTight->SetBins(ptbins,ptEdges);
    letaHist->SetBins(etabins,etaEdges);
    letaHistTight->SetBins(etabins,etaEdges);
    dPhiHist->SetBins(phibins,phiEdges);
    dPhiHistTight->SetBins(phibins,phiEdges);
    nbjets->SetBins(nobjbins, nobjEdges);
    nbjetsTight->SetBins(nobjbins, nobjEdges);
    njets->SetBins(nobjbins, nobjEdges);
    njetsTight->SetBins(nobjbins, nobjEdges);


    ptmtHist->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptmtHistTight->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptetaHist->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptetaHistTight->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptphiHist->SetBins(ptbins,ptEdges,phibins,phiEdges);
    ptphiHistTight->SetBins(ptbins,ptEdges,phibins,phiEdges);
    //nJetnBJetEtaHist->SetBins(nobjbins, nobjEdges, nobjbins, nobjEdges, etabins, etaEdges);
    //nJetnBJetEtaHistTight->SetBins(nobjbins, nobjEdges, nobjbins, nobjEdges, etabins, etaEdges);
  }

  if(channel == "el"){
    const Int_t ptbins = 4; const Int_t mtbins = 5;const Int_t phibins = 5; const Int_t etabins = 5;const Int_t nobjbins = 20;
    Double_t ptEdges[ptbins + 1] = {27.,35., 45., 62., 100.};
    //Double_t mtEdges[mtbins + 1] = {0.,40.,60.,80., 140.};
    Double_t mtEdges[mtbins + 1] = {0.,7.,15., 25., 40.,100.};
    Double_t phiEdges[phibins + 1] = {0., 0.5, 1.0, 1.5, 2.0, 3.2};
    Double_t etaEdges[nobjbins+ 1] = {0.,0.5,1.,1.5,2.0,2.5};
    Double_t nobjEdges[nobjbins + 1] = {0.,1.,2.0,3, 4, 5, 6,7, 8, 9, 10, 11,  12, 13, 14, 15, 16, 17, 18, 19, 20};
    mtHist->SetBins(mtbins,mtEdges);
    mtHistTight->SetBins(mtbins,mtEdges);
    lptHist->SetBins(ptbins,ptEdges);
    lptHistTight->SetBins(ptbins,ptEdges);
    letaHist->SetBins(etabins,etaEdges);
    letaHistTight->SetBins(etabins,etaEdges);
    dPhiHist->SetBins(phibins,phiEdges);
    dPhiHistTight->SetBins(phibins,phiEdges);
    nbjets->SetBins(nobjbins, nobjEdges);
    nbjetsTight->SetBins(nobjbins, nobjEdges);
    njets->SetBins(nobjbins, nobjEdges);
    njetsTight->SetBins(nobjbins, nobjEdges);

    ptmtHist->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptmtHistTight->SetBins(ptbins,ptEdges,mtbins,mtEdges);
    ptetaHist->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptetaHistTight->SetBins(ptbins,ptEdges,etabins,etaEdges);
    ptphiHist->SetBins(ptbins,ptEdges,phibins,phiEdges);
    ptphiHistTight->SetBins(ptbins,ptEdges,phibins,phiEdges);
    //nJetnBJetEtaHist->SetBins(nobjbins, nobjEdges, nobjbins, nobjEdges, etabins, etaEdges);
    //nJetnBJetEtaHistTight->SetBins(nobjbins, nobjEdges, nobjbins, nobjEdges, etabins, etaEdges);

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
  EffTree *looseTree = new EffTree((TTree*)tfile->Get(treename));
  int nEntries = looseTree->fChain->GetEntries();
  cout << "###########################################" << endl;
  cout << "Processing "<<mcID <<" with " <<nEntries << " Entries" << endl;
  cout << "###########################################" << endl;

  for (int entry(0); entry < nEntries; entry++){
        looseTree->fChain->GetEntry(entry);
        if((entry%100)==0) cout << "Processed " <<entry<<"/"<<nEntries <<" Entries" << endl;
        //if(stype == "fake" && channel == "mu" && (looseTree->met > 30 )) continue;
        //if(stype == "fake" && channel == "el" && (looseTree->met < 30 || looseTree->met > 50)) continue;
        //if(stype == "fake" && channel == "mu" && (looseTree->met < 30 || looseTree->met > 50)) continue;

        if(stype == "fake" && channel == "mu" && looseTree->met > 30 ) continue;
        if(stype == "fake" && channel == "el" && looseTree->met > 30 ) continue;
        if(!isData){
            if(channel == "mu" && !(looseTree->mc_truthIFFClass == 4)) continue;
            else if(channel == "el" && !(looseTree->mc_truthIFFClass == 2 || looseTree->mc_truthIFFClass == 3)) continue;
        }

        //if(fabs(looseTree->mu_phi->at(0)-looseTree->met_phi) > 1.0) continue;

        double mtval = looseTree->mt;
        double dPhival = dPhi(mtval,looseTree->pt_probe, looseTree->met);
        double weight = 1.;
				
				/*
				// this part is not needed when calculating for efficiency calculation 
				//if data, get the lepton fake event weight
				double leptonFakeWeight = 1;
				if(isData){
					if(!looseTree->isTight)
					leptonFakeWeight = getLeptonFakeWeight(looseTree->eta_probe, looseTree->pt_probe, looseTree->isTight);
				}
				double weight_loose = weight*leptonFakeWeight;
				//std::cout<<weight_loose<<std::endl;
				// this part is not needed when calculating for efficiency calculation 
				*/

        if(!isData){
	    //if(mcID==410470) {weight = looseTree->eventWeightLoose*95/100;} // chaning ttbar normalization by 5%
            //else {weight = looseTree->eventWeightLoose;}
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
        //nJetnBJetEtaHist->Fill(looseTree->nJets, looseTree->nBJets, fabs(looseTree->eta_probe), weight);


        nbjets->Fill(looseTree->nBJets, weight);
        njets->Fill(looseTree->nJets, weight);

        if(looseTree->isTight==1){
						//double weight_lepfake = 1;
						//weight_lepfake = getLeptonFakeWeight(looseTree->eta_probe, looseTree->pt_probe, looseTree->isTight);
						//weight = weight*weight_lepfake;
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
            nJetnBJetEtaHistTight->Fill(looseTree->nJets, looseTree->nBJets, fabs(looseTree->eta_probe), weight);
            
            nbjetsTight->Fill(looseTree->nBJets, weight);
            njetsTight->Fill(looseTree->nJets, weight);
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
  //nJetnBJetEtaHist->Write();
  nJetnBJetEtaHistTight->Write();
  ptphiHistTight->Write();
  MCLumiHist->Write();
  nbjetsTight->Write();
  njetsTight->Write();
  nbjets->Write();
  njets->Write();

  ofile->Write();
  ofile->Close();

  return 0;

}
