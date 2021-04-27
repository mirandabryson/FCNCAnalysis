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
#include "./helpers/fcnc_functions.h"
#include "./helpers/sampleLoader.h"
#include "./helpers/objectClasses.h"
#include "./helpers/weights.h"
#include "./helpers/histogrammingClass.h"
#include "./helpers/flip_weights.h"
#include "./helpers/fake_rates.h"


using namespace std;
using namespace std::chrono;

void event_looper(){
    //global variables
    int year = 2018;
    double lumi = 137;
    string babyVersion = "fcnc_v3";
    string inputDir = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/"+babyVersion+"/";
    vector< string > sample_names = {   "background", //for testing, removing background
                                        "signal_hut",
                                        "signal_hct"
                                    };


    //auto outFile = new TFile("plots/outputHistos.root", "recreate");
    auto outFile = new TFile("plots/outputHistos_test.root", "recreate");//for testing only!!

    //Load samples
    for(uint btype = 0; btype < sample_names.size(); btype++){
    //for(uint btype = 0; btype < 2; btype++){ //for testing only!!!
        TChain* chain = new TChain("Events");
        vector<string> samples = loadSamples ( year, sample_names[btype],babyVersion );
        for ( uint s = 0; s < samples.size(); s++ ){
            string pathname = inputDir+samples[s];
            string name = inputDir+samples[s]+"/output_*.root";
            chain->Add(name.c_str());
        }
        /*//check we've got all the output files
        TObjArray *fileElements = chain->GetListOfFiles();
        TIter next(fileElements);
        TChainElement *chEl = 0;
        while(( chEl=(TChainElement*)next())){
            TFile f(chEl->GetTitle());
            cout << f.GetName() << endl;
        }*/
        cout << "Loaded Samples!" << endl;

        int nEvents = chain->GetEntries();
        cout << "found " << nEvents << " " << sample_names[btype] << " events" << endl;

        //event variables
        uint nMuon = 0;
        uint nElectron = 0;
        uint nJet = 0;
        uint nGenPart = 0;
        float MET = 0;
        float MET_phi = 0;
        float genWeight = 0;

        chain->SetBranchAddress("nMuon", &nMuon);
        chain->SetBranchAddress("nElectron", &nElectron);
        chain->SetBranchAddress("nJet", &nJet);
        chain->SetBranchAddress("nGenPart", &nGenPart);
        chain->SetBranchAddress("MET_pt", &MET);
        chain->SetBranchAddress("MET_phi", &MET_phi);
        chain->SetBranchAddress("Generator_weight", &genWeight);
        
        //make all histograms
        makeHistograms histos(sample_names[btype]);
        cout << "defined histograms" << endl;
        
        auto start = high_resolution_clock::now();

        int nTriLep   = 0;
        int nSSDiLep  = 0;
        int nOSDiLep  = 0;
        int nOneLepFO = 0;
        int nFODiLep  = 0;

        //Main for loop
        //for ( int counter = 0; counter < nEvents; counter++ ){
        //for ( int counter = 0; counter < 100000; counter++ ){ //for testing only!!
        //for ( int counter = 0; counter < 10000; counter++ ){ //for testing only!!
        for ( int counter = 0; counter < 100; counter++ ){ //for testing only!!
        //for ( int counter = 0; counter < 10; counter++ ){ //for testing only!!
            //cout << "counter " << counter << endl;
            if ( counter%100000==0 ){
                cout << "event " << counter << endl;
            }

            //variables to hold information
            int nGoodLep = 0;
            int nFakeableLep = 0;
            int nLooseNotTight_mu = 0;
            int nTightNotLoose_mu = 0;
            int nLooseNotTight_el = 0;
            int nTightNotLoose_el = 0;
            int nJets = 0;
            int nBjets = 0;
            float minMT_tight = 10000;
            float minMT_loose = 10000;
            float MT_MET_lep = 0;
            float MT_leadb_MET = 10000;
            float leadLep_pt = 0;
            float leadLep_eta = 0;
            float leadLep_mass = 0;
            float leadLep_miniIso = 0;
            float leadLep_ptRel = 0;
            float leadLep_ptRatio = 0;
            float leadJet_pt = 0;
            float leadB_pt = 0;
            float leadB_mass = 0;
            float jetHT = 0; 

            vector<int> muCharge_tight;
            vector<int> elCharge_tight;
            vector<int> muCharge_loose;
            vector<int> elCharge_loose;
            
            //Get individual event
            Long64_t event = chain->GetEntry(counter);

            //check if event is fake or flip




            /*if(samples_names[btype]=="extraFlips" || samples_names[btype]=="extraFakes"){
                GenPart genParts(chain, nGenPart, year);
                int nGenLepsFromW = 0;
                for (int i = 0; i < nGenPart; i++){
                    if ( abs(genParts.pdgid[i]) == 11 || abs(genParts.pdgid[i]) == 13 ){
                        int motherIndex = genParts.motherIdx[i];
                        if( abs(genParts.pdgid[motherIndex])==24 ){
                            nGenLepsFromW++;
                        }
                    }
                }

                bool isFake = 0;
                bool isFlip = 0;
                if (nGenLepsFromW == 1){
                    isFake = 1;
                }else if (nGenLepsFromW > 1){
                    isFlip = 1;
                }
            }

            if (sample_names[btype]=="extraFlips" && isFlip==0){
                break;
            }
            if (sample_names[btype]=="extraFakes" && isFake==0){
                break;
            }*/

            //Find the exact sample name
            TFile* sFile(chain->GetFile());
            string sName = sFile->GetName();
            if ( counter%10000==0 ){
                cout << sName << endl;
            }
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
            GenPart genParts(chain, nGenPart, year);

            bool isFlip = 0;
            bool isFake = 0;
            bool isSMSS = 0;
            bool isSignal = 0;

            float fakeRateValue = 0;
            vector<float> fakeRates;
            float flipRateValue = 0;
            vector<float> flipRates;

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
                        leadLep_mass = mu.mass[iMu];
                        leadLep_miniIso = mu.miniIso[iMu];
                        leadLep_ptRel = mu.jetPtRelv2[iMu];
                        leadLep_ptRatio = 1/(mu.jetRelIso[iMu] + 1);
                    }
                    if( sample_names[btype]=="background" ){
                        if( mu.genPartFlav[iMu] != 1 && mu.genPartFlav[iMu] != 15 ){
                            isFake = 1;
                        }else if( mu.pdgid[iMu]*-1 == genParts.pdgid[mu.genPartIdx[iMu]] ){
                            isFlip = 1;
                            //cout << "Mu isFlip" << endl;
                        }else{
                            isSMSS = 1;
                            //cout << "Mu isOther" << endl;
                        }
                    }else{
                        isSignal =1;
                    }
                    if(!isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType )){
                        nTightNotLoose_mu++;
                    }
                }else if ( isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
                    nFakeableLep += 1;
                    muCharge_loose.push_back(mu.charge[iMu]);
                    if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
                    }
                    MT_MET_lep = mt(MET, MET_phi, mu.pt[iMu], mu.phi[iMu]);
                    if(!isTightLepton(mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType)){
                        nLooseNotTight_mu++;
                        fakeRateValue = fakeRate(year, mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu]);
                        fakeRates.push_back(fakeRateValue);
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
                        leadLep_mass = el.mass[iEl];
                        leadLep_miniIso = el.miniIso[iEl];
                        leadLep_ptRel = el.jetPtRelv2[iEl];
                        leadLep_ptRatio = 1/(el.jetRelIso[iEl] + 1);
                    }
                    if( sample_names[btype]=="background" ){
                        if( el.genPartFlav[iEl] != 1 && el.genPartFlav[iEl] != 15 ){
                            isFake = 1;
                        }else if( el.pdgid[iEl]*-1 == genParts.pdgid[el.genPartIdx[iEl]] ){
                            isFlip = 1;
                        }else{
                            isSMSS = 1;
                        }
                    }else{
                        isSignal = 1;
                    }
                    if(!(isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ))){
                        nTightNotLoose_el++;
                        flipRateValue = GetFlipWeight(el.pt[iEl],el.eta[iEl],el.pdgid[iEl]);
                        flipRates.push_back(flipRateValue);
                    }
                }else if ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ){
                    nFakeableLep += 1;
                    elCharge_loose.push_back(el.charge[iEl]);
                    if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
                    }
                    MT_MET_lep = mt(MET, MET_phi, el.pt[iEl], el.phi[iEl]);
                    if(!(( isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ))){
                        nLooseNotTight_el++;
                        fakeRateValue = fakeRate(year, el.pdgid[iEl], el.pt[iEl], el.eta[iEl]);
                        fakeRates.push_back(fakeRateValue);
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
                            if (jet.pt[iJet]>leadJet_pt){
                                leadJet_pt=jet.pt[iJet];
                            }
                            jetHT = jetHT + jet.pt[iJet];
                            if ( jet.btag_score[iJet] > 0.2770 ){
                                nBjets += 1;
                                if(jet.pt[iJet]>leadB_pt){
                                    leadB_pt = jet.pt[iJet];
                                    leadB_mass = jet.mass[iJet];
                                    MT_leadb_MET = mt( MET, MET_phi, jet.pt[iJet], jet.phi[iJet] );
                                }
                            }else continue;
                        }else continue;
                    }else continue;
                }

            }



            //apply fake rate to fake CR events
            cout << nGoodLep << endl;
            cout << nFakeableLep << endl;
            cout << nLooseNotTight_mu << endl;
            cout << nLooseNotTight_el << endl;
            cout << nTightNotLoose_el << endl;
            cout << nTightNotLoose_mu << endl;
            cout << "****************" << endl;

            if ((nLooseNotTight_mu+nLooseNotTight_el) > 0 && nJets > 1){
                for(uint f = 0; f < fakeRates.size(); f++){
                    //cout << "fake" << endl;
                    weight = weight * (fakeRates[f]/(1-fakeRates[f]));
                    //cout << weight << endl;
                }
            }
            int nLooseNotTight = nLooseNotTight_mu + nLooseNotTight_el;
            //apply flip rate to flip CR events
            if (nTightNotLoose_el > 0 && nJets > 1){
                float flipWeight = 0;
                for(uint f = 0; f < flipRates.size(); f++){
                    flipWeight = flipWeight + (flipRates[f]/(1-flipRates[f]));
                    //cout << weight << endl;
                }
                weight = weight * flipWeight;
            }


            
            //organize into signature types
            vector<float> variablesForFilling;
            variablesForFilling.push_back(nJets);
            variablesForFilling.push_back(nBjets);
            variablesForFilling.push_back(nGoodLep);
            variablesForFilling.push_back(leadLep_pt);
            variablesForFilling.push_back(leadLep_eta);
            variablesForFilling.push_back(leadLep_mass);
            variablesForFilling.push_back(leadLep_miniIso);
            variablesForFilling.push_back(leadLep_ptRel);
            variablesForFilling.push_back(leadLep_ptRatio);
            variablesForFilling.push_back(leadJet_pt);
            variablesForFilling.push_back(leadB_pt);
            variablesForFilling.push_back(leadB_mass);
            variablesForFilling.push_back(jetHT);
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
            variablesForFilling.push_back(MT_leadb_MET);

            //Now fill with those variables
            if (isFake||isFlip||isSMSS||isSignal){
                histos.fill(variablesForFilling, weight, nJets, nBjets, nGoodLep, nFakeableLep, nLooseNotTight, nTightNotLoose_el, muCharge_tight, elCharge_tight, isFake, isFlip, isSMSS, isSignal);
            }

       }//event loop

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);

        cout << "processed " << nEvents << " events in " << duration.count() << " seconds!!" << endl;

        histos.write(sample_names[btype], outFile);
    }

    //write histograms
    outFile->Close();

}
