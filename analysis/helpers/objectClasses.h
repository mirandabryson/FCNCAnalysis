//define classes for physics objects 
class Lepton {
    public:
        vector<int> pdgid;
        vector<float> pt;
        vector<float> eta;
        vector<float> phi;
        vector<float> charge;
        vector<float> miniIso;
        vector<float> jetRelIso;
        vector<float> jetPtRelv2;
        vector<float> dxy;
        vector<float> dz;
        vector<float> sip3d;
        vector<int> tightCharge;
};




class Electron: public Lepton {//class electron inherits from class lepton
    private:
        vector<int> el_pdgid;
        vector<float> el_pt;
        vector<float> el_eta;
        vector<float> el_phi;
        vector<float> el_charge;
        vector<float> el_miniIso;
        vector<float> el_jetRelIso;
        vector<float> el_jetPtRelv2;
        vector<float> el_mva;
        vector<float> el_dxy;
        vector<float> el_dz;
        vector<float> el_sip3d;
        vector<int> el_lostHits;
        vector<bool> el_convVeto;
        vector<int> el_tightCharge;
    public:
        vector<float> mva;
        vector<int> lostHits;
        vector<bool> convVeto;

        //constructor automatically gets and fills the necessary kinematic variables
        Electron(TChain* &chain, int nElectrons, int year) {

            for ( int el = 0; el < nElectrons; el++ ){
                el_pdgid.push_back( chain->GetLeaf("Electron_pdgId")->GetValue(el) );
                el_pt.push_back( chain->GetLeaf("Electron_pt")->GetValue(el) );
                el_eta.push_back( chain->GetLeaf("Electron_eta")->GetValue(el) );
                el_phi.push_back( chain->GetLeaf("Electron_phi")->GetValue(el) );
                el_charge.push_back( chain->GetLeaf("Electron_charge")->GetValue(el) );
                el_miniIso.push_back( chain->GetLeaf("Electron_miniPFRelIso_all")->GetValue(el) );
                el_jetRelIso.push_back( chain->GetLeaf("Electron_jetRelIso")->GetValue(el) );
                el_jetPtRelv2.push_back( chain->GetLeaf("Electron_jetPtRelv2")->GetValue(el) );
                el_dxy.push_back( chain->GetLeaf("Electron_dxy")->GetValue(el) );
                el_dz.push_back( chain->GetLeaf("Electron_dz")->GetValue(el) );
                el_sip3d.push_back( chain->GetLeaf("Electron_sip3d")->GetValue(el) );
                el_lostHits.push_back( chain->GetLeaf("Electron_lostHits")->GetValue(el) );
                el_convVeto.push_back( chain->GetLeaf("Electron_convVeto")->GetValue(el) );
                el_tightCharge.push_back( chain->GetLeaf("Electron_tightCharge")->GetValue(el) );

                if (year == 2016){
                    el_mva.push_back( chain->GetLeaf("Electron_mvaSpring16GP")->GetValue(el) );
                }else{
                    el_mva.push_back( chain->GetLeaf("Electron_mvaFall17V1noIso")->GetValue(el) );
                }
            }

            pdgid = el_pdgid;
            pt = el_pt;
            eta = el_eta;
            phi = el_phi;
            charge = el_charge;
            miniIso = el_miniIso;
            jetRelIso = el_jetRelIso;
            jetPtRelv2 = el_jetPtRelv2;
            mva = el_mva;
            dxy = el_dxy;
            dz = el_dz;
            sip3d = el_sip3d;
            lostHits = el_lostHits;
            convVeto = el_convVeto;
            tightCharge = el_tightCharge;

        }//end constructor
};




