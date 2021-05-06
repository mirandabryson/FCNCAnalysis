//duplicate of event_looper.C with edits to specifically run over frank's ttjets sample and to print event info

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

void franksTest(){
    //global variables
    int year = 2018;
    double lumi = 137;
    string babyVersion = "fcnc_v4";
    string inputDir = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/"+babyVersion+"/";
    /*vector< string > sample_names = {   "background", //for testing, removing background
                                        //"signal_hut",
                                        //"signal_hct"
                                    };*/
    vector< string > sample_names = {   "franksTest",
                                    };


    //auto outFile = new TFile("plots/outputHistos.root", "recreate");
    auto outFile = new TFile("plots/outputHistos_test.root", "recreate");//for testing only!!

    //Load samples
    for(uint btype = 0; btype < sample_names.size(); btype++){
    //for(uint btype = 0; btype < 2; btype++){ //for testing only!!!
        TChain* chain = new TChain("Events");
        vector<string> samples = loadSamples ( year, sample_names[btype],babyVersion );
        /*for ( uint s = 0; s < samples.size(); s++ ){
            string pathname = inputDir+samples[s];
            string name = inputDir+samples[s]+"/output_*.root";
            chain->Add(name.c_str());
        }*/
        //use this for loop for franksTest
        for ( uint s = 0; s < samples.size(); s++ ){
            string name = samples[s];
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
        uint run = 0;
        uint lumiBlock = 0;
        uint nMuon = 0;
        uint nElectron = 0;
        uint nJet = 0;
        uint nGenPart = 0;
        float MET = 0;
        float MET_phi = 0;
        float genWeight = 0;

        chain->SetBranchAddress("run", &run);
        chain->SetBranchAddress("luminosityBlock", &lumiBlock);
        chain->SetBranchAddress("nMuon", &nMuon);
        chain->SetBranchAddress("nElectron", &nElectron);
        chain->SetBranchAddress("nJet", &nJet);
        chain->SetBranchAddress("nGenPart", &nGenPart);
        chain->SetBranchAddress("MET_pt", &MET);
        chain->SetBranchAddress("MET_phi", &MET_phi);
        chain->SetBranchAddress("Generator_weight", &genWeight);
        
        //make all histograms
        makeHistograms histos(sample_names[btype]);
        makeSampleHistos sampleHistos(sample_names[btype]);
        cout << "defined histograms" << endl;
        
        auto start = high_resolution_clock::now();

        int processed = 0;
        int stitchCounter = 0;
        //Main for loop
        //for ( int counter = 0; counter < nEvents; counter++ ){
        //for ( int counter = 0; counter < 100000; counter++ ){ //for testing only!!
        //for ( int counter = 0; counter < 10000; counter++ ){ //for testing only!!
        //for ( int counter = 0; counter < 100; counter++ ){ //for testing only!!
        for ( int counter = 0; counter < 10; counter++ ){ //for testing only!!
            processed++;
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

            //Find the exact sample name
            TFile* sFile(chain->GetFile());
            string sName = sFile->GetName();
            if ( counter%10000==0 ){
                cout << sName << endl;
            }
            //get event weight based on sample!
            //for franksTest, comment out weighting, instead make weight 1
            double weight = 1;
            /*double weight = getEventWeight( sName, inputDir, babyVersion );
            cout << weight << endl;
            cout << genWeight << endl;
            cout << lumi << endl;
            weight = (weight*genWeight*lumi)/(abs(genWeight));
            cout << weight << endl;
            cout << "***************" << endl;*/

            //Define physics objects
            Muon mu(chain, nMuon, year);
            Electron el(chain, nElectron, year);
            Jet jet(chain, nJet, year);
            GenPart genParts(chain, nGenPart, year);

            bool isFlip = 0;
            bool isFake_mu = 0;
            bool isFake_el = 0;
            bool isFake = 0;
            bool isFake_loose = 0;
            bool isSMSS = 0;
            bool isSignal = 0;

            float fakeRateValue = 0;
            vector<float> fakeRates;
            float coneCorrPtValue = 0;
            float flipRateValue = 0;
            vector<float> flipRates;

            /*bool stitch = 1;
            int w_idx = sName.find("WJets");
            int t_idx = sName.find("TTJets");
            if ( w_idx!=-1 || t_idx!=-1 ){
                for ( uint i = 0; i<nGenPart; i++ ){
                    if (abs(genParts.pdgid[i])==22 && genParts.statusFlags[i]%2==1 && genParts.pt[i]>15 && abs(genParts.eta[i])<2.6){
                        stitch = 0;
                    }
                }
            }
            w_idx = sName.find("WG");
            t_idx = sName.find("TTG");
            if (w_idx!=-1 || t_idx!=-1){
                stitch = 0;
                for ( uint i = 0; i<nGenPart; i++ ){
                    if(abs(genParts.pdgid[i])==22 && genParts.statusFlags[i]%2==1 && genParts.pt[i]>15 && abs(genParts.eta[i])<2.6){
                        stitch = 1;
                    }
                }
            }
            if (stitch ==1){
            stitchCounter++;
            }*/
            //cout << stitch << endl;


            vector<vector<float>> lep_info;
            //loop to count tight/loose muons
            for( uint iMu = 0; iMu < nMuon; iMu++ ){
                vector<float> mu_vec;

                //check if meets basic object requirements
                bool mu_isGood = isGoodMuon( mu.dxy[iMu], mu.dz[iMu], mu.sip3d[iMu], mu.tightCharge[iMu], mu.mediumId[iMu], mu.chargeQuality[iMu] );
                int mu_isoType = isoType( year, mu.pdgid[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
                bool mu_isTight = isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType );
                bool mu_isLoose = isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType );
                mu_vec.push_back(mu.pdgid[iMu]);
                mu_vec.push_back(mu.pt[iMu]);
                mu_vec.push_back(mu.eta[iMu]);
                mu_vec.push_back(mu_isLoose);
                mu_vec.push_back(mu_isTight);
                lep_info.push_back(mu_vec);
                mu_vec.clear();
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
                            isFake_mu = 1;
                        }
                    }else{
                        isSignal = 1;
                    }
                    flipRateValue = GetFlipWeight(mu.pt[iMu],mu.eta[iMu],mu.pdgid[iMu]);
                    flipRates.push_back(flipRateValue);

                }else if ( isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
                    nFakeableLep += 1;
                    muCharge_loose.push_back(mu.charge[iMu]);

                    if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
                    }
                    MT_MET_lep = mt(MET, MET_phi, mu.pt[iMu], mu.phi[iMu]);


                    if( sample_names[btype]=="background" ){
                        if( mu.genPartFlav[iMu] != 1 && mu.genPartFlav[iMu] != 15 ){
                            isFake_loose = 1;
                        }
                    }

                    coneCorrPtValue = coneCorrPt(year, mu.pdgid[iMu], mu.pt[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
                    fakeRateValue = fakeRate(year, mu.pdgid[iMu], coneCorrPtValue, mu.eta[iMu]);
                    fakeRates.push_back(fakeRateValue);
                }else continue;
            }
            //loop to count tight/loose electrons
            for( uint iEl = 0; iEl < nElectron; iEl++ ){
                vector<float> el_vec;

                //check if meets basic object requirements
                bool el_isGood = isGoodElectron( el.dxy[iEl], el.dz[iEl], el.sip3d[iEl], el.tightCharge[iEl], el.lostHits[iEl], el.convVeto[iEl] );
                int el_isoType = isoType( year, el.pdgid[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
                bool el_isTight =  (isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) );
                bool el_isLoose = (isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) );
                el_vec.push_back(el.pdgid[iEl]);
                el_vec.push_back(el.pt[iEl]);
                el_vec.push_back(el.eta[iEl]);
                el_vec.push_back(el_isLoose);
                el_vec.push_back(el_isTight);
                lep_info.push_back(el_vec);
                el_vec.clear();
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
                            isFake_el = 1;
                        }else if( el.pdgid[iEl]*-1 == genParts.pdgid[el.genPartIdx[iEl]] ){
                            isFlip = 1;
                        }
                    }else{
                        isSignal = 1;
                    }
                    flipRateValue = GetFlipWeight(el.pt[iEl],el.eta[iEl],el.pdgid[iEl]);
                    flipRates.push_back(flipRateValue);
                }else if ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ){
                    nFakeableLep += 1;
                    elCharge_loose.push_back(el.charge[iEl]);

                    if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_loose ){
                        minMT_loose = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
                    }
                    MT_MET_lep = mt(MET, MET_phi, el.pt[iEl], el.phi[iEl]);


                    if( sample_names[btype]=="background" ){
                        if( el.genPartFlav[iEl] != 1 && el.genPartFlav[iEl] != 15 ){
                            isFake_loose = 1;
                        }
                    }

                    coneCorrPtValue = coneCorrPt(year, el.pdgid[iEl], el.pt[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
                    fakeRateValue = fakeRate(year, el.pdgid[iEl], coneCorrPtValue, el.eta[iEl]);
                    fakeRates.push_back(fakeRateValue);
                }else continue;
            }


            //background categorization 
            if( sample_names[btype]=="background" ){
                if (isFake_mu || isFake_el || isFake_loose){
                    //if we found a fake muon, electron, or loose lepton, then fake event
                    isFake = 1;
                }else if (!isFlip){
                    //isFlip is set only in electron loop, so if it's not a flip, then it has to be other
                    isSMSS = 1;
                }
            }


            int category = 0;
            if(isFake) category = 1;
            if(isFlip) category = 2;
            if(isSMSS) category = 3;

            //for franksTest, rm nlepton requirement here and replace with same but without if/else
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
/*            if ( !((nFakeableLep==0 && nGoodLep>1) || (nFakeableLep>0 && nGoodLep<2)) ){
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

            }*/


            //Lepton classification
            bool isTrilep = 0;
            bool isSS_SFdilep = 0;
            bool isSS_OFdilep = 0;
            bool isOS_SFdilep = 0;
            bool isOS_OFdilep = 0;
            bool isOneLepFO = 0;
            bool isDilepFO = 0;
            bool isSSFO = 0;
            float goodLepCh = 0;
            float fakeLepCh = 0;

            if (nGoodLep>=3){
                isTrilep = 1;
            }else if (nGoodLep == 2){
                if (muCharge_tight.size() == 2){
                    if (muCharge_tight[0]*muCharge_tight[1]>0){
                        isSS_SFdilep = 1;
                    }else{ 
                        isOS_SFdilep = 1;
                    }
                }else if (elCharge_tight.size() == 2) {
                    if (elCharge_tight[0]*elCharge_tight[1]>0){
                        isSS_SFdilep = 1;
                    }else{
                        isOS_SFdilep = 1;
                    }
                }else if (muCharge_tight.size() == 1) {
                    if (muCharge_tight[0]*elCharge_tight[0]>0){
                        isSS_OFdilep = 1;
                    }else{
                        isOS_OFdilep = 1;
                    }
                }
            }else if (nGoodLep==1 && nFakeableLep==1){
                if(muCharge_tight.size()==1){
                    goodLepCh = muCharge_tight[0];
                }else if (elCharge_tight.size()==1){
                    goodLepCh = elCharge_tight[0];
                }
                if(muCharge_loose.size()==1){
                    fakeLepCh = muCharge_loose[0];
                }else if (elCharge_loose.size()==1){
                    fakeLepCh = elCharge_loose[0];
                }
                if(goodLepCh*fakeLepCh>0){
                    isSSFO = 1;
                    isOneLepFO = 1;
                }
            }else if (nFakeableLep==2){
                if(muCharge_loose.size()==2){
                    if(muCharge_loose[0]*muCharge_loose[1]>0){
                        isSSFO = 1;
                    }
                }else if(elCharge_loose.size()==2){
                    if(elCharge_loose[0]*elCharge_loose[1]>0){
                        isSSFO = 1;
                    }
                }else{
                    if(elCharge_loose[0]*muCharge_loose[0]>0){
                        isSSFO = 1;
                    }
                }
                if (isSSFO){
                    isDilepFO = 1;
                }
            }


            //define a weight for CR events.
            //this will be applied to those events and fill the estimate histograms
            float crWeight = 0;
            //calculate fake rate weight
            if ((isOneLepFO||isDilepFO) && nJets > 1){
                float fakeWeight = 1;
                if (fakeRates.size() < 1){
                    fakeWeight = 0;
                }else{
                    for(uint f = 0; f < fakeRates.size(); f++){
                        fakeWeight = fakeWeight * (fakeRates[f]/(1-fakeRates[f]));
                    }
                }
                crWeight = weight*fakeWeight;
            }

            //calculate flip rate weight
            if ((isOS_OFdilep||isOS_SFdilep) && nJets > 1){
                float flipWeight = 0;
                for(uint f = 0; f < flipRates.size(); f++){
                    flipWeight = flipWeight + (flipRates[f]/(1-flipRates[f]));
                }
                crWeight = weight * flipWeight;
            }

            //hyp_type for franksTest
            int hyp_type = 0;
            //1 for mass resonance veto
            //2 for trilep
            //3 for 2tight, 1loose
            //4 for ss2l
            //5 for os2l
            //6 for 1tight, 1loose
            //7 for 2loose

            if (nGoodLep>=3){
                hyp_type = 2;
            }else if (nGoodLep == 2 && nFakeableLep ==1){
                hyp_type = 3;
            }else if (nGoodLep == 2 && nFakeableLep == 0){
                if (muCharge_tight.size() == 2){
                    if (muCharge_tight[0]*muCharge_tight[1]>0){
                        hyp_type = 4;
                    }else{ 
                        hyp_type = 5;
                    }
                }else if (elCharge_tight.size() == 2) {
                    if (elCharge_tight[0]*elCharge_tight[1]>0){
                        hyp_type = 4;
                    }else{
                        hyp_type = 5;
                    }
                }else if (muCharge_tight.size() == 1) {
                    if (muCharge_tight[0]*elCharge_tight[0]>0){
                        hyp_type = 4;
                    }else{
                        hyp_type = 5;
                    }
                }
            }else if (nGoodLep==1 && nFakeableLep==1){
                hyp_type = 6;
            }else if (nGoodLep == 0 && nFakeableLep==2){
                hyp_type = 7;
            }

            //print for franksTest
            cout << run << "," << lumiBlock << "," << event << "," << hyp_type << ",";
            for (uint i = 0; i < lep_info.size(); i++){
                cout << lep_info[i][0] << "," << lep_info[i][1] << "," << lep_info[i][2] << "," << lep_info[i][3] << "," << lep_info[i][4] << ",";
            }
            cout << nJets << "," << nBjets << "," << category << endl;
            
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
                histos.fill(variablesForFilling, weight, crWeight, nJets, nBjets, nGoodLep, nFakeableLep, muCharge_tight, elCharge_tight, isSSFO, isFake, isFlip, isSMSS, isSignal);
            }
            if(isTrilep||isSS_SFdilep||isSS_OFdilep){
                //cout << isFake << " " << isFlip << " " << isSMSS << " " << isSignal << endl;
                vector<int> sampleHistoVars = {isFake, isFlip, isSMSS, nGoodLep, nJets, nBjets};
                sampleHistos.fillHistos(sName,sampleHistoVars, weight);
            }
            

       }//event loop

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(stop - start);

        //cout << stitchCounter << endl;
        cout << "processed " << processed << " events in " << duration.count() << " seconds!!" << endl;

        histos.write(sample_names[btype], outFile);
        sampleHistos.writeHistos(outFile);
    }

    //write histograms
    outFile->Close();

}
