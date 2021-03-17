//Basic looper to categorize FCNC events
//Compile and run with root -l event_looper.C+
//March 2021
//Kaitlin Salyer

#include <iostream>
//#include <cmath>
#include <cstdlib>
#include <chrono>
#include <TChain.h>
#include <TLeaf.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>


using namespace std;
using namespace std::chrono;

//useful functions

float deltaR( float obj1_eta, float obj1_phi, float obj2_eta, float obj2_phi ){
    float deltaEta = obj1_eta - obj2_eta;
    float deltaPhi = obj1_phi - obj2_phi;

    float deltaR = sqrt( pow( deltaEta, 2 ) + pow( deltaPhi, 2 ) );
    
    return deltaR;
}

bool isTightLepton( float pdgid, float pt, float eta, float miniIso_all, bool tight_id ){

    bool isTight = 0;
    if ( abs( eta ) < 2.4 ){
        if ( abs( pdgid ) == 11 && pt > 25 && miniIso_all < 0.12 ){
            isTight = 1;
        }else if( abs( pdgid ) ==13 && pt > 20 && tight_id == 1 and miniIso_all < 0.16 ){
            isTight = 1;
        }else {
            isTight = 0;
        }
    }else {
        isTight = 0;
    }
    return isTight;

}

bool isLooseLepton( float pdgid, float pt, float eta, float miniIso_all, bool loose_id ){
    
    bool isLoose = 0;
    if ( abs( eta ) <2.4 ){
        if ( pdgid==11 and pt>25 and miniIso_all > 0.12 and miniIso_all < 0.4 ){
            isLoose = 1;
        }else if ( pdgid==13 and pt>20 and loose_id == 1 and miniIso_all > 0.12 and miniIso_all < 0.4 ){
            isLoose = 1;
        }else {
            isLoose = 0;
        }
    }else {
        isLoose = 0;
    }
    return isLoose;
}

bool isGoodJet(float pt, float eta){
  
    bool isGood = 0;
    
    if ( pt > 25 && abs( eta ) < 2.4 ){      
        isGood = 1;
    }else{
        isGood = 0;
    }
    return isGood;
}

void saveFig(TH1F hist, string hist_name, string outdir){
    auto can = new TCanvas( "c", "c", 800, 800 );

    TPad *pad1 = new TPad( "pad1", "pad1", 0, 0.3, 1, 1.0 );
    pad1->Draw();

    pad1->cd();
    hist.Draw();

    string filename = outdir.append(hist_name);
    string filename_pdf = filename.append(".pdf");
    string filename_png = filename.append(".png");

    can->SaveAs(filename_pdf.c_str());
    can->SaveAs(filename_png.c_str());
}

