//Basic looper to categorize FCNC events
//Compile and run with root -l event_looper.C+
//March 2021
//Kaitlin Salyer

#include <iostream>
//#include <cmath>
#include <cstdlib>
#include <chrono>
#include <TChain.h>
#include <TChainElement.h>
#include <TLeaf.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>
#include <THStack.h>
#include <TLegend.h>
#include <TFile.h>
//#include <sampleClasses.h>
#include "./helpers/fcnc_functions.h"
#include "./helpers/sampleLoader.h"
#include "./helpers/objectClasses.h"
#include "./helpers/weights.h"


using namespace std;
using namespace std::chrono;

void event_looper(){
    //global variables
    int year = 2018;
    double lumi = 137;
    string babyVersion = "fcnc_v2/";
    string inputDir = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/"+babyVersion;
    vector< string > sample_names = {   "fakes",
                                        "flips",
                                        "other",
                                        "signal_hut",
                                        "signal_hct"
                                    };
    /*vector< string > sample_names = {   "ttjets",
                                        "multiboson",
                                        "wjets",
                                        "ttX",
                                        "DY",
                                        "rareSM",
                                        "signal_hut",
                                        "signal_hct"
                                    };*/

    auto outFile = new TFile("plots/outputHistos.root", "recreate");

    //Load samples
    for(uint btype = 0; btype < sample_names.size(); btype++){
    //for(uint btype = 0; btype < 2; btype++){ //for testing only!!!
        TChain* chain = new TChain("Events");
        vector<string> samples = loadSamples ( year, sample_names[btype] );
        for ( uint s = 0; s < samples.size(); s++ ){
            string name = inputDir+samples[s]+"/output_*.root";
            chain->Add(name.c_str());
        }
        cout << "Loaded Samples!" << endl;

        int nEvents = chain->GetEntries();
        cout << "found " << nEvents << " " << sample_names[btype] << " events" << endl;

        //event variables
        uint nMuon = 0;
        uint nElectron = 0;
        uint nJet = 0;
        float MET = 0;
        float MET_phi = 0;
        float genWeight = 0;

        chain->SetBranchAddress("nMuon", &nMuon);
        chain->SetBranchAddress("nElectron", &nElectron);
        chain->SetBranchAddress("nJet", &nJet);
        chain->SetBranchAddress("MET_pt", &MET);
        chain->SetBranchAddress("MET_phi", &MET_phi);
        chain->SetBranchAddress("Generator_weight", &genWeight);

        //vectors to loop through
        vector<string> variables = {"nJet",
                                    "nBJet",
                                    "MET",
                                    "minMT"};

        vector<string> numLepSel = {"trilep",
                                    "SSdilep",
                                    "OSdilep",
                                    "onelepFO",
                                    "dilepFO"};
                                    
        vector<string> numJetSel = {"2j",
                                    "3j",
                                    "ge4j"};
                                    
        vector<string> numBSel   = {"0b",
                                    "1b",
                                    "ge2b"};
        
        //vectors to hold variable info
        
        /*//Define histograms
        //2 jets, 0 b
        auto h_nJet_trilep_2j_0b = new TH1F(("h_nJet_trilep_2j_0b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_2j_0b = new TH1F(("h_nJet_SSdilep_2j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_2j_0b = new TH1F(("h_nJet_OSdilep_2j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_2j_0b = new TH1F(("h_nJet_onelepFO_2j_0b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_2j_0b = new TH1F(("h_nJet_dilepFO_2j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_2j_0b = new TH1F(("h_nBJet_trilep_2j_0b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_2j_0b = new TH1F(("h_nBJet_SSdilep_2j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_2j_0b = new TH1F(("h_nBJet_OSdilep_2j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_2j_0b = new TH1F(("h_nBJet_onelepFO_2j_0b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_2j_0b = new TH1F(("h_nBJet_dilepFO_2j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_2j_0b = new TH1F(("h_MET_trilep_2j_0b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_2j_0b = new TH1F(("h_MET_SSdilep_2j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_2j_0b = new TH1F(("h_MET_OSdilep_2j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_2j_0b = new TH1F(("h_MET_onelepFO_2j_0b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_2j_0b = new TH1F(("h_MET_dilepFO_2j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_2j_0b = new TH1F(("h_minMT_trilep_2j_0b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_2j_0b = new TH1F(("h_minMT_SSdilep_2j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_2j_0b = new TH1F(("h_minMT_OSdilep_2j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_2j_0b = new TH1F(("h_minMT_onelepFO_2j_0b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_2j_0b = new TH1F(("h_minMT_dilepFO_2j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //2 jets, 1 b
        auto h_nJet_trilep_2j_1b = new TH1F(("h_nJet_trilep_2j_1b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_2j_1b = new TH1F(("h_nJet_SSdilep_2j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_2j_1b = new TH1F(("h_nJet_OSdilep_2j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_2j_1b = new TH1F(("h_nJet_onelepFO_2j_1b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_2j_1b = new TH1F(("h_nJet_dilepFO_2j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_2j_1b = new TH1F(("h_nBJet_trilep_2j_1b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_2j_1b = new TH1F(("h_nBJet_SSdilep_2j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_2j_1b = new TH1F(("h_nBJet_OSdilep_2j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_2j_1b = new TH1F(("h_nBJet_onelepFO_2j_1b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_2j_1b = new TH1F(("h_nBJet_dilepFO_2j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_2j_1b = new TH1F(("h_MET_trilep_2j_1b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_2j_1b = new TH1F(("h_MET_SSdilep_2j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_2j_1b = new TH1F(("h_MET_OSdilep_2j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_2j_1b = new TH1F(("h_MET_onelepFO_2j_1b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_2j_1b = new TH1F(("h_MET_dilepFO_2j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_2j_1b = new TH1F(("h_minMT_trilep_2j_1b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_2j_1b = new TH1F(("h_minMT_SSdilep_2j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_2j_1b = new TH1F(("h_minMT_OSdilep_2j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_2j_1b = new TH1F(("h_minMT_onelepFO_2j_1b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_2j_1b = new TH1F(("h_minMT_dilepFO_2j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //2 jets, 2+ b
        auto h_nJet_trilep_2j_ge2b = new TH1F(("h_nJet_trilep_2j_ge2b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_2j_ge2b = new TH1F(("h_nJet_SSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_2j_ge2b = new TH1F(("h_nJet_OSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_2j_ge2b = new TH1F(("h_nJet_onelepFO_2j_ge2b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_2j_ge2b = new TH1F(("h_nJet_dilepFO_2j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_2j_ge2b = new TH1F(("h_nBJet_trilep_2j_ge2b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_2j_ge2b = new TH1F(("h_nBJet_SSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_2j_ge2b = new TH1F(("h_nBJet_OSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_2j_ge2b = new TH1F(("h_nBJet_onelepFO_2j_ge2b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_2j_ge2b = new TH1F(("h_nBJet_dilepFO_2j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_2j_ge2b = new TH1F(("h_MET_trilep_2j_ge2b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_2j_ge2b = new TH1F(("h_MET_SSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_2j_ge2b = new TH1F(("h_MET_OSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_2j_ge2b = new TH1F(("h_MET_onelepFO_2j_ge2b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_2j_ge2b = new TH1F(("h_MET_dilepFO_2j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_2j_ge2b = new TH1F(("h_minMT_trilep_2j_ge2b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_2j_ge2b = new TH1F(("h_minMT_SSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_2j_ge2b = new TH1F(("h_minMT_OSdilep_2j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_2j_ge2b = new TH1F(("h_minMT_onelepFO_2j_ge2b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_2j_ge2b = new TH1F(("h_minMT_dilepFO_2j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //3 jets, 0b
        auto h_nJet_trilep_3j_0b = new TH1F(("h_nJet_trilep_3j_0b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_3j_0b = new TH1F(("h_nJet_SSdilep_3j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_3j_0b = new TH1F(("h_nJet_OSdilep_3j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_3j_0b = new TH1F(("h_nJet_onelepFO_3j_0b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_3j_0b = new TH1F(("h_nJet_dilepFO_3j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_3j_0b = new TH1F(("h_nBJet_trilep_3j_0b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_3j_0b = new TH1F(("h_nBJet_SSdilep_3j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_3j_0b = new TH1F(("h_nBJet_OSdilep_3j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_3j_0b = new TH1F(("h_nBJet_onelepFO_3j_0b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_3j_0b = new TH1F(("h_nBJet_dilepFO_3j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_3j_0b = new TH1F(("h_MET_trilep_3j_0b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_3j_0b = new TH1F(("h_MET_SSdilep_3j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_3j_0b = new TH1F(("h_MET_OSdilep_3j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_3j_0b = new TH1F(("h_MET_onelepFO_3j_0b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_3j_0b = new TH1F(("h_MET_dilepFO_3j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_3j_0b = new TH1F(("h_minMT_trilep_3j_0b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_3j_0b = new TH1F(("h_minMT_SSdilep_3j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_3j_0b = new TH1F(("h_minMT_OSdilep_3j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_3j_0b = new TH1F(("h_minMT_onelepFO_3j_0b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_3j_0b = new TH1F(("h_minMT_dilepFO_3j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //3 jets, 1b
        auto h_nJet_trilep_3j_1b = new TH1F(("h_nJet_trilep_3j_1b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_3j_1b = new TH1F(("h_nJet_SSdilep_3j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_3j_1b = new TH1F(("h_nJet_OSdilep_3j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_3j_1b = new TH1F(("h_nJet_onelepFO_3j_1b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_3j_1b = new TH1F(("h_nJet_dilepFO_3j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_3j_1b = new TH1F(("h_nBJet_trilep_3j_1b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_3j_1b = new TH1F(("h_nBJet_SSdilep_3j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_3j_1b = new TH1F(("h_nBJet_OSdilep_3j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_3j_1b = new TH1F(("h_nBJet_onelepFO_3j_1b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_3j_1b = new TH1F(("h_nBJet_dilepFO_3j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_3j_1b = new TH1F(("h_MET_trilep_3j_1b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_3j_1b = new TH1F(("h_MET_SSdilep_3j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_3j_1b = new TH1F(("h_MET_OSdilep_3j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_3j_1b = new TH1F(("h_MET_onelepFO_3j_1b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_3j_1b = new TH1F(("h_MET_dilepFO_3j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_3j_1b = new TH1F(("h_minMT_trilep_3j_1b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_3j_1b = new TH1F(("h_minMT_SSdilep_3j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_3j_1b = new TH1F(("h_minMT_OSdilep_3j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_3j_1b = new TH1F(("h_minMT_onelepFO_3j_1b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_3j_1b = new TH1F(("h_minMT_dilepFO_3j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //3 jets, 2+ b
        auto h_nJet_trilep_3j_ge2b = new TH1F(("h_nJet_trilep_3j_ge2b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_3j_ge2b = new TH1F(("h_nJet_SSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_3j_ge2b = new TH1F(("h_nJet_OSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_3j_ge2b = new TH1F(("h_nJet_onelepFO_3j_ge2b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_3j_ge2b = new TH1F(("h_nJet_dilepFO_3j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_3j_ge2b = new TH1F(("h_nBJet_trilep_3j_ge2b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_3j_ge2b = new TH1F(("h_nBJet_SSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_3j_ge2b = new TH1F(("h_nBJet_OSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_3j_ge2b = new TH1F(("h_nBJet_onelepFO_3j_ge2b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_3j_ge2b = new TH1F(("h_nBJet_dilepFO_3j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_3j_ge2b = new TH1F(("h_MET_trilep_3j_ge2b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_3j_ge2b = new TH1F(("h_MET_SSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_3j_ge2b = new TH1F(("h_MET_OSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_3j_ge2b = new TH1F(("h_MET_onelepFO_3j_ge2b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_3j_ge2b = new TH1F(("h_MET_dilepFO_3j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_3j_ge2b = new TH1F(("h_minMT_trilep_3j_ge2b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_3j_ge2b = new TH1F(("h_minMT_SSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_3j_ge2b = new TH1F(("h_minMT_OSdilep_3j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_3j_ge2b = new TH1F(("h_minMT_onelepFO_3j_ge2b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_3j_ge2b = new TH1F(("h_minMT_dilepFO_3j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //4+ jets, 0b
        auto h_nJet_trilep_ge4j_0b = new TH1F(("h_nJet_trilep_ge4j_0b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_ge4j_0b = new TH1F(("h_nJet_SSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_ge4j_0b = new TH1F(("h_nJet_OSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_ge4j_0b = new TH1F(("h_nJet_onelepFO_ge4j_0b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_ge4j_0b = new TH1F(("h_nJet_dilepFO_ge4j_0b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_ge4j_0b = new TH1F(("h_nBJet_trilep_ge4j_0b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_ge4j_0b = new TH1F(("h_nBJet_SSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_ge4j_0b = new TH1F(("h_nBJet_OSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_ge4j_0b = new TH1F(("h_nBJet_onelepFO_ge4j_0b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_ge4j_0b = new TH1F(("h_nBJet_dilepFO_ge4j_0b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_ge4j_0b = new TH1F(("h_MET_trilep_ge4j_0b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_ge4j_0b = new TH1F(("h_MET_SSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_ge4j_0b = new TH1F(("h_MET_OSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_ge4j_0b = new TH1F(("h_MET_onelepFO_ge4j_0b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_ge4j_0b = new TH1F(("h_MET_dilepFO_ge4j_0b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_ge4j_0b = new TH1F(("h_minMT_trilep_ge4j_0b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_ge4j_0b = new TH1F(("h_minMT_SSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_ge4j_0b = new TH1F(("h_minMT_OSdilep_ge4j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_ge4j_0b = new TH1F(("h_minMT_onelepFO_ge4j_0b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_ge4j_0b = new TH1F(("h_minMT_dilepFO_ge4j_0b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //4+ jets, 1b
        auto h_nJet_trilep_ge4j_1b = new TH1F(("h_nJet_trilep_ge4j_1b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_ge4j_1b = new TH1F(("h_nJet_SSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_ge4j_1b = new TH1F(("h_nJet_OSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_ge4j_1b = new TH1F(("h_nJet_onelepFO_ge4j_1b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_ge4j_1b = new TH1F(("h_nJet_dilepFO_ge4j_1b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_ge4j_1b = new TH1F(("h_nBJet_trilep_ge4j_1b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_ge4j_1b = new TH1F(("h_nBJet_SSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_ge4j_1b = new TH1F(("h_nBJet_OSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_ge4j_1b = new TH1F(("h_nBJet_onelepFO_ge4j_1b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_ge4j_1b = new TH1F(("h_nBJet_dilepFO_ge4j_1b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_ge4j_1b = new TH1F(("h_MET_trilep_ge4j_1b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_ge4j_1b = new TH1F(("h_MET_SSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_ge4j_1b = new TH1F(("h_MET_OSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_ge4j_1b = new TH1F(("h_MET_onelepFO_ge4j_1b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_ge4j_1b = new TH1F(("h_MET_dilepFO_ge4j_1b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_ge4j_1b = new TH1F(("h_minMT_trilep_ge4j_1b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_ge4j_1b = new TH1F(("h_minMT_SSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_ge4j_1b = new TH1F(("h_minMT_OSdilep_ge4j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_ge4j_1b = new TH1F(("h_minMT_onelepFO_ge4j_1b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_ge4j_1b = new TH1F(("h_minMT_dilepFO_ge4j_1b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        //4+ jets, 2+ b
        auto h_nJet_trilep_ge4j_ge2b = new TH1F(("h_nJet_trilep_ge4j_ge2b_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep_ge4j_ge2b = new TH1F(("h_nJet_SSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep_ge4j_ge2b = new TH1F(("h_nJet_OSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO_ge4j_ge2b = new TH1F(("h_nJet_onelepFO_ge4j_ge2b_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO_ge4j_ge2b = new TH1F(("h_nJet_dilepFO_ge4j_ge2b_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep_ge4j_ge2b = new TH1F(("h_nBJet_trilep_ge4j_ge2b_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep_ge4j_ge2b = new TH1F(("h_nBJet_SSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep_ge4j_ge2b = new TH1F(("h_nBJet_OSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO_ge4j_ge2b = new TH1F(("h_nBJet_onelepFO_ge4j_ge2b_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO_ge4j_ge2b = new TH1F(("h_nBJet_dilepFO_ge4j_ge2b_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep_ge4j_ge2b = new TH1F(("h_MET_trilep_ge4j_ge2b_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep_ge4j_ge2b = new TH1F(("h_MET_SSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep_ge4j_ge2b = new TH1F(("h_MET_OSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO_ge4j_ge2b = new TH1F(("h_MET_onelepFO_ge4j_ge2b_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO_ge4j_ge2b = new TH1F(("h_MET_dilepFO_ge4j_ge2b_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep_ge4j_ge2b = new TH1F(("h_minMT_trilep_ge4j_ge2b_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep_ge4j_ge2b = new TH1F(("h_minMT_SSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep_ge4j_ge2b = new TH1F(("h_minMT_OSdilep_ge4j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO_ge4j_ge2b = new TH1F(("h_minMT_onelepFO_ge4j_ge2b_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO_ge4j_ge2b = new TH1F(("h_minMT_dilepFO_ge4j_ge2b_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        cout << "defined histograms!" << endl;
*/
        auto start = high_resolution_clock::now();

        int nTriLep   = 0;
        int nSSDiLep  = 0;
        int nOSDiLep  = 0;
        int nOneLepFO = 0;
        int nFODiLep  = 0;

        //Main for loop
        //for ( int counter = 0; counter < nEvents; counter++ ){
        //for ( int counter = 0; counter < 10000; counter++ ){ //for testing only!!
        //for ( int counter = 0; counter < 100; counter++ ){ //for testing only!!
        for ( int counter = 0; counter < 10; counter++ ){ //for testing only!!
            //cout << "counter " << counter << endl;
            if ( counter%100000==0 ){
                cout << "event " << counter << endl;
            }

            //variables to hold information
            int nGoodLep = 0;
            int nFakeableLep = 0;
            int nJets = 0;
            int nBjets = 0;
            float minMT_tight = 10000;
            float minMT_loose = 10000;

            vector<int> muCharge_tight;
            vector<int> elCharge_tight;
            vector<int> muCharge_loose;
            vector<int> elCharge_loose;
            
            //Get individual event
            Long64_t event = chain->GetEntry(counter);

            //Find the exact sample name
            TFile* sFile(chain->GetFile());
            string sName = sFile->GetName();
            /*if ( counter%1000==0 ){
                cout << sName << endl;
            }*/
            //get event weight based on sample!
            double weight = getEventWeight( sName, inputDir, babyVersion );
            /*cout << weight << endl;
            cout << genWeight << endl;
            cout << lumi << endl;*/
            weight = (weight*genWeight*lumi)/(abs(genWeight));
            /*cout << weight << endl;
            cout << "***************" << endl;*/

            //Define physics objects
            Muon mu(chain, nMuon, year);
            Electron el(chain, nElectron, year);
            Jet jet(chain, nJet, year);

            //loop to count tight/loose muons
            for( uint iMu = 0; iMu < nMuon; iMu++ ){

                //check if meets basic object requirements
                bool mu_isGood = isGoodMuon( mu.dxy[iMu], mu.dz[iMu], mu.sip3d[iMu], mu.tightCharge[iMu], mu.mediumId[iMu], mu.chargeQuality[iMu] );
                int mu_isoType = isoType( year, mu.pdgid[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );

                //check for tight or loose
                if ( isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
                    nGoodLep += 1;
                    muCharge_tight.push_back(mu.charge[iMu]);
                    if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_tight ){
                        minMT_tight = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
                    }
                }else if ( isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
                    nFakeableLep += 1;
                    muCharge_loose.push_back(mu.charge[iMu]);
                    if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
                    }
                }else continue;
            }
            //loop to count tight/loose electrons
            for( uint iEl = 0; iEl < nElectron; iEl++ ){

                //check if meets basic object requirements
                bool el_isGood = isGoodElectron( el.dxy[iEl], el.dz[iEl], el.sip3d[iEl], el.tightCharge[iEl], el.lostHits[iEl], el.convVeto[iEl] );
                int el_isoType = isoType( year, el.pdgid[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );

                //check for tight or loose
                if ( isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ){
                    nGoodLep += 1;
                    elCharge_tight.push_back(el.charge[iEl]);
                    if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_tight ){
                        minMT_tight = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
                    }
                }else if ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ){
                    nFakeableLep += 1;
                    elCharge_loose.push_back(el.charge[iEl]);
                    if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
                    }
                }else continue;
            }

            if ( !((nFakeableLep==0 && nGoodLep>1) || (nFakeableLep>0 && nGoodLep<2)) ){
                continue;
            }else{
                //loop to count good jets and b-tagged jets
                for ( uint iJet = 0; iJet < nJet; iJet++ ){
                    if ( isGoodJet(jet.pt[iJet], jet.eta[iJet]) ){
                        //next two for loops to clean jets
                        bool isGood = 1;
                        for (uint iMu = 0; iMu < nMuon; iMu++ ){
                            bool mu_isGood = isGoodMuon( mu.dxy[iMu], mu.dz[iMu], mu.sip3d[iMu], mu.tightCharge[iMu], mu.mediumId[iMu], mu.chargeQuality[iMu] );
                            int mu_isoType = isoType( year, mu.pdgid[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
                            if ( isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) || isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
                                if ( deltaR( jet.eta[iJet], jet.phi[iJet], mu.eta[iMu], mu.phi[iMu] ) < 0.4 ){
                                    isGood = 0;
                                }else continue;
                            }else continue;
                        }
                        for (uint iEl = 0; iEl < nElectron; iEl++ ){
                            bool el_isGood = isGoodElectron( el.dxy[iEl], el.dz[iEl], el.sip3d[iEl], el.tightCharge[iEl], el.lostHits[iEl], el.convVeto[iEl] );
                            int el_isoType = isoType( year, el.pdgid[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
                            if ( ( isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ) || ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ) ){
                                if ( deltaR( jet.eta[iJet], jet.phi[iJet], el.eta[iEl], el.phi[iEl] ) < 0.4 ){
                                    isGood = 0;
                                }else continue;
                            }else continue;
                        }

                        if ( isGood == 1 ){
                            nJets += 1;
                            if ( jet.btag_score[iJet] > 0.2770 ){
                                nBjets += 1;
                            }else continue;
                        }else continue;
                    }else continue;
                }

            }

            //organize into signature types
            if( nJets==2 ){
                if (nBjets == 0){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_2j_0b->Fill(nJets, weight);
                        h_nBJet_trilep_2j_0b->Fill(nBjets, weight);
                        h_MET_trilep_2j_0b->Fill(MET, weight);
                        h_minMT_trilep_2j_0b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_0b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_0b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_0b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_0b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_0b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_0b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_2j_0b->Fill(nJets, weight);
                        h_nBJet_onelepFO_2j_0b->Fill(nBjets, weight);
                        h_MET_onelepFO_2j_0b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_2j_0b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_2j_0b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_2j_0b->Fill(nJets, weight);
                        h_nBJet_dilepFO_2j_0b->Fill(nBjets, weight);
                        h_MET_dilepFO_2j_0b->Fill(MET, weight);
                        h_minMT_dilepFO_2j_0b->Fill(minMT_loose);
                    }//2FO
                }/*0b*/else if(nBjets == 1){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_2j_1b->Fill(nJets, weight);
                        h_nBJet_trilep_2j_1b->Fill(nBjets, weight);
                        h_MET_trilep_2j_1b->Fill(MET, weight);
                        h_minMT_trilep_2j_1b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_1b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_1b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_1b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_1b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_1b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_1b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_2j_1b->Fill(nJets, weight);
                        h_nBJet_onelepFO_2j_1b->Fill(nBjets, weight);
                        h_MET_onelepFO_2j_1b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_2j_1b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_2j_1b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_2j_1b->Fill(nJets, weight);
                        h_nBJet_dilepFO_2j_1b->Fill(nBjets, weight);
                        h_MET_dilepFO_2j_1b->Fill(MET, weight);
                        h_minMT_dilepFO_2j_1b->Fill(minMT_loose);
                    }//2FO
                }/*1b*/else if(nBjets >= 2){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_2j_ge2b->Fill(nJets, weight);
                        h_nBJet_trilep_2j_ge2b->Fill(nBjets, weight);
                        h_MET_trilep_2j_ge2b->Fill(MET, weight);
                        h_minMT_trilep_2j_ge2b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_ge2b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_ge2b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_ge2b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_ge2b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_2j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_2j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_2j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_2j_ge2b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_2j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_2j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_2j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_2j_ge2b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_2j_ge2b->Fill(nJets, weight);
                        h_nBJet_onelepFO_2j_ge2b->Fill(nBjets, weight);
                        h_MET_onelepFO_2j_ge2b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_2j_ge2b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_2j_ge2b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_2j_ge2b->Fill(nJets, weight);
                        h_nBJet_dilepFO_2j_ge2b->Fill(nBjets, weight);
                        h_MET_dilepFO_2j_ge2b->Fill(MET, weight);
                        h_minMT_dilepFO_2j_ge2b->Fill(minMT_loose);
                    }//2FO
                }/*>=2b*/
            }/*2jet*/else if( nJets==3 ){
                if (nBjets == 0){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_3j_0b->Fill(nJets, weight);
                        h_nBJet_trilep_3j_0b->Fill(nBjets, weight);
                        h_MET_trilep_3j_0b->Fill(MET, weight);
                        h_minMT_trilep_3j_0b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_0b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_0b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_0b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_0b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_0b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_0b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_3j_0b->Fill(nJets, weight);
                        h_nBJet_onelepFO_3j_0b->Fill(nBjets, weight);
                        h_MET_onelepFO_3j_0b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_3j_0b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_3j_0b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_3j_0b->Fill(nJets, weight);
                        h_nBJet_dilepFO_3j_0b->Fill(nBjets, weight);
                        h_MET_dilepFO_3j_0b->Fill(MET, weight);
                        h_minMT_dilepFO_3j_0b->Fill(minMT_loose);
                    }//2FO
                }/*0b*/else if(nBjets == 1){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_3j_1b->Fill(nJets, weight);
                        h_nBJet_trilep_3j_1b->Fill(nBjets, weight);
                        h_MET_trilep_3j_1b->Fill(MET, weight);
                        h_minMT_trilep_3j_1b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_1b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_1b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_1b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_1b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_1b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_1b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_3j_1b->Fill(nJets, weight);
                        h_nBJet_onelepFO_3j_1b->Fill(nBjets, weight);
                        h_MET_onelepFO_3j_1b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_3j_1b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_3j_1b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_3j_1b->Fill(nJets, weight);
                        h_nBJet_dilepFO_3j_1b->Fill(nBjets, weight);
                        h_MET_dilepFO_3j_1b->Fill(MET, weight);
                        h_minMT_dilepFO_3j_1b->Fill(minMT_loose);
                    }//2FO
                }/*1b*/else if(nBjets >= 2){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_3j_ge2b->Fill(nJets, weight);
                        h_nBJet_trilep_3j_ge2b->Fill(nBjets, weight);
                        h_MET_trilep_3j_ge2b->Fill(MET, weight);
                        h_minMT_trilep_3j_ge2b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_ge2b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_ge2b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_ge2b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_ge2b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_3j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_3j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_3j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_3j_ge2b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_3j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_3j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_3j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_3j_ge2b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_3j_ge2b->Fill(nJets, weight);
                        h_nBJet_onelepFO_3j_ge2b->Fill(nBjets, weight);
                        h_MET_onelepFO_3j_ge2b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_3j_ge2b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_3j_ge2b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_3j_ge2b->Fill(nJets, weight);
                        h_nBJet_dilepFO_3j_ge2b->Fill(nBjets, weight);
                        h_MET_dilepFO_3j_ge2b->Fill(MET, weight);
                        h_minMT_dilepFO_3j_ge2b->Fill(minMT_loose);
                    }//2FO
                }/*>=2b*/
            }/*3jet*/else if( nJets >= 4 ){
                if (nBjets == 0){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_ge4j_0b->Fill(nJets, weight);
                        h_nBJet_trilep_ge4j_0b->Fill(nBjets, weight);
                        h_MET_trilep_ge4j_0b->Fill(MET, weight);
                        h_minMT_trilep_ge4j_0b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_0b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_0b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_0b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_0b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_0b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_0b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_0b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_0b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_0b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_0b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_0b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_0b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_ge4j_0b->Fill(nJets, weight);
                        h_nBJet_onelepFO_ge4j_0b->Fill(nBjets, weight);
                        h_MET_onelepFO_ge4j_0b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_ge4j_0b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_ge4j_0b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_ge4j_0b->Fill(nJets, weight);
                        h_nBJet_dilepFO_ge4j_0b->Fill(nBjets, weight);
                        h_MET_dilepFO_ge4j_0b->Fill(MET, weight);
                        h_minMT_dilepFO_ge4j_0b->Fill(minMT_loose);
                    }//2FO
                }/*0b*/else if(nBjets == 1){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_ge4j_1b->Fill(nJets, weight);
                        h_nBJet_trilep_ge4j_1b->Fill(nBjets, weight);
                        h_MET_trilep_ge4j_1b->Fill(MET, weight);
                        h_minMT_trilep_ge4j_1b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_1b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_1b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_1b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_1b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_1b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_1b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_1b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_1b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_1b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_1b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_1b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_1b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_ge4j_1b->Fill(nJets, weight);
                        h_nBJet_onelepFO_ge4j_1b->Fill(nBjets, weight);
                        h_MET_onelepFO_ge4j_1b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_ge4j_1b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_ge4j_1b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_ge4j_1b->Fill(nJets, weight);
                        h_nBJet_dilepFO_ge4j_1b->Fill(nBjets, weight);
                        h_MET_dilepFO_ge4j_1b->Fill(MET, weight);
                        h_minMT_dilepFO_ge4j_1b->Fill(minMT_loose);
                    }//2FO
                }/*1b*/else if(nBjets >= 2){
                    if ( nGoodLep >= 3 ){
                        nTriLep += 1;
                        h_nJet_trilep_ge4j_ge2b->Fill(nJets, weight);
                        h_nBJet_trilep_ge4j_ge2b->Fill(nBjets, weight);
                        h_MET_trilep_ge4j_ge2b->Fill(MET, weight);
                        h_minMT_trilep_ge4j_ge2b->Fill(minMT_tight, weight);
                    }//3lep
                    if ( nGoodLep == 2 ){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_ge2b->Fill(minMT_tight, weight);
                            }else{ 
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_ge2b->Fill(minMT_tight, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_ge2b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_ge2b->Fill(minMT_tight, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                nSSDiLep += 1;
                                h_nJet_SSdilep_ge4j_ge2b->Fill(nJets, weight);
                                h_nBJet_SSdilep_ge4j_ge2b->Fill(nBjets, weight);
                                h_MET_SSdilep_ge4j_ge2b->Fill(MET, weight);
                                h_minMT_SSdilep_ge4j_ge2b->Fill(minMT_tight, weight);
                            }else{
                                nOSDiLep += 1;
                                h_nJet_OSdilep_ge4j_ge2b->Fill(nJets, weight);
                                h_nBJet_OSdilep_ge4j_ge2b->Fill(nBjets, weight);
                                h_MET_OSdilep_ge4j_ge2b->Fill(MET, weight);
                                h_minMT_OSdilep_ge4j_ge2b->Fill(minMT_tight, weight);
                            }
                        }
                    }//if nGoodLep == 2
                    if (nGoodLep == 1 and nFakeableLep == 1){
                        nOneLepFO += 1;
                        h_nJet_onelepFO_ge4j_ge2b->Fill(nJets, weight);
                        h_nBJet_onelepFO_ge4j_ge2b->Fill(nBjets, weight);
                        h_MET_onelepFO_ge4j_ge2b->Fill(MET, weight);
                        if (minMT_tight < minMT_loose){
                            h_minMT_onelepFO_ge4j_ge2b->Fill(minMT_tight, weight);
                        } else if (minMT_loose < minMT_tight){
                            h_minMT_onelepFO_ge4j_ge2b->Fill(minMT_loose);
                        }
                    }//1lep+1FO
                    if (nFakeableLep == 2){
                        nFODiLep += 1;
                        h_nJet_dilepFO_ge4j_ge2b->Fill(nJets, weight);
                        h_nBJet_dilepFO_ge4j_ge2b->Fill(nBjets, weight);
                        h_MET_dilepFO_ge4j_ge2b->Fill(MET, weight);
                        h_minMT_dilepFO_ge4j_ge2b->Fill(minMT_loose);
                    }//2FO
                }/*>=2b*/
            }/*>=4jet*/
        }//event loop

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);

        cout << "TriLep: " << nTriLep << endl;
        cout << "SS DiLep: " << nSSDiLep << endl;
        cout << "OS DiLep: " << nOSDiLep << endl;
        cout << "One Lep with FO: " << nOneLepFO << endl;
        cout << "FO DiLep: " << nFODiLep << endl;
        //cout << "total filtered: " << (nTriLep+nSSDiLep+nOSDiLep) << endl;

        cout << "processed " << nEvents << " events in " << duration.count() << " seconds!!" << endl;


        /*h_nJet_trilep_2j_0b->Write();
        h_nJet_SSdilep_2j_0b->Write();
        h_nJet_OSdilep_2j_0b->Write();
        h_nJet_onelepFO_2j_0b->Write();
        h_nJet_dilepFO_2j_0b->Write();

        h_nBJet_trilep_2j_0b->Write();
        h_nBJet_SSdilep_2j_0b->Write();
        h_nBJet_OSdilep_2j_0b->Write();
        h_nBJet_onelepFO_2j_0b->Write();
        h_nBJet_dilepFO_2j_0b->Write();

        h_MET_trilep_2j_0b->Write();
        h_MET_SSdilep_2j_0b->Write();
        h_MET_OSdilep_2j_0b->Write();
        h_MET_onelepFO_2j_0b->Write();
        h_MET_dilepFO_2j_0b->Write();

        h_minMT_trilep_2j_0b->Write();
        h_minMT_SSdilep_2j_0b->Write();
        h_minMT_OSdilep_2j_0b->Write();
        h_minMT_onelepFO_2j_0b->Write();
        h_minMT_dilepFO_2j_0b->Write();
        


        h_nJet_trilep_2j_1b->Write();
        h_nJet_SSdilep_2j_1b->Write();
        h_nJet_OSdilep_2j_1b->Write();
        h_nJet_onelepFO_2j_1b->Write();
        h_nJet_dilepFO_2j_1b->Write();

        h_nBJet_trilep_2j_1b->Write();
        h_nBJet_SSdilep_2j_1b->Write();
        h_nBJet_OSdilep_2j_1b->Write();
        h_nBJet_onelepFO_2j_1b->Write();
        h_nBJet_dilepFO_2j_1b->Write();

        h_MET_trilep_2j_1b->Write();
        h_MET_SSdilep_2j_1b->Write();
        h_MET_OSdilep_2j_1b->Write();
        h_MET_onelepFO_2j_1b->Write();
        h_MET_dilepFO_2j_1b->Write();

        h_minMT_trilep_2j_1b->Write();
        h_minMT_SSdilep_2j_1b->Write();
        h_minMT_OSdilep_2j_1b->Write();
        h_minMT_onelepFO_2j_1b->Write();
        h_minMT_dilepFO_2j_1b->Write();
        


        h_nJet_trilep_2j_ge2b->Write();
        h_nJet_SSdilep_2j_ge2b->Write();
        h_nJet_OSdilep_2j_ge2b->Write();
        h_nJet_onelepFO_2j_ge2b->Write();
        h_nJet_dilepFO_2j_ge2b->Write();

        h_nBJet_trilep_2j_ge2b->Write();
        h_nBJet_SSdilep_2j_ge2b->Write();
        h_nBJet_OSdilep_2j_ge2b->Write();
        h_nBJet_onelepFO_2j_ge2b->Write();
        h_nBJet_dilepFO_2j_ge2b->Write();

        h_MET_trilep_2j_ge2b->Write();
        h_MET_SSdilep_2j_ge2b->Write();
        h_MET_OSdilep_2j_ge2b->Write();
        h_MET_onelepFO_2j_ge2b->Write();
        h_MET_dilepFO_2j_ge2b->Write();

        h_minMT_trilep_2j_ge2b->Write();
        h_minMT_SSdilep_2j_ge2b->Write();
        h_minMT_OSdilep_2j_ge2b->Write();
        h_minMT_onelepFO_2j_ge2b->Write();
        h_minMT_dilepFO_2j_ge2b->Write();
        

        
        h_nJet_trilep_3j_0b->Write();
        h_nJet_SSdilep_3j_0b->Write();
        h_nJet_OSdilep_3j_0b->Write();
        h_nJet_onelepFO_3j_0b->Write();
        h_nJet_dilepFO_3j_0b->Write();

        h_nBJet_trilep_3j_0b->Write();
        h_nBJet_SSdilep_3j_0b->Write();
        h_nBJet_OSdilep_3j_0b->Write();
        h_nBJet_onelepFO_3j_0b->Write();
        h_nBJet_dilepFO_3j_0b->Write();

        h_MET_trilep_3j_0b->Write();
        h_MET_SSdilep_3j_0b->Write();
        h_MET_OSdilep_3j_0b->Write();
        h_MET_onelepFO_3j_0b->Write();
        h_MET_dilepFO_3j_0b->Write();

        h_minMT_trilep_3j_0b->Write();
        h_minMT_SSdilep_3j_0b->Write();
        h_minMT_OSdilep_3j_0b->Write();
        h_minMT_onelepFO_3j_0b->Write();
        h_minMT_dilepFO_3j_0b->Write();
        


        h_nJet_trilep_3j_1b->Write();
        h_nJet_SSdilep_3j_1b->Write();
        h_nJet_OSdilep_3j_1b->Write();
        h_nJet_onelepFO_3j_1b->Write();
        h_nJet_dilepFO_3j_1b->Write();

        h_nBJet_trilep_3j_1b->Write();
        h_nBJet_SSdilep_3j_1b->Write();
        h_nBJet_OSdilep_3j_1b->Write();
        h_nBJet_onelepFO_3j_1b->Write();
        h_nBJet_dilepFO_3j_1b->Write();

        h_MET_trilep_3j_1b->Write();
        h_MET_SSdilep_3j_1b->Write();
        h_MET_OSdilep_3j_1b->Write();
        h_MET_onelepFO_3j_1b->Write();
        h_MET_dilepFO_3j_1b->Write();

        h_minMT_trilep_3j_1b->Write();
        h_minMT_SSdilep_3j_1b->Write();
        h_minMT_OSdilep_3j_1b->Write();
        h_minMT_onelepFO_3j_1b->Write();
        h_minMT_dilepFO_3j_1b->Write();
        


        h_nJet_trilep_3j_ge2b->Write();
        h_nJet_SSdilep_3j_ge2b->Write();
        h_nJet_OSdilep_3j_ge2b->Write();
        h_nJet_onelepFO_3j_ge2b->Write();
        h_nJet_dilepFO_3j_ge2b->Write();

        h_nBJet_trilep_3j_ge2b->Write();
        h_nBJet_SSdilep_3j_ge2b->Write();
        h_nBJet_OSdilep_3j_ge2b->Write();
        h_nBJet_onelepFO_3j_ge2b->Write();
        h_nBJet_dilepFO_3j_ge2b->Write();

        h_MET_trilep_3j_ge2b->Write();
        h_MET_SSdilep_3j_ge2b->Write();
        h_MET_OSdilep_3j_ge2b->Write();
        h_MET_onelepFO_3j_ge2b->Write();
        h_MET_dilepFO_3j_ge2b->Write();

        h_minMT_trilep_3j_ge2b->Write();
        h_minMT_SSdilep_3j_ge2b->Write();
        h_minMT_OSdilep_3j_ge2b->Write();
        h_minMT_onelepFO_3j_ge2b->Write();
        h_minMT_dilepFO_3j_ge2b->Write();
        
        
        
        h_nJet_trilep_ge4j_0b->Write();
        h_nJet_SSdilep_ge4j_0b->Write();
        h_nJet_OSdilep_ge4j_0b->Write();
        h_nJet_onelepFO_ge4j_0b->Write();
        h_nJet_dilepFO_ge4j_0b->Write();

        h_nBJet_trilep_ge4j_0b->Write();
        h_nBJet_SSdilep_ge4j_0b->Write();
        h_nBJet_OSdilep_ge4j_0b->Write();
        h_nBJet_onelepFO_ge4j_0b->Write();
        h_nBJet_dilepFO_ge4j_0b->Write();

        h_MET_trilep_ge4j_0b->Write();
        h_MET_SSdilep_ge4j_0b->Write();
        h_MET_OSdilep_ge4j_0b->Write();
        h_MET_onelepFO_ge4j_0b->Write();
        h_MET_dilepFO_ge4j_0b->Write();

        h_minMT_trilep_ge4j_0b->Write();
        h_minMT_SSdilep_ge4j_0b->Write();
        h_minMT_OSdilep_ge4j_0b->Write();
        h_minMT_onelepFO_ge4j_0b->Write();
        h_minMT_dilepFO_ge4j_0b->Write();
        


        h_nJet_trilep_ge4j_1b->Write();
        h_nJet_SSdilep_ge4j_1b->Write();
        h_nJet_OSdilep_ge4j_1b->Write();
        h_nJet_onelepFO_ge4j_1b->Write();
        h_nJet_dilepFO_ge4j_1b->Write();

        h_nBJet_trilep_ge4j_1b->Write();
        h_nBJet_SSdilep_ge4j_1b->Write();
        h_nBJet_OSdilep_ge4j_1b->Write();
        h_nBJet_onelepFO_ge4j_1b->Write();
        h_nBJet_dilepFO_ge4j_1b->Write();

        h_MET_trilep_ge4j_1b->Write();
        h_MET_SSdilep_ge4j_1b->Write();
        h_MET_OSdilep_ge4j_1b->Write();
        h_MET_onelepFO_ge4j_1b->Write();
        h_MET_dilepFO_ge4j_1b->Write();

        h_minMT_trilep_ge4j_1b->Write();
        h_minMT_SSdilep_ge4j_1b->Write();
        h_minMT_OSdilep_ge4j_1b->Write();
        h_minMT_onelepFO_ge4j_1b->Write();
        h_minMT_dilepFO_ge4j_1b->Write();
        


        h_nJet_trilep_ge4j_ge2b->Write();
        h_nJet_SSdilep_ge4j_ge2b->Write();
        h_nJet_OSdilep_ge4j_ge2b->Write();
        h_nJet_onelepFO_ge4j_ge2b->Write();
        h_nJet_dilepFO_ge4j_ge2b->Write();

        h_nBJet_trilep_ge4j_ge2b->Write();
        h_nBJet_SSdilep_ge4j_ge2b->Write();
        h_nBJet_OSdilep_ge4j_ge2b->Write();
        h_nBJet_onelepFO_ge4j_ge2b->Write();
        h_nBJet_dilepFO_ge4j_ge2b->Write();

        h_MET_trilep_ge4j_ge2b->Write();
        h_MET_SSdilep_ge4j_ge2b->Write();
        h_MET_OSdilep_ge4j_ge2b->Write();
        h_MET_onelepFO_ge4j_ge2b->Write();
        h_MET_dilepFO_ge4j_ge2b->Write();

        h_minMT_trilep_ge4j_ge2b->Write();
        h_minMT_SSdilep_ge4j_ge2b->Write();
        h_minMT_OSdilep_ge4j_ge2b->Write();
        h_minMT_onelepFO_ge4j_ge2b->Write();
        h_minMT_dilepFO_ge4j_ge2b->Write();*/

    }

    //write histograms
    outFile->Close();

}
