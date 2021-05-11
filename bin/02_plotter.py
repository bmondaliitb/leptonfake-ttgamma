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


def merge(sample, stype,campaign, selection, channel):
    indirs = ["../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel]
    if "fR2" == campaign: indirs = ["../ohists/{}/mc16a/".format(stype)+selection+"_"+channel, "../ohists/{}/mc16d/".format(stype)+selection+"_"+channel, "../ohists/{}/mc16e/".format(stype)+selection+"_"+channel]
    if not sample == "0" and not sample == "1":
        MChadd = "hadd -f ../ohists/{}/{}/{}_{}/merged/{}.root ".format(stype,campaign, selection, channel, sample)
        for indir in indirs: MChadd += "{}/{}/*.root ".format(indir,sample)
        os.system("{} > ../logs_merger/{}.log 2>&1".format(MChadd,sample))
    elif not sample == "1":
        #debug_message(0, sample, sample)
        datahadd = "hadd -f ../ohists/{}/{}/{}_{}/merged/data.root ".format(stype,campaign, selection, channel)
        for indir in indirs:
            datahadd += "{}/{}/*.root ".format(indir,sample)
            #if "mc16a" in indir: datahadd += "{}/1/*.root ".format(indir)
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


def totalMCgen(lumi, key, stype,campaign, selection, channel):
    totalHistMC = None
    for sample in os.listdir("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/"):
        if "data" in sample or "MC" in sample: continue
        tfile = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/{}".format(sample))
        if(not tfile.Get("MCLumi")):
          debug_message(1, "totalMCgen:tfile", "../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/{}".format(sample))
          continue
        MCLumi = tfile.Get("MCLumi").GetBinContent(1)
        MCHist = tfile.Get(key)
        MCHist.Scale(lumi/MCLumi)
        if totalHistMC == None:
            totalHistMC = MCHist.Clone(key+"_totalMC")
            totalHistMC.SetDirectory(0)
            totalHistMC.Add(MCHist)
        else:
            totalHistMC.Add(MCHist)
    return totalHistMC


def fakeEff(merge, campaign, nworkers, selection, channel, stype):
    data = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/data.root")
    os.system("mkdir -p ../EfficiencyMaps/{}/{}/".format(stype, campaign)+selection+"_"+channel)
    os.system("mkdir -p ../kinDists/{}/{}/".format(stype,campaign)+selection+"_"+channel)
    lumi = 36207.66
    if(campaign == "mc16d"): lumi = 44307.4
    elif(campaign == "mc16e"): lumi = 58450.1
    elif(campaign == "fR2"): lumi += 44307.4+58450.1

    ROOT.gROOT.SetStyle("ATLAS")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasStyle.C")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasUtils.C")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasLabels.C")

    ROOT.SetAtlasStyle()
    ROOT.gStyle.SetPalette(ROOT.kCividis)
    ROOT.gStyle.SetPaintTextFormat(".2f")


    for key in data.GetListOfKeys():
        if "MCLumi" in key.GetName() or "Tight" in key.GetName(): continue
        tightName = key.GetName()+"_Tight"
        dataHist = data.Get(key.GetName())
        dataTightHist = data.Get(tightName)
        MCHist = totalMCgen(lumi,key.GetName(), stype, campaign,selection, channel)
        MCTightHist = totalMCgen(lumi,tightName, stype, campaign, selection, channel)
        if not "2D" in key.GetName():
            print("datayield: {}".format(dataHist.Integral()+dataHist.GetBinContent(dataHist.GetNbinsX()+1)))
            print("MCyield: {}".format(MCHist.Integral()+MCHist.GetBinContent(MCHist.GetNbinsX()+1)))
            print("datatightyield: {}".format(dataTightHist.Integral()+dataTightHist.GetBinContent(dataHist.GetNbinsX()+1)))
            print("MCtightyield: {}".format(MCTightHist.Integral()+MCTightHist.GetBinContent(MCHist.GetNbinsX()+1)))
            canv = ROOT.TCanvas("","",1600,1200)
            dataHist.SetMarkerColor(ROOT.kBlack)
            dataHist.SetLineColor(ROOT.kBlack)
            MCHist.SetMarkerColor(ROOT.kRed)
            MCHist.SetLineColor(ROOT.kRed)
            dataHist.SetXTitle(dataHist.GetTitle())
            dataHist.Draw("E1")
            MCHist.Draw("HIST,E1,SAME")
            canv.SetLogy()

            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}.pdf".format(stype,campaign,selection,channel,key.GetName()))
            del canv

            canv = ROOT.TCanvas("","",1600,1200)
            dataTightHist.SetMarkerColor(ROOT.kBlack)
            dataTightHist.SetLineColor(ROOT.kBlack)
            MCTightHist.SetMarkerColor(ROOT.kRed)
            MCTightHist.SetLineColor(ROOT.kRed)
            dataTightHist.SetXTitle(dataHist.GetTitle())
            dataTightHist.Draw("E1")
            MCTightHist.Draw("HIST,E1,SAME")
            canv.SetLogy()
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}.pdf".format(stype,campaign, selection,channel,key.GetName()+"_Tight"))
            del canv

            fakeHist = dataHist.Clone("lfake_"+key.GetName())
            fakeHist.Add(MCHist, -1)
            fakeTightHist = dataTightHist.Clone("lfake_"+key.GetName()+"_Tight")
            fakeTightHist.Add(MCTightHist, -1)
            fakeTightHist.Divide(fakeHist)
            canv = ROOT.TCanvas("","",1600,1200)
            fakeTightHist.SetXTitle(fakeTightHist.GetTitle())
            fakeTightHist.Draw("Hist,E1")
            canv.SetLogy()
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}_TightFakeEff.pdf".format(stype,campaign, selection,channel,key.GetName()))
            del canv
            realHistTight = MCTightHist.Clone("real_"+key.GetName()+"_Tight")
            realHistTight.Divide(MCHist)
            EffFile = ROOT.TFile("../EfficiencyMaps/{}/{}/{}_{}/{}.root".format(stype,campaign, selection,channel,key.GetName()), "RECREATE")
            realHistTight.Write()
            fakeTightHist.Write()

            EffFile.Write()
            EffFile.Close()
        else:
            fakeHist = dataHist.Clone("lfake_"+key.GetName())
            fakeHist.Add(MCHist, -1)
            fakeTightHist = dataTightHist.Clone("lfake_"+key.GetName()+"_Tight")
            fakeTightHist.Add(MCTightHist, -1)
            if channel == "el":
                fakeTightHist.Divide(fakeHist)
            else:
                xbinning = [27.,35.,45., 52.,60.]
                ybinning = [0.,7.,15.,25.]
                ft = ROOT.TH2F("lfake_"+key.GetName()+"_TightRebin", "", len(xbinning)-1, array('d', xbinning),len(ybinning)-1, array('d', ybinning))
                mt = ROOT.TH2F(key.GetName()+"_mtRebin", "", len(xbinning)-1, array('d', xbinning),len(ybinning)-1, array('d', ybinning))
                for x in range(fakeTightHist.GetNbinsX()):
                    for y in range(fakeTightHist.GetNbinsY()):
                        xybin = ft.FindBin(fakeTightHist.GetXaxis().GetBinCenter(x+1), fakeTightHist.GetYaxis().GetBinCenter(y+1))
                        ft.SetBinContent(xybin, ft.GetBinContent(xybin)+fakeTightHist.GetBinContent(x+1,y+1))
                        ft.SetBinError(xybin, np.sqrt(ft.GetBinError(xybin)**2+fakeTightHist.GetBinError(x+1,y+1)**2))

                        mt.SetBinContent(xybin, mt.GetBinContent(xybin)+fakeHist.GetBinContent(x+1,y+1))
                        mt.SetBinError(xybin, np.sqrt(mt.GetBinError(xybin)**2+fakeHist.GetBinError(x+1,y+1)**2))
                ft.Divide(mt)
                fakeTightHist.Divide(fakeHist)


            canv = ROOT.TCanvas("","",1600,1200)
            canv.SetTopMargin(0.15)
            canv.SetRightMargin(0.15)

            fakeTightHist.SetXTitle("#it{p}_{T}^{l} [GeV]")
            fakeTightHist.SetYTitle("#it{m}_{T}^{l+#nu} [GeV]")
            fakeTightHist.Draw("colz,text,error")
            ROOT.gStyle.SetTextSize(0.05)
            ROOT.ATLASLabel(0.15, 0.94, "Internal")
            ROOT.gStyle.SetTextSize(0.04)
            ROOT.myText(0.65, 0.86,ROOT.kBlack, "13 TeV, 140 fb^{-1}")
            efficiencyTag = "Fake muon efficiencies (data)"
            if channel == "el": efficiencyTag = "Fake electron efficiencies (data)"
            selectionTag = "1b70"
            if "0b70" in selection: selectionTag = "0b701b85"
            ROOT.myText(0.15, 0.90,ROOT.kBlack, selectionTag)
            ROOT.myText(0.15, 0.86,ROOT.kBlack, efficiencyTag)
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}_TightFakeEff.pdf".format(stype,campaign,selection,channel,key.GetName()))
            del canv

            realHistTight = MCTightHist.Clone("real_"+key.GetName()+"_Tight")
            realHistTight.Divide(MCHist)
            canv = ROOT.TCanvas("","",1600,1200)
            canv.SetTopMargin(0.15)
            canv.SetRightMargin(0.15)
            realHistTight.SetXTitle("#it{p}_{T}^{l} [GeV]")
            realHistTight.SetYTitle("#it{m}_{T}^{l+#nu} [GeV]")
            realHistTight.Draw("colz,text,error")
            ROOT.gStyle.SetTextSize(0.05)
            ROOT.ATLASLabel(0.15, 0.94, "Simulation Internal")
            ROOT.gStyle.SetTextSize(0.04)
            ROOT.myText(0.65, 0.87,ROOT.kBlack, "13 TeV, 140 fb^{-1}")
            efficiencyTag = "Real muon efficiencies (MC)"
            if channel == "el": efficiencyTag = "Real electron efficiencies (MC)"
            ROOT.myText(0.15, 0.87,ROOT.kBlack, efficiencyTag)
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}_TightRealEff.pdf".format(stype,campaign, selection,channel,key.GetName()))
            del canv
            EffFile = ROOT.TFile("../EfficiencyMaps/{}/{}/{}_{}/{}.root".format(stype,campaign, selection,channel,key.GetName()), "RECREATE")
            realHistTight.Write()
            fakeTightHist.Write()
            print("Buddha")

            EffFile.Write()
            EffFile.Close()