class Muon: public Lepton {//class muon inherits from class lepton
    private:
        vector<int> mu_pdgid;
        vector<float> mu_pt;
        vector<float> mu_eta;
        vector<float> mu_phi;
        vector<float> mu_charge;
        vector<float> mu_miniIso;
        vector<float> mu_jetRelIso;
        vector<float> mu_jetPtRelv2;
        vector<float> mu_dxy;
        vector<float> mu_dz;
        vector<float> mu_sip3d;
        vector<float> mu_chargeQuality;
        vector<int> mu_tightId;
        vector<int> mu_mediumId;
        vector<int> mu_looseId;
        vector<int> mu_tightCharge;
    public:
        vector<float> chargeQuality;
        vector<int> tightId;
        vector<int> mediumId;
        vector<int> looseId;

        //constructor automatically gets and fills the necessary kinematic variables
        Muon(TChain* &chain, int nMuons, int year) {

            for ( int mu = 0; mu < nMuons; mu++ ){
                mu_pdgid.push_back( chain->GetLeaf("Muon_pdgId")->GetValue(mu) );
                mu_pt.push_back( chain->GetLeaf("Muon_pt")->GetValue(mu) );
                mu_eta.push_back( chain->GetLeaf("Muon_eta")->GetValue(mu) );
                mu_phi.push_back( chain->GetLeaf("Muon_phi")->GetValue(mu) );
                mu_charge.push_back( chain->GetLeaf("Muon_charge")->GetValue(mu) );
                mu_miniIso.push_back( chain->GetLeaf("Muon_miniPFRelIso_all")->GetValue(mu) );
                mu_jetRelIso.push_back( chain->GetLeaf("Muon_jetRelIso")->GetValue(mu) );
                mu_jetPtRelv2.push_back( chain->GetLeaf("Muon_jetPtRelv2")->GetValue(mu) );
                mu_dxy.push_back( chain->GetLeaf("Muon_dxy")->GetValue(mu) );
                mu_dz.push_back( chain->GetLeaf("Muon_dz")->GetValue(mu) );
                mu_sip3d.push_back( chain->GetLeaf("Muon_sip3d")->GetValue(mu) );
                mu_tightId.push_back( chain->GetLeaf("Muon_tightId")->GetValue(mu) );
                mu_mediumId.push_back( chain->GetLeaf("Muon_mediumId")->GetValue(mu) );
                mu_looseId.push_back( chain->GetLeaf("Muon_looseId")->GetValue(mu) );
                mu_tightCharge.push_back( chain->GetLeaf("Muon_tightCharge")->GetValue(mu) );
                mu_chargeQuality.push_back( (chain->GetLeaf("Muon_ptErr")->GetValue(mu))/(chain->GetLeaf("Muon_pt")->GetValue(mu)) );
            }

            pdgid = mu_pdgid;
            pt = mu_pt;
            eta = mu_eta;
            phi = mu_phi;
            charge = mu_charge;
            miniIso = mu_miniIso;
            jetRelIso = mu_jetRelIso;
            jetPtRelv2 = mu_jetPtRelv2;
            dxy = mu_dxy;
            dz = mu_dz;
            sip3d = mu_sip3d;
            tightId = mu_tightId;
            mediumId = mu_mediumId;
            looseId = mu_looseId;
            tightCharge = mu_tightCharge;
            chargeQuality = mu_chargeQuality;

        }//end constructor
};




class Jet {
    private:
        vector<float> jet_pt;
        vector<float> jet_eta;
        vector<float> jet_phi;
        vector<float> jet_btag_score;

    public:
        vector<float> pt;
        vector<float> eta;
        vector<float> phi;
        vector<float> btag_score;

        //constructor automatically gets and fills the necessary kinematic variables
        Jet(TChain* &chain, int nJets, int year) {

            for ( int j = 0; j < nJets; j++ ){
                jet_pt.push_back( chain->GetLeaf("Jet_pt")->GetValue(j) );
                jet_eta.push_back( chain->GetLeaf("Jet_eta")->GetValue(j) );
                jet_phi.push_back( chain->GetLeaf("Jet_phi")->GetValue(j) );
                jet_btag_score.push_back( chain->GetLeaf("Jet_btagDeepFlavB")->GetValue(j) );

            }

            pt = jet_pt;
            eta = jet_eta;
            phi = jet_phi;
            btag_score = jet_btag_score;


        }//end constructor
};

