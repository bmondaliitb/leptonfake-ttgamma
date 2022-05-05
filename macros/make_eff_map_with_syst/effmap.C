void effmap(TString channel){
  //TFile *outputfile = TFile::Open("final_effmap_with_syst.root", "RECREATE");
  gStyle->SetPaintTextFormat("4.2f ");
  gStyle->SetTextFont(62);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  // minimum bin value putting it near 0
  double binval_min = 0.00000001;
  
  
  //TString prefix="";
  TString nominal = "nominal_pt_mt_2D_"+channel+"_77.root";
  TString cr3 = "cr3_pt_mt_2D_"+channel+"_77.root";
  TString norm = "norm_pt_mt_2D_"+channel+"_77.root";


  TFile *fnominal = TFile::Open(nominal);
  TFile *fcr3 = TFile::Open(cr3);
  TFile *fnorm = TFile::Open(norm);

  // histograms
  TH2D* nominal_hist_fake = (TH2D*)fnominal->Get("lfake_pt_mt_2D_Tight");
  TH2D* cr3_hist_fake = (TH2D*)fcr3->Get("lfake_pt_mt_2D_Tight");
  TH2D* norm_hist_fake = (TH2D*)fnorm->Get("lfake_pt_mt_2D_Tight");


  TH2D* final_eff_map_fake = (TH2D*) nominal_hist_fake->Clone();
  TH2D* diff_nominal_cr3_fake = (TH2D*) nominal_hist_fake->Clone();
  TH2D* diff_nominal_norm_fake = (TH2D*) nominal_hist_fake->Clone();

  // loop over bins
  for (int binx = 0; binx < nominal_hist_fake->GetNbinsX(); binx++){
    for(int biny=0; biny < nominal_hist_fake->GetNbinsY(); biny++){
      double binvalue_nominal =0;
      binvalue_nominal = nominal_hist_fake->GetBinContent(binx+1, biny+1);
      double binerror_nominal = 0;
      binerror_nominal = nominal_hist_fake->GetBinError(binx+1, biny+1);

      double binvalue_cr3 = cr3_hist_fake->GetBinContent(binx+1, biny+1);
      double binvalue_norm = norm_hist_fake->GetBinContent(binx+1, biny+1);
      // if bin value is negative, set it to zero
      if(!(binvalue_nominal > 0)) {binvalue_nominal = 0; binerror_nominal=0;}
      if(!(binvalue_cr3 > 0)) binvalue_cr3 = 0;
      if(!(binvalue_norm > 0)) binvalue_norm = 0;


      // relative error
      if(binvalue_nominal > 0) diff_nominal_cr3_fake->SetBinContent(binx+1, biny+1, fabs(binvalue_cr3-binvalue_nominal)/binvalue_nominal);
      else diff_nominal_cr3_fake->SetBinContent(binx+1, biny+1, binval_min);
      if(binvalue_nominal > 0) diff_nominal_norm_fake->SetBinContent(binx+1, biny+1, fabs(binvalue_norm-binvalue_nominal)/binvalue_nominal);
      else diff_nominal_norm_fake->SetBinContent(binx+1, biny+1, binval_min);
      
      // total uncertainty
      double syst_total_sqrd = (binvalue_cr3 - binvalue_nominal)*(binvalue_cr3 - binvalue_nominal) + (binvalue_norm - binvalue_nominal)*(binvalue_norm - binvalue_nominal) + (binerror_nominal*binerror_nominal);

      // set the nominal value to the output histogram
      if(binvalue_nominal > 0){
        nominal_hist_fake->SetBinContent(binx+1, biny+1, binvalue_nominal);
        nominal_hist_fake->SetBinError(binx+1, biny+1, sqrt(syst_total_sqrd) );
      }
      else{
        nominal_hist_fake->SetBinContent(binx+1, biny+1, binval_min);
        nominal_hist_fake->SetBinError(binx+1, biny+1, binval_min );
      }

    } 

  }

  TCanvas *ctotalSF = new TCanvas("ctotalSF");
  ctotalSF->cd();
  ctotalSF->SetRightMargin(0.15);
  ctotalSF->SetLeftMargin(0.18);
  ctotalSF->SetBottomMargin(0.15);

  nominal_hist_fake->SaveAs(channel+"final_effmap_with_syst_fake.root");
  nominal_hist_fake->Draw("textcolzerror");
  ctotalSF->SaveAs(channel+"final_effmap_with_syst_fake.pdf");

  TCanvas *c1 = new TCanvas("c1");
  c1->cd();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.18);
  c1->SetBottomMargin(0.15);
  diff_nominal_cr3_fake->Draw("textcolz0");
  c1->SaveAs(channel+"diff_nominal_cr3_fake.pdf");
  TCanvas *c2 = new TCanvas("c2");
  c2->cd();
  c2->SetRightMargin(0.15);
  c2->SetLeftMargin(0.18);
  c2->SetBottomMargin(0.15);
  diff_nominal_norm_fake->Draw("textcolz0 ");
  c2->SaveAs(channel+"diff_nominal_norm_fake.pdf");
}

