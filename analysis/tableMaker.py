import numpy as np
import ROOT as r
import pandas as pd
import glob
import os
r.TH1F.SetDefaultSumw2()
pd.set_option('display.float_format', lambda x: '%.5f' % x)

years=[2016,2017,2018]
procs=['signal_tch','signal_tuh','fakes_mc','flips_mc','rares','data']
sigWeight = 0.01
#years=[2016]
#procs=['fakes_mc']
blind = True

ml_hist_prefix='h_ml_'
ss_hist_prefix='h_ss_'
br_hist_prefix='h_br_'
sf_hist_prefix='h_sf_'
sfest_hist_prefix='h_sfest_'
df_hist_prefix='h_df_'
dfest_hist_prefix='h_dfest_'
basepath = os.path.realpath(__file__)
basepath = basepath.replace("tableMaker.py","")
#histdir=basepath+'outputs/jun14_allMC_estimate/'
histdir=basepath+'outputs/'
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

for year in years:
    sigregions =    {   
                        "nBtags": [0,0,0,1,1,1,2,2,2,0,0,0,1,1,1,2,2,2],
                        "nJets": [2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4],
                        "nLeptons": [2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3],
                    }
    invsigregions =    {   
                        "nBtags": [0,0,0,1,1,1,2,2,2,0,0,0,1,1,1,2,2,2],
                        "nJets": [2,3,4,2,3,4,2,3,4,2,3,4,2,3,4,2,3,4],
                        "nLeptons": [3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2],
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
    fake_cr_df = pd.DataFrame(sigregions)
    fakeEstsf_df = pd.DataFrame(sigregions)
    fakeVal_df = pd.DataFrame(sigregions)
    fakeEstdf_df = pd.DataFrame(sigregions)
    flipEst_df = pd.DataFrame(flipsregions)

    ## make signal region yields
    for proc in procs:
        if blind and proc == 'data': continue
        yields = []
        err = []
        fname=histdir+proc+'_{}_hists.root'.format(year)
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

    df["Total Background"] = df["fakes_mc"]+df["flips_mc"]+df["rares"]
    df["Total Background error"] = np.sqrt(df["fakes_mc error"]**2+df["flips_mc error"]**2+df["rares error"]**2)
    
    df = df.fillna("")
    print df

    ## make fake CR yields
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
    print fake_cr_df


    ## make fake estimatation tables
    for proc in procs:
        yields = []
        err = []
        estyields = []
        esterr = []
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        histsToAdd = [  "h_sf_fakecr_"+proc,
                        "h_mlsf_fakecr_"+proc,
                        "h_df_fakecr_"+proc,
                        "h_mldf_fakecr_"+proc
                        ]
        sfEstimationHistsToAdd = [  "h_sfest_fakecr_"+proc,
                                    "h_mlsfest_fakecr_"+proc,
                                    ]
        dfEstimationHistsToAdd = [  "h_dfest_fakecr_"+proc,
                                    "h_mldfest_fakecr_"+proc
                                    ]
        #print sr_hname
        cr_hist = r.TH1F("fake_cr"+proc, "fake_cr"+proc, 18, 0.5, 18.5)
        sfest_hist = r.TH1F("fake_sfest"+proc, "fake_sfest"+proc, 18, 0.5, 18.5)
        dfest_hist = r.TH1F("fake_dfest"+proc, "fake_dfest"+proc, 18, 0.5, 18.5)
        fakeest_hist = r.TH1F("fake_est"+proc, "fake_est"+proc, 18, 0.5, 18.5)
        for name in histsToAdd:
            cr_hist.Add(getObjFromFile(fname,name))
        for h_sf,h_df in zip(sfEstimationHistsToAdd,dfEstimationHistsToAdd):
            sfest_hist.Add(getObjFromFile(fname,h_sf))
            dfest_hist.Add(getObjFromFile(fname,h_df))
            fakeest_hist.Add(getObjFromFile(fname,h_sf))
            fakeest_hist.Add(getObjFromFile(fname,h_df),-1)
        for b in range(1,cr_hist.GetNbinsX()+1):
            if 'signal' in proc:
                yields.append(sigWeight*cr_hist.GetBinContent(b))
                err.append(sigWeight*cr_hist.GetBinError(b))
            else:
                yields.append(cr_hist.GetBinContent(b))
                err.append(cr_hist.GetBinError(b))
                if 'data' in proc:
                    #estyields.append(sfest_hist.GetBinContent(b)-dfest_hist.GetBinContent(b))
                    #esterr.append(sqrt(sfest_hist.GetBinError(b)**2+dfest_hist.GetBinError(b)**2))
                    estyields.append(fakeest_hist.GetBinContent(b))
                    esterr.append(fakeest_hist.GetBinError(b))
        #print yields
        fakeEstsf_df[proc] = yields
        fakeEstsf_df[proc+" error"] = err
        if 'data' in proc:
            fakeEstsf_df[proc+" estimate"] = estyields
            fakeEstsf_df[proc+" estimate error"] = esterr

    fakeEstsf_df["Total Background"] = fakeEstsf_df["fakes_mc"]+fakeEstsf_df["flips_mc"]+fakeEstsf_df["rares"]
    fakeEstsf_df["Total Background error"] = np.sqrt(fakeEstsf_df["fakes_mc error"]**2+fakeEstsf_df["flips_mc error"]**2+fakeEstsf_df["rares error"]**2)
    fakeEstsf_df= fakeEstsf_df.drop([   "fakes_mc",
                                        "fakes_mc error",
                                        "flips_mc",
                                        "flips_mc error",
                                        "rares",
                                        "rares error",
                                        "signal_tch",
                                        "signal_tch error",
                                        "signal_tuh",
                                        "signal_tuh error"], axis=1)
    totmcback = fakeEstsf_df['Total Background']
    totmcbackerr = fakeEstsf_df['Total Background error']
    fakeEstsf_df.drop(['Total Background','Total Background error'], axis=1, inplace=True)
    fakeEstsf_df.insert(3,"Total Background", totmcback)
    fakeEstsf_df.insert(4,"Total Background error", totmcbackerr)
    fakeEstsf_df = fakeEstsf_df.fillna("")
    print fakeEstsf_df
    


    ## make fake validation tables
    for proc in procs:
        if 'fake' not in proc: continue
        sryields = []
        srerr = []
        sfyields = []
        sferr = []
        sfestyields = []
        sfesterr = []
        cryields = []
        crerr = []
        crestyields = []
        cresterr = []
        fname=histdir+proc+'_{}_hists.root'.format(year)
        print fname
        srHistosToAdd = [   "h_vrsr_ss_vrsr_"+proc,
                            "h_vrsr_ml_vrsr_"+proc
                        ]
        sfHistosToAdd = [   "h_vrcr_sf_vrcr_"+proc,
                            "h_vrcr_mlsf_vrcr_"+proc
                        ]
        dfHistosToAdd = [   "h_vrcr_df_vrcr_"+proc,
                            "h_vrcr_mldf_vrcr_"+proc
                        ]
        sfEstHistos =   [   "h_vrcr_sfest_vrcr_"+proc,
                            "h_vrcr_mlsfest_vrcr_"+proc,
                        ]
        dfEstHistos =   [   "h_vrcr_dfest_vrcr_"+proc,
                            "h_vrcr_mldfest_vrcr_"+proc,
                        ]
        #print sr_hname
        sr_hist = r.TH1F("fake_vrsr"+proc, "fake_vrsr"+proc, 18, 0.5, 18.5)
        sf_hist = r.TH1F("fake_vrcr_sf"+proc, "fake_vrcr_sf"+proc, 18, 0.5, 18.5)
        df_hist = r.TH1F("fake_vrcr_df"+proc, "fake_vrcr_df"+proc, 18, 0.5, 18.5)
        sfest_hist = r.TH1F("fake_vrcr_sfest"+proc, "fake_vrcr_sfest"+proc, 18, 0.5, 18.5)
        dfest_hist = r.TH1F("fake_vrcr_dfest"+proc, "fake_vrcr_dfest"+proc, 18, 0.5, 18.5)
        cr_hist = r.TH1F("fake_vrcr"+proc, "fake_vrcr"+proc, 18, 0.5, 18.5)
        crest_hist = r.TH1F("fake_vrcrest"+proc, "fake_vrcrest"+proc, 18, 0.5, 18.5)
        for srname in srHistosToAdd:
            #print srname
            sr_hist.Add(getObjFromFile(fname,srname))
        for h_sf,h_df in zip(sfHistosToAdd,dfHistosToAdd):
            #print h_sf, h_df
            sf_hist.Add(getObjFromFile(fname,h_sf))
            df_hist.Add(getObjFromFile(fname,h_df))
            cr_hist.Add(getObjFromFile(fname,h_sf))
            cr_hist.Add(getObjFromFile(fname,h_df))
        for h_sfest,h_dfest in zip(sfEstHistos,dfEstHistos):
            sfest_hist.Add(getObjFromFile(fname,h_sfest))
            dfest_hist.Add(getObjFromFile(fname,h_dfest))
            crest_hist.Add(getObjFromFile(fname,h_sfest))
            crest_hist.Add(getObjFromFile(fname,h_dfest),-1)
        for b in range(1,sr_hist.GetNbinsX()+1):
            if 'signal' in proc:
                continue
                #yields.append(sigWeight*cr_hist.GetBinContent(b))
                #err.append(sigWeight*cr_hist.GetBinError(b))
            else:
                if 'data' in proc: continue
                sryields.append(sr_hist.GetBinContent(b))
                srerr.append(sr_hist.GetBinError(b))
                sfyields.append(sf_hist.GetBinContent(b))
                sferr.append(sf_hist.GetBinError(b))
                sfestyields.append(sfest_hist.GetBinContent(b))
                sfesterr.append(sfest_hist.GetBinError(b))
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
    print fakeVal_df



    






    # for proc in procs:
    #     yields = []
    #     err = []
    #     fname=histdir+proc+'_{}_hists.root'.format(year)
    #     print fname
    #     sf_hname="h_sf_nbjets_"+proc
    #     mlsf_hname="h_mlsf_nbjets_"+proc
    #     sf_hist=getObjFromFile(fname,sf_hname)
    #     mlsf_hist=getObjFromFile(fname,mlsf_hname)
    #     dlyld = 0
    #     mlyld = 0
    #     dlerr = 0
    #     mlerr = 0
    #     for b in range(3,sf_hist.GetNbinsX()+2):
    #         dlyld += sf_hist.GetBinContent(b)
    #         mlyld += mlsf_hist.GetBinContent(b)
    #         dlerr = np.sqrt(dlerr**2 + sf_hist.GetBinError(b))
    #         mlerr = np.sqrt(mlerr**2 + mlsf_hist.GetBinError(b))
    #     yields.append(sf_hist.GetBinContent(1))
    #     yields.append(sf_hist.GetBinContent(2))
    #     yields.append(dlyld)
    #     yields.append(mlsf_hist.GetBinContent(1))
    #     yields.append(mlsf_hist.GetBinContent(2))
    #     yields.append(mlyld)
    #     err.append(np.sqrt(sf_hist.GetBinError(1)**2))
    #     err.append(np.sqrt(sf_hist.GetBinError(2)**2))
    #     err.append(dlerr)
    #     err.append(np.sqrt(mlsf_hist.GetBinError(1)**2))
    #     err.append(np.sqrt(mlsf_hist.GetBinError(2)**2))
    #     err.append(mlerr)
    #     fakeEstsf_df[proc] = yields
    #     fakeEstsf_df[proc+" error"] = err

    # fakeEstsf_df["Total Background"] = fakeEstsf_df["fakes_mc"]+fakeEstsf_df["flips_mc"]+fakeEstsf_df["rares"]
    # fakeEstsf_df["Total Background error"] = np.sqrt(fakeEstsf_df["fakes_mc error"]**2+fakeEstsf_df["flips_mc error"]**2+fakeEstsf_df["rares error"]**2)
    # sfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_sfest_nbjets_data")
    # mlsfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_mlsfest_nbjets_data")
    # column = []
    # err = []
    # dlyld = 0
    # mlyld = 0
    # dlerr = 0
    # mlerr = 0
    # for b in range(3,sfest_hist.GetNbinsX()+2):
    #     dlyld += sfest_hist.GetBinContent(b)
    #     mlyld += mlsfest_hist.GetBinContent(b)
    #     dlerr = np.sqrt(dlerr**2 + sfest_hist.GetBinError(b)**2)
    #     mlerr = np.sqrt(mlerr**2 + mlsfest_hist.GetBinError(b)**2)
    # column.append(sfest_hist.GetBinContent(1))
    # column.append(sfest_hist.GetBinContent(2))
    # column.append(dlyld)
    # column.append(mlsfest_hist.GetBinContent(1))
    # column.append(mlsfest_hist.GetBinContent(2))
    # column.append(mlyld)
    # err.append(np.sqrt(sfest_hist.GetBinError(1)**2))
    # err.append(np.sqrt(sfest_hist.GetBinError(2)**2))
    # err.append(dlerr)
    # err.append(np.sqrt(mlsfest_hist.GetBinError(1)**2))
    # err.append(np.sqrt(mlsfest_hist.GetBinError(2)**2))
    # err.append(mlerr)
    # fakeEstsf_df["Estimated Fakes"] = column
    # fakeEstsf_df["Estimated Fakes error"] = err
    # ss_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ss_nbjets_fakes_mc")
    # ml_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ml_nbjets_fakes_mc")
    # column = []
    # err = []
    # dlyld = 0
    # mlyld = 0
    # dlerr = 0
    # mlerr = 0
    # for b in range(3,ss_hist.GetNbinsX()+2):
    #     dlyld += ss_hist.GetBinContent(b)
    #     mlyld += ml_hist.GetBinContent(b)
    #     dlerr = np.sqrt(dlerr**2 + ss_hist.GetBinError(b)**2)
    #     mlerr = np.sqrt(mlerr**2 + ml_hist.GetBinError(b)**2)
    # column.append(ss_hist.GetBinContent(1))
    # column.append(ss_hist.GetBinContent(2))
    # column.append(dlyld)
    # column.append(ml_hist.GetBinContent(1))
    # column.append(ml_hist.GetBinContent(2))
    # column.append(mlyld)
    # err.append(ss_hist.GetBinError(1))
    # err.append(ss_hist.GetBinError(2))
    # err.append(dlerr)
    # err.append(ml_hist.GetBinError(1))
    # err.append(ml_hist.GetBinError(2))
    # err.append(mlerr)
    # fakeEstsf_df["SR fakes"] = column
    # fakeEstsf_df["SR error"] = err
    # fakeEstsf_df = fakeEstsf_df.drop(["signal_tch","signal_tch error","signal_tuh","signal_tuh error","fakes_mc","fakes_mc error","flips_mc","flips_mc error","rares","rares error"],axis=1)
    # print fakeEstsf_df



    # for proc in procs:
    #     yields = []
    #     err = []
    #     fname=histdir+proc+'_{}_hists.root'.format(year)
    #     print fname
    #     df_hname="h_df_nbjets_"+proc
    #     mldf_hname="h_mldf_nbjets_"+proc
    #     df_hist=getObjFromFile(fname,df_hname)
    #     mldf_hist=getObjFromFile(fname,mldf_hname)
    #     dlyld = 0
    #     mlyld = 0
    #     dlerr = 0
    #     mlerr = 0
    #     for b in range(3,df_hist.GetNbinsX()+2):
    #         dlyld += df_hist.GetBinContent(b)
    #         mlyld += mldf_hist.GetBinContent(b)
    #         dlerr = np.sqrt(dlerr**2 + df_hist.GetBinError(b)**2)
    #         mlerr = np.sqrt(mlerr**2 + mldf_hist.GetBinError(b)**2)
    #     yields.append(df_hist.GetBinContent(1))
    #     yields.append(df_hist.GetBinContent(2))
    #     yields.append(dlyld)
    #     yields.append(mldf_hist.GetBinContent(1))
    #     yields.append(mldf_hist.GetBinContent(2))
    #     yields.append(mlyld)
    #     err.append(np.sqrt(df_hist.GetBinError(1)**2))
    #     err.append(np.sqrt(df_hist.GetBinError(2)**2))
    #     err.append(dlerr)
    #     err.append(np.sqrt(mldf_hist.GetBinError(1)**2))
    #     err.append(np.sqrt(mldf_hist.GetBinError(2)**2))
    #     err.append(mlerr)
    #     fakeEstdf_df[proc] = yields
    #     fakeEstdf_df[proc+" error"] = err

    # fakeEstdf_df["Total Background"] = fakeEstdf_df["fakes_mc"]+fakeEstdf_df["flips_mc"]+fakeEstdf_df["rares"]
    # fakeEstdf_df["Total Background error"] = np.sqrt(fakeEstdf_df["fakes_mc error"]**2+fakeEstdf_df["flips_mc error"]**2+fakeEstdf_df["rares error"]**2)
    # dfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_dfest_nbjets_data")
    # mldfest_hist=getObjFromFile(histdir+'data_{}_hists.root'.format(year),"h_mldfest_nbjets_data")
    # column = []
    # err = []
    # dlyld = 0
    # mlyld = 0
    # dlerr = 0
    # mlerr = 0
    # for b in range(3,dfest_hist.GetNbinsX()+2):
    #     dlyld += dfest_hist.GetBinContent(b)
    #     mlyld += mldfest_hist.GetBinContent(b)
    #     dlerr = np.sqrt(dlerr**2 + dfest_hist.GetBinError(b)**2)
    #     mlerr = np.sqrt(mlerr**2 + mldfest_hist.GetBinError(b)**2)
    # column.append(dfest_hist.GetBinContent(1))
    # column.append(dfest_hist.GetBinContent(2))
    # column.append(dlyld)
    # column.append(mldfest_hist.GetBinContent(1))
    # column.append(mldfest_hist.GetBinContent(2))
    # column.append(mlyld)
    # err.append(np.sqrt(dfest_hist.GetBinError(1)**2))
    # err.append(np.sqrt(dfest_hist.GetBinError(2)**2))
    # err.append(dlerr)
    # err.append(np.sqrt(mldfest_hist.GetBinError(1)**2))
    # err.append(np.sqrt(mldfest_hist.GetBinError(2)**2))
    # err.append(mlerr)
    # fakeEstdf_df["Estimated Fakes"] = column
    # fakeEstdf_df["Estimated Fakes error"] = err
    # ss_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ss_nbjets_fakes_mc")
    # ml_hist=getObjFromFile(histdir+'fakes_mc_{}_hists.root'.format(year),"h_ml_nbjets_fakes_mc")
    # column = []
    # err = []
    # dlyld = 0
    # mlyld = 0
    # dlerr = 0
    # mlerr = 0
    # for b in range(3,ss_hist.GetNbinsX()+2):
    #     dlyld += ss_hist.GetBinContent(b)
    #     mlyld += ml_hist.GetBinContent(b)
    #     dlerr = np.sqrt(dlerr**2 + ss_hist.GetBinError(b)**2)
    #     mlerr = np.sqrt(mlerr**2 + ml_hist.GetBinError(b)**2)
    # column.append(ss_hist.GetBinContent(1))
    # column.append(ss_hist.GetBinContent(2))
    # column.append(dlyld)
    # column.append(ml_hist.GetBinContent(1))
    # column.append(ml_hist.GetBinContent(2))
    # column.append(mlyld)
    # err.append(ss_hist.GetBinError(1))
    # err.append(ss_hist.GetBinError(2))
    # err.append(dlerr)
    # err.append(ml_hist.GetBinError(1))
    # err.append(ml_hist.GetBinError(2))
    # err.append(mlerr)
    # fakeEstdf_df["SR fakes"] = column
    # fakeEstdf_df["SR error"] = err
    # fakeEstdf_df = fakeEstdf_df.drop(["signal_tch","signal_tch error","signal_tuh","signal_tuh error","fakes_mc","fakes_mc error","flips_mc","flips_mc error","rares","rares error"],axis=1)
    # print fakeEstdf_df







    # for proc in procs:
    #     yields = []
    #     err = []
    #     fname=histdir+proc+'_{}_hists.root'.format(year)
    #     print fname
    #     os_hname="h_os_nbjets_"+proc
    #     os_hist=getObjFromFile(fname,os_hname)
    #     yld = 0
    #     error = 0
    #     for b in range(3,os_hist.GetNbinsX()+2):
    #         yld += os_hist.GetBinContent(b)
    #         error = np.sqrt(error**2 + os_hist.GetBinError(b)**2)
    #     yields.append(os_hist.GetBinContent(1))
    #     yields.append(os_hist.GetBinContent(2))
    #     yields.append(yld)
    #     err.append(os_hist.GetBinError(1))
    #     err.append(os_hist.GetBinError(2))
    #     err.append(error)
    #     flipEst_df[proc] = yields
    #     flipEst_df[proc+" error"] = err

    # flipEst_df["Total Background"] = flipEst_df["fakes_mc"]+flipEst_df["flips_mc"]+flipEst_df["rares"]
    # flipEst_df["Total Background error"] = np.sqrt(flipEst_df["fakes_mc error"]**2+flipEst_df["flips_mc error"]**2+flipEst_df["rares error"]**2)
    # osest_hist=getObjFromFile(histdir+'flips_mc_{}_hists.root'.format(year),"h_osest_nbjets_flips_mc")
    # column = []
    # err = []
    # yld = 0
    # error = 0
    # for b in range(3,osest_hist.GetNbinsX()+2):
    #     yld += osest_hist.GetBinContent(b)
    #     error = np.sqrt(error**2 + osest_hist.GetBinError(b)**2)
    # column.append(osest_hist.GetBinContent(1))
    # column.append(osest_hist.GetBinContent(2))
    # column.append(yld)
    # err.append(osest_hist.GetBinError(1))
    # err.append(osest_hist.GetBinError(2))
    # err.append(error)
    # flipEst_df["Estimated Flips"] = column
    # flipEst_df["Estimated Flips error"] = err
    # ss_hist=getObjFromFile(histdir+'flips_mc_{}_hists.root'.format(year),"h_ss_nbjets_flips_mc")
    # #ml_hist=getObjFromFile(histdir+'_flips_mc_{}_hists.root'.format(year),"h_ml_nbjets_flips_mc")
    # column = []
    # err = []
    # dlyld = 0
    # mlyld = 0
    # dlerr = 0
    # mlerr = 0
    # for b in range(3,ss_hist.GetNbinsX()+2):
    #     dlyld += ss_hist.GetBinContent(b)
    #     #mlyld += ml_hist.GetBinContent(b)
    #     dlerr = np.sqrt(dlerr**2 + ss_hist.GetBinError(b)**2)
    #     #mlerr = np.sqrt(mlerr**2 + ml_hist.GetBinError(b)**2)
    # column.append(ss_hist.GetBinContent(1))
    # column.append(ss_hist.GetBinContent(2))
    # column.append(dlyld)
    # #column.append(ml_hist.GetBinContent(1))
    # #column.append(ml_hist.GetBinContent(2))
    # #column.append(mlyld)
    # err.append(ss_hist.GetBinError(1))
    # err.append(ss_hist.GetBinError(2))
    # err.append(dlerr)
    # #err.append(ml_hist.GetBinError(1))
    # #err.append(ml_hist.GetBinError(2))
    # #err.append(mlerr)
    # flipEst_df["SR flips"] = column
    # flipEst_df["SR error"] = err
    # print flipEst_df


    #save as tex files
    outtxt = open(outdir+"tables/tableMaker_"+str(year)+".txt","w")
    outtxt.write(df.to_csv())
    outFile = open(outdir+"tables/tableMaker_"+str(year)+".tex","w")
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


    outFile = open(outdir+"tables/fakeCR_"+str(year)+".tex","w")
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
    outFile.write(fake_cr_df.to_latex())
    #outFile.write("\end{preview} \n")
    outFile.write("\end{document} \n")
    #outFile.write("\end{document}")
    #outFile.write("\n")
    outFile.close()
    #print(df.to_latex())


    outFile = open(outdir+"tables/fakeEstsf_"+str(year)+".tex","w")
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


    outFile = open(outdir+"tables/fakeVal_"+str(year)+".tex","w")
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
    outFile.write(fakeVal_df.to_latex())
    #outFile.write("\end{preview} \n")
    outFile.write("\end{document} \n")
    #outFile.write("\end{document}")
    #outFile.write("\n")
    outFile.close()
    #print(df.to_latex())
