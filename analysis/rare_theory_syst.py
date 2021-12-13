#import some useful packages
import ROOT as r
import time
import numpy as np
import sys
import pandas as pd
import os
import json


#flat uncertainties we're applying
# wz_unc = [1.10, 0.90]
# qqww_unc = [1.10, 0.90]
# ttw_unc = [1.15, 0.85]
# ttz_unc = [1.15, 0.85]
# other_unc = [1.25, 0.75]

wz_unc = [1.05, 0.95]
qqww_unc = [1.1, 0.9]
ttw_unc = [1.12, 0.88]
ttz_unc = [1.08, 0.92]
other_unc = [1.25, 0.75]

# wz_unc = [1.50, 0.5]
# qqww_unc = [1.50, 0.5]
# ttw_unc = [1.50, 0.5]
# ttz_unc = [1.50, 0.5]
# other_unc = [1.25, 0.75]

#lists to loop through
years = ["2016", "2017", "2018"]
# years = ["2016","2017"]
couplings = ["tch","tuh"]
ccbins = [  "l2_j2_b0","l2_j3_b0","l2_j4_b0",
            "l2_j2_b1","l2_j3_b1","l2_j4_b1",
            "l2_j2_b2","l2_j3_b2","l2_j4_b2",
            "l3_j1_b0","l3_j2_b0","l3_j3_b0","l3_j4_b0",
            "l3_j1_b1","l3_j2_b1","l3_j3_b1","l3_j4_b1",
            "l3_j1_b2","l3_j2_b2","l3_j3_b2","l3_j4_b2",
            ]
bdtbins = ["bin_"+str(x) for x in range(20)]

doBDT = 0
doCC = 1

if doBDT:
    srbins = bdtbins
    inputdir = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/dec3_raresByProcess/"
if doCC:
    srbins = ccbins
    inputdir = "/home/users/ksalyer/FCNCAnalysis/analysis/outputs/dec3_CC_raresByProcess/"

def calculate_total_unc_asymmetric(yield_wz, yield_ttw, yield_qqww, yield_ttz, yield_other, verbose=False):
    #raw_unc_up = (tt_unc[0] * yield_tt) + (st_unc[0] * yield_st)
    #raw_unc_down = (tt_unc[1] * yield_tt) + (st_unc[1] * yield_st)

    raw_unc_up_wz = wz_unc[0] * yield_wz
    raw_unc_down_wz = wz_unc[1] * yield_wz
    raw_unc_up_ttw = ttw_unc[0] * yield_ttw
    raw_unc_down_ttw = ttw_unc[1] * yield_ttw
    raw_unc_up_qqww = qqww_unc[0] * yield_qqww
    raw_unc_down_qqww = qqww_unc[1] * yield_qqww
    raw_unc_up_ttz = ttz_unc[0] * yield_ttz
    raw_unc_down_ttz = ttz_unc[1] * yield_ttz
    raw_unc_up_other = other_unc[0] * yield_other
    raw_unc_down_other = other_unc[1] * yield_other

    yield_all = yield_wz + yield_ttw + yield_qqww + yield_ttz + yield_other

    unc_up_wz = (raw_unc_up_wz + (yield_all-yield_wz)) / (yield_all)
    unc_down_wz = (raw_unc_down_wz + (yield_all-yield_wz)) / (yield_all)
    unc_up_ttw = (raw_unc_up_ttw + (yield_all-yield_ttw)) / (yield_all)
    unc_down_ttw = (raw_unc_down_ttw + (yield_all-yield_ttw)) / (yield_all)
    unc_up_qqww = (raw_unc_up_qqww + (yield_all-yield_qqww)) / (yield_all)
    unc_down_qqww = (raw_unc_down_qqww + (yield_all-yield_qqww)) / (yield_all)
    unc_up_ttz = (raw_unc_up_ttz + (yield_all-yield_ttz)) / (yield_all)
    unc_down_ttz = (raw_unc_down_ttz + (yield_all-yield_ttz)) / (yield_all)
    unc_up_other = (raw_unc_up_other + (yield_all-yield_other)) / (yield_all)
    unc_down_other = (raw_unc_down_other + (yield_all-yield_other)) / (yield_all)

    unc_up = (  (abs(1-unc_up_wz)**2) +
                (abs(1-unc_up_ttw)**2) +
                (abs(1-unc_up_qqww)**2) +
                (abs(1-unc_up_ttz)**2) +
                (abs(1-unc_up_other)**2)
                )**(0.5)
    unc_down = ((abs(1-unc_down_wz)**2) +
                (abs(1-unc_down_ttw)**2) +
                (abs(1-unc_down_qqww)**2) +
                (abs(1-unc_down_ttz)**2) +
                (abs(1-unc_down_other)**2)
                )**(0.5)

    # print "The fractional uncertainty in yield due to tt (st) is %.3f/%.3f (%.3f/%.3f)" % (unc_up_tt, unc_down_tt, unc_up_st, unc_down_st)

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


