std::string short_to_long (std::string sampleName) {
    std::map< std::string, std::string > m_short_to_long;
    m_short_to_long["dyjets_m50"] = "DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["ttw"] = "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["www"] = "WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["signal_hut_atop"] = "TT_FCNC-aTtoHJ_Tleptonic_HToWWZZtautau_eta_hut_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["wjets_ht800-1200"] = "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["wjets_ht600-800"] = "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["wzz"] = "WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["wz"] = "WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["tg"] = "TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["wzg"] = "WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["tth_nobb"] = "ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["signal_hct_top"] = "TT_FCNC-TtoHJ_aTleptonic_HToWWZZtautau_eta_hct_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["ttg_dilep"] = "TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["tttj"] = "TTTJ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttjets"] = "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM";
    m_short_to_long["tttt"] = "TTTT_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM";
    m_short_to_long["tttw"] = "TTTW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["wjets_ht100-200"] = "WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["tthh"] = "TTHH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["vh_nobb"] = "VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["wjets"] = "WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["signal_hct_atop"] = "TT_FCNC-aTtoHJ_Tleptonic_HToWWZZtautau_eta_hct_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["wjets_ht400-600"] = "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["tzq"] = "tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttwh"] = "TTWH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttg_1lep"] = "TTGamma_SingleLept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["dyjets_m10-50"] = "DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["zg"] = "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM";
    m_short_to_long["wwz"] = "WWZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["wwg"] = "WWG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttwz"] = "TTWZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["zz"] = "ZZTo4L_TuneCP5_13TeV_powheg_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM";
    m_short_to_long["ttww"] = "TTWW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM";
    m_short_to_long["wjets_ht200-400"] = "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["wg"] = "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttz_m10"] = "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["qqww"] = "WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["zzz"] = "ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ww"] = "WWTo2L2Nu_DoubleScattering_13TeV-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["signal_hut_top"] = "TT_FCNC-TtoHJ_aTleptonic_HToWWZZtautau_eta_hut_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["data"] = "";
    m_short_to_long["ggh"] = "GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["ttzh"] = "TTZH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttz_m1-10"] = "TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM";
    m_short_to_long["tw_dilep"] = "ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";
    m_short_to_long["ttzz"] = "TTZZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM";

    return m_short_to_long[sampleName]:
}

double getXSec( string sampleName ){
    map< string, double > xsecs;

    xsecs["ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.01123;
    xsecs["TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM"] = 831.762;
    xsecs["TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 2.967;
    xsecs["WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 405.271;
    xsecs["WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 1345;
    xsecs["WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 359.7;
    xsecs["WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 48.91;
    xsecs["WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 12.05;
    xsecs["WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 5.501;
    xsecs["WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 61334.9;
    xsecs["WWG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.2147;
    xsecs["WWTo2L2Nu_DoubleScattering_13TeV-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.16975;
    xsecs["WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.2086;
    xsecs["WWZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.1651;
    xsecs["WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.04123;
    xsecs["WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 4.4297;
    xsecs["WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.05565;
    xsecs["WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.05390;
    xsecs["ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM"] = 405.271;
    xsecs["ZZTo4L_TuneCP5_13TeV_powheg_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM"] = 1.256;
    xsecs["ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.01398;
    xsecs["GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.01181;
    xsecs["TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.632;
    xsecs["TTGamma_SingleLept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.77;
    xsecs["TTHH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.000757;
    xsecs["TTTJ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.000474;
    xsecs["TTTT_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM"] = 0.01197;
    xsecs["TTTW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.000788;
    xsecs["TTWH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.001582;
    xsecs["TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.2043;
    xsecs["TTWW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM"] = 0.01150;
    xsecs["TTWZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.003884;
    xsecs["TTZH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.001535;
    xsecs["TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.2529;
    xsecs["TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.0493;
    xsecs["TTZZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.001982;
    xsecs["DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 18610;
    xsecs["DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 6020.85;
    xsecs["VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 2.1360;
    xsecs["tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM"] = 0.0758;
    xsecs["ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 0.2710;
    xsecs["TT_FCNC-TtoHJ_aTleptonic_HToWWZZtautau_eta_hut_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 83.88144;
    xsecs["TT_FCNC-aTtoHJ_Tleptonic_HToWWZZtautau_eta_hut_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 83.88144;
    xsecs["TT_FCNC-TtoHJ_aTleptonic_HToWWZZtautau_eta_hct_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 83.88144;
    xsecs["TT_FCNC-aTtoHJ_Tleptonic_HToWWZZtautau_eta_hct_TuneCP5-MadGraph5-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_tauDecays_102X_upgrade2018_realistic_v21-v1_NANOAODSIM"] = 83.88144;

    double xsecForWeight = xsecs[ short_to_long(sampleName) ];

    return xsecForWeight;
}
