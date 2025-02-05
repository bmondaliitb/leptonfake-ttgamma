import sys
sys.path.append('/afs/cern.ch/work/b/bmondal/python_packages/tqdm')

import os, sys,ROOT
import click
import numpy as np
import multiprocessing as mp
#from tqdm import tqdm
from tqdm.auto import tqdm
from functools import partial
from array import array
import numpy as np

def debug_message(debug_level, function, debug_msg):
	if debug_level==0 : print("==INFO::{0}       {1}".format(function,debug_msg))
	if debug_level==1 : print("==WARNING::{0}       {1}".format(function,debug_msg))

def legend(key):
    if "met" in key: return "#it{E}_{T}^{miss} [GeV]"
    elif "mt" in key: return "#it{m}_{T}^{l+#nu} [GeV]"
    elif "leta" in key: return "#eta^{l}"
    elif "lpt" in key: return "#it{p}_{T}^{l} [GeV]"
    else: return "Undefined legend"

def merge(sample, stype,campaign, selection, channel):
    indirs = ["../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel]
    if "fR2" == campaign: indirs = ["../ohists/{}/mc16a/".format(stype)+selection+"_"+channel, "../ohists/{}/mc16d/".format(stype)+selection+"_"+channel, "../ohists/{}/mc16e/".format(stype)+selection+"_"+channel]

    if not sample == "0" and not sample == "1":
        MChadd = "hadd -f ../ohists/{}/{}/{}_{}/merged/{}.root ".format(stype,campaign, selection, channel, sample)
        for indir in indirs: MChadd += "{}/{}/*.root ".format(indir,sample)
        os.system("{} > ../logs_merger/{}.log 2>&1".format(MChadd,sample))
    elif not sample == "1":
        datahadd = "hadd -f ../ohists/{}/{}/{}_{}/merged/data.root ".format(stype,campaign, selection, channel)
        for indir in indirs:
            datahadd += "{}/{}/*.root ".format(indir,sample)
            if "mc16a" in indir: datahadd += "{}/1/*.root ".format(indir)
        os.system("{} > ../logs_merger/{}.log 2>&1".format(datahadd,sample))

def merger(nworkers, stype, campaign, selection, channel):

    indir = "../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel
    os.system("mkdir -p {}/merged".format(indir))
    if "fR2" == campaign: indir = "../ohists/{}/mc16d/".format(stype)+selection+"_"+channel
    os.system("mkdir -p ../logs_merger/")
    samples = []
    for sample in os.listdir(indir):
        if "merged" in sample: continue
        samples.append(sample)
    p = mp.Pool(nworkers)
    for _ in tqdm(p.imap_unordered(partial(merge,stype=stype, campaign=campaign, selection=selection, channel=channel), samples), total=len(samples)):
        pass
    p.close()
    p.join()


def plotting(campaign, selection, channel, stype):
    ROOT.gROOT.SetStyle("ATLAS")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasStyle.C")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasUtils.C")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasLabels.C")

    ROOT.SetAtlasStyle()
    sampleList = [363355,363356,363357,363358,363359, 363360, 363489, 364250,364253, 364254, 364255]+[410644,410645,410646,410647]+[410470]+[410658,410659]+[410155, 410156, 410157, 410218, 410219, 410220]+[x for x in range(364100,364142)]+[x for x in range(364156,364198)]

    color_lfake = ROOT.TColor(3./252., 252./252., 232./252.)
    color_diboson = ROOT.TColor(238.0/255,31.0/255,96.0/255)
    color_wjets =ROOT.TColor(0,95.0/255,134.0/255)
    color_zjets = ROOT.TColor(204.0/255, 102.0/255, 255.0/255)
    color_sgtop = ROOT.TColor(156.0/255,173.0/255,183.0/255)
    #color_zjetsgamma = ROOT.TColor(0,169.0/255,183.0/255)
    #color_wjetsgamma =ROOT.TColor(255.0/255,214.0/255,0)
    #color_ttgamma = ROOT.TColor(87.0/255,157.0/255,66.0/255)
    color_ttv = ROOT.TColor(87.0/255,157.0/255,66.0/255)
    color_ttbar =ROOT.TColor(1., 0, 0)
    color_tchan = ROOT.TColor(214.0/255,210.0/255,196.0/255)
    lumi = 36207.66
    if(campaign == "mc16d"): lumi = 44307.4
    elif(campaign == "mc16e"): lumi = 58450.1
    elif(campaign == "fR2"): lumi += 44307.4+58450.1
    data = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/data.root")
    for key in data.GetListOfKeys():
        if "2D" in key.GetName(): continue
        stack = ROOT.THStack()
        totalMCHist = None
        for mcID in sampleList:
        #for sample in os.listdir("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/"):
            sample = "{}.root".format(mcID)
            if "data" in sample or "MC" in sample: continue

            tfile = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/{}".format(sample))
            if(not tfile.Get("MCLumi")):
              debug_message(1, "plotting:tfile", "../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/{}".format(sample)+"   MCLumi not found")
              continue

            MCLumi = tfile.Get("MCLumi").GetBinContent(1)
            MCHist = tfile.Get(key.GetName())
            #if "999999" in sample:
            #  if "Tight" in key.GetName():
            #    print("Buddha MCHist: {}".format(key.GetName()[:-6]))
            #    MCHist = tfile.Get(key.GetName()[:-6])
            #    print("Buddha MCHist: {}".format(key.GetName()[:-6]))
            #else:
            #MCHist = tfile.Get(key.GetName())

            #if not "999999" in sample: MCHist.Scale(lumi/MCLumi)
            MCHist.Scale(lumi/MCLumi)
            color = None
            sample = sample.replace(".root", "")
            if "410470" in sample: color =  color_ttbar
            elif "410658" in sample or "410659" in sample: color =  color_tchan
            elif sample in ["410644", "410645", "410646", "410647"]: color =  color_sgtop
            elif sample in ["410155", "410156", "410157", "410218", "410219", "410220"]: color =  color_ttv
            #elif sample in ["999999"]: color =  color_lfake
            elif int(sample) in range(364156,364198): color =  color_wjets
            elif int(sample) in range(364100,364142): color =  color_zjets
            elif sample in ["363355","363356","363357","363358","363359", "363360", "363489", "364250","364253", "364254", "364255"]: color =  color_diboson
            MCHist.SetLineColor(color.GetNumber())
            MCHist.SetFillColor(color.GetNumber())
            MCHist.SetDirectory(0)

            if totalMCHist == None: totalMCHist = MCHist.Clone(MCHist.GetName()+"_totalMC")
            else: totalMCHist.Add(MCHist)
            totalMCHist.SetDirectory(0)
            stack.Add(MCHist)
        dataHist = data.Get(key.GetName())
        print(totalMCHist.Integral())
        canv = ROOT.TCanvas("","",1600,1200)
        pad1 = ROOT.TPad("pad_eff_1", "", 0., 0.26,1.,1.)
        pad2 = ROOT.TPad("pad_eff_2", "", 0., 0.0,1.,0.26)
        pad1.Draw()
        pad2.Draw()
        pad1.cd()
        pad1.SetBottomMargin(0.0)
        pad1.SetLeftMargin(0.15)
        pad1.SetRightMargin(0.05)
        dataHist.SetMarkerSize(2)
        dataHist.SetMinimum(1)
        dataHist.Draw("E1")
        stack.Draw("Hist,Same")
        dataHist.Draw("E1,SAME")
        ROOT.gStyle.SetTextSize(0.05)
        ROOT.ATLASLabel(0.60, 0.89, "Internal")
        ROOT.gStyle.SetTextSize(0.04)
        channeltag = "electron"
        if "mu" in channel: channeltag = "muon"
        qt = "loose "
        if "Tight" in key.GetName(): qt = "tight "
        rt = "1b77"
        if "1b85" in selection: rt = "0b701b85"
        ROOT.myText(0.60, 0.84,ROOT.kBlack, 0.025, "13 TeV, 139 fb^{-1}")
        ROOT.myText(0.60,0.79,ROOT.kBlack, 0.025, qt+channeltag+", "+rt)
        ROOT.myMarkerText(0.65, 0.74,  ROOT.kBlack,20, "data", 2)
        #ROOT.myBoxText(0.65,0.70 , 0.03, color_wjets.GetNumber(), color_wjets.GetNumber(), "#it{W}+jets")
        #ROOT.myBoxText(0.65,0.66 , 0.03, color_zjets.GetNumber(), color_zjets.GetNumber(), "#it{Z}+jets")
        #ROOT.myBoxText(0.65,0.62 , 0.03, color_tchan.GetNumber(), color_tchan.GetNumber(), "#it{t}#it{q}")
        #ROOT.myBoxText(0.80,0.70 , 0.03, color_ttbar.GetNumber(), color_ttbar.GetNumber(), "#it{t}#it{#bar{t}}")
        #ROOT.myBoxText(0.80,0.66 , 0.03, color_sgtop.GetNumber(), color_sgtop.GetNumber(), '#it{t}#it{W}+#it{t}#it{b}')
        ROOT.myBoxText(0.65,0.70 , 0.03, color_wjets.GetNumber(), "#it{W}+jets")
        ROOT.myBoxText(0.65,0.66 , 0.03, color_zjets.GetNumber(), "#it{Z}+jets")
        ROOT.myBoxText(0.65,0.62 , 0.03, color_tchan.GetNumber(), "#it{t}#it{q}")
        ROOT.myBoxText(0.80,0.70 , 0.03, color_ttbar.GetNumber(), "#it{t}#it{#bar{t}}")
        ROOT.myBoxText(0.80,0.66 , 0.03, color_sgtop.GetNumber(), '#it{t}#it{W}+#it{t}#it{b}')
        ROOT.myBoxText(0.80,0.62 , 0.03, color_diboson.GetNumber(), '#it{V}#it{V}')
        ROOT.myBoxText(0.80,0.58 , 0.03, color_ttv.GetNumber(), '#it{ttv}')
        #ROOT.myBoxText(0.80,0.54 , 0.03, color_lfake.GetNumber(), '#it{lfake}')
        pad1.RedrawAxis()
        pad2.cd()
        pad2.SetRightMargin(0.05)
        pad2.SetLeftMargin(0.15)
        pad2.SetTopMargin(0.0)
        pad2.SetBottomMargin(0.4)
        ratio = dataHist.Clone(dataHist.GetName()+"_ratio")
        ratio.Divide(totalMCHist)

        ratio.SetYTitle("#frac{data}{MC}")
        ratio.SetXTitle(legend(key.GetName()))
        ratio.SetOption("][")
        ratio.GetXaxis().SetLabelSize(0.13)
        ratio.GetYaxis().SetLabelSize(0.13)
        ratio.GetXaxis().SetTitleSize(0.13)
        ratio.GetYaxis().SetTitleSize(0.13)
        ratio.GetYaxis().SetNdivisions(505)
        ratio.GetXaxis().SetTitleOffset(0.9)
        ratio.GetYaxis().SetTitleOffset(0.45)
        ratio.GetYaxis().SetLabelOffset(0.01)
        ratio.GetYaxis().SetTickLength(0.047)
        ratio.GetXaxis().SetTickLength(0.08)
        ratio.SetMarkerColor(ROOT.kBlack)
        ratio.SetLineColor(ROOT.kBlack)
        ratio.SetMarkerStyle(20)
        ratio.SetMarkerSize(1.8)
        #ratio.GetYaxis().SetRangeUser(0.5, 2.49)
        ratio.GetYaxis().SetRangeUser(0.5, 1.6)
        ratio.Draw("E1")
        odir = "../kinPlots/{}_{}/".format(selection, channel)
        os.system("mkdir -p {}".format(odir))
        canv.SaveAs("{}/{}.pdf".format(odir,key.GetName()))
        pad1.cd()
        pad1.SetLogy()
        canv.SaveAs("{}/{}_log.pdf".format(odir, key.GetName()))
        del canv


