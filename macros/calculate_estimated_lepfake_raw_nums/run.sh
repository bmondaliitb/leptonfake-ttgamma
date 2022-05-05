#root -l -q ~/work/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_el_pt_up")'
#root -l -q ~/work/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_el_pt_nominal")'
#root -l -q ~/work/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_el_pt_down")'
#
#root -l -q ~/work/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_mu_pt_up")'
#root -l -q ~/work/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_mu_pt_nominal")'
#root -l -q ~/work/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_mu_pt_down")'

echo ">>>>>>>>>>>>>>>>>>electron   pt:dPhi"
root -l -q /afs/cern.ch/work/b/bmondal/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_el_pt_up",1)'
echo "---------------------------------------------------------------------------------------------"
echo ">>>>>>>>>>>>>>>>>>electron   pt:mtw"
root -l -q /afs/cern.ch/work/b/bmondal/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_el_pt_nominal",1)'
echo "---------------------------------------------------------------------------------------------"
echo ">>>>>>>>>>>>>>>>>>electron   pt:eta"
root -l -q /afs/cern.ch/work/b/bmondal/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_el_pt_down",1)'
echo "---------------------------------------------------------------------------------------------"

echo ">>>>>>>>>>>>>>>>>>muon    pt:mtw"
root -l -q /afs/cern.ch/work/b/bmondal/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_mu_pt_up",1)'
echo "---------------------------------------------------------------------------------------------"
echo ">>>>>>>>>>>>>>>>>>muon    pt:eta"
root -l -q /afs/cern.ch/work/b/bmondal/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_mu_pt_nominal",1)'
echo "---------------------------------------------------------------------------------------------"
echo ">>>>>>>>>>>>>>>>>>muon    pt:dPhi"
root -l -q /afs/cern.ch/work/b/bmondal/Macros/getIntegralRoot.C'("histograms.data.AlgDefault.root", "h_mu_pt_down",1)'
echo "---------------------------------------------------------------------------------------------"
