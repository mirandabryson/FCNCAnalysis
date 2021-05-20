#!/usr/bin/env python

import os
import sys
import utils.pyrun as pyrun
import argparse
import fnmatch
import operator
import glob
import ast
import time
sys.path.append('/home/users/fgolf/fcnc/current/samples/')
import samples
from samples import get_sample_path

def make_obj(fpatts=[],options="",treename="Events"):
    if type(fpatts) == str: fpatts = [fpatts]
    ch = r.TChain(treename)
    for fpatt in fpatts:
        ch.Add(fpatt)
    return {"ch": ch, "options": options}

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--out", help="output directory", default="outputs")
    parser.add_argument("-e", "--extra_options", help="quoted string of extra options", default="")
    parser.add_argument(      "--plot_kwargs", help="""kwargs to pass to plotter e.g., '{"show_mcfakes": True,}'""", default="")
    parser.add_argument("-t", "--tag", help="tag for bookkeeping and output directory location", default="fcnc_v4")

    parser.add_argument("-y", "--year", help="year, if you only want to run one", default="")
    parser.add_argument(      "--proc", help="process, if you only want to run one/some. accepts wildcards if quoted.", default="", type=str)
    parser.add_argument(      "--excludeproc", help="opposite of proc", default="", type=str)
    parser.add_argument(      "--skip_already_done", help="skip procs if already in limits folder", action="store_true")
    parser.add_argument(      "--slim", help="smaller subset of processes", action="store_true")
    parser.add_argument(      "--ncpu", help="number of cpus", default=25, type=int)
    parser.add_argument(      "--maxprocs", help="maximum number of chains", default=-1, type=int)
    parser.add_argument(      "--nevts", help="maximum number of events", default=-1, type=int)

    parser.add_argument("-n", "--noloop", help="skip looping/scanchain", action="store_true")
    parser.add_argument("-s", "--shapes", help="make shape hists and copy to limit directory tag folder", action="store_true")
    parser.add_argument("-p", "--plots", help="make plots and copy to the limit directory tag folder", action="store_true")
    parser.add_argument("-f", "--fastsim", help="include fastsim scans", action="store_true")
    parser.add_argument("-v", "--verbosity", help="verbosity level (0 = default,1,2)", default=0, type=int)
    parser.add_argument(      "--debug", help="print debug info to file deubg/<sample>.log", action="store_true")

    args = parser.parse_args()
    excludeprocs = args.excludeproc.strip().split(',')

    print('args.excludeproc: ',excludeprocs)

    plot_kwargs = {} if not args.plot_kwargs else ast.literal_eval(args.plot_kwargs)

    try:
        args.year = int(args.year)
    except:
        pass

    import ROOT as r
    r.gROOT.SetBatch()

    if not args.noloop:
        if os.path.isfile(".lastcompile.tmp"):
            with open(".lastcompile.tmp","r") as fh:
                lastcompile = fh.read().strip()
                if lastcompile != ("fcnc"):
                    print "Last compilation was different, so doing `rm event_looper_C.so"
                    os.system("rm event_looper_C.so")
        r.gSystem.SetAclicMode(r.TSystem.kDebug)
        r.gROOT.ProcessLine(".L ../../NanoTools/NanoCORE/NANO_CORE.so")
        #r.gROOT.ProcessLine(".L helpers/histogrammingClass_C.so")
        r.gROOT.ProcessLine(".L helpers/histogrammingClass.C++")
        #r.gROOT.ProcessLine(".L ../../common/CORE/Tools/goodrun.cc+")
        #r.gROOT.ProcessLine(".L ../../common/CORE/Tools/dorky/dorky.cc+")
        r.gROOT.ProcessLine(".L event_looper.C+")
        with open(".lastcompile.tmp","w") as fh: fh.write("fcnc")

    years_to_consider = [
            2016,
            2017,
            2018,
            ]

    # for _ in range(10): print "SKIMTEST"
    basedirs = {
            2016: "/nfs-7/userdata/ksalyer/fcnc/{}/2016/".format(args.tag),
            2017: "/nfs-7/userdata/ksalyer/fcnc/{}/2017/".format(args.tag),
            2018: "/nfs-7/userdata/ksalyer/fcnc/{}/2018/".format(args.tag),
            }

    outputdir = args.out
    extra_global_options = args.extra_options
    options = {
            2016: "Data2016 quiet {} evaluateBDT ".format(extra_global_options),
            2017: "Data2017 quiet {} evaluateBDT minPtFake18 ".format(extra_global_options),
            2018: "Data2018 quiet {} evaluateBDT minPtFake18 ".format(extra_global_options),
            }

    chs = {
        2016: {
            "fakes": make_obj([
                basedirs[2016]+get_sample_path("data",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttw",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttz_m1-10",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttz_m10",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("tth_nobb",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("qqww",2016,args.tag)+".root",
                ] , options=options[2016]+" doFakes doData "),
            "flips": make_obj(basedirs[2016]+get_sample_path("data",2016,args.tag)+".root", options=options[2016]+" doFlips doData "),
            "data": make_obj(basedirs[2016]+get_sample_path("data",2016,args.tag)+".root", options=options[2016] + " doData "),
            "signal_tuh": make_obj(basedirs[2016]+get_sample_path("signal_hut_atop",2016,args.tag)+".root", options=options[2016]),
            "signal_tuh": make_obj(basedirs[2016]+get_sample_path("signal_hut_top",2016,args.tag)+".root", options=options[2016]),
            "signal_tch": make_obj(basedirs[2016]+get_sample_path("signal_hct_atop",2016,args.tag)+".root", options=options[2016]),
            "signal_tuh": make_obj(basedirs[2016]+get_sample_path("signal_hct_top",2016,args.tag)+".root", options=options[2016]),
            # "fakes_mc": make_obj(basedirs[2016]+get_sample_path("TTBAR*",2016)+".root", options=options[2016]+ " doFakesMC "),
            "fakes_mc": make_obj([
                basedirs[2016]+get_sample_path("ttjets",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wjets_ht100-200",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wjets_ht200-400",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wjets_ht400-600",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wjets_ht600-800",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wjets_ht800-1200",2016,args.tag)+".root",
                ] , options=options[2016]+ " doTruthFake doStitch "),
            "flips_mc": make_obj([
                basedirs[2016]+get_sample_path("dyjets_m10-50",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("dyjets_m50", 2016,args.tag) + ".root",
                basedirs[2016]+get_sample_path("ww", 2016,args.tag) + ".root",
                basedirs[2016]+get_sample_path("ttjets", 2016,args.tag) + ".root",
                ], options=options[2016]+"doTruthFlip doStitch"),
            "ttjets": make_obj([
                basedirs[2016]+get_sample_path("ttjets", 2016,args.tag) + ".root",
                ], options=options[2016]),
            "ttw": make_obj(basedirs[2016]+get_sample_path("ttw",2016,args.tag)+".root", options=options[2016]),
            "tth": make_obj(basedirs[2016]+get_sample_path("tth_nobb",2016,args.tag)+".root", options=options[2016]),
            "ttz": make_obj([
                basedirs[2016]+get_sample_path("ttz_m1-10",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttz_m10",2016,args.tag)+".root",
                ] , options=options[2016]),
            "xg": make_obj([
                basedirs[2016]+get_sample_path("tg",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttg_dilep",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttg_1lep",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wg",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("zg",2016,args.tag)+".root",
                ],options=options[2016] + " doXgamma "),
            "ttvv": make_obj([
                basedirs[2016]+get_sample_path("tthh",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttwh",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttww",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttwz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttzh",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("ttzz",2016,args.tag)+".root",
                ],options=options[2016]),
            "rares": make_obj([
                basedirs[2016]+get_sample_path("ggh",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("qqww",2016,args.tag)+".root",
                #basedirs[2016]+get_sample_path("twz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("tzq",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("vh_nobb",2016,args.tag)+".root",
                #basedirs[2016]+get_sample_path("ww_dps",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("www",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wwz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wzg",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wwg",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("wzz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("zz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("zzz",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("tttj",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("tttw",2016,args.tag)+".root",
                basedirs[2016]+get_sample_path("tttt",2016,args.tag)+".root",
                ],options=options[2016]),
            },
        2017: {
            "fakes": make_obj([
                basedirs[2017]+get_sample_path("data",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttw",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttz_m1-10",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttz_m10",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("tth_nobb",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("qqww",2017,args.tag)+".root",
                ] , options=options[2017]+" doFakes doData "),
            "flips": make_obj(basedirs[2017]+get_sample_path("data",2017,args.tag)+".root", options=options[2017]+" doFlips doData "),
            "data": make_obj(basedirs[2017]+get_sample_path("data",2017,args.tag)+".root", options=options[2017] + " doData "),
            "signal_tuh": make_obj(basedirs[2017]+get_sample_path("signal_hut_atop",2017,args.tag)+".root", options=options[2017]),
            "signal_tuh": make_obj(basedirs[2017]+get_sample_path("signal_hut_top",2017,args.tag)+".root", options=options[2017]),
            "signal_tch": make_obj(basedirs[2017]+get_sample_path("signal_hct_atop",2017,args.tag)+".root", options=options[2017]),
            "signal_tuh": make_obj(basedirs[2017]+get_sample_path("signal_hct_top",2017,args.tag)+".root", options=options[2017]),
            # "fakes_mc": make_obj(basedirs[2017]+get_sample_path("TTBAR*",2017,args.tag)+".root", options=options[2017]+ " doFakesMC "),
            "fakes_mc": make_obj([
                basedirs[2017]+get_sample_path("ttjets",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wjets_ht100-200",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wjets_ht200-400",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wjets_ht400-600",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wjets_ht600-800",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wjets_ht800-1200",2017,args.tag)+".root",
                ] , options=options[2017]+ " doTruthFake doStitch "),
            "flips_mc": make_obj([
                basedirs[2017]+get_sample_path("dyjets_m10-50",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("dyjets_m50", 2017,args.tag) + ".root",
                basedirs[2017]+get_sample_path("ww", 2017,args.tag) + ".root",
                basedirs[2017]+get_sample_path("ttjets", 2017,args.tag) + ".root",
                ], options=options[2017]+"doTruthFlip doStitch"),
            "ttw": make_obj(basedirs[2017]+get_sample_path("ttw",2017,args.tag)+".root", options=options[2017]),
            "tth": make_obj(basedirs[2017]+get_sample_path("tth_nobb",2017,args.tag)+".root", options=options[2017]),
            "ttz": make_obj([
                basedirs[2017]+get_sample_path("ttz_m1-10",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttz_m10",2017,args.tag)+".root",
                ] , options=options[2017]),
            "xg": make_obj([
                basedirs[2017]+get_sample_path("tg",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttg_dilep",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttg_1lep",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wg",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("zg",2017,args.tag)+".root",
                ],options=options[2017] + " doXgamma "),
            "ttvv": make_obj([
                basedirs[2017]+get_sample_path("tthh",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttwh",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttww",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttwz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttzh",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("ttzz",2017,args.tag)+".root",
                ],options=options[2017]),
            "rares": make_obj([
                basedirs[2017]+get_sample_path("ggh",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("qqww",2017,args.tag)+".root",
                #basedirs[2017]+get_sample_path("twz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("tzq",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("vh_nobb",2017,args.tag)+".root",
                #basedirs[2017]+get_sample_path("ww_dps",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("www",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wwz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wzg",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wwg",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("wzz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("zz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("zzz",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("tttj",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("tttw",2017,args.tag)+".root",
                basedirs[2017]+get_sample_path("tttt",2017,args.tag)+".root",
                ],options=options[2017]),
            },
        2018: {
            # "fakes": make_obj([
            #     basedirs[2018]+get_sample_path("Data*",2018)+".root",
            #     basedirs[2018]+get_sample_path("TTWnlo",2018)+".root",
            #     basedirs[2018]+get_sample_path("TTZnlo",2018)+".root",
            #     basedirs[2018]+get_sample_path("TTHtoNonBB",2018)+".root",
            #     ] , options=options[2018]+" doFakes doData "),
            # "flips": make_obj(basedirs[2018]+get_sample_path("Data*",2018)+".root", options=options[2018]+" doFlips "),
            # "data": make_obj(basedirs[2018]+get_sample_path("Data*",2018)+".root", options=options[2018]+" doData "),
            "fakes": make_obj([
                basedirs[2018] + get_sample_path("data", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttw", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttz_m1-10", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttz_m10", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("tth_nobb", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("qqww", 2018,args.tag) + ".root",
                ], options=options[2018] + " doFakes doData "),
            "flips": make_obj(basedirs[2018] + get_sample_path("data", 2018,args.tag) + ".root",
                              options=options[2018] + " doFlips doData "),
            "data": make_obj(basedirs[2018] + get_sample_path("data", 2018,args.tag) + ".root",
                             options=options[2018] + " doData "),
            "signal_tuh": make_obj(basedirs[2018] + get_sample_path("signal_hut_atop", 2018,args.tag) + ".root",
                                   options=options[2018]),
            "signal_tuh": make_obj(basedirs[2018] + get_sample_path("signal_hut_top", 2018,args.tag) + ".root",
                                   options=options[2018]),
            "signal_tch": make_obj(basedirs[2018] + get_sample_path("signal_hct_atop", 2018,args.tag) + ".root",
                                   options=options[2018]),
            "signal_tuh": make_obj(basedirs[2018] + get_sample_path("signal_hct_top", 2018,args.tag) + ".root",
                                   options=options[2018]),
            # "fakes_mc": make_obj(basedirs[2018]+get_sample_path("TTBAR*",2018,args.tag)+".root", options=options[2018]+ " doFakesMC "),
            "fakes_mc": make_obj([
                basedirs[2018] + get_sample_path("ttjets", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wjets_ht100-200", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wjets_ht200-400", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wjets_ht400-600", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wjets_ht600-800", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wjets_ht800-1200", 2018,args.tag) + ".root",
                ], options=options[2018] + " doTruthFake doStitch "),
            "flips_mc": make_obj([
                basedirs[2018] + get_sample_path("dyjets_m10-50", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("dyjets_m50", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ww", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttjets", 2018,args.tag) + ".root",
                ], options=options[2018] + "doTruthFlip doStitch"),
            "ttjets": make_obj([
                basedirs[2018]+get_sample_path("ttjets", 2018,args.tag) + ".root",
                ], options=options[2016]),
            "ttw": make_obj(basedirs[2018] + get_sample_path("ttw", 2018,args.tag) + ".root", options=options[2018]),
            "tth": make_obj(basedirs[2018] + get_sample_path("tth_nobb", 2018,args.tag) + ".root", options=options[2018]),
            "ttz": make_obj([
                basedirs[2018] + get_sample_path("ttz_m1-10", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttz_m10", 2018,args.tag) + ".root",
                ], options=options[2018]),
            "xg": make_obj([
                basedirs[2018] + get_sample_path("tg", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttg_dilep", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttg_1lep", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wg", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("zg", 2018,args.tag) + ".root",
                ], options=options[2018] + " doXgamma "),
            "ttvv": make_obj([
                basedirs[2018] + get_sample_path("tthh", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttwh", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttww", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttwz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttzh", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("ttzz", 2018,args.tag) + ".root",
                ], options=options[2018]),
            "rares": make_obj([
                basedirs[2018] + get_sample_path("ggh", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("qqww", 2018,args.tag) + ".root",
                #basedirs[2018] + get_sample_path("twz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("tzq", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("vh_nobb", 2018,args.tag) + ".root",
                #basedirs[2018] + get_sample_path("ww_dps", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("www", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wwz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wzg", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wwg", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("wzz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("zz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("zzz", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("tttj", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("tttw", 2018,args.tag) + ".root",
                basedirs[2018] + get_sample_path("tttt", 2018,args.tag) + ".root",
            ], options=options[2018]),
       }
    }

    if args.verbosity>=1:
        print basedirs[2016]+get_sample_path("ttw",2016,args.tag)+".root"

    do_slim = args.slim

    def run_chain((index,info)):
        ch, options, outputdir = info
        t0 = time.time()
        ret = r.event_looper(ch,options,args.nevts,outputdir)
        t1 = time.time()
        return index, [ret, ch.GetTitle(), t1-t0]

    to_run = []
    already_done = []
    if args.skip_already_done and os.path.exists("../limits/{}/".format(args.tag)):
        parse = lambda x: x.rsplit("/",1)[1].split("_histos")[0]
        already_done = map(parse,glob.glob("../limits/{}/*_srhh_2016.root".format(args.tag)))
        print "Skipping up to {} processes (e.g., {}, ...)".format(len(already_done),already_done[0])
    for year in years_to_consider:
        if (args.year) and (year != args.year): continue
        for proc in chs[year].keys():
            # if (len(args.proc) > 0) and (proc != args.proc): continue
            if (len(args.proc) > 0) and not fnmatch.fnmatch(proc,args.proc): continue
            if (len(excludeprocs) > 0) and len(fnmatch.filter(excludeprocs,proc))>0: 
                print 'excluding process ', proc
                continue
            if args.skip_already_done and (proc in already_done): continue
            obj = chs[year][proc]
            opts = obj["options"]
            if args.verbosity >= 1:
                opts = opts.replace("quiet","")
            if args.year and args.proc and "*" not in args.proc:  # if one process, show the progress bar
                opts = opts.replace("quiet","")
            if args.verbosity == 0:
                opts += " quiet"
            if args.debug:
                opts += " printDebugFile"
            # Change chain titles to proc so that we output the right root file name
            obj["ch"].SetTitle("{}".format(proc))
            to_run.append([obj["ch"], opts, outputdir])
            if args.verbosity >= 2:
                print "Adding:", obj["ch"].GetTitle(), opts, outputdir, year

    if args.maxprocs > 0:
        print "Actually, you specified a maximum of {} chains, so taking the first ones".format(args.maxprocs)
        to_run = to_run[:args.maxprocs]

    os.system("mkdir -p {}".format(outputdir))

    # Make sure all the requested root files actually exist
    for ch,opts,_ in to_run:
        for fname in [str(x.GetTitle()) for x in ch.GetListOfFiles()]:
            if not os.path.exists(fname):
                print "[!] {} does not exist!".format(fname)

    # to_run = [t for t in to_run if "doXgamma" in t[1]]
    # print to_run

    # to_run = [t for t in to_run if ("doData " in t[1] and "2016" in t[1] and "Fake" not in t[1] and "Flip" not in t[1])]
    # to_run[0][1] = to_run[0][1].replace("quiet","")
    # print to_run
    # run_chain((0,to_run[0]))

    # to_run = [t for t in to_run if ("doFakes " in t[1] and "2016" in t[1])]
    # to_run[0][1] = to_run[0][1].replace("quiet","")
    # print to_run
    # run_chain((0,to_run[0]))

    procnames = list(set([x[0].GetTitle() for x in to_run]))
    fcnc_procnames = [pn for pn in procnames if "fcnc" in pn]

    if not args.noloop:
        def callback(ret):
            pass
        # if len(to_run) < 30:
        #     def callback(ret):
        #         ret, proc, t = ret
        #         print "Processed {} in {:.1f} seconds".format(proc,t)
        # else:
        #     def callback(ret):
        #         pass

        if len(to_run) > 3000:
            print "[!] You might want to kill this at some point and run the rest with --skip_already_done because of memory leaks"

        # Now run them
        if len(to_run) == 1:
            print "Running one chain"
            map(run_chain,enumerate(to_run))
            print "Done"
        else:
            os.nice(4)
            runner = pyrun.Runner(nproc=min(args.ncpu,len(to_run)), func=run_chain, dot_type=(3 if len(to_run)<500 else 0))
            runner.add_args(to_run)
            runner.run(print_callback=callback)

    if args.tag:
        outdir_limits = "../limits/{}/".format(args.tag)
        #os.system("mkdir -p {}".format(outdir_limits))
        #os.system("cp ../misc/signal_regions.h {}/".format(outdir_limits))
        #os.system("cp ../misc/bdt.h {}/".format(outdir_limits))
        #os.system("cp yieldMaker.C make_shape_hists.py py_doAll.py plot_all.py {}/".format(outdir_limits))

        if args.shapes:
            import make_shape_hists
            regions = ["SRCR","SRDISC"] if not "noBDT" in extra_global_options else ["SRCR"]
            make_shape_hists.make_root_files(
                    outputdir=outdir_limits,
                    inputdir=args.out,
                    extra_procs=fastsim_procnames+higgs_procnames+oblique_procnames+rpv_procnames+fcnc_procnames,
                    regions=regions,
                    verbose=(args.verbosity >= 2),
                    doss=args.ss,
                    )

        if args.plots:
            # numba njit causes segfault when pyroot has been imported (more specifically, once we've gotten a root MethodProxy somehow)
            # so prevent uproot from importing it (which prevents the njit)
            # https://github.com/scikit-hep/uproot/issues/58
            # https://stackoverflow.com/questions/1350466/preventing-python-code-from-importing-certain-modules
            import sys
            sys.modules["numba"] = None
            import plot_all


            signames = ["tttt"]
            if args.ss:
                signames = ["fs_t1tttt_m1600_m600"]
                # signames = fastsim_procnames[:1]
            plot_all.make_plots(
                    outputdir="{}/plots/".format(outdir_limits),
                    inputdir=args.out,
                    year=2016,
                    lumi="35.9",
                    other_years = [],
                    doss=args.ss,
                    signames=signames,
                    **plot_kwargs
                    )

            plot_all.make_plots(
                    outputdir="{}/plots/".format(outdir_limits),
                    inputdir=args.out,
                    year=2017,
                    lumi=("41.5"),
                    other_years = [],
                    doss=args.ss,
                    signames=signames,
                    **plot_kwargs
                    )

            plot_all.make_plots(
                    outputdir="{}/plots/".format(outdir_limits),
                    inputdir=args.out,
                    year=2018,
                    lumi=("59.7"),
                    other_years = [],
                    doss=args.ss,
                    signames=signames,
                    **plot_kwargs
                    )

            plot_all.make_plots(
                    outputdir="{}/plots/".format(outdir_limits),
                    inputdir=args.out,
                    year=2018,
                    # lumi="136.3", # 2016+2017+2018 --> 35.922+41.53+58.83 = 136.3
                    lumi=("137"),
                    other_years = [2016,2017],
                    doss=args.ss,
                    signames=signames,
                    **plot_kwargs
                    )

    print "end"
