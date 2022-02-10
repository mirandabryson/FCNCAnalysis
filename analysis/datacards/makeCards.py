##import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd
import os
import json


## HARDCODED PATHS TO INPUT HISTOS ##
inFileCC    = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov16_ccYields/"
# inFileBDT   = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov18_bdtYields/"
# inFileBDT   = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/dec2_bdtYields/"
inFileBDT   = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/jan18_ctagBDT_normedCTagging/"
# inFileCC    = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov16_ccYields/"
# inFileBDT   = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/dec16_ctagBDTYields/"
# inFileBDT   = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/dec13_tthYieldsBDT/"

##define functions
#function to get multiplicities for a given cc bin
def getCCSRBin(binIdx, hist, ccSRDict):
    yld = hist.GetBinContent(binIdx)
    err = hist.GetBinError(binIdx)
    nl = ccSRDict[str(binIdx)]["nleps"]
    nj = ccSRDict[str(binIdx)]["njets"]
    nb = ccSRDict[str(binIdx)]["nbtags"]
    srName = "l"+str(nl)+"_j"+str(nj)+"_b"+str(nb)
    return {"nleps":nl,
            "njets":nj,
            "nbtags":nb,
            "yield":yld,
            "error":err,
            "name":srName}

#function to make CC column titles
def getCCColumns(ccSRDict, numSRs):
    columns = []
    for key in ccSRDict:
        colTitle = "l"+str(ccSRDict[key]["nleps"])
        colTitle += "_j"+str(ccSRDict[key]["njets"])
        colTitle += "_b"+str(ccSRDict[key]["nbtags"])
        columns.append(colTitle)
    return columns

#function to make the SR stat row titles
def getSRStatRows(processes, numSRs):
    titles = []
    for p in processes:
        for i in range(numSRs):
            rowTitle = p[:3]
            rowTitle += "_stat_"
            rowTitle += str(i)
            while len(rowTitle) < 17: rowTitle += " "
            rowTitle += "lnN"
            titles.append(rowTitle)
    return titles

#function to make the CC CR stat and dd rate Syst row titles
def getCCCRStatRows(year, processes, SRs, CRDict):
    titles = []
    for p in processes:
        for i in range(len(SRs)): 
            if "flips" in p and CRDict[str(year)][p][SRs[i]]["yield"]==0: continue
            rowTitle = p[:2]
            rowTitle += "_st"
            rowTitle += str(i)
            rowTitle += "_"+str(y)[-2:]+" "
            rowTitle2 = str(int(CRDict[str(year)][p][SRs[i]]["yield"]))
            while len(rowTitle+rowTitle2) < 16: rowTitle += " "
            rowTitle += "gmN "
            rowTitle += rowTitle2
            titles.append(rowTitle)
        rowTitle = p[:4]
        rowTitle += "RateSyst_"
        rowTitle += str(y)[-2:]
        while len(rowTitle) < 17: rowTitle += " "
        rowTitle += "lnN"
        titles.append(rowTitle)
    return titles

#function to make the bdt CR stat and dd rate Syst row titles
def getBDTCRStatRows(year, processes, SRs, CRDict, signal):
    titles = []
    for p in processes:
        for i in range(len(SRs)): 
            rowTitle = p[:2]
            rowTitle += "_st"
            rowTitle += str(i)
            rowTitle += "_"+str(y)[-2:]+" "
            rowTitle2 = str(int(CRDict[str(year)][signal][p][SRs[i]]["yield"]))
            while len(rowTitle+rowTitle2) < 16: rowTitle += " "
            rowTitle += "gmN "
            rowTitle += rowTitle2
            titles.append(rowTitle)
        rowTitle = p[:4]
        rowTitle += "RateSyst_"
        rowTitle += str(y)[-2:]
        while len(rowTitle) < 17: rowTitle += " "
        rowTitle += "lnN"
        titles.append(rowTitle)
    return titles

