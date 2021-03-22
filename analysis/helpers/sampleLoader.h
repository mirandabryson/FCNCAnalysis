std::vector<string> loadSamples ( string year, string type ){
    
    vector<string> samples;
    if ( year == "2018" ){
        
        if ( type == "DY" ){
            samples.push_back("DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("DYJetsToLL_M-50_Zpt-150toInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
        
        }else if ( type == "GluGlu" ){//close drell yan, open gluglu
            samples.push_back("GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("GluGluToContinToZZTo2e2mu_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("GluGluToContinToZZTo2e2tau_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("GluGluToContinToZZTo2mu2tau_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("GluGluToContinToZZTo4e_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("GluGluToContinToZZTo4tau_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
        
        }else if ( type == "Top" ){//close gluglu, open top
            samples.push_back("ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_EXT_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_EXT_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TGJets_leptonDecays_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTGamma_SingleLept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTHH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTPlus1Jet_DiLept_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTTJ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTTT_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTTW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext3-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTWH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTWW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTWZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTZH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TTZZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("TT_DiLept_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");

        }else if ( type == "W" ){//close top, open W
            samples.push_back("WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WWG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WWZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WW_DoubleScattering_13TeV-pythia8_TuneCP5_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WW_TuneCP5_13TeV-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");

        }else if ( type == "Z" ){//close W, open Z
            samples.push_back("ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ZZTo4L_TuneCP5_13TeV_powheg_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");

        }else if ( type == "tHX" ){//close Z, open tHX
            samples.push_back("tHW_HToTT_0J_mH-350_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-375_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-400_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-425_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-450_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-475_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-500_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-525_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-550_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-575_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-600_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-625_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHW_HToTT_0J_mH-650_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-350_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-375_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-400_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-425_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-450_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-475_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-500_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-525_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-550_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-575_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-600_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-625_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tHq_HToTT_0J_mH-650_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-350_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-375_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-425_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-450_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-475_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-500_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-525_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-550_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-575_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-625_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("ttH_HToTT_1J_mH-650_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");

        }else if ( type == "other" ){//close tHX, open other
            samples.push_back("VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1");
            samples.push_back("tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1");

        }//close other
    }//close 2018
    
    //return vector of samples
    return samples;
}//close function
