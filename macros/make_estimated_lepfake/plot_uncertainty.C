//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasUtils.h"
#include "/afs/cern.ch/work/b/bmondal/atlasrootstyle/AtlasStyle.h"
#include "/afs/cern.ch/work/b/bmondal/atlasrootstyle/AtlasLabels.h"
//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasStyle.h"
//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasLabels.C"
//#include "/afs/cern.ch/user/b/bmondal/work/atlasrootstyle/AtlasUtils.C"
//
void plot_uncertainty(std::string objName, std::string kinVar, std::string channelName, std::string yaxistitle){
  TString obj = objName;
  TString var = kinVar;
  TString channel = channelName;
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
  ph_eta_nominal->GetXaxis()->SetTitle(yaxistitle.c_str());
  ph_eta_nominal->GetYaxis()->SetTitle("Events");
  ph_eta_nominal->Draw("HIST E ");
  ph_eta_up->Draw("HIST SAME E ");
  ph_eta_down->Draw("HIST SAME E ");


  myText(  0.4,  0.85, 1, 0.040,"#sqrt{s}= 13 TeV; Lumi = 139 fb^{-1};");
  myText(  0.4, 0.80, 1, 0.040,"#mujets; t#bar{t}#gamma SR");

  ATLASLabel(0.4,0.75,"Internal");

  TLegend *leg = new TLegend(0.8, 0.6, 0.98, 0.9); 
  //leg->AddEntry(ph_eta_nominal, Form("pt:mt %0.1f", nominal_yield), "l");
  //leg->AddEntry(ph_eta_up, Form("pt:dPhi %0.1f",up_yield), "l");
  //leg->AddEntry(ph_eta_down, Form("pt:eta %0.1f", down_yield), "l");
  leg->AddEntry(ph_eta_nominal, Form("pt:mt"), "l");
  leg->AddEntry(ph_eta_up, Form("pt:dPhi "), "l");
  leg->AddEntry(ph_eta_down, Form("pt:eta "), "l");

  leg->Draw();


  TString saveName = obj+"_"+var+".pdf";
  c->SaveAs(saveName);

}

void plot_uncertainty(std::string fileName, std::string saveNamePrefix, std::string objName, std::string kinVar, std::string channelName, std::string yaxistitle, int rebin){

  TString obj = objName;
  TString var = kinVar;
  TString channel = channelName;
  TFile *file = TFile::Open(fileName.c_str());

  TString hist_up="";
  TString hist_nominal="";
  TString hist_down="";
  if((obj=="met")|| (obj=="mt")){hist_up = "h_"+obj+"_up";}else{hist_up = "h_"+obj+"_"+var+"_up";}
  if((obj=="met")|| (obj=="mt")){hist_nominal = "h_"+obj+"_nominal";}else{hist_nominal = "h_"+obj+"_"+var+"_nominal";}
  if((obj=="met")|| (obj=="mt")){hist_down = "h_"+obj+"_down";}else{hist_down = "h_"+obj+"_"+var+"_down";}
  TH1F* ph_eta_nominal = (TH1F*)file->Get(hist_nominal);
  TH1F* ph_eta_up = (TH1F*)file->Get(hist_up);
  TH1F* ph_eta_down = (TH1F*)file->Get(hist_down);
  //rebin
  ph_eta_nominal->Rebin(rebin);
  ph_eta_up->Rebin(rebin);
  ph_eta_down->Rebin(rebin);

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
  ph_eta_nominal->GetXaxis()->SetTitle(yaxistitle.c_str());
  ph_eta_nominal->GetYaxis()->SetTitle("Events");
  ph_eta_nominal->Draw("HIST E min0");
  ph_eta_up->Draw("HIST SAME E min0");
  ph_eta_down->Draw("HIST SAME E min0");


  myText(  0.4,  0.85, 1, 0.040,"#sqrt{s}= 13 TeV; Lumi = 139 fb^{-1};");
  myText(  0.4, 0.80, 1, 0.040,"#mujets; t#bar{t}#gamma SR");

  ATLASLabel(0.4,0.75,"Internal");

  TLegend *leg = new TLegend(0.8, 0.6, 0.98, 0.9); 
  //leg->AddEntry(ph_eta_nominal, Form("pt:mt %0.1f", nominal_yield), "l");
  //leg->AddEntry(ph_eta_up, Form("pt:dPhi %0.1f",up_yield), "l");
  //leg->AddEntry(ph_eta_down, Form("pt:eta %0.1f", down_yield), "l");
  leg->AddEntry(ph_eta_nominal, Form("pt:mt"), "l");
  leg->AddEntry(ph_eta_up, Form("pt:dPhi "), "l");
  leg->AddEntry(ph_eta_down, Form("pt:eta "), "l");

  leg->Draw();


  TString saveName = obj+"_"+var+saveNamePrefix;
  c->SaveAs(saveName+".pdf");
  c->SaveAs(saveName+".png");
  c->SaveAs(saveName+".root");

}
