import numpy as np
import ROOT as r
import pandas as pd
import glob
import os
r.TH1F.SetDefaultSumw2()
pd.set_option('display.float_format', lambda x: '%.5f' % x)

years=[2016,2017,2018]
pdfyear = 2016
# years=[2016]
procs=['signal_tch','signal_tuh','rares']
# procs=['signal_tuh','signal_tch']
variations = ['up','central','down']
# sources = ['pdf','renorm','LepSF','PU','Trigger','bTag','jes']
sources = [ 'pdf','renorm','LepSF','PU','Trigger', 'jes',
# sources = [ 'LepSF','PU','Trigger', 'jes',
            'lf_up','lf_down',
            'hf_up','hf_down',
            'hfstats1_up','hfstats1_down',
            'hfstats2_up','hfstats2_down',
            'lfstats1_up','lfstats1_down',
            'lfstats2_up','lfstats2_down',
            'cferr1_up','cferr1_down',
            'cferr2_up','cferr2_down']
sigWeight = 0.01

br_hist_prefix='h_br_'
basepath = os.path.realpath(__file__)
basepath = basepath.replace("variationsTable.py","")
centraldir=basepath+'outputs/aug19_centralValues_lead25_MET50_jet30/'
nobsfdir=basepath+'outputs/sept3_nobsf/'
pdfdir = basepath+'outputs/aug31_systematics/'
variationdir=basepath+'outputs/aug19_variations_lead25_MET50_jet30/'
bvariationdir=basepath+'outputs/sept3_btag_systematics/'
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
    tuhpdf_up = []
    tuhpdf_down = []
    tuhrenorm = []
    for proc in procs:
        sigregions =    {   
                            "nBtags": [0,0,0,1,1,1,2,2,2, 0,0,0,0,1,1,1,1,2,2,2,2],
                            "nJets": [2,3,4,2,3,4,2,3,4, 1,2,3,4,1,2,3,4,1,2,3,4],
                            "nLeptons": [2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3],
                        }
        df = pd.DataFrame(sigregions)

        yields = []
        err = []
        fname = bvariationdir+proc+'_{}_hists.root'.format(year)
        hname = "h_btag_central_sr_syst_"+proc
        hist=getObjFromFile(fname,hname)
        for b in range(1,hist.GetNbinsX()+1):
            yields.append(hist.GetBinContent(b))
            err.append(hist.GetBinError(b))
        df[proc + " central"] = yields

        # yields = []
        # err = []
        # fname = centraldir+proc+'_{}_hists.root'.format(year)
        # hname = "h_br_sr_"+proc
        # hist=getObjFromFile(fname,hname)
        # for b in range(1,hist.GetNbinsX()+1):
        #     yields.append(hist.GetBinContent(b))
        #     err.append(hist.GetBinError(b))
        # df[proc + " 1a central"] = yields

        # yields = []
        # err = []
        # fname = nobsfdir+proc+'_{}_hists.root'.format(year)
        # hname = "h_br_sr_"+proc
        # hist=getObjFromFile(fname,hname)
        # for b in range(1,hist.GetNbinsX()+1):
        #     yields.append(hist.GetBinContent(b))
        #     err.append(hist.GetBinError(b))
        # df[proc + " no bsf central"] = yields

        ## make variations table
        for s in sources:
            if "pdf" in s:
                yields = []
                err = []
                fname = pdfdir+proc+'_{}_hists.root'.format(pdfyear)
                hname = "h_0_0_pdf_scale_sr_syst_"+proc
                centhist=getObjFromFile(fname,hname)
                # print(fname, hname)
                for b in range(1,centhist.GetNbinsX()+1):
                    yields.append(centhist.GetBinContent(b))
                    err.append(centhist.GetBinError(b))
                df[proc + " " + s + " central"] = yields

                yields = []
                yields_up = []
                yields_down = []
                err = []
                for b in range(1,centhist.GetNbinsX()+1):
                    srVar = []
                    for p in range(1,101):
                        fname = pdfdir+proc+'_{}_hists.root'.format(pdfyear)
                        hname = "h_"+str(p)+"_"+str(p)+"_pdf_scale_sr_syst_"+proc
                        hist=getObjFromFile(fname,hname)
                        srVar.append([hist.GetBinContent(b),p])
                        # print(p, b, hist.GetBinContent(b))
                    srVar.sort()
                    yields_down.append(srVar[15][0])
                    print(s, b, srVar[15][1], srVar[83][1])
                    yields_up.append(srVar[83][0])
                    # srVar = srVar[15:83]
                    # srVar[:] = [val-centhist.GetBinContent(b) for val in srVar]
                    # srVar[:] = [val/centhist.GetBinContent(b) for val in srVar]
                    # srVar[:] = [val**2 for val in srVar]
                    # binVal = 0
                    # for val in srVar:
                    #     binVal += val
                    # binVal = np.sqrt(binVal)
                    # yields.append(binVal)
                # print(yields)
                df[proc + " " + s + " up"] = yields_up
                df[proc + " " + s + " down"] = yields_down
                df[proc + "_" + s + "_up"] = df[proc + " " + s + " up"]/df[proc + " " + s + " central"]
                df[proc + "_" + s + "_down"] = df[proc + " " + s + " down"]/df[proc + " " + s + " central"]
                tuhpdf_up = df[proc + "_" + s + "_up"]
                tuhpdf_down = df[proc + "_" + s + "_down"]
                df = df.drop([proc + " " + s + " central"],axis=1)
                df = df.drop([proc + " " + s + " up"],axis=1)
                df = df.drop([proc + " " + s + " down"],axis=1)


                # for p in range(0,102):
                #     yields = []
                #     err = []
                #     fname = variationdir+proc+'_{}_hists.root'.format(year)
                #     hname = "h_pdf_scale_"+str(p)+"_sr_syst_"+proc
                #     hist=getObjFromFile(fname,hname)
                #     for b in range(1,hist.GetNbinsX()+1):
                #         # if b ==1: print(hist.GetBinContent(b)/13569.88477)
                #         yields.append(hist.GetBinContent(b))
                #         err.append(hist.GetBinError(b))
                #     df[proc + " " + s + " " + str(p)] = yields
                #     # df[proc + " " + s + " " + str(p)] = ((df[proc + " " + s + " " + str(p)]-df[proc+" "+s+" central"])/df[proc+" "+s+" central"])**2
                # df[proc+" "+s+" variation"] = [0]*21
                # for p in range(0,102):
                #     df[proc+" "+s+" variation"] += df[proc + " " + s + " " + str(p)]
                #     df = df.drop([proc + " " + s + " " + str(p)],axis=1)
                # df[proc+" "+s+" variation"] = np.sqrt(df[proc+" "+s+" variation"])
                # print df

            elif "renorm" in s:
                yields = []
                err = []
                fname = centraldir+proc+'_{}_hists.root'.format(pdfyear)
                hname = "h_br_sr_"+proc
                hist=getObjFromFile(fname,hname)
                for b in range(1,hist.GetNbinsX()+1):
                    yields.append(hist.GetBinContent(b))
                    err.append(hist.GetBinError(b))
                df[proc + " " + s + " central"] = yields
                # print("central", yields)

                for p in range(0,7):
                    yields = []
                    err = []
                    fname = pdfdir+proc+'_{}_hists.root'.format(pdfyear)
                    hname = "h_"+str(p)+"_renorm_scale_sr_syst_"+proc
                    hist=getObjFromFile(fname,hname)
                    for b in range(1,hist.GetNbinsX()+1):
                        yields.append(hist.GetBinContent(b))
                        err.append(hist.GetBinError(b))
                    # print(p, yields)
                    df[proc + " " + s + " " + str(p)] = yields
                    df[proc + " " + s + " " + str(p)] = abs(df[proc + " " + s + " " + str(p)]-df[proc+" "+s+" central"])
                    # print(df[proc + " " + s + " " + str(p)])
                df[proc+"_"+s+"_variation"] = df[[  proc + " " + s + " 0",
                                                    proc + " " + s + " 1",
                                                    proc + " " + s + " 2",
                                                    proc + " " + s + " 3",
                                                    proc + " " + s + " 4",
                                                    proc + " " + s + " 5"]].max(axis=1)
                # df[proc+" "+s+" variation"] = [0.]*21
                # for ind in df.index:
                #     for p in range(0,7):
                #         if (df[proc + " " + s + " " + str(p)][ind] > df[proc+" "+s+" variation"][ind]): 
                #             print(df[proc + " " + s + " " + str(p)][ind], df[proc+" "+s+" variation"][ind])
                #             df[proc+" "+s+" variation"][ind] = df[proc + " " + s + " " + str(p)][ind]
                #         # df = df.drop(df[proc + " " + s + " " + str(p)],axis=1)
                for p in range(0,7):
                    df = df.drop([proc + " " + s + " " + str(p)],axis=1)
                df[proc+"_"+s+"_variation"] = df[proc+"_"+s+"_variation"]/df[proc + " " + s + " central"]
                df[proc+"_"+s+"_variation"] += [1.]*21
                df = df.drop([proc + " " + s + " central"],axis=1)
                # print df
                tuhrenorm = df[proc+"_"+s+"_variation"]
            elif "up" in s or "down" in s:
                yields = []
                err = []
                fname = bvariationdir+proc+'_{}_hists.root'.format(year)
                hname = "h_"+s+"_sr_syst_"+proc
                # print(fname, hname)
                hist=getObjFromFile(fname,hname)
                for b in range(1,hist.GetNbinsX()+1):
                    yields.append(hist.GetBinContent(b))
                    err.append(hist.GetBinError(b))
                # print(p, yields)
                df[proc + "_" + s] = yields
                df[proc + "_" + s] = df[proc + "_" + s]/df[proc+" central"]
                # print df
            else:
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
                    hist=getObjFromFile(fname,hname)
                    # print(hname)
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

        
        df = df.drop([proc+ " central"],axis=1)
        av_col = df.mean(axis=0)
        print(av_col)
        # df.append(av_col, ignore_index=True)
        # df.loc['Average',proc+'_'+]= df.mean(numeric_only=True, axis=0)
        # df.at["Total", proc+" central"] = df[proc + " central"].sum()
        # df.at["Total", proc+" 1a central"] = df[proc + " 1a central"].sum()
        # df.at["Total", proc+" no bsf central"] = df[proc + " no bsf central"].sum()
        # print(av_col)
    
        # df["S/B"] = (df['signal_tch']+df['signal_tuh'])/(df["fakes_mc"]+df["flips_mc"]+df["rares"])
        
        # df = df.drop([5])
        # df.ix[9],df.ix[10],df.ix[11],df.ix[12] = df.ix[12],df.ix[9],df.ix[10],df.ix[11]

        # df = df.fillna("")
        for column in df:
            yields = df[column].tolist()
            # print yields
            yields = [round(abs(i-1)*100,0) for i in yields]
            yields.sort()
            # print yields
            print (column, yields[3], yields[17])
        writeToLatexFile("variations/"+outtag+"/"+proc+"_"+str(year), df)
        outtxt = open(outdir+"variations/" +outtag+"/"+proc+"_"+str(year)+".txt","w")
        outtxt.write(df.to_csv(index=False))
        outtxt.close()
        print df
