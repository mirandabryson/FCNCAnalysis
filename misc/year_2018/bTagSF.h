float getBtagEffFromFile(float pt, int mcFlavour, TFile* &f_btag_eff){
    
    TH2D* h_btag_eff_b_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_med_Eff_b");
    TH2D* h_btag_eff_c_temp    = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_med_Eff_c");
    TH2D* h_btag_eff_udsg_temp = (TH2D*) f_btag_eff->Get("h2_BTaggingEff_med_Eff_udsg");

    TH2D* h_btag_eff_b               = (TH2D*) h_btag_eff_b_temp->Clone("h_btag_eff_b");
    TH2D* h_btag_eff_c               = (TH2D*) h_btag_eff_c_temp->Clone("h_btag_eff_c");
    TH2D* h_btag_eff_udsg            = (TH2D*) h_btag_eff_udsg_temp->Clone("h_btag_eff_udsg");

    /*if(!h_btag_eff_b || !h_btag_eff_c || !h_btag_eff_udsg) {
        std::cout << "babyMaker::getBtagEffFromFile: ERROR: missing input hists" << std::endl;
        return 1.;
    }*/

    // only use pt bins up to 400 GeV for charm and udsg
    float pt_cutoff = std::max(20.,std::min(399.,double(pt)));
    TH2D* h(0);
    if (abs(mcFlavour) == 5) {
        h = h_btag_eff_b;
        // use pt bins up to 600 GeV for b
        pt_cutoff = std::max(20.,std::min(599.,double(pt)));
    }
    else if (abs(mcFlavour) == 4) {
        h = h_btag_eff_c;
    }
    else {
        h = h_btag_eff_udsg;
    }

    int binx = h->GetXaxis()->FindBin(pt_cutoff);
    //int biny = h->GetYaxis()->FindBin(fabs(eta));
    return h->GetBinContent(binx);//,biny);
    //f_btag_eff->Close();
}

float getBSF(int year, Jets &jets, Jets &bjets, TFile* &effFile, BTagCalibrationReader &deepjet_medium_reader){
    float weight = 1.;
    float btag_data = 1.;
    float btag_mc = 1.;

    for ( auto bjet : bjets ){
        float sf = deepjet_medium_reader.eval(  BTagEntry::FLAV_B,
                                                bjet.eta(),
                                                bjet.pt(),
                                                bjet.bdisc());
        float eff = getBtagEffFromFile(bjet.pt(), bjet.hadronFlavor(), effFile);

        btag_data *= sf * eff;
        btag_mc *= eff;
    }
    for ( auto jet : jets ){
        BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
        if (jet.hadronFlavor()==5) flavor = BTagEntry::FLAV_B;
        if (jet.hadronFlavor()==4) flavor = BTagEntry::FLAV_C;
        float sf = deepjet_medium_reader.eval(  flavor,
                                                jet.eta(),
                                                jet.pt(),
                                                jet.bdisc());
        float eff = getBtagEffFromFile(jet.pt(), jet.hadronFlavor(), effFile);

        btag_data *= (1 - (sf * eff));
        btag_mc *= (1 - eff);
    }
    weight = btag_data/btag_mc;
    return weight;

}
