void PrintLepfakeNumber(std::string obj, std::string param, TH1D* hist){

  std::cout<<"Estimated Lepfake for "<<obj<<"  for  "<<param<<" : "<<hist->Integral()<<std::endl; 

}
void getNumbers(std::string filename){
  TFile* file = TFile::Open(filename.c_str());
  TH1D* h_tot_events_el_down_weight = (TH1D*)file->Get("h_tot_events_el_down_weight"); 
  TH1D* h_tot_events_el_nominal_weight = (TH1D*)file->Get("h_tot_events_el_nominal_weight"); 
  TH1D* h_tot_events_el_up_weight = (TH1D*)file->Get("h_tot_events_el_up_weight"); 
  // mu
  TH1D* h_tot_events_mu_down_weight  = (TH1D*)file->Get("h_tot_events_mu_down_weight"); 
  TH1D* h_tot_events_mu_nominal_weight = (TH1D*)file->Get("h_tot_events_mu_nominal_weight"); 
  TH1D* h_tot_events_mu_up_weight = (TH1D*)file->Get("h_tot_events_mu_up_weight"); 

  PrintLepfakeNumber("el", "Down", h_tot_events_el_down_weight);
  PrintLepfakeNumber("el", "Nominal", h_tot_events_el_nominal_weight);
  PrintLepfakeNumber("el", "Up", h_tot_events_el_up_weight);

  PrintLepfakeNumber("mu", "Down", h_tot_events_mu_down_weight);
  PrintLepfakeNumber("mu", "Nominal", h_tot_events_mu_nominal_weight);
  PrintLepfakeNumber("mu", "Up", h_tot_events_mu_up_weight);

}
