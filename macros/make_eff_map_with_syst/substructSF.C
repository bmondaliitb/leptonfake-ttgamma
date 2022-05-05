/* Direction to use:
 * 1. keep the sf files in this folder
 * 2. change the prefix variable to "un" for unconverted and keep it empty for converted case
 * 3. run the macro
 */
void substructSF(TString prefix){
  gStyle->SetPaintTextFormat("4.2f ");
  gStyle->SetTextFont(62);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  
  
  //TString prefix="";
  TString nominal = prefix+"converted_nominal__sf.root";
  TString mass = prefix+"converted_syst_mass_sf.root";
  TString bkg = prefix+"converted_syst_bkg_sf.root";
  TString sig = prefix+"converted_syst_sig_sf.root";
  TFile *fnominal = TFile::Open(nominal);
  TFile *fCmass = TFile::Open(mass);
  TFile *fCbkg = TFile::Open(bkg);
  TFile *fCsig = TFile::Open(sig);
//TFile *fCzeey = TFile::Open("h2_sf_using_zeey.root");

  //calculate total systematics
  const Int_t NBINS_ETA = 5;  
  Double_t edges_eta[NBINS_ETA + 1] = {0.0, 0.6,  1.37, 1.52, 1.8, 2.37}; 
  const Int_t NBINS_PT = 3;
  Double_t edges_pt[NBINS_PT + 1] = {20, 35, 45, 1000};
  
  
  TH2F *hnominal = (TH2F*)fnominal->Get("SF");
  TH2F *hCmass   = (TH2F*)fCmass->Get("SF");
  TH2F *hCbkg    = (TH2F*)fCbkg->Get("SF");
  TH2F *hCsig    = (TH2F*)fCsig->Get("SF");
//	TH2F *hCzeey    = (TH2F*)fCzeey->Get("SF");

  TH2F *diffMassNomi= new TH2F("diffMassNomi","difference in SF(changing-mass, nominal)",NBINS_ETA, edges_eta, NBINS_PT, edges_pt); 
  TH2F *diffCbkgNomi= new TH2F("diffCbkgNomi","difference in SF(changing-bkg-to-Gaus, nominal)",NBINS_ETA, edges_eta, NBINS_PT, edges_pt); 
  TH2F *diffCsigNomi= new TH2F("diffCsigNomi","difference in SF(changing-sig-to-MC-template, nominal)",NBINS_ETA, edges_eta, NBINS_PT, edges_pt); 
  TH2F *diffCzeeyNomi= new TH2F("diffCzeeyNomi","difference in SF(changing-to-zeey-sample, nominal)",NBINS_ETA, edges_eta, NBINS_PT, edges_pt); 
  
  TH2F *finalSF = new TH2F("finalSF","finalSF",NBINS_ETA, edges_eta, NBINS_PT, edges_pt); 
  
  
  //calculating total SF
  double totNomiSF = 0;
  double totcbkgSF = 0;
  double totcmassSF = 0;
  double totcsigSF = 0;
  double totzeeSF = 0;
  
  
  
  
  double syst_sig = 0; // systematic uncertainty due to change in sig func
  double syst_mass= 0; // systematic uncertainty due to change in sig func
  double syst_bkg= 0; // systematic uncertainty due to change in sig func
  for(int eta=0; eta<2; eta++)
  {
    for(int pt=0; pt<3; pt++)
      {
      double binvalueNominal = hnominal->GetBinContent(eta+1, pt+1);
      double binerrorNominal = hnominal->GetBinError(eta+1, pt+1);
      double binvalueCmass= hCmass->GetBinContent(eta+1, pt+1);
      double binvalueCbkg= hCbkg->GetBinContent(eta+1, pt+1);
      double binvalueCsig= hCsig->GetBinContent(eta+1, pt+1);
      //double binvalueCzeey= hCzeey->GetBinContent(eta+1, pt+1);
      
      diffMassNomi->SetBinContent(eta+1, pt+1, fabs(binvalueCmass-binvalueNominal)/binvalueNominal);
      diffCbkgNomi->SetBinContent(eta+1, pt+1, fabs(binvalueCbkg-binvalueNominal)/binvalueNominal);
      diffCsigNomi->SetBinContent(eta+1, pt+1, fabs(binvalueCsig-binvalueNominal)/binvalueNominal);
      //diffCzeeyNomi->SetBinContent(eta+1, pt+1, (binvalueCzeey-binvalueNominal));
      
      //double totalsyssqrd = (binvalueCmass-binvalueNominal)*(binvalueCmass-binvalueNominal) + (binvalueCbkg-binvalueNominal)*(binvalueCbkg-binvalueNominal) + (binvalueCsig-binvalueNominal)*(binvalueCsig-binvalueNominal) + (binvalueCzeey-binvalueNominal)*(binvalueCzeey-binvalueNominal);
      double totalsyssqrd = (binvalueCmass-binvalueNominal)*(binvalueCmass-binvalueNominal) + (binvalueCbkg-binvalueNominal)*(binvalueCbkg-binvalueNominal) + (binvalueCsig-binvalueNominal)*(binvalueCsig-binvalueNominal) ;
      
      double totalsys = sqrt(totalsyssqrd);
      
      finalSF->SetBinContent(eta+1, pt+1, binvalueNominal);
      finalSF->SetBinError(eta+1, pt+1, sqrt((binerrorNominal*binerrorNominal)+(totalsys*totalsys)));
      
      //double binerror= hCmass->GetBinError(eta+1, pt+1);
      //totSys->SetBinError(eta+1, pt+1, sqrt(binerror));
  		totNomiSF += binvalueNominal;
  		totcbkgSF += binvalueCbkg;
  		totcmassSF += binvalueCmass;
  		totcsigSF += binvalueCsig;
  		//totzeeSF += binvalueCzeey;
  
  		syst_sig = syst_sig + (binvalueNominal - binvalueCsig)*(binvalueNominal - binvalueCsig);
  		syst_mass= syst_mass+ (binvalueNominal - binvalueCmass)*(binvalueNominal - binvalueCmass);
  		syst_bkg= syst_bkg+ (binvalueNominal - binvalueCbkg)*(binvalueNominal - binvalueCbkg);
  
  		
  	}
  }
  for(int eta=2; eta<4; eta++)
  {
  	for(int pt=0; pt<3; pt++)
  	{
  		double binvalueNominal = hnominal->GetBinContent(eta+2, pt+1);
  		double binerrorNominal = hnominal->GetBinError(eta+2, pt+1);
  		double binvalueCmass= hCmass->GetBinContent(eta+2, pt+1);
  		double binvalueCbkg= hCbkg->GetBinContent(eta+2, pt+1);
  		double binvalueCsig= hCsig->GetBinContent(eta+2, pt+1);
  		//double binvalueCzeey= hCzeey->GetBinContent(eta+2, pt+1);
  
  		diffMassNomi->SetBinContent(eta+2, pt+1, fabs(binvalueCmass-binvalueNominal)/binvalueNominal);
  		diffCbkgNomi->SetBinContent(eta+2, pt+1, fabs(binvalueCbkg-binvalueNominal)/binvalueNominal);
  		diffCsigNomi->SetBinContent(eta+2, pt+1, fabs(binvalueCsig-binvalueNominal)/binvalueNominal);
  		//diffCzeeyNomi->SetBinContent(eta+2, pt+1, (binvalueCzeey-binvalueNominal));
  
  		//double totalsyssqrd = (binvalueCmass-binvalueNominal)*(binvalueCmass-binvalueNominal) + (binvalueCbkg-binvalueNominal)*(binvalueCbkg-binvalueNominal) + (binvalueCsig-binvalueNominal)*(binvalueCsig-binvalueNominal) + (binvalueCzeey-binvalueNominal)*(binvalueCzeey-binvalueNominal);
  		double totalsyssqrd = (binvalueCmass-binvalueNominal)*(binvalueCmass-binvalueNominal) + (binvalueCbkg-binvalueNominal)*(binvalueCbkg-binvalueNominal) + (binvalueCsig-binvalueNominal)*(binvalueCsig-binvalueNominal);
  
  		double totalsys = sqrt(totalsyssqrd);
  
  		finalSF->SetBinContent(eta+2, pt+1, binvalueNominal);
  		finalSF->SetBinError(eta+2, pt+1, sqrt((binerrorNominal*binerrorNominal)+(totalsys*totalsys)));
  
  		totNomiSF += binvalueNominal;
  		totcbkgSF += binvalueCbkg;
  		totcmassSF += binvalueCmass;
  		totcsigSF += binvalueCsig;
  		//totzeeSF += binvalueCzeey;
  
  
  		syst_sig = syst_sig + (binvalueNominal - binvalueCsig)*(binvalueNominal - binvalueCsig);
  		syst_mass= syst_mass+ (binvalueNominal - binvalueCmass)*(binvalueNominal - binvalueCmass);
  		syst_bkg= syst_bkg+ (binvalueNominal - binvalueCbkg)*(binvalueNominal - binvalueCbkg);
  
  	}
  }
  
  double avgNomiSF  = totNomiSF/12;
  double avgcbkgSF  = totcbkgSF/12;
  double avgcmassSF  = totcmassSF/12;
  double avgcsigSF  = totcsigSF/12;
  //double avgzeeSF  = totzeeSF/20;
  
  //cout <<"total nomiSF   "<<avgNomiSF<<"   Percentage change  :"<<endl;
  //cout <<"total cbkgSF   "<<avgcbkgSF<<"   Percentage change  :" <<fabs(avgcbkgSF - avgNomiSF)*100/avgNomiSF<<"%"<<endl;
  //cout <<"total cmassSF  "<<avgcmassSF<<"   Percentage change  :"<<fabs(avgcmassSF - avgNomiSF)*100/avgNomiSF<<"%"<<endl;
  //cout <<"total csigSF   "<<avgcsigSF<<"   Percentage change  :" <<fabs(avgcsigSF - avgNomiSF)*100/avgNomiSF<<"%"<<endl;
  
  
  //cout <<"total csigSF   "<<avgcsigSF<<"   Impact due to sig func change  :" <<sqrt(syst_sig)/(12)<<endl;
  std::cout<< "nominal SF : " <<avgNomiSF<<std::endl;
  cout <<"total csigSF   "<<avgcsigSF<<"   Impact due to sig func change  :" <<sqrt(syst_sig)*100/(12*avgNomiSF)<<"%"<<endl;
  //cout <<"total cbkgSF   "<<avgcbkgSF<<"   Impact due to bkg func change  :" <<sqrt(syst_bkg)/(12)<<endl;
  cout <<"total cbkgSF   "<<avgcbkgSF<<"   Impact due to bkg func change  :" <<sqrt(syst_bkg)*100/(12*avgNomiSF)<<"%"<<endl;
  //cout <<"total cmassSF   "<<avgcmassSF<<"   Impact due to mass func change  :" <<sqrt(syst_mass)/(12)<<endl;
  cout <<"total cmassSF   "<<avgcmassSF<<"   Impact due to mass func change  :" <<sqrt(syst_mass)*100/(12*avgNomiSF)<<"%"<<endl;
  
  
  cout <<"total zeeSF    "<<avgzeeSF<<"   Percentage change  :"<<(avgzeeSF - avgNomiSF)/avgNomiSF<<endl;
  
  
  
  
  TCanvas *c = new TCanvas("c");
  c->SetRightMargin(0.15);
  c->SetLeftMargin(0.18);
  c->SetBottomMargin(0.15);
  
  diffMassNomi->GetXaxis()->SetTitle("|#eta|");
  diffMassNomi->GetYaxis()->SetTitle("pT [GeV]");
  diffMassNomi->GetXaxis()->SetBinLabel(1,"[0.0 - 0.6]");
  diffMassNomi->GetXaxis()->SetBinLabel(2,"[0.6 - 1.37]");
  //diffMassNomi->GetXaxis()->SetBinLabel(3,"[1.0 - 1.37]");
  diffMassNomi->GetXaxis()->SetBinLabel(4,"[1.37 - 1.52]");
  diffMassNomi->GetXaxis()->SetBinLabel(5,"[1.52 - 1.8]");
  diffMassNomi->GetXaxis()->SetBinLabel(6,"[1.8 - 2.37]");
  diffMassNomi->GetYaxis()->SetBinLabel(1,"[20 - 35] ");
  diffMassNomi->GetYaxis()->SetBinLabel(2,"[35 - 45] ");
  diffMassNomi->GetYaxis()->SetBinLabel(3,"[45 - 1000] ");
  //diffMassNomi->GetYaxis()->SetBinLabel(4,"[60 - 100]");
  diffMassNomi->Draw("colztext");
  gStyle->SetOptStat("ne");
  c->SetLogy();
  c->SaveAs(prefix+"diffchangingMassWindow.png");
  c->SaveAs(prefix+"diffchangingMassWindow.pdf");
  
  TCanvas *c1 = new TCanvas("c1");
  c1->SetRightMargin(0.15);
  c1->SetLeftMargin(0.18);
  c1->SetBottomMargin(0.15);
  
  diffCbkgNomi->GetXaxis()->SetTitle("|#eta|");
  diffCbkgNomi->GetYaxis()->SetTitle("pT [GeV]");
  diffCbkgNomi->GetXaxis()->SetBinLabel(1,"[0.0 - 0.6]");
  diffCbkgNomi->GetXaxis()->SetBinLabel(2,"[0.6 - 1.37]");
  //diffCbkgNomi->GetXaxis()->SetBinLabel(3,"[1.0 - 1.37]");
  diffCbkgNomi->GetXaxis()->SetBinLabel(4,"[1.37 - 1.52]");
  diffCbkgNomi->GetXaxis()->SetBinLabel(5,"[1.52 - 1.8]");
  diffCbkgNomi->GetXaxis()->SetBinLabel(6,"[1.8 - 2.37]");
  diffCbkgNomi->GetYaxis()->SetBinLabel(1,"[20 - 35] ");
  diffCbkgNomi->GetYaxis()->SetBinLabel(2,"[35 - 45] ");
  diffCbkgNomi->GetYaxis()->SetBinLabel(3,"[45 - 1000] ");
  //diffCbkgNomi->GetYaxis()->SetBinLabel(4,"[60 - 100]");
  diffCbkgNomi->Draw("colztext");
  gStyle->SetOptStat("ne");
  c1->SetLogy();
  c1->SaveAs(prefix+"diffchangingBkgtoGaus.png");
  c1->SaveAs(prefix+"diffchangingBkgtoGaus.pdf");
  
  TCanvas *c2 = new TCanvas("c2");
  c2->SetRightMargin(0.15);
  c2->SetLeftMargin(0.18);
  c2->SetBottomMargin(0.15);
  
  diffCsigNomi->GetXaxis()->SetTitle("|#eta|");
  diffCsigNomi->GetYaxis()->SetTitle("p_{T} [GeV]");
  diffCsigNomi->GetXaxis()->SetBinLabel(1,"[0.0 - 0.6]");
  diffCsigNomi->GetXaxis()->SetBinLabel(2,"[0.6 - 1.37]");
  //diffCsigNomi->GetXaxis()->SetBinLabel(3,"[1.0 - 1.37]");
  diffCsigNomi->GetXaxis()->SetBinLabel(4,"[1.37 - 1.52]");
  diffCsigNomi->GetXaxis()->SetBinLabel(5,"[1.52 - 1.8]");
  diffCsigNomi->GetXaxis()->SetBinLabel(6,"[1.8 - 2.37]");
  diffCsigNomi->GetYaxis()->SetBinLabel(1,"[20 - 35] ");
  diffCsigNomi->GetYaxis()->SetBinLabel(2,"[35 - 45] ");
  diffCsigNomi->GetYaxis()->SetBinLabel(3,"[45 - 1000] ");
  //diffCsigNomi->GetYaxis()->SetBinLabel(4,"[60 - 100]");
  diffCsigNomi->Draw("colztext");
  gStyle->SetOptStat("ne");
  c2->SetLogy();
  c2->SaveAs(prefix+"diffchangingSigtoMCtemplate.png");
  c2->SaveAs(prefix+"diffchangingSigtoMCtemplate.pdf");

//	TCanvas *c3 = new TCanvas("c3");
//	diffCzeeyNomi->GetXaxis()->SetTitle("|eta|");
//        diffCzeeyNomi->GetYaxis()->SetTitle("pT [GeV]");
//        diffCzeeyNomi->GetXaxis()->SetBinLabel(1,"[0.0 - 0.5]");
//        diffCzeeyNomi->GetXaxis()->SetBinLabel(2,"[0.5 - 1.0]");
//        diffCzeeyNomi->GetXaxis()->SetBinLabel(3,"[1.0 - 1.37]");
//        diffCzeeyNomi->GetXaxis()->SetBinLabel(4,"[1.37 - 1.52]");
//        diffCzeeyNomi->GetXaxis()->SetBinLabel(5,"[1.52 - 2.0]");
//        diffCzeeyNomi->GetXaxis()->SetBinLabel(6,"[2.0 - 2.37]");
//        diffCzeeyNomi->GetYaxis()->SetBinLabel(1,"[20 - 35] ");
//        diffCzeeyNomi->GetYaxis()->SetBinLabel(2,"[35 - 45] ");
//        diffCzeeyNomi->GetYaxis()->SetBinLabel(3,"[45 - 1000] ");
//        //diffCzeeyNomi->GetYaxis()->SetBinLabel(4,"[60 - 100]");
//	diffCzeeyNomi->Draw("colztext");
//	gStyle->SetOptStat("ne");
//	c3->SetLogy();
//	c3->SaveAs("diffchangingtoZeeSample.eps");

	
  TCanvas *ctotalSF = new TCanvas("ctotalSF");
  ctotalSF->SetRightMargin(0.15);
  ctotalSF->SetLeftMargin(0.18);
  ctotalSF->SetBottomMargin(0.15);
  
  ctotalSF->SetLogy();
  finalSF->GetXaxis()->SetTitle("|#eta|");
  finalSF->GetYaxis()->SetTitle("p_{T} [GeV]");
  finalSF->GetXaxis()->SetBinLabel(1,"[0.0 - 0.6]");
  finalSF->GetXaxis()->SetBinLabel(2,"[0.6 - 1.37]");
  //finalSF->GetXaxis()->SetBinLabel(3,"[1.37 - 1.52]");
  finalSF->GetXaxis()->SetBinLabel(4,"[1.52 - 1.8]");
  finalSF->GetXaxis()->SetBinLabel(5,"[1.8 - 2.37]");
  //finalSF->GetXaxis()->SetBinLabel(6,"[1.8 - 2.37]");
  finalSF->GetYaxis()->SetBinLabel(1,"[20 - 35] ");
  finalSF->GetYaxis()->SetBinLabel(2,"[35 - 45] ");
  finalSF->GetYaxis()->SetBinLabel(3,"[45 - 60] ");
  finalSF->GetYaxis()->SetBinLabel(4,"[60 - 100]");
  finalSF->Draw("colztexterror");
  gStyle->SetOptStat(0);
  ctotalSF->SaveAs(prefix+"converted_finalSF.pdf");
  finalSF->SaveAs(prefix+"converted_finalSF.root");


}