void effmap(TString channel, TString real){
  if(real == "real") std::cout<<">>>>>>>>>>> executing for real efficiency one <<<<<<<<<<<<<<"<<std::endl;
  //TFile *outputfile = TFile::Open("final_effmap_with_syst.root", "RECREATE");
  gStyle->SetPaintTextFormat("4.2f ");
  gStyle->SetTextFont(62);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  // minimum bin value putting it near 0
  double binval_min = 0.00000001;
  
  
  //TString prefix="";
  TString nominal = "nominal_pt_mt_2D_"+channel+"_77.root";
  TString var = "real_syst_var_pt_mt_2D_"+channel+"_77.root";

  TFile *fnominal = TFile::Open(nominal);
  TFile *fvar = TFile::Open(var);

  // histograms
  TH2D* nominal_hist_real = (TH2D*)fnominal->Get("real_pt_mt_2D_Tight");
  TH2D* var_hist_real = (TH2D*)fvar->Get("real_pt_mt_2D_Tight");


  TH2D* final_eff_map_real = (TH2D*) nominal_hist_real->Clone();
  TH2D* diff_nominal_var_real = (TH2D*) nominal_hist_real->Clone();

  // loop over bins
  for (int binx = 0; binx < nominal_hist_real->GetNbinsX(); binx++){
    for(int biny=0; biny < nominal_hist_real->GetNbinsY(); biny++){
      double binvalue_nominal =0;
      binvalue_nominal = nominal_hist_real->GetBinContent(binx+1, biny+1);
      double binerror_nominal = 0;
      binerror_nominal = nominal_hist_real->GetBinError(binx+1, biny+1);

      double binvalue_var = var_hist_real->GetBinContent(binx+1, biny+1);


      // relative error
      if(binvalue_nominal >=0) diff_nominal_var_real->SetBinContent(binx+1, biny+1, fabs(binvalue_var-binvalue_nominal)/binvalue_nominal);
      else diff_nominal_var_real->SetBinContent(binx+1, biny+1, binval_min);
      
      // total uncertainty
      double syst_total_sqrd = (binvalue_var - binvalue_nominal)*(binvalue_var - binvalue_nominal) +  (binerror_nominal*binerror_nominal);

      // set the nominal value to the output histogram
      if(binvalue_nominal >=0){
        nominal_hist_real->SetBinContent(binx+1, biny+1, binvalue_nominal);
        nominal_hist_real->SetBinError(binx+1, biny+1, sqrt(syst_total_sqrd) );
      }
      else{
        nominal_hist_real->SetBinContent(binx+1, biny+1, binval_min);
        nominal_hist_real->SetBinError(binx+1, biny+1, binval_min );
      }

    } 

  }

  TCanvas *ctotalSF = new TCanvas("ctotalSF");
  ctotalSF->cd();
  ctotalSF->SetRightMargin(0.15);
  ctotalSF->SetLeftMargin(0.18);
  ctotalSF->SetBottomMargin(0.15);

  nominal_hist_real->SaveAs(channel+"final_effmap_with_syst_real.root");
  nominal_hist_real->Draw("textcolzerror");
  ctotalSF->SaveAs(channel+"final_effmap_with_syst_real.pdf");

  TCanvas *c1 = new TCanvas("c1");
  c1->cd();
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.18);
  c1->SetBottomMargin(0.15);
  diff_nominal_var_real->Draw("textcolz0");
  c1->SaveAs(channel+"diff_nominal_var_real.pdf");
}
