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
//#include "./helpers/objectClasses.h"
#include "./helpers/weights.h"
#include "./helpers/histogrammingClass.h"
#include "./helpers/flip_weights.h"
#include "./helpers/fake_rates.h"
#include "../../NanoTools/NanoCORE/MCTools.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"
#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/Config.h"



using namespace std;
using namespace std::chrono;

void franksTest(){
    //global variables
    bool debug = 0;
    int year = 2018;
    double lumi = 137;
    vector< string > sample_names = {   "background", //for testing, removing background
                                        "signal_hut",
                                        "signal_hct",
                                        //"data"
                                    };
    string babyVersion_MC = "fcnc_v6_SRonly_5may2021";
    string babyVersion_data = "fcnc_v5_SRandCR_5may2021";
    string inputDir_MC = "/nfs-7/userdata/ksalyer/fcnc/"+babyVersion_MC+"/"+to_string(year)+"/";
    string inputDir_data = "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/"+babyVersion_data+"/";


    string outdir = "debug/may26/"+to_string(year)+"/";

    //Load samples
    for(uint btype = 0; btype < sample_names.size(); btype++){
    //for(uint btype = 0; btype < 2; btype++){ //for testing only!!!
        string babyVersion;
        string inputDir;
        if (sample_names[btype]=="data"){
            babyVersion = babyVersion_data;
            inputDir = inputDir_data;
        }else{
            babyVersion = babyVersion_MC;
            inputDir = inputDir_MC;
        }
        TChain* chain = new TChain("Events");
        vector<string> samples = loadSamples ( year, sample_names[btype],babyVersion );
        for ( uint s = 0; s < samples.size(); s++ ){
            string name = inputDir+samples[s];
            chain->Add(name.c_str());
        }
        cout << "Loaded Samples into chain" << endl;
        /*//check we've got all the output files
        TObjArray *fileElements = chain->GetListOfFiles();
        TIter next(fileElements);
        TChainElement *chEl = 0;
        while(( chEl=(TChainElement*)next())){
            TFile f(chEl->GetTitle());
            cout << f.GetName() << endl;
        }*/
        //loop through files in chain
        TObjArray *files = chain->GetListOfFiles();
        TIter fileIter(files);
        TFile *currentFile = 0;

        while( (currentFile = (TFile*)fileIter.Next()) ){
            TFile *file = new TFile(currentFile->GetTitle());
            string sName = currentFile->GetTitle();
            TTree *tree = (TTree*)file->Get("Events");
            nt.Init(tree);

            int nEvents = tree->GetEntriesFast();
            cout << "found " << nEvents << " " << sName << " events" << endl;
            
            auto start = high_resolution_clock::now();

            int processed = 0;
            int stitchCounter = 0;

            //make output file
            string outfileName = sName;
            outfileName = outfileName.replace(0,inputDir_MC.length(),"");
            outfileName = outfileName.replace(outfileName.length()-5,5,"");
            outfileName = outdir+outfileName+".log";
            ofstream outfile;
            outfile.open(outfileName);

            //Main for loop
            //for ( int counter = 0; counter < nEvents; counter++ ){
            //for ( int counter = 0; counter < 100000; counter++ ){ //for testing only!!
            //for ( int counter = 0; counter < 300000; counter++ ){ //for testing only!!
            for ( int counter = 0; counter < 1000; counter++ ){ //for testing only!!
            //for ( int counter = 0; counter < 100; counter++ ){ //for testing only!!
            //for ( int counter = 0; counter < 10; counter++ ){ //for testing only!!
                processed++;
                //cout << "counter " << counter << endl;
                if ( counter%100000==0 ){
                    cout << "event " << counter << endl;
                }
                
                //Get individual event
                nt.GetEntry(counter);
                ULong64_t eventNum = nt.event();
                if(debug){
                    cout << eventNum << endl;
                }
                uint run = nt.run();
                uint lumiBlock = nt.luminosityBlock();
                float genWeight = nt.Generator_weight();

                //get event weight based on sample!
                double weight = getEventWeight( sName, inputDir, babyVersion, year );
                //cout << "got weight" << endl;
                /*cout << weight << endl;
                cout << genWeight << endl;
                cout << lumi << endl;*/
                weight = (weight*genWeight*lumi)/(abs(genWeight));
                weight = 1;
                /*cout << weight << endl;
                cout << "***************" << endl;*/

                //Define physics objects
                Leptons leptons = getLeptons();
                Leptons tightLeptons;
                Leptons looseLeptons;
                Genparts genparts = getGenparts();
                float MET = nt.MET_pt();

                int nTight = 0;
                int nLoose = 0;
                vector<float> tightCharges;
                vector<float> looseCharges;
                vector<float> looseNotTightCharges;

                bool isFake = 0;
                bool isFlip = 0;
                bool isSMSS = 0;
                bool isSMOS = 0;
                bool isSignal = 0;
                bool isData = 0;

                float fakeRateValue = 0;
                vector<float> fakeRates;
                float coneCorrPtValue = 0;
                float flipRateValue = 0;
                vector<float> flipRates;

                //sample overlap removal
                bool stitch = 1;
                int w_idx = sName.find("wjets");
                int z_idx = sName.find("dyjets");
                int t_idx = sName.find("ttjets");
                if ( w_idx!=-1 || z_idx!=-1){
                    for (auto part : genparts){
                        if (abs(part.id())==22 && part.statusflags()%2==1 && part.pt()>15 && abs(part.eta())<2.6){
                            stitch = 0;
                        }
                    }
                }else if ( t_idx!=-1 ){
                    for ( auto part : genparts ){
                        if (abs(part.id())==22 && part.statusflags()%2==1 && part.pt()>10 && abs(part.eta())<5.0){
                            stitch = 0;
                        }
                    }
                }
                w_idx = sName.find("wg");
                z_idx = sName.find("zg");
                t_idx = sName.find("ttg");
                if (w_idx!=-1 || z_idx!=-1){
                    stitch = 0;
                    for ( auto part : genparts ){
                        if(abs(part.id())==22 && part.statusflags()%2==1 && part.pt()>15 && abs(part.eta())<2.6){
                            stitch = 1;
                        }
                    }
                }else if ( t_idx!=-1 ){
                    for ( auto part : genparts ){
                        if (abs(part.id())==22 && part.statusflags()%2==1 && part.pt()>10 && abs(part.eta())<5.0){
                            stitch = 1;
                        }
                    }
                }

                //for debugging purposes, set stitch =1
                stitch = 1;

                if (stitch != 1){ continue; }

                if(debug){
                    cout << "did overlap removal" << endl;
                }



                //categorizing leptons as tight or loose
                vector< vector< float > > lepton_info;
                for(auto lep:leptons){
                    if( (lep.absid()==13&&lep.pt()>20&&abs(lep.eta())<2.4)||(lep.absid()==11&&lep.pt()>25&&abs(lep.eta())<2.4) ){
                        if(lep.idlevel()==SS::IDtight){
                            tightLeptons.push_back(lep);
                            tightCharges.push_back(lep.charge());
                        }
                        if(lep.idlevel()==SS::IDfakable) looseNotTightCharges.push_back(lep.charge());
                        if(lep.idlevel()==SS::IDfakable||lep.idlevel()==SS::IDtight){
                            vector<float> leptonVals;
                            leptonVals.push_back(lep.id());
                            leptonVals.push_back(lep.pt());
                            leptonVals.push_back(lep.eta());
                            leptonVals.push_back(lep.idlevel()==SS::IDfakable||lep.idlevel()==SS::IDtight);
                            leptonVals.push_back(lep.idlevel()==SS::IDtight);
                            leptonVals.push_back(lep.genPartFlav());
                            leptonVals.push_back(lep.isFake());
                            leptonVals.push_back(lep.isFlip());
                            lepton_info.push_back(leptonVals);
                            leptonVals.clear();
                            looseLeptons.push_back(lep);
                            looseCharges.push_back(lep.charge());
                            if(sample_names[btype]=="background"){
                                if (lep.isFake()==1){
                                    isFake =1;
                                }else if(lep.absid()==11 && lep.isFlip()==1){
                                    isFlip = lep.isFlip();
                                }
                            }
                        }
                    }
                }

                nTight = tightLeptons.size();
                nLoose = looseLeptons.size();


                //background categorization
                if(sample_names[btype]=="background"){
                    if(!(isFake||isFlip)){
                        if (looseCharges.size()==2 && (looseCharges[0]*looseCharges[1]<0)){
                            isSMOS=1;
                            isSMSS=0;
                        }else{
                            isSMSS=1;
                            isSMOS=0;
                        }
                    }
                }else if(sample_names[btype]=="signal_hct"||sample_names[btype]=="signal_hut"){
                    isSignal = 1;
                }else{
                    isData = 1;
                }
                int category = 0;
                if(isFake) category = 1;
                if(isFlip) category = 2;
                if(isSMSS) category = 3;
                if(isSMOS) category = 4;



                int nLooseNotTight = nLoose-nTight;
                bool tightLooseSS = 0;
                bool looseLooseSS = 0;
                if(nTight==1 && nLooseNotTight >= 2){
                    if (looseNotTightCharges[0]*looseNotTightCharges[1]>0) looseLooseSS = 1;
                    else{
                        for (int i = 0; i<nLooseNotTight; i++){
                            if(tightCharges[0]*looseNotTightCharges[i]>0){tightLooseSS = 1;}
                        }
                    } 
                }


                std::tuple<int, int, float> Jets = getCleanJetInfo(looseLeptons);
                int nJets = get<0>(Jets);
                int nBjets = get<1>(Jets);


                //hyp_type for franksTest
                int hyp_type = 0;
                //1 for mass resonance
                //2 for trilep
                //3 for 2tight, 1loose
                //4 for ss2l
                //5 for os2l
                //6 for 1tight, 1loose
                //7 for 2loose
                //8 for tll
                //9 for lll
                std::pair<int, int> z_result = {-1, -1};
                std::pair<int, int> gammastar_result = {-1, -1};
                bool extraZ = 0;
                bool extraGammaStar = 0;
                bool lowMassRes = 0;
                if (nTight>1 && !(nTight==2&&nLoose==3)){
                    for (int i = 0; i<nTight; i++){
                        for (int j = i+1; j<nTight; j++){
                            auto z_result = makesResonance(looseLeptons,tightLeptons[i], tightLeptons[j], 91., 15.);
                            auto gammastar_result = makesResonance(looseLeptons,tightLeptons[i], tightLeptons[j], 0., 12.);
                            if (tightLeptons[i].charge()==tightLeptons[j].charge() && z_result.first>=0){extraZ=1;}
                            if (tightLeptons[i].charge()==tightLeptons[j].charge() && gammastar_result.first>=0){extraGammaStar=1;}
                            if (tightLeptons[i].absid()==11 && 
                                tightLeptons[i].id()==tightLeptons[j].id() && 
                                (tightLeptons[i].p4()+tightLeptons[j].p4()).M()<12.){lowMassRes = 1;}
                            if (tightLeptons[i].id() == -tightLeptons[j].id() &&
                                (tightLeptons[i].p4()+tightLeptons[j].p4()).M()<12.){lowMassRes = 1;}

                            if (nt.event() == 356199504 || nt.event() == 333032626 || nt.event() == 400671596){
                                cout << nt.event() << endl;
                                cout << z_result.first << " " << z_result.second << " " << extraZ << endl;
                                cout << gammastar_result.first << " " << gammastar_result.second << " " << extraGammaStar << endl;
                                cout << lowMassRes << endl;
                                cout << (tightLeptons[i].p4()+tightLeptons[j].p4()).M() << endl;
                                cout << tightLeptons[i].id() << " " << tightLeptons[i].pt() << " " << tightLeptons[i].eta() << endl;
                                cout << tightLeptons[j].id() << " " << tightLeptons[j].pt() << " " << tightLeptons[j].eta() << endl;
                            }
                        }
                    }
                }else{
                    for (int i = 0; i<nLoose; i++){
                        for (int j = i+1; j<nLoose; j++){
                            auto z_result = makesResonance(looseLeptons,looseLeptons[i], looseLeptons[j], 91., 15.);
                            auto gammastar_result = makesResonance(looseLeptons,looseLeptons[i], looseLeptons[j], 0., 12.);
                            if (looseLeptons[i].charge()==looseLeptons[j].charge() && z_result.first>=0){extraZ=1;}
                            if (looseLeptons[i].charge()==looseLeptons[j].charge() && gammastar_result.first>=0){extraGammaStar=1;}
                            if (looseLeptons[i].absid()==11 && 
                                looseLeptons[i].id()==looseLeptons[j].id() && 
                                (looseLeptons[i].p4()+looseLeptons[j].p4()).M()<12.){lowMassRes = 1;}
                            if (looseLeptons[i].id() == -looseLeptons[j].id() &&
                                (looseLeptons[i].p4()+looseLeptons[j].p4()).M()<12.){lowMassRes = 1;}

                            if (nt.event() == 356199504 || nt.event() == 333032626 || nt.event() == 400671596){
                                cout << nt.event() << endl;
                                cout << z_result.first << " " << z_result.second << " " << extraZ << endl;
                                cout << gammastar_result.first << " " << gammastar_result.second << " " << extraGammaStar << endl;
                                cout << lowMassRes << endl;
                                cout << (looseLeptons[i].p4()+looseLeptons[j].p4()).M() << endl;
                                cout << looseLeptons[i].id() << " " << looseLeptons[i].pt() << " " << looseLeptons[i].eta() << endl;
                                cout << looseLeptons[j].id() << " " << looseLeptons[j].pt() << " " << looseLeptons[j].eta() << endl;
                            }
                        }
                    }
                }

                if (lowMassRes){hyp_type = 0;}
                else if (extraZ||extraGammaStar){hyp_type=1;}
                else{
                    if (nTight>=3){hyp_type = 2;}
                    else if (nTight == 2 && nLoose >=3){hyp_type = 3;}
                    else if (nTight == 2 && nLoose == 2){
                        if (tightCharges[0]*tightCharges[1]>0){
                            hyp_type = 4;
                        }else{ 
                            hyp_type = 5;
                        }
                    }else if ((nTight==1 && nLoose==2 && tightCharges[0]*looseNotTightCharges[0]>0)  ){hyp_type = 6;}
                    else if (nLooseNotTight==2 && (looseNotTightCharges[0]*looseNotTightCharges[1]>0||tightLooseSS)){
                        if( nLoose==2 ){hyp_type = 7;}
                        else if( nLoose==3 && nTight==1 ){hyp_type = 8;}
                    }else if (nLooseNotTight>=3 && (looseNotTightCharges[0]*looseNotTightCharges[1]>0||looseNotTightCharges[0]*looseNotTightCharges[2]>0||looseNotTightCharges[1]*looseNotTightCharges[2]>0)){
                        if( nLoose==3 && nTight==0 ){hyp_type = 9;}
                    }
                }

                //for category debugging:
                if(nt.event() == 356199504 || nt.event() == 333032626 || nt.event() == 400671596){
                    cout << run << "," << lumiBlock << "," << eventNum << "," << category << "," << nLoose << "," << nTight << "," << hyp_type << "," << nJets << "," << nBjets <<endl;
                    for(uint i = 0; i<lepton_info.size(); i++){
                        cout << "     ";
                        for(uint j = 0; j<lepton_info[i].size();j++){
                            cout << lepton_info[i][j] << " ";
                        }
                        cout << endl;
                    }
                }
                //for nloose debugging:
                //if(eventNum==164860112||eventNum==339311788||eventNum==199821521){
                

                if (hyp_type>0){
                    //cout << run << ", " << lumiBlock << ", " << eventNum << ", " << category << ", " << nLoose << ", " << nTight << ", " << hyp_type << ", " << nJets << ", " << nBjets <<endl;
                    outfile << run << "," << lumiBlock << "," << eventNum << "," << category << "," << nLoose << "," << nTight << "," << hyp_type << "," << nJets << "," << nBjets <<endl;


                    /*for(uint i = 0; i<lepton_info.size(); i++){
                        cout << "     ";
                        for(uint j = 0; j<lepton_info[i].size();j++){
                            cout << lepton_info[i][j] << " ";
                        }
                        cout << endl;
                    }*/
                }
            }
            outfile.close();
        }//close while loop
    }//close chain loop
}