def realEff(merge, campaign, nworkers, selection, channel, stype):
    MC = ROOT.TFile("../ohists/{}/{}/".format(stype,campaign)+selection+"_"+channel+"/merged/410470.root")
    os.system("mkdir -p ../EfficiencyMaps/{}/{}/".format(stype, campaign)+selection+"_"+channel)
    os.system("mkdir -p ../kinDists/{}/{}/".format(stype,campaign)+selection+"_"+channel)
    lumi = 36207.66
    if(campaign == "mc16d"): lumi = 44307.4
    elif(campaign == "mc16e"): lumi = 58450.1
    elif(campaign == "fR2"): lumi += 44307.4+58450.1

    ROOT.gROOT.SetStyle("ATLAS")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasStyle.C")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasUtils.C")
    ROOT.gROOT.LoadMacro(os.environ["ATLAS_STYLE_PATH"]+"/AtlasLabels.C")

    ROOT.SetAtlasStyle()
    ROOT.gStyle.SetPalette(ROOT.kCividis)
    ROOT.gStyle.SetPaintTextFormat(".2f")

    for key in MC.GetListOfKeys():
        if "MCLumi" in key.GetName() or "Tight" in key.GetName(): continue
        tightName = key.GetName()+"_Tight"
        MCHist = totalMCgen(lumi,key.GetName(), stype, campaign,selection, channel)
        MCTightHist = totalMCgen(lumi,tightName, stype, campaign, selection, channel)
        if not "2D" in key.GetName():
            canv = ROOT.TCanvas("","",1600,1200)
            MCHist.SetMarkerColor(ROOT.kRed)
            MCHist.SetLineColor(ROOT.kRed)
            MCHist.SetXTitle(MCHist.GetTitle())
            MCHist.Draw("HIST,E1,SAME")
            canv.SetLogy()
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}.pdf".format(stype,campaign,selection,channel,key.GetName()))
            del canv

            canv = ROOT.TCanvas("","",1600,1200)
            MCTightHist.SetMarkerColor(ROOT.kRed)
            MCTightHist.SetLineColor(ROOT.kRed)
            MCTightHist.SetXTitle(MCTightHist.GetTitle())
            MCTightHist.Draw("HIST,E1,SAME")
            canv.SetLogy()
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}.pdf".format(stype,campaign, selection,channel,key.GetName()+"_Tight"))
            del canv

            realHistTight = MCTightHist.Clone("real_"+key.GetName()+"_Tight")
            realHistTight.Divide(MCHist)
            EffFile = ROOT.TFile("../EfficiencyMaps/{}/{}/{}_{}/{}.root".format(stype,campaign, selection,channel,key.GetName()), "RECREATE")
            realHistTight.Write()
            EffFile.Write()
            EffFile.Close()
        else:
            realHistTight = MCTightHist.Clone("real_"+key.GetName()+"_Tight")
            realHistTight.Divide(MCHist)
            canv = ROOT.TCanvas("","",1600,1200)
            realHistTight.SetXTitle("#it{p}_{T}^{l} [GeV]")
            realHistTight.SetYTitle("#it{m}_{T}^{l+#nu} [GeV]")
            realHistTight.Draw("colz,text,error")
            canv.SaveAs("../kinDists/{}/{}/{}_{}/{}_TightRealEff.pdf".format(stype, campaign, selection,channel,key.GetName()))
            del canv
            EffFile = ROOT.TFile("../EfficiencyMaps/{}/{}/{}_{}/{}.root".format(stype,campaign, selection,channel,key.GetName()), "RECREATE")
            realHistTight.Write()
            EffFile.Write()
            EffFile.Close()


@click.command()
@click.option("--merge", default="no",type=click.Choice(["yes", "no"]) ,help="Should the files be merged")
@click.option("--campaign", required=True, type=click.Choice(["mc16a","mc16d", "mc16e", "fR2"]), help="Specify the campaign and choose between mc16[a,d,e]")
@click.option("--nworkers", default=1, help="Specify the number of workers used for merging")
@click.option("--selection", required=True,type=click.Choice(["4jgt1b70", "1j1b70","1j1b701b85", "1j0b701b85","1j1b702b85"]), help="Specify the selection that you want to apply to retrieve the fake weights")
@click.option("--channel", required=True, type=click.Choice(["el","mu"]),  help="Selection electron or muon channel")
@click.option("--stype", required=True, type=click.Choice(["real","fake"]), help="Process real or fake Ntuples")


def main(merge, campaign, nworkers, selection, channel, stype):
    selection = "Efficiencies_Selection_"+selection
    if merge == "yes": merger(nworkers, stype, campaign, selection, channel)
    if stype == "fake": fakeEff(merge, campaign, nworkers, selection, channel, stype)
    else: realEff(merge, campaign, nworkers, selection, channel, stype)


if __name__ == "__main__":

    main()
