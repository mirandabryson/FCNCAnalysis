//Basic looper to categorize FCNC events
//Compile and run with root -l event_looper.C+
//March 2021
//Kaitlin Salyer

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <dirent.h>
#include <TChain.h>
#include <TChainElement.h>
#include <TLeaf.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>
#include <THStack.h>
#include <TLegend.h>
#include <TFile.h>
#include <signal.h>
#include "./helpers/weights.h"
#include "./helpers/histogrammingClass.h"
#include "./helpers/tqdm.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"
#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/Config.h"
#include "../../NanoTools/NanoCORE/Tools/goodrun.h"
#include "../../NanoTools/NanoCORE/Tools/dorky.h"
#include "../misc/common_utils.h"

using namespace std;
using namespace std::chrono;

void event_looper(TChain *chain, TString options="", int nevts=-1, TString outputdir="outputs/"){
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
    int doFakes = 0;
    int exclude = 0;
    bool isGamma = 0;
    bool truthfake = 0;
    bool skipmatching = 0;
    bool ignoreFakeFactor = 0;
    float scaleLumi=1.;
    int nbdtbins = 17;
    int nsrdisc = nbdtbins+1; // this is supposed to be 1 more than nbdtbins (we add in CRZ as a "bin")

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

    TString chainTitle = chain->GetTitle();
    const char* chainTitleCh = chainTitle.Data();
    if (!quiet) std::cout << "Working on " << chainTitle << std::endl;

    bool isFakes = (chainTitle=="fakes") || (chainTitle=="fakes_mc");
    bool isFlips = (chainTitle=="flips") || (chainTitle=="flips_mc");
    bool isRares = (chainTitle=="rares");
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
    std::string goodrun_path = "/home/users/fgolf/fcnc/current/samples/goodRunList/";
    std::map<int, std::string> goodrun_file = {
        {2016, "goldenJson_2016rereco_36p46ifb.txt"},
        {2017, "Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1_snt.txt"},
        {2018, "goldenJson_2018_final_59p76ifb_snt.txt"} };
    set_goodrun_file( (goodrun_path+goodrun_file[year]).c_str() );


    auto outFileName = outputdir+"/"+chainTitle+"_"+TString(std::to_string(year).c_str())+"_hists.root";
    std::cout << "Will write histograms to " << outFileName.Data() << std::endl;
    auto outFile = new TFile(outFileName.Data(), "recreate");//for testing only!!

    HistContainer hists;
    hists.loadHists(chainTitleCh);

        //nEvents in chain
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();

    //Set up iterator
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    //Number of selected events
    //int nSelected = 0;

    tqdm bar;
    // bar.set_theme_braille();

    auto start = high_resolution_clock::now();

    //File Loop
    while ( (currentFile = (TFile*)fileIter.Next()) ){
        TFile *file = new TFile(currentFile->GetTitle());
        TString filename = currentFile->GetTitle();
        TTree *tree = (TTree*)file->Get("Events");
        nt.Init(tree);

        for ( unsigned int counter = 0; counter < tree->GetEntries(); counter++ ){ //for testing only!!
            nt.GetEntry(counter);
            if ( nevts>0 && nEventsTotal>=nevts ) break;
            ++nEventsTotal;

            if (!quiet) bar.progress(nEventsTotal, nEventsChain);

            // filter lumi blocks not in the good run list
            if ( isData && !goodrun( nt.run(), nt.luminosityBlock() ) ) continue;

            // remove duplicates
            if ( isData ) {
                duplicate_removal::DorkyEventIdentifier id( nt.run(), nt.event(), nt.luminosityBlock() );
                if ( duplicate_removal::is_duplicate(id) ) continue;
            }

            //get event weight based on sample!
            double weight = getEventWeight( file->GetName(), chainTitle.Data() );
            double genWeight = nt.Generator_weight();
            weight = (weight*genWeight*lumi)/(abs(genWeight));

            // cutflow counter
            int cutflow_counter=1;
            hists.fill1d("cutflow","br",chainTitleCh,cutflow_counter,weight);
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
            }

            // let's first figure out what kind of lepton hypothesis we have, by priority: 3L, TTL, TT, OS, TL, LL
            std::pair<int,Leptons> best_hyp_info = getBestHypFCNC(leptons,false);
            int best_hyp_type = best_hyp_info.first;
            Leptons best_hyp = best_hyp_info.second;
            if (!quiet) std::cout << "best hyp type: " << best_hyp_type << std::endl;

            // if there isn't a good lepton hypothesis
            if (best_hyp_type<0) continue;
            else {hists.fill1d("cutflow","br",chainTitleCh,cutflow_counter,weight); cutflow_counter++;}
            if (nleps_tight>=2) {hists.fill1d("cutflow","br",chainTitleCh,cutflow_counter); cutflow_counter++;}

            sort(best_hyp.begin(),best_hyp.end(),lepsort); // sort hyp leptons by pt (may already be done in getBestHyp)
            Lepton leading_lep = best_hyp[0];
            Lepton trailing_lep = best_hyp[1];
            Lepton third_lep;
            if (best_hyp.size()>2) third_lep = best_hyp[2];

            if (!quiet) {
                std::cout << "best hyp type: " << best_hyp_type << "; lepton ids: " << leading_lep.id()
                                                                << ", " << trailing_lep.id() << std::endl;
            }

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

            if (!quiet) {
                std::cout << "Event has " << good_jets.size() << " jets and "
                          << good_bjets.size() << " b-tagged jets." << std::endl;
            }

            if (njets < 2) continue;

            if (!quiet) {
                std::cout << "leading jet pt: " << good_jets[0].pt() << std::endl;
            }

            // now let's check if there are additional requirements we need to make
            bool is_fake = false;
            bool is_flip = false;
            if (doFakes && !isData && doTruthFake) {
                int nfakes=0;
                for ( auto lep : best_hyp ) {if (lep.isFake()) nfakes++;}
                if (nfakes>0) is_fake=true;
                if (!is_fake) continue;
            }
            if (doFlips && !isData && doTruthFlip) {
                int nflips=0;
                for ( auto lep : best_hyp ) {if (lep.isFlip()) nflips++;}
                if (best_hyp.size() == 2 && nflips==1) is_flip=true;
                if (!is_flip) continue;
            }

            // if we've reached here we've passed the baseline selection
            // fill histograms
            hists.fill(chainTitleCh,best_hyp_type,best_hyp,good_jets,good_bjets,nt.MET_pt(),weight);
        }//loop over events
     } // loop over files

     auto stop = high_resolution_clock::now();
     auto duration = duration_cast<seconds>(stop - start);

     if (!quiet) cout << "processed " << nEventsTotal << " events in " << duration.count() << " seconds!!" << endl;

     //write histograms
     if (!quiet) std::cout << "Writing " << chainTitleCh << " histograms to " << outFile->GetName() << std::endl;

     outFile->cd();
     hists.write();
     outFile->Close();
}