//             Muon mu(chain, nMuon, year);
//             Electron el(chain, nElectron, year);
//             Jet jet(chain, nJet, year);
//             GenPart genParts(chain, nGenPart, year);

//             bool isFlip = 0;
//             bool isFake_mu = 0;
//             bool isFake_el = 0;
//             bool isFake = 0;
//             bool isFake_loose = 0;
//             bool isSMSS = 0;
//             bool isSignal = 0;

//             float fakeRateValue = 0;
//             vector<float> fakeRates;
//             float coneCorrPtValue = 0;
//             float flipRateValue = 0;
//             vector<float> flipRates;

//             /*bool stitch = 1;
//             int w_idx = sName.find("WJets");
//             int t_idx = sName.find("TTJets");
//             if ( w_idx!=-1 || t_idx!=-1 ){
//                 for ( uint i = 0; i<nGenPart; i++ ){
//                     if (abs(genParts.pdgid[i])==22 && genParts.statusFlags[i]%2==1 && genParts.pt[i]>15 && abs(genParts.eta[i])<2.6){
//                         stitch = 0;
//                     }
//                 }
//             }
//             w_idx = sName.find("WG");
//             t_idx = sName.find("TTG");
//             if (w_idx!=-1 || t_idx!=-1){
//                 stitch = 0;
//                 for ( uint i = 0; i<nGenPart; i++ ){
//                     if(abs(genParts.pdgid[i])==22 && genParts.statusFlags[i]%2==1 && genParts.pt[i]>15 && abs(genParts.eta[i])<2.6){
//                         stitch = 1;
//                     }
//                 }
//             }
//             if (stitch ==1){
//             stitchCounter++;
//             }*/
//             //cout << stitch << endl;

