import numpy as np
import ROOT as r
import pandas as pd
import glob
import os
r.TH1F.SetDefaultSumw2()
pd.set_option('display.float_format', lambda x: '%.5f' % x)

years=[2016,2017,2018]
procs=['signal_tch','signal_tuh','rares']
# procs=['signal_tuh']
variations = ['up','central','down']
sources = ['LepSF','PU','Trigger','bTag','jes']
sigWeight = 0.01

br_hist_prefix='h_br_'
basepath = os.path.realpath(__file__)
basepath = basepath.replace("variationsTable.py","")
centraldir=basepath+'outputs/aug19_centralValues_lead25_MET50_jet30/'
variationdir=basepath+'outputs/aug19_variations_lead25_MET50_jet30/'
jesupdir=basepath+'outputs/aug19_jesup_lead25_MET50_jet30/'
jesdowndir=basepath+'outputs/aug19_jesdown_lead25_MET50_jet30/'
outdir=basepath+'outputs/'
outtag=''
#files = glob.glob(histdir)
if not os.path.exists(outdir+"variations/"+outtag): os.makedirs(outdir+"variations/"+outtag)

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

def writeToLatexFile(outName, df):
    outFile = open(outdir+outName+".tex","w")
    outFile.write("\documentclass[oneside]{report} \n")
    outFile.write("\usepackage[a1paper]{geometry}")
    outFile.write("\usepackage{graphicx,xspace,amssymb,amsmath,colordvi,colortbl,verbatim,multicol} \n")
    outFile.write("\\renewcommand{\\arraystretch}{1.1} \n")
    outFile.write("\\begin{document} \n")
    outFile.write("\\centering \n")
    outFile.write(df.to_latex())
    outFile.write("\end{document} \n")
    outFile.close()

for year in years:
    for proc in procs:
        sigregions =    {   
                            "nBtags": [0,0,0,1,1,1,2,2,2, 0,0,0,0,1,1,1,1,2,2,2,2],
                            "nJets": [2,3,4,2,3,4,2,3,4, 1,2,3,4,1,2,3,4,1,2,3,4],
                            "nLeptons": [2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3],
                        }
        df = pd.DataFrame(sigregions)

        ## make variations table
        for s in sources:
            for v in variations:
                yields = []
                err = []
                if "central" in v: histdir = centraldir
                elif 'up' in v and 'jes' in s: histdir = jesupdir
                elif 'down' in v and 'jes' in s: histdir = jesdowndir
                else: histdir = variationdir
                fname=histdir+proc+'_{}_hists.root'.format(year)
                # print fname
                if 'central' in v: hname="h_br_sr_"+proc
                elif s=='jes': hname="h_br_sr_"+proc
                else: hname="h_"+s+"_"+v+"_sr_syst_"+proc
                # print hname
                hist=getObjFromFile(fname,hname)
                for b in range(1,hist.GetNbinsX()+1):
                    yields.append(hist.GetBinContent(b))
                    err.append(hist.GetBinError(b))
                df[proc + " " + s + " " + v] = yields
                # print(proc + " " + s + " " + v)
               # df[proc + " " + s + " " + v + " error"] = err
            df[proc+ "_" + s + "_up"] = df[proc+ " " + s + " up"]/df[proc+ " " + s + " central"]
            df[proc+ "_" + s + "_down"] = df[proc+ " " + s + " down"]/df[proc+ " " + s + " central"]
            df = df.drop([proc+ " " + s + " up"],axis=1)
            df = df.drop([proc+ " " + s + " down"],axis=1)
            df = df.drop([proc+ " " + s + " central"],axis=1)
            # df.loc['Average',proc+'_'+s+'_up'] = df.mean(df[proc+'_'+s+'_up'])
            # df.loc['Average',proc+'_'+s+'_down'] = df.mean(df[proc+'_'+s+'_down'])

        av_col = df.mean(axis=0)
        print(av_col)
        # df.append(av_col, ignore_index=True)
        # df.loc['Average',proc+'_'+]= df.mean(numeric_only=True, axis=0)
        # df.at["Total", "fakes_mc"] = df["fakes_mc"].sum()
        # df.at["Total", "fakes_mc error"] = round(np.sqrt(df["fakes_mc error"].pow(2).sum()),2)
        # df.loc["Total", "flips_mc"] = df["flips_mc"].sum()
        # df.at["Total", "flips_mc error"] = round(np.sqrt(df["flips_mc error"].pow(2).sum()),2)
        # df.loc["Total", "rares"] = df["rares"].sum()
        # df.at["Total", "rares error"] = round(np.sqrt(df["rares error"].pow(2).sum()),2)
        # df.loc["Total", "signal_tuh"] = df["signal_tuh"].sum()
        # df.at["Total", "signal_tuh error"] = round(np.sqrt(df["signal_tuh error"].pow(2).sum()),2)
        # df.loc["Total", "signal_tch"] = df["signal_tch"].sum()
        # df.at["Total", "signal_tch error"] = rou
        # print(av_col)
    
        # df["S/B"] = (df['signal_tch']+df['signal_tuh'])/(df["fakes_mc"]+df["flips_mc"]+df["rares"])
        
        # df = df.drop([5])
        # df.ix[9],df.ix[10],df.ix[11],df.ix[12] = df.ix[12],df.ix[9],df.ix[10],df.ix[11]

        # df = df.fillna("")
        writeToLatexFile("variations/"+outtag+"/"+proc+"_"+str(year), df)
        outtxt = open(outdir+"variations/" +outtag+"/"+proc+"_"+str(year)+".txt","w")
        outtxt.write(df.to_csv(index=False))
        outtxt.close()
        print df
