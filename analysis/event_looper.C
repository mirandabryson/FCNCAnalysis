//Basic looper to categorize FCNC events
//Compile and run with root -l event_looper.C+
//March 2021
//Kaitlin Salyer

#include <iostream>
//#include <cmath>
#include <cstdlib>
#include <chrono>
#include <TChain.h>


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
    vector<float> mu_pt;
    vector<float> *mu_eta = 0;
    vector<float> *mu_iso = 0;
    vector<bool> *mu_tightId = 0;

    chain.SetBranchAddress("nMuon", &nMuon);
    chain.SetBranchAddress("nElectron", &nElectron);
    chain.SetBranchAddress("Muon_pt", &mu_pt);
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
    //for ( int counter = 0; counter < nEvents; counter++ ){
    for ( int counter = 0; counter < 100; counter++ ){
        cout << "counter " << counter << endl;
        if ( counter%10000==0 ){
            cout << "event " << counter << endl;
        }

        Long64_t event = chain.GetEntry(counter);
        int nGoodLep = 0;
        int nFakeableLep = 0;
        int nJets = 0;
        int nBjets = 0;

        vector<int> muIdx_tight;
        vector<int> elIdx_tight;
        vector<int> muIdx_loose;
        vector<int> elIdx_loose;

        cout << "nMuon: " << nMuon << endl;
        cout << "nElectron: " << nElectron << endl;
        if(nMuon>0){
            cout << "Muon pT: " << mu_pt[0] << endl;
        }
        /*for( uint mu = 0; mu < mu_pt->size(); mu++ ){
            cout << (*mu_pt)[mu] << endl;
            
            if ( isTightLepton( 13, (*mu_pt)[mu], (*mu_eta)[mu], (*mu_iso)[mu], (*mu_tightId)[mu] ) ){
                nGoodLep += 1;
                muIdx_tight.push_back(mu);
            }*//*elif isLooseLepton(event, 13, mu):
                nFakeableLep += 1
                muIdx_loose.append(mu)
            else: continue*/
        //}

    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(stop - start);

    cout << "processed " << nEvents << " events in " << duration.count() << " minutes!!" << endl;


}