//             if(eventNum==8033721||eventNum==8034006||eventNum==23264557||eventNum==23265140||eventNum==23307768||eventNum==23307962||eventNum==23308060){
//                 cout << "found missing event " << eventNum << endl;
//             }


//             vector<vector<float>> lep_info;
//             //loop to count tight/loose muons
//             for( uint iMu = 0; iMu < nMuon; iMu++ ){
//                 vector<float> mu_vec;

//                 //check if meets basic object requirements
//                 bool mu_isGood = isGoodMuon( mu.dxy[iMu], mu.dz[iMu], mu.sip3d[iMu], mu.tightCharge[iMu], mu.mediumId[iMu], mu.chargeQuality[iMu] );
//                 int mu_isoType = isoType( year, mu.pdgid[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
//                 bool mu_isTight = isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType );
//                 bool mu_isLoose = isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType );
//                 mu_vec.push_back(mu.pdgid[iMu]);
//                 mu_vec.push_back(mu.pt[iMu]);
//                 mu_vec.push_back(mu.eta[iMu]);
//                 mu_vec.push_back(mu_isLoose);
//                 mu_vec.push_back(mu_isTight);
//                 lep_info.push_back(mu_vec);
//                 mu_vec.clear();


//                 /*if(eventNum==24206669||eventNum==38158050){
//                     cout << "entered muon loop for missing event" << endl;
//                     //cout << mu.pdgid[iMu] << ", " << mu.pt[iMu] << ", " << mu.eta[iMu] << ", " << mu.miniIso[iMu] << ", " << mu.jetRelIso[iMu] << ", " << mu.jetPtRelv2[iMu] << endl;
//                     //cout << mu_isGood << ", " << mu_isoType << ", " << mu_isTight << ", " << mu_isLoose << endl;
//                 }*/

