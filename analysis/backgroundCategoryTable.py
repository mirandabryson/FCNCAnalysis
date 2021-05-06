#code to write background category table from txt file
#run with python backgroundCategoryTable.py
#Kaitlin Salyer, May 2021

#import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd

#hardcoded variables other users should customize
outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/backgroundCategoryTables"

#load input file
filename = sys.argv[-1]

#useful functions
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

#break into background categories
samples = [
    "TTGamma_SingleLept",
    "TGJets",
    "TTWJetsToLNu",
    "WJetsToLNu",
    "ST_tWll_5f_LO",
    "TTGamma_Dilept",
    "TTZToLLNuNu_M10",
    "TTZToLL_M1to10",
    "DYJetsToLL_M10to50",
    "DYJetsToLL_M50",
    "ZGToLLG_01J_5f",
    "ZZTo4L",
    "ZZZ",
    "GluGluHToZZTo4L",
    "GluGluToContinToZZTo2e2mu",
    "GluGluToContinToZZTo2e2tau",
    "GluGluToContinToZZTo2mu2tau",
    "GluGluToContinToZZTo4e",
    "GluGluToContinToZZTo4mu",
    "GluGluToContinToZZTo4tau",
    "WWG",
    "WWTo2L2Nu_DoubleScattering",
    "WWW_4F",
    "WWZ",
    "WZG",
    "WZTo3LNu",
    "WZZ",
    "TTJets",
    "TTHH",
    "TTTJ",
    "TTTT",
    "TTTW",
    "TTWH",
    "TTWW",
    "TTWZ",
    "TTZH",
    "TTZZ",
    "WGToLNuG_01J_5f",
    "WpWpJJ_EWKQCD",
    "VHToNonbb_M125",
    "tZq_ll_4f_ckm_NLO",
    "ttHToNonbb_M125"
]


columns = ["sample", "fakes", "fakes error", "flips", "flips error", "other", "other error"]

df = pd.DataFrame()

for s in samples:
    print(s)
    histoName = "h_backgroundTypes_" + s + "_background"
    hist = getObjFromFile(filename,histoName)
    isFakeYld = hist.GetBinContent(0)
    isFlipYld = hist.GetBinContent(1)
    isOtherYld = hist.GetBinContent(2)
    isFakeErr = hist.GetBinError(0)
    isFlipErr = hist.GetBinError(1)
    isOtherErr = hist.GetBinError(2)
    #print(isFakeYld, isFlipYld, isOtherYld)
    row = [[s, isFakeYld, isFakeErr, isFlipYld, isFlipErr, isOtherYld, isOtherErr]]
    new_row = pd.DataFrame(row, columns=columns)
    df = df.append(new_row, ignore_index = True)

isFakeYld = df["fakes"].sum()
isFakeErr = np.sqrt(df["fakes error"].pow(2).sum())
isFlipYld = df["flips"].sum()
isFlipErr = np.sqrt(df["flips error"].pow(2).sum())
isOtherYld = df["other"].sum()
isOtherErr = np.sqrt(df["other error"].pow(2).sum())
totRow = pd.DataFrame([["Total", isFakeYld, isFakeErr, isFlipYld, isFlipErr, isOtherYld, isOtherErr]], columns = columns)
df = df.append(totRow, ignore_index = True)
df = df.fillna("")
print(df)


outFile = open(outdir+"/backgroundCategories.tex","w")
outFile.write("\documentclass[oneside]{report} \n")
outFile.write("\usepackage[a1paper]{geometry}")
outFile.write("\usepackage{graphicx,xspace,amssymb,amsmath,colordvi,colortbl,verbatim,multicol} \n")
outFile.write("\\renewcommand{\\arraystretch}{1.1} \n")
outFile.write("\\begin{document} \n")
outFile.write("\\centering \n")
outFile.write(df.to_latex())
outFile.write("\end{document} \n")
outFile.close()

