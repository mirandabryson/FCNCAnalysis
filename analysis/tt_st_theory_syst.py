#import some useful packages
import ROOT as r
import time
import numpy as np
import sys
import pandas as pd
import os
import json


#flat uncertainties we're applying
tt_unc = [1.056, 0.939]
st_unc = [1.3, 0.7]

#lists to loop through
years = ["2016", "2017", "2018"]
couplings = ["tch","tuh"]
ccbins = [  "l2_j2_b0","l2_j3_b0","l2_j4_b0",
            "l2_j2_b1","l2_j3_b1","l2_j4_b1",
            "l2_j2_b2","l2_j3_b2","l2_j4_b2",
            "l3_j1_b0","l3_j2_b0","l3_j3_b0","l3_j4_b0",
            "l3_j1_b1","l3_j2_b1","l3_j3_b1","l3_j4_b1",
            "l3_j1_b2","l3_j2_b2","l3_j3_b2","l3_j4_b2",
            ]
srbins = ["bin_"+str(x) for x in range(20)]

isBDT = 0
isCC = 0

def calculate_total_unc_asymmetric(yield_tt, yield_st, verbose=False):
    #raw_unc_up = (tt_unc[0] * yield_tt) + (st_unc[0] * yield_st)
    #raw_unc_down = (tt_unc[1] * yield_tt) + (st_unc[1] * yield_st)

    raw_unc_up_tt = tt_unc[0] * yield_tt
    raw_unc_down_tt = tt_unc[1] * yield_tt
    raw_unc_up_st = st_unc[0] * yield_st
    raw_unc_down_st = st_unc[1] * yield_st

    unc_up_tt = (raw_unc_up_tt + yield_st) / (yield_tt + yield_st)
    unc_down_tt = (raw_unc_down_tt + yield_st) / (yield_tt + yield_st)
    unc_up_st = (raw_unc_up_st + yield_tt) / (yield_tt + yield_st)
    unc_down_st = (raw_unc_down_st + yield_tt) / (yield_tt + yield_st) 

    unc_up = ( (abs(1-unc_up_tt)**2) + (abs(1-unc_up_st)**2) )**(0.5)
    unc_down = ( (abs(1-unc_down_tt)**2) + (abs(1-unc_down_st)**2) )**(0.5)

    print "The fractional uncertainty in yield due to tt (st) is %.3f/%.3f (%.3f/%.3f)" % (unc_up_tt, unc_down_tt, unc_up_st, unc_down_st)

    return unc_up, unc_down

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

uncertainties = {}
for y in years:
    uncertainties[y] = {}
    for c in couplings:
        uncertainties[y][c] = {}
        if("tch" in c): altSig = "hct"
        else: altSig = "hut"
        
        tt_file = "./outputs/nov30_bdtTTonly/signal_{0}_{1}_hists.root".format(c,y)
        st_file = "./outputs/nov30_bdtSTonly/signal_{0}_{1}_hists.root".format(c,y)

        # tt_hist = getObjFromFile(tt_file, "h_br_sr_signal_{0}".format(c))
        # st_hist = getObjFromFile(st_file, "h_br_sr_signal_{0}".format(c))

        tt_hist = getObjFromFile(tt_file, "h_br_bdtScore_{0}{1}_signal_{2}".format(altSig,y,c))
        st_hist = getObjFromFile(st_file, "h_br_bdtScore_{0}{1}_signal_{2}".format(altSig,y,c))
        it = 0
        for b in range(1,tt_hist.GetNbinsX()+1):
            up,down = calculate_total_unc_asymmetric(tt_hist.GetBinContent(b),st_hist.GetBinContent(b))
            print(up,down)

            uncertainties[y][c][srbins[it]] = {"up":1+up,"down":1-down}
            it+=1

with open("./datacards/bdt_fcnc_individual_uncs.json", "w") as f_out:
    json.dump(uncertainties, f_out, sort_keys=True, indent=4)