//                 //check for tight or loose
//                 if ( isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){

//                     /*if(eventNum==24206669||eventNum==38158050){
//                         cout << "entered tight muon loop for missing event" << endl;
//                     }*/
//                     nGoodLep += 1;
//                     nLooseLep++;
//                     muCharge_tight.push_back(mu.charge[iMu]);
//                     if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_tight ){
//                         minMT_tight = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
//                     }
//                     if( mu.pt[iMu]>leadLep_pt ){
//                         leadLep_pt = mu.pt[iMu];
//                         leadLep_eta = mu.eta[iMu];
//                         leadLep_mass = mu.mass[iMu];
//                         leadLep_miniIso = mu.miniIso[iMu];
//                         leadLep_ptRel = mu.jetPtRelv2[iMu];
//                         leadLep_ptRatio = 1/(mu.jetRelIso[iMu] + 1);
//                     }
//                     if( sample_names[btype]=="franksTest" ){
//                         if( mu.genPartFlav[iMu] != 1 && mu.genPartFlav[iMu] != 15 ){
//                             isFake_mu = 1;
//                         }
//                     }else{
//                         isSignal = 1;
//                     }
//                     flipRateValue = GetFlipWeight(mu.pt[iMu],mu.eta[iMu],mu.pdgid[iMu]);
//                     flipRates.push_back(flipRateValue);

//                 }else if ( isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){

//                     /*if(eventNum==24206669||eventNum==38158050){
//                         cout << "entered loose muon loop for missing event" << endl;
//                     }*/
//                     nFakeableLep += 1;
//                     nLooseLep++;
//                     muCharge_loose.push_back(mu.charge[iMu]);

