void Amartya_macro(){
  TH1D *hqcd_ej_eta = new TH1D("he_eta","he_eta",1,0,1)
  TH1D *hqcd_ej_mT = new TH1D("he_mT","he_mT",1,0,1)
  TH1D *hqcd_ej_phi = new TH1D("he_phi","he_phi",1,0,1)
  TH1D *hqcd_mj_eta = new TH1D("hm_eta","hm_eta",1,0,1)
  TH1D *hqcd_mj_mT = new TH1D("hm_mT","hm_mT",1,0,1)
  TH1D *hqcd_mj_phi = new TH1D("hm_phi","hm_phi",1,0,1)
  
  double weight_lfake_pTeta
  double weight_lfake_pTmT
  double weight_lfake_pTphi
  Int_t ejets_2015;
  Int_t ejets_2016;
  Int_t ejets_2017;
  Int_t ejets_2018;
  Int_t mujets_2015;
  Int_t mujets_2016;
  Int_t mujets_2017;
  Int_t mujets_2018;
  
  nominal_lj->SetBranchAddress("weight_lfake_pTeta", &weight_lfake_pTeta)
  nominal_lj->SetBranchAddress("weight_lfake_pTmT", &weight_lfake_pTmT)
  nominal_lj->SetBranchAddress("weight_lfake_pTphi", &weight_lfake_pTphi)
  nominal_lj->SetBranchAddress("ejets_2015", &ejets_2015)
  nominal_lj->SetBranchAddress("ejets_2016", &ejets_2016)
  nominal_lj->SetBranchAddress("ejets_2017", &ejets_2017)
  nominal_lj->SetBranchAddress("ejets_2018", &ejets_2018)
  nominal_lj->SetBranchAddress("mujets_2015", &mujets_2015)
  nominal_lj->SetBranchAddress("mujets_2016", &mujets_2016)
  nominal_lj->SetBranchAddress("mujets_2017", &mujets_2017)
  nominal_lj->SetBranchAddress("mujets_2018", &mujets_2018)
  
  for(int i=0;i<nominal_lj->GetEntries();++i){
  nominal_lj->GetEntry(i);
  if(ejets_2015 || ejets_2016 || ejets_2017 || ejets_2018){
  hqcd_ej_eta->Fill(0.5, weight_lfake_pTeta);
  hqcd_ej_mT->Fill(0.5, weight_lfake_pTmT);
  hqcd_ej_phi->Fill(0.5, weight_lfake_pTphi);
  }
  else if(mujets_2015 || mujets_2016 || mujets_2017 || mujets_2018){
  hqcd_mj_eta->Fill(0.5, weight_lfake_pTeta);
  hqcd_mj_mT->Fill(0.5, weight_lfake_pTmT);
  hqcd_mj_phi->Fill(0.5, weight_lfake_pTphi);
  }
  }
  
  hqcd_ej_eta->Integral()
  hqcd_ej_mT->Integral()
  hqcd_ej_phi->Integral()
  
  hqcd_mj_eta->Integral()
  hqcd_mj_mT->Integral()
  hqcd_mj_phi->Integral()


}
