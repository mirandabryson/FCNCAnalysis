import numpy as np
import ROOT as r
r.TH1F.SetDefaultSumw2()

#years=[2016,2017,2018]
#procs=['fakes_mc','flips_mc','rares']
years=[2016]
procs=['fakes_mc']

sr_hist_prefix='h_br_sr_'
histdir='outputs/'

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

yields={}
for proc in procs:
    if proc not in yields: yields[proc] = {}
    for year in years:
        fname=histdir+proc+'_{}_hists.root'.format(year)
        hname=sr_hist_prefix+proc
        hist=getObjFromFile(fname,hname)
        yields[proc:year]=np.array([hist.GetArray().GetArray()])
        print '{} {}:'.format(proc,year), yields[proc:year]
