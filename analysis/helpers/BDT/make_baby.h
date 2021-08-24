#include <TFile.h>
#include "../../../../NanoTools/NanoCORE/SSSelections.h"
#include "../../../../NanoTools/NanoCORE/Nano.h"

class BDTBabyMaker{
    std::map<std::string, Float_t> parameter_map; 
    TFile* BabyFile;
    TTree* BabyTree;
    Float_t weight;
    public:
        void set_features(std::map<std::string, Float_t>, Float_t);
        BDTBabyMaker(char*);
        BDTBabyMaker(); //return empty object
        void close(bool);
};

BDTBabyMaker::BDTBabyMaker(char* output_name) {
    BabyFile = new TFile(output_name, "RECREATE");
    BabyFile->cd();
    BabyTree = new TTree("T", "Events");
    //BabyTree->Branch("Event", &(parameter_map["Event"])); 
    BabyTree->Branch("Most_Forward_pt", &(parameter_map["Most_Forward_pt"]));
    BabyTree->Branch("HT", &(parameter_map["HT"]));
    BabyTree->Branch("LeadLep_eta", &(parameter_map["LeadLep_eta"]));
    BabyTree->Branch("LeadLep_pt", &(parameter_map["LeadLep_pt"]));
    BabyTree->Branch("LeadLep_dxy", &(parameter_map["LeadLep_dxy"]));
    BabyTree->Branch("LeadLep_dz", &(parameter_map["LeadLep_dz"]));
    BabyTree->Branch("SubLeadLep_pt", &(parameter_map["SubLeadLep_pt"]));
    BabyTree->Branch("SubLeadLep_eta", &(parameter_map["SubLeadLep_eta"]));
    BabyTree->Branch("SubLeadLep_dxy", &(parameter_map["SubLeadLep_dxy"]));
    BabyTree->Branch("SubLeadLep_dz", &(parameter_map["SubLeadLep_dz"]));
    BabyTree->Branch("nJets", &(parameter_map["nJets"]));
    BabyTree->Branch("nBtag", &(parameter_map["nBtag"]));
    BabyTree->Branch("LeadJet_pt", &(parameter_map["LeadJet_pt"]));
    BabyTree->Branch("SubLeadJet_pt", &(parameter_map["SubLeadJet_pt"]));
    BabyTree->Branch("SubSubLeadJet_pt", &(parameter_map["SubSubLeadJet_pt"]));
    BabyTree->Branch("LeadJet_BtagScore", &(parameter_map["LeadJet_BtagScore"]));
    BabyTree->Branch("SubLeadJet_BtagScore", &(parameter_map["SubLeadJet_BtagScore"]));
    BabyTree->Branch("SubSubLeadJet_BtagScore", &(parameter_map["SubSubLeadJet_BtagScore"]));
    BabyTree->Branch("nElectron", &(parameter_map["nElectron"]));
    BabyTree->Branch("MET_pt", &(parameter_map["MET_pt"]));
    BabyTree->Branch("LeadBtag_pt", &(parameter_map["LeadBtag_pt"]));
    BabyTree->Branch("MT_LeadLep_MET", &(parameter_map["MT_LeadLep_MET"]));
    BabyTree->Branch("MT_SubLeadLep_MET", &(parameter_map["MT_SubLeadLep_MET"]));
    BabyTree->Branch("LeadLep_SubLeadLep_Mass", &(parameter_map["LeadLep_SubLeadLep_Mass"]));
    BabyTree->Branch("SubSubLeadLep_pt", &(parameter_map["SubSubLeadLep_pt"]));
    BabyTree->Branch("SubSubLeadLep_eta", &(parameter_map["SubSubLeadLep_eta"]));
    BabyTree->Branch("SubSubLeadLep_dxy", &(parameter_map["SubSubLeadLep_dxy"]));
    BabyTree->Branch("SubSubLeadLep_dz", &(parameter_map["SubSubLeadLep_dz"]));
    BabyTree->Branch("MT_SubSubLeadLep_MET", &(parameter_map["MT_SubSubLeadLep_MET"]));
    BabyTree->Branch("LeadBtag_score", &(parameter_map["LeadBtag_score"]));
    BabyTree->Branch("Weight", &weight);
}

