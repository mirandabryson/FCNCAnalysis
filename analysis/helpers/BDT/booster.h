#include <iostream>
#include "TMVA/Reader.h"
#include "../../../../NanoTools/NanoCORE/SSSelections.h"
#include "../../../../NanoTools/NanoCORE/Nano.h"

using namespace std;
Float_t get_BDT_score(Leptons ordered_leptons){
    unique_ptr<TMVA::Reader> FCNC_booster;
    Float_t event = 1.0;
    Float_t MET_pt = nt.MET_pt();
    Lepton LeadLep = ordered_leptons[0];
    Lepton SubLeadLep = ordered_leptons[1];
    Float_t LeadLep_pt = LeadLep.pt();
    Float_t SubLeadLep_pt = SubLeadLep.pt();
    Float_t LeadLep_eta = LeadLep.eta();
    Float_t SubLeadLep_eta = SubLeadLep.eta();
    //Float_t LeadLep_dxy = abs(LeadLep.dxy());
    Float_t default_dxy = 0.01;
    //Float_t SubLeadLep_dxy = abs(SubLeadLep.dxy());
    //cout << "subleadlep_dxy: " << SubLeadLep_dxy << endl;
    //Float_t LeadLep_dz = abs(LeadLep.dz());
    //Float_t SubLeadLep_dz = abs(SubLeadLep.dz());
    //cout << "SubLeadLep_dz: " << SubLeadLep_dz;
    Float_t nElectron = nt.nElectron();
    Float_t LeadLep_SubLeadLep_Mass = (LeadLep.p4() + SubLeadLep.p4()).M();
    Float_t default_pt = 200.0;
    FCNC_booster.reset( new TMVA::Reader( "!Color:Silent" ) );
    FCNC_booster->AddVariable("Most_Forward_pt", &default_pt);
    FCNC_booster->AddVariable("HT", &default_pt);
    FCNC_booster->AddVariable("LeadLep_eta", &LeadLep_eta);
    FCNC_booster->AddVariable("LeadLep_pt", &LeadLep_pt);
    FCNC_booster->AddVariable("LeadLep_dxy", &default_dxy);
    FCNC_booster->AddVariable("LeadLep_dz", &default_dxy);
    FCNC_booster->AddVariable("SubLeadLep_pt", &SubLeadLep_pt);
    FCNC_booster->AddVariable("SubLeadLep_eta", &SubLeadLep_eta);
    FCNC_booster->AddVariable("SubLeadLep_dxy", &default_dxy);
    FCNC_booster->AddVariable("SubLeadLep_dz", &default_dxy);
    FCNC_booster->AddVariable("nJet", &event);
    FCNC_booster->AddVariable("nbtag", &event);
    FCNC_booster->AddVariable("LeadJet_pt", &default_pt);
    FCNC_booster->AddVariable("SubLeadJet_pt", &default_pt);
    FCNC_booster->AddVariable("SubSubLeadJet_pt", &default_pt);
    FCNC_booster->AddVariable("nElectron", &nElectron);
    FCNC_booster->AddVariable("MET_pt", &MET_pt);
    FCNC_booster->AddVariable("LeadBtag_pt", &default_pt);
    FCNC_booster->AddVariable("MT_LeadLep_MET", &default_pt);
    FCNC_booster->AddVariable("MT_SubLeadLep_MET", &default_pt);
    FCNC_booster->AddVariable("LeadLep_SubLeadLep_Mass", &LeadLep_SubLeadLep_Mass);
    FCNC_booster->BookMVA(TString(""), TString("./helpers/BDT/test.xml"));
    cout << nt.event() << endl;
    Float_t booster_score = FCNC_booster->EvaluateMVA(TString(""));
    return booster_score;
}

