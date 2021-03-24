//define classes for physics objects 
class Lepton {
    public:
        vector<float> pt;
        vector<float> eta;
        vector<float> phi;
        vector<float> charge;
        vector<float> iso;

};




class Electron: public Lepton {//class electron inherits from class lepton
    private:
        vector<float> el_pt;
        vector<float> el_eta;
        vector<float> el_phi;
        vector<float> el_charge;
        vector<float> el_iso;
        vector<float> el_mva;
    public:
        vector<float> mva;

        //constructor automatically gets and fills the necessary kinematic variables
        Electron(TChain* &chain, int nElectrons, int year) {

            for ( int el = 0; el < nElectrons; el++ ){
                el_pt.push_back( chain->GetLeaf("Electron_pt")->GetValue(el) );
                el_eta.push_back( chain->GetLeaf("Electron_eta")->GetValue(el) );
                el_phi.push_back( chain->GetLeaf("Electron_phi")->GetValue(el) );
                el_charge.push_back( chain->GetLeaf("Electron_charge")->GetValue(el) );
                el_iso.push_back( chain->GetLeaf("Electron_miniPFRelIso_all")->GetValue(el) );

                if (year == 2016){
                    el_mva.push_back( chain->GetLeaf("Electron_mvaSpring16GP")->GetValue(el) );
                }else{
                    el_mva.push_back( chain->GetLeaf("Electron_mvaFall17V1noIso")->GetValue(el) );
                }
            }

            pt = el_pt;
            eta = el_eta;
            phi = el_phi;
            charge = el_charge;
            iso = el_iso;
            mva = el_mva;

        }//end constructor
};




class Muon: public Lepton {//class muon inherits from class lepton
    private:
        vector<float> mu_pt;
        vector<float> mu_eta;
        vector<float> mu_phi;
        vector<float> mu_charge;
        vector<float> mu_iso;
        vector<int> mu_tightId;
        vector<int> mu_looseId;
    public:
        vector<int> tightId;
        vector<int> looseId;

        //constructor automatically gets and fills the necessary kinematic variables
        Muon(TChain* &chain, int nMuons, int year) {

            for ( int mu = 0; mu < nMuons; mu++ ){
                mu_pt.push_back( chain->GetLeaf("Muon_pt")->GetValue(mu) );
                mu_eta.push_back( chain->GetLeaf("Muon_eta")->GetValue(mu) );
                mu_phi.push_back( chain->GetLeaf("Muon_phi")->GetValue(mu) );
                mu_charge.push_back( chain->GetLeaf("Muon_charge")->GetValue(mu) );
                mu_iso.push_back( chain->GetLeaf("Muon_miniPFRelIso_all")->GetValue(mu) );
                mu_tightId.push_back( chain->GetLeaf("Muon_tightId")->GetValue(mu) );
                mu_looseId.push_back( chain->GetLeaf("Muon_looseId")->GetValue(mu) );
            }

            pt = mu_pt;
            eta = mu_eta;
            phi = mu_phi;
            charge = mu_charge;
            iso = mu_iso;
            tightId = mu_tightId;
            looseId = mu_looseId;

        }//end constructor
};
