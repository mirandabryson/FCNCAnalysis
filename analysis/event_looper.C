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
#include "./helpers/sampleLoader.h"
#include "./helpers/weights.h"
#include "./helpers/histogrammingClass.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"
#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/Config.h"


using namespace std;
using namespace std::chrono;

void event_looper(){
    bool verbose = false;
    //global variables
    int year = 2018;
    double lumi = 137;
    string babyVersion = "fcnc_v3";
    string inputDir = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/"+babyVersion+"/";
    //vector< string > sample_names = {   "background", //for testing, removing background
    //                                    "signal_hut",
    //                                    "signal_hct"
    //                                };
    vector< string > sample_names = {"signal_hct"};

    auto outFile = new TFile("plots/outputHistos_test.root", "recreate");//for testing only!!

    MyHists hists;
    for(uint btype = 0; btype < sample_names.size(); btype++){
        // book histograms
        hists.load_hists(sample_names[btype]);
    }

    //Load samples
    for(uint btype = 0; btype < sample_names.size(); btype++){
        TChain* chain = new TChain("Events");
        vector<string> samples = loadSamples ( year, sample_names[btype],babyVersion );
        for ( uint s = 0; s < samples.size(); s++ ){
            string pathname = inputDir+samples[s];
            string name = inputDir+samples[s]+"/output_*.root";
            chain->Add(name.c_str());
        }
        cout << "Loaded Samples!" << endl;

        int nEvents = chain->GetEntries();
        cout << "found " << nEvents << " " << sample_names[btype] << " events" << endl;

        // setup iterator
        TObjArray *listOfFiles = chain->GetListOfFiles();
        TIter fileIter(listOfFiles);
        TFile *currentFile = 0;

        auto start = high_resolution_clock::now();

        //Find the exact sample name
        TFile* sFile(chain->GetFile());
        string sName = sFile->GetName();

        // loop over events
        while ( (currentFile = (TFile*)fileIter.Next()) ) {
            TFile *file = new TFile(currentFile->GetTitle());
            TString filename = currentFile->GetTitle();
            TTree *tree = (TTree*)file->Get("Events");
            nt.Init(tree);
//            for ( unsigned int counter = 0; counter < tree->GetEntries(); counter++ ){ //for testing only!!
            for ( unsigned int counter = 0; counter < 100; counter++ ){ //for testing only!!
                if ( counter%100000==0 ){
                    cout << "event " << counter << endl;
                }

                //Get individual event
                //Long64_t event = chain->GetEntry(counter);
                nt.GetEntry(counter);

                // print out sample name
                if ( counter%10000==0 ){
                    cout << filename.Data() << endl;
                }
                //get event weight based on sample!
                double weight = getEventWeight( sName, inputDir, babyVersion );
                double genWeight = nt.Generator_weight();
                weight = (weight*genWeight*lumi)/(abs(genWeight));

                // load the leptons
                Leptons leptons = getLeptons();
                Leptons tight_leptons = getTightLeptons();
                Leptons loose_leptons = getLooseLeptons();
                unsigned int nleps_tight = tight_leptons.size();
                unsigned int nleps_loose = loose_leptons.size();

                if (verbose) {
                    std::cout << "Event has " << nleps_loose << " loose leptons and "
                              << nleps_tight << " tight leptons." << std::endl;
                }

                // let's first figure out what kind of lepton hypothesis we have, by priority: 3L, TTL, TT, TL, OS
                std::pair<int,Leptons> best_hyp_info = getBestHypFCNC(leptons,false);
                int best_hyp_type = best_hyp_info.first;
                Leptons best_hyp = best_hyp_info.second;
                if (best_hyp_type<0) continue;
                sort(best_hyp.begin(),best_hyp.end(),lepsort);
                Lepton leading_lep = best_hyp[0];
                Lepton trailing_lep = best_hyp[1];
                Lepton third_lep;
                if (best_hyp.size()>2) third_lep = best_hyp[2];

                if (verbose) {
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

                if (verbose) {
                    std::cout << "Event has " << good_jets.size() << " jets and "
                              << good_bjets.size() << " b-tagged jets." << std::endl;
                }

                if (njets < 2) continue;

                if (verbose) {
                    std::cout << "leading jet pt: " << good_jets[0].pt() << std::endl;
                }

                // if we've reached here we've passed the baseline selection
                // fill histograms
                hists.fill(sample_names[btype],best_hyp,best_hyp_type,good_jets,good_bjets,nt.MET_pt(),weight);
           }//loop over events

        } // loop over files

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);

        cout << "processed " << nEvents << " events in " << duration.count() << " seconds!!" << endl;

        //write histograms
        std::cout << "Writing " << sample_names[btype] << " histograms to " << outFile->GetName() << std::endl;

        outFile->cd();
        hists.write(outFile);
    } // loop over samples
    outFile->Close();
}
