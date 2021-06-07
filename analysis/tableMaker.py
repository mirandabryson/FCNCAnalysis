import numpy as np
import ROOT as r
import pandas as pd
import glob
import os
r.TH1F.SetDefaultSumw2()
pd.set_option('display.float_format', lambda x: '%.5f' % x)

#years=[2016,2017,2018]
procs=['signal_tch','signal_tuh','fakes_mc','flips_mc','rares','data']
years=[2018]
#procs=['fakes_mc']

ml_hist_prefix='h_ml_'
ss_hist_prefix='h_ss_'
br_hist_prefix='h_br_'
sf_hist_prefix='h_sf_'
sfest_hist_prefix='h_sfest_'
df_hist_prefix='h_df_'
dfest_hist_prefix='h_dfest_'
basepath = os.path.realpath(__file__)
basepath = basepath.replace("tableMaker.py","")
#histdir=basepath+'outputs/v6BabyPlots/'
histdir=basepath+'outputs/v8Data_triggers_nelnmu/'
outdir=basepath+'outputs/'
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

sigregions =    {   
                    "nBtags": [0.0,0.0,0.0,1.0,1.0,1.0,2.0,2.0,2.0,0.0,0.0,0.0,1.0,1.0,1.0,2.0,2.0,2],
                    "nJets": [2.0,3.0,4.0,2.0,3.0,4.0,2.0,3.0,4.0,2.0,3.0,4.0,2.0,3.0,4.0,2.0,3.0,4],
                    "nLeptons": [2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,2.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0,3],
                }
fakesregions =    {   
                    "nBtags": [0,1,2,0,1,2],
                    "nLeptons": [2,2,2,3,3,3],
                }
flipsregions =    {   
                    "nBtags": [0,1,2],
                    "nLeptons": [2,2,2],
                }
df = pd.DataFrame(sigregions)
fakeEstsf_df = pd.DataFrame(fakesregions)
fakeEstdf_df = pd.DataFrame(fakesregions)
flipEst_df = pd.DataFrame(flipsregions)
for proc in procs:
    yields = []
    err = []
    for year in years:
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        sr_hname=br_hist_prefix+"sr_"+proc
        print sr_hname
        sr_hist=getObjFromFile(fname,sr_hname)
        for b in range(1,sr_hist.GetNbinsX()+1):
            yields.append(sr_hist.GetBinContent(b))
            err.append(sr_hist.GetBinError(b))
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
print df


for proc in procs:
    yields = []
    err = []
    for year in years:
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        sf_hname="h_sf_nbjets_"+proc
        mlsf_hname="h_mlsf_nbjets_"+proc
        sf_hist=getObjFromFile(fname,sf_hname)
        mlsf_hist=getObjFromFile(fname,mlsf_hname)
        dlyld = 0
        mlyld = 0
        dlerr = 0
        mlerr = 0
        for b in range(3,sf_hist.GetNbinsX()+2):
            dlyld += sf_hist.GetBinContent(b)
            mlyld += mlsf_hist.GetBinContent(b)
            dlerr = np.sqrt(dlerr**2 + sf_hist.GetBinError(b))
            mlerr = np.sqrt(mlerr**2 + mlsf_hist.GetBinError(b))
        yields.append(sf_hist.GetBinContent(1))
        yields.append(sf_hist.GetBinContent(2))
        yields.append(dlyld)
        yields.append(mlsf_hist.GetBinContent(1))
        yields.append(mlsf_hist.GetBinContent(2))
        yields.append(mlyld)
        err.append(np.sqrt(sf_hist.GetBinError(1)**2))
        err.append(np.sqrt(sf_hist.GetBinError(2)**2))
        err.append(dlerr)
        err.append(np.sqrt(mlsf_hist.GetBinError(1)**2))
        err.append(np.sqrt(mlsf_hist.GetBinError(2)**2))
        err.append(mlerr)
    fakeEstsf_df[proc] = yields
    fakeEstsf_df[proc+" error"] = err