//                     if ( mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] ) < minMT_loose ){
//                         minMT_loose = mt( MET, MET_phi, mu.pt[iMu], mu.phi[iMu] );
//                     }
//                     MT_MET_lep = mt(MET, MET_phi, mu.pt[iMu], mu.phi[iMu]);


//                     if( sample_names[btype]=="franksTest" ){
//                         if( mu.genPartFlav[iMu] != 1 && mu.genPartFlav[iMu] != 15 ){
//                             isFake_loose = 1;
//                         }
//                     }

//                     coneCorrPtValue = coneCorrPt(year, mu.pdgid[iMu], mu.pt[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
//                     fakeRateValue = fakeRate(year, mu.pdgid[iMu], coneCorrPtValue, mu.eta[iMu]);
//                     fakeRates.push_back(fakeRateValue);
//                 }else continue;
//             }
//             //loop to count tight/loose electrons
//             for( uint iEl = 0; iEl < nElectron; iEl++ ){
//                 vector<float> el_vec;

//                 //check if meets basic object requirements
//                 bool el_isGood = isGoodElectron( el.dxy[iEl], el.dz[iEl], el.sip3d[iEl], el.tightCharge[iEl], el.lostHits[iEl], el.convVeto[iEl] );
//                 int el_isoType = isoType( year, el.pdgid[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
//                 bool el_isTight =  (isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) );
//                 bool el_isLoose = (isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) );
//                 el_vec.push_back(el.pdgid[iEl]);
//                 el_vec.push_back(el.pt[iEl]);
//                 el_vec.push_back(el.eta[iEl]);
//                 el_vec.push_back(el_isLoose);
//                 el_vec.push_back(el_isTight);
//                 lep_info.push_back(el_vec);
//                 el_vec.clear();


//                 /*if(eventNum==24206669||eventNum==38158050){
//                     cout << "entered electron loop for missing event" << endl;
//                     //cout << el.pdgid[iEl] << ", " << el.pt[iEl] << ", " << el.eta[iEl] << ", " << el.miniIso[iEl] << ", " << el.jetRelIso[iEl] << ", " << el.jetPtRelv2[iEl] << endl;
//                     //cout << el_isGood << ", " << el_isoType << ", " << el_isTight << ", " << el_isLoose << endl;
//                     //cout << isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) << ", " << electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) << ", " << isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) << ", " << electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) << endl;
//                     //cout << year << ", " << el.eta[iEl] << ", " << el.pt[iEl] << ", " << el.mva[iEl] << endl;
//                 }*/
//                 //check for tight or loose
//                 if ( isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ){

//                     /*if(eventNum==24206669||eventNum==38158050){
//                         cout << "entered tight electron loop for missing event" << endl;
//                     }*/
//                     nGoodLep += 1;
//                     nLooseLep++;
//                     elCharge_tight.push_back(el.charge[iEl]);
//                     if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_tight ){
//                         minMT_tight = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
//                     }
//                     if( el.pt[iEl]>leadLep_pt ){
//                         leadLep_pt = el.pt[iEl];
//                         leadLep_eta = el.eta[iEl];
//                         leadLep_mass = el.mass[iEl];
//                         leadLep_miniIso = el.miniIso[iEl];
//                         leadLep_ptRel = el.jetPtRelv2[iEl];
//                         leadLep_ptRatio = 1/(el.jetRelIso[iEl] + 1);
//                     }
//                     if( sample_names[btype]=="franksTest" ){
//                         if( el.genPartFlav[iEl] != 1 && el.genPartFlav[iEl] != 15 ){
//                             isFake_el = 1;
//                         }else if( el.pdgid[iEl]*-1 == genParts.pdgid[el.genPartIdx[iEl]] ){
//                             isFlip = 1;
//                         }
//                     }else{
//                         isSignal = 1;
//                     }
//                     flipRateValue = GetFlipWeight(el.pt[iEl],el.eta[iEl],el.pdgid[iEl]);
//                     flipRates.push_back(flipRateValue);
//                 }else if ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ){
                    
//                     /*if(eventNum==24206669||eventNum==38158050){
//                         cout << "entered loose electron loop for missing event" << endl;
//                     }*/
//                     nFakeableLep += 1;
//                     nLooseLep++;
//                     elCharge_loose.push_back(el.charge[iEl]);

//                     if ( mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] ) < minMT_loose ){
//                         minMT_loose = mt( MET, MET_phi, el.pt[iEl], el.phi[iEl] );
//                     }
//                     MT_MET_lep = mt(MET, MET_phi, el.pt[iEl], el.phi[iEl]);


//                     if( sample_names[btype]=="franksTest" ){
//                         if( el.genPartFlav[iEl] != 1 && el.genPartFlav[iEl] != 15 ){
//                             isFake_loose = 1;
//                         }
//                     }

//                     coneCorrPtValue = coneCorrPt(year, el.pdgid[iEl], el.pt[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
//                     fakeRateValue = fakeRate(year, el.pdgid[iEl], coneCorrPtValue, el.eta[iEl]);
//                     fakeRates.push_back(fakeRateValue);
//                 }else continue;
//             }


//             //background categorization 
//             if( sample_names[btype]=="franksTest" ){
//                 if (isFake_mu || isFake_el || isFake_loose){
//                     //if we found a fake muon, electron, or loose lepton, then fake event
//                     isFake = 1;
//                 }else if (!isFlip){
//                     //isFlip is set only in electron loop, so if it's not a flip, then it has to be other
//                     isSMSS = 1;
//                 }
//             }