#function to make the Syst row titles
def getSystRows(year, correlated, uncorrelated):
    titles = []
    for c in correlated:
        rowTitle = c
        if "ctag_" in c: rowTitle = c[5:]
        if "LHEScaleWeight" in c: rowTitle = rowTitle[8:]
        if "ValuesSystOnly" in c: rowTitle = rowTitle[6:]
        while len(rowTitle)<17: rowTitle+=" "
        rowTitle += "lnN"
        titles.append(rowTitle)
    for u in uncorrelated:
        rowTitle = u
        if "ctag_" in u: rowTitle = u[5:]
        if "LHEScaleWeight" in u: rowTitle = rowTitle[8:]
        if "ValuesSystOnly" in u: rowTitle = rowTitle[6:]
        rowTitle += "_" + str(year)[-2:]
        while len(rowTitle)<17: rowTitle+=" "
        rowTitle += "lnN"
        titles.append(rowTitle)
    return titles

#function to make the norm row titles
def getNormRows(year, processes):
    titles = []
    for p in processes:
        rowTitle = p[:3]
        rowTitle += "_norm"
        rowTitle += str(year)[-2:]
        while len(rowTitle)<17: rowTitle+=" "
        rowTitle += "lnN"
        titles.append(rowTitle)
    return titles

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

#function to write output text file
def writeToTxt(df, filename, SRlist, processes, observations, yields):
    outFile = open(filename, "w+")

    outFile.write("imax "+str(len(SRlist))+ " number of channels\n")
    outFile.write("jmax "+str(len(processes)-1)+ " number of backgrounds\n")
    outFile.write("kmax "+str(len(df.index))+ " number of nuisance parameters\n")
    outFile.write("shapes * * FAKE\n\n")

    line = "bin"
    while len(line)<20: line+=" "
    line += "\t"
    for reg in SRlist:
        while len(reg)<20: reg+=" "
        line += reg
        line += "\t"
    outFile.write(line+"\n")

    line = "observation"
    while len(line)<20: line+=" "
    line += "\t"
    for reg in SRlist:
        obs = observations[reg]
        obs = str(int(obs))
        while len(obs)<20: obs+=" "
        line += obs
        line += "\t"
    outFile.write(line+"\n\n")

    line = "bin"
    while len(line)<20: line+=" "
    line += "\t"
    for reg in SRlist:
        while len(reg)<20: reg+=" "
        reg += "\t"
        line += reg*len(processes)
    outFile.write(line+"\n")

    line = "process"
    while len(line)<20: line+=" "
    line += "\t"
    subline = ""
    for p in processes:
        while len(p)<20: p+=" "
        subline += p
        subline += "\t"
    line += subline*len(SRlist)
    outFile.write(line+"\n")

    line = "process"
    while len(line)<20: line+=" "
    line += "\t"
    subline = ""
    for i in range(len(processes)):
        i = str(i)
        while len(i)<20: i+=" "
        subline += i
        subline += "\t"
    line += subline*len(SRlist)
    outFile.write(line+"\n")

    line = "rate"
    while len(line)<20: line+=" "
    line += "\t"
    for reg in SRlist:
        for p in processes:
            yld = str(round(yields[reg][p], 6))
            while len(yld)<20: yld+=" "
            line += yld
            line += "\t"
    outFile.write(line+"\n")

    filler = "-"
    while len(filler)<20: filler+=" "
    df = df.fillna(filler)
    outFile.write(df.to_csv(sep="\t",index=True,header=False))

    outFile.close()

##load useful jsons
with open('./ccSRbins.json') as ccbins_json: ccSRDict = json.load(ccbins_json)
with open('./ccCRStats.json') as ccCR_json: ccCRDict = json.load(ccCR_json)
with open('./bdtCRStats.json') as bdtCR_json: bdtCRDict = json.load(bdtCR_json)
with open('./ccMCsyst.json') as ccSyst_json: ccSystDict = json.load(ccSyst_json)
with open('./bdtMCsyst.json') as bdtSyst_json: bdtSystDict = json.load(bdtSyst_json)

##lists to loop
numCCSRs = 21
numBDTSRs = 20
years = [2016,2017,2018]
# years = [2016]
signalNorm = 0.01
signals = ["tch","tuh"]
procs   = ["signal","rares","fakes_mc","flips_mc"]
mcProcs = ["signal","rares"]
ddProcs = ["fakes_mc","flips_mc"]

uncorrSyst = ["jes","Trigger","LepSF","lfstats1","lfstats2","hfstats1","hfstats2"]
corrSyst = ["rarTh","sigTh","rarScShp","sigScShp","pdfShp","PU","lf","hf","cferr1","cferr2"]

