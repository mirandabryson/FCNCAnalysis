#include <iostream>
#include "TMVA/Reader.h"
#include "../../../../NanoTools/NanoCORE/SSSelections.h"
#include "../../../../NanoTools/NanoCORE/Nano.h"

using namespace std;
using namespace std::chrono;
double convert_tmva_to_prob(double score) {
    // Undo TMVA transformation
    double raw_score = -0.5 * log( (2 / (score + 1)) - 1);
    // Apply logistic (sigmoid) transformation
    double prob = 1 / (1 + exp(-raw_score));
    return prob;
}
class BDT {
    unique_ptr<TMVA::Reader> booster;

    public:
        BDT(std::string path_to_xml);
        void set_features(Leptons, std::map<std::string, Float_t>, bool);
        Float_t get_score();    
};

Float_t get_BDT_score(Leptons ordered_leptons, std::map<std::string, Float_t> BDT_params, bool debug=false){
    auto start_time = high_resolution_clock::now();
    unique_ptr<TMVA::Reader> FCNC_booster;
    Float_t event = 1.0;
    Float_t MET_pt = nt.MET_pt();
    Lepton LeadLep = ordered_leptons[0];
    Lepton SubLeadLep = ordered_leptons[1];
    Float_t LeadLep_pt = LeadLep.pt();
    Float_t SubLeadLep_pt = SubLeadLep.pt();
    Float_t LeadLep_eta = abs(LeadLep.eta());
    Float_t SubLeadLep_eta = abs(SubLeadLep.eta());
    Float_t LeadLep_dxy = abs(LeadLep.dxy());
    Float_t SubLeadLep_dxy = abs(SubLeadLep.dxy());
    Float_t LeadLep_dz = abs(LeadLep.dz());
    Float_t SubLeadLep_dz = abs(SubLeadLep.dz());
    Float_t nElectron = nt.nElectron();
    Float_t LeadLep_SubLeadLep_Mass = (LeadLep.p4() + SubLeadLep.p4()).M();
    FCNC_booster.reset( new TMVA::Reader( "!Color:Silent" ) );
    // NOTE: you must add the booster variables in the same order
    // that they are organized in the xml file
    FCNC_booster->AddVariable("Most_Forward_pt", &(BDT_params["Most_Forward_pt"]));
    FCNC_booster->AddVariable("HT", &(BDT_params["HT"]));
    FCNC_booster->AddVariable("LeadLep_eta", &LeadLep_eta);
    FCNC_booster->AddVariable("LeadLep_pt", &LeadLep_pt);
    FCNC_booster->AddVariable("LeadLep_dxy", &LeadLep_dxy);
    FCNC_booster->AddVariable("LeadLep_dz", &LeadLep_dz);
    FCNC_booster->AddVariable("SubLeadLep_pt", &SubLeadLep_pt);
    FCNC_booster->AddVariable("SubLeadLep_eta", &SubLeadLep_eta);
    FCNC_booster->AddVariable("SubLeadLep_dxy", &SubLeadLep_dxy);
    FCNC_booster->AddVariable("SubLeadLep_dz", &SubLeadLep_dz);
    FCNC_booster->AddVariable("nJet", &(BDT_params["nJets"]));
    FCNC_booster->AddVariable("nbtag", &(BDT_params["nBtag"]));
    FCNC_booster->AddVariable("LeadJet_pt", &(BDT_params["LeadJet_pt"]));
    FCNC_booster->AddVariable("SubLeadJet_pt", &(BDT_params["SubLeadJet_pt"]));
    FCNC_booster->AddVariable("SubSubLeadJet_pt", &(BDT_params["SubSubLeadJet_pt"]));
    FCNC_booster->AddVariable("nElectron", &nElectron);
    FCNC_booster->AddVariable("MET_pt", &MET_pt);
    FCNC_booster->AddVariable("LeadBtag_pt", &(BDT_params["LeadBtag_pt"]));
    FCNC_booster->AddVariable("MT_LeadLep_MET", &(BDT_params["MT_LeadLep_MET"]));
    FCNC_booster->AddVariable("MT_SubLeadLep_MET", &(BDT_params["MT_SubLeadLep_MET"]));
    FCNC_booster->AddVariable("LeadLep_SubLeadLep_Mass", &LeadLep_SubLeadLep_Mass);
    FCNC_booster->BookMVA("BDT", "./helpers/BDT/test.xml");

    if (debug) {
        cout << "event: " << nt.event() << endl;
        cout << "Most_Forward_pt: " << BDT_params["Most_Forward_pt"] << endl;
        cout << "HT: " << BDT_params["HT"] << endl;
        cout << "LeadLep_eta: " << LeadLep_eta << endl;
        cout << "LeadLep_pt: " << LeadLep_pt << endl;
        cout << "LeadLep_dxy: " << LeadLep_dxy << endl;
        cout << "LeadLep_dz: " << LeadLep_dz << endl;
        cout << "SubLeadLep_pt: " << SubLeadLep_pt << endl;
        cout << "SubLeadLep_eta: " << SubLeadLep_eta << endl;
        cout << "SubLeadLep_dxy: " << SubLeadLep_dxy << endl;
        cout << "SubLeadLep_dz: " << SubLeadLep_dz << endl;
        cout << "nJet: " << BDT_params["nJets"] << endl;
        cout << "nBtag: " << BDT_params["nBtag"] << endl;
        cout << "LeadJet_pt: " << BDT_params["LeadJet_pt"] << endl;
        cout << "SubLeadJet_pt: " << BDT_params["SubLeadJet_pt"] << endl;
        cout << "SubSubLeadJet_pt: " << BDT_params["SubSubLeadJet_pt"] << endl;
        cout << "nElectron: " << nElectron << endl;
        cout << "MET_pt: " << MET_pt << endl;
        cout << "LeadBtag_pt: " << BDT_params["LeadBtag_pt"] << endl;
        cout << "MT_LeadLep_MET: " << BDT_params["MT_LeadLep_MET"] << endl;
        cout << "MT_SubLeadLep_MET: " << BDT_params["MT_SubLeadLep_MET"] << endl;
        cout << "LeadLep_SubLeadLep_Mass: " << LeadLep_SubLeadLep_Mass << endl;
    }
    Float_t booster_score = convert_tmva_to_prob(FCNC_booster->EvaluateMVA("BDT"));
    cout << "BDT eval time: " << duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() << endl;
    return booster_score;
}