void event_looper()
{
    /*TChain DY("Events");
    TChain GluGlu("Events");
    TChain Top("Events");
    TChain W("Events");
    TChain Z("Events");
    TChain tHX("Events");
    TChain other("Events");
    
    vector<string> years = {"2016", "2017", "2018"};
    vector<TChain> backgrounds = {  DY,
                                    GluGlu,
                                    Top,
                                    W,
                                    Z,
                                    tHX,
                                    other
                                };
    vector< vector< string > > = {  {   "DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "DYJetsToLL_M-50_Zpt-150toInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1"
                                    },
                                    {   "GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "GluGluToContinToZZTo2e2mu_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "GluGluToContinToZZTo2e2tau_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "GluGluToContinToZZTo2mu2tau_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "GluGluToContinToZZTo4e_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "GluGluToContinToZZTo4mu_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "GluGluToContinToZZTo4tau_13TeV_MCFM701_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1"
                                    },
                                    {   "ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_EXT_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_EXT_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "ST_tWll_5f_LO_TuneCP5_PSweights_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TGJets_leptonDecays_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "TTGamma_SingleLept_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "TTHH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "TTJets_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1",
                                        "TTPlus1Jet_DiLept_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTTJ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTTT_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1",
                                        "TTTW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext3-v1_NANOAODSIM_fcnc_v1",
                                        "TTWH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTWW_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1",
                                        "TTWZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTZH_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "TTZZ_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "TT_DiLept_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1"
                                    },
                                    {   "WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WWG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WWZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WW_DoubleScattering_13TeV-pythia8_TuneCP5_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WW_TuneCP5_13TeV-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1",
                                        "WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1"
                                    },
                                    {   "ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1",
                                        "ZZTo4L_TuneCP5_13TeV_powheg_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext2-v1_NANOAODSIM_fcnc_v1",
                                        "ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1"
                                    },
                                    {   "tHW_HToTT_0J_mH-350_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-375_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-400_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-425_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-450_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-475_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-500_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-525_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-550_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-575_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-600_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-625_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHW_HToTT_0J_mH-650_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-350_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-375_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-400_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-425_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-450_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-475_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-500_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-525_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-550_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-575_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-600_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-625_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tHq_HToTT_0J_mH-650_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-350_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-375_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-425_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-450_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-475_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-500_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-525_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-550_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-575_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-625_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "ttH_HToTT_1J_mH-650_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1"
                                    },
                                    {   "VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1",
                                        "tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-madgraph-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1"
                                    },
                                };
    string sample_directory = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v1/2018/"
    for(int ch = 0; ch < backgrounds.size(); ch++){
        for(int samp = 0; samp < backgrounds[ch].size(); samp++){
            string sample_name = sample_directory+samples[ch][samp]+"output_*.root"
            backgrounds[ch].Add(sample_name);
        }
    }*/

    //Load samples
    TChain chain("Events");
    chain.Add("/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v1/2018/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21_ext1-v1_NANOAODSIM_fcnc_v1/output_*.root");
    chain.Add("/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v1/2018/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1/output_*.root");
    chain.Add("/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v1/2018/DYJetsToLL_M-50_Zpt-150toInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1_NANOAODSIM_fcnc_v1/output_*.root");

    cout << "Loaded Samples!" << endl;

    int nEvents = chain.GetEntries();
    cout << "found " << nEvents << " events" << endl;

    //event variables
    uint nMuon = 0;
    uint nElectron = 0;
    uint nJet = 0;
    //vector<float> mu_pt;
    //vector<float> *mu_eta = 0;
    //vector<float> *mu_iso = 0;
    //vector<bool> *mu_tightId = 0;

    chain.SetBranchAddress("nMuon", &nMuon);
    chain.SetBranchAddress("nElectron", &nElectron);
    chain.SetBranchAddress("nJet", &nJet);
    //chain.SetBranchAddress("Muon_pt", &mu_pt);
    /*chain.SetBranchAddress("Muon_eta", &mu_eta);
    chain.SetBranchAddress("Muon_miniPFRelIso_all", &mu_iso);
    chain.SetBranchAddress("Muon_tightId",&mu_tightId);
    */

    //Define histograms
    TH1F h_nJet_trilep("h_nJet_trilep",   "nJets", 7, -0.5, 6.5);
    TH1F h_nJet_SSdilep("h_nJet_SSdilep",  "nJets", 7, -0.5, 6.5);
    TH1F h_nJet_OSdilep("h_nJet_OSdilep",  "nJets", 7, -0.5, 6.5);
    TH1F h_nJet_onelepFO("h_nJet_onelepFO", "nJets", 7, -0.5, 6.5);
    TH1F h_nJet_dilepFO("h_nJet_dilepFO",  "nJets", 7, -0.5, 6.5);

    TH1F h_nBJet_trilep("h_nBJet_trilep",   "nb-tagged Jets", 4, -0.5, 3.5);
    TH1F h_nBJet_SSdilep("h_nBJet_SSdilep",  "nb-tagged Jets", 4, -0.5, 3.5);
    TH1F h_nBJet_OSdilep("h_nBJet_OSdilep",  "nb-tagged Jets", 4, -0.5, 3.5);
    TH1F h_nBJet_onelepFO("h_nBJet_onelepFO", "nb-tagged Jets", 4, -0.5, 3.5);
    TH1F h_nBJet_dilepFO("h_nBJet_dilepFO",  "nb-tagged Jets", 4, -0.5, 3.5);

    cout << "defined histograms!" << endl;

    auto start = high_resolution_clock::now();

    int nTriLep   = 0;
    int nSSDiLep  = 0;
    int nOSDiLep  = 0;
    int nOneLepFO = 0;
    int nFODiLep  = 0;

    //Main for loop
    for ( int counter = 0; counter < nEvents; counter++ ){
    //for ( int counter = 0; counter < 100; counter++ ){
        //cout << "counter " << counter << endl;
        if ( counter%100000==0 ){
            cout << "event " << counter << endl;
        }

        Long64_t event = chain.GetEntry(counter);
        int nGoodLep = 0;
        int nFakeableLep = 0;
        int nJets = 0;
        int nBjets = 0;

        vector<int> muCharge_tight;
        vector<int> elCharge_tight;
        vector<int> muCharge_loose;
        vector<int> elCharge_loose;

        //cout << "nMuon: " << nMuon << endl;
        //cout << "nElectron: " << nElectron << endl;

        //loop to count good jets and b-tagged jets
        for ( uint jet = 0; jet < nJet; jet++ ){
            float jet_pt = chain.GetLeaf("Jet_pt")->GetValue(jet);
            float jet_eta = chain.GetLeaf("Jet_eta")->GetValue(jet);
            float jet_phi = chain.GetLeaf("Jet_phi")->GetValue(jet);
            float btag_score = chain.GetLeaf("Jet_btagDeepFlavB")->GetValue(jet);

            if ( isGoodJet(jet_pt, jet_eta) ){
                //next two for loops to clean jets
                bool isGood = 1;
                for (uint mu = 0; mu < nMuon; mu++ ){
                    float mu_pt = chain.GetLeaf("Muon_pt")->GetValue(mu);
                    float mu_eta = chain.GetLeaf("Muon_eta")->GetValue(mu);
                    float mu_phi = chain.GetLeaf("Muon_phi")->GetValue(mu);
                    float mu_charge = chain.GetLeaf("Muon_charge")->GetValue(mu);
                    float mu_iso = chain.GetLeaf("Muon_miniPFRelIso_all")->GetValue(mu);
                    float mu_tightId = chain.GetLeaf("Muon_tightId")->GetValue(mu);
                    float mu_looseId = chain.GetLeaf("Muon_looseId")->GetValue(mu);

                    if ( isTightLepton( 13, mu_pt, mu_eta, mu_iso, mu_tightId ) || isLooseLepton( 13, mu_pt, mu_eta, mu_iso, mu_looseId ) ){
                        if ( deltaR( jet_eta, jet_phi, mu_eta, mu_phi ) < 0.4 ){
                            isGood = 0;
                        }else continue;
                    }else continue;
                }
                for (uint el = 0; el < nElectron; el++ ){
                    float el_pt = chain.GetLeaf("Electron_pt")->GetValue(el);
                    float el_eta = chain.GetLeaf("Electron_eta")->GetValue(el);
                    float el_phi = chain.GetLeaf("Electron_phi")->GetValue(el);
                    float el_charge = chain.GetLeaf("Electron_charge")->GetValue(el);
                    float el_iso = chain.GetLeaf("Electron_miniPFRelIso_all")->GetValue(el);

                    if ( isTightLepton( 11, el_pt, el_eta, el_iso, 0 ) || isLooseLepton( 11, el_pt, el_eta, el_iso, 0 ) ){
                        if ( deltaR( jet_eta, jet_phi, el_eta, el_phi ) < 0.4 ){
                            isGood = 0;
                        }else continue;
                    }else continue;
                }

                if ( isGood == 1 ){
                    nJets += 1;
                    if ( btag_score > 0.2770 ){
                        nBjets += 1;
                    }else continue;
                }else continue;
            }else continue;
        }


        if(nJets>1 && nBjets>=0){
            //loop to count tight/loose muons
            for( uint mu = 0; mu < nMuon; mu++ ){
                //cout << (*mu_pt)[mu] << endl;
                float mu_pt = chain.GetLeaf("Muon_pt")->GetValue(mu);
                float mu_eta = chain.GetLeaf("Muon_eta")->GetValue(mu);
                float mu_charge = chain.GetLeaf("Muon_charge")->GetValue(mu);
                float mu_iso = chain.GetLeaf("Muon_miniPFRelIso_all")->GetValue(mu);
                float mu_tightId = chain.GetLeaf("Muon_tightId")->GetValue(mu);
                float mu_looseId = chain.GetLeaf("Muon_looseId")->GetValue(mu);

                if ( isTightLepton( 13, mu_pt, mu_eta, mu_iso, mu_tightId ) ){
                    nGoodLep += 1;
                    muCharge_tight.push_back(mu_charge);
                }else if ( isLooseLepton( 13, mu_pt, mu_eta, mu_iso, mu_looseId ) ){
                    nFakeableLep += 1;
                    muCharge_loose.push_back(mu_charge);
                }else continue;
            }
            //loop to count tight/loose electrons
            for( uint el = 0; el < nElectron; el++ ){
                //cout << (*el_pt)[el] << endl;
                float el_pt = chain.GetLeaf("Electron_pt")->GetValue(el);
                float el_eta = chain.GetLeaf("Electron_eta")->GetValue(el);
                float el_charge = chain.GetLeaf("Electron_charge")->GetValue(el);
                float el_iso = chain.GetLeaf("Electron_miniPFRelIso_all")->GetValue(el);
                //float el_tightId = chain.GetLeaf("Electron_tightId")->GetValue(el);
                //float el_looseId = chain.GetLeaf("Electron_looseId")->GetValue(el);

                if ( isTightLepton( 13, el_pt, el_eta, el_iso, 0 ) ){
                    nGoodLep += 1;
                    elCharge_tight.push_back(el_charge);
                }else if ( isLooseLepton( 13, el_pt, el_eta, el_iso, 0 ) ){
                    nFakeableLep += 1;
                    elCharge_loose.push_back(el_charge);
                }else continue;
            }
        }
    
        //organize into signature types
        if ( nGoodLep == 3 ){
            nTriLep += 1;
            h_nJet_trilep.Fill(nJets);
            h_nBJet_trilep.Fill(nBjets);
        }
        if ( nGoodLep == 2 ){
            if (muCharge_tight.size() == 2){
                if (muCharge_tight[0]*muCharge_tight[1]>0){
                    nSSDiLep += 1;
                    h_nJet_SSdilep.Fill(nJets);
                    h_nBJet_SSdilep.Fill(nBjets);
                }else{ 
                    nOSDiLep += 1;
                    h_nJet_OSdilep.Fill(nJets);
                    h_nBJet_OSdilep.Fill(nBjets);
                }
            }else if (elCharge_tight.size() == 2) {
                if (elCharge_tight[0]*elCharge_tight[1]>0){
                    nSSDiLep += 1;
                    h_nJet_SSdilep.Fill(nJets);
                    h_nBJet_SSdilep.Fill(nBjets);
                }else{
                    nOSDiLep += 1;
                    h_nJet_OSdilep.Fill(nJets);
                    h_nBJet_OSdilep.Fill(nBjets);
                }
            }else if (muCharge_tight.size() == 1) {
                if (muCharge_tight[0]*elCharge_tight[0]>0){
                    nSSDiLep += 1;
                    h_nJet_SSdilep.Fill(nJets);
                    h_nBJet_SSdilep.Fill(nBjets);
                }else{
                    nOSDiLep += 1;
                    h_nJet_OSdilep.Fill(nJets);
                    h_nBJet_OSdilep.Fill(nBjets);
                }
            }
        }//if nGoodLep == 2
        if (nGoodLep == 1 and nFakeableLep == 1){
            nOneLepFO += 1;
            h_nJet_onelepFO.Fill(nJets);
            h_nBJet_onelepFO.Fill(nBjets);
        }
        if (nFakeableLep == 2){
            nFODiLep += 1;
            h_nJet_dilepFO.Fill(nJets);
            h_nBJet_dilepFO.Fill(nBjets);
        }

    }//event loop

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(stop - start);

    cout << "TriLep: " << nTriLep << endl;
    cout << "SS DiLep: " << nSSDiLep << endl;
    cout << "OS DiLep: " << nOSDiLep << endl;
    cout << "One Lep with FO: " << nOneLepFO << endl;
    cout << "FO DiLep: " << nFODiLep << endl;
    cout << "total filtered: " << (nTriLep+nSSDiLep+nOSDiLep) << endl;

    cout << "processed " << nEvents << " events in " << duration.count() << " minutes!!" << endl;

    //write histograms
    string outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots/";
    //outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/plots/"

    /*saveFig(h_nJet_trilep, "h_nJet_trilep", outdir);
    saveFig(h_nJet_SSdilep, "h_nJet_SSdilep", outdir);
    saveFig(h_nJet_OSdilep, "h_nJet_OSdilep", outdir);
    saveFig(h_nJet_onelepFO, "h_nJet_onelepFO", outdir);
    saveFig(h_nJet_dilepFO, "h_nJet_dilepFO", outdir);

    saveFig(h_nBJet_trilep, "h_nBJet_trilep", outdir);
    saveFig(h_nBJet_SSdilep, "h_nBJet_SSdilep", outdir);
    saveFig(h_nBJet_OSdilep, "h_nBJet_OSdilep", outdir);
    saveFig(h_nBJet_onelepFO, "h_nBJet_onelepFO", outdir);
    saveFig(h_nBJet_dilepFO, "h_nBJet_dilepFO", outdir);
*/
    cout << "saved histograms!" << endl;

}
