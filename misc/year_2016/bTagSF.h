float getBtagEffFromFile(float pt, int mcFlavour, std::map<std::string, TH1D*> effMap){
    
    float pt_cutoff = std::max(20.,std::min(999.,double(pt)));
    TH1D* h(0);
    if (abs(mcFlavour) == 5) {h = effMap["btag"];}
    else if (abs(mcFlavour) == 4) {h = effMap["ctag"];}
    else {h = effMap["udsgtag"];}

    int binx = h->GetXaxis()->FindBin(pt_cutoff);
    return h->GetBinContent(binx);
}

float getBSF(int year, Jets &jets, Jets &bjets, std::map<std::string, TH1D*> effMap, BTagCalibrationReader &deepjet_medium_reader, string variation){
    float weight = 1.;
    float btag_data = 1.;
    float btag_mc = 1.;

    for ( auto bjet : bjets ){
        float pt_cutoff = std::max(20.,std::min(999.,double(bjet.pt())));
        float sf = deepjet_medium_reader.eval_auto_bounds(  variation,
                                                BTagEntry::FLAV_B,
                                                bjet.eta(),
                                                pt_cutoff,
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
        float sf = deepjet_medium_reader.eval_auto_bounds(  variation,
                                                flavor,
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

// float getIterativeBSF(int year, Jets &jets, Jets &bjets, BTagCalibrationReader &deepjet_medium_reader){
//     float weight = 1.;

//     for ( auto bjet : bjets ){
//         float pt_cutoff = std::max(20.,std::min(999.,double(bjet.pt())));
//         float sf = deepjet_medium_reader.eval_auto_bounds(  "central",
//                                                             BTagEntry::FLAV_B,
//                                                             bjet.eta(),
//                                                             pt_cutoff,
//                                                             bjet.bdisc());
        
//         weight *= sf;
//     }
//     for ( auto jet : jets ){
//         if (jet.isBtag()){continue;}
//         BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
//         if (jet.hadronFlavor()==5) flavor = BTagEntry::FLAV_B;
//         if (jet.hadronFlavor()==4) flavor = BTagEntry::FLAV_C;
//         float pt_cutoff = std::max(20.,std::min(999.,double(jet.pt())));
//         float sf = deepjet_medium_reader.eval_auto_bounds(  "central",
//                                                             flavor,
//                                                             jet.eta(),
//                                                             pt_cutoff,
//                                                             jet.bdisc());
        
//         weight *= sf;
//     }
//     return weight;

// }

float getIterativeBSF(int year, Jets &jets, Jets &bjets, BTagCalibrationReader &deepjet_medium_reader, string variationName){
    float weight = 1.;
    string syst = variationName;

    for ( auto bjet : bjets ){
        BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
        if (bjet.hadronFlavor()==5) flavor = BTagEntry::FLAV_B;
        if (bjet.hadronFlavor()==4) flavor = BTagEntry::FLAV_C;
        //apply lf, hfstats1, hfstats2 to bjets
        if(variationName.find("lf")!=std::string::npos && variationName.find("lfstats")==std::string::npos && flavor!=BTagEntry::FLAV_B){syst="central";}
        if(variationName.find("hfstats")!=std::string::npos && flavor!=BTagEntry::FLAV_B){syst="central";}
        //apply hf, lfstats1, lfstats2 to udsg jets
        if(variationName.find("hf")!=std::string::npos && variationName.find("hfstats")==std::string::npos && flavor!=BTagEntry::FLAV_UDSG){syst="central";}
        if(variationName.find("lfstats")!=std::string::npos && flavor!=BTagEntry::FLAV_UDSG){syst="central";}
        //apply cferr1, cferr2 to cjets
        if(variationName.find("cferr")!=std::string::npos && flavor!=BTagEntry::FLAV_C){syst="central";}
        float pt_cutoff = std::max(20.,std::min(999.,double(bjet.pt())));
        float sf = deepjet_medium_reader.eval_auto_bounds(  syst,
                                                            flavor,
                                                            bjet.eta(),
                                                            pt_cutoff,
                                                            bjet.bdisc());
        weight *= sf;
    }
    for ( auto jet : jets ){
        if (jet.isBtag()){continue;}
        BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
        if (jet.hadronFlavor()==5) flavor = BTagEntry::FLAV_B;
        if (jet.hadronFlavor()==4) flavor = BTagEntry::FLAV_C;
        //apply lf, hfstats1, hfstats2 to bjets
        if(variationName.find("lf")!=std::string::npos && variationName.find("lfstats")==std::string::npos && flavor!=BTagEntry::FLAV_B){syst="central";}
        if(variationName.find("hfstats")!=std::string::npos && flavor!=BTagEntry::FLAV_B){syst="central";}
        //apply hf, lfstats1, lfstats2 to udsg jets
        if(variationName.find("hf")!=std::string::npos && variationName.find("hfstats")==std::string::npos && flavor!=BTagEntry::FLAV_UDSG){syst="central";}
        if(variationName.find("lfstats")!=std::string::npos && flavor!=BTagEntry::FLAV_UDSG){syst="central";}
        //apply cferr1, cferr2 to cjets
        if(variationName.find("cferr")!=std::string::npos && flavor!=BTagEntry::FLAV_C){syst="central";}
        float pt_cutoff = std::max(20.,std::min(999.,double(jet.pt())));
        float sf = deepjet_medium_reader.eval_auto_bounds(  syst,
                                                            flavor,
                                                            jet.eta(),
                                                            pt_cutoff,
                                                            jet.bdisc());
        weight *= sf;
    }
    return weight;

}