//             int category = 0;
//             if(isFake) category = 1;
//             if(isFlip) category = 2;
//             if(isSMSS) category = 3;
//             //cout << isFake << isFlip << isSMSS << category << endl;

//             /*if(eventNum==24206669||eventNum==38158050){
//                 cout << "*************************" << endl;
//             }

//             if(eventNum==87794577){
//                 cout << "found event with more jets " << eventNum << endl;
//             }*/

//             //for franksTest, rm nlepton requirement here and replace with same but without if/else
//             //loop to count good jets and b-tagged jets
//             vector<vector<float>> jet_info;
//             for ( uint iJet = 0; iJet < nJet; iJet++ ){
//                 vector<float> jet_vec;
//                 if ( isGoodJet(jet.pt[iJet], jet.eta[iJet]) ){
//                     //next two for loops to clean jets
//                     bool isGood = 1;
//                     for (uint iMu = 0; iMu < nMuon; iMu++ ){
//                         bool mu_isGood = isGoodMuon( mu.dxy[iMu], mu.dz[iMu], mu.sip3d[iMu], mu.tightCharge[iMu], mu.mediumId[iMu], mu.chargeQuality[iMu] );
//                         int mu_isoType = isoType( year, mu.pdgid[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
//                         if ( isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) || isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
//                             if ( deltaR( jet.eta[iJet], jet.phi[iJet], mu.eta[iMu], mu.phi[iMu] ) < 0.4 ){
//                                 isGood = 0;
//                             }else continue;
//                         }else continue;
//                     }
//                     for (uint iEl = 0; iEl < nElectron; iEl++ ){
//                         bool el_isGood = isGoodElectron( el.dxy[iEl], el.dz[iEl], el.sip3d[iEl], el.tightCharge[iEl], el.lostHits[iEl], el.convVeto[iEl] );
//                         int el_isoType = isoType( year, el.pdgid[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
//                         if ( ( isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ) || ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ) ){
//                             if ( deltaR( jet.eta[iJet], jet.phi[iJet], el.eta[iEl], el.phi[iEl] ) < 0.4 ){
//                                 isGood = 0;
//                             }else continue;
//                         }else continue;
//                     }

//                     if ( isGood == 1 ){
//                         bool isBJet = 0;
//                         if (jet.pt[iJet]>40){
//                             nJets += 1;
//                             if (jet.pt[iJet]>leadJet_pt){
//                                 leadJet_pt=jet.pt[iJet];
//                             }
//                             jetHT = jetHT + jet.pt[iJet];
//                             if (jet.btag_score[iJet] > 0.2770 ){
//                                 isBJet = 1;
//                                 nBjets +=1;
//                             }
//                             jet_vec.push_back(jet.pt[iJet]);
//                             jet_vec.push_back(jet.eta[iJet]);
//                             jet_vec.push_back(isBJet);
//                             jet_info.push_back(jet_vec);
//                             /*if(eventNum==87794577){
//                                 cout << jet.pt[iJet] << ", " << jet.eta[iJet] << ", " << isBJet << endl;
//                             }*/
//                         } else if ( jet.btag_score[iJet] > 0.2770 ){
//                             isBJet = 1;
//                             nBjets += 1;
//                             jet_vec.push_back(jet.pt[iJet]);
//                             jet_vec.push_back(jet.eta[iJet]);
//                             jet_vec.push_back(isBJet);
//                             jet_info.push_back(jet_vec);
//                             jet_vec.clear();
//                             if(jet.pt[iJet]>leadB_pt){
//                                 leadB_pt = jet.pt[iJet];
//                                 leadB_mass = jet.mass[iJet];
//                                 MT_leadb_MET = mt( MET, MET_phi, jet.pt[iJet], jet.phi[iJet] );
//                             }
//                         }else continue;
//                     }else continue;
//                 }else continue;
//             }


//             /*if(eventNum==87794577){
//                 cout << "*************************" << endl;
//             }*/
// /*            if ( !((nFakeableLep==0 && nGoodLep>1) || (nFakeableLep>0 && nGoodLep<2)) ){
//                 continue;
//             }else{
//                 //loop to count good jets and b-tagged jets
//                 for ( uint iJet = 0; iJet < nJet; iJet++ ){
//                     if ( isGoodJet(jet.pt[iJet], jet.eta[iJet]) ){
//                         //next two for loops to clean jets
//                         bool isGood = 1;
//                         for (uint iMu = 0; iMu < nMuon; iMu++ ){
//                             bool mu_isGood = isGoodMuon( mu.dxy[iMu], mu.dz[iMu], mu.sip3d[iMu], mu.tightCharge[iMu], mu.mediumId[iMu], mu.chargeQuality[iMu] );
//                             int mu_isoType = isoType( year, mu.pdgid[iMu], mu.miniIso[iMu], mu.jetRelIso[iMu], mu.jetPtRelv2[iMu] );
//                             if ( isTightLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) || isLooseLepton( mu.pdgid[iMu], mu.pt[iMu], mu.eta[iMu], mu_isGood, mu_isoType ) ){
//                                 if ( deltaR( jet.eta[iJet], jet.phi[iJet], mu.eta[iMu], mu.phi[iMu] ) < 0.4 ){
//                                     isGood = 0;
//                                 }else continue;
//                             }else continue;
//                         }
//                         for (uint iEl = 0; iEl < nElectron; iEl++ ){
//                             bool el_isGood = isGoodElectron( el.dxy[iEl], el.dz[iEl], el.sip3d[iEl], el.tightCharge[iEl], el.lostHits[iEl], el.convVeto[iEl] );
//                             int el_isoType = isoType( year, el.pdgid[iEl], el.miniIso[iEl], el.jetRelIso[iEl], el.jetPtRelv2[iEl] );
//                             if ( ( isTightLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "tight" ) ) || ( isLooseLepton( el.pdgid[iEl], el.pt[iEl], el.eta[iEl], el_isGood, el_isoType ) && electronID( year, el.eta[iEl], el.pt[iEl], el.mva[iEl], "loose" ) ) ){
//                                 if ( deltaR( jet.eta[iJet], jet.phi[iJet], el.eta[iEl], el.phi[iEl] ) < 0.4 ){
//                                     isGood = 0;
//                                 }else continue;
//                             }else continue;
//                         }

