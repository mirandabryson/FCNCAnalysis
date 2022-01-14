float getIterativeCSF(int year, Jets &jets, Jets &btags, TFile* sfFile, string variationName, TString sampleCategory){
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
    }

    for ( auto bjet : btags ){
        flav = int(bjet.hadronFlavor());
        cdisc = bjet.cdisc();
        bdisc = bjet.bdisc();
        jetPt = bjet.pt();
        if (jetPt>30) {continue;}
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
    }
    // cout << "final weight: " << weight << endl;
    std::string sampCat = sampleCategory.Data();

    if(sampCat.find("fakes")!=std::string::npos){weight *= 0.55;}
    if(sampCat.find("flips")!=std::string::npos){weight *= 0.50;}
    if(sampCat.find("rares")!=std::string::npos){weight *= 0.60;}
    if(sampCat.find("signal_tch")!=std::string::npos){weight *= 0.54;}
    if(sampCat.find("signal_tuh")!=std::string::npos){weight *= 0.55;}

    return weight;

}
