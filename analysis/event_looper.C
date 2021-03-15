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
    /*    for muon in range(event.nMuon):
            if isTightLepton(event, 13, muon) or isLooseLepton(event, 13, muon):
                #deltaR = deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Muon_eta[muon], event.Muon_phi[muon] )
                if deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Muon_eta[muon], event.Muon_phi[muon] ) < 0.4:
                    return False
                #if deltaR < 0.4:
                #    return False
                else: continue
            else: continue
        for electron in range(event.nElectron):
            if isTightLepton(event, 11, electron) or isLooseLepton(event, 11, electron):
                #deltaR = deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Electron_eta[electron], event.Electron_phi[electron] )
                if deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Electron_eta[electron], event.Electron_phi[electron] ) < 0.4:
                    return False
                #if deltaR < 0.4:
                    #return False
                else: continue
            else: continue
        */
        isGood = 1;
    }else{
        isGood = 0;
    }
    return isGood;
}

void event_looper()
{

    //Load samples
    TChain chain("Events");
    chain.Add("/home/users/ksalyer/SSValBabies/nano/ttbar_semileptonic_RunIISummer16NanoAODv7_0.root");

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
    //cout << "defined histograms!" << endl;

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
        if ( counter%10000==0 ){
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
            float btag_score = chain.GetLeaf("Jet_btagDeepFlavB")->GetValue(jet);

            if ( isGoodJet(jet_pt, jet_eta) ){
                nJets += 1;
                if ( btag_score > 0.2770 ){
                    nBjets += 1;
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
            //h_nJet_trilep.Fill(nJets)
            //h_nBJet_trilep.Fill(nBjets)
        }
        if ( nGoodLep == 2 ){
            if (muCharge_tight.size() == 2){
                if (muCharge_tight[0]*muCharge_tight[1]>0){
                    nSSDiLep += 1;
                    //h_nJet_SSdilep.Fill(nJets)
                    //h_nBJet_SSdilep.Fill(nBjets)
                }else{ 
                    nOSDiLep += 1;
                    //h_nJet_OSdilep.Fill(nJets)
                    //h_nBJet_OSdilep.Fill(nBjets)
                }
            }else if (elCharge_tight.size() == 2) {
                if (elCharge_tight[0]*elCharge_tight[1]>0){
                    nSSDiLep += 1;
                    //h_nJet_SSdilep.Fill(nJets)
                    //h_nBJet_SSdilep.Fill(nBjets)
                }else{
                    nOSDiLep += 1;
                    //h_nJet_OSdilep.Fill(nJets)
                    //h_nBJet_OSdilep.Fill(nBjets)
                }
            }else if (muCharge_tight.size() == 1) {
                if (muCharge_tight[0]*elCharge_tight[0]>0){
                    nSSDiLep += 1;
                    //h_nJet_SSdilep.Fill(nJets)
                    //h_nBJet_SSdilep.Fill(nBjets)
                }else{
                    nOSDiLep += 1;
                    //h_nJet_OSdilep.Fill(nJets)
                    //h_nBJet_OSdilep.Fill(nBjets)
                }
            }
        }//if nGoodLep == 2
        if (nGoodLep == 1 and nFakeableLep == 1){
            nOneLepFO += 1;
            //h_nJet_onelepFO.Fill(nJets)
            //h_nBJet_onelepFO.Fill(nBjets)
        }
        if (nFakeableLep == 2){
            nFODiLep += 1;
            //h_nJet_dilepFO.Fill(nJets)
            //h_nBJet_dilepFO.Fill(nBjets)
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


}
