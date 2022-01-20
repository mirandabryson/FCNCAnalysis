float getIterativeCSF(int year, Jets &jets, Jets &btags, TFile* sfFile, string variationName, TString sampleCategory){
    // cout << "in cTagSF.h" << endl;
    TH2F *cWtHist;
    TH2F *bWtHist;
    TH2F *lWtHist;
    if(variationName=="central"){
        cWtHist = (TH2F*)sfFile->Get("SFc_hist");
        bWtHist = (TH2F*)sfFile->Get("SFb_hist");
        lWtHist = (TH2F*)sfFile->Get("SFl_hist");
    }else{
        cWtHist = (TH2F*)sfFile->Get(TString("SFc_hist_"+variationName).Data());
        bWtHist = (TH2F*)sfFile->Get(TString("SFb_hist_"+variationName).Data());
        lWtHist = (TH2F*)sfFile->Get(TString("SFl_hist_"+variationName).Data());
    }


    float weight = 1.;
    string syst = variationName;
    int flav, xbin, ybin;
    float cdisc, bdisc, jetPt, CvsLval, CvsBval;
    TH2F *wtHist;

    for ( auto jet : jets ){
        flav = int(jet.hadronFlavor());
        cdisc = jet.cdisc();
        bdisc = jet.bdisc();
        jetPt = jet.pt();
        CvsLval = 0;
        CvsBval = 0;
        // if((cdisc+bdisc)>1){std::cout << "error: cdisc+bdisc>1 " << cdisc << " " << bdisc << std::endl;}
        if(cdisc<0 || cdisc+bdisc==0){
            CvsLval = -1;
            CvsBval = -1;
        }else{
            CvsLval = cdisc/(1-bdisc);
            CvsBval = cdisc/(cdisc+bdisc);
        }

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

        xbin = wtHist->GetXaxis()->FindBin(CvsLval);
        ybin = wtHist->GetYaxis()->FindBin(CvsBval);
        weight *= wtHist->GetBinContent(xbin,ybin);

        // cout << "xbin: " << xbin << " ybin: " << ybin << " sf: " << wtHist->GetBinContent(xbin,ybin) << endl;
    }

    for ( auto bjet : btags ){
        flav = int(bjet.hadronFlavor());
        cdisc = bjet.cdisc();
        bdisc = bjet.bdisc();
        jetPt = bjet.pt();
        CvsLval = 0;
        CvsBval = 0;
        // if((cdisc+bdisc)>1){std::cout << "error: cdisc+bdisc>1 " << cdisc << " " << bdisc << std::endl;}
        if(cdisc<0 || cdisc+bdisc==0){
            CvsLval = -1;
            CvsBval = -1;
        }else{
            CvsLval = cdisc/(1-bdisc);
            CvsBval = cdisc/(cdisc+bdisc);
        }
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

        xbin = wtHist->GetXaxis()->FindBin(CvsLval);
        ybin = wtHist->GetYaxis()->FindBin(CvsBval);
        weight *= wtHist->GetBinContent(xbin,ybin);

        // cout << "xbin: " << xbin << " ybin: " << ybin << " sf: " << wtHist->GetBinContent(xbin,ybin) << endl;
    }
    // cout << "final weight: " << weight << endl;
    std::string sampCat = sampleCategory.Data();

    if(sampCat.find("fakes")!=std::string::npos){weight *= 1.01290;}
    if(sampCat.find("flips")!=std::string::npos){weight *= 1.04080;}
    if(sampCat.find("rares")!=std::string::npos){weight *= 0.95831;}
    if(sampCat.find("signal_tch")!=std::string::npos){weight *= 0.96338;}
    if(sampCat.find("signal_tuh")!=std::string::npos){weight *= 0.98814;}

    return weight;

}
