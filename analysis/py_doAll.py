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
sys.path.append('/home/users/mbryson/fcnc/ana/samples/')
#sys.path.append('/home/users/ksalyer/FCNCAnalysis/samples/')
import samples
from samples import get_sample_path

def make_obj(fpatts=[],options="",treename="Events"):
    if type(fpatts) == str: fpatts = [fpatts]
    listOfFiles = r.TObjArray()
    for fpatt in fpatts:
        fileToAdd = r.TObjString(fpatt)
        # print(fileToAdd)
        listOfFiles.Add(fileToAdd)
    return {"ch": listOfFiles, "options": options}

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--out", help="output directory", default="outputs")
    parser.add_argument("-e", "--extra_options", help="quoted string of extra options", default="")
    parser.add_argument(      "--plot_kwargs", help="""kwargs to pass to plotter e.g., '{"show_mcfakes": True,}'""", default="")
    parser.add_argument("-t", "--tag", help="tag for bookkeeping and output directory location", default="fcnc_v4")
    parser.add_argument("-d", "--datatag", help="tag for bookkeeping and output directory location", default="")

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
    myprocs = args.proc.strip().split(',')
    print(len(myprocs))
    if not args.datatag: args.datatag = args.tag
    print("data tag", args.datatag)
    print("mc tag", args.tag)

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
                    print("Last compilation was different, so doing `rm event_looper_C.so")
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

    basedirs = {
            2016: '/ceph/cms/store/group/tttt/Skims/220705/2016_NonAPV/',
            2017: '/ceph/cms/store/group/tttt/Skims/220705/2017/',
            2018: '/ceph/cms/store/group/tttt/Skims/220705/2018/',
            }
    datadirs = {
            2016: '/ceph/cms/store/group/tttt/Skims/220705/2016_NonAPV/',
            2017: '/ceph/cms/store/group/tttt/Skims/220705/2017/',
            2018: '/ceph/cms/store/group/tttt/Skims/220705/2018/',
            }

    outputdir = args.out
    extra_global_options = args.extra_options
    options = {
            2016: "Data2016 quiet {} ".format(extra_global_options),
            2017: "Data2017 quiet {} minPtFake18 ".format(extra_global_options),
            2018: "Data2018 quiet {} minPtFake18 ".format(extra_global_options),
            }

    chs = {
        2016: {
            # "fakes": make_obj([
            #     # basedirs[2016]+get_sample_path("data",2016,args.tag)+".root",
            #     # basedirs[2016]+get_sample_path("TTW_lnu",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZ_2l2nu_M_1to10",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZ_2l2nu_M_10",2016,args.tag)+".root",
            #     # basedirs[2016]+get_sample_path("TTH_HToNonBB",2016,args.tag)+".root",
            #     # basedirs[2016]+get_sample_path("qqWZ_3lnu_MG",2016,args.tag)+".root",
            #     # basedirs[2016]+get_sample_path("qqww",2016,args.tag)+".root",
            #     ] , options=options[2016]+" doFakes doData "),
            # # "flips": make_obj(basedirs[2016]+get_sample_path("data",2016,args.tag)+".root", options=options[2016]+" doFlips doData "),
            # "data": make_obj([
            #     datadirs[2016] + get_sample_path("double_muon_data", 2016,args.tag) + ".root",
            #     datadirs[2016] + get_sample_path("eg_data", 2016,args.tag) + ".root",
            #     datadirs[2016] + get_sample_path("muon_eg_data", 2016,args.tag) + ".root",
            #     ], options=options[2016] + " doData "),
            # "signal_tuh": make_obj([
            #     basedirs[2016]+get_sample_path("signal_hut_ST",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("signal_hut_atop",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("signal_hut_top",2016,args.tag)+".root",
            #     ] , options=options[2016]),
            "signal_tch": make_obj(
                glob.glob(basedirs[2016] + get_sample_path("TTTT", 2016,args.tag) + '*.root'), options=options[2016]),
            # # "fakes_mc": make_obj(basedirs[2016]+get_sample_path("TTBAR*",2016)+".root", options=options[2016]+ " doFakesMC "),
            "fakes_mc": make_obj(
                glob.glob(basedirs[2016] + get_sample_path("TT_2l2nu", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TT_lnu_nlo", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTJets", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("WJets_lnu_lo", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("DY_2l_M_10to50", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("DY_2l_M_50", 2016,args.tag) + "*.root"), options=options[2016] + " doTruthFake doStitch "),
            "flips_mc": make_obj(
                glob.glob(basedirs[2016] + get_sample_path("TT_2l2nu", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TT_lnu_nlo", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("WJets_lnu_lo", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTJets", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("DY_2l_M_10to50", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("DY_2l_M_50", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("qqWW_2l2nu", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("qqZG_ll_01j", 2016,args.tag) + "*.root"), options=options[2016] + "doTruthFlip doStitch"),
            # "top": make_obj([
            #     basedirs[2016] + get_sample_path("TT_2l2nu", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TT_lnu_nlo", 2016,args.tag) + ".root",
            #     # # basedirs[2016] + get_sample_path("TTJets", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tw_top", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tw_atop", 2016,args.tag) + ".root",

            #     ], options=options[2016] + " doStitch"),
            # "otherFakes": make_obj([
            #     basedirs[2016] + get_sample_path("tw_top", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("tw_atop", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + ".root",
            #     ], options=options[2016] + " doTruthFake doStitch "),
            # "wboson": make_obj([
            #     basedirs[2016] + get_sample_path("WJets_lnu_lo", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + ".root",
            #     ], options=options[2016] + " doStitch"),
            # "tw": make_obj([
            #     # basedirs[2016] + get_sample_path("TT_2l2nu", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("TTJets", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("tw_top", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("tw_atop", 2016,args.tag) + ".root",

            #     ], options=options[2016] + " doStitch"),
            # "dy": make_obj([
            #     basedirs[2016] + get_sample_path("DY_2l_M_10to50", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("DY_2l_M_50", 2016,args.tag) + ".root",
            #     ], options=options[2016] + " doStitch"),
            # "TTJets": make_obj([
            #     basedirs[2016]+get_sample_path("TTJets", 2016,args.tag) + ".root",
            #     ], options=options[2016]),
            # "WJets_lnu_lo": make_obj([
            #     basedirs[2016]+get_sample_path("WJets_lnu_lo", 2016,args.tag) + ".root",
            #     ], options=options[2016]),
            # "TTW_lnu": make_obj(basedirs[2016]+get_sample_path("TTW_lnu",2016,args.tag)+".root", options=options[2016]),
            # "tth": make_obj(basedirs[2016]+get_sample_path("TTH_HToNonBB",2016,args.tag)+".root", options=options[2016]),
            # "ttz": make_obj([
            #     basedirs[2016]+get_sample_path("TTZ_2l2nu_M_1to10",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZ_2l2nu_M_10",2016,args.tag)+".root",
            #     ] , options=options[2016]),
            # "xg": make_obj([
            #     # basedirs[2016]+get_sample_path("tg",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTG_2l2nu",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTG_lnu",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("qqWG_lnu_nlo_01j",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("WWG",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("WZG",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("qqZG_ll_01j",2016,args.tag)+".root",
            #     ],options=options[2016] + " doXgamma "),
            # "ttvv": make_obj([
            #     basedirs[2016]+get_sample_path("TTTW",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTTJ",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTWH",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTWW",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTWZ",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZH",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZZ",2016,args.tag)+".root",
            #     ],options=options[2016]),
            # "ttx": make_obj([
            #     basedirs[2016]+get_sample_path("TTH_HToNonBB",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZ_2l2nu_M_1to10",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTZ_2l2nu_M_10",2016,args.tag)+".root",
            #     # basedirs[2016]+get_sample_path("tzq",2016,args.tag)+".root",
            #     # basedirs[2016]+get_sample_path("tw_dilep",2016,args.tag)+".root",
            #     ],options=options[2016]),
            "rares": make_obj(
                glob.glob(basedirs[2016] + get_sample_path("GGH_ZZTo4L_POWHEG", 2016,args.tag) + "*.root") 
                # basedirs[2016] + get_sample_path("qqww", 2016,args.tag) + ".root",
                # basedirs[2016] + get_sample_path("tzq", 2016,args.tag) + ".root",
                # basedirs[2016] + get_sample_path("vh_nobb", 2016,args.tag) + ".root",
                + glob.glob(basedirs[2016] + get_sample_path("WWW_4f", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("WWW_4f_ext", 2016,args.tag) + "*.root")
                # basedirs[2016] + get_sample_path("wwz", 2016,args.tag) + ".root",
                + glob.glob(basedirs[2016] + get_sample_path("qqWZ_3lnu_MG", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("WZG", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("WWG", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("WZZ", 2016,args.tag) + "*.root",)
                + glob.glob(basedirs[2016] + get_sample_path("WZZ_ext", 2016,args.tag) + "*.root",)
                + glob.glob(basedirs[2016] + get_sample_path("qqZZ_4l", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("ZZZ", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("ZZZ_ext", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTTJ", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTTW", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTWH", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTWW", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTZH", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTWZ", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTZZ", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTHH", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTH_HToNonBB", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTG_2l2nu", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTG_lnu", 2016,args.tag) + "*.root")
                # basedirs[2016] + get_sample_path("tg", 2016,args.tag) + ".root",
                + glob.glob(basedirs[2016] + get_sample_path("TTW_lnu", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTZ_2l2nu_M_1to10", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("TTZ_2l2nu_M_10", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("qqZG_ll_01j", 2016,args.tag) + "*.root")
                + glob.glob(basedirs[2016] + get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + "*.root")
                # basedirs[2016] + get_sample_path("tw_dilep", 2016,args.tag) + ".root",
                + glob.glob(basedirs[2016] + get_sample_path("qqWW_2l2nu", 2016,args.tag) + "*.root"), options=options[2016]),
            # "nonleadingrares": make_obj([
            #     # basedirs[2016] + get_sample_path("TT_2l2nu", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("TT_lnu_nlo", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("WJets_lnu_lo", 2016,args.tag) + ".root",

            #     basedirs[2016] + get_sample_path("GGH_ZZTo4L_POWHEG", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("qqww", 2016,args.tag) + ".root",
            #     ###basedirs[2016] + get_sample_path("twz", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tzq", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("vh_nobb", 2016,args.tag) + ".root",
            #     ###basedirs[2016] + get_sample_path("ww_dps", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WWW", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("wwz", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("qqWZ_3lnu_MG", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WZG", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WWG", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WZZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqZZ_4l", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("ZZZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTTJ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTTW", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTWH", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTWW", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTZH", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTWZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTZZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTHH", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTH_HToNonBB", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTG_2l2nu", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTG_lnu", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tg", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("TTW_lnu", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("TTZ_2l2nu_M_1to10", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("TTZ_2l2nu_M_10", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqZG_ll_01j", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tw_dilep", 2016,args.tag) + ".root",


            # ], options=options[2016]),
            # "os_rares": make_obj([
            #     basedirs[2016] + get_sample_path("GGH_ZZTo4L_POWHEG", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("qqww", 2016,args.tag) + ".root",
            #     #basedirs[2016] + get_sample_path("twz", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tzq", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("vh_nobb", 2016,args.tag) + ".root",
            #     #basedirs[2016] + get_sample_path("ww_dps", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WWW", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("wwz", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqWZ_3lnu_MG", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WZG", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WWG", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("WZZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqZZ_4l", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("ZZZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTTJ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTTW", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTZH", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTWZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTZZ", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTHH", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTH_HToNonBB", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTG_2l2nu", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTG_lnu", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tg", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTW_lnu", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTZ_2l2nu_M_1to10", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("TTZ_2l2nu_M_10", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqZG_ll_01j", 2016,args.tag) + ".root",
            #     basedirs[2016] + get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + ".root",
            #     # basedirs[2016] + get_sample_path("tw_dilep", 2016,args.tag) + ".root",
            # ], options=options[2016]),
            # "smallRares": make_obj([
            #     basedirs[2016]+get_sample_path("GGH_ZZTo4L_POWHEG",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("vh_nobb",2016,args.tag)+".root",
            #     basedirs[2016]+get_sample_path("TTHH",2016,args.tag)+".root",
            #     ],options=options[2016]),
            # "GGH_ZZTo4L_POWHEG": make_obj([basedirs[2016]+get_sample_path("GGH_ZZTo4L_POWHEG", 2016,args.tag) + ".root",], options=options[2016]),
            # "qqww": make_obj([basedirs[2016]+get_sample_path("qqww", 2016,args.tag) + ".root",], options=options[2016]),
            # "tzq": make_obj([basedirs[2016]+get_sample_path("tzq", 2016,args.tag) + ".root",], options=options[2016]),
            # "vh_nobb": make_obj([basedirs[2016]+get_sample_path("vh_nobb", 2016,args.tag) + ".root",], options=options[2016]),
            # "WWW": make_obj([basedirs[2016]+get_sample_path("WWW", 2016,args.tag) + ".root",], options=options[2016]),
            # "wwz": make_obj([basedirs[2016]+get_sample_path("wwz", 2016,args.tag) + ".root",], options=options[2016]),
            # "qqWZ_3lnu_MG": make_obj([basedirs[2016]+get_sample_path("qqWZ_3lnu_MG", 2016,args.tag) + ".root",], options=options[2016]),
            # "qqWW_2l2nu": make_obj([basedirs[2016]+get_sample_path("qqWW_2l2nu", 2016,args.tag) + ".root",], options=options[2016]),
            # "WZG": make_obj([basedirs[2016]+get_sample_path("WZG", 2016,args.tag) + ".root",], options=options[2016]),
            # "WWG": make_obj([basedirs[2016]+get_sample_path("WWG", 2016,args.tag) + ".root",], options=options[2016]),
            # "WZZ": make_obj([basedirs[2016]+get_sample_path("WZZ", 2016,args.tag) + ".root",], options=options[2016]),
            # "qqZZ_4l": make_obj([basedirs[2016]+get_sample_path("qqZZ_4l", 2016,args.tag) + ".root",], options=options[2016]),
            # "ZZZ": make_obj([basedirs[2016]+get_sample_path("ZZZ", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTTJ": make_obj([basedirs[2016]+get_sample_path("TTTJ", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTTW": make_obj([basedirs[2016]+get_sample_path("TTTW", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTTT": make_obj([basedirs[2016]+get_sample_path("TTTT", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTZH": make_obj([basedirs[2016]+get_sample_path("TTZH", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTWZ": make_obj([basedirs[2016]+get_sample_path("TTWZ", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTWH": make_obj([basedirs[2016]+get_sample_path("TTWH", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTWW": make_obj([basedirs[2016]+get_sample_path("TTWW", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTZZ": make_obj([basedirs[2016]+get_sample_path("TTZZ", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTHH": make_obj([basedirs[2016]+get_sample_path("TTHH", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTH_HToNonBB": make_obj([basedirs[2016]+get_sample_path("TTH_HToNonBB", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTG_2l2nu": make_obj([basedirs[2016]+get_sample_path("TTG_2l2nu", 2016,args.tag) + ".root",], options=options[2016]),
            # "tg": make_obj([basedirs[2016]+get_sample_path("tg", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTW_lnu": make_obj([basedirs[2016]+get_sample_path("TTW_lnu", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTZ_2l2nu_M_1to10": make_obj([basedirs[2016]+get_sample_path("TTZ_2l2nu_M_1to10", 2016,args.tag) + ".root",], options=options[2016]),
            # "TTZ_2l2nu_M_10": make_obj([basedirs[2016]+get_sample_path("TTZ_2l2nu_M_10", 2016,args.tag) + ".root",], options=options[2016]),
            # "qqZG_ll_01j": make_obj([basedirs[2016]+get_sample_path("qqZG_ll_01j", 2016,args.tag) + ".root",], options=options[2016]),
            # "qqWG_lnu_nlo_01j": make_obj([basedirs[2016]+get_sample_path("qqWG_lnu_nlo_01j", 2016,args.tag) + ".root",], options=options[2016]),
            # "tw_dilep": make_obj(basedirs[2016] + get_sample_path("tw_dilep", 2016,args.tag) + ".root", options=options[2016]),
            # "multiboson": make_obj([
            #     basedirs[2016]+get_sample_path("qqww", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("qqWZ_3lnu_MG", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("qqZZ_4l", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("WWW", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("wwz", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("WZZ", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("ZZZ", 2016,args.tag) + ".root",
            #     ],options=options[2016]),
            # "ttxx": make_obj([
            #     basedirs[2016]+get_sample_path("TTTJ", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("TTTW", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("TTZH", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("TTWZ", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("TTZZ", 2016,args.tag) + ".root",
            #     basedirs[2016]+get_sample_path("TTHH", 2016,args.tag) + ".root",
            #     ],options=options[2016]),
            },
        2017: {
            # "fakes": make_obj([
            #     # basedirs[2017]+get_sample_path("data",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTW_lnu",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("TTZ_2l2nu_M_1to10",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("TTZ_2l2nu_M_10",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTH_HToNonBB",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("qqWZ_3lnu_MG",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("qqww",2017,args.tag)+".root",
            #     ] , options=options[2017]+" doFakes doData "),
            # # "flips": make_obj(basedirs[2017]+get_sample_path("data",2017,args.tag)+".root", options=options[2017]+" doFlips doData "),
            # "data": make_obj([
            #     datadirs[2017] + get_sample_path("double_muon_data", 2017,args.tag) + ".root",
            #     datadirs[2017] + get_sample_path("eg_data", 2017,args.tag) + ".root",
            #     datadirs[2017] + get_sample_path("muon_eg_data", 2017,args.tag) + ".root",
            #     ], options=options[2017] + " doData "),
            # "signal_tuh": make_obj([
            #     # basedirs[2017]+get_sample_path("signal_hut_ST",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("signal_hut_atop",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("signal_hut_top",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTTT",2017,args.tag)+".root",
            #     ] , options=options[2017]),
            "signal_tch": make_obj(
                glob.glob(basedirs[2017] + get_sample_path("TTTT", 2017,args.tag) + '*.root'), options=options[2017]),
            "fakes_mc": make_obj(
                glob.glob(basedirs[2017] + get_sample_path("TT_2l2nu", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TT_lnu_nlo", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTJets", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("WJets_lnu_lo", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + ".root")
                + glob.glob(basedirs[2017] + get_sample_path("DY_2l_M_10to50", 2017,args.tag) + ".root")
                + glob.glob(basedirs[2017] + get_sample_path("DY_2l_M_50", 2017,args.tag) + ".root"), options=options[2017] + " doTruthFake doStitch "),
            "flips_mc": make_obj(
                glob.glob(basedirs[2017] + get_sample_path("TT_2l2nu", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TT_lnu_nlo", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("WJets_lnu_lo", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTJets", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("DY_2l_M_10to50", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("DY_2l_M_50", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("qqWW_2l2nu", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("qqZG_ll_01j", 2017,args.tag) + "*.root"), options=options[2017] + "doTruthFlip doStitch"),
            # "top": make_obj([
            #     basedirs[2017] + get_sample_path("TT_2l2nu", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TT_lnu_nlo", 2017,args.tag) + ".root",
            #     # # basedirs[2017] + get_sample_path("TTJets", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tw_top", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tw_atop", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("TTG_2l2nu", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("TTG_lnu", 2017,args.tag) + ".root",
            #     ], options=options[2017] + " doStitch"),
            # "wboson": make_obj([
            #     basedirs[2017] + get_sample_path("WJets_lnu_lo", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + ".root",
            #     ], options=options[2017] + " doStitch"),
            # "otherFakes": make_obj([
            #     basedirs[2017] + get_sample_path("tw_top", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("tw_atop", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + ".root",
            #     ], options=options[2017] + " doTruthFake doStitch "),
            # "tw": make_obj([
            #     # basedirs[2017] + get_sample_path("TT_2l2nu", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("TTJets", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("tw_top", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("tw_atop", 2017,args.tag) + ".root",

            #     ], options=options[2017] + " doStitch"),
            # "dy": make_obj([
            #     basedirs[2017] + get_sample_path("DY_2l_M_10to50", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("DY_2l_M_50", 2017,args.tag) + ".root",
            #     ], options=options[2017] + " doStitch"),
            # "TTJets": make_obj([
            #     basedirs[2017]+get_sample_path("TTJets", 2017,args.tag) + ".root",
            #     ], options=options[2017]),
            # "WJets_lnu_lo": make_obj([
            #     basedirs[2017]+get_sample_path("WJets_lnu_lo", 2017,args.tag) + ".root",
            #     ], options=options[2017]),
            # "TTW_lnu": make_obj(basedirs[2017]+get_sample_path("TTW_lnu",2017,args.tag)+".root", options=options[2017]),
            # "tth": make_obj(basedirs[2017]+get_sample_path("TTH_HToNonBB",2017,args.tag)+".root", options=options[2017]),
            # "ttz": make_obj([
            #     basedirs[2017]+get_sample_path("TTZ_2l2nu_M_1to10",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTZ_2l2nu_M_10",2017,args.tag)+".root",
            #     ] , options=options[2017]),
            # "xg": make_obj([
            #     # basedirs[2017]+get_sample_path("tg",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTG_2l2nu",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTG_lnu",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("qqWG_lnu_nlo_01j",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("WWG",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("WZG",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("qqZG_ll_01j",2017,args.tag)+".root",
            #     ],options=options[2017] + " doXgamma "),
            # "ttvv": make_obj([
            #     basedirs[2017]+get_sample_path("TTTW",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTTJ",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTWH",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTWW",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTWZ",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTZH",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTZZ",2017,args.tag)+".root",
            #     ],options=options[2017]),
            # "ttx": make_obj([
            #     basedirs[2017]+get_sample_path("TTH_HToNonBB",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTZ_2l2nu_M_1to10",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTZ_2l2nu_M_10",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("tzq",2017,args.tag)+".root",
            #     # basedirs[2017]+get_sample_path("tw_dilep",2017,args.tag)+".root",
            #     ],options=options[2017]),
            "rares": make_obj(
                glob.glob(basedirs[2017] + get_sample_path("GGH_ZZTo4L_POWHEG", 2017,args.tag) + "*.root")
                # basedirs[2017] + get_sample_path("qqww", 2017,args.tag) + ".root",
                # basedirs[2017] + get_sample_path("tzq", 2017,args.tag) + ".root",
                # basedirs[2017] + get_sample_path("vh_nobb", 2017,args.tag) + ".root",
                + glob.glob(basedirs[2017] + get_sample_path("WWW", 2017,args.tag) + "*.root")
                # basedirs[2017] + get_sample_path("wwz", 2017,args.tag) + ".root",
                + glob.glob(basedirs[2017] + get_sample_path("qqWZ_3lnu_MG", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("WZG", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("WWG", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("WZZ", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("qqZZ_4l", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("ZZZ", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTTJ", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTTW", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTWH", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTWW", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTZH", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTWZ", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTZZ", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTHH", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTH_HToNonBB", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTG_2l2nu", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTG_lnu", 2017,args.tag) + "*.root")
                # basedirs[2017] + get_sample_path("tg", 2017,args.tag) + ".root",
                + glob.glob(basedirs[2017] + get_sample_path("TTW_lnu", 2017,args.tag) + ".*root")
                + glob.glob(basedirs[2017] + get_sample_path("TTZ_2l2nu_M_1to10", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("TTZ_2l2nu_M_10", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("qqZG_ll_01j", 2017,args.tag) + "*.root")
                + glob.glob(basedirs[2017] + get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + "*.root")
                # basedirs[2017] + get_sample_path("tw_dilep", 2017,args.tag) + ".root",
                + glob.glob(basedirs[2017] + get_sample_path("qqWW_2l2nu", 2017,args.tag) + "*.root"), options=options[2017]),
            # "nonleadingrares": make_obj([
            #     basedirs[2017] + get_sample_path("GGH_ZZTo4L_POWHEG", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("qqww", 2017,args.tag) + ".root",
            #     ###basedirs[2017] + get_sample_path("twz", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tzq", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("vh_nobb", 2017,args.tag) + ".root",
            #     ###basedirs[2017] + get_sample_path("ww_dps", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WWW", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("wwz", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqWZ_3lnu_MG", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WZG", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WWG", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WZZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqZZ_4l", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("ZZZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTTJ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTTW", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTWH", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTWW", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTZH", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTWZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTZZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTHH", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTH_HToNonBB", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTG_2l2nu", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTG_lnu", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tg", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("TTW_lnu", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("TTZ_2l2nu_M_1to10", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("TTZ_2l2nu_M_10", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqZG_ll_01j", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tw_dilep", 2017,args.tag) + ".root",

            # ], options=options[2017]),
            # "os_rares": make_obj([
            #     basedirs[2017] + get_sample_path("GGH_ZZTo4L_POWHEG", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("qqww", 2017,args.tag) + ".root",
            #     #basedirs[2017] + get_sample_path("twz", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tzq", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("vh_nobb", 2017,args.tag) + ".root",
            #     #basedirs[2017] + get_sample_path("ww_dps", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WWW", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("wwz", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqWZ_3lnu_MG", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WZG", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WWG", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("WZZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqZZ_4l", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("ZZZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTTJ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTTW", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTZH", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTWZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTZZ", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTHH", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTH_HToNonBB", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTG_2l2nu", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTG_lnu", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tg", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTW_lnu", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTZ_2l2nu_M_1to10", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("TTZ_2l2nu_M_10", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqZG_ll_01j", 2017,args.tag) + ".root",
            #     basedirs[2017] + get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + ".root",
            #     # basedirs[2017] + get_sample_path("tw_dilep", 2017,args.tag) + ".root",

            # ], options=options[2017]),
            # "smallRares": make_obj([
            #     basedirs[2017]+get_sample_path("GGH_ZZTo4L_POWHEG",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("vh_nobb",2017,args.tag)+".root",
            #     basedirs[2017]+get_sample_path("TTHH",2017,args.tag)+".root",
            #     ],options=options[2017]),
            # "GGH_ZZTo4L_POWHEG": make_obj([basedirs[2017]+get_sample_path("GGH_ZZTo4L_POWHEG", 2017,args.tag) + ".root",], options=options[2017]),
            # "qqww": make_obj([basedirs[2017]+get_sample_path("qqww", 2017,args.tag) + ".root",], options=options[2017]),
            # "tzq": make_obj([basedirs[2017]+get_sample_path("tzq", 2017,args.tag) + ".root",], options=options[2017]),
            # "vh_nobb": make_obj([basedirs[2017]+get_sample_path("vh_nobb", 2017,args.tag) + ".root",], options=options[2017]),
            # "WWW": make_obj([basedirs[2017]+get_sample_path("WWW", 2017,args.tag) + ".root",], options=options[2017]),
            # "wwz": make_obj([basedirs[2017]+get_sample_path("wwz", 2017,args.tag) + ".root",], options=options[2017]),
            # "qqWZ_3lnu_MG": make_obj([basedirs[2017]+get_sample_path("qqWZ_3lnu_MG", 2017,args.tag) + ".root",], options=options[2017]),
            # "qqWW_2l2nu": make_obj([basedirs[2017]+get_sample_path("qqWW_2l2nu", 2017,args.tag) + ".root",], options=options[2017]),
            # "WZG": make_obj([basedirs[2017]+get_sample_path("WZG", 2017,args.tag) + ".root",], options=options[2017]),
            # "WWG": make_obj([basedirs[2017]+get_sample_path("WWG", 2017,args.tag) + ".root",], options=options[2017]),
            # "WZZ": make_obj([basedirs[2017]+get_sample_path("WZZ", 2017,args.tag) + ".root",], options=options[2017]),
            # "qqZZ_4l": make_obj([basedirs[2017]+get_sample_path("qqZZ_4l", 2017,args.tag) + ".root",], options=options[2017]),
            # "ZZZ": make_obj([basedirs[2017]+get_sample_path("ZZZ", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTTJ": make_obj([basedirs[2017]+get_sample_path("TTTJ", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTTW": make_obj([basedirs[2017]+get_sample_path("TTTW", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTTT": make_obj([basedirs[2017]+get_sample_path("TTTT", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTZH": make_obj([basedirs[2017]+get_sample_path("TTZH", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTWZ": make_obj([basedirs[2017]+get_sample_path("TTWZ", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTWH": make_obj([basedirs[2017]+get_sample_path("TTWH", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTWW": make_obj([basedirs[2017]+get_sample_path("TTWW", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTZZ": make_obj([basedirs[2017]+get_sample_path("TTZZ", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTHH": make_obj([basedirs[2017]+get_sample_path("TTHH", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTH_HToNonBB": make_obj([basedirs[2017]+get_sample_path("TTH_HToNonBB", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTG_2l2nu": make_obj([basedirs[2017]+get_sample_path("TTG_2l2nu", 2017,args.tag) + ".root",], options=options[2017]),
            # "tg": make_obj([basedirs[2017]+get_sample_path("tg", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTW_lnu": make_obj([basedirs[2017]+get_sample_path("TTW_lnu", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTZ_2l2nu_M_1to10": make_obj([basedirs[2017]+get_sample_path("TTZ_2l2nu_M_1to10", 2017,args.tag) + ".root",], options=options[2017]),
            # "TTZ_2l2nu_M_10": make_obj([basedirs[2017]+get_sample_path("TTZ_2l2nu_M_10", 2017,args.tag) + ".root",], options=options[2017]),
            # "qqZG_ll_01j": make_obj([basedirs[2017]+get_sample_path("qqZG_ll_01j", 2017,args.tag) + ".root",], options=options[2017]),
            # "qqWG_lnu_nlo_01j": make_obj([basedirs[2017]+get_sample_path("qqWG_lnu_nlo_01j", 2017,args.tag) + ".root",], options=options[2017]),
            # "tw_dilep": make_obj(basedirs[2017] + get_sample_path("tw_dilep", 2017,args.tag) + ".root", options=options[2017]),
            # "multiboson": make_obj([
            #     basedirs[2017]+get_sample_path("qqww", 2017,args.tag) + ".root",
            #     basedirs[2017]+get_sample_path("qqWZ_3lnu_MG", 2017,args.tag) + ".root",
            #     basedirs[2017]+get_sample_path("qqZZ_4l", 2017,args.tag) + ".root",
            #     basedirs[2017]+get_sample_path("WWW", 2017,args.tag) + ".root",
            #     basedirs[2017]+get_sample_path("wwz", 2017,args.tag) + ".root",
            #     basedirs[2017]+get_sample_path("WZZ", 2017,args.tag) + ".root",
            #     basedirs[2017]+get_sample_path("ZZZ", 2017,args.tag) + ".root",
            #     ],options=options[2017]),
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
            # "fakes": make_obj([
            #     # basedirs[2018] + get_sample_path("data", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTW_lnu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZ_2l2nu_M_1to10", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZ_2l2nu_M_10", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTH_HToNonBB", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("qqWZ_3lnu_MG", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doFakes doData "),
            # # "flips": make_obj(basedirs[2018] + get_sample_path("data", 2018,args.tag) + ".root",options=options[2018] + " doFlips doData "),
            # "data": make_obj([
            #     datadirs[2018] + get_sample_path("double_muon_data", 2018,args.tag) + ".root",
            #     datadirs[2018] + get_sample_path("eg_data", 2018,args.tag) + ".root",
            #     datadirs[2018] + get_sample_path("muon_eg_data", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doData "),
            # "signal_tuh": make_obj([
            #     basedirs[2018]+get_sample_path("signal_hut_ST",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("signal_hut_atop",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("signal_hut_top",2018,args.tag)+".root",
            #     ] , options=options[2018]),
            "signal_tch": make_obj(
                glob.glob(basedirs[2018] + get_sample_path("TTTT", 2018,args.tag) + '*.root'), options=options[2018]),
            "fakes_mc": make_obj(
                glob.glob(basedirs[2018] + get_sample_path("TTJets", 2018,args.tag) + ".root")
                # basedirs[2018] + get_sample_path("TT_2l2nu", 2018,args.tag) + ".root",
                # basedirs[2018] + get_sample_path("TT_lnu_nlo", 2018,args.tag) + ".root",
                + glob.glob(basedirs[2018] + get_sample_path("WJets_lnu_lo", 2018,args.tag) + ".root")
                + glob.glob(basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root")
                + glob.glob(basedirs[2018] + get_sample_path("DY_2l_M_10to50", 2018,args.tag) + ".root")
                + glob.glob(basedirs[2018] + get_sample_path("DY_2l_M_50", 2018,args.tag) + ".root")
                , options=options[2018] + " doTruthFake doStitch "),
            "flips_mc": make_obj(
                glob.glob(basedirs[2018] + get_sample_path("TTJets", 2018,args.tag) + "*.root")
                # basedirs[2018] + get_sample_path("TT_2l2nu", 2018,args.tag) + ".root",
                + glob.glob(basedirs[2018] + get_sample_path("DY_2l_M_10to50", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("DY_2l_M_50", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("qqWW_2l2nu", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("qqZG_ll_01j", 2018,args.tag) + "*.root")

                , options=options[2018] + "doTruthFlip doStitch"),
            # "top": make_obj([
            #     basedirs[2018] + get_sample_path("TT_2l2nu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TT_lnu_nlo", 2018,args.tag) + ".root",
            #     # # basedirs[2018] + get_sample_path("TTJets", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("tw_top", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("tw_atop", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTG_2l2nu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTG_lnu", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doStitch"),
            # "wboson": make_obj([
            #     basedirs[2018] + get_sample_path("WJets_lnu_lo", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doStitch"),
            # "otherFakes": make_obj([
            #     basedirs[2018] + get_sample_path("tw_top", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("tw_atop", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doTruthFake doStitch "),
            # "tw": make_obj([
            #     # basedirs[2018] + get_sample_path("TT_2l2nu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTJets", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("tw_top", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("tw_atop", 2018,args.tag) + ".root",

            #     ], options=options[2018] + " doStitch"),
            # "dy": make_obj([
            #     basedirs[2018] + get_sample_path("DY_2l_M_10to50", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("DY_2l_M_50", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doStitch"),
            # "TTJets": make_obj([
            #     basedirs[2018]+get_sample_path("TTJets", 2018,args.tag) + ".root",
            #     ], options=options[2018]),
            # "WJets_lnu_lo": make_obj([
            #     basedirs[2018]+get_sample_path("WJets_lnu_lo", 2018,args.tag) + ".root",
            #     ], options=options[2018]),
            # "tw_dilep": make_obj(basedirs[2018] + get_sample_path("tw_dilep", 2018,args.tag) + ".root", options=options[2018]),
            # "TTW_lnu": make_obj(basedirs[2018] + get_sample_path("TTW_lnu", 2018,args.tag) + ".root", options=options[2018]),
            # "tth": make_obj(basedirs[2018] + get_sample_path("TTH_HToNonBB", 2018,args.tag) + ".root", options=options[2018]),
            # "ttz": make_obj([
            #     basedirs[2018] + get_sample_path("TTZ_2l2nu_M_1to10", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZ_2l2nu_M_10", 2018,args.tag) + ".root",
            #     ], options=options[2018]),
            # "ttz_m1_10": make_obj(basedirs[2018] + get_sample_path("TTZ_2l2nu_M_1to10", 2018,args.tag) + ".root", options=options[2018]),
            # "TTZ_2l2nu_M_10": make_obj(basedirs[2018] + get_sample_path("TTZ_2l2nu_M_10", 2018,args.tag) + ".root", options=options[2018]),
            # "xg": make_obj([
            #     # basedirs[2018] + get_sample_path("tg", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTG_2l2nu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTG_lnu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WWG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WZG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqZG_ll_01j", 2018,args.tag) + ".root",
            #     ], options=options[2018] + " doXgamma "),
            # "tg": make_obj(basedirs[2018] + get_sample_path("tg", 2018,args.tag) + ".root", options=options[2018] + " doXgamma "),
            # "TTG_2l2nu": make_obj(basedirs[2018] + get_sample_path("TTG_2l2nu", 2018,args.tag) + ".root", options=options[2018] + " doXgamma "),
            # "TTG_lnu": make_obj(basedirs[2018] + get_sample_path("TTG_lnu", 2018,args.tag) + ".root", options=options[2018] + " doXgamma "),
            # "qqWG_lnu_nlo_01j": make_obj(basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root", options=options[2018] + " doXgamma "),
            # "qqZG_ll_01j": make_obj(basedirs[2018] + get_sample_path("qqZG_ll_01j", 2018,args.tag) + ".root", options=options[2018] + " doXgamma "),
            # "TTH_HToNonBB": make_obj([basedirs[2018]+get_sample_path("TTH_HToNonBB", 2018,args.tag) + ".root",], options=options[2018]),
            # "TTHH": make_obj(basedirs[2018] + get_sample_path("TTHH", 2018,args.tag) + ".root", options=options[2018]),
            # "TTWH": make_obj(basedirs[2018] + get_sample_path("TTWH", 2018,args.tag) + ".root", options=options[2018]),
            # "TTWW": make_obj(basedirs[2018] + get_sample_path("TTWW", 2018,args.tag) + ".root", options=options[2018]),
            # "TTWZ": make_obj(basedirs[2018] + get_sample_path("TTWZ", 2018,args.tag) + ".root", options=options[2018]),
            # "TTZH": make_obj(basedirs[2018] + get_sample_path("TTZH", 2018,args.tag) + ".root", options=options[2018]),
            # "TTZZ": make_obj(basedirs[2018] + get_sample_path("TTZZ", 2018,args.tag) + ".root", options=options[2018]),
            # "ttvv": make_obj([
            #     # basedirs[2018] + get_sample_path("TTTT", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTTW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTTJ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZZ", 2018,args.tag) + ".root",
            #     ], options=options[2018]),
            # "ttx": make_obj([
            #     basedirs[2018]+get_sample_path("TTH_HToNonBB",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("TTZ_2l2nu_M_1to10",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("TTZ_2l2nu_M_10",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("tzq",2018,args.tag)+".root",
            #     # basedirs[2018]+get_sample_path("tw_dilep",2018,args.tag)+".root",
            #     ],options=options[2018]),
            "rares": make_obj(
                glob.glob(basedirs[2018] + get_sample_path("GGH_ZZTo4L_POWHEG", 2018,args.tag) + "*.root")
                # basedirs[2018] + get_sample_path("qqww", 2018,args.tag) + ".root",
                # basedirs[2018] + get_sample_path("tzq", 2018,args.tag) + ".root",
                # basedirs[2018] + get_sample_path("vh_nobb", 2018,args.tag) + ".root",
                + glob.glob(basedirs[2018] + get_sample_path("WWW", 2018,args.tag) + "*.root")
                # basedirs[2018] + get_sample_path("wwz", 2018,args.tag) + ".root",
                + glob.glob(basedirs[2018] + get_sample_path("qqWZ_3lnu_MG", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("WZG", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("WWG", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("WZZ", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("qqZZ_4l", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("ZZZ", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTTJ", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTTW", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTWH", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTWW", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTZH", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTWZ", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTZZ", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTHH", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTH_HToNonBB", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTG_2l2nu", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTG_lnu", 2018,args.tag) + "*.root")
                # basedirs[2018] + get_sample_path("tg", 2018,args.tag) + ".root",
                # basedirs[2018] + get_sample_path("tw_dilep", 2018,args.tag) + ".root"
                + glob.glob(basedirs[2018] + get_sample_path("TTW_lnu", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTZ_2l2nu_M_1to10", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("TTZ_2l2nu_M_10", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("qqZG_ll_01j", 2018,args.tag) + "*.root")
                + glob.glob(basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + "*.root") 
                , options=options[2018]),
            
            # "nonleadingrares": make_obj([
            #     # basedirs[2018] + get_sample_path("TT_2l2nu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TT_lnu_nlo", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("WJets_lnu_lo", 2018,args.tag) + ".root",

            #     basedirs[2018] + get_sample_path("GGH_ZZTo4L_POWHEG", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("qqww", 2018,args.tag) + ".root",
            #     ###basedirs[2018] + get_sample_path("twz", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("tzq", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("vh_nobb", 2018,args.tag) + ".root",
            #     ###basedirs[2018] + get_sample_path("ww_dps", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WWW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("wwz", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqWZ_3lnu_MG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WZG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WWG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WZZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqZZ_4l", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("ZZZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTTJ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTTW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTHH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTH_HToNonBB", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTG_2l2nu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTG_lnu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("tg", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTW_lnu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTZ_2l2nu_M_1to10", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TTZ_2l2nu_M_10", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqZG_ll_01j", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("tw_dilep", 2018,args.tag) + ".root",

            # ], options=options[2018]),
            # "os_rares": make_obj([
            #     # basedirs[2018] + get_sample_path("TT_2l2nu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("TT_lnu_nlo", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("WJets_lnu_lo", 2018,args.tag) + ".root",

            #     basedirs[2018] + get_sample_path("GGH_ZZTo4L_POWHEG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqww", 2018,args.tag) + ".root",
            #     #basedirs[2018] + get_sample_path("twz", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("tzq", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("vh_nobb", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WWW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("wwz", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqWZ_3lnu_MG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WZG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WWG", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("WZZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqZZ_4l", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("ZZZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTTJ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTTW", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTWZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZZ", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTHH", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTH_HToNonBB", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTG_2l2nu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTG_lnu", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("tg", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTW_lnu", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZ_2l2nu_M_1to10", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("TTZ_2l2nu_M_10", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqZG_ll_01j", 2018,args.tag) + ".root",
            #     basedirs[2018] + get_sample_path("qqWG_lnu_nlo_01j", 2018,args.tag) + ".root",
            #     # basedirs[2018] + get_sample_path("tw_dilep", 2018,args.tag) + ".root",

            # ], options=options[2018]),
            # "smallRares": make_obj([
            #     basedirs[2018]+get_sample_path("GGH_ZZTo4L_POWHEG",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("vh_nobb",2018,args.tag)+".root",
            #     basedirs[2018]+get_sample_path("TTHH",2018,args.tag)+".root",
            #     ],options=options[2018]),
            # "GGH_ZZTo4L_POWHEG": make_obj(basedirs[2018] + get_sample_path("GGH_ZZTo4L_POWHEG", 2018,args.tag) + ".root", options=options[2018]),
            # "qqww": make_obj(basedirs[2018] + get_sample_path("qqww", 2018,args.tag) + ".root", options=options[2018]),
            # "tzq": make_obj(basedirs[2018] + get_sample_path("tzq", 2018,args.tag) + ".root", options=options[2018]),
            # "vh_nobb": make_obj(basedirs[2018] + get_sample_path("vh_nobb", 2018,args.tag) + ".root", options=options[2018]),
            # "WWW": make_obj(basedirs[2018] + get_sample_path("WWW", 2018,args.tag) + ".root", options=options[2018]),
            # "wwz": make_obj(basedirs[2018] + get_sample_path("wwz", 2018,args.tag) + ".root", options=options[2018]),
            # "qqWZ_3lnu_MG": make_obj(basedirs[2018] + get_sample_path("qqWZ_3lnu_MG", 2018,args.tag) + ".root", options=options[2018]),
            # "qqWW_2l2nu": make_obj(basedirs[2018] + get_sample_path("qqWW_2l2nu", 2018,args.tag) + ".root", options=options[2018]),
            # "WZG": make_obj(basedirs[2018] + get_sample_path("WZG", 2018,args.tag) + ".root", options=options[2018]),
            # "WWG": make_obj(basedirs[2018] + get_sample_path("WWG", 2018,args.tag) + ".root", options=options[2018]),
            # "WZZ": make_obj(basedirs[2018] + get_sample_path("WZZ", 2018,args.tag) + ".root",options=options[2018]),
            # "qqZZ_4l": make_obj(basedirs[2018] + get_sample_path("qqZZ_4l", 2018,args.tag) + ".root",options=options[2018]),
            # "ZZZ": make_obj(basedirs[2018] + get_sample_path("ZZZ", 2018,args.tag) + ".root",options=options[2018]),
            # "TTTJ": make_obj(basedirs[2018] + get_sample_path("TTTJ", 2018,args.tag) + ".root",options=options[2018]),
            # "TTTW": make_obj(basedirs[2018] + get_sample_path("TTTW", 2018,args.tag) + ".root",options=options[2018]),
            # "TTTT": make_obj(basedirs[2018] + get_sample_path("TTTT", 2018,args.tag) + ".root",options=options[2018]),
            # "multiboson": make_obj([
            #     basedirs[2018]+get_sample_path("qqww", 2018,args.tag) + ".root",
            #     basedirs[2018]+get_sample_path("qqWZ_3lnu_MG", 2018,args.tag) + ".root",
            #     basedirs[2018]+get_sample_path("qqZZ_4l", 2018,args.tag) + ".root",
            #     basedirs[2018]+get_sample_path("WWW", 2018,args.tag) + ".root",
            #     basedirs[2018]+get_sample_path("wwz", 2018,args.tag) + ".root",
            #     basedirs[2018]+get_sample_path("WZZ", 2018,args.tag) + ".root",
            #     basedirs[2018]+get_sample_path("ZZZ", 2018,args.tag) + ".root",
            #     ],options=options[2018]),

       }
    }

    if args.verbosity>=1:
        print(basedirs[2016]+get_sample_path("TTW_lnu",2016,args.tag)+".root")

    do_slim = args.slim

    def run_chain(xxx_todo_changeme):
        (index,info) = xxx_todo_changeme
        ch, title, options, outputdir = info
        t0 = time.time()
        ret = r.event_looper(ch,title,options,args.nevts,outputdir)
        t1 = time.time()
        return index, [ret, title, t1-t0]

    to_run = []
    already_done = []
    if args.skip_already_done and os.path.exists("../limits/{}/".format(args.tag)):
        parse = lambda x: x.rsplit("/",1)[1].split("_histos")[0]
        already_done = list(map(parse,glob.glob("../limits/{}/*_srhh_2016.root".format(args.tag))))
        print("Skipping up to {} processes (e.g., {}, ...)".format(len(already_done),already_done[0]))
    for year in years_to_consider:
        if (args.year) and (year != args.year): continue
        print((list(chs[year].keys())))
        for proc in list(chs[year].keys()):
            # if (len(args.proc) > 0) and (proc != args.proc): continue
            if (len(myprocs) > 0) and len(fnmatch.filter(myprocs,proc))==0: continue
            if (len(excludeprocs) > 0) and len(fnmatch.filter(excludeprocs,proc))>0: continue
            if args.skip_already_done and (proc in already_done): continue
            obj = chs[year][proc]
            opts = obj["options"]
            if args.verbosity >= 1:
                opts = opts.replace("quiet","")
            if args.year and len(myprocs)==1 and len(fnmatch.filter(myprocs,'*'))==0:  # if one process, show the progress bar
                opts = opts.replace("quiet","")
            if args.verbosity == 0:
                opts += " quiet"
            if args.debug:
                opts += " printDebugFile"
            # Change chain titles to proc so that we output the right root file name
            chTitle = r.TString("{}".format(proc))
            to_run.append([obj["ch"], chTitle, opts, outputdir])
            if args.verbosity >= 2:
                print("Adding:", obj["ch"].GetTitle(), opts, outputdir, year)

    if args.maxprocs > 0:
        print("Actually, you specified a maximum of {} chains, so taking the first ones".format(args.maxprocs))
        to_run = to_run[:args.maxprocs]

    os.system("mkdir -p {}".format(outputdir))

    # Make sure all the requested root files actually exist
    for ch,title,opts,_ in to_run:
        for fname in [str(x) for x in ch]:
            #print fname
            if not os.path.exists(fname):
                print("[!] {} does not exist!".format(fname))

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
            print("[!] You might want to kill this at some point and run the rest with --skip_already_done because of memory leaks")

        # Now run them
        if len(to_run) == 1:
            print("Running one chain")
            list(map(run_chain,enumerate(to_run)))
            print("Done")
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


            signames = ["TTTT"]
            if args.ss:
                signames = ["fs_t1TTTT_m1600_m600"]
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

    print("end")