BDT::BDT(std::string path_to_xml) {
    booster.reset( new TMVA::Reader( "!Color:Silent" ) );
    booster->BookMVA("BDT", path_to_xml);
}
     
void BDT::set_features(Leptons ordered_leptons, std::map<std::string, Float_t> BDT_params, bool debug=false){
    Float_t MET_pt = nt.MET_pt();
    Lepton LeadLep = ordered_leptons[0];
    Lepton SubLeadLep = ordered_leptons[1];
    Float_t LeadLep_pt = LeadLep.pt();
    Float_t SubLeadLep_pt = SubLeadLep.pt();
    Float_t LeadLep_eta = abs(LeadLep.eta());
    Float_t SubLeadLep_eta = abs(SubLeadLep.eta());
    Float_t LeadLep_dxy = abs(LeadLep.dxy());
    Float_t SubLeadLep_dxy = abs(SubLeadLep.dxy());
    Float_t LeadLep_dz = abs(LeadLep.dz());
    Float_t SubLeadLep_dz = abs(SubLeadLep.dz());
    Float_t nElectron = nt.nElectron();
    Float_t LeadLep_SubLeadLep_Mass = (LeadLep.p4() + SubLeadLep.p4()).M();
    //FCNC_booster.reset( new TMVA::Reader( "!Color:Silent" ) );
    // NOTE: you must add the booster variables in the same order
    // that they are organized in the xml file
    booster->AddVariable("Most_Forward_pt", &(BDT_params["Most_Forward_pt"]));
    booster->AddVariable("HT", &(BDT_params["HT"]));
    booster->AddVariable("LeadLep_eta", &LeadLep_eta);
    booster->AddVariable("LeadLep_pt", &LeadLep_pt);
    booster->AddVariable("LeadLep_dxy", &LeadLep_dxy);
    booster->AddVariable("LeadLep_dz", &LeadLep_dz);
    booster->AddVariable("SubLeadLep_pt", &SubLeadLep_pt);
    booster->AddVariable("SubLeadLep_eta", &SubLeadLep_eta);
    booster->AddVariable("SubLeadLep_dxy", &SubLeadLep_dxy);
    booster->AddVariable("SubLeadLep_dz", &SubLeadLep_dz);
    booster->AddVariable("nJet", &(BDT_params["nJets"]));
    booster->AddVariable("nbtag", &(BDT_params["nBtag"]));
    booster->AddVariable("LeadJet_pt", &(BDT_params["LeadJet_pt"]));
    booster->AddVariable("SubLeadJet_pt", &(BDT_params["SubLeadJet_pt"]));
    booster->AddVariable("SubSubLeadJet_pt", &(BDT_params["SubSubLeadJet_pt"]));
    booster->AddVariable("nElectron", &nElectron);
    booster->AddVariable("MET_pt", &MET_pt);
    booster->AddVariable("LeadBtag_pt", &(BDT_params["LeadBtag_pt"]));
    booster->AddVariable("MT_LeadLep_MET", &(BDT_params["MT_LeadLep_MET"]));
    booster->AddVariable("MT_SubLeadLep_MET", &(BDT_params["MT_SubLeadLep_MET"]));
    booster->AddVariable("LeadLep_SubLeadLep_Mass", &LeadLep_SubLeadLep_Mass);
    booster->BookMVA("BDT", "./helpers/BDT/test.xml");

    if (debug) {
        cout << "event: " << nt.event() << endl;
        cout << "Most_Forward_pt: " << BDT_params["Most_Forward_pt"] << endl;
        cout << "HT: " << BDT_params["HT"] << endl;
        cout << "LeadLep_eta: " << LeadLep_eta << endl;
        cout << "LeadLep_pt: " << LeadLep_pt << endl;
        cout << "LeadLep_dxy: " << LeadLep_dxy << endl;
        cout << "LeadLep_dz: " << LeadLep_dz << endl;
        cout << "SubLeadLep_pt: " << SubLeadLep_pt << endl;
        cout << "SubLeadLep_eta: " << SubLeadLep_eta << endl;
        cout << "SubLeadLep_dxy: " << SubLeadLep_dxy << endl;
        cout << "SubLeadLep_dz: " << SubLeadLep_dz << endl;
        cout << "nJet: " << BDT_params["nJets"] << endl;
        cout << "nBtag: " << BDT_params["nBtag"] << endl;
        cout << "LeadJet_pt: " << BDT_params["LeadJet_pt"] << endl;
        cout << "SubLeadJet_pt: " << BDT_params["SubLeadJet_pt"] << endl;
        cout << "SubSubLeadJet_pt: " << BDT_params["SubSubLeadJet_pt"] << endl;
        cout << "nElectron: " << nElectron << endl;
        cout << "MET_pt: " << MET_pt << endl;
        cout << "LeadBtag_pt: " << BDT_params["LeadBtag_pt"] << endl;
        cout << "MT_LeadLep_MET: " << BDT_params["MT_LeadLep_MET"] << endl;
        cout << "MT_SubLeadLep_MET: " << BDT_params["MT_SubLeadLep_MET"] << endl;
        cout << "LeadLep_SubLeadLep_Mass: " << LeadLep_SubLeadLep_Mass << endl;
    }
    //cout << "BDT eval time: " << duration_cast<milliseconds>(high_resolution_clock::now() - start_time).count() << endl;
    //return booster_score;
}

Float_t BDT::get_score() {
    Float_t booster_score = convert_tmva_to_prob(booster->EvaluateMVA("BDT"));
    return booster_score;
}

