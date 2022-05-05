filepath='/afs/cern.ch/user/b/bmondal/work/ttgamma-analysis/trex_fitter/run/LeptonFake/leptonfake_estimated_240122'
#filepath='/afs/cern.ch/user/b/bmondal/work/ttgamma-analysis/trex_fitter/run/LeptonFake/leptonfake_estimated_150222'
filepatharg1='leptonfake_estimated'
# el pt
cp ${filepath}/${filepatharg1}_nominal/Histograms/el_pt_preFit.root el_pt_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/el_pt_preFit.root el_pt_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/el_pt_preFit.root el_pt_preFit_down.root
cp ${filepath}/${filepatharg1}_nominal/Histograms/el_eta_preFit.root el_eta_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/el_eta_preFit.root el_eta_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/el_eta_preFit.root el_eta_preFit_down.root

## jet pt
cp ${filepath}/${filepatharg1}_nominal/Histograms/jet_pt_preFit.root jet_pt_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/jet_pt_preFit.root jet_pt_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/jet_pt_preFit.root jet_pt_preFit_down.root
#met
cp ${filepath}/${filepatharg1}_nominal/Histograms/met_met_preFit.root met_met_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/met_met_preFit.root met_met_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/met_met_preFit.root met_met_preFit_down.root
#mu
cp ${filepath}/${filepatharg1}_nominal/Histograms/mu_pt_preFit.root mu_pt_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/mu_pt_preFit.root mu_pt_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/mu_pt_preFit.root mu_pt_preFit_down.root
cp ${filepath}/${filepatharg1}_nominal/Histograms/mu_eta_preFit.root mu_eta_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/mu_eta_preFit.root mu_eta_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/mu_eta_preFit.root mu_eta_preFit_down.root
##ph
cp ${filepath}/${filepatharg1}_nominal/Histograms/ph_pt_preFit.root ph_pt_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/ph_pt_preFit.root ph_pt_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/ph_pt_preFit.root ph_pt_preFit_down.root
cp ${filepath}/${filepatharg1}_nominal/Histograms/ph_eta_preFit.root ph_eta_preFit_nominal.root
cp ${filepath}/${filepatharg1}_up/Histograms/ph_eta_preFit.root ph_eta_preFit_up.root
cp ${filepath}/${filepatharg1}_down/Histograms/ph_eta_preFit.root ph_eta_preFit_down.root