def ProcYield(campaign, selection, channel, stype):

    diboson = [363355,363356,363357,363358,363359, 363360, 363489, 364250,364253, 364254, 364255]
    sgtop = [410644,410645,410646,410647]
    ttbar = [410470]
    tchan = [410658,410659]
    zjets = range(364100,364142)
    wjets = range(364156,364198)
    ttv = [410155, 410156, 410157, 410218, 410219, 410220]

    lumi = 36207.66
    if(campaign == "mc16d"): lumi = 44307.4
    elif(campaign == "mc16e"): lumi = 58450.1
    elif(campaign == "fR2"): lumi += 44307.4+58450.1
    tyield = 0.
    tyieldErr = 0.
    for sample in [diboson, sgtop, ttbar, tchan, zjets, wjets, ttv]:
        syield = 0.
        syieldErr = 0.
        for mcID in sample:
            sample = "{}.root".format(mcID)
            if "data" in sample or "MC" in sample: continue

            tfile = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/{}".format(sample))
            if(not tfile.Get("MCLumi")):
              debug_message(1, "ProcYield:tfile", "../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/{}".format(sample)+"   MCLumi not found")
              continue

            MCLumi = tfile.Get("MCLumi").GetBinContent(1)
            MCLumiUnc = tfile.Get("MCLumi").GetBinError(1)
            MCHist = tfile.Get("leta_kin")
            MCHist.Scale(lumi/MCLumi)
            syield += MCHist.Integral()
            thisUnc = 0.
            for nbin in range(MCHist.GetNbinsX()):
                thisUnc += MCHist.GetBinError(nbin+1)**2
            syieldErr += thisUnc
            tyield += MCHist.Integral()
            tyieldErr += thisUnc
        print("yield: {} +/- {}".format(syield, np.sqrt(syieldErr)))
    print("totalyield: {} +/- {}".format(tyield, np.sqrt(tyieldErr)))
    data = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/data.root")
    dataHist = data.Get("leta_kin")
    print("datayield: {} +/- {}".format(dataHist.Integral(), np.sqrt(dataHist.Integral())))






@click.command()
@click.option("--merge", default="no",type=click.Choice(["yes", "no"]) ,help="Should the files be merged")
@click.option("--campaign", required=True, type=click.Choice(["mc16a","mc16d", "mc16e", "fR2"]), help="Specify the campaign and choose between mc16[a,d,e]")
@click.option("--nworkers", default=1, help="Specify the number of workers used for merging")
@click.option("--selection", required=True,type=click.Choice(["4jgt1b77","4jgt1b70","1jgt1b77","1jgt1b70" , "4jgt1b85","4jgt1b70","1j1b70","1j1b701b85", "1j0b701b85","1j1b702b85"]), help="Specify the selection that you want to apply to retrieve the fake weights")
@click.option("--channel", required=True, type=click.Choice(["el","mu"]),  help="Selection electron or muon channel")
@click.option("--stype", required=True, type=click.Choice(["real","fake"]), help="Process real or fake Ntuples")
def main(merge, campaign, nworkers, selection, channel, stype):
    selection = "Efficiencies_Selection_"+selection
    if merge == "yes": merger(nworkers, stype, campaign, selection, channel)
    plotting(campaign, selection, channel, stype)
    ProcYield(campaign, selection, channel, stype)



if __name__ == "__main__":
    main()
