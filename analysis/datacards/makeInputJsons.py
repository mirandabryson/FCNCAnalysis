##import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd
import os
import json

inputCCHistos = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov16_ccYields/"
inputBDTHistos = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov18_bdtYields/"
# inputBDTHistos = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov18_bdtYields_jet25/"

inputCCSyst = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov15_ccSystematics/"
inputBDTSyst = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov23_bdtSystematics/"
inputBDTBTagSyst = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov18_bdtBTagSyst/"
inputCCBTagSyst = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov18_ccBTagSyst/"

inputCCJESUp = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov23_ccJESUp/"
inputCCJESDown = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov23_ccJESDown/"
inputBDTJESUp = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov23_bdtJESUp/"
inputBDTJESDown = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov23_bdtJESDown/"

#function to get CC SR titles
def getCCColumns(ccSRDict, numSRs):
    columns = []
    for key in ccSRDict:
        colTitle = "l"+str(ccSRDict[key]["nleps"])
        colTitle += "_j"+str(ccSRDict[key]["njets"])
        colTitle += "_b"+str(ccSRDict[key]["nbtags"])
        columns.append(colTitle)
    return columns

#function to get histogram from root file
def getObjFromFile(fname, hname):
    f = ROOT.TFile(fname)
    assert not f.IsZombie()
    f.cd()
    htmp = f.Get(hname)
    if not htmp:  return htmp
    ROOT.gDirectory.cd('PyROOT:/')
    res = htmp.Clone()
    f.Close()
    return res

with open('./ccSRbins.json') as ccbins_json: ccSRDict = json.load(ccbins_json)

years = [2016, 2017, 2018]
# years = [2016]
signals = ["tch", "tuh"]
procs = ["signal","rares","fakes_mc","flips_mc"]
mcProcs = ["signal_tch", "signal_tuh", "rares"]
ddProcs = ["fakes_mc","flips_mc"]

# systSources = ["LepSF","PU","Trigger","cferr1","cferr2","hf","hfstats1","hfstats2","lf","lfstats1","lfstats2"]
systSources = ["LepSF","PU","Trigger"]
btagsystSources = ["cferr1","cferr2","hf","hfstats1","hfstats2","lf","lfstats1","lfstats2"]
otherSyst = ["jes"]#,"pdfScale","renormScale"]

bdtSRs = ["bin_"+str(x) for x in range(20)]
ccSRs = getCCColumns(ccSRDict, 21)

##BDT CR JSON##
bdtCRstats = {}
for y in years:
    bdtCRstats[str(y)] = {}
    for s in signals:
        bdtCRstats[str(y)][s] = {}
        if "tch" in s: altSig = "hct"
        else: altSig = "hut"
        for p in ddProcs:
            bdtCRstats[str(y)][s][p] ={}
            bdtFileName = inputBDTHistos + "data_" + str(y) + "_hists.root"
            if "fakes" in p:
                sf = getObjFromFile(bdtFileName, "h_sf_bdtScore_"+altSig+str(y)+"_data")
                mlsf = getObjFromFile(bdtFileName, "h_mlsf_bdtScore_"+altSig+str(y)+"_data")
                hist = sf.Clone()
                hist.Add(mlsf)
            elif "flips" in p: hist = getObjFromFile(bdtFileName, "h_os_bdtScore_"+altSig+str(y)+"_data")
            iterator = 1
            for r in bdtSRs:
                bdtCRstats[str(y)][s][p][r] = {}
                bdtCRstats[str(y)][s][p][r]["yield"] = hist.GetBinContent(iterator)
                bdtCRstats[str(y)][s][p][r]["error"] = hist.GetBinError(iterator)
                iterator += 1

with open("./bdtCRStats.json", "w") as f_out: json.dump(bdtCRstats, f_out, indent=4)