fakeEstsf_df["Total Background"] = fakeEstsf_df["fakes_mc"]+fakeEstsf_df["flips_mc"]+fakeEstsf_df["rares"]
fakeEstsf_df["Total Background error"] = np.sqrt(fakeEstsf_df["fakes_mc error"]**2+fakeEstsf_df["flips_mc error"]**2+fakeEstsf_df["rares error"]**2)
sfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_sfest_nbjets_data")
mlsfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_mlsfest_nbjets_data")
column = []
err = []
dlyld = 0
mlyld = 0
dlerr = 0
mlerr = 0
for b in range(3,sfest_hist.GetNbinsX()+2):
    dlyld += sfest_hist.GetBinContent(b)
    mlyld += mlsfest_hist.GetBinContent(b)
    dlerr = np.sqrt(dlerr**2 + sfest_hist.GetBinError(b)**2)
    mlerr = np.sqrt(mlerr**2 + mlsfest_hist.GetBinError(b)**2)
column.append(sfest_hist.GetBinContent(1))
column.append(sfest_hist.GetBinContent(2))
column.append(dlyld)
column.append(mlsfest_hist.GetBinContent(1))
column.append(mlsfest_hist.GetBinContent(2))
column.append(mlyld)
err.append(np.sqrt(sfest_hist.GetBinError(1)**2))
err.append(np.sqrt(sfest_hist.GetBinError(2)**2))
err.append(dlerr)
err.append(np.sqrt(mlsfest_hist.GetBinError(1)**2))
err.append(np.sqrt(mlsfest_hist.GetBinError(2)**2))
err.append(mlerr)
fakeEstsf_df["Estimated Fakes"] = column
fakeEstsf_df["Estimated Fakes error"] = err
ss_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ss_nbjets_fakes_mc")
ml_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ml_nbjets_fakes_mc")
column = []
err = []
dlyld = 0
mlyld = 0
dlerr = 0
mlerr = 0
for b in range(3,ss_hist.GetNbinsX()+2):
    dlyld += ss_hist.GetBinContent(b)
    mlyld += ml_hist.GetBinContent(b)
    dlerr = np.sqrt(dlerr**2 + ss_hist.GetBinError(b)**2)
    mlerr = np.sqrt(mlerr**2 + ml_hist.GetBinError(b)**2)
column.append(ss_hist.GetBinContent(1))
column.append(ss_hist.GetBinContent(2))
column.append(dlyld)
column.append(ml_hist.GetBinContent(1))
column.append(ml_hist.GetBinContent(2))
column.append(mlyld)
err.append(ss_hist.GetBinError(1))
err.append(ss_hist.GetBinError(2))
err.append(dlerr)
err.append(ml_hist.GetBinError(1))
err.append(ml_hist.GetBinError(2))
err.append(mlerr)
fakeEstsf_df["SR fakes"] = column
fakeEstsf_df["SR error"] = err
fakeEstsf_df = fakeEstsf_df.drop(["signal_tch","signal_tch error","signal_tuh","signal_tuh error","fakes_mc","fakes_mc error","flips_mc","flips_mc error","rares","rares error"],axis=1)
print fakeEstsf_df



