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
#include "./helpers/histogrammingClass.h"


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
    //auto outFile = new TFile("plots/outputHistos_test.root", "recreate");//for testing only!!

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
        
        //make all histograms
        categoryHistogram trilep_2j_0b("trilep","2j","0b",sample_names[btype]);
        categoryHistogram trilep_2j_1b("trilep","2j","1b",sample_names[btype]);
        categoryHistogram trilep_2j_ge2b("trilep","2j","ge2b",sample_names[btype]);
        categoryHistogram trilep_3j_0b("trilep","3j","0b",sample_names[btype]);
        categoryHistogram trilep_3j_1b("trilep","3j","1b",sample_names[btype]);
        categoryHistogram trilep_3j_ge2b("trilep","3j","ge2b",sample_names[btype]);
        categoryHistogram trilep_ge4j_0b("trilep","ge4j","0b",sample_names[btype]);
        categoryHistogram trilep_ge4j_1b("trilep","ge4j","1b",sample_names[btype]);
        categoryHistogram trilep_ge4j_ge2b("trilep","ge4j","ge2b",sample_names[btype]);

        categoryHistogram SS_SF_dilep_2j_0b("SS_SF_dilep","2j","0b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_2j_1b("SS_SF_dilep","2j","1b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_2j_ge2b("SS_SF_dilep","2j","ge2b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_3j_0b("SS_SF_dilep","3j","0b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_3j_1b("SS_SF_dilep","3j","1b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_3j_ge2b("SS_SF_dilep","3j","ge2b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_ge4j_0b("SS_SF_dilep","ge4j","0b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_ge4j_1b("SS_SF_dilep","ge4j","1b",sample_names[btype]);
        categoryHistogram SS_SF_dilep_ge4j_ge2b("SS_SF_dilep","ge4j","ge2b",sample_names[btype]);

        categoryHistogram SS_OF_dilep_2j_0b("SS_OF_dilep","2j","0b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_2j_1b("SS_OF_dilep","2j","1b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_2j_ge2b("SS_OF_dilep","2j","ge2b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_3j_0b("SS_OF_dilep","3j","0b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_3j_1b("SS_OF_dilep","3j","1b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_3j_ge2b("SS_OF_dilep","3j","ge2b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_ge4j_0b("SS_OF_dilep","ge4j","0b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_ge4j_1b("SS_OF_dilep","ge4j","1b",sample_names[btype]);
        categoryHistogram SS_OF_dilep_ge4j_ge2b("SS_OF_dilep","ge4j","ge2b",sample_names[btype]);

        categoryHistogram OS_SF_dilep_2j_0b("OS_SF_dilep","2j","0b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_2j_1b("OS_SF_dilep","2j","1b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_2j_ge2b("OS_SF_dilep","2j","ge2b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_3j_0b("OS_SF_dilep","3j","0b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_3j_1b("OS_SF_dilep","3j","1b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_3j_ge2b("OS_SF_dilep","3j","ge2b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_ge4j_0b("OS_SF_dilep","ge4j","0b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_ge4j_1b("OS_SF_dilep","ge4j","1b",sample_names[btype]);
        categoryHistogram OS_SF_dilep_ge4j_ge2b("OS_SF_dilep","ge4j","ge2b",sample_names[btype]);

        categoryHistogram OS_OF_dilep_2j_0b("OS_OF_dilep","2j","0b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_2j_1b("OS_OF_dilep","2j","1b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_2j_ge2b("OS_OF_dilep","2j","ge2b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_3j_0b("OS_OF_dilep","3j","0b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_3j_1b("OS_OF_dilep","3j","1b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_3j_ge2b("OS_OF_dilep","3j","ge2b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_ge4j_0b("OS_OF_dilep","ge4j","0b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_ge4j_1b("OS_OF_dilep","ge4j","1b",sample_names[btype]);
        categoryHistogram OS_OF_dilep_ge4j_ge2b("OS_OF_dilep","ge4j","ge2b",sample_names[btype]);

        categoryHistogram onelepFO_2j_0b("onelepFO","2j","0b",sample_names[btype]);
        categoryHistogram onelepFO_2j_1b("onelepFO","2j","1b",sample_names[btype]);
        categoryHistogram onelepFO_2j_ge2b("onelepFO","2j","ge2b",sample_names[btype]);
        categoryHistogram onelepFO_3j_0b("onelepFO","3j","0b",sample_names[btype]);
        categoryHistogram onelepFO_3j_1b("onelepFO","3j","1b",sample_names[btype]);
        categoryHistogram onelepFO_3j_ge2b("onelepFO","3j","ge2b",sample_names[btype]);
        categoryHistogram onelepFO_ge4j_0b("onelepFO","ge4j","0b",sample_names[btype]);
        categoryHistogram onelepFO_ge4j_1b("onelepFO","ge4j","1b",sample_names[btype]);
        categoryHistogram onelepFO_ge4j_ge2b("onelepFO","ge4j","ge2b",sample_names[btype]);

        categoryHistogram dilepFO_2j_0b("dilepFO","2j","0b",sample_names[btype]);
        categoryHistogram dilepFO_2j_1b("dilepFO","2j","1b",sample_names[btype]);
        categoryHistogram dilepFO_2j_ge2b("dilepFO","2j","ge2b",sample_names[btype]);
        categoryHistogram dilepFO_3j_0b("dilepFO","3j","0b",sample_names[btype]);
        categoryHistogram dilepFO_3j_1b("dilepFO","3j","1b",sample_names[btype]);
        categoryHistogram dilepFO_3j_ge2b("dilepFO","3j","ge2b",sample_names[btype]);
        categoryHistogram dilepFO_ge4j_0b("dilepFO","ge4j","0b",sample_names[btype]);
        categoryHistogram dilepFO_ge4j_1b("dilepFO","ge4j","1b",sample_names[btype]);
        categoryHistogram dilepFO_ge4j_ge2b("dilepFO","ge4j","ge2b",sample_names[btype]);

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
        //for ( int counter = 0; counter < 10; counter++ ){ //for testing only!!
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
            float leadLep_pt = 0;
            float leadLep_eta = 0;
            float leadLep_miniIso = 0;
            float leadLep_ptRel = 0;
            float leadLep_ptRatio = 0;
            float leadJet_pt = 0;
            float leadB_pt = 0;

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
                    if( mu.pt[iMu]>leadLep_pt ){
                        leadLep_pt = mu.pt[iMu];
                        leadLep_eta = mu.eta[iMu];
                        leadLep_miniIso = mu.miniIso[iMu];
                        leadLep_ptRel = mu.jetPtRelv2[iMu];
                        leadLep_ptRatio = 1/(mu.jetRelIso[iMu] + 1);
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
                    if( el.pt[iEl]>leadLep_pt ){
                        leadLep_pt = el.pt[iEl];
                        leadLep_eta = el.eta[iEl];
                        leadLep_miniIso = el.miniIso[iEl];
                        leadLep_ptRel = el.jetPtRelv2[iEl];
                        leadLep_ptRatio = 1/(el.jetRelIso[iEl] + 1);
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
                                if(jet.pt[iJet]>leadB_pt){
                                    leadB_pt = jet.pt[iJet];
                                }
                            }else continue;
                            if (jet.pt[iJet]>leadJet_pt){
                                leadJet_pt=jet.pt[iJet];
                            }
                        }else continue;
                    }else continue;
                }

            }


            //organize into signature types
            vector<float> variablesForFilling;
            variablesForFilling.push_back(nJets);
            variablesForFilling.push_back(nBjets);
            variablesForFilling.push_back(nGoodLep);
            variablesForFilling.push_back(leadLep_pt);
            variablesForFilling.push_back(leadLep_eta);
            variablesForFilling.push_back(leadLep_miniIso);
            variablesForFilling.push_back(leadLep_ptRel);
            variablesForFilling.push_back(leadLep_ptRatio);
            variablesForFilling.push_back(leadJet_pt);
            variablesForFilling.push_back(leadB_pt);
            variablesForFilling.push_back(MET);
            if (nGoodLep >= 2){
                variablesForFilling.push_back(minMT_tight);
            }
            if (nGoodLep == 1 && nFakeableLep ==1){
                if (minMT_tight < minMT_loose){
                    variablesForFilling.push_back(minMT_tight);
                } else if (minMT_loose < minMT_tight){
                    variablesForFilling.push_back(minMT_loose);
                }
            }
            if (nFakeableLep==2){
                variablesForFilling.push_back(minMT_loose);
            }


            if (nJets==2){
                if (nBjets==0){
                    if (nGoodLep>=3){
                        trilep_2j_0b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_2j_0b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_2j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_2j_0b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_2j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_2j_0b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_2j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_2j_0b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_2j_0b.fillHistogram(variablesForFilling, weight);
                    }
                }else if (nBjets==1){
                    if (nGoodLep>=3){
                        trilep_2j_1b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_2j_1b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_2j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_2j_1b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_2j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_2j_1b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_2j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_2j_1b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_2j_1b.fillHistogram(variablesForFilling, weight);
                    }
                }else if (nBjets>=2){
                    if (nGoodLep>=3){
                        trilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_2j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_2j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_2j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                }
            }//njet==2
            if (nJets==3){
                if (nBjets==0){
                    if (nGoodLep>=3){
                        trilep_3j_0b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_3j_0b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_3j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_3j_0b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_3j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_3j_0b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_3j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_3j_0b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_3j_0b.fillHistogram(variablesForFilling, weight);
                    }
                }else if (nBjets==1){
                    if (nGoodLep>=3){
                        trilep_3j_1b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_3j_1b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_3j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_3j_1b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_3j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_3j_1b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_3j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_3j_1b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_3j_1b.fillHistogram(variablesForFilling, weight);
                    }
                }else if (nBjets>=2){
                    if (nGoodLep>=3){
                        trilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_3j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_3j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_3j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                }
            }//njet==3
            if (nJets>=4){
                if (nBjets==0){
                    if (nGoodLep>=3){
                        trilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_ge4j_0b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_ge4j_0b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_ge4j_0b.fillHistogram(variablesForFilling, weight);
                    }
                }else if (nBjets==1){
                    if (nGoodLep>=3){
                        trilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_ge4j_1b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_ge4j_1b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_ge4j_1b.fillHistogram(variablesForFilling, weight);
                    }
                }else if (nBjets>=2){
                    if (nGoodLep>=3){
                        trilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nGoodLep == 2){
                        if (muCharge_tight.size() == 2){
                            if (muCharge_tight[0]*muCharge_tight[1]>0){
                                SS_SF_dilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{ 
                                OS_SF_dilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (elCharge_tight.size() == 2) {
                            if (elCharge_tight[0]*elCharge_tight[1]>0){
                                SS_SF_dilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_SF_dilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }else if (muCharge_tight.size() == 1) {
                            if (muCharge_tight[0]*elCharge_tight[0]>0){
                                SS_OF_dilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                            }else{
                                OS_OF_dilep_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                    if (nGoodLep==1 && nFakeableLep==1){
                        onelepFO_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                    if (nFakeableLep==2){
                        dilepFO_ge4j_ge2b.fillHistogram(variablesForFilling, weight);
                    }
                }
            }//njets>=4
       }//event loop

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);

        /*cout << "TriLep: " << nTriLep << endl;
        cout << "SS DiLep: " << nSSDiLep << endl;
        cout << "OS DiLep: " << nOSDiLep << endl;
        cout << "One Lep with FO: " << nOneLepFO << endl;
        cout << "FO DiLep: " << nFODiLep << endl;*/
        //cout << "total filtered: " << (nTriLep+nSSDiLep+nOSDiLep) << endl;

        cout << "processed " << nEvents << " events in " << duration.count() << " seconds!!" << endl;


        trilep_2j_0b.writeHistogram(outFile);
        trilep_2j_1b.writeHistogram(outFile);
        trilep_2j_ge2b.writeHistogram(outFile);
        trilep_3j_0b.writeHistogram(outFile);
        trilep_3j_1b.writeHistogram(outFile);
        trilep_3j_ge2b.writeHistogram(outFile);
        trilep_ge4j_0b.writeHistogram(outFile);
        trilep_ge4j_1b.writeHistogram(outFile);
        trilep_ge4j_ge2b.writeHistogram(outFile);

        SS_SF_dilep_2j_0b.writeHistogram(outFile);
        SS_SF_dilep_2j_1b.writeHistogram(outFile);
        SS_SF_dilep_2j_ge2b.writeHistogram(outFile);
        SS_SF_dilep_3j_0b.writeHistogram(outFile);
        SS_SF_dilep_3j_1b.writeHistogram(outFile);
        SS_SF_dilep_3j_ge2b.writeHistogram(outFile);
        SS_SF_dilep_ge4j_0b.writeHistogram(outFile);
        SS_SF_dilep_ge4j_1b.writeHistogram(outFile);
        SS_SF_dilep_ge4j_ge2b.writeHistogram(outFile);

        SS_OF_dilep_2j_0b.writeHistogram(outFile);
        SS_OF_dilep_2j_1b.writeHistogram(outFile);
        SS_OF_dilep_2j_ge2b.writeHistogram(outFile);
        SS_OF_dilep_3j_0b.writeHistogram(outFile);
        SS_OF_dilep_3j_1b.writeHistogram(outFile);
        SS_OF_dilep_3j_ge2b.writeHistogram(outFile);
        SS_OF_dilep_ge4j_0b.writeHistogram(outFile);
        SS_OF_dilep_ge4j_1b.writeHistogram(outFile);
        SS_OF_dilep_ge4j_ge2b.writeHistogram(outFile);

        OS_SF_dilep_2j_0b.writeHistogram(outFile);
        OS_SF_dilep_2j_1b.writeHistogram(outFile);
        OS_SF_dilep_2j_ge2b.writeHistogram(outFile);
        OS_SF_dilep_3j_0b.writeHistogram(outFile);
        OS_SF_dilep_3j_1b.writeHistogram(outFile);
        OS_SF_dilep_3j_ge2b.writeHistogram(outFile);
        OS_SF_dilep_ge4j_0b.writeHistogram(outFile);
        OS_SF_dilep_ge4j_1b.writeHistogram(outFile);
        OS_SF_dilep_ge4j_ge2b.writeHistogram(outFile);

        OS_OF_dilep_2j_0b.writeHistogram(outFile);
        OS_OF_dilep_2j_1b.writeHistogram(outFile);
        OS_OF_dilep_2j_ge2b.writeHistogram(outFile);
        OS_OF_dilep_3j_0b.writeHistogram(outFile);
        OS_OF_dilep_3j_1b.writeHistogram(outFile);
        OS_OF_dilep_3j_ge2b.writeHistogram(outFile);
        OS_OF_dilep_ge4j_0b.writeHistogram(outFile);
        OS_OF_dilep_ge4j_1b.writeHistogram(outFile);
        OS_OF_dilep_ge4j_ge2b.writeHistogram(outFile);

        onelepFO_2j_0b.writeHistogram(outFile);
        onelepFO_2j_1b.writeHistogram(outFile);
        onelepFO_2j_ge2b.writeHistogram(outFile);
        onelepFO_3j_0b.writeHistogram(outFile);
        onelepFO_3j_1b.writeHistogram(outFile);
        onelepFO_3j_ge2b.writeHistogram(outFile);
        onelepFO_ge4j_0b.writeHistogram(outFile);
        onelepFO_ge4j_1b.writeHistogram(outFile);
        onelepFO_ge4j_ge2b.writeHistogram(outFile);

        dilepFO_2j_0b.writeHistogram(outFile);
        dilepFO_2j_1b.writeHistogram(outFile);
        dilepFO_2j_ge2b.writeHistogram(outFile);
        dilepFO_3j_0b.writeHistogram(outFile);
        dilepFO_3j_1b.writeHistogram(outFile);
        dilepFO_3j_ge2b.writeHistogram(outFile);
        dilepFO_ge4j_0b.writeHistogram(outFile);
        dilepFO_ge4j_1b.writeHistogram(outFile);
        dilepFO_ge4j_ge2b.writeHistogram(outFile);

    }

    //write histograms
    outFile->Close();

}