##CC CR JSON##
with open("./ccRates.json") as ccRates_json: ccRates = json.load(ccRates_json)
ccCRstats = {}
for y in years:
    ccCRstats[str(y)] = {}
    for p in ddProcs:
        ccCRstats[str(y)][p] ={}
        ccFileName = inputCCHistos + "data_" + str(y) + "_hists.root"
        if "fakes" in p:
            sf = getObjFromFile(ccFileName, "h_sf_fakecr_data")
            mlsf = getObjFromFile(ccFileName, "h_mlsf_fakecr_data")
            hist = sf.Clone()
            hist.Add(mlsf)
        elif "flips" in p: hist = getObjFromFile(ccFileName, "h_os_flipcr_data")
        iterator = 1
        for r in ccSRs:
            ccCRstats[str(y)][p][r] = {}
            ccCRstats[str(y)][p][r]["yield"] = hist.GetBinContent(iterator)
            ccCRstats[str(y)][p][r]["error"] = hist.GetBinError(iterator)
            ccCRstats[str(y)][p][r]["syst"] = ccRates[str(y)][p][r]["syst"]
            iterator += 1

with open("./ccCRStats.json", "w") as f_out: json.dump(ccCRstats, f_out, indent=4)



##BDT Systematics JSON##
bdtMCsyst = {}
for y in years:
    bdtMCsyst[str(y)] = {}
    for s in signals:
        bdtMCsyst[str(y)][s] = {}
        if "tch" in s: altSig = "hct"
        else: altSig = "hut"
        for p in mcProcs:
            # bdtMCsyst[str(y)][s][p] = {}
            # bdtFileName = inputBDTHistos + p + "_" + str(y) + "_hists.root"
            # centralHist = getObjFromFile(bdtFileName, "h_br_bdtScore_" + altSig + str(y) + "_" + p)
            # ##Trigger,Lepton,PU,BTagging
            # for t in systSources:
            #     bdtMCsyst[str(y)][s][p][t] = {}
            #     bdtSystFileName = inputBDTSyst + p + "_" + str(y) + "_hists.root"
            #     upHist = getObjFromFile(bdtSystFileName, "h_"+t+"_up_bdtScore_syst_"+ altSig + str(y) + "_" +p)
            #     downHist = getObjFromFile(bdtSystFileName, "h_"+t+"_down_bdtScore_syst_"+ altSig + str(y) + "_" +p)
            #     upHist.Divide(centralHist)
            #     downHist.Divide(centralHist)
            #     iterator = 1
            #     for r in bdtSRs:
            #         bdtMCsyst[str(y)][s][p][t][r] = {}
            #         bdtMCsyst[str(y)][s][p][t][r]["up"] = upHist.GetBinContent(iterator)
            #         bdtMCsyst[str(y)][s][p][t][r]["down"] = downHist.GetBinContent(iterator)
            #         iterator += 1
            ##BTAGGING
            bdtMCsyst[str(y)][s][p] ={}
            bdtFileName = inputBDTBTagSyst + p + "_" + str(y) + "_hists.root"
            centralHist = getObjFromFile(bdtFileName, "h_btag_central_bdtScore_syst_" + altSig + str(y) + "_" + p)
            for b in btagsystSources:
                bdtMCsyst[str(y)][s][p][b] ={}
                upHist = getObjFromFile(bdtFileName, "h_" + b + "_up_bdtScore_syst_" + altSig + str(y) + "_" + p)
                downHist = getObjFromFile(bdtFileName, "h_" + b + "_down_bdtScore_syst_" + altSig + str(y) + "_" + p)
                upHist.Divide(centralHist)
                downHist.Divide(centralHist)
                iterator = 1
                for r in bdtSRs:
                    bdtMCsyst[str(y)][s][p][b][r] = {}
                    bdtMCsyst[str(y)][s][p][b][r]["up"] = upHist.GetBinContent(iterator)
                    bdtMCsyst[str(y)][s][p][b][r]["down"] = downHist.GetBinContent(iterator)
                    iterator += 1
            ##JES
            bdtFileName = inputBDTHistos + p + "_" + str(y) + "_hists.root"
            centralHist = getObjFromFile(bdtFileName, "h_br_bdtScore_" + altSig + str(y) + "_" + p)
            bdtFileNameUp = inputBDTJESUp + p + "_" + str(y) + "_hists.root"
            upHist = getObjFromFile(bdtFileNameUp, "h_br_bdtScore_" + altSig + str(y) + "_" + p)
            upHist.Divide(centralHist)
            bdtFileNameDown = inputBDTJESDown + p + "_" + str(y) + "_hists.root"
            downHist = getObjFromFile(bdtFileNameDown, "h_br_bdtScore_" + altSig + str(y) + "_" + p)
            downHist.Divide(centralHist)
            bdtMCsyst[str(y)][s][p]["jes"] = {}
            iterator = 1
            for r in bdtSRs:
                bdtMCsyst[str(y)][s][p]["jes"][r] = {}
                bdtMCsyst[str(y)][s][p]["jes"][r]["up"] = upHist.GetBinContent(iterator)
                bdtMCsyst[str(y)][s][p]["jes"][r]["down"] = downHist.GetBinContent(iterator)
                iterator += 1