//                         if ( isGood == 1 ){
//                             nJets += 1;
//                             if (jet.pt[iJet]>leadJet_pt){
//                                 leadJet_pt=jet.pt[iJet];
//                             }
//                             jetHT = jetHT + jet.pt[iJet];
//                             if ( jet.btag_score[iJet] > 0.2770 ){
//                                 nBjets += 1;
//                                 if(jet.pt[iJet]>leadB_pt){
//                                     leadB_pt = jet.pt[iJet];
//                                     leadB_mass = jet.mass[iJet];
//                                     MT_leadb_MET = mt( MET, MET_phi, jet.pt[iJet], jet.phi[iJet] );
//                                 }
//                             }else continue;
//                         }else continue;
//                     }else continue;
//                 }

//             }*/


//             //Lepton classification
//             bool isTrilep = 0;
//             bool isSS_SFdilep = 0;
//             bool isSS_OFdilep = 0;
//             bool isOS_SFdilep = 0;
//             bool isOS_OFdilep = 0;
//             bool isOneLepFO = 0;
//             bool isDilepFO = 0;
//             bool isSSFO = 0;
//             float goodLepCh = 0;
//             float fakeLepCh = 0;

//             if (nGoodLep>=3){
//                 isTrilep = 1;
//             }else if (nGoodLep == 2){
//                 if (muCharge_tight.size() == 2){
//                     if (muCharge_tight[0]*muCharge_tight[1]>0){
//                         isSS_SFdilep = 1;
//                     }else{ 
//                         isOS_SFdilep = 1;
//                     }
//                 }else if (elCharge_tight.size() == 2) {
//                     if (elCharge_tight[0]*elCharge_tight[1]>0){
//                         isSS_SFdilep = 1;
//                     }else{
//                         isOS_SFdilep = 1;
//                     }
//                 }else if (muCharge_tight.size() == 1) {
//                     if (muCharge_tight[0]*elCharge_tight[0]>0){
//                         isSS_OFdilep = 1;
//                     }else{
//                         isOS_OFdilep = 1;
//                     }
//                 }
//             }else if (nGoodLep==1 && nFakeableLep==1){
//                 if(muCharge_tight.size()==1){
//                     goodLepCh = muCharge_tight[0];
//                 }else if (elCharge_tight.size()==1){
//                     goodLepCh = elCharge_tight[0];
//                 }
//                 if(muCharge_loose.size()==1){
//                     fakeLepCh = muCharge_loose[0];
//                 }else if (elCharge_loose.size()==1){
//                     fakeLepCh = elCharge_loose[0];
//                 }
//                 if(goodLepCh*fakeLepCh>0){
//                     isSSFO = 1;
//                     isOneLepFO = 1;
//                 }
//             }else if (nFakeableLep==2){
//                 if(muCharge_loose.size()==2){
//                     if(muCharge_loose[0]*muCharge_loose[1]>0){
//                         isSSFO = 1;
//                     }
//                 }else if(elCharge_loose.size()==2){
//                     if(elCharge_loose[0]*elCharge_loose[1]>0){
//                         isSSFO = 1;
//                     }
//                 }else{
//                     if(elCharge_loose[0]*muCharge_loose[0]>0){
//                         isSSFO = 1;
//                     }
//                 }
//                 if (isSSFO){
//                     isDilepFO = 1;
//                 }
//             }


//             //define a weight for CR events.
//             //this will be applied to those events and fill the estimate histograms
//             float crWeight = 0;
//             //calculate fake rate weight
//             if ((isOneLepFO||isDilepFO) && nJets > 1){
//                 float fakeWeight = 1;
//                 if (fakeRates.size() < 1){
//                     fakeWeight = 0;
//                 }else{
//                     for(uint f = 0; f < fakeRates.size(); f++){
//                         fakeWeight = fakeWeight * (fakeRates[f]/(1-fakeRates[f]));
//                     }
//                 }
//                 crWeight = weight*fakeWeight;
//             }

//             //calculate flip rate weight
//             if ((isOS_OFdilep||isOS_SFdilep) && nJets > 1){
//                 float flipWeight = 0;
//                 for(uint f = 0; f < flipRates.size(); f++){
//                     flipWeight = flipWeight + (flipRates[f]/(1-flipRates[f]));
//                 }
//                 crWeight = weight * flipWeight;
//             }

//             //hyp_type for franksTest
//             int hyp_type = 0;
//             //1 for mass resonance veto
//             //2 for trilep
//             //3 for 2tight, 1loose
//             //4 for ss2l
//             //5 for os2l
//             //6 for 1tight, 1loose
//             //7 for 2loose

