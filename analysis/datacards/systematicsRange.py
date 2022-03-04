##import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd
import os
import json

with open('./ccMCsyst.json') as ccSyst_json: ccSyst = json.load(ccSyst_json)
with open('./bdtMCsyst.json') as bdtSyst_json: bdtSyst = json.load(bdtSyst_json)

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
mcProcs_bdt = ["signal", "rares"]
mcProcs_cc = ["signal_tch", "signal_tuh", "rares"]

uncertainties = [   "LepSF","PU","Trigger","jes",
                    "ctag_stat","ctag_EleIDSF","ctag_LHEScaleWeightmuF","ctag_LHEScaleWeightmuR",
                    "ctag_MuIDSF","ctag_PSWeightFSR","ctag_PSWeightISR","ctag_PUWeight",
                    "ctag_XSecDYJets","ctag_XSecST","ctag_XSecWJets","ctag_XSecttbar",
                    "ctag_bFrag","ctag_jer","ctag_jesTotal","ctag_ValuesSystOnly"#,
                    #"ctag_TotalUnc"
                    ]

bdtSRs = ["bin_"+str(x) for x in range(20)]
ccSRs = getCCColumns(ccSRDict, 21)

##BDT##
for y in years:
    for s in signals:
        if "tch" in s: altSig = "hct"
        else: altSig = "hut"
        for p in mcProcs_bdt:
            if "signal" in p:
                p += "_"
                p += s
            for u in uncertainties:
                values_up = []
                values_down = []
                for b in bdtSRs:
                    values_up.append(bdtSyst[str(y)][str(s)][str(p)][str(u)][str(b)]["up"])
                    values_down.append(bdtSyst[str(y)][str(s)][str(p)][str(u)][str(b)]["down"])
                print(y, s, p, u)
                values_up.sort()
                print("\t", values_up[int(0.16*len(values_up))-1])
                print("\t", values_up[len(values_up)-int(0.16*len(values_up))-1])
                values_down.sort()
                print("\t", values_down[int(0.16*len(values_down))-1])
                print("\t", values_down[len(values_down)-int(0.16*len(values_down))-1])


print("***************************************************")

# ##CC##
# for y in years:
#     for p in mcProcs_cc:
#         for u in uncertainties:
#             values_up = []
#             values_down = []
#             for b in ccSRs:
#                 values_up.append(ccSyst[str(y)][str(p)][str(u)][str(b)]["up"])
#                 values_down.append(ccSyst[str(y)][str(p)][str(u)][str(b)]["down"])
#             print(y, s, p, u)
#             values_up.sort()
#             print("\t", values_up[int(0.16*len(values_up))-1])
#             print("\t", values_up[len(values_up)-int(0.16*len(values_up))-1])
#             values_down.sort()
#             print("\t", values_down[int(0.16*len(values_down))-1])
#             print("\t", values_down[len(values_down)-int(0.16*len(values_down))-1])