# bdtSystCorr = ["rarTh","sigTh","rarScShp","sigScShp","pdfShp","PU","lf","hf","cferr1","cferr2"]
# bdtSystUncorr = ["jes","Trigger","LepSF","lfstats1","lfstats2","hfstats1","hfstats2"]

bdtSystCorr = [ "rarTh","sigTh","rarScShp","sigScShp","pdfShp","PU",
                "ctag_LHEScaleWeightmuF",
                "ctag_LHEScaleWeightmuR",
                "ctag_PSWeightFSR",
                "ctag_PSWeightISR",
                "ctag_PUWeight",
                "ctag_XSecDYJets",
                "ctag_XSecST",
                "ctag_XSecWJets",
                "ctag_XSecttbar",
                "ctag_bFrag",
                ]
bdtSystUncorr = [   "jes",
                    "Trigger",
                    "LepSF",
                    "ctag_stat",
                    "ctag_EleIDSF",
                    "ctag_MuIDSF",
                    "ctag_jer",
                    "ctag_jesTotal",
                    #"ctag_ValuesSystOnly"
                    ]

# corrSyst = ["rarTh","sigTh","rarScShp","sigScShp","pdfShp","PU"]
# uncorrSyst = ["jes","Trigger","LepSF","hfstats1","hfstats2"]

# bdtSystCorr = ["rarTh","sigTh","rarScShp","sigScShp","pdfShp","PU"]
# bdtSystUncorr = ["jes","Trigger","LepSF","hfstats1","hfstats2"]

