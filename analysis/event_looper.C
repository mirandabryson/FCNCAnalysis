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
#include <THStack.h>
#include <TLegend.h>
//#include <sampleClasses.h>
#include "./helpers/fcnc_functions.h"
#include "./helpers/sampleLoader.h"


using namespace std;
using namespace std::chrono;

void event_looper(){
    //global variables
    string year = "2018";
    string inputDir = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v1/2018/";
    vector< string > sample_names = {  "DY",
                                       "GluGlu",
                                       "Top",
                                       "W",
                                       "Z",
                                       "tHX",
                                       "other",
                                    };

    auto h_nJet_trilep_stacked = new THStack("h_nJet_trilep_stacked","nJet_trilep");
    auto h_nJet_SSdilep_stacked = new THStack("h_nJet_SSdilep_stacked","nJet_SSdilep");
    auto h_nJet_OSdilep_stacked = new THStack("h_nJet_OSdilep_stacked","nJet_OSdilep");
    auto h_nJet_onelepFO_stacked = new THStack("h_nJet_onelepFO_stacked","nJet_onelepFO");
    auto h_nJet_dilepFO_stacked = new THStack("h_nJet_dilepFO_stacked","nJet_dilepFO");

    auto h_nBJet_trilep_stacked = new THStack("h_nBJet_trilep_stacked","nBJet_trilep");
    auto h_nBJet_SSdilep_stacked = new THStack("h_nBJet_SSdilep_stacked","nBJet_SSdilep");
    auto h_nBJet_OSdilep_stacked = new THStack("h_nBJet_OSdilep_stacked","nBJet_OSdilep");
    auto h_nBJet_onelepFO_stacked = new THStack("h_nBJet_onelepFO_stacked","nBJet_onelepFO");
    auto h_nBJet_dilepFO_stacked = new THStack("h_nBJet_dilepFO_stacked","nBJet_dilepFO");

    auto h_MET_trilep_stacked = new THStack("h_MET_trilep_stacked","MET_trilep");
    auto h_MET_SSdilep_stacked = new THStack("h_MET_SSdilep_stacked","MET_SSdilep");
    auto h_MET_OSdilep_stacked = new THStack("h_MET_OSdilep_stacked","MET_OSdilep");
    auto h_MET_onelepFO_stacked = new THStack("h_MET_onelepFO_stacked","MET_onelepFO");
    auto h_MET_dilepFO_stacked = new THStack("h_MET_dilepFO_stacked","MET_dilepFO");

    auto h_minMT_trilep_stacked = new THStack("h_minMT_trilep_stacked","minMT_trilep");
    auto h_minMT_SSdilep_stacked = new THStack("h_minMT_SSdilep_stacked","minMT_SSdilep");
    auto h_minMT_OSdilep_stacked = new THStack("h_minMT_OSdilep_stacked","minMT_OSdilep");
    auto h_minMT_onelepFO_stacked = new THStack("h_minMT_onelepFO_stacked","minMT_onelepFO");
    auto h_minMT_dilepFO_stacked = new THStack("h_minMT_dilepFO_stacked","minMT_dilepFO");

    auto leg_nJet_trilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nJet_SSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nJet_OSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nJet_onelepFO = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nJet_dilepFO = new TLegend(0.7, 0.7, 0.89, 0.89);

    auto leg_nBJet_trilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nBJet_SSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nBJet_OSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nBJet_onelepFO = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_nBJet_dilepFO = new TLegend(0.7, 0.7, 0.89, 0.89);

    auto leg_MET_trilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_MET_SSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_MET_OSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_MET_onelepFO = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_MET_dilepFO = new TLegend(0.7, 0.7, 0.89, 0.89);

    auto leg_minMT_trilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_minMT_SSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_minMT_OSdilep = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_minMT_onelepFO = new TLegend(0.7, 0.7, 0.89, 0.89);
    auto leg_minMT_dilepFO = new TLegend(0.7, 0.7, 0.89, 0.89);

    //Load samples
    for(uint btype = 0; btype < sample_names.size(); btype++){
    //for(uint btype = 0; btype < 4; btype++){ //for testing only!!!
        TChain chain("Events");
        vector<string> samples = loadSamples ( year, sample_names[btype] );
        for ( uint s = 0; s < samples.size(); s++ ){
            string name = inputDir+samples[s]+"/output_*.root";
            chain.Add(name.c_str());
        }
        cout << "Loaded Samples!" << endl;

        int nEvents = chain.GetEntries();
        cout << "found " << nEvents << " " << sample_names[btype] << " events" << endl;

        //event variables
        uint nMuon = 0;
        uint nElectron = 0;
        uint nJet = 0;
        float MET = 0;
        float MET_phi = 0;

        chain.SetBranchAddress("nMuon", &nMuon);
        chain.SetBranchAddress("nElectron", &nElectron);
        chain.SetBranchAddress("nJet", &nJet);
        chain.SetBranchAddress("MET_pt", &MET);
        chain.SetBranchAddress("MET_phi", &MET_phi);


        //Define histograms
        auto h_nJet_trilep = new TH1F("h_nJet_trilep"+sample_names[btype],   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep = new TH1F("h_nJet_SSdilep"+sample_names[btype],  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep = new TH1F("h_nJet_OSdilep"+sample_names[btype],  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO = new TH1F("h_nJet_onelepFO"+sample_names[btype], "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO = new TH1F("h_nJet_dilepFO"+sample_names[btype],  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep = new TH1F("h_nBJet_trilep"+sample_names[btype],   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep = new TH1F("h_nBJet_SSdilep"+sample_names[btype],  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep = new TH1F("h_nBJet_OSdilep"+sample_names[btype],  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO = new TH1F("h_nBJet_onelepFO"+sample_names[btype], "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO = new TH1F("h_nBJet_dilepFO"+sample_names[btype],  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep = new TH1F("h_MET_trilep"+sample_names[btype],   "MET", 5, 0, 500);
        auto h_MET_SSdilep = new TH1F("h_MET_SSdilep"+sample_names[btype],  "MET", 5, 0, 500);
        auto h_MET_OSdilep = new TH1F("h_MET_OSdilep"+sample_names[btype],  "MET", 5, 0, 500);
        auto h_MET_onelepFO = new TH1F("h_MET_onelepFO"+sample_names[btype], "MET", 5, 0, 500);
        auto h_MET_dilepFO = new TH1F("h_MET_dilepFO"+sample_names[btype],  "MET", 5, 0, 500);

        auto h_minMT_trilep = new TH1F("h_minMT_trilep"+sample_names[btype],   "minMT", 5, 0, 500);
        auto h_minMT_SSdilep = new TH1F("h_minMT_SSdilep"+sample_names[btype],  "minMT", 5, 0, 500);
        auto h_minMT_OSdilep = new TH1F("h_minMT_OSdilep"+sample_names[btype],  "minMT", 5, 0, 500);
        auto h_minMT_onelepFO = new TH1F("h_minMT_onelepFO"+sample_names[btype], "minMT", 5, 0, 500);
        auto h_minMT_dilepFO = new TH1F("h_minMT_dilepFO"+sample_names[btype],  "minMT", 5, 0, 500);

        cout << "defined histograms!" << endl;

        auto start = high_resolution_clock::now();

        int nTriLep   = 0;
        int nSSDiLep  = 0;
        int nOSDiLep  = 0;
        int nOneLepFO = 0;
        int nFODiLep  = 0;

        //Main for loop
        //for ( int counter = 0; counter < nEvents; counter++ ){
        for ( int counter = 0; counter < 100; counter++ ){ //for testing only!!
            //cout << "counter " << counter << endl;
            if ( counter%100000==0 ){
                cout << "event " << counter << endl;
            }

            Long64_t event = chain.GetEntry(counter);
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
                    float mu_phi = chain.GetLeaf("Muon_phi")->GetValue(mu);
                    float mu_charge = chain.GetLeaf("Muon_charge")->GetValue(mu);
                    float mu_iso = chain.GetLeaf("Muon_miniPFRelIso_all")->GetValue(mu);
                    float mu_tightId = chain.GetLeaf("Muon_tightId")->GetValue(mu);
                    float mu_looseId = chain.GetLeaf("Muon_looseId")->GetValue(mu);

                    if ( isTightLepton( 13, mu_pt, mu_eta, mu_iso, mu_tightId ) ){
                        nGoodLep += 1;
                        muCharge_tight.push_back(mu_charge);
                        if ( mt( MET, MET_phi, mu_pt, mu_phi ) < minMT_tight ){
                            minMT_tight = mt( MET, MET_phi, mu_pt, mu_phi );
                        }
                    }else if ( isLooseLepton( 13, mu_pt, mu_eta, mu_iso, mu_looseId ) ){
                        nFakeableLep += 1;
                        muCharge_loose.push_back(mu_charge);
                        if ( mt( MET, MET_phi, mu_pt, mu_phi ) < minMT_loose ){
                            minMT_loose = mt( MET, MET_phi, mu_pt, mu_phi );
                        }
                    }else continue;
                }
                //loop to count tight/loose electrons
                for( uint el = 0; el < nElectron; el++ ){
                    //cout << (*el_pt)[el] << endl;
                    float el_pt = chain.GetLeaf("Electron_pt")->GetValue(el);
                    float el_eta = chain.GetLeaf("Electron_eta")->GetValue(el);
                    float el_phi = chain.GetLeaf("Electron_phi")->GetValue(el);
                    float el_charge = chain.GetLeaf("Electron_charge")->GetValue(el);
                    float el_iso = chain.GetLeaf("Electron_miniPFRelIso_all")->GetValue(el);

                    if ( isTightLepton( 13, el_pt, el_eta, el_iso, 0 ) ){
                        nGoodLep += 1;
                        elCharge_tight.push_back(el_charge);
                        if ( mt( MET, MET_phi, el_pt, el_phi ) < minMT_tight ){
                            minMT_tight = mt( MET, MET_phi, el_pt, el_phi );
                        }
                    }else if ( isLooseLepton( 13, el_pt, el_eta, el_iso, 0 ) ){
                        nFakeableLep += 1;
                        elCharge_loose.push_back(el_charge);
                        if ( mt( MET, MET_phi, el_pt, el_phi ) < minMT_loose ){
                            minMT_loose = mt( MET, MET_phi, el_pt, el_phi );
                        }
                    }else continue;
                }
            }
        
            //organize into signature types
            if ( nGoodLep == 3 ){
                nTriLep += 1;
                h_nJet_trilep->Fill(nJets);
                h_nBJet_trilep->Fill(nBjets);
                h_MET_trilep->Fill(MET);
                h_minMT_trilep->Fill(minMT_tight);
            }
            if ( nGoodLep == 2 ){
                if (muCharge_tight.size() == 2){
                    if (muCharge_tight[0]*muCharge_tight[1]>0){
                        nSSDiLep += 1;
                        h_nJet_SSdilep->Fill(nJets);
                        h_nBJet_SSdilep->Fill(nBjets);
                        h_MET_SSdilep->Fill(MET);
                        h_minMT_SSdilep->Fill(minMT_tight);
                    }else{ 
                        nOSDiLep += 1;
                        h_nJet_OSdilep->Fill(nJets);
                        h_nBJet_OSdilep->Fill(nBjets);
                        h_MET_OSdilep->Fill(MET);
                        h_minMT_OSdilep->Fill(minMT_tight);
                    }
                }else if (elCharge_tight.size() == 2) {
                    if (elCharge_tight[0]*elCharge_tight[1]>0){
                        nSSDiLep += 1;
                        h_nJet_SSdilep->Fill(nJets);
                        h_nBJet_SSdilep->Fill(nBjets);
                        h_MET_SSdilep->Fill(MET);
                        h_minMT_SSdilep->Fill(minMT_tight);
                    }else{
                        nOSDiLep += 1;
                        h_nJet_OSdilep->Fill(nJets);
                        h_nBJet_OSdilep->Fill(nBjets);
                        h_MET_OSdilep->Fill(MET);
                        h_minMT_OSdilep->Fill(minMT_tight);
                    }
                }else if (muCharge_tight.size() == 1) {
                    if (muCharge_tight[0]*elCharge_tight[0]>0){
                        nSSDiLep += 1;
                        h_nJet_SSdilep->Fill(nJets);
                        h_nBJet_SSdilep->Fill(nBjets);
                        h_MET_SSdilep->Fill(MET);
                        h_minMT_SSdilep->Fill(minMT_tight);
                    }else{
                        nOSDiLep += 1;
                        h_nJet_OSdilep->Fill(nJets);
                        h_nBJet_OSdilep->Fill(nBjets);
                        h_MET_OSdilep->Fill(MET);
                        h_minMT_OSdilep->Fill(minMT_tight);
                    }
                }
            }//if nGoodLep == 2
            if (nGoodLep == 1 and nFakeableLep == 1){
                nOneLepFO += 1;
                h_nJet_onelepFO->Fill(nJets);
                h_nBJet_onelepFO->Fill(nBjets);
                h_MET_onelepFO->Fill(MET);
                if (minMT_tight < minMT_loose){
                    h_minMT_onelepFO->Fill(minMT_tight);
                } else if (minMT_loose < minMT_tight){
                    h_minMT_onelepFO->Fill(minMT_loose);
                }
            }
            if (nFakeableLep == 2){
                nFODiLep += 1;
                h_nJet_dilepFO->Fill(nJets);
                h_nBJet_dilepFO->Fill(nBjets);
                h_MET_dilepFO->Fill(MET);
                h_minMT_dilepFO->Fill(minMT_loose);
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

        h_nJet_trilep_stacked->Add(h_nJet_trilep);
        h_nJet_SSdilep_stacked->Add(h_nJet_SSdilep);
        h_nJet_OSdilep_stacked->Add(h_nJet_OSdilep);
        h_nJet_onelepFO_stacked->Add(h_nJet_onelepFO);
        h_nJet_dilepFO_stacked->Add(h_nJet_dilepFO);

        h_nBJet_trilep_stacked->Add(h_nBJet_trilep);
        h_nBJet_SSdilep_stacked->Add(h_nBJet_SSdilep);
        h_nBJet_OSdilep_stacked->Add(h_nBJet_OSdilep);
        h_nBJet_onelepFO_stacked->Add(h_nBJet_onelepFO);
        h_nBJet_dilepFO_stacked->Add(h_nBJet_dilepFO);

        h_MET_trilep_stacked->Add(h_MET_trilep);
        h_MET_SSdilep_stacked->Add(h_MET_SSdilep);
        h_MET_OSdilep_stacked->Add(h_MET_OSdilep);
        h_MET_onelepFO_stacked->Add(h_MET_onelepFO);
        h_MET_dilepFO_stacked->Add(h_MET_dilepFO);

        h_minMT_trilep_stacked->Add(h_minMT_trilep);
        h_minMT_SSdilep_stacked->Add(h_minMT_SSdilep);
        h_minMT_OSdilep_stacked->Add(h_minMT_OSdilep);
        h_minMT_onelepFO_stacked->Add(h_minMT_onelepFO);
        h_minMT_dilepFO_stacked->Add(h_minMT_dilepFO);

        leg_nJet_trilep->AddEntry(h_nJet_trilep,sample_names[btype].c_str(), "f");
        leg_nJet_SSdilep->AddEntry(h_nJet_SSdilep,sample_names[btype].c_str(), "f");
        leg_nJet_OSdilep->AddEntry(h_nJet_OSdilep,sample_names[btype].c_str(), "f");
        leg_nJet_onelepFO->AddEntry(h_nJet_onelepFO,sample_names[btype].c_str(), "f");
        leg_nJet_dilepFO->AddEntry(h_nJet_dilepFO,sample_names[btype].c_str(), "f");

        leg_nBJet_trilep->AddEntry(h_nBJet_trilep,sample_names[btype].c_str(), "f");
        leg_nBJet_SSdilep->AddEntry(h_nBJet_SSdilep,sample_names[btype].c_str(), "f");
        leg_nBJet_OSdilep->AddEntry(h_nBJet_OSdilep,sample_names[btype].c_str(), "f");
        leg_nBJet_onelepFO->AddEntry(h_nBJet_onelepFO,sample_names[btype].c_str(), "f");
        leg_nBJet_dilepFO->AddEntry(h_nBJet_dilepFO,sample_names[btype].c_str(), "f");

        leg_MET_trilep->AddEntry(h_MET_trilep,sample_names[btype].c_str(), "f");
        leg_MET_SSdilep->AddEntry(h_MET_SSdilep,sample_names[btype].c_str(), "f");
        leg_MET_OSdilep->AddEntry(h_MET_OSdilep,sample_names[btype].c_str(), "f");
        leg_MET_onelepFO->AddEntry(h_MET_onelepFO,sample_names[btype].c_str(), "f");
        leg_MET_dilepFO->AddEntry(h_MET_dilepFO,sample_names[btype].c_str(), "f");

        leg_minMT_trilep->AddEntry(h_minMT_trilep,sample_names[btype].c_str(), "f");
        leg_minMT_SSdilep->AddEntry(h_minMT_SSdilep,sample_names[btype].c_str(), "f");
        leg_minMT_OSdilep->AddEntry(h_minMT_OSdilep,sample_names[btype].c_str(), "f");
        leg_minMT_onelepFO->AddEntry(h_minMT_onelepFO,sample_names[btype].c_str(), "f");
        leg_minMT_dilepFO->AddEntry(h_minMT_dilepFO,sample_names[btype].c_str(), "f");
    }

    //write histograms
    //string outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots/";
    string outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots_testing/"; //for testing only!!
    
    saveFig(h_nJet_trilep_stacked, leg_nJet_trilep, "h_nJet_trilep", outdir);
    saveFig(h_nJet_SSdilep_stacked, leg_nJet_SSdilep, "h_nJet_SSdilep", outdir);
    saveFig(h_nJet_OSdilep_stacked, leg_nJet_OSdilep, "h_nJet_OSdilep", outdir);
    saveFig(h_nJet_onelepFO_stacked, leg_nJet_onelepFO, "h_nJet_onelepFO", outdir);
    saveFig(h_nJet_dilepFO_stacked, leg_nJet_dilepFO, "h_nJet_dilepFO", outdir);

    saveFig(h_nBJet_trilep_stacked, leg_nBJet_trilep, "h_nBJet_trilep", outdir);
    saveFig(h_nBJet_SSdilep_stacked, leg_nBJet_SSdilep, "h_nBJet_SSdilep", outdir);
    saveFig(h_nBJet_OSdilep_stacked, leg_nBJet_OSdilep, "h_nBJet_OSdilep", outdir);
    saveFig(h_nBJet_onelepFO_stacked, leg_nBJet_onelepFO, "h_nBJet_onelepFO", outdir);
    saveFig(h_nBJet_dilepFO_stacked, leg_nBJet_dilepFO, "h_nBJet_dilepFO", outdir);
    
    saveFig(h_MET_trilep_stacked, leg_MET_trilep, "h_MET_trilep", outdir);
    saveFig(h_MET_SSdilep_stacked, leg_MET_SSdilep, "h_MET_SSdilep", outdir);
    saveFig(h_MET_OSdilep_stacked, leg_MET_OSdilep, "h_MET_OSdilep", outdir);
    saveFig(h_MET_onelepFO_stacked, leg_MET_onelepFO, "h_MET_onelepFO", outdir);
    saveFig(h_MET_dilepFO_stacked, leg_MET_dilepFO, "h_MET_dilepFO", outdir);

    saveFig(h_minMT_trilep_stacked, leg_minMT_trilep, "h_minMT_trilep", outdir);
    saveFig(h_minMT_SSdilep_stacked, leg_minMT_SSdilep, "h_minMT_SSdilep", outdir);
    saveFig(h_minMT_OSdilep_stacked, leg_minMT_OSdilep, "h_minMT_OSdilep", outdir);
    saveFig(h_minMT_onelepFO_stacked, leg_minMT_onelepFO, "h_minMT_onelepFO", outdir);
    saveFig(h_minMT_dilepFO_stacked, leg_minMT_dilepFO, "h_minMT_dilepFO", outdir);

    cout << "saved histograms!" << endl;

}
