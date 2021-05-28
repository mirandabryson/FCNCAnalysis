import numpy as np
import ROOT as r
import pandas as pd
import glob
import os
r.TH1F.SetDefaultSumw2()
pd.set_option('display.float_format', lambda x: '%.5f' % x)

#years=[2016,2017,2018]
procs=['signal_tch','signal_tuh','fakes_mc','flips_mc','rares']
years=[2018]
#procs=['fakes_mc']

ml_hist_prefix='h_ml_'
ss_hist_prefix='h_ss_'
br_hist_prefix='h_br_'
basepath = os.path.realpath(__file__)
basepath = basepath.replace("tableMaker.py","")
histdir=basepath+'outputs/'
#files = glob.glob(histdir)

def getObjFromFile(fname, hname):
    f = r.TFile(fname)
    assert not f.IsZombie()
    f.cd()
    htmp = f.Get(hname)
    if not htmp:  return htmp
    r.gDirectory.cd('PyROOT:/')
    res = htmp.Clone()
    f.Close()
    return res

sigregions =    {   "nLeptons": [2, 2, 2, 3, 3, 3],
                    "nBtags": [0,1,2,0,1,2]
                }
df = pd.DataFrame(sigregions)
for proc in procs:
    yields = []
    err = []
    for year in years:
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        ml_hname=ml_hist_prefix+"nbjets_"+proc
        ss_hname=ss_hist_prefix+"nbjets_"+proc
        print ml_hname
        print ss_hname
        ml_hist=getObjFromFile(fname,ml_hname)
        ss_hist=getObjFromFile(fname,ss_hname)
        yields.append(ss_hist.GetBinContent(1))
        yields.append(ss_hist.GetBinContent(2))
        yields.append(ss_hist.GetBinContent(3)+ss_hist.GetBinContent(4)+ss_hist.GetBinContent(5)+ss_hist.GetBinContent(6))
        yields.append(ml_hist.GetBinContent(1))
        yields.append(ml_hist.GetBinContent(2))
        yields.append(ml_hist.GetBinContent(3)+ml_hist.GetBinContent(4)+ml_hist.GetBinContent(5)+ml_hist.GetBinContent(6))

        print yields
        err.append(ss_hist.GetBinError(1))
        err.append(ss_hist.GetBinError(2))
        err.append(np.sqrt(ss_hist.GetBinError(3)**2+ss_hist.GetBinError(4)**2+ss_hist.GetBinError(5)**2+ss_hist.GetBinError(6)**2))
        err.append(ml_hist.GetBinError(1))
        err.append(ml_hist.GetBinError(2))
        err.append(np.sqrt(ml_hist.GetBinError(3)**2+ml_hist.GetBinError(4)**2+ml_hist.GetBinError(5)**2+ml_hist.GetBinError(6)**2))
        
    df[proc] = yields
    df[proc+" error"] = err

#df.loc['Total']= df.sum(numeric_only=True, axis=0)
df.at["Total", "fakes_mc"] = df["fakes_mc"].sum()
df.at["Total", "fakes_mc error"] = round(np.sqrt(df["fakes_mc error"].pow(2).sum()),2)
df.loc["Total", "flips_mc"] = df["flips_mc"].sum()
df.at["Total", "flips_mc error"] = round(np.sqrt(df["flips_mc error"].pow(2).sum()),2)
df.loc["Total", "rares"] = df["rares"].sum()
df.at["Total", "rares error"] = round(np.sqrt(df["rares error"].pow(2).sum()),2)
df.loc["Total", "signal_tuh"] = df["signal_tuh"].sum()
df.at["Total", "signal_tuh error"] = round(np.sqrt(df["signal_tuh error"].pow(2).sum()),2)
df.loc["Total", "signal_tch"] = df["signal_tch"].sum()
df.at["Total", "signal_tch error"] = round(np.sqrt(df["signal_tch error"].pow(2).sum()),2)
df = df.fillna("")

#save as tex file
outFile = open(histdir+"tables/tableMaker.tex","w")
outFile.write("\documentclass[oneside]{report} \n")
outFile.write("\usepackage[a1paper]{geometry}")
outFile.write("\usepackage{graphicx,xspace,amssymb,amsmath,colordvi,colortbl,verbatim,multicol} \n")
#outFile.write("\usepackage{multirow, rotating} \n")
#outFile.write("\usepackage[active,tightpage]{preview} \n")
outFile.write("\\renewcommand{\\arraystretch}{1.1} \n")
outFile.write("\\begin{document} \n")
#outFile.write("\begin{preview} \n")
#outFile.write("\\footnotesize \n")
outFile.write("\\centering \n")
outFile.write(df.to_latex())
#outFile.write("\end{preview} \n")
outFile.write("\end{document} \n")
#outFile.write("\end{document}")
#outFile.write("\n")
outFile.close()
#print(df.to_latex())