## main loop
for y in years:
    for s in signals:
        if "tch" in s: altSig = "hct"
        if "tuh" in s: altSig = "hut"

        ## CUT AND COUNT COLUMNS, ROWS, AND DATAFRAME ##
        ccSRs = getCCColumns(ccSRDict, numCCSRs)
        ccDFCols = [b+"_"+p[:3] for b in ccSRs for p in procs]

        ccRows = []
        ccRows += getSRStatRows(mcProcs, numCCSRs)
        ccRows += getCCCRStatRows(y, ddProcs, ccSRs, ccCRDict)
        ccRows += getSystRows(y, corrSyst, uncorrSyst)
        ccRows += getNormRows(y, procs)

        cc_df = pd.DataFrame(columns = ccDFCols, index = ccRows)
        ccObs = {x:0 for x in ccSRs}
        ccYld = {}
        for a in ccSRs: 
            ccYld[a] = {}
            for b in procs: 
                ccYld[a][b] = 0

        ## BDT COLUMNS, ROWS, AND DATAFRAME ##
        bdtSRs = ["bin_"+str(x) for x in range(20)]
        bdtDFCols = [b+"_"+p[:3] for b in bdtSRs for p in procs]

        bdtRows = []
        # bdtRows += getSRStatRows(procs, numBDTSRs)
        bdtRows += getSRStatRows(mcProcs, numBDTSRs)
        bdtRows += getBDTCRStatRows(y, ddProcs, bdtSRs, bdtCRDict, s)
        # bdtRows += getSystRows(y, corrSyst, uncorrSyst)
        bdtRows += getSystRows(y, bdtSystCorr, bdtSystUncorr)
        bdtRows += getNormRows(y, ddProcs)

        bdt_df = pd.DataFrame(columns = bdtDFCols, index = bdtRows)
        bdtObs = {x:0 for x in bdtSRs}
        bdtYld = {}
        for a in bdtSRs: 
            bdtYld[a] = {}
            for b in procs: 
                bdtYld[a][b] = 0


        ## FILL MC ESTIMATES ##
        # for p in procs:
        for p in mcProcs:
            if "signal" in p:
                ccFileName = inFileCC + p + "_" + s + "_" + str(y) + "_hists.root"
                ccHist = getObjFromFile(ccFileName, "h_br_sr_signal_"+s)

                bdtFileName = inFileBDT + p + "_" + s + "_" + str(y) + "_hists.root"
                bdtHist = getObjFromFile(bdtFileName, "h_br_bdtScore_"+altSig+str(y)+"_"+ p + "_" + s)
            else:
                ccFileName = inFileCC + p + "_" + str(y) + "_hists.root"
                ccHist = getObjFromFile(ccFileName, "h_br_sr_"+p)

                bdtFileName = inFileBDT + p + "_" + str(y) + "_hists.root"
                bdtHist = getObjFromFile(bdtFileName, "h_br_bdtScore_"+altSig+str(y)+"_"+ p)

            ##LOOP TO FILL CUT AND COUNT##
            for i in range(1, numCCSRs+1):
                binDict = getCCSRBin(i, ccHist, ccSRDict)
                if "signal" in p: ccYld[binDict["name"]][p] = signalNorm*binDict["yield"]
                else:
                    ccYld[binDict["name"]][p] = binDict["yield"]
                    ccObs[binDict["name"]] += binDict["yield"]
                colTitle = binDict["name"] + "_" + p[:3]
                rowTitle = p[:3] + "_stat_" + str(i-1)
                while len(rowTitle)<17: rowTitle += " "
                rowTitle += "lnN"
                if binDict["yield"] == 0: fill = 2
                else: fill = 1+round(binDict["error"]/binDict["yield"], 6)
                fill = str(fill)
                while len(fill) <20: fill += " "
                cc_df[colTitle][rowTitle] = fill

                # if "signal" in p: pname = p + "_" + s
                # else: pname = p
                # for c in corrSyst:
                #     if (("ScShp" in c) and p[:3] not in c): continue
                #     if (("Th" in c) and p[:3] not in c): continue
                #     rowTitle = c
                #     while len(rowTitle)<17: rowTitle += " "
                #     rowTitle += "lnN"
                #     fill = str(round(ccSystDict[str(y)][pname][c][colTitle[:-4]]["down"],6))
                #     fill += "/"
                #     fill += str(round(ccSystDict[str(y)][pname][c][colTitle[:-4]]["up"],6))
                #     while len(fill)<20: fill += " "
                #     cc_df[colTitle][rowTitle] = fill
                # for u in uncorrSyst:
                #     rowTitle = u
                #     rowTitle += "_" + str(y)[-2:]
                #     while len(rowTitle)<17: rowTitle += " "
                #     rowTitle += "lnN"
                #     fill = str(round(ccSystDict[str(y)][pname][u][colTitle[:-4]]["down"],6))
                #     fill += "/"
                #     fill += str(round(ccSystDict[str(y)][pname][u][colTitle[:-4]]["up"],6))
                #     while len(fill)<20: fill += " "
                #     cc_df[colTitle][rowTitle] = fill
                rowTitle = p[:3] + "_norm" + str(y)[-2:]
                while len(rowTitle)<17: rowTitle+=" "
                rowTitle += "lnN"
                if "signal" in p: fill = "0.8/1.2"
                else: fill = "0.7/1.3"
                while len(fill)<20: fill += " "
                cc_df[colTitle][rowTitle] = fill

            ##LOOP TO FILL BDT##
            for i in range(1, numBDTSRs+1):
                yld = bdtHist.GetBinContent(i)
                err = bdtHist.GetBinError(i)
                if "signal" in p: bdtYld["bin_"+str(i-1)][p] = signalNorm*yld
                else:
                    bdtYld["bin_"+str(i-1)][p] = yld
                    bdtObs["bin_"+str(i-1)] += yld
                colTitle = "bin_"+str(i-1) + "_" + p[:3]
                rowTitle = p[:3] + "_stat_" + str(i-1)
                while len(rowTitle)<17: rowTitle += " "
                rowTitle += "lnN"
                if yld == 0: fill = 2
                else: fill = 1+round(err/yld, 6)
                fill = str(fill)
                while len(fill) <20: fill += " "
                bdt_df[colTitle][rowTitle] = fill
                # rowTitle = p[:3] + "_norm" + str(y)[-2:]
                # while len(rowTitle)<17: rowTitle+=" "
                # rowTitle += "lnN"
                # if "signal" in p: fill = "0.8/1.2"
                # else: fill = "0.7/1.3"
                # # elif "rares" in p: fill = "0.7/1.3"
                # # else: fill = "-"
                # while len(fill)<20: fill += " "
                # bdt_df[colTitle][rowTitle] = fill

                if "signal" in p: pname = p + "_" + s
                else: pname = p
                if ("signal" in pname) or ("rare" in pname):
                    for c in bdtSystCorr:
                        if (("ScShp" in c) and p[:3] not in c): continue
                        if (("Th" in c) and p[:3] not in c): continue
                        rowTitle = c
                        if "ctag_" in c: rowTitle = c[5:]
                        if "LHEScaleWeight" in c: rowTitle = rowTitle[8:]
                        if "ValuesSystOnly" in c: rowTitle = rowTitle[6:]
                        while len(rowTitle)<17: rowTitle += " "
                        rowTitle += "lnN"
                        fill = str(round(bdtSystDict[str(y)][s][pname][c][colTitle[:-4]]["down"],6))
                        fill += "/"
                        fill += str(round(bdtSystDict[str(y)][s][pname][c][colTitle[:-4]]["up"],6))
                        if (("bFrag" in c) and (y==2018)): fill = "-"
                        while len(fill)<20: fill += " "
                        bdt_df[colTitle][rowTitle] = fill
                    for u in bdtSystUncorr:
                        rowTitle = u
                        if "ctag_" in u: rowTitle = u[5:]
                        if "LHEScaleWeight" in u: rowTitle = rowTitle[8:]
                        if "ValuesSystOnly" in u: rowTitle = rowTitle[6:]
                        rowTitle += "_" + str(y)[-2:]
                        while len(rowTitle)<17: rowTitle += " "
                        rowTitle += "lnN"
                        fill = str(round(bdtSystDict[str(y)][s][pname][u][colTitle[:-4]]["down"],6))
                        fill += "/"
                        fill += str(round(bdtSystDict[str(y)][s][pname][u][colTitle[:-4]]["up"],6))
                        if (("bFrag" in u) and (y==2018)): fill = "-"
                        while len(fill)<20: fill += " "
                        bdt_df[colTitle][rowTitle] = fill


        ## FILL DATA DRIVEN ESTIMATES ##
        for p in ddProcs:
            ccFileName = inFileCC + "data_" + str(y) + "_hists.root" 
            bdtFileName = inFileBDT + "data_" + str(y) + "_hists.root" 
            
            if "fakes" in p: 
                raresFilecc = inFileCC + "rares_" + str(y) + "_hists.root"
                raresFilebdt = inFileBDT + "rares_" + str(y) + "_hists.root"

                sfHist = getObjFromFile(ccFileName, "h_sfest_fakecr_data")
                mlsfHist = getObjFromFile(ccFileName, "h_mlsfest_fakecr_data")
                dfHist = getObjFromFile(ccFileName, "h_dfest_fakecr_data")
                mldfHist = getObjFromFile(ccFileName, "h_mldfest_fakecr_data")
                sfppHist = getObjFromFile(raresFilecc, "h_sfppest_fakecr_rares")
                mlsfpppHist = getObjFromFile(raresFilecc, "h_mlsfpppest_fakecr_rares")

                ccHist = sfHist.Clone()
                ccHist.Add(mlsfHist)
                ccHist.Add(dfHist, -2)
                ccHist.Add(mldfHist, -2)
                ccHist.Add(sfppHist, -1)
                ccHist.Add(mlsfpppHist, -1)

                sfHist = getObjFromFile(bdtFileName, "h_sfest_bdtScore_"+altSig+str(y)+"_data")
                mlsfHist = getObjFromFile(bdtFileName, "h_mlsfest_bdtScore_"+altSig+str(y)+"_data")
                dfHist = getObjFromFile(bdtFileName, "h_dfest_bdtScore_"+altSig+str(y)+"_data")
                mldfHist = getObjFromFile(bdtFileName, "h_mldfest_bdtScore_"+altSig+str(y)+"_data")
                sfppHist = getObjFromFile(raresFilebdt, "h_sfppest_bdtScore_"+altSig+str(y)+"_rares")
                mlsfpppHist = getObjFromFile(raresFilebdt, "h_mlsfpppest_bdtScore_"+altSig+str(y)+"_rares")

                bdtHist = sfHist.Clone()
                bdtHist.Add(mlsfHist)
                bdtHist.Add(dfHist, -2)
                bdtHist.Add(mldfHist, -2)
                bdtHist.Add(sfppHist, -1)
                bdtHist.Add(mlsfpppHist, -1)
            else:
                ccHist = getObjFromFile(ccFileName, "h_osest_flipcr_data")
                bdtHist = getObjFromFile(bdtFileName, "h_osest_bdtScore_"+altSig+str(y)+"_data")

            ##LOOP TO FILL CC##
            for i in range(1, numCCSRs+1):
                binDict = getCCSRBin(i, ccHist, ccSRDict)

                ccYld[binDict["name"]][p] = binDict["yield"]
                if "signal" not in p: ccObs[binDict["name"]] += binDict["yield"]

                if "flip" in p and ccCRDict[str(y)][p][binDict["name"]]["yield"]==0: continue
                colTitle = binDict["name"] + "_" + p[:3]
                rowTitle = p[:2] + "_st" + str(i-1) + "_" + str(y)[-2:] + " "
                rowTitle2 = str(int(ccCRDict[str(y)][p][binDict["name"]]["yield"]))
                while len(rowTitle+rowTitle2)<16: rowTitle += " "
                rowTitle += "gmN "
                rowTitle += rowTitle2
                fill = round(binDict["yield"]/ccCRDict[str(y)][p][binDict["name"]]["yield"], 6)
                fill = str(fill)
                while len(fill)<20: fill += " "
                cc_df[colTitle][rowTitle] = fill
                rowTitle = p[:4] + "RateSyst_" + str(y)[-2:]
                while len(rowTitle)<17: rowTitle += " "
                rowTitle += "lnN"
                fill = round(1+ (ccCRDict[str(y)][p][binDict["name"]]["syst"]/100), 6)
                fill = str(fill)
                while len(fill)<20: fill += " "
                cc_df[colTitle][rowTitle] = fill
                rowTitle = p[:3] + "_norm" + str(y)[-2:]
                while len(rowTitle)<17: rowTitle+=" "
                rowTitle += "lnN"
                if "fakes" in p: fill = "0.6/1.4"
                else: fill = "0.7/1.3"
                while len(fill)<20: fill += " "
                cc_df[colTitle][rowTitle] = fill

            ##LOOP TO FILL BDT##
            for i in range(1, numBDTSRs+1):
                yld = bdtHist.GetBinContent(i)
                err = bdtHist.GetBinError(i)

                bdtYld["bin_"+str(i-1)][p] = yld
                if "signal" not in p: bdtObs["bin_"+str(i-1)] += yld

                colTitle = "bin_"+str(i-1) + "_" + p[:3]
                rowTitle = p[:2] + "_st" + str(i-1) + "_" + str(y)[-2:] + " "
                rowTitle2 = str(int(bdtCRDict[str(y)][s][p]["bin_"+str(i-1)]["yield"]))
                while len(rowTitle+rowTitle2)<16: rowTitle += " "
                rowTitle += "gmN "
                rowTitle += rowTitle2
                fill = round(yld/bdtCRDict[str(y)][s][p]["bin_"+str(i-1)]["yield"], 6)
                fill = str(fill)
                while len(fill)<20: fill += " "
                bdt_df[colTitle][rowTitle] = fill
                rowTitle = p[:4] + "RateSyst_" + str(y)[-2:]
                while len(rowTitle)<17: rowTitle += " "
                rowTitle += "lnN"
                fill = round(1+ (bdtCRDict[str(y)][s][p]["bin_"+str(i-1)]["syst"]/100), 6)
                fill = str(fill)
                while len(fill)<20: fill += " "
                bdt_df[colTitle][rowTitle] = fill
                rowTitle = p[:3] + "_norm" + str(y)[-2:]
                while len(rowTitle)<17: rowTitle+=" "
                rowTitle += "lnN"
                if "fakes" in p: fill = "0.85/1.15"
                else: fill = "0.7/1.3"
                while len(fill)<20: fill += " "
                bdt_df[colTitle][rowTitle] = fill

        ## write to output file
        writeToTxt(cc_df, "/home/users/ksalyer/FCNCAnalysis/analysis/datacards/CC/datacard_"+s+"_"+str(y)+".txt", ccSRs, procs, ccObs, ccYld)
        writeToTxt(bdt_df, "/home/users/ksalyer/FCNCAnalysis/analysis/datacards/BDT/datacard_"+s+"_"+str(y)+".txt", bdtSRs, procs, bdtObs, bdtYld)
