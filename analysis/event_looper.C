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
#include <algorithm>
#include "./helpers/fcnc_functions.h"
#include "./helpers/sampleLoader.h"
//#include "./helpers/objectClasses.h"
#include "./helpers/weights.h"
#include "./helpers/histogrammingClass.h"
#include "./helpers/flip_weights.h"
#include "./helpers/fake_rates.h"
#include "../../NanoTools/NanoCORE/MCTools.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"
#include "../../NanoTools/NanoCORE/IsolationTools.h"
#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/Config.h"


using namespace std;
using namespace std::chrono;

int main(void){
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


    string outdir = "plots/may26Histos/"+to_string(year)+"/";

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
            if (sample_names[btype]=="signal_hct"||sample_names[btype]=="signal_hut"){
                outfileName = outdir+"signal/"+outfileName+"_outputHistos.root";
            }else{outfileName = outdir+outfileName+"_outputHistos.root";}
            auto outFile = new TFile(outfileName.c_str(), "recreate");

            //make all histograms
            makeHistograms histos(sample_names[btype]);
            makeSampleHistos sampleHistos(sample_names[btype]);
            cout << "defined histograms" << endl;
            
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
                for(auto lep:leptons){
                    if( (lep.absid()==13&&lep.pt()>20&&abs(lep.eta())<2.4)||(lep.absid()==11&&lep.pt()>25&&abs(lep.eta())<2.4) ){
                        if(lep.idlevel()==SS::IDtight){
                            tightLeptons.push_back(lep);
                            tightCharges.push_back(lep.charge());
                        }
                        if(lep.idlevel()==SS::IDfakable) looseNotTightCharges.push_back(lep.charge());
                        if(lep.idlevel()==SS::IDfakable||lep.idlevel()==SS::IDtight){
                            looseLeptons.push_back(lep);
                            looseCharges.push_back(lep.charge());
                            if(sample_names[btype]=="background"){
                                if (lep.isFake()==1){
                                    isFake =1;
                                }else if(lep.absid()==11 && lep.isFlip()==1){
                                    isFlip = lep.isFlip();
                                }
                            }
                            flipRateValue = GetFlipWeight(lep.pt(),lep.eta(),lep.id());
                            flipRates.push_back(flipRateValue);

                            float ptrel_cut = 0;
                            float miniIso_cut = 0;
                            float ptRatio_cut = 0;
                            if (nt.year() == 2016){
                                if(lep.absid()==11){
                                    ptrel_cut = 7.2;
                                    miniIso_cut = 0.12;
                                    ptRatio_cut = 0.80;
                                }else if(lep.absid()==13){
                                    ptrel_cut = 7.2;
                                    miniIso_cut = 0.12;
                                    ptRatio_cut = 0.76;
                                }
                            }else{
                                if(lep.absid()==11){
                                    ptrel_cut = 8.0;
                                    miniIso_cut = 0.07;
                                    ptRatio_cut = 0.78;
                                }else if(lep.absid()==13){
                                    ptrel_cut = 6.8;
                                    miniIso_cut = 0.11;
                                    ptRatio_cut = 0.74;
                                }
                            }
                            coneCorrPtValue = coneCorrPt(lep.id(), lep.idx(), lep.pt(), miniIso_cut, ptRatio_cut, ptrel_cut);
                            fakeRateValue = fakeRate(year, lep.id(), coneCorrPtValue, lep.eta());
                            fakeRates.push_back(fakeRateValue);
                        }
                    }
                }
                nTight = tightLeptons.size();
                nLoose = looseLeptons.size();

                if (debug){
                    cout << "got leps" << endl;
                }


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
                else if(isFlip) category = 2;
                else if(isSMSS) category = 3;
                else if(isSMOS) category = 4;

                if(debug){
                    cout << "did categories" << endl;
                }



                //now we can get our jet information
                std::tuple<int, int, float> Jets = getCleanJetInfo(looseLeptons);
                int nJets = get<0>(Jets);
                int nBjets = get<1>(Jets);

                if (debug){
                    cout << "did jets" << endl;
                }


                //Lepton classification
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
                int hyp_type = 0;
                /*//1 for mass resonance
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
                if (nTight>=3){
                    for (uint i = 0; i<tightLeptons.size()-1; i++){
                        auto z_result = makesResonance(looseLeptons, tightLeptons[i], tightLeptons[i+1], 91., 15.);
                        auto gammastar_result = makesResonance(looseLeptons, tightLeptons[i], tightLeptons[i+1], 0., 12.);
                        if(z_result.first>=0){extraZ=1;}
                        if(gammastar_result.first>=0){extraGammaStar=1;}
                    }
                    if( (extraZ||extraGammaStar) ){hyp_type=1;}
                    else{hyp_type = 2;}
                }else if (nTight == 2 && nLoose >=3){
                    for (uint i = 0; i<looseLeptons.size()-1; i++){
                        auto z_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 91., 15.);
                        auto gammastar_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 0., 12.);
                        if(z_result.first>=0){extraZ=1;}
                        if(gammastar_result.first>=0){extraGammaStar=1;}
                        if(eventNum==37992149||eventNum==31921416||eventNum==101415088){
                            cout << z_result.first << " " << z_result.second << " " << gammastar_result.first << " " << gammastar_result.second << endl;
                            cout << extraZ << " " << extraGammaStar << " " << endl;
                        }
                    }
                    if( (extraZ||extraGammaStar) ){hyp_type=1;}
                    else{hyp_type = 3;}
                }else if (nTight == 2 && nLoose == 2){
                    auto z_result = makesResonance(looseLeptons, looseLeptons[0], looseLeptons[1], 91., 15.);
                    auto gammastar_result = makesResonance(looseLeptons, looseLeptons[0], looseLeptons[1], 0., 12.);
                    if(z_result.first>=0){extraZ=1;}
                    if(gammastar_result.first>=0){extraGammaStar=1;}
                    if( (extraZ||extraGammaStar) ){hyp_type=1;}
                    else{
                        if (tightCharges[0]*tightCharges[1]>0){
                            hyp_type = 4;
                        }else{ 
                            hyp_type = 5;
                        }
                    }
                }else if ((nTight==1 && nLoose==2 && tightCharges[0]*looseNotTightCharges[0]>0)  ){
                    for (uint i = 0; i<looseLeptons.size()-1; i++){
                        auto z_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 91., 15.);
                        auto gammastar_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 0., 12.);
                        if(z_result.first>=0){extraZ=1;}
                        if(gammastar_result.first>=0){extraGammaStar=1;}
                        if(eventNum==37992149||eventNum==31921416||eventNum==101415088){
                            cout << z_result.first << " " << z_result.second << " " << gammastar_result.first << " " << gammastar_result.second << endl;
                            cout << extraZ << " " << extraGammaStar << " " << endl;
                        }
                    }
                    if( (extraZ||extraGammaStar) ){hyp_type=1;}
                    else{hyp_type = 6;}
                }else if (nLooseNotTight==2 && (looseNotTightCharges[0]*looseNotTightCharges[1]>0||tightLooseSS)){
                    for (uint i = 0; i<looseLeptons.size()-1; i++){
                        auto z_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 91., 15.);
                        auto gammastar_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 0., 12.);
                        if(z_result.first>=0){extraZ=1;}
                        if(gammastar_result.first>=0){extraGammaStar=1;}
                        if(eventNum==37992149||eventNum==31921416||eventNum==101415088){
                            cout << z_result.first << " " << z_result.second << " " << gammastar_result.first << " " << gammastar_result.second << endl;
                            cout << extraZ << " " << extraGammaStar << " " << endl;
                        }
                    }
                    if( (extraZ||extraGammaStar) ){hyp_type=1;}
                    else if( nLoose==2 ){hyp_type = 7;}
                    else if( nLoose==3 && nTight==1 ){hyp_type = 8;}
                }else if (nLooseNotTight>=3 && (looseNotTightCharges[0]*looseNotTightCharges[1]>0||looseNotTightCharges[0]*looseNotTightCharges[2]>0||looseNotTightCharges[1]*looseNotTightCharges[2]>0)){
                    for (uint i = 0; i<looseLeptons.size()-1; i++){
                        auto z_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 91., 15.);
                        auto gammastar_result = makesResonance(looseLeptons, looseLeptons[i], looseLeptons[i+1], 0., 12.);
                        if(z_result.first>=0){extraZ=1;}
                        if(gammastar_result.first>=0){extraGammaStar=1;}
                    }
                    if( (extraZ||extraGammaStar) ){hyp_type=1;}
                    else if( nLoose==3 && nTight==0 ){hyp_type = 9;}
                }*/
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



                //1 for mass resonance
                //2 for trilep
                //3 for 2tight, 1loose
                //4 for ss2l
                //5 for os2l
                //6 for 1tight, 1loose
                //7 for 2loose
                //8 for tll
                //9 for lll
                bool isTrilep = 0;
                bool isSS_SFdilep = 0;
                bool isSS_OFdilep = 0;
                bool isOS_SFdilep = 0;
                bool isOS_OFdilep = 0;
                bool isOneLepFO = 0;
                bool isDilepFO = 0;
                bool isSSFO = 0;
                if (hyp_type==2){isTrilep=1;}
                if (hyp_type==4 && tightLeptons[0].absid()==tightLeptons[1].absid()){isSS_SFdilep=1;}
                if (hyp_type==4 && tightLeptons[0].absid()!=tightLeptons[1].absid()){isSS_OFdilep=1;}
                if (hyp_type==5 && tightLeptons[0].absid()==tightLeptons[1].absid()){isOS_SFdilep=1;}
                if (hyp_type==5 && tightLeptons[0].absid()!=tightLeptons[1].absid()){isOS_OFdilep=1;}
                if (hyp_type==3||hyp_type==6){
                    isOneLepFO=1;
                    isSSFO=1;
                }
                if (hyp_type==7||hyp_type==8||hyp_type==9){
                    isDilepFO=1;
                    isSSFO=1;
                }

                /*if (nTight>=3){
                    isTrilep = 1;
                }else if (nTight == 2){
                    if (tightCharges[0]*tightCharges[1]>0){
                        if (tightLeptons[0].absid()==tightLeptons[1].absid()){
                            isSS_SFdilep = 1;
                        }else{
                            isSS_OFdilep = 1;
                        }
                    }else if (tightCharges[0]*tightCharges[1]<0){
                        if (tightLeptons[0].absid()==tightLeptons[1].absid()){
                            isOS_SFdilep = 1;
                        }else{
                            isOS_OFdilep = 1;
                        }
                    }
                }else if (nTight==1 && nLoose==2){
                    if(looseCharges[0]*looseCharges[1]>0){
                        isSSFO = 1;
                        isOneLepFO = 1;
                    }
                }else if (nTight==0 && nLoose==2){
                    if(looseCharges[0]*looseCharges[1]>0){
                        isSSFO = 1;
                        isDilepFO = 1;
                    }
                }*/

                if (debug) {cout << "hyp type" << endl;}



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

                if (debug) {cout << "fake weight" << endl;}

                //calculate flip rate weight
                if ((isOS_OFdilep||isOS_SFdilep) && nJets > 1){
                    float flipWeight = 0;
                    for(uint f = 0; f < flipRates.size(); f++){
                        flipWeight = flipWeight + (flipRates[f]/(1-flipRates[f]));
                    }
                    crWeight = weight * flipWeight;
                }

                if (debug) {cout << "flip weight" << endl;}


                sort(tightLeptons.begin(), tightLeptons.end(), lepsort);
                sort(looseLeptons.begin(), looseLeptons.end(), lepsort);

                if (debug) {cout << "lepton sort" << endl;}

                //organize into signature types
                vector<float> variablesForFilling;
                if (nJets>1 && (isFake||isFlip||isSMSS||isSignal) && looseLeptons.size()>0 && stitch == 1){
                    variablesForFilling.push_back(nJets);
                    variablesForFilling.push_back(nBjets);
                    variablesForFilling.push_back(nTight);
                    variablesForFilling.push_back(looseLeptons[0].pt());
                    variablesForFilling.push_back(looseLeptons[0].eta());
                    variablesForFilling.push_back(looseLeptons[0].mass());
                    variablesForFilling.push_back(looseLeptons[0].miniIso());
                    //variablesForFilling.push_back(looseLeptons[0].ptRel);
                    //variablesForFilling.push_back(looseLeptons[0].ptRatio);
                    //variablesForFilling.push_back(nt.Jet_pt()[get<2>(Jets)]);
                    //variablesForFilling.push_back(leadB_pt);
                    //variablesForFilling.push_back(leadB_mass);
                    //variablesForFilling.push_back(get<4>(Jets));
                    variablesForFilling.push_back(MET);
                    /*cout << "variables: ";
                    for (uint a = 0; a < variablesForFilling.size(); a++){
                        cout << " " << variablesForFilling[a] << " ";
                    }
                    cout << endl;*/
                    /*if (nGoodLep >= 2){
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
                    variablesForFilling.push_back(MT_leadb_MET);*/
                }

                if (debug) {cout << "found variables" << endl;}


                //Now fill with those variables
                if (nJets>1 && (isFake||isFlip||isSMSS||isSignal) && variablesForFilling.size()>0){
                    //cout << nJets << " " << nBjets << endl;
                    histos.fill(variablesForFilling, weight, crWeight, nJets, nBjets, /*nGoodLep, nFakeableLep, muCharge_tight, elCharge_tight,*/ isSSFO, isFake, isFlip, isSMSS, isSignal, isTrilep, isSS_SFdilep, isSS_OFdilep, isOS_SFdilep, isOS_OFdilep, isOneLepFO, isDilepFO/*, eventNum*/);
                }
                if(nJets>1 && (isTrilep||isSS_SFdilep||isSS_OFdilep)){
                    //cout << isFake << " " << isFlip << " " << isSMSS << " " << isSignal << endl;
                    vector<int> sampleHistoVars = {isFake, isFlip, isSMSS, nTight, nJets, nBjets};
                    sampleHistos.fillHistos(sName,sampleHistoVars, weight);
                }

                if (debug) {cout << "filled histos" << endl;}


            }//event loop
       

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);

            //cout << stitchCounter << endl;
            cout << "processed " << processed << " events in " << duration.count() << " seconds!!" << endl;

            histos.write(sample_names[btype], outFile);
            sampleHistos.writeHistos(outFile);
            outFile->Close();
        }//file loop
    }//chain loop

}
