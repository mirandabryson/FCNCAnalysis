import numpy as np
import ROOT as r
import pandas as pd
import glob
import os
r.TH1F.SetDefaultSumw2()
pd.set_option('display.float_format', lambda x: '%.5f' % x)

years=[2016,2017,2018]
# years=[2018]
# procs=['signal_tch','signal_tuh','fakes_mc','flips_mc','rares','data']
# procs=['data']
procs=['signal_tch','signal_tuh']
# procs=['signal_tuh']
# procs=['signal_tch', 'signal_tuh','rares']
sigWeight = 0.01
# sigWeight = 1
# years=[2016]
blind = True

doCutflow = 0
doSRTable = 1
doFakeCR  = 0
doFakeEst = 0
doFakeVal = 0
doFlipCR  = 0
doFlipEst = 0
doFlipVal = 0

br_hist_prefix='h_br_'
basepath = os.path.realpath(__file__)
basepath = basepath.replace("tableMaker.py","")
histdir=basepath+'outputs/oct12_runAll/'
sighistdir=basepath+'outputs/oct12_runAll/'
outdir=basepath+'outputs/'
outtag='oct12_runAll/'
#files = glob.glob(histdir)
if not os.path.exists(outdir+"tables/"+outtag): os.makedirs(outdir+"tables/"+outtag)

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
    sigregions =    {   
                        "nBtags": [0,0,0,1,1,1,2,2,2, 0,0,0,0,1,1,1,1,2,2,2,2],
                        "nJets": [2,3,4,2,3,4,2,3,4, 1,2,3,4,1,2,3,4,1,2,3,4],
                        "nLeptons": [2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3],
                    }
    cutregions =    {   
                        "cuts": [   'entry',
                                    'MET>=50',
                                    '2SS or 3 leptons',
                                    'N_jets>=2 or N_jets>=1',
                                    'pass triggers',
                                    'pass filters',
                                    'onZveto',],
                    }
    df = pd.DataFrame(sigregions)
    fake_cr_df = pd.DataFrame(sigregions)
    fakeEst_df = pd.DataFrame(sigregions)
    fakeVal_df = pd.DataFrame(sigregions)
    flip_cr_df = pd.DataFrame(sigregions)
    flipEst_df = pd.DataFrame(sigregions)
    flipVal_df = pd.DataFrame(sigregions)
    df_cutflow = pd.DataFrame(cutregions)

    ## make signal region yields
    if doCutflow:
        for proc in procs:
            if blind and proc == 'data': continue
            yields = []
            err = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            cutflow_hname=br_hist_prefix+"cutflow_"+proc
            #print sr_hname
            cutflow_hist=getObjFromFile(fname,cutflow_hname)
            for b in range(1,cutflow_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    yields.append(sigWeight*cutflow_hist.GetBinContent(b))
                    err.append(sigWeight*cutflow_hist.GetBinError(b))
                else:
                    yields.append(cutflow_hist.GetBinContent(b))
                    err.append(cutflow_hist.GetBinError(b))
            df_cutflow[proc] = yields
            df_cutflow[proc+" error"] = err
        
        # df_cutflow["S/B"] = (df_cutflow['signal_tch']+df_cutflow['signal_tuh'])/(df_cutflow["fakes_mc"]+df_cutflow["flips_mc"]+df_cutflow["rares"])
        
        # df_cutflow = df_cutflow.drop([5],axis=0)
        # df_cutflow.ix[9],df_cutflow.ix[10],df_cutflow.ix[11],df_cutflow.ix[12] = df_cutflow.ix[12],df_cutflow.ix[9],df_cutflow.ix[10],df_cutflow.ix[11]

        df_cutflow = df_cutflow.fillna("")
        df_cutflow = df_cutflow.round(1)
        writeToLatexFile("tables/cutflow_"+str(year), df_cutflow)
        print df_cutflow

    ## make signal region yields
    if doSRTable:
        for proc in procs:
            if blind and proc == 'data': continue
            yields = []
            err = []
            if "signal" in proc: fname=sighistdir+proc+'_{}_hists.root'.format(year)
            else: fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            sr_hname=br_hist_prefix+"sr_"+proc
            #print sr_hname
            sr_hist=getObjFromFile(fname,sr_hname)
            for b in range(1,sr_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    yields.append(sigWeight*sr_hist.GetBinContent(b))
                    err.append(sigWeight*sr_hist.GetBinError(b))
                else:
                    yields.append(sr_hist.GetBinContent(b))
                    err.append(sr_hist.GetBinError(b))
            df[proc] = yields
            df[proc+" error"] = err

        #to compare to old an: drop 3l and 0b
        # df = df.drop([0,1,2,9,10,11,12,13,14,15,16,17],axis=0)
        # df = df.drop([0,1,2,9,10,11,12],axis=0)

        # df.loc['Total']= df.sum(numeric_only=True, axis=0)
        # df.at["Total", "fakes_mc"] = df["fakes_mc"].sum()
        # df.at["Total", "fakes_mc error"] = round(np.sqrt(df["fakes_mc error"].pow(2).sum()),2)
        # df.loc["Total", "flips_mc"] = df["flips_mc"].sum()
        # df.at["Total", "flips_mc error"] = round(np.sqrt(df["flips_mc error"].pow(2).sum()),2)
        # df.loc["Total", "rares"] = df["rares"].sum()
        # df.at["Total", "rares error"] = round(np.sqrt(df["rares error"].pow(2).sum()),2)
        # df.loc["Total", "signal_tuh"] = df["signal_tuh"].sum()
        # df.at["Total", "signal_tuh error"] = round(np.sqrt(df["signal_tuh error"].pow(2).sum()),2)
        # df.loc["Total", "signal_tch"] = df["signal_tch"].sum()
        # df.at["Total", "signal_tch error"] = round(np.sqrt(df["signal_tch error"].pow(2).sum()),2)

        # df["Total Background"] = df["fakes_mc"]+df["flips_mc"]+df["rares"]
        # df["Total Background error"] = np.sqrt(df["fakes_mc error"]**2+df["flips_mc error"]**2+df["rares error"]**2)
        #df = df[df.nBtags!=0]
        # df["Signal/Background Ratio"] = (df["signal_tuh"] + df["signal_tch"]) / df["Total Background"]
        df = df.fillna("")
        # df = df.round(1)
        writeToLatexFile("tables/SRyields_"+str(year), df)
        #save to txt file for datacards
        outtxt = open(outdir+"tables/"+outtag+"tableMaker_"+str(year)+".txt","w")
        outtxt.write(df.to_csv(index=False))
        outtxt.close()
        print df

    ## make fake CR yields
    if doFakeCR: 
        for proc in procs:
            yields = []
            err = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            histsToAdd = [  "h_sf_fakecr_"+proc,
                            "h_mlsf_fakecr_"+proc,
                            "h_df_fakecr_"+proc,
                            "h_mldf_fakecr_"+proc
                            ]
            #print sr_hname
            cr_hist = r.TH1F("fake_cr"+proc, "fake_cr"+proc, 18, 0.5, 18.5)
            for name in histsToAdd:
                cr_hist.Add(getObjFromFile(fname,name))
            for b in range(1,cr_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    yields.append(sigWeight*cr_hist.GetBinContent(b))
                    err.append(sigWeight*cr_hist.GetBinError(b))
                else:
                    yields.append(cr_hist.GetBinContent(b))
                    err.append(cr_hist.GetBinError(b))
            #print yields
            fake_cr_df[proc] = yields
            fake_cr_df[proc+" error"] = err

        #fake_cr_df.loc['Total']= fake_cr_df.sum(numeric_only=True, axis=0)
        fake_cr_df.at["Total", "fakes_mc"] = fake_cr_df["fakes_mc"].sum()
        fake_cr_df.at["Total", "fakes_mc error"] = round(np.sqrt(fake_cr_df["fakes_mc error"].pow(2).sum()),2)
        fake_cr_df.loc["Total", "flips_mc"] = fake_cr_df["flips_mc"].sum()
        fake_cr_df.at["Total", "flips_mc error"] = round(np.sqrt(fake_cr_df["flips_mc error"].pow(2).sum()),2)
        fake_cr_df.loc["Total", "rares"] = fake_cr_df["rares"].sum()
        fake_cr_df.at["Total", "rares error"] = round(np.sqrt(fake_cr_df["rares error"].pow(2).sum()),2)
        fake_cr_df.loc["Total", "signal_tuh"] = fake_cr_df["signal_tuh"].sum()
        fake_cr_df.at["Total", "signal_tuh error"] = round(np.sqrt(fake_cr_df["signal_tuh error"].pow(2).sum()),2)
        fake_cr_df.loc["Total", "signal_tch"] = fake_cr_df["signal_tch"].sum()
        fake_cr_df.at["Total", "signal_tch error"] = round(np.sqrt(fake_cr_df["signal_tch error"].pow(2).sum()),2)

        fake_cr_df["Total Background"] = fake_cr_df["fakes_mc"]+fake_cr_df["flips_mc"]+fake_cr_df["rares"]
        fake_cr_df["Total Background error"] = np.sqrt(fake_cr_df["fakes_mc error"]**2+fake_cr_df["flips_mc error"]**2+fake_cr_df["rares error"]**2)
        
        fake_cr_df = fake_cr_df.fillna("")
        writeToLatexFile("tables/fakeCRyields_"+str(year), fake_cr_df)
        print fake_cr_df

    ## make fake estimatation tables
    if doFakeEst:
        for proc in procs:
            yields = []
            err = []
            estyields = []
            esterr = []
            ppestyields = []
            ppesterr = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            histsToAdd = [  "h_sf_fakecr_"+proc,
                            "h_mlsf_fakecr_"+proc,
                            # "h_df_fakecr_"+proc,
                            # "h_mldf_fakecr_"+proc
                            ]
            sfEstimationHistsToAdd = [  "h_sfest_fakecr_"+proc,
                                        "h_mlsfest_fakecr_"+proc,
                                        ]
            # sfppEstimationHistsToAdd = [  "h_sfppest_fakecr_"+proc,
            #                               "h_mlsfpppest_fakecr_"+proc,
            #                               #"h_dfppest_fakecr_"+proc,
            #                               #"h_mldfpppest_fakecr_"+proc,
            #                             ]
            dfEstimationHistsToAdd = [  "h_dfest_fakecr_"+proc,
                                        "h_mldfest_fakecr_"+proc
                                        ]

            cr_hist = r.TH1F("fake_cr"+proc, "fake_cr"+proc, 21, 0.5, 21.5)
            sfest_hist = r.TH1F("fake_sfest"+proc, "fake_sfest"+proc, 21, 0.5, 21.5)
            dfest_hist = r.TH1F("fake_dfest"+proc, "fake_dfest"+proc, 21, 0.5, 21.5)
            # sfppest_hist = r.TH1F("fake_sfppest"+proc, "fake_sfppest"+proc, 21, 0.5, 21.5)
            fakeest_hist = r.TH1F("fake_est"+proc, "fake_est"+proc, 21, 0.5, 21.5)
            for name in histsToAdd:
                cr_hist.Add(getObjFromFile(fname,name))
            for h_sf,h_df in zip(sfEstimationHistsToAdd,dfEstimationHistsToAdd):
                sfest_hist.Add(getObjFromFile(fname,h_sf))
                dfest_hist.Add(getObjFromFile(fname,h_df))
                fakeest_hist.Add(getObjFromFile(fname,h_sf))
                fakeest_hist.Add(getObjFromFile(fname,h_df),-1)
            # if proc == "data":
            #     for b in range(1,sfest_hist.GetNbinsX()+1):
            #         print(b, sfest_hist.GetBinContent(b), dfest_hist.GetBinContent(b), dfest_hist.GetBinContent(b)/sfest_hist.GetBinContent(b))
            # for h_sfpp in sfppEstimationHistsToAdd:
            #     sfppest_hist.Add(getObjFromFile(fname,h_sfpp))
            for b in range(1,cr_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    yields.append(sigWeight*cr_hist.GetBinContent(b))
                    err.append(sigWeight*cr_hist.GetBinError(b))
                else:
                    yields.append(cr_hist.GetBinContent(b))
                    err.append(cr_hist.GetBinError(b))
                    # ppestyields.append(sfppest_hist.GetBinContent(b))
                    # ppesterr.append(sfppest_hist.GetBinError(b))
                    if 'data' in proc:
                        #estyields.append(sfest_hist.GetBinContent(b)-dfest_hist.GetBinContent(b))
                        #esterr.append(sqrt(sfest_hist.GetBinError(b)**2+dfest_hist.GetBinError(b)**2))
                        estyields.append(fakeest_hist.GetBinContent(b))
                        esterr.append(fakeest_hist.GetBinError(b))
            #print yields
            fakeEst_df[proc] = yields
            fakeEst_df[proc+" error"] = err
            # if 'rares' in proc:
            #     # print ppestyields
            #     fakeEst_df[proc+" prompt"] = ppestyields
            #     fakeEst_df[proc+" prompt error"] = ppesterr
            if 'data' in proc:
                fakeEst_df[proc+" estimate"] = estyields
                fakeEst_df[proc+" estimate error"] = esterr

        # fakeEst_df["Total Background"] = fakeEst_df["fakes_mc"]+fakeEst_df["flips_mc"]+fakeEst_df["rares"]
        # fakeEst_df["Total Background error"] = np.sqrt(fakeEst_df["fakes_mc error"]**2+fakeEst_df["flips_mc error"]**2+fakeEst_df["rares error"]**2)
        # fakeEst_df= fakeEst_df.drop([   "fakes_mc",
        #                                 "fakes_mc error",
        #                                 "flips_mc",
        #                                 "flips_mc error",
        #                                 "rares",
        #                                 "rares error",
        #                                 "signal_tch",
        #                                 "signal_tch error",
        #                                 "signal_tuh",
        #                                 "signal_tuh error"], axis=1)
        # totmcback = fakeEst_df['Total Background']
        # totmcbackerr = fakeEst_df['Total Background error']
        # fakeEst_df.drop(['Total Background','Total Background error'], axis=1, inplace=True)
        # fakeEst_df.insert(3,"Total Background", totmcback)
        # fakeEst_df.insert(4,"Total Background error", totmcbackerr)

        # fakeEst_df.at["Total", "data"] = fakeEst_df["data"].sum()
        # fakeEst_df.at["Total", "data estimate"] = fakeEst_df["data estimate"].sum()

        # rarespp = fakeEst_df['rares prompt']
        # rarespperr = fakeEst_df['rares prompt error']
        # fakeEst_df.drop(['rares prompt','rares prompt error'], axis=1, inplace=True)
        # fakeEst_df.insert(7,"rares prompt", rarespp)
        # fakeEst_df.insert(8,"rares prompt error", rarespperr)

        # fakeEst_df["Corrected Estimate"] = fakeEst_df["data estimate"] - fakeEst_df["rares prompt"]
        # fakeEst_df["Corrected Estimate error"] = np.sqrt(fakeEst_df["data estimate error"]**2+fakeEst_df["rares prompt error"]**2)

        fakeEst_df = fakeEst_df.fillna("")
        writeToLatexFile("tables/fakeEstyields_"+str(year), fakeEst_df)
        #save to txt file for datacards
        outtxt = open(outdir+"tables/" +outtag+"fakeEstyields_"+str(year)+".txt","w")
        outtxt.write(fakeEst_df.to_csv(index=False))
        outtxt.close()
        print fakeEst_df
    
    ## make fake validation tables
    if doFakeVal:
        for proc in procs:
            if 'fake' not in proc: continue
            sryields = []
            srerr = []
            sfyields = []
            cryields = []
            crerr = []
            crestyields = []
            cresterr = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            srName = "h__vrsr_"+proc
            crName = "h__vrcr_"+proc
            crestName = "h__vrcrest_"+proc
            sr_hist = getObjFromFile(fname, srName)
            cr_hist = getObjFromFile(fname, crName)
            crest_hist = getObjFromFile(fname, crestName)
            for b in range(1,sr_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    continue
                    #yields.append(sigWeight*cr_hist.GetBinContent(b))
                    #err.append(sigWeight*cr_hist.GetBinError(b))
                else:
                    if 'data' in proc: continue
                    sryields.append(sr_hist.GetBinContent(b))
                    srerr.append(sr_hist.GetBinError(b))
                    #sfyields.append(sf_hist.GetBinContent(b))
                    #sferr.append(sf_hist.GetBinError(b))
                    #sfestyields.append(sfest_hist.GetBinContent(b))
                    #sfesterr.append(sfest_hist.GetBinError(b))
                    cryields.append(cr_hist.GetBinContent(b))
                    crerr.append(cr_hist.GetBinError(b))
                    crestyields.append(crest_hist.GetBinContent(b))
                    cresterr.append(crest_hist.GetBinError(b))
            #print sryields
            #print sfyields
            if 'signal' in proc: continue
            if 'data' in proc: continue
            else:
                fakeVal_df[proc+" cr"] = cryields
                fakeVal_df[proc+" cr error"] = crerr
                fakeVal_df[proc+" est"] = crestyields
                fakeVal_df[proc+" est error"] = cresterr
                fakeVal_df[proc+" sr"] = sryields
                fakeVal_df[proc+" sr error"] = srerr
        fakeVal_df = fakeVal_df.fillna("")
        writeToLatexFile("tables/fakeValyields_"+str(year), fakeVal_df)
        print fakeVal_df
    
    ## make flip CR yields
    if doFlipCR: 
        for proc in procs:
            yields = []
            err = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            histsToAdd = [  "h_os_flipcr_"+proc,
                            ]
            #print sr_hname
            cr_hist = getObjFromFile(fname,"h_os_flipcr_"+proc)
            for b in range(1,cr_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    yields.append(sigWeight*cr_hist.GetBinContent(b))
                    err.append(sigWeight*cr_hist.GetBinError(b))
                else:
                    yields.append(cr_hist.GetBinContent(b))
                    err.append(cr_hist.GetBinError(b))
            #print yields
            flip_cr_df[proc] = yields
            flip_cr_df[proc+" error"] = err

        #flip_cr_df.loc['Total']= flip_cr_df.sum(numeric_only=True, axis=0)
        # flip_cr_df.at["Total", "fakes_mc"] = flip_cr_df["fakes_mc"].sum()
        # flip_cr_df.at["Total", "fakes_mc error"] = round(np.sqrt(flip_cr_df["fakes_mc error"].pow(2).sum()),2)
        # flip_cr_df.loc["Total", "flips_mc"] = flip_cr_df["flips_mc"].sum()
        # flip_cr_df.at["Total", "flips_mc error"] = round(np.sqrt(flip_cr_df["flips_mc error"].pow(2).sum()),2)
        # flip_cr_df.loc["Total", "rares"] = flip_cr_df["rares"].sum()
        # flip_cr_df.at["Total", "rares error"] = round(np.sqrt(flip_cr_df["rares error"].pow(2).sum()),2)
        # flip_cr_df.loc["Total", "signal_tuh"] = flip_cr_df["signal_tuh"].sum()
        # flip_cr_df.at["Total", "signal_tuh error"] = round(np.sqrt(flip_cr_df["signal_tuh error"].pow(2).sum()),2)
        # flip_cr_df.loc["Total", "signal_tch"] = flip_cr_df["signal_tch"].sum()
        # flip_cr_df.at["Total", "signal_tch error"] = round(np.sqrt(flip_cr_df["signal_tch error"].pow(2).sum()),2)

        # flip_cr_df["Total Background"] = flip_cr_df["fakes_mc"]+flip_cr_df["flips_mc"]+flip_cr_df["rares"]
        # flip_cr_df["Total Background error"] = np.sqrt(flip_cr_df["fakes_mc error"]**2+flip_cr_df["flips_mc error"]**2+flip_cr_df["rares error"]**2)
        
        flip_cr_df = flip_cr_df.fillna("")
        writeToLatexFile("tables/flipCRyields_"+str(year), flip_cr_df)
        print flip_cr_df

    ## make flip estimatation tables
    if doFlipEst:
        for proc in procs:
            yields = []
            err = []
            estyields = []
            esterr = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            #print sr_hname
            cr_hist = getObjFromFile(fname,"h_os_flipcr_"+proc)
            est_hist = getObjFromFile(fname,"h_osest_flipcr_"+proc)
            for b in range(1,cr_hist.GetNbinsX()+1):
                if 'signal' in proc:
                    yields.append(sigWeight*cr_hist.GetBinContent(b))
                    err.append(sigWeight*cr_hist.GetBinError(b))
                else:
                    yields.append(cr_hist.GetBinContent(b))
                    err.append(cr_hist.GetBinError(b))
                    if 'data' in proc:
                        estyields.append(est_hist.GetBinContent(b))
                        esterr.append(est_hist.GetBinError(b))
            #print yields
            flipEst_df[proc] = yields
            flipEst_df[proc+" error"] = err
            if 'data' in proc:
                flipEst_df[proc+" estimate"] = estyields
                flipEst_df[proc+" estimate error"] = esterr

        # flipEst_df["Total Background"] = flipEst_df["fakes_mc"]+flipEst_df["flips_mc"]+flipEst_df["rares"]
        # flipEst_df["Total Background error"] = np.sqrt(flipEst_df["fakes_mc error"]**2+flipEst_df["flips_mc error"]**2+flipEst_df["rares error"]**2)
        # flipEst_df= flipEst_df.drop([   "fakes_mc",
        #                                 "fakes_mc error",
        #                                 "flips_mc",
        #                                 "flips_mc error",
        #                                 "rares",
        #                                 "rares error",
        #                                 "signal_tch",
        #                                 "signal_tch error",
        #                                 "signal_tuh",
        #                                 "signal_tuh error"], axis=1)
        # totmcback = flipEst_df['Total Background']
        # totmcbackerr = flipEst_df['Total Background error']
        # flipEst_df.drop(['Total Background','Total Background error'], axis=1, inplace=True)
        # flipEst_df.insert(3,"Total Background", totmcback)
        # flipEst_df.insert(4,"Total Background error", totmcbackerr)
        flipEst_df = flipEst_df.fillna("")
        writeToLatexFile("tables/flipEstyields_"+str(year), flipEst_df)
        #save to txt file for datacards
        outtxt = open(outdir+"tables/"+outtag+"flipEstyields_"+str(year)+".txt","w")
        outtxt.write(flipEst_df.to_csv(index=False))
        outtxt.close()
        print flipEst_df
    
    ## make flip validation tables
    if doFlipVal:
        for proc in procs:
            #if 'flip' not in proc: continue
            sryields = []
            srerr = []
            cryields = []
            crerr = []
            crestyields = []
            cresterr = []
            fname=histdir+proc+'_{}_hists.root'.format(year)
            print fname
            srName = "h_vrsr_flip_valSR_flip_"+proc
            crName = "h_vrcr_flip_valCR_flip_"+proc
            crestName = "h_vrcrest_flip_valCRest_flip_"+proc
            sr_hist = getObjFromFile(fname, srName)
            cr_hist = getObjFromFile(fname, crName)
            crest_hist = getObjFromFile(fname, crestName)
            for b in range(1,sr_hist.GetNbinsX()+1):
                if 'signal' in proc: continue
                    #yields.append(sigWeight*cr_hist.GetBinContent(b))
                    #err.append(sigWeight*cr_hist.GetBinError(b))
                else:
                    if 'data' in proc: continue
                    sryields.append(sr_hist.GetBinContent(b))
                    srerr.append(sr_hist.GetBinError(b))
                    cryields.append(cr_hist.GetBinContent(b))
                    crerr.append(cr_hist.GetBinError(b))
                    crestyields.append(crest_hist.GetBinContent(b))
                    cresterr.append(crest_hist.GetBinError(b))
            if 'signal' in proc: continue
            if 'data' in proc: continue
            else:
                flipVal_df[proc+" cr"] = cryields
                flipVal_df[proc+" cr error"] = crerr
                flipVal_df[proc+" est"] = crestyields
                flipVal_df[proc+" est error"] = cresterr
                flipVal_df[proc+" sr"] = sryields
                flipVal_df[proc+" sr error"] = srerr
        flipVal_df = flipVal_df.loc[:, (flipVal_df != 0).any(axis=0)]
        flipVal_df = flipVal_df.fillna("")
        writeToLatexFile("tables/flipValyields_"+str(year), flipVal_df)
        print flipVal_df
