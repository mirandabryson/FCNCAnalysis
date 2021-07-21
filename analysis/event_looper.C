//Basic looper to categorize FCNC events
//Compile and run with root -l event_looper.C+
//March 2021
//Kaitlin Salyer

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <dirent.h>
#include <TChain.h>
#include <TChainElement.h>
#include <TLeaf.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TPad.h>
#include <THStack.h>
#include <TLegend.h>
#include <TFile.h>
#include <signal.h>
#include "./helpers/weights.h"
#include "./helpers/histogrammingClass.h"
//#include "./helpers/flip_weights.h"
#include "./helpers/BDT/booster.h"
#include "./helpers/BDT/make_baby.h"
#include "./helpers/tqdm.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"
#include "../../NanoTools/NanoCORE/IsolationTools.h"
#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/Config.h"
#include "../../NanoTools/NanoCORE/Tools/goodrun.h"
#include "../../NanoTools/NanoCORE/Tools/dorky.h"
#include "../../NanoTools/NanoCORE/Tools/btagsf/BTagCalibrationStandalone.h"
#include "../../NanoTools/NanoCORE/Tools/btagsf/BTagCalibrationStandalone.cc"
#include "../misc/common_utils.h"

using namespace std;
using namespace std::chrono;

void print_debug (ofstream& outfile, int hyp_type, Leptons leptons, Jets jets, Jets bjets, int category) {
/*
    outfile << hyp_type << ",";
    for (auto lepton : leptons) {
        outfile << lepton.id() << "," << lepton.pt() << "," << lepton.eta() << "," << lepton.is_loose() << "," << lepton.is_tight() << ",";
    }
    outfile << jets.size() << "," << bjets.size() << ",";
*/
    //int category=3;
    //if (is_fake) category=1;
    //if (is_flip) category=2;
    outfile << category << ","; 

    int nloose = 0;
    int ntight = 0;
    for (auto lepton : leptons) {if (lepton.is_loose()) nloose++; if (lepton.is_tight()) ntight++;}
    outfile << nloose << ","  << ntight << "," << hyp_type << "," << jets.size() << "," << bjets.size() << std::endl;
    //for (auto lepton: leptons) {outfile << "\tL " << lepton.id() << "," << lepton.pt() << ", " << lepton.eta() << "," << lepton.is_loose() << ", " << lepton.is_tight() << ", " << lepton.genPartFlav() << ", " << lepton.isFake() << ", " << lepton.isFlip() << ", " << lepton.mcid() << ", " << lepton.id() << std::endl;}
    for (auto jet : jets) {outfile << "\tJ " << jet.pt() << ", " << jet.eta() << "," << jet.isBtag() << std::endl;}
    for (auto bjet : bjets) {if (bjet.pt()>40.) continue; outfile << "\tJ " << bjet.pt() << ", " << bjet.eta() << "," << bjet.isBtag() << std::endl;}
}

void print_sample_yields (ofstream& outfile, TString sampleName, float nFlip, float nFake, float nRare) {
    outfile << sampleName << " " << nFake << " " << nFlip << " " << nRare << endl;
}

