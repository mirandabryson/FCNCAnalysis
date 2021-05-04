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
outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/"

#load input file
filename = sys.argv[-1]

#first, we load the txt output from the tableMaker.py script into a dataframe
#we will manipulate these data, save it into a different dataframe, and print to an output file
df = pd.read_csv(filename, delimiter=" ")
print("filled df")
#print(df)

#break into background categories
samples = [
"TTGamma_SingleLept",
"TGJets",
"TTWJetsToLNu",
"WJetsToLNu",
"ST_tWll_5f_LO",
"TTGamma_Dilept",
"TTZToLLNuNu_M-10",
"TTZToLL_M-1to10",
"DYJetsToLL_M-10to50",
"DYJetsToLL_M-50",
"ZGToLLG_01J_5f",
"ZZTo4L",
"ZZZ",
"GluGluHToZZTo4L_M125",
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
"WpWpJJ_EWK-QCD",
"VHToNonbb_M125",
"tZq_ll_4f_ckm_NLO",
"ttHToNonbb_M125"
]

for s in samples:
    sample_df = df[df["sampleName"].str.contains(s)]
    sample_idx = df.index[ df["sampleName"].str.contains(s) ].tolist()
    for row in sample_df.index:
        if (sample_df["isFake"][row] == 1) and (sample_df["isOther"][row] == 1):
            sample_df["isOther"][row] = 0
    #print(sample_df)
    row = [[s, sample_df["isFake"].sum(), sample_df["isFlip"].sum(), sample_df["isOther"].sum()]]
    new_row = pd.DataFrame(row, columns=df.columns)
    #print(new_row)
    df = df.drop(sample_idx, axis=0)
    df = df.append(new_row, ignore_index = True)
print df

outFile = open("./backgroundCategories.tex","w")
outFile.write("\documentclass[oneside]{report} \n")
outFile.write("\usepackage[a1paper]{geometry}")
outFile.write("\usepackage{graphicx,xspace,amssymb,amsmath,colordvi,colortbl,verbatim,multicol} \n")
outFile.write("\\renewcommand{\\arraystretch}{1.1} \n")
outFile.write("\\begin{document} \n")
outFile.write("\\centering \n")
outFile.write(df.to_latex())
outFile.write("\end{document} \n")
outFile.close()
