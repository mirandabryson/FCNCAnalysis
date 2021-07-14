float getBtagEffFromFile(float pt, int mcFlavour, std::map<std::string, TH1D*> effMap){
    
    float pt_cutoff = std::max(20.,std::min(999.,double(pt)));
    TH1D* h(0);
    if (abs(mcFlavour) == 5) {h = effMap["btag"];}
    else if (abs(mcFlavour) == 4) {h = effMap["ctag"];}
    else {h = effMap["udsgtag"];}

    int binx = h->GetXaxis()->FindBin(pt_cutoff);
    return h->GetBinContent(binx);
}

float getBSF(int year, Jets &jets, Jets &bjets, std::map<std::string, TH1D*> effMap, BTagCalibrationReader &deepjet_medium_reader){
    float weight = 1.;
    float btag_data = 1.;
    float btag_mc = 1.;

    for ( auto bjet : bjets ){
        float sf = deepjet_medium_reader.eval(  BTagEntry::FLAV_B,
                                                bjet.eta(),
                                                bjet.pt(),
                                                bjet.bdisc());
        float eff = getBtagEffFromFile(bjet.pt(), bjet.hadronFlavor(), effMap);
        
        btag_data *= sf * eff;
        btag_mc *= eff;
    }
    for ( auto jet : jets ){
        if (jet.isBtag()){continue;}
        BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
        if (jet.hadronFlavor()==5) flavor = BTagEntry::FLAV_B;
        if (jet.hadronFlavor()==4) flavor = BTagEntry::FLAV_C;
        float pt_cutoff = std::max(20.,std::min(999.,double(jet.pt())));
        float sf = deepjet_medium_reader.eval(  flavor,
                                                jet.eta(),
                                                pt_cutoff,
                                                jet.bdisc());
        float eff = getBtagEffFromFile(jet.pt(), jet.hadronFlavor(), effMap);

        btag_data *= (1 - (sf * eff));
        btag_mc *= (1 - eff);
    }
    weight = btag_data/btag_mc;
    return weight;

}