if doBDT:
    uncertainties = {}
    for y in years:
        uncertainties[y] = {}
        for c in couplings:
            uncertainties[y][c] = {}
            if("tch" in c): altSig = "hct"
            else: altSig = "hut"
            
            wz_file = inputdir + ("wz_{0}_hists.root".format(y))
            qqww_file = inputdir + ("qqww_{0}_hists.root".format(y))
            ttw_file = inputdir + ("ttw_{0}_hists.root".format(y))
            ttz_file = inputdir + ("ttz_{0}_hists.root".format(y))
            other_file = inputdir + ("nonleadingrares_{0}_hists.root".format(y))

            wz_hist = getObjFromFile(wz_file, "h_br_bdtScore_{0}{1}_wz".format(altSig,y))
            qqww_hist = getObjFromFile(qqww_file, "h_br_bdtScore_{0}{1}_qqww".format(altSig,y))
            ttw_hist = getObjFromFile(ttw_file, "h_br_bdtScore_{0}{1}_ttw".format(altSig,y))
            ttz_hist = getObjFromFile(ttz_file, "h_br_bdtScore_{0}{1}_ttz".format(altSig,y))
            other_hist = getObjFromFile(other_file, "h_br_bdtScore_{0}{1}_nonleadingrares".format(altSig,y))

            it = 0
            for b in range(1,wz_hist.GetNbinsX()+1):
                up,down = calculate_total_unc_asymmetric(
                    wz_hist.GetBinContent(b),
                    ttw_hist.GetBinContent(b),
                    qqww_hist.GetBinContent(b),
                    ttz_hist.GetBinContent(b),
                    other_hist.GetBinContent(b))
                print(up,down)

                uncertainties[y][c][srbins[it]] = {"up":1+up,"down":1-down}
                it+=1

    with open("./datacards/bdt_rare_individual_uncs.json", "w") as f_out:
        json.dump(uncertainties, f_out, sort_keys=True, indent=4)

if doCC:
    uncertainties = {}
    for y in years:
        uncertainties[y] = {}
        
        wz_file = inputdir + ("wz_{0}_hists.root".format(y))
        qqww_file = inputdir + ("qqww_{0}_hists.root".format(y))
        ttw_file = inputdir + ("ttw_{0}_hists.root".format(y))
        ttz_file = inputdir + ("ttz_{0}_hists.root".format(y))
        other_file = inputdir + ("nonleadingrares_{0}_hists.root".format(y))

        wz_hist = getObjFromFile(wz_file, "h_br_sr_wz")
        qqww_hist = getObjFromFile(qqww_file, "h_br_sr_qqww")
        ttw_hist = getObjFromFile(ttw_file, "h_br_sr_ttw")
        ttz_hist = getObjFromFile(ttz_file, "h_br_sr_ttz")
        other_hist = getObjFromFile(other_file, "h_br_sr_nonleadingrares")

        it = 0
        for b in range(1,wz_hist.GetNbinsX()+1):
            up,down = calculate_total_unc_asymmetric(
                wz_hist.GetBinContent(b),
                ttw_hist.GetBinContent(b),
                qqww_hist.GetBinContent(b),
                ttz_hist.GetBinContent(b),
                other_hist.GetBinContent(b))
            print(up,down)

            uncertainties[y][srbins[it]] = {"up":1+up,"down":1-down}
            it+=1

    with open("./datacards/cc_rare_individual_uncs.json", "w") as f_out:
        json.dump(uncertainties, f_out, sort_keys=True, indent=4)
