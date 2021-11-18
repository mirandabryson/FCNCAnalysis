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
signals = ["tch", "tuh"]
procs = ["signal","rares","fakes_mc","flips_mc"]
mcProcs = ["signal_tch", "signal_tuh", "rares"]
ddProcs = ["fakes_mc","flips_mc"]

systSources = ["LepSF","PU","Trigger","cferr1","cferr2","hf","hfstats1","hfstats2","lf","lfstats1","lfstats2"]
otherShitToComeBackTo = ["bTag","jes","pdfScale","renormScale"]

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
# bdtMCsyst = {}
# for y in years:
#     bdtMCsyst[str(y)] = {}
#     for s in signals:
#         bdtMCsyst[str(y)][s] = {}
#         if "tch" in s: altSig = "hct"
#         else: altSig = "hut"
#         for p in mcProcs:
#             bdtMCsyst[str(y)][s][p] ={}
#             bdtFileName = inputBDTHistos + "data_" + str(y) + "_hists.root"
#             if "fakes" in p:
#                 sf = getObjFromFile(bdtFileName, "h_sf_bdtScore_"+altSig+str(y)+"_data")
#                 mlsf = getObjFromFile(bdtFileName, "h_mlsf_bdtScore_"+altSig+str(y)+"_data")
#                 hist = sf.Clone()
#                 hist.Add(mlsf)
#             elif "flips" in p: hist = getObjFromFile(bdtFileName, "h_os_bdtScore_"+altSig+str(y)+"_data")
#             iterator = 1
#             for r in bdtSRs:
#                 bdtMCsyst[str(y)][s][p][r] = {}
#                 bdtMCsyst[str(y)][s][p][r]["yield"] = hist.GetBinContent(iterator)
#                 bdtMCsyst[str(y)][s][p][r]["error"] = hist.GetBinError(iterator)
#                 iterator += 1

# with open("./bdtMCsyst.json", "w") as f_out: json.dump(bdtMCsyst, f_out, indent=4)



##CC Systematics JSON##
ccMCsyst = {}
for y in years:
    ccMCsyst[str(y)] = {}
    for p in mcProcs:
        ccMCsyst[str(y)][p] ={}
        ccFileName = inputCCHistos + p + "_" + str(y) + "_hists.root"
        centralHist = getObjFromFile(ccFileName, "h_br_sr_"+p)
        for s in systSources:
            ccMCsyst[str(y)][p][s] ={}
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

with open("./ccMCsyst.json", "w") as f_out: json.dump(ccMCsyst, f_out, indent=4)