with open("./bdtMCsyst.json", "w") as f_out: json.dump(bdtMCsyst, f_out, indent=4)



##CC Systematics JSON##
ccMCsyst = {}
for y in years:
    ccMCsyst[str(y)] = {}
    for p in mcProcs:
        ccMCsyst[str(y)][p] ={}
        ccFileName = inputCCHistos + p + "_" + str(y) + "_hists.root"
        centralHist = getObjFromFile(ccFileName, "h_br_sr_"+p)
        ##Trigger,Lepton,PU
        for s in systSources:
            ccMCsyst[str(y)][p][s] = {}
            ccSystFileName = inputCCSyst + p + "_" + str(y) + "_hists.root"
            upHist = getObjFromFile(ccSystFileName, "h_"+s+"_up_sr_syst_"+p)
            downHist = getObjFromFile(ccSystFileName, "h_"+s+"_down_sr_syst_"+p)
            upHist.Divide(centralHist)
            downHist.Divide(centralHist)
            iterator = 1
            for r in ccSRs:
                ccMCsyst[str(y)][p][s][r] = {}
                ccMCsyst[str(y)][p][s][r]["up"] = upHist.GetBinContent(iterator)
                ccMCsyst[str(y)][p][s][r]["down"] = downHist.GetBinContent(iterator)
                iterator += 1
        ##BTagging
        # ccMCsyst[str(y)][p]["bTag"] = {}
        ccSystFileName = inputCCBTagSyst + p + "_" + str(y) + "_hists.root"
        centralHist = getObjFromFile(ccSystFileName, "h_btag_central_sr_syst_"+p)        
        for b in btagsystSources:
            ccMCsyst[str(y)][p][b] ={}
            upHist = getObjFromFile(ccSystFileName, "h_" + b + "_up_sr_syst_" + p)
            downHist = getObjFromFile(ccSystFileName, "h_" + b + "_down_sr_syst_" + p)
            upHist.Divide(centralHist)
            downHist.Divide(centralHist)
            iterator = 1
            for r in ccSRs:
                ccMCsyst[str(y)][p][b][r] = {}
                ccMCsyst[str(y)][p][b][r]["up"] = upHist.GetBinContent(iterator)
                ccMCsyst[str(y)][p][b][r]["down"] = downHist.GetBinContent(iterator)
                iterator += 1
        ##JES
        ccFileName = inputCCHistos + p + "_" + str(y) + "_hists.root"
        centralHist = getObjFromFile(ccFileName, "h_br_sr_" + p)
        ccFileNameUp = inputCCJESUp + p + "_" + str(y) + "_hists.root"
        upHist = getObjFromFile(ccFileNameUp, "h_br_sr_syst_" + p)
        upHist.Divide(centralHist)
        ccFileNameDown = inputCCJESDown + p + "_" + str(y) + "_hists.root"
        downHist = getObjFromFile(ccFileNameDown, "h_br_sr_syst_" + p)
        downHist.Divide(centralHist)
        ccMCsyst[str(y)][p]["jes"] = {}
        iterator = 1
        for r in ccSRs:
            ccMCsyst[str(y)][p]["jes"][r] = {}
            ccMCsyst[str(y)][p]["jes"][r]["up"] = upHist.GetBinContent(iterator)
            ccMCsyst[str(y)][p]["jes"][r]["down"] = downHist.GetBinContent(iterator)
            iterator += 1

with open("./ccMCsyst.json", "w") as f_out: json.dump(ccMCsyst, f_out, indent=4)