for proc in procs:
    yields = []
    err = []
    for year in years:
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        df_hname="h_df_nbjets_"+proc
        mldf_hname="h_mldf_nbjets_"+proc
        df_hist=getObjFromFile(fname,df_hname)
        mldf_hist=getObjFromFile(fname,mldf_hname)
        dlyld = 0
        mlyld = 0
        dlerr = 0
        mlerr = 0
        for b in range(3,df_hist.GetNbinsX()+2):
            dlyld += df_hist.GetBinContent(b)
            mlyld += mldf_hist.GetBinContent(b)
            dlerr = np.sqrt(dlerr**2 + df_hist.GetBinError(b)**2)
            mlerr = np.sqrt(mlerr**2 + mldf_hist.GetBinError(b)**2)
        yields.append(df_hist.GetBinContent(1))
        yields.append(df_hist.GetBinContent(2))
        yields.append(dlyld)
        yields.append(mldf_hist.GetBinContent(1))
        yields.append(mldf_hist.GetBinContent(2))
        yields.append(mlyld)
        err.append(np.sqrt(df_hist.GetBinError(1)**2))
        err.append(np.sqrt(df_hist.GetBinError(2)**2))
        err.append(dlerr)
        err.append(np.sqrt(mldf_hist.GetBinError(1)**2))
        err.append(np.sqrt(mldf_hist.GetBinError(2)**2))
        err.append(mlerr)
    fakeEstdf_df[proc] = yields
    fakeEstdf_df[proc+" error"] = err

fakeEstdf_df["Total Background"] = fakeEstdf_df["fakes_mc"]+fakeEstdf_df["flips_mc"]+fakeEstdf_df["rares"]
fakeEstdf_df["Total Background error"] = np.sqrt(fakeEstdf_df["fakes_mc error"]**2+fakeEstdf_df["flips_mc error"]**2+fakeEstdf_df["rares error"]**2)
dfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_dfest_nbjets_data")
mldfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_mldfest_nbjets_data")
column = []
err = []
dlyld = 0
mlyld = 0
dlerr = 0
mlerr = 0
for b in range(3,dfest_hist.GetNbinsX()+2):
    dlyld += dfest_hist.GetBinContent(b)
    mlyld += mldfest_hist.GetBinContent(b)
    dlerr = np.sqrt(dlerr**2 + dfest_hist.GetBinError(b)**2)
    mlerr = np.sqrt(mlerr**2 + mldfest_hist.GetBinError(b)**2)
column.append(dfest_hist.GetBinContent(1))
column.append(dfest_hist.GetBinContent(2))
column.append(dlyld)
column.append(mldfest_hist.GetBinContent(1))
column.append(mldfest_hist.GetBinContent(2))
column.append(mlyld)
err.append(np.sqrt(dfest_hist.GetBinError(1)**2))
err.append(np.sqrt(dfest_hist.GetBinError(2)**2))
err.append(dlerr)
err.append(np.sqrt(mldfest_hist.GetBinError(1)**2))
err.append(np.sqrt(mldfest_hist.GetBinError(2)**2))
err.append(mlerr)
fakeEstdf_df["Estimated Fakes"] = column
fakeEstdf_df["Estimated Fakes error"] = err
ss_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ss_nbjets_fakes_mc")
ml_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ml_nbjets_fakes_mc")
column = []
err = []
dlyld = 0
mlyld = 0
dlerr = 0
mlerr = 0
for b in range(3,ss_hist.GetNbinsX()+2):
    dlyld += ss_hist.GetBinContent(b)
    mlyld += ml_hist.GetBinContent(b)
    dlerr = np.sqrt(dlerr**2 + ss_hist.GetBinError(b)**2)
    mlerr = np.sqrt(mlerr**2 + ml_hist.GetBinError(b)**2)
column.append(ss_hist.GetBinContent(1))
column.append(ss_hist.GetBinContent(2))
column.append(dlyld)
column.append(ml_hist.GetBinContent(1))
column.append(ml_hist.GetBinContent(2))
column.append(mlyld)
err.append(ss_hist.GetBinError(1))
err.append(ss_hist.GetBinError(2))
err.append(dlerr)
err.append(ml_hist.GetBinError(1))
err.append(ml_hist.GetBinError(2))
err.append(mlerr)
fakeEstdf_df["SR fakes"] = column
fakeEstdf_df["SR error"] = err
fakeEstdf_df = fakeEstdf_df.drop(["signal_tch","signal_tch error","signal_tuh","signal_tuh error","fakes_mc","fakes_mc error","flips_mc","flips_mc error","rares","rares error"],axis=1)
print fakeEstdf_df







