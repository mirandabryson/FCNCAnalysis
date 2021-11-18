##import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd
import os
import json

inputBDTHistos = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov16_bdtYields/"
# inputBDTHistos = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov16_bdtYields_jet25/"

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

years = [2016, 2017, 2018]
signals = ["tch", "tuh"]
procs = ["signal","rares","fakes_mc","flips_mc"]
mcProcs = ["signal", "rares"]
ddProcs = ["fakes_mc","flips_mc"]

bdtSRs = ["bin_"+str(x) for x in range(20)]

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

