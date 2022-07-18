#!/usr/bin/env python
import json
import ROOT
import os
import sys
import argparse
import fnmatch
import operator
import glob
import ast
import time
import samples
from samples import get_sample_path


if __name__ == "__main__":
	
	parser = argparse.ArgumentParser()
	parser.add_argument("-y", "--year", help="year, if you only want to run one", default="")
	parser.add_argument(      "--proc", help="process, if you only want to run one/some. accepts wildcards if quoted.", default="", type=str)

	
	args = parser.parse_args()
	myprocs = args.proc.strip().split(',')
	print(len(myprocs))

	try:
		args.year = int(args.year)
	except:
		pass

	years_to_consider = [
		2016,
        2017,
       	2018,
        ]

	basedirs = {
        2016: '/ceph/cms/store/group/tttt/Skims/220705/2016_APV/',
        2017: '/ceph/cms/store/group/tttt/Skims/220705/2017/',
        2018: '/ceph/cms/store/group/tttt/Skims/220705/2018/',
        }

	chs = {
		2016: {
            "tttt":["DY_2l_M_10to50", "DY_2l_M_50","GGH_ZZTo4L_POWHEG","ST_tW_antitop_5f_NoFullyHadronicDecays",
            "ST_tW_top_5f_NoFullyHadronicDecays","TTGJets","TTG_2l2nu","TTG_lnu","TTHH","TTH_HToNonBB","TTJets","TTTJ","TTTT","TTTW",
            "TTWH","TTWW","TTWZ","TTW_lnu","TTZH","TTZZ","TTZ_2l2nu_M_10","TTZ_2l2nu_M_1to10","TT_2l2nu","TT_lnu_antitop_lo",
            "TT_lnu_nlo","TT_lnu_top_lo","WJets_lnu_0j","WJets_lnu_1j","WJets_lnu_2j","WJets_lnu_HT_100-200","WJets_lnu_HT_1200-2500",
            "WJets_lnu_HT_1200-2500_ext","WJets_lnu_HT_200-400","WJets_lnu_HT_2500-inf","WJets_lnu_HT_2500-inf_ext","WJets_lnu_HT_400-600",
            "WJets_lnu_HT_400-600_ext","WJets_lnu_HT_600-800","WJets_lnu_HT_600-800_ext","WJets_lnu_HT_70-100","WJets_lnu_HT_800-1200",
            "WJets_lnu_HT_800-1200_ext","WWG","WWW_4f","WWW_4f_ext","WZG","WZZ","WZZ_ext","ZZZ","ZZZ_ext","qqWG_lnu_lo","qqWG_lnu_nlo_01j",
            "qqWW_2l2nu","qqWZ_3lnu_MG","qqWZ_3lnu_POWHEG","qqZG_ll_01j","qqZZ_4l",
            ],
            "all": ["DY_2l_M_10to50", "DY_2l_M_50","DoubleEG_2016B-ver1","DoubleEG_2016B-ver2","DoubleEG_2016C","DoubleEG_2016D",
            "DoubleEG_2016E","DoubleEG_2016F","DoubleMuon_2016B-ver1","DoubleMuon_2016B-ver2","DoubleMuon_2016C","DoubleMuon_2016D",
            "DoubleMuon_2016E","DoubleMuon_2016F","GGH_ZZTo4L_POWHEG","HTMHT_2016B-ver1","HTMHT_2016B-ver2","HTMHT_2016C",
            "HTMHT_2016D","HTMHT_2016E","HTMHT_2016F","JetHT_2016B-ver1","JetHT_2016B-ver2","JetHT_2016C","JetHT_2016D",
            "JetHT_2016E","JetHT_2016F","MET_2016B-ver1","MET_2016B-ver2","MET_2016C","MET_2016D","MET_2016E","MET_2016F",
            "MuonEG_2016B-ver1","MuonEG_2016B-ver2","MuonEG_2016C","MuonEG_2016D","MuonEG_2016E","MuonEG_2016F",
            "ST_tW_antitop_5f_NoFullyHadronicDecays","ST_tW_top_5f_NoFullyHadronicDecays","SingleElectron_2016B-ver1",
            "SingleElectron_2016B-ver2","SingleElectron_2016C","SingleElectron_2016D","SingleElectron_2016E","SingleElectron_2016F",
            "SingleMuon_2016B-ver1","SingleMuon_2016B-ver2","SingleMuon_2016C","SingleMuon_2016D","SingleMuon_2016E",
            "SingleMuon_2016F","SinglePhoton_2016B-ver1","SinglePhoton_2016B-ver2","SinglePhoton_2016C","SinglePhoton_2016D",
            "SinglePhoton_2016E","SinglePhoton_2016F","TTGJets","TTG_2l2nu","TTG_lnu","TTHH","TTH_HToNonBB","TTJets","TTTJ","TTTT",
            "TTTW","TTWH","TTWW","TTWZ","TTW_lnu","TTZH","TTZZ","TTZ_2l2nu_M_10","TTZ_2l2nu_M_1to10","TT_2l2nu","TT_lnu_antitop_lo",
            "TT_lnu_nlo","TT_lnu_top_lo","WJets_lnu_0j","WJets_lnu_1j","WJets_lnu_2j","WJets_lnu_HT_100-200","WJets_lnu_HT_1200-2500",
            "WJets_lnu_HT_1200-2500_ext","WJets_lnu_HT_200-400","WJets_lnu_HT_2500-inf","WJets_lnu_HT_2500-inf_ext",
            "WJets_lnu_HT_400-600","WJets_lnu_HT_400-600_ext","WJets_lnu_HT_600-800","WJets_lnu_HT_600-800_ext","WJets_lnu_HT_70-100",
            "WJets_lnu_HT_800-1200","WJets_lnu_HT_800-1200_ext","WWG","WWW_4f","WWW_4f_ext","WZG","WZZ","WZZ_ext","ZZZ","ZZZ_ext",
            "qqWG_lnu_lo","qqWG_lnu_nlo_01j","qqWW_2l2nu","qqWZ_3lnu_MG","qqWZ_3lnu_POWHEG","qqZG_ll_01j","qqZZ_4l"
            ],
   		},
        2017: {
            "tttt":["DY_2l_M_10to50","DY_2l_M_50","GGH_ZZTo4L_POWHEG","ST_tW_antitop_5f_NoFullyHadronicDecays",
            "ST_tW_top_5f_NoFullyHadronicDecays","TTGJets","TTG_2l2nu","TTG_lnu","TTHH","TTH_HToNonBB","TTJets","TTTJ","TTTT","TTTW",
            "TTWH","TTWW","TTWZ","TTW_lnu","TTZH","TTZZ","TTZ_2l2nu_M_10","TTZ_2l2nu_M_1to10","TT_2l2nu","TT_lnu_antitop_lo","TT_lnu_nlo",
            "TT_lnu_top_lo","WJets_lnu_0j","WJets_lnu_1j","WJets_lnu_2j","WJets_lnu_HT_100-200","WJets_lnu_HT_1200-2500",
            "WJets_lnu_HT_200-400","WJets_lnu_HT_2500-inf","WJets_lnu_HT_400-600","WJets_lnu_HT_600-800","WJets_lnu_HT_70-100",
            "WJets_lnu_HT_800-1200","WJets_lnu_lo","WWG","WWW_4f","WWW_4f_ext","WZG","WZZ","WZZ_ext","ZZZ","ZZZ_ext","qqWG_lnu_lo",
            "qqWG_lnu_nlo_01j","qqWW_2l2nu","qqWZ_3lnu_MG","qqWZ_3lnu_POWHEG","qqZG_ll_01j","qqZZ_4l",
            ],
            "all": ["DY_2l_M_10to50","DY_2l_M_50","DoubleEG_2017B","DoubleEG_2017C","DoubleEG_2017D","DoubleEG_2017E","DoubleEG_2017F",
            "DoubleMuon_2017B","DoubleMuon_2017C","DoubleMuon_2017D","DoubleMuon_2017E","DoubleMuon_2017F","GGH_ZZTo4L_POWHEG",
            "HTMHT_2017B","HTMHT_2017C","HTMHT_2017D","HTMHT_2017E","HTMHT_2017F","JetHT_2017B","JetHT_2017C","JetHT_2017D","JetHT_2017E",
            "JetHT_2017F","MET_2017B","MET_2017C","MET_2017D","MET_2017E","MET_2017F","MuonEG_2017B","MuonEG_2017C","MuonEG_2017D",
            "MuonEG_2017E","MuonEG_2017F","ST_tW_antitop_5f_NoFullyHadronicDecays","ST_tW_top_5f_NoFullyHadronicDecays","SingleElectron_2017B",
            "SingleElectron_2017C","SingleElectron_2017D","SingleElectron_2017E","SingleElectron_2017F","SingleMuon_2017B",
            "SingleMuon_2017C","SingleMuon_2017D","SingleMuon_2017E","SingleMuon_2017F","SinglePhoton_2017B","SinglePhoton_2017C",
            "SinglePhoton_2017D","SinglePhoton_2017E","SinglePhoton_2017F","TTGJets","TTG_2l2nu","TTG_lnu","TTHH","TTH_HToNonBB","TTJets",
            "TTTJ","TTTT","TTTW","TTWH","TTWW","TTWZ","TTW_lnu","TTZH","TTZZ","TTZ_2l2nu_M_10","TTZ_2l2nu_M_1to10","TT_2l2nu",
            "TT_lnu_antitop_lo","TT_lnu_nlo","TT_lnu_top_lo","WJets_lnu_0j","WJets_lnu_1j","WJets_lnu_2j","WJets_lnu_HT_100-200",
            "WJets_lnu_HT_1200-2500","WJets_lnu_HT_200-400","WJets_lnu_HT_2500-inf","WJets_lnu_HT_400-600","WJets_lnu_HT_600-800",
            "WJets_lnu_HT_70-100","WJets_lnu_HT_800-1200","WJets_lnu_lo","WWG","WWW_4f","WWW_4f_ext","WZG","WZZ","WZZ_ext","ZZZ",
            "ZZZ_ext","qqWG_lnu_lo","qqWG_lnu_nlo_01j","qqWW_2l2nu","qqWZ_3lnu_MG","qqWZ_3lnu_POWHEG","qqZG_ll_01j","qqZZ_4l",
            ],

        },
        2018: {
            "tttt":["DY_2l_M_10to50","DY_2l_M_50","GGH_ZZTo4L_POWHEG","ST_tW_antitop_5f_NoFullyHadronicDecays",
            "ST_tW_top_5f_NoFullyHadronicDecays","TTGJets","TTGJets_ext","TTG_2l2nu","TTG_lnu","TTHH","TTH_HToNonBB","TTJets","TTTJ",
            "TTTT","TTTW","TTWH","TTWW","TTWZ","TTW_lnu","TTZH","TTZZ","TTZ_2l2nu_M_10","TTZ_2l2nu_M_1to10","TT_2l2nu","TT_lnu_nlo",
            "TT_lnu_top_lo","WJets_lnu_0j","WJets_lnu_1j","WJets_lnu_2j","WJets_lnu_HT_100-200","WJets_lnu_HT_1200-2500",
            "WJets_lnu_HT_200-400","WJets_lnu_HT_2500-inf","WJets_lnu_HT_400-600","WJets_lnu_HT_600-800","WJets_lnu_HT_70-100",
            "WJets_lnu_HT_800-1200","WJets_lnu_lo","WWG","WWW_4f","WWW_4f_ext","WZG","WZZ","WZZ_ext","ZZZ","ZZZ_ext","qqWG_lnu_lo",
            "qqWG_lnu_nlo_01j","qqWW_2l2nu","qqWZ_3lnu_MG","qqWZ_3lnu_POWHEG","qqWZ_3lnu_POWHEG_mll_0p1-inf","qqZG_ll_01j","qqZZ_4l",
            ],
            "all": ["DY_2l_M_10to50","DY_2l_M_50","DoubleMuon_2018A","DoubleMuon_2018B","DoubleMuon_2018C","DoubleMuon_2018D",
            "EGamma_2018A","EGamma_2018B","EGamma_2018C","EGamma_2018D","GGH_ZZTo4L_POWHEG","JetHT_2018A","JetHT_2018B","JetHT_2018C",
            "JetHT_2018D","MET_2018A","MET_2018B","MET_2018C","MET_2018D","MuonEG_2018A","MuonEG_2018B","MuonEG_2018C","MuonEG_2018D",
            "ST_tW_antitop_5f_NoFullyHadronicDecays","ST_tW_top_5f_NoFullyHadronicDecays","SingleMuon_2018A","SingleMuon_2018B",
            "SingleMuon_2018C","SingleMuon_2018D","TTGJets","TTGJets_ext","TTG_2l2nu","TTG_lnu","TTHH","TTH_HToNonBB","TTJets","TTTJ",
            "TTTT","TTTW","TTWH","TTWW","TTWZ","TTW_lnu","TTZH","TTZZ","TTZ_2l2nu_M_10","TTZ_2l2nu_M_1to10","TT_2l2nu","TT_lnu_nlo",
            "TT_lnu_top_lo","WJets_lnu_0j","WJets_lnu_1j","WJets_lnu_2j","WJets_lnu_HT_100-200","WJets_lnu_HT_1200-2500",
            "WJets_lnu_HT_200-400","WJets_lnu_HT_2500-inf","WJets_lnu_HT_400-600","WJets_lnu_HT_600-800","WJets_lnu_HT_70-100",
            "WJets_lnu_HT_800-1200","WJets_lnu_lo","WWG","WWW_4f","WWW_4f_ext","WZG","WZZ","WZZ_ext","ZZZ","ZZZ_ext","qqWG_lnu_lo",
            "qqWG_lnu_nlo_01j","qqWW_2l2nu","qqWZ_3lnu_MG","qqWZ_3lnu_POWHEG","qqWZ_3lnu_POWHEG_mll_0p1-inf","qqZG_ll_01j","qqZZ_4l",
            ],
        }
    }

	for year in years_to_consider:
		if (args.year) and (year != args.year): continue
		print(year)
		dictionary = {}
		for proc in list(chs[year].keys()):
			if (args.proc) and (proc != args.proc): continue
			obj = chs[year][proc]
			for o in obj:
				sum_wgts = 0.
				fileset = glob.glob(basedirs[year] + o + "/*.root")
				for file in fileset:
					inFile = ROOT.TFile.Open(file)
					hCounters = inFile.Get("Counters")
					sum_wgts += hCounters.GetBinContent(0,0)
				dictionary[o] = sum_wgts
				print("Completed", o)
		# print(dictionary)
		filename = "sumweight_%s.py" % year
		with open(filename, "w") as output_file:
			title = "sumweight_%s" % year
			output_file.write(title)
			output_file.write(json.dumps(dictionary))


	print("end")
