//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasUtils.h"
#include "/afs/cern.ch/work/b/bmondal/atlasrootstyle/AtlasStyle.h"
#include "/afs/cern.ch/work/b/bmondal/atlasrootstyle/AtlasLabels.h"
//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasStyle.h"
//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasLabels.C"
//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasUtils.C"
void plot_uncertainty(){
  TString obj = "el";
  TString var = "eta";
  TString channel = "ljets";
  TString filename_nominal = obj+"_"+var+"_preFit_nominal.root";
  TString filename_up = obj+"_"+var+"_preFit_up.root";
  TString filename_down = obj+"_"+var+"_preFit_down.root";
  TFile *file_nominal = TFile::Open(filename_nominal);
  TFile *file_up = TFile::Open(filename_up);
  TFile *file_down = TFile::Open(filename_down);

  TH1F* ph_eta_nominal = (TH1F*)file_nominal->Get("h_tot");
  TH1F* ph_eta_up = (TH1F*)file_up->Get("h_tot");
  TH1F* ph_eta_down = (TH1F*)file_down->Get("h_tot");
  //rebin
  ph_eta_nominal->Rebin(2);
  ph_eta_up->Rebin(2);
  ph_eta_down->Rebin(2);

  double nominal_yield = ph_eta_nominal->Integral() + ph_eta_nominal->GetBinContent(0)+ ph_eta_nominal->GetBinContent(ph_eta_nominal->GetNbinsX()+1);
  double up_yield = ph_eta_up->Integral()+ ph_eta_up->GetBinContent(0)+ ph_eta_up->GetBinContent(ph_eta_up->GetNbinsX()+1);
  double down_yield = ph_eta_down->Integral()+ ph_eta_down->GetBinContent(0)+ ph_eta_down->GetBinContent(ph_eta_down->GetNbinsX()+1);

  ph_eta_nominal->SetLineColor(1);
  ph_eta_nominal->SetMarkerColor(1);
  ph_eta_up->SetLineColor(2);
  ph_eta_up->SetMarkerColor(2);
  ph_eta_down->SetLineColor(3);
  ph_eta_down->SetMarkerColor(3);
 
  TCanvas *c = new TCanvas("c");
  c->cd();
  ph_eta_nominal->GetXaxis()->SetTitle("#eta");
  ph_eta_nominal->GetYaxis()->SetTitle("Events");
  ph_eta_nominal->Draw("HIST E ");
  ph_eta_up->Draw("HIST SAME E ");
  ph_eta_down->Draw("HIST SAME E ");


  myText(  0.3,  0.85, 1, "#sqrt{s}= 13 TeV; t#bar{t}#gamma SR");
  myText(  0.57, 0.85, 1, "Lumi = 139 fb^{-1}");

  ATLASLabel(0.3,0.8,"Internal");

  TLegend *leg = new TLegend(0.8, 0.6, 0.98, 0.9); 
  leg->AddEntry(ph_eta_nominal, Form("pt:mt %0.1f", nominal_yield), "l");
  leg->AddEntry(ph_eta_up, Form("pt:dPhi %0.1f",up_yield), "l");
  leg->AddEntry(ph_eta_down, Form("pt:eta %0.1f", down_yield), "l");
  leg->Draw();


  TString saveName = obj+"_"+var+".pdf";
  c->SaveAs(saveName);

}