//             if (nGoodLep>=3){
//                 hyp_type = 2;
//             }else if (nGoodLep == 2 && nFakeableLep ==1){
//                 hyp_type = 3;
//             }else if (nGoodLep == 2 && nFakeableLep == 0){
//                 if (muCharge_tight.size() == 2){
//                     if (muCharge_tight[0]*muCharge_tight[1]>0){
//                         hyp_type = 4;
//                     }else{ 
//                         hyp_type = 5;
//                     }
//                 }else if (elCharge_tight.size() == 2) {
//                     if (elCharge_tight[0]*elCharge_tight[1]>0){
//                         hyp_type = 4;
//                     }else{
//                         hyp_type = 5;
//                     }
//                 }else if (muCharge_tight.size() == 1) {
//                     if (muCharge_tight[0]*elCharge_tight[0]>0){
//                         hyp_type = 4;
//                     }else{
//                         hyp_type = 5;
//                     }
//                 }
//             }else if (nGoodLep==1 && nFakeableLep==1){
//                 hyp_type = 6;
//             }else if (nGoodLep == 0 && nFakeableLep==2){
//                 hyp_type = 7;
//             }


//             if(eventNum==8033721||eventNum==8034006||eventNum==23264557||eventNum==23265140||eventNum==23307768||eventNum==23307962||eventNum==23308060){
//                 for(uint i = 0; i<lep_info.size(); i++){
//                     cout << "     " << lep_info[i][0] << "," << lep_info[i][1] << "," << lep_info[i][2] << "," << lep_info[i][3] << "," << lep_info[i][4] << endl;
//                 }
//             }

//             if (isTrilep||isSS_SFdilep||isSS_OFdilep||isOS_SFdilep||isOS_OFdilep||isOneLepFO||isDilepFO){
//                 //print for franksTest
//                 //cout << "*************************" << endl;
//                 cout << run << "," << lumiBlock << "," << eventNum << "," << category << "," << nLooseLep << "," << nGoodLep << "," << hyp_type << "," << nJets << "," << nBjets << endl;
//                 for (uint i = 0; i<jet_info.size(); i++){
//                     cout << "     " << jet_info[i][0] << ", " << jet_info[i][1] << ", " << jet_info[i][2] << endl;
//                 }
//                 //cout << "*************************" << endl;
//                 /*cout << run << "," << lumiBlock << "," << eventNum << "," << hyp_type << ",";
//                 for (uint i = 0; i < lep_info.size(); i++){
//                     cout << lep_info[i][0] << "," << lep_info[i][1] << "," << lep_info[i][2] << "," << lep_info[i][3] << "," << lep_info[i][4] << ",";
//                 }
//                 cout << nJets << "," << nBjets << "," << category << endl;*/
                
//                 //organize into signature types
//                 /*vector<float> variablesForFilling;
//                 variablesForFilling.push_back(nJets);
//                 variablesForFilling.push_back(nBjets);
//                 variablesForFilling.push_back(nGoodLep);
//                 variablesForFilling.push_back(leadLep_pt);
//                 variablesForFilling.push_back(leadLep_eta);
//                 variablesForFilling.push_back(leadLep_mass);
//                 variablesForFilling.push_back(leadLep_miniIso);
//                 variablesForFilling.push_back(leadLep_ptRel);
//                 variablesForFilling.push_back(leadLep_ptRatio);
//                 variablesForFilling.push_back(leadJet_pt);
//                 variablesForFilling.push_back(leadB_pt);
//                 variablesForFilling.push_back(leadB_mass);
//                 variablesForFilling.push_back(jetHT);
//                 variablesForFilling.push_back(MET);
//                 if (nGoodLep >= 2){
//                     variablesForFilling.push_back(minMT_tight);
//                 }
//                 if (nGoodLep == 1 && nFakeableLep ==1){
//                     if (minMT_tight < minMT_loose){
//                         variablesForFilling.push_back(minMT_tight);
//                     } else if (minMT_loose < minMT_tight){
//                         variablesForFilling.push_back(minMT_loose);
//                     }
//                 }
//                 if (nFakeableLep==2){
//                     variablesForFilling.push_back(minMT_loose);
//                 }
//                 variablesForFilling.push_back(MT_leadb_MET);

//                 //Now fill with those variables
//                 if (isFake||isFlip||isSMSS||isSignal){
//                     histos.fill(variablesForFilling, weight, crWeight, nJets, nBjets, nGoodLep, nFakeableLep, muCharge_tight, elCharge_tight, isSSFO, isFake, isFlip, isSMSS, isSignal);
//                 }
//                 if(isTrilep||isSS_SFdilep||isSS_OFdilep){
//                     //cout << isFake << " " << isFlip << " " << isSMSS << " " << isSignal << endl;
//                     vector<int> sampleHistoVars = {isFake, isFlip, isSMSS, nGoodLep, nJets, nBjets};
//                     sampleHistos.fillHistos(sName,sampleHistoVars, weight);
//                 }*/
//             }
            

       //}//event loop

        //auto stop = high_resolution_clock::now();
        //auto duration = duration_cast<seconds>(stop - start);

        //cout << stitchCounter << endl;
        //cout << "processed " << processed << " events in " << duration.count() << " seconds!!" << endl;

        /*histos.write(sample_names[btype], outFile);
        sampleHistos.writeHistos(outFile);*/
    //}

    //write histograms
    //outFile->Close();

//}