void event_looper(TObjArray* list, TString title, TString options="", int nevts=-1, TString outputdir="outputs/"){
    bool debugPrints = 0;
    //*************************************************************************//
    //*************************** begin set options ***************************//
    bool quiet = options.Contains("quiet");
    bool evaluateBDT = options.Contains("evaluateBDT") && not options.Contains("noBDT");
    bool write_tree = options.Contains("writeTree");
    bool minPtFake18 = options.Contains("minPtFake18");
    bool new2016FRBins = options.Contains("new2016FRBins");
    bool doStitch = options.Contains("doStitch");
    bool doTruthFake = options.Contains("doTruthFake");
    bool doTruthFlip = options.Contains("doTruthFlip");
    bool isData = 0;
    bool doFlips = 0;
    bool doFakes = 0;
    int exclude = 0;
    bool isGamma = 0;
    bool truthfake = 0;
    bool skipmatching = 0;
    bool ignoreFakeFactor = 0;
    float scaleLumi=1.;
    int nbdtbins = 17;
    int nsrdisc = nbdtbins+1; // this is supposed to be 1 more than nbdtbins (we add in CRZ as a "bin")
    bool print_debug_file = options.Contains("printDebugFile");
    bool print_sample_file = options.Contains("printSampleFile");
    ofstream debug_file;
    ofstream sample_file;

/*
    bool STOP_REQUESTED = false;

    signal(SIGINT, [](int){
            cout << "SIGINT Caught, stopping after current event" << endl;
            STOP_REQUESTED=true;
            });
    STOP_REQUESTED=false;
*/

    int year = -1;
    TString extra("");
    if (options.Contains("Data2016")) {
        year = 2016;
        if (options.Contains("94x")) extra = "_94x";
    } else if (options.Contains("Data2017")) {
        year = 2017;
    } else if (options.Contains("Data2018")) {
        year = 2018;
    } else {
        cout << "Need to specify year!\n";
        assert(year > 0);
    }

    int year_for_output = year;
    float lumi = getLumi(year);
    //cout << lumi << endl;

    float min_pt_fake = minPtFake18 ? 18. : -1;

    if (options.Contains("FakeLumi2017")) {
        if (!quiet) std::cout << "Faking 2017 luminosity" << std::endl;
        lumi = getLumi(2017);
    } else if (options.Contains("FakeLumi2018")) {
        if (!quiet) std::cout << "Faking 2018 luminosity" << std::endl;
        lumi = getLumi(2018);
    }

    bool partialUnblind = false;
    /*
    if (options.Contains("partialUnblind")) {
        set_goodrun_file("unblindjson/allsnt.txt");
        if (year == 2017 or options.Contains("FakeLumi2017")) {
            lumi = 10.;
        }
        if (year == 2018 or options.Contains("FakeLumi2018")) {
            lumi = 15.415;
        }
        partialUnblind = true;
    }
    */

    // Note the blocks and else/ifs
    if (options.Contains("doData")) {
        if (!quiet) std::cout << "Doing data" << std::endl;
        isData = 1;
    }

    // --------
    if (options.Contains("doFakesMCUnw")) {
        if (!quiet) std::cout << "Doing fakesMC unweighted" << std::endl;
        doFakes = 1;
        ignoreFakeFactor = 1;
    }
    else if (options.Contains("doFakesUnw")) {
        if (!quiet) std::cout << "Doing fakes unweighted" << std::endl;
        isData = 1;
        doFakes = 1;
        ignoreFakeFactor = 1;
    }
    else if (options.Contains("doFakesMC")) {
        if (!quiet) std::cout << "Doing fakesMC" << std::endl;
        doFakes = 1;
    }
    else if (options.Contains("doFakes")) {
        if (!quiet) std::cout << "Doing fakes" << std::endl;
        isData = 1;
        doFakes = 1;
    }

    // --------
    if (options.Contains("doFlipsMC")) {
        if (!quiet) std::cout << "Doing flipsMC" << std::endl;
        doFlips = 1;
    }

    // --------
    if (options.Contains("doFlips")) {
        if (!quiet) std::cout << "Doing flips" << std::endl;
        isData = 1;
        doFlips = 1;
    }

    // --------
    if (options.Contains("doTruthFake")) {
        if (!quiet) std::cout << "Doing truthfake" << std::endl;
        truthfake = 1;
    }

    // --------
    if (options.Contains("doSkipMatching")) {
        if (!quiet) std::cout << "Skipping gen matching" << std::endl;
        skipmatching = 1;
    }

    // --------
    if (options.Contains("doXgamma")) {
        if (!quiet) std::cout << "Doing x+gamma" << std::endl;
        isGamma = 1;
    }

    if (!quiet) cout << "Running with lumi=" << lumi*scaleLumi << endl;

    TString chainTitle = title;
    const char* chainTitleCh = chainTitle.Data();
    if (print_debug_file) {
        debug_file.open(Form("debug/%s.log",chainTitleCh));
        debug_file << "run,lumi,evt,cat,nloose,ntight,hyp_type,njets,nbjets" << std::endl;
    }
    if (print_sample_file) {
        sample_file.open(Form("sampleYields_%s.txt",chainTitleCh));
        sample_file << "sample,nFakes,nFlips,nRares" << std::endl;
    }
    if (!quiet) std::cout << "Working on " << chainTitle << std::endl;

    bool isFakes = (chainTitle=="fakes") || (chainTitle=="fakes_mc");
    bool isFlips = (chainTitle=="flips") || (chainTitle=="flips_mc");
    bool isRares = (chainTitle=="rares");
    bool isSignal = (chainTitle=="signal_tch") || (chainTitle=="signal_tuh");
    bool istt = (chainTitle=="ttjets") || (chainTitle=="fakes_mc") || (chainTitle=="fakes_mc_unw");
    bool isttH = (chainTitle=="tth");
    bool istttt = (chainTitle=="tttt");
    bool isttVV = (chainTitle=="ttvv");
    bool isttW = (chainTitle=="ttw");
    bool isWW = (chainTitle=="ww");
    bool isttZ = (chainTitle=="ttz_m1-10") || (chainTitle=="ttz_m10");
    bool isWZ = (chainTitle=="wz");
    bool isXgamma = (chainTitle=="xg");

    //**************************** end set options ****************************//
    //*************************************************************************//

    //*************************************************************************//
    //************************** setup good run list **************************//
    std::string goodrun_path = "/home/users/ksalyer/FranksFCNC/ana/samples/goodRunList/";
    std::map<int, std::string> goodrun_file = {
        {2016, "goldenJson_2016rereco_36p46ifb.txt"},
        {2017, "Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1_snt.txt"},
        {2018, "goldenJson_2018_final_59p76ifb_snt.txt"} };
    set_goodrun_file( (goodrun_path+goodrun_file[year]).c_str() );

    //open trig eff SF file here so it's only opened once
    TFile* f_trigEff = new TFile("/home/users/ksalyer/FranksFCNC/ana/misc/year_run2/triggeffcymapsRA5_Run2_ALL.root");


    //open b SF files here so they are opened only once
    auto startBOpening = high_resolution_clock::now();
    //efficiency files
    TFile* f_btag_eff_2016 = new TFile("./outputs/2016_bEff.root");
    TFile* f_btag_eff_2017 = new TFile("./outputs/2017_bEff.root");
    TFile* f_btag_eff_2018 = new TFile("./outputs/2018_bEff.root");

    TH1D* h_btag_eff_b_temp_2016    = (TH1D*) f_btag_eff_2016->Get("h2_BTaggingEff_med_Eff_b");
    TH1D* h_btag_eff_c_temp_2016    = (TH1D*) f_btag_eff_2016->Get("h2_BTaggingEff_med_Eff_c");
    TH1D* h_btag_eff_udsg_temp_2016 = (TH1D*) f_btag_eff_2016->Get("h2_BTaggingEff_med_Eff_udsg");

    TH1D* h_btag_eff_b_temp_2017    = (TH1D*) f_btag_eff_2017->Get("h2_BTaggingEff_med_Eff_b");
    TH1D* h_btag_eff_c_temp_2017    = (TH1D*) f_btag_eff_2017->Get("h2_BTaggingEff_med_Eff_c");
    TH1D* h_btag_eff_udsg_temp_2017 = (TH1D*) f_btag_eff_2017->Get("h2_BTaggingEff_med_Eff_udsg");

    TH1D* h_btag_eff_b_temp_2018    = (TH1D*) f_btag_eff_2018->Get("h2_BTaggingEff_med_Eff_b");
    TH1D* h_btag_eff_c_temp_2018    = (TH1D*) f_btag_eff_2018->Get("h2_BTaggingEff_med_Eff_c");
    TH1D* h_btag_eff_udsg_temp_2018 = (TH1D*) f_btag_eff_2018->Get("h2_BTaggingEff_med_Eff_udsg");

    TH1D* h_btag_eff_b_2016    = (TH1D*) h_btag_eff_b_temp_2016->Clone("h_btag_eff_b");
    TH1D* h_btag_eff_c_2016    = (TH1D*) h_btag_eff_c_temp_2016->Clone("h_btag_eff_c");
    TH1D* h_btag_eff_udsg_2016 = (TH1D*) h_btag_eff_udsg_temp_2016->Clone("h_btag_eff_udsg");

    TH1D* h_btag_eff_b_2017    = (TH1D*) h_btag_eff_b_temp_2017->Clone("h_btag_eff_b");
    TH1D* h_btag_eff_c_2017    = (TH1D*) h_btag_eff_c_temp_2017->Clone("h_btag_eff_c");
    TH1D* h_btag_eff_udsg_2017 = (TH1D*) h_btag_eff_udsg_temp_2017->Clone("h_btag_eff_udsg");

    TH1D* h_btag_eff_b_2018    = (TH1D*) h_btag_eff_b_temp_2018->Clone("h_btag_eff_b");
    TH1D* h_btag_eff_c_2018    = (TH1D*) h_btag_eff_c_temp_2018->Clone("h_btag_eff_c");
    TH1D* h_btag_eff_udsg_2018 = (TH1D*) h_btag_eff_udsg_temp_2018->Clone("h_btag_eff_udsg");

    std::map<std::string,TH1D*> eff2016 {
        {"btag", h_btag_eff_b_2016},
        {"ctag", h_btag_eff_c_2016},
        {"udsgtag", h_btag_eff_udsg_2016},
    };

    std::map<std::string,TH1D*> eff2017 {
        {"btag", h_btag_eff_b_2017},
        {"ctag", h_btag_eff_c_2017},
        {"udsgtag", h_btag_eff_udsg_2017},
    };

    std::map<std::string,TH1D*> eff2018 {
        {"btag", h_btag_eff_b_2018},
        {"ctag", h_btag_eff_c_2018},
        {"udsgtag", h_btag_eff_udsg_2018},
    };

    h_btag_eff_b_temp_2016->Delete();
    h_btag_eff_c_temp_2016->Delete();
    h_btag_eff_udsg_temp_2016->Delete();
    h_btag_eff_b_temp_2017->Delete();
    h_btag_eff_c_temp_2017->Delete();
    h_btag_eff_udsg_temp_2017->Delete();
    h_btag_eff_b_temp_2018->Delete();
    h_btag_eff_c_temp_2018->Delete();
    h_btag_eff_udsg_temp_2018->Delete();

    //csv paths
    string csv_path_2016 = "../../NanoTools/NanoCORE/Tools/btagsf/csv/DeepJet_2016LegacySF_WP_V1.csv";
    string csv_path_2017 = "../../NanoTools/NanoCORE/Tools/btagsf/csv/DeepFlavour_94XSF_WP_V3_B_F.csv";
    string csv_path_2018 = "../../NanoTools/NanoCORE/Tools/btagsf/csv/DeepJet_102XSF_WP_V1.csv";
    // CSV objects
    BTagCalibration deepjet_csv_2016 = BTagCalibration("csvv1", csv_path_2016);
    BTagCalibration deepjet_csv_2017 = BTagCalibration("csvv1", csv_path_2017);
    BTagCalibration deepjet_csv_2018 = BTagCalibration("csvv1", csv_path_2018);
    // Medium reader
    BTagCalibrationReader deepjet_medium_reader_2016 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
    BTagCalibrationReader deepjet_medium_reader_2017 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
    BTagCalibrationReader deepjet_medium_reader_2018 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
    deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_B, "comb");
    deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_C, "comb");
    deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_UDSG, "incl");
    deepjet_medium_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_B, "comb");
    deepjet_medium_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_C, "comb");
    deepjet_medium_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_UDSG, "incl");
    deepjet_medium_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_B, "comb");
    deepjet_medium_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_C, "comb");
    deepjet_medium_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_UDSG, "incl");



    auto outFileName = outputdir+"/"+chainTitle+"_"+TString(std::to_string(year).c_str())+"_hists.root";
    std::cout << "Will write histograms to " << outFileName.Data() << std::endl;

    HistContainer hists;
    hists.loadHists(chainTitleCh);

    //nEvents in chain
    unsigned int nEventsTotal = 0;
    //unsigned int nEventsChain = chain->GetEntries();
    //std::cout << "Events in Chain: " << nEventsChain << endl;

    //Set up iterator
    TObjArray *listOfFiles = list;
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    //delete chain;

    //Number of selected events
    //int nSelected = 0;

    tqdm bar;
    // bar.set_theme_braille();
    //BDT constructor
    BDT booster("./helpers/BDT/BDT.xml");
    std::string tmp_yr_str = std::to_string(year);
    //BDTBabyMaker bdt_fakes_baby(Form("./helpers/BDT/babies/%s/data_driven/%s_fakes.root", tmp_yr_str.c_str(), chainTitleCh));
    //BDTBabyMaker bdt_flips_baby(Form("./helpers/BDT/babies/%s/data_driven/%s_flips.root", tmp_yr_str.c_str(), chainTitleCh));
    BDTBabyMaker bdt_MC_baby(Form("./helpers/BDT/babies/%s/MC/%s.root", tmp_yr_str.c_str(), chainTitleCh));
    auto start = high_resolution_clock::now();

    //File Loop
    while ( (currentFile = (TFile*)fileIter.Next()) ){
        TFile *file = new TFile(currentFile->GetName());
        TString filename = currentFile->GetName();
        TTree *tree = (TTree*)file->Get("Events");
        nt.Init(tree);
        if (debugPrints){std::cout << "working on file " << filename << endl;}
        if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
        if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}

        float nFakes = 0.;
        float nFlips = 0.;
        float nRares = 0.;

        for ( unsigned int counter = 0; counter < tree->GetEntries(); counter++ ){ 
        //for ( unsigned int counter = 0; counter < 1000; counter++ ){ //for testing only!!
            //if (counter%100000==0){std::cout << "processed " << counter << " events and elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}

            nt.GetEntry(counter);
            if ( nevts>0 && nEventsTotal>=nevts ) break;
            ++nEventsTotal;

            //if (!quiet) bar.progress(nEventsTotal, nEventsChain);

            // filter lumi blocks not in the good run list
            if ( isData && !goodrun( nt.run(), nt.luminosityBlock() ) ) continue;

            // remove duplicates
            if ( isData ) {
                duplicate_removal::DorkyEventIdentifier id( nt.run(), nt.event(), nt.luminosityBlock() );
                if ( duplicate_removal::is_duplicate(id) ) continue;
            }

            //if(nt.event()!=313915097){continue;}

            //MET CUT
            if (nt.MET_pt() < 50.){continue;}
            if (debugPrints){std::cout << "passed MET cut for event " << nt.event() << ": " << nt.MET_pt() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}

            //get event weight based on sample!
            // cout << nt.event() << endl;
            double weight = 1.;
            if (!isData){
                weight = getEventWeight( file->GetName(), chainTitle.Data(), nt.year() );
                // cout << "scale1fb: " << weight << endl;
                //double weight = 1.;
                double genWeight = nt.Generator_weight();
                // cout << "genWeight: " << genWeight << endl;
                weight = (weight*genWeight*lumi)/(abs(genWeight));
                // cout << "weight: " << weight << endl;
                // cout << "lumi: " << lumi << endl;
            }else {weight = 1.;}
            // cout << weight << endl;
            double evtWeight = weight; 
            if (debugPrints){std::cout << "passed eventWeight for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}


            // cutflow counter
            int cutflow_counter=1;
            hists.fill1d("cutflow","br",chainTitleCh,1,weight);
            cutflow_counter++;

            // load the leptons
            Leptons leptons = getLeptons();
            Leptons tight_leptons = getTightLeptons();
            Leptons loose_leptons = getLooseLeptons();
            unsigned int nleps_tight = tight_leptons.size();
            unsigned int nleps_loose = loose_leptons.size();

            if (!quiet) {
                std::cout << "Event has " << nleps_loose << " loose leptons and "
                          << nleps_tight << " tight leptons." << std::endl;
                for (auto lep: leptons) {
                    std::cout << "pdgId: " << lep.id() << ", pt: " << lep.pt() << ", eta: " << lep.eta()
                              << ", loose: " << lep.is_loose() << ", tight: " << lep.is_tight() << std::endl;
                }
            }
            if (debugPrints){std::cout << "loaded leptons for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}


            // let's first figure out what kind of lepton hypothesis we have, by priority: 3L, TTL, TT, OS, TL, LL
            std::pair<int,Leptons> best_hyp_info = getBestHypFCNC(leptons,!quiet);
            int best_hyp_type = best_hyp_info.first;

            if (best_hyp_type < 0 && print_debug_file) {
                debug_file << nt.run() << "," << nt.luminosityBlock() << "," << nt.event() << ",";
                debug_file << " ," << loose_leptons.size() << "," << tight_leptons.size();
                debug_file << std::endl;
                for (auto lepton: loose_leptons) {debug_file << "\tL " << lepton.id() << "," << lepton.pt() << ", " << lepton.eta() << "," << lepton.is_loose() << ", " << lepton.is_tight() << std::endl;}
                debug_file << std::endl;
                continue;
            }
            
            if (best_hyp_type < 0) continue;
            else{hists.fill1d("cutflow","br",chainTitleCh,2,weight);}
            
            if(!quiet) {std::cout << "best_hyp_type: " << best_hyp_type << std::endl;}
            Leptons best_hyp = best_hyp_info.second;
            if (!quiet) std::cout << "best hyp type: " << best_hyp_type << std::endl;

            sort(best_hyp.begin(),best_hyp.end(),lepsort); // sort hyp leptons by pt (may already be done in getBestHyp)
            Lepton leading_lep = best_hyp[0];
            Lepton trailing_lep = best_hyp[1];
            Lepton third_lep;
            if (best_hyp.size()>2) third_lep = best_hyp[2];


            if (!quiet) {
                std::cout << "best hyp type: " << best_hyp_type << "; lepton ids: " << leading_lep.id()
                                                                << ", " << trailing_lep.id() << std::endl;
            }
            if (debugPrints){std::cout << "got best hyp for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}

            // now let's check if there are additional requirements we need to make
            bool is_fake = false;
            bool is_flip = false;
            bool is_os = false;
            bool is_rare = false;
            int nfakes=0;
            int nflips=0;
            if(!isData){
                for ( auto lep : best_hyp ) {if (lep.isFake()) nfakes++;}
                for ( auto lep : best_hyp ) {if (lep.isFlip() && lep.absid()==11) nflips++;}
                if (best_hyp.size() == 2 && best_hyp[0].charge()*best_hyp[1].charge()<0) is_os=true;
                if (nfakes>0 && !is_os) is_fake=true;
                if (best_hyp.size() == 2 && nflips==1) is_flip=true;
                if (!is_fake && (best_hyp.size()>2 || (best_hyp.size()==2 && !is_flip && best_hyp[0].charge()*best_hyp[1].charge()>0))) is_rare = true;
            }
            int category=4;
            if (is_flip) category=2;
            if (is_rare) category=3;
            if (is_fake) category=1;
            // cout << category << endl;
            if (debugPrints){std::cout << "got category for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}


            //for fake validation: gen matching for best_hyp leptons
            bool isVR_CR_fake = 0;
            bool isVR_SR_fake = 0;
            bool isEE = 0;
            bool isMM = 0;
            bool isEM = 0;
            bool isME = 0;
            bool isEFake = 0;
            bool isMFake = 0;
            //for flip validation: gen matching for best_hyp leptons
            bool isVR_CR_flip = 0;
            bool isVR_SR_flip = 0;
            bool isEE_flip = 0;
            bool isEM_flip = 0;
            if (!isData){
                vector<int> nPromptTight;
                vector<int> nNonPromptTight;
                vector<int> nPromptLoose;
                vector<int> nNonPromptLoose;
                for ( auto lep : loose_leptons){
                    if (lep.idlevel()==SS::IDLevel::IDtight && (lep.genPartFlav()==1 || lep.genPartFlav()==15)){nPromptTight.push_back(lep.absid());}
                    if (lep.idlevel()==SS::IDLevel::IDtight && !(lep.genPartFlav()==1 || lep.genPartFlav()==15)){nNonPromptTight.push_back(lep.absid());}
                    if (lep.idlevel()==SS::IDLevel::IDfakable && (lep.genPartFlav()==1 || lep.genPartFlav()==15)){nPromptLoose.push_back(lep.absid());}
                    if (lep.idlevel()==SS::IDLevel::IDfakable && !(lep.genPartFlav()==1 || lep.genPartFlav()==15)){nNonPromptLoose.push_back(lep.absid());}
                }
                vector<int> nTightNotFlip;
                vector<int> nTightFlip;
                //cout << "******************" << endl;
                for ( auto lep : tight_leptons ){
                    //cout << lep.id() << " " << lep.mcid() << " " << lep.pt() << " " << lep.eta() << " " << lep.isFlip() << endl;
                    if (lep.idlevel()==SS::IDLevel::IDtight && (lep.genPartFlav()==1||lep.genPartFlav()==15) && !lep.isFlip()){nTightNotFlip.push_back(lep.id());}
                    if (lep.idlevel()==SS::IDLevel::IDtight && (lep.genPartFlav()==1||lep.genPartFlav()==15) && lep.absid()==11 && lep.isFlip()){nTightFlip.push_back(lep.id());}
                }

                if(best_hyp.size()==2){
                    //fake categorization
                    if ((nPromptTight.size()==1&&nNonPromptTight.size()==1)||(nNonPromptTight.size()==2)){
                        isVR_SR_fake=1;
                        if (nPromptTight.size()==1){
                            if (nPromptTight[0]==11 && nNonPromptTight[0]==11){isEE=1;}
                            else if (nPromptTight[0]==11 && nNonPromptTight[0]==13){isEM=1;}
                            else if (nPromptTight[0]==13 && nNonPromptTight[0]==11){isME=1;}
                            else if (nPromptTight[0]==13 && nNonPromptTight[0]==13){isMM=1;}
                        }else{
                            if (nNonPromptTight[0]==11 && nNonPromptTight[1]==11){isEE=1;}
                            else if (nNonPromptTight[0]==11 && nNonPromptTight[1]==13){isEM=1;}
                            else if (nNonPromptTight[0]==13 && nNonPromptTight[1]==11){isME=1;}
                            else if (nNonPromptTight[0]==13 && nNonPromptTight[1]==13){isMM=1;}
                        }
                    }
                    if ((nPromptTight.size()==1&&nNonPromptLoose.size()==1)||(nNonPromptLoose.size()==2)){
                        isVR_CR_fake=1;
                        if (nPromptTight.size()==1){
                            if (nPromptTight[0]==11 && nNonPromptLoose[0]==11){isEE=1;}
                            else if (nPromptTight[0]==11 && nNonPromptLoose[0]==13){isEM=1;}
                            else if (nPromptTight[0]==13 && nNonPromptLoose[0]==11){isME=1;}
                            else if (nPromptTight[0]==13 && nNonPromptLoose[0]==13){isMM=1;}
                        }else{
                            if (nNonPromptLoose[0]==11 && nNonPromptLoose[1]==11){isEE=1;}
                            else if (nNonPromptLoose[0]==11 && nNonPromptLoose[1]==13){isEM=1;}
                            else if (nNonPromptLoose[0]==13 && nNonPromptLoose[1]==11){isME=1;}
                            else if (nNonPromptLoose[0]==13 && nNonPromptLoose[1]==13){isMM=1;}
                        }
                    }
                    //flip categorization
                    if(nTightNotFlip.size()==2 && (nTightNotFlip[0]/abs(nTightNotFlip[0]))!=(nTightNotFlip[1]/abs(nTightNotFlip[1]))){
                        //check if there's an electron in the CR event
                        if(abs(nTightNotFlip[0])==11){
                            if(abs(nTightNotFlip[1])==11){
                                isVR_CR_flip=1;
                                isEE_flip=1;
                            }else{
                                isVR_CR_flip=1;
                                isEM_flip=1;
                            }
                        }else if(abs(nTightNotFlip[1])==11){
                            isVR_CR_flip=1;
                            isEM_flip=1;
                        }
                    }
                    //can't enter VR SR without containing an electron
                    //because nTightFlip isn't filled for muons
                    if(nTightNotFlip.size()==1 && nTightFlip.size()==1 && (nTightNotFlip[0]/abs(nTightNotFlip[0]))==(nTightFlip[0]/abs(nTightFlip[0]))){
                        isVR_SR_flip=1;
                        //cout << "found a VR_SR event" << endl;
                        if(abs(nTightNotFlip[0])==11&&abs(nTightFlip[0])==11){isEE_flip=1;}
                        else{isEM_flip=1;}
                    }
                }
                if(best_hyp.size()==3){
                    isVR_CR_flip = 0;
                    isVR_SR_flip = 0;
                    isEE_flip = 0;
                    isEM_flip = 0;
                    
                    if ((nPromptTight.size()==2&&nNonPromptTight.size()==1)||(nPromptTight.size()==1&&nNonPromptTight.size()==2)){
                        isVR_SR_fake=1;
                        if (nNonPromptTight.size()==1){
                            if (nNonPromptTight[0]==11){isEFake=1;}
                            else if (nNonPromptTight[0]==13){isMFake=1;}
                        }else{
                            if (nNonPromptTight[0]==11 && nNonPromptTight[1]==11){isEE=1;}
                            else if (nNonPromptTight[0]==11 && nNonPromptTight[1]==13){isEM=1;}
                            else if (nNonPromptTight[0]==13 && nNonPromptTight[1]==11){isME=1;}
                            else if (nNonPromptTight[0]==13 && nNonPromptTight[1]==13){isMM=1;}
                        }
                    }
                    if ((nPromptTight.size()==2&&nNonPromptLoose.size()==1)||(nPromptTight.size()==1&&nNonPromptLoose.size()==2)){
                        isVR_CR_fake=1;
                        if (nNonPromptLoose.size()==1){
                            if (nNonPromptLoose[0]==11){isEFake=1;}
                            else if (nNonPromptLoose[0]==13){isMFake=1;}
                        }else{
                            if (nNonPromptLoose[0]==11 && nNonPromptLoose[1]==11){isEE=1;}
                            else if (nNonPromptLoose[0]==11 && nNonPromptLoose[1]==13){isEM=1;}
                            else if (nNonPromptLoose[0]==13 && nNonPromptLoose[1]==11){isME=1;}
                            else if (nNonPromptLoose[0]==13 && nNonPromptLoose[1]==13){isMM=1;}
                        }
                    }
                }
            }
            if (debugPrints){std::cout << "passed validation categorization for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}

            // get jets and bjets
            std:pair<Jets, Jets> good_jets_and_bjets = getJets(best_hyp);
            Jets good_jets = good_jets_and_bjets.first;
            Jets good_bjets = good_jets_and_bjets.second;
            int njets = good_jets.size();
            int nbjets = good_bjets.size();
            sort(good_jets.begin(),good_jets.end(),jetptsort);
            sort(good_bjets.begin(),good_bjets.end(),jetptsort);
            float ht = 0.;
            for (auto jet : good_jets) ht += jet.pt();

            //BJET CUT
            if(nbjets<1){continue;}

            if (debugPrints){std::cout << "loaded jets for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}


            //apply SFs to MC events
            // cout << nt.event() << endl;
            // cout << weight << endl;
            if (!isData){
                //apply lepton SFs to hypothesis leptons
                for ( auto lep : best_hyp ) {weight = weight * leptonScaleFactor(nt.year(), lep.id(), lep.pt(), lep.eta(), ht);}
                // cout << "after lepton SF: " << weight << endl;

                //apply PU weight
                weight = weight * nt.puWeight();
                // cout << "after PU weight: " << weight << endl;

                //only apply trigger scale factors to dilepton events
                if (best_hyp.size()==2){weight = weight * triggerScaleFactor(f_trigEff, nt.year(), best_hyp[0].id(), best_hyp[1].id(), best_hyp[0].pt(), best_hyp[1].pt(), best_hyp[0].eta(), best_hyp[1].eta(), ht, 0);}
                // cout << "after trigger SF: " << weight << endl;

                //applying b-tag SFs
                if (nt.year() == 2016){weight = weight * getBSF(nt.year(),good_jets,good_bjets,eff2016,deepjet_medium_reader_2016);}
                else if (nt.year() == 2017){weight = weight * getBSF(nt.year(),good_jets,good_bjets,eff2017,deepjet_medium_reader_2017);}
                else if (nt.year() == 2018){weight = weight * getBSF(nt.year(),good_jets,good_bjets,eff2018,deepjet_medium_reader_2018);}
                // cout << "after b tag SF: " << weight << endl;
            }
            if(isnan(weight)||isinf(weight)){
                cout << "found a wrong weight!!!!!" << endl;
                cout << nt.event() << endl;
                cout << "final weight: " << weight << endl;
                cout << "******************" << endl;
            }
            if ((category == 1 && chainTitle=="fakes_mc")||
                (category == 2 && chainTitle=="flips_mc")||
                (category == 3 && chainTitle=="rares")||
                // (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData))||
                (isSignal||isData)){
                
                hists.fill1d("cutflow","br",chainTitleCh,3,weight);
            }
            if (debugPrints){std::cout << "passed sfs for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<milliseconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<milliseconds>(high_resolution_clock::now() - startBOpening).count() << endl;}


            if (print_debug_file) {
                debug_file << nt.run() << "," << nt.luminosityBlock() << "," << nt.event() << ",";
                print_debug(debug_file,best_hyp_type,best_hyp,good_jets,good_bjets,category);
                //debug_file << std::endl;
            }
            
            // if there isn't a good lepton hypothesis
            if (best_hyp_type<0) continue;
            //else {hists.fill1d("cutflow","br",chainTitleCh,2,weight);}


            if (!quiet) {
                std::cout << "Event has " << good_jets.size() << " jets and "
                          << good_bjets.size() << " b-tagged jets." << std::endl;
            }

            if (best_hyp.size()==2&&njets < 2) continue;
            if (best_hyp.size()>2&&njets < 1) continue;
            if ((category == 1 && chainTitle=="fakes_mc")||
                (category == 2 && chainTitle=="flips_mc")||
                (category == 3 && chainTitle=="rares")||
                // (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData))||
                (isSignal||isData)){
                hists.fill1d("cutflow","br",chainTitleCh,4,weight);
            }

            if (!quiet) {
                std::cout << "leading jet pt: " << good_jets[0].pt() << std::endl;
            }

            if (doFakes && !isData && doTruthFake && !is_fake) continue;
            if (doFlips && !isData && doTruthFlip && !is_flip) continue;
            if (nt.year()==2016){
                if(!(nt.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL()||
                     nt.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ()||
                     nt.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ()||
                     nt.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ()||
                     nt.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ())) {continue;}
            }else if (nt.year()==2017){
                if(!(nt.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL()||
                     nt.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8()||
                     nt.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL()||
                     nt.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ()||
                     nt.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ())) {continue;}
            }else if (nt.year()==2018){
                if(!(nt.HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8()||
                     nt.HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL()||
                     nt.HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ()||
                     nt.HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ())) {continue;}
            }
            if(debugPrints){std::cout << "passed triggers for event " << nt.event() << endl;}
            if ((category == 1 && chainTitle=="fakes_mc")||
                (category == 2 && chainTitle=="flips_mc")||
                (category == 3 && chainTitle=="rares")||
                // (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData))||
                (isSignal||isData)){
                hists.fill1d("cutflow","br",chainTitleCh,5,weight);
            }
            if (debugPrints){std::cout << "passed triggers for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<seconds>(high_resolution_clock::now() - startBOpening).count() << endl;}

            if (nt.year()==2016){
                if(!(nt.Flag_globalSuperTightHalo2016Filter()&&
                     nt.Flag_HBHENoiseFilter()&&
                     nt.Flag_HBHENoiseIsoFilter()&&
                     nt.Flag_EcalDeadCellTriggerPrimitiveFilter()&&
                     nt.Flag_BadPFMuonFilter()&&
                     nt.Flag_goodVertices())) {continue;}
            }else if (nt.year()==2017){
                if(!(nt.Flag_globalSuperTightHalo2016Filter()&&
                     nt.Flag_HBHENoiseFilter()&&
                     nt.Flag_HBHENoiseIsoFilter()&&
                     nt.Flag_EcalDeadCellTriggerPrimitiveFilter()&&
                     nt.Flag_BadPFMuonFilter()&&
                     nt.Flag_goodVertices()&&
                     nt.Flag_ecalBadCalibFilterV2())) {continue;}
            }else if (nt.year()==2018){
                if(!(nt.Flag_globalSuperTightHalo2016Filter()&&
                     nt.Flag_HBHENoiseFilter()&&
                     nt.Flag_HBHENoiseIsoFilter()&&
                     nt.Flag_EcalDeadCellTriggerPrimitiveFilter()&&
                     nt.Flag_BadPFMuonFilter()&&
                     nt.Flag_goodVertices()&&
                     nt.Flag_ecalBadCalibFilterV2())) {continue;}
            }

            if ((category == 1 && chainTitle=="fakes_mc")||
                (category == 2 && chainTitle=="flips_mc")||
                (category == 3 && chainTitle=="rares")||
                // (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData))||
                (isSignal||isData)){
                hists.fill1d("cutflow","br",chainTitleCh,6,weight);
            }
            if (debugPrints){std::cout << "passed filters for event " << nt.event() << endl;}
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<seconds>(high_resolution_clock::now() - startBOpening).count() << endl;}

            //calculate control region weights for background estimates
            //we calculate the weight
            float crWeight = 0;
            //start with fake rate weight
            if (best_hyp_type==3||best_hyp_type>=6){
                float fakeWeight = 1;
                // FIX ME: MOVE TO SSSELECTIONS
                for (auto lep : loose_leptons){
                    if (lep.idlevel()==SS::IDLevel::IDtight) continue;
                    float ptrel_cut = 0;
                    float miniIso_cut = 0;
                    float ptRatio_cut = 0;
                    if (nt.year() == 2016){
                        if(lep.absid()==11){
                            ptrel_cut = 7.2;
                            miniIso_cut = 0.12;
                            ptRatio_cut = 0.80;
                        }else if(lep.absid()==13){
                            ptrel_cut = 7.2;
                            miniIso_cut = 0.12;
                            ptRatio_cut = 0.76;
                        }
                    }else{
                        if(lep.absid()==11){
                            ptrel_cut = 8.0;
                            miniIso_cut = 0.07;
                            ptRatio_cut = 0.78;
                        }else if(lep.absid()==13){
                            ptrel_cut = 6.8;
                            miniIso_cut = 0.11;
                            ptRatio_cut = 0.74;
                        }
                    }
                    float coneCorrPtValue = coneCorrPt(lep.id(), lep.idx(), miniIso_cut, ptRatio_cut, ptrel_cut);
                    float fakeRateValue = fakeRate(year, lep.id(), coneCorrPtValue, lep.eta(), isData);
                    fakeWeight = fakeWeight * (fakeRateValue/(1-fakeRateValue));
                }
                crWeight = weight * fakeWeight;
                //std::cout << crWeight << std::endl;
            }

            //now, we move to the flip weight
            if (best_hyp_type==5){
                //cout << "******************" << endl;
                float flipWeight = 0;
                for (auto lep : tight_leptons){
                    //cout << lep.id() << " " << lep.mcid() << " " << lep.pt() << " " << lep.eta() << " " << lep.isFlip() << endl;
                    if (lep.absid()==13){continue;}
                    float flipRateValue = flipRate(nt.year(),lep.pt(),lep.eta());
                    if(nt.year()==2016){flipRateValue *= 1.1128218361769364;}
                    if(nt.year()==2017){flipRateValue *= 1.4447739510004296;}
                    if(nt.year()==2018){flipRateValue *= 1.3061565063535605;}
                    //std::cout << "flip rate: " << flipRateValue << endl;
                    flipWeight = flipWeight + (flipRateValue/(1-flipRateValue));
                    //std::cout << "flip Weight: " << flipWeight << endl;
                }
                crWeight = weight * flipWeight;
                //std::cout << "event crWeight: " << crWeight << endl;
            }
            if (debugPrints){std::cout << "passed crWeight for event " << nt.event() << endl;}
            // prepare BDT parameters
            if (njets < 2) {
                continue;
            }
            //auto start_time = high_resolution_clock::now();
            bool fill_BDT_MC = (((category==1) && (chainTitle=="fakes_mc")) ||
                               ((category==2) && (chainTitle=="flips_mc")) ||
                               ((category==3) && (chainTitle=="rares"   )) ||
                               ((chainTitle=="signal_tch"))                ||
                               ((chainTitle=="signal_tuh"))                );
            bool fill_BDT_data_driven = (abs(crWeight) > 0.0);
            //std::cout << "fill_BDT_data_driven: " << fill_BDT_data_driven << std::endl;
            //std::cout << "category: " << category << "\tchainTitle: " << chainTitle;
            //std::cout << "\tfill_BDT: " << fill_BDT << std::endl;
            if (fill_BDT_MC) {
                if ((best_hyp_type == 4) || (((best_hyp.size() > 2) && (best_hyp_type==2)))) {
                    std::map<std::string, Float_t> BDT_params = booster.calculate_features(good_jets, good_bjets, ht, best_hyp);
                    bdt_MC_baby.set_features(BDT_params, weight);
                }
            }
            else if (fill_BDT_data_driven) {
                if (best_hyp_type == 5){
                    Float_t BDT_crWeight = crWeight;
                    std::map<std::string, Float_t> BDT_params = booster.calculate_features(good_jets, good_bjets, ht, best_hyp);
                    //bdt_fakes_baby.set_features(BDT_params, BDT_crWeight);

                } else if ((best_hyp_type==3) || (best_hyp_type>=6)) {
                    Float_t BDT_crWeight = crWeight;
                    std::map<std::string, Float_t> BDT_params = booster.calculate_features(good_jets, good_bjets, ht, best_hyp);
                    //bdt_flips_baby.set_features(BDT_params, BDT_crWeight);
                }
            }
            //booster.set_features(BDT_params);
            //booster.get_score();
            //cout << "BDT eval time: " << duration_cast<microseconds>(high_resolution_clock::now() - start_time).count() << endl;
            //std::cout << booster.get_score() << endl;
            if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << endl;}
            if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<seconds>(high_resolution_clock::now() - startBOpening).count() << endl;}
            
            if (nleps_tight>=2) {
                if ((category == 1 && chainTitle=="fakes_mc")||
                    (category == 2 && chainTitle=="flips_mc")||
                    (category == 3 && chainTitle=="rares")||
                    // (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData))||
                    (isSignal||isData)){
                    hists.fill1d("cutflow","br",chainTitleCh,7,weight);
                }
            }
            if (nleps_tight==2&&tight_leptons[0].charge()*tight_leptons[1].charge()>0) {
                if ((category == 1 && chainTitle=="fakes_mc")||
                    (category == 2 && chainTitle=="flips_mc")||
                    (category == 3 && chainTitle=="rares")||
                    // (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData))||
                    (isSignal||isData)){
                    hists.fill1d("cutflow","br",chainTitleCh,8,weight);
                }
            }

            // if we've reached here we've passed the baseline selection
            // cout << category << endl;
            // fill histograms
            /*if ((chainTitle == "top"||chainTitle =="dy") && (best_hyp_type==4) ){
                hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
            }*/
            if (category == 1 && !(isSignal||isData)){
                // hists.fill("fakes_mc",best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
                hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
                if(print_sample_file){nFakes+=weight;}
            }else if (category == 2 && !(isSignal||isData)){
                // hists.fill("flips_mc",best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
                hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
                if(print_sample_file){nFlips+=weight;}
            }else if (category == 3 && !(isSignal||isData)){
                // hists.fill("rares",best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
                hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
                if(print_sample_file){nRares+=weight;}
            }else if (category == 4 && chainTitle!="fakes_mc" && chainTitle!="flips_mc" && chainTitle!="rares" && !(isSignal||isData)){
                hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,isEE_flip,isEM_flip,weight,crWeight);
            }else if (isSignal||isData){
                hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),isVR_SR_fake,isVR_CR_fake,isVR_SR_flip,isVR_CR_flip,isEE,isEM,isME,isMM,isEFake,isMFake,weight,crWeight);
            }
            //cout << "**********" << endl;
        }//loop over events
        if(print_sample_file){print_sample_yields(sample_file, filename ,nFlips, nFakes, nRares);}
        std::cout << "closing file " << file->GetName() << endl;
        if (debugPrints){std::cout << "elapsed time since start: " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << endl;}
        if (debugPrints){std::cout << "elapsed time since b SF start: " << duration_cast<seconds>(high_resolution_clock::now() - startBOpening).count() << endl;}
        file->Close();
        delete file;
     } // loop over files

     auto stop = high_resolution_clock::now();
     auto duration = duration_cast<milliseconds>(stop - start);
     if (debug_file.is_open()) debug_file.close();

     if (!quiet) cout << "processed " << nEventsTotal << " events in " << duration.count() << " milliseconds!!" << endl;
     cout << "processed " << nEventsTotal << " events in " << duration.count() << " milliseconds!!" << endl;
     //write histograms
     auto outFile = new TFile(outFileName.Data(), "recreate");
     if (!quiet) std::cout << "Writing " << chainTitleCh << " histograms to " << outFile->GetName() << std::endl;
     outFile->cd();
     hists.write();
     outFile->Close();
     //bdt_fakes_baby.close();
     //bdt_flips_baby.close();
     bdt_MC_baby.close();
}