for proc in procs:
    yields = []
    err = []
    for year in years:
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        os_hname="h_os_nbjets_"+proc
        os_hist=getObjFromFile(fname,os_hname)
        yld = 0
        error = 0
        for b in range(3,os_hist.GetNbinsX()+2):
            yld += os_hist.GetBinContent(b)
            error = np.sqrt(error**2 + os_hist.GetBinError(b)**2)
        yields.append(os_hist.GetBinContent(1))
        yields.append(os_hist.GetBinContent(2))
        yields.append(yld)
        err.append(os_hist.GetBinError(1))
        err.append(os_hist.GetBinError(2))
        err.append(error)
    flipEst_df[proc] = yields
    flipEst_df[proc+" error"] = err

flipEst_df["Total Background"] = flipEst_df["fakes_mc"]+flipEst_df["flips_mc"]+flipEst_df["rares"]
flipEst_df["Total Background error"] = np.sqrt(flipEst_df["fakes_mc error"]**2+flipEst_df["flips_mc error"]**2+flipEst_df["rares error"]**2)
osest_hist=getObjFromFile(histdir+'flips_mc_{}_hists.root'.format(year),"h_osest_nbjets_flips_mc")
column = []
err = []
yld = 0
error = 0
for b in range(3,osest_hist.GetNbinsX()+2):
    yld += osest_hist.GetBinContent(b)
    error = np.sqrt(error**2 + osest_hist.GetBinError(b)**2)
column.append(osest_hist.GetBinContent(1))
column.append(osest_hist.GetBinContent(2))
column.append(yld)
err.append(osest_hist.GetBinError(1))
err.append(osest_hist.GetBinError(2))
err.append(error)
flipEst_df["Estimated Flips"] = column
flipEst_df["Estimated Flips error"] = err
ss_hist=getObjFromFile(histdir+'flips_mc_{}_hists.root'.format(year),"h_ss_nbjets_flips_mc")
#ml_hist=getObjFromFile(histdir+'_flips_mc_{}_hists.root'.format(year),"h_ml_nbjets_flips_mc")
column = []
err = []
dlyld = 0
mlyld = 0
dlerr = 0
mlerr = 0
for b in range(3,ss_hist.GetNbinsX()+2):
    dlyld += ss_hist.GetBinContent(b)
    #mlyld += ml_hist.GetBinContent(b)
    dlerr = np.sqrt(dlerr**2 + ss_hist.GetBinError(b)**2)
    #mlerr = np.sqrt(mlerr**2 + ml_hist.GetBinError(b)**2)
column.append(ss_hist.GetBinContent(1))
column.append(ss_hist.GetBinContent(2))
column.append(dlyld)
#column.append(ml_hist.GetBinContent(1))
#column.append(ml_hist.GetBinContent(2))
#column.append(mlyld)
err.append(ss_hist.GetBinError(1))
err.append(ss_hist.GetBinError(2))
err.append(dlerr)
#err.append(ml_hist.GetBinError(1))
#err.append(ml_hist.GetBinError(2))
#err.append(mlerr)
flipEst_df["SR flips"] = column
flipEst_df["SR error"] = err
print flipEst_df


#save as tex files
outFile = open(outdir+"tables/tableMaker.tex","w")
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


outFile = open(outdir+"tables/fakeEstsf.tex","w")
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
outFile.write(fakeEstsf_df.to_latex())
#outFile.write("\end{preview} \n")
outFile.write("\end{document} \n")
#outFile.write("\end{document}")
#outFile.write("\n")
outFile.close()
#print(df.to_latex())


outFile = open(outdir+"tables/fakeEstdf.tex","w")
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
outFile.write(fakeEstdf_df.to_latex())
#outFile.write("\end{preview} \n")
outFile.write("\end{document} \n")
#outFile.write("\end{document}")
#outFile.write("\n")
outFile.close()
#print(df.to_latex())
