void makePlots(TString filename, TString obj, TString effType, TString var2, TString yaxisTitle, TString saveString){
  //TString obj = "el"; //el/mu
  //TString effType = "lfake"; //"real"/"lfake"
  TString var1 = "pt";
  //TString var2 = "eta"; //eta/mt/phi
  //TString filename = "pt_eta_2D_el.root";
  //TString yaxisTitle = "|#eta|";
  TFile *file = TFile::Open(filename);
  //Hist name
  TString histName = effType + "_"+var1+"_"+var2+"_2D_Tight";
  TH2F *hist = (TH2F*)file->Get(histName);
  hist->GetXaxis()->SetTitle("p^{l}_{T} [GeV]");
  hist->GetYaxis()->SetTitle(yaxisTitle);
  //TCanvas *c = new TCanvas("c", "canvas", 1200,900);
  TCanvas *c = new TCanvas("c");
  c->SetRightMargin(0.09);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.15);
  c->cd();
  gStyle->SetPaintTextFormat("0.2f");
  hist->Draw("textcolzerror");
  gStyle->SetOptStat("ne");
/*
  gPad->Update();
  TPaletteAxis *palette = (TPaletteAxis*)hist->GetListOfFunctions()->FindObject("palette");

  // the following lines moe the paletter. Choose the values you need for the position.
  palette->SetX1NDC(0.95);
  palette->SetX2NDC(1.0);
  palette->SetY1NDC(0.2);
  palette->SetY2NDC(0.8);
  gPad->Modified();
  gPad->Update();
*/
  //TString saveString = obj+"_"+histName+".pdf";
  c->SaveAs(saveString);
  c->SaveAs(saveString+".root");
}
