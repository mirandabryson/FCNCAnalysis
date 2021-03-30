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
#include <TFile.h>
//#include <sampleClasses.h>
#include "./helpers/fcnc_functions.h"
#include "./helpers/sampleLoader.h"
#include "./helpers/objectClasses.h"


using namespace std;
using namespace std::chrono;

void event_looper(){
    //global variables
    int year = 2018;
    string inputDir = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v2/2018/";
    vector< string > sample_names = {   "fakes",
                                        "flips",
                                        "rareSM",
                                        "GluGlu",
                                        "signal"
                                    };

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

        chain->SetBranchAddress("nMuon", &nMuon);
        chain->SetBranchAddress("nElectron", &nElectron);
        chain->SetBranchAddress("nJet", &nJet);
        chain->SetBranchAddress("MET_pt", &MET);
        chain->SetBranchAddress("MET_phi", &MET_phi);


        //Define histograms
        auto h_nJet_trilep = new TH1F(("h_nJet_trilep_"+sample_names[btype]).c_str(),   "nJets", 7, -0.5, 6.5);
        auto h_nJet_SSdilep = new TH1F(("h_nJet_SSdilep_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_OSdilep = new TH1F(("h_nJet_OSdilep_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);
        auto h_nJet_onelepFO = new TH1F(("h_nJet_onelepFO_"+sample_names[btype]).c_str(), "nJets", 7, -0.5, 6.5);
        auto h_nJet_dilepFO = new TH1F(("h_nJet_dilepFO_"+sample_names[btype]).c_str(),  "nJets", 7, -0.5, 6.5);

        auto h_nBJet_trilep = new TH1F(("h_nBJet_trilep_"+sample_names[btype]).c_str(),   "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_SSdilep = new TH1F(("h_nBJet_SSdilep_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_OSdilep = new TH1F(("h_nBJet_OSdilep_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_onelepFO = new TH1F(("h_nBJet_onelepFO_"+sample_names[btype]).c_str(), "nb-tagged Jets", 4, -0.5, 3.5);
        auto h_nBJet_dilepFO = new TH1F(("h_nBJet_dilepFO_"+sample_names[btype]).c_str(),  "nb-tagged Jets", 4, -0.5, 3.5);

        auto h_MET_trilep = new TH1F(("h_MET_trilep_"+sample_names[btype]).c_str(),   "MET", 50, 0, 500);
        auto h_MET_SSdilep = new TH1F(("h_MET_SSdilep_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_OSdilep = new TH1F(("h_MET_OSdilep_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);
        auto h_MET_onelepFO = new TH1F(("h_MET_onelepFO_"+sample_names[btype]).c_str(), "MET", 50, 0, 500);
        auto h_MET_dilepFO = new TH1F(("h_MET_dilepFO_"+sample_names[btype]).c_str(),  "MET", 50, 0, 500);

        auto h_minMT_trilep = new TH1F(("h_minMT_trilep_"+sample_names[btype]).c_str(),   "minMT", 50, 0, 500);
        auto h_minMT_SSdilep = new TH1F(("h_minMT_SSdilep_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_OSdilep = new TH1F(("h_minMT_OSdilep_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);
        auto h_minMT_onelepFO = new TH1F(("h_minMT_onelepFO_"+sample_names[btype]).c_str(), "minMT", 50, 0, 500);
        auto h_minMT_dilepFO = new TH1F(("h_minMT_dilepFO_"+sample_names[btype]).c_str(),  "minMT", 50, 0, 500);

        cout << "defined histograms!" << endl;

        auto start = high_resolution_clock::now();

        int nTriLep   = 0;
        int nSSDiLep  = 0;
        int nOSDiLep  = 0;
        int nOneLepFO = 0;
        int nFODiLep  = 0;

        //Main for loop
        for ( int counter = 0; counter < nEvents; counter++ ){
        //for ( int counter = 0; counter < 10000; counter++ ){ //for testing only!!
        //for ( int counter = 0; counter < 100; counter++ ){ //for testing only!!
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

            //Define physics objects
            Muon mu(chain, nMuon, year);
            Electron el(chain, nElectron, year);
            Jet jet(chain, nJet, year);

            //loop to count tight/loose muons
            for( uint iMu = 0; iMu < nMuon; iMu++ ){
                if ( isTightLepton( 13, mu.pt[iMu], mu.eta[iMu], mu.iso[iMu], mu.tightId[iMu] ) ){
                    nGoodLep += 1;
                    muCharge_tight.push_back(mu.charge[iMu]);
                    if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_tight ){
                        minMT_tight = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
                    }
                }else if ( isLooseLepton( 13, mu.pt[iMu], mu.eta[iMu], mu.iso[iMu], mu.looseId[iMu] ) ){
                    nFakeableLep += 1;
                    muCharge_loose.push_back(mu.charge[iMu]);
                    if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
                    }
                }else continue;
            }
            //loop to count tight/loose electrons
            for( uint iEl = 0; iEl < nElectron; iEl++ ){
                if ( isTightLepton( 11, el.pt[iEl], el.eta[iEl], el.iso[iEl], 0 ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ){
                    nGoodLep += 1;
                    elCharge_tight.push_back(el.charge[iEl]);
                    if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_tight ){
                        minMT_tight = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
                    }
                }else if ( isLooseLepton( 11, el.pt[iEl], el.eta[iEl], el.iso[iEl], 0 ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ){
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
                            if ( isTightLepton( 13, mu.pt[iMu], mu.eta[iMu], mu.iso[iMu], mu.tightId[iMu] ) || isLooseLepton( 13, mu.pt[iMu], mu.eta[iMu], mu.iso[iMu], mu.looseId[iMu] ) ){
                                if ( deltaR( jet.eta[iJet], jet.phi[iJet], mu.eta[iMu], mu.phi[iMu] ) < 0.4 ){
                                    isGood = 0;
                                }else continue;
                            }else continue;
                        }
                        for (uint iEl = 0; iEl < nElectron; iEl++ ){
                            if ( ( isTightLepton( 11, el.pt[iEl], el.eta[iEl], el.iso[iEl], 0 ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ) || ( isLooseLepton( 11, el.pt[iEl], el.eta[iEl], el.iso[iEl], 0 ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ) ){
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

            if ( nJets>1 && nBjets>=0 ){


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


            }

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


        h_nJet_trilep->Write();
        h_nJet_SSdilep->Write();
        h_nJet_OSdilep->Write();
        h_nJet_onelepFO->Write();
        h_nJet_dilepFO->Write();

        h_nBJet_trilep->Write();
        h_nBJet_SSdilep->Write();
        h_nBJet_OSdilep->Write();
        h_nBJet_onelepFO->Write();
        h_nBJet_dilepFO->Write();

        h_MET_trilep->Write();
        h_MET_SSdilep->Write();
        h_MET_OSdilep->Write();
        h_MET_onelepFO->Write();
        h_MET_dilepFO->Write();

        h_minMT_trilep->Write();
        h_minMT_SSdilep->Write();
        h_minMT_OSdilep->Write();
        h_minMT_onelepFO->Write();
        h_minMT_dilepFO->Write();

    }

    //write histograms
    outFile->Close();

}