BDTBabyMaker::BDTBabyMaker() {
    BabyFile = new TFile;
    BabyFile->cd();
    BabyTree = new TTree("T", "Events");
    //BabyTree->Branch("Event", &(parameter_map["Event"])); 
    BabyTree->Branch("Most_Forward_pt", &(parameter_map["Most_Forward_pt"]));
    BabyTree->Branch("HT", &(parameter_map["HT"]));
    BabyTree->Branch("LeadLep_eta", &(parameter_map["LeadLep_eta"]));
    BabyTree->Branch("LeadLep_pt", &(parameter_map["LeadLep_pt"]));
    BabyTree->Branch("LeadLep_dxy", &(parameter_map["LeadLep_dxy"]));
    BabyTree->Branch("LeadLep_dz", &(parameter_map["LeadLep_dz"]));
    BabyTree->Branch("SubLeadLep_pt", &(parameter_map["SubLeadLep_pt"]));
    BabyTree->Branch("SubLeadLep_eta", &(parameter_map["SubLeadLep_eta"]));
    BabyTree->Branch("SubLeadLep_dxy", &(parameter_map["SubLeadLep_dxy"]));
    BabyTree->Branch("SubLeadLep_dz", &(parameter_map["SubLeadLep_dz"]));
    BabyTree->Branch("nJets", &(parameter_map["nJets"]));
    BabyTree->Branch("nBtag", &(parameter_map["nBtag"]));
    BabyTree->Branch("LeadJet_pt", &(parameter_map["LeadJet_pt"]));
    BabyTree->Branch("SubLeadJet_pt", &(parameter_map["SubLeadJet_pt"]));
    BabyTree->Branch("SubSubLeadJet_pt", &(parameter_map["SubSubLeadJet_pt"]));
    BabyTree->Branch("LeadJet_BtagScore", &(parameter_map["LeadJet_BtagScore"]));
    BabyTree->Branch("SubLeadJet_BtagScore", &(parameter_map["SubLeadJet_BtagScore"]));
    BabyTree->Branch("SubSubLeadJet_BtagScore", &(parameter_map["SubSubLeadJet_BtagScore"]));
    BabyTree->Branch("nElectron", &(parameter_map["nElectron"]));
    BabyTree->Branch("MET_pt", &(parameter_map["MET_pt"]));
    BabyTree->Branch("LeadBtag_pt", &(parameter_map["LeadBtag_pt"]));
    BabyTree->Branch("MT_LeadLep_MET", &(parameter_map["MT_LeadLep_MET"]));
    BabyTree->Branch("MT_SubLeadLep_MET", &(parameter_map["MT_SubLeadLep_MET"]));
    BabyTree->Branch("LeadLep_SubLeadLep_Mass", &(parameter_map["LeadLep_SubLeadLep_Mass"]));
    BabyTree->Branch("SubSubLeadLep_pt", &(parameter_map["SubSubLeadLep_pt"]));
    BabyTree->Branch("SubSubLeadLep_eta", &(parameter_map["SubSubLeadLep_eta"]));
    BabyTree->Branch("SubSubLeadLep_dxy", &(parameter_map["SubSubLeadLep_dxy"]));
    BabyTree->Branch("SubSubLeadLep_dz", &(parameter_map["SubSubLeadLep_dz"]));
    BabyTree->Branch("MT_SubSubLeadLep_MET", &(parameter_map["MT_SubSubLeadLep_MET"]));
    BabyTree->Branch("LeadBtag_score", &(parameter_map["LeadBtag_score"]));
    BabyTree->Branch("Weight", &weight);
}


void BDTBabyMaker::set_features(std::map<std::string, Float_t> BDT_params, Float_t event_weight=1.0) {
    //parameter_map["Event"] = nt.event();
    parameter_map["Most_Forward_pt"] = BDT_params["Most_Forward_pt"];
    parameter_map["HT"] = BDT_params["HT"];
    parameter_map["LeadLep_eta"] = BDT_params["LeadLep_eta"];
    parameter_map["LeadLep_pt"] = BDT_params["LeadLep_pt"];
    parameter_map["LeadLep_dxy"] = BDT_params["LeadLep_dxy"];
    parameter_map["LeadLep_dz"] = BDT_params["LeadLep_dz"];
    parameter_map["SubLeadLep_pt"] = BDT_params["SubLeadLep_pt"];
    parameter_map["SubLeadLep_eta"] = BDT_params["SubLeadLep_eta"];
    parameter_map["SubLeadLep_dxy"] = BDT_params["SubLeadLep_dxy"];
    parameter_map["SubLeadLep_dz"] = BDT_params["SubLeadLep_dz"];
    parameter_map["nJets"] = BDT_params["nJets"];
    parameter_map["nBtag"] = BDT_params["nBtag"];
    parameter_map["LeadJet_pt"] = BDT_params["LeadJet_pt"];
    parameter_map["SubLeadJet_pt"] = BDT_params["SubLeadJet_pt"];
    parameter_map["SubSubLeadJet_pt"] = BDT_params["SubSubLeadJet_pt"];
    parameter_map["LeadJet_BtagScore"] = BDT_params["LeadJet_BtagScore"];
    parameter_map["SubLeadJet_BtagScore"] = BDT_params["SubLeadJet_BtagScore"];
    parameter_map["SubSubLeadJet_BtagScore"] = BDT_params["SubSubLeadJet_BtagScore"];
    parameter_map["nElectron"] = BDT_params["nElectron"];
    parameter_map["MET_pt"] = BDT_params["MET_pt"];
    parameter_map["LeadBtag_pt"] = BDT_params["LeadBtag_pt"];
    parameter_map["MT_LeadLep_MET"] = BDT_params["MT_LeadLep_MET"];
    parameter_map["MT_SubLeadLep_MET"] = BDT_params["MT_SubLeadLep_MET"];
    parameter_map["LeadLep_SubLeadLep_Mass"] = BDT_params["LeadLep_SubLeadLep_Mass"];
    parameter_map["SubSubLeadLep_pt"] = BDT_params["SubSubLeadLep_pt"];
    parameter_map["SubSubLeadLep_eta"] = BDT_params["SubSubLeadLep_eta"];
    parameter_map["SubSubLeadLep_dxy"] = BDT_params["SubSubLeadLep_dxy"];
    parameter_map["SubSubLeadLep_dz"] = BDT_params["SubSubLeadLep_dz"];
    parameter_map["MT_SubSubLeadLep_MET"] = BDT_params["MT_SubSubLeadLep_MET"];
    parameter_map["LeadBtag_score"] = BDT_params["LeadBtag_score"];
    weight = event_weight;
    BabyTree->Fill();
}

void BDTBabyMaker::close(bool write) {
    if (write){
        BabyFile->Write();
    }
    BabyFile->Close();
}
