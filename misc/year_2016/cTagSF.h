float getIterativeCSF(int year, Jets &jets, TFile* sfFile, string variationName){
    // cout << "in cTagSF.h" << endl;
    TH2F *cWtHist = (TH2F*)sfFile->Get("SFc_hist");
    TH2F *bWtHist = (TH2F*)sfFile->Get("SFb_hist");
    TH2F *lWtHist = (TH2F*)sfFile->Get("SFl_hist");


    float weight = 1.;
    string syst = variationName;
    int flav, xbin, ybin;
    float cdisc, bdisc, jetPt;
    TH2F *wtHist;

    for ( auto jet : jets ){
        flav = int(jet.hadronFlavor());
        cdisc = jet.cdisc();
        bdisc = jet.bdisc();
        jetPt = jet.pt();
        if(flav == 4){
            wtHist = cWtHist;
            // cout << "cWtHist" << endl;
        }else if(flav == 5){
            wtHist = bWtHist;
            // cout << "bWtHist" << endl;
        }else{
            wtHist = lWtHist;
            // cout << "lWtHist" << endl;
        }

        xbin = wtHist->GetXaxis()->FindBin(cdisc);
        ybin = wtHist->GetYaxis()->FindBin(bdisc);
        weight *= wtHist->GetBinContent(xbin,ybin);

        // cout << "xbin: " << xbin << " ybin: " << ybin << " sf: " << wtHist->GetBinContent(xbin,ybin) << endl;


        // BTagEntry::JetFlavor flavor = BTagEntry::FLAV_UDSG;
        // if (jet.hadronFlavor()==5) flavor = BTagEntry::FLAV_B;
        // if (jet.hadronFlavor()==4) flavor = BTagEntry::FLAV_C;
        // //apply lf, hfstats1, hfstats2 to bjets
        // if(variationName.find("lf")!=std::string::npos && variationName.find("lfstats")==std::string::npos && flavor!=BTagEntry::FLAV_B){syst="central";}
        // if(variationName.find("hfstats")!=std::string::npos && flavor!=BTagEntry::FLAV_B){syst="central";}
        // //apply hf, lfstats1, lfstats2 to udsg jets
        // if(variationName.find("hf")!=std::string::npos && variationName.find("hfstats")==std::string::npos && flavor!=BTagEntry::FLAV_UDSG){syst="central";}
        // if(variationName.find("lfstats")!=std::string::npos && flavor!=BTagEntry::FLAV_UDSG){syst="central";}
        // //apply cferr1, cferr2 to cjets
        // if(variationName.find("cferr")!=std::string::npos && flavor!=BTagEntry::FLAV_C){syst="central";}
        // float pt_cutoff = std::max(20.,std::min(999.,double(jet.pt())));
        // float sf = deepjet_medium_reader.eval_auto_bounds(  syst,
        //                                                     flavor,
        //                                                     jet.eta(),
        //                                                     pt_cutoff,
        //                                                     jet.bdisc());
        // weight *= sf;
    }
    // cout << "final weight: " << weight << endl;
    return weight;

}
