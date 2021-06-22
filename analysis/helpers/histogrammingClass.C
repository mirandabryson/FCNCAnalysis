#include "histogrammingClass.h"

std::string HistContainer::getRegionName(int hyp_type, int njets, int  nbjets) {
    std::vector<std::string> rnames = {"br","mr","ml","mlsf","ss","os","sf","df","mldf"};
    std::vector<std::string> jnames = {"0j","1j","2j","3j","ge4j"};
    std::vector<std::string> bnames = {"0j","1j","ge2j"};
    //return rnames[hyp_type]+"_"+jnames[std::min(njets,4)]+"_"+bnames[std::min(nbjets,2)];
    return rnames[hyp_type];
}

std::vector<std::string> HistContainer::getRegionNames() {
    std::vector<std::string> rnames = { "br","mr","ml","mlsf","ss","os","sf","df","mldf",
                                        "osest","mlsfest","sfest","mldfest","dfest",
                                        //"vrcr_mlsf","vrcr_sf","vrcr_mldf","vrcr_df",
                                        //"vrcr_mlsfest","vrcr_sfest","vrcr_mldfest","vrcr_dfest",
                                        //"vrsr_ml","vrsr_ss",
                                        "vrcr","vrcrest","vrsr"};
    return rnames;
}

int HistContainer::getSR(int hyp_type, int njets, int nbjets) {
    if ( !(hyp_type==2 || hyp_type==4) ) return -1;
    int ret=0;
    int offset=(std::min(njets,4)-1)+3*std::min(nbjets,2);
    int loffset=0;
    if (hyp_type==2) loffset=9;
    return loffset+offset;
}

int HistContainer::getCRbin(int nleps, int njets, int nbjets) {
    //if ( !(hyp_type==2 || hyp_type==4) ) return -1;
    int ret=0;
    int offset=(std::min(njets,4)-1)+3*std::min(nbjets,2);
    int loffset=0;
    if (nleps==3) loffset=9;
    return loffset+offset;
}

void HistContainer::addHist1d(std::string quantity, std::string sample, int nbins, float xmin, float xmax, std::string region) {
    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH1F *hist = new TH1F(hname.c_str(),htitle.c_str(),nbins,xmin,xmax);
            hists1d_[htitle] = hist;
        }
    }
    else {
        TString tregion(region);
        TObjArray* objarray = tregion.Tokenize(" ");
        std::vector<std::string> regions;
        for (auto obj : *objarray) {
            regions.push_back( ((TString*)obj)->Data() );
        }
        for (auto name : regions) {
            //cout << name << endl;
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH1F *hist = new TH1F(hname.c_str(),htitle.c_str(),nbins,xmin,xmax);
            hists1d_[htitle] = hist;
            //cout << htitle << "  " << hname << endl;
        }
    }
    return;
}

void HistContainer::addHist2d(std::string quantity, std::string sample, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, std::string region) {
    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH2F *hist = new TH2F(hname.c_str(),htitle.c_str(),nbinsx,xmin,xmax,nbinsy,ymin,ymax);
            hists2d_[htitle] = hist;
        }
    }
    else {
        TString tregion(region);
        TObjArray* objarray = tregion.Tokenize(" ");
        std::vector<std::string> regions;
        for (auto obj : *objarray) {
            regions.push_back( ((TString*)obj)->Data() );
        }
        for (auto name : regions) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH2F *hist = new TH2F(hname.c_str(),htitle.c_str(),nbinsx,xmin,xmax,nbinsy,ymin,ymax);
            hists2d_[htitle] = hist;
        }
    }
    return;
}

void HistContainer::loadHists(std::string sample) {
    addHist1d("njets",sample,7,-0.5,6.5);
    addHist1d("nbjets",sample,5,-0.5,4.5);
    addHist1d("nleps",sample,5,-0.5,4.5);
    addHist1d("neles",sample,5,-0.5,4.5);
    addHist1d("nmus",sample,5,-0.5,4.5);
    addHist1d("llpt",sample,100,0,200);
    addHist1d("ltpt",sample,100,0,200);
    addHist1d("lleta",sample,100,-5.,-5.);
    addHist1d("lteta",sample,100,-5.,-5.);
    addHist1d("llminiiso",sample,16,0.,0.4);
    addHist1d("ltminiiso",sample,16,0.,0.4);
    addHist1d("mll",sample,100,0,200);
    addHist1d("ljpt",sample,50,0,500);
    addHist1d("tjpt",sample,50,0,500);
    addHist1d("lbpt",sample,50,0,500);
    addHist1d("ht",sample,50,0,1000);
    addHist1d("met",sample,20,0,400);
    //addHist1d("cutflow",sample,4,0.5,4.5);//,"br");
    addHist1d("sr",sample,18,0.5,18.5);//,"br");
    addHist1d("fakecr",sample,18,0.5,18.5);//,"br");
    //addHist1d("vrsr",sample,18,0.5,18.5);//,"br");
    //addHist1d("vrcr",sample,18,0.5,18.5);//,"br");
    addHist1d("vrsr",sample,18,0.5,18.5,"vrsr");
    addHist1d("vrcr",sample,18,0.5,18.5,"vrcr");
    addHist1d("vrcrest",sample,18,0.5,18.5,"vrcrest");
    addHist1d("vrsr_ee",sample,18,0.5,18.5,"vrsr");
    addHist1d("vrcr_ee",sample,18,0.5,18.5,"vrcr");
    addHist1d("vrcrest_ee",sample,18,0.5,18.5,"vrcrest");
    addHist1d("vrsr_mm",sample,18,0.5,18.5,"vrsr");
    addHist1d("vrcr_mm",sample,18,0.5,18.5,"vrcr");
    addHist1d("vrcrest_mm",sample,18,0.5,18.5,"vrcrest");
    addHist1d("vrsr_em",sample,18,0.5,18.5,"vrsr");
    addHist1d("vrcr_em",sample,18,0.5,18.5,"vrcr");
    addHist1d("vrcrest_em",sample,18,0.5,18.5,"vrcrest");
    addHist1d("vrsr_me",sample,18,0.5,18.5,"vrsr");
    addHist1d("vrcr_me",sample,18,0.5,18.5,"vrcr");
    addHist1d("vrcrest_me",sample,18,0.5,18.5,"vrcrest");
    addHist1d("bEff_b_num",sample,100,0,1000);
    addHist1d("bEff_c_num",sample,100,0,1000);
    addHist1d("bEff_l_num",sample,100,0,1000);
    addHist1d("bEff_b_den",sample,100,0,1000);
    addHist1d("bEff_c_den",sample,100,0,1000);
    addHist1d("bEff_l_den",sample,100,0,1000);
    return;
}

void HistContainer::sumw2() {
    std::map<std::string,TH1F*>::iterator it1d;
    std::map<std::string,TH2F*>::iterator it2d;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {it1d->second->Sumw2();}
    for (it2d=hists2d_.begin();it2d!=hists2d_.end();it2d++) {it2d->second->Sumw2();}
    return;
}

void HistContainer::write() {
    std::map<std::string,TH1F*>::iterator it1d;
    std::map<std::string,TH2F*>::iterator it2d;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {it1d->second->Write();}
    for (it2d=hists2d_.begin();it2d!=hists2d_.end();it2d++) {it2d->second->Write();}
    return;
}

void HistContainer::fill1d(std::string quantity, std::string region, std::string sample, float value, float weight) {
    std::map<std::string,TH1F*>::iterator it1d;
    //cout << quantity << " " << region << " " << sample << endl;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {
        //cout << it1d->first << endl;
        if (it1d->first.find(sample)==std::string::npos)  continue;
        if (it1d->first.find(quantity)==std::string::npos) continue;
        if (it1d->first.find(region)==std::string::npos) continue;
        if (region.find("est")==std::string::npos && it1d->first.find("est")!=std::string::npos) continue;
        if (region.find("ml")==std::string::npos && it1d->first.find("ml")!=std::string::npos) continue;
        if (region.find("vr")==std::string::npos && it1d->first.find("vr")!=std::string::npos) continue;
        it1d->second->Fill(value,weight);
        //cout << "filled " << it1d->first << " for event " << nt.event() << endl;
        /*if (region.find("vrcr")!=std::string::npos){
            std::cout << "Filling hist " << quantity << " with value " << value << " and weight " << weight << std::endl;
        }*/
    }
}

void HistContainer::fill2d(std::string region, std::string quantity, std::string sample, float xvalue, float yvalue, float weight) {
    std::map<std::string,TH2F*>::iterator it2d;
    for (it2d=hists2d_.begin();it2d!=hists2d_.end();it2d++) {
        if (it2d->first.find(sample)==std::string::npos)  continue;
        if (it2d->first.find(quantity)!=std::string::npos) it2d->second->Fill(xvalue,yvalue,weight);
    }
}

float get_sum_pt(Jets  &jets) {
    float ret = 0.;
    for (unsigned int idx=0; idx<jets.size();idx++) {
        ret += jets[idx].pt();
    }
    return ret;
}

void HistContainer::fill(std::string sample, int best_hyp_type, Leptons &leps, Jets &jets, Jets &bjets, float met, bool isVR_SR, bool isVR_CR, bool isEE, bool isEM, bool isME, bool isMM, bool isEFake, bool isMFake, float weight, float crWeight) {
    float fillWeight = 0;
    bool fillFakeCR = false;
    // fill 1d histograms first
    std::string rname = getRegionName(best_hyp_type,jets.size(),bjets.size());
    //std::cout << "SR: " << rname << std::endl;
    std::vector<std::string> rnames = {rname};
    std::vector<std::string> brmap = {"ml","ss"};
    if ( rname=="ml" || rname=="ss") rnames.push_back("br");
    if ( rname=="os" ) rnames.push_back("osest");
    if ( rname=="mlsf" ) rnames.push_back("mlsfest");
    if ( rname=="sf" ) rnames.push_back("sfest");
    if ( rname=="df" ) rnames.push_back("dfest");
    if ( rname=="mldf" ) rnames.push_back("mldfest");
    if ( rname=="sf"||rname=="df"||rname=="mlsf"||rname=="mldf" ) {fillFakeCR = true;}
    //if ( rname=="vrcr_sf"||rname=="vrcr_df"||rname=="vrcr_mlsf"||rname=="vrcr_mldf" ) {fillFakeVRCR = true;}
    //if ( rname=="vrsr_sf"||rname=="vrsr_df"||rname=="vrsr_mlsf"||rname=="vrsr_mldf" ) {fillFakeVRSR = true;}
    //std::cout << "# SRs: " << rnames.size() << std::endl;
    int njets=jets.size();
    int nbjets=bjets.size();
    int nleps=leps.size();
    int neles=0;
    int nmus=0;
    for (auto lep: leps) {
        if (lep.absid()==11){neles++;}
        else if (lep.absid()==13){nmus++;}
    }
    for (auto name : rnames) {
        if (name=="br") {
            counter_++;
            //std::cout << "Filled br histograms for " << counter_ << " time" << std::endl;
        }
        if ( name.find("est")==std::string::npos ) fillWeight = weight;
        else fillWeight = crWeight;
        //std::cout << "Filling histograms for region " << name << std::endl;
        fill1d("njets",name,sample,njets,fillWeight);
        fill1d("nbjets",name,sample,nbjets,fillWeight);
        fill1d("nleps",name,sample,nleps,fillWeight);
        fill1d("neles",name,sample,neles,fillWeight);
        fill1d("nmus",name,sample,nmus,fillWeight);
        fill1d("llpt",name,sample,leps[0].pt(),fillWeight);
        fill1d("ltpt",name,sample,leps[1].pt(),fillWeight);
        fill1d("lleta",name,sample,leps[0].eta(),fillWeight);
        fill1d("lteta",name,sample,leps[1].eta(),fillWeight);
        fill1d("llminiiso",name,sample,leps[0].miniIso(),fillWeight);
        fill1d("ltminiiso",name,sample,leps[1].miniIso(),fillWeight);
        fill1d("ljpt",name,sample,jets[0].pt(),fillWeight);
        fill1d("tjpt",name,sample,jets[1].pt(),fillWeight);
        fill1d("met",name,sample,met,fillWeight);
        if (nbjets>0) fill1d("lbpt",name,sample,bjets[0].pt(),fillWeight);
        float ht = get_sum_pt(jets);
        fill1d("ht",name,sample,ht,fillWeight);
        for (unsigned int idx1=0; idx1<leps.size();idx1++) {
            for (unsigned int idx2=idx1+1; idx2<leps.size();idx2++) {
                float mass = (leps[idx1].p4()+leps[idx2].p4()).M();
                fill1d("mll",name,sample,mass,fillWeight);
            }
        }
        for (auto bjet: bjets) {
            if (bjet.hadronFlavor()==5){
                fill1d("bEff_b_num",name,sample,bjet.pt(),fillWeight);
                if (bjet.pt()<40){fill1d("bEff_b_den",name,sample,bjet.pt(),fillWeight);}
            }
            else if (bjet.hadronFlavor()==4){
                fill1d("bEff_c_num",name,sample,bjet.pt(),fillWeight);
                if (bjet.pt()<40){fill1d("bEff_c_den",name,sample,bjet.pt(),fillWeight);}
            }
            else if (bjet.hadronFlavor()==0){
                fill1d("bEff_l_num",name,sample,bjet.pt(),fillWeight);
                if (bjet.pt()<40){fill1d("bEff_l_den",name,sample,bjet.pt(),fillWeight);}
            }
        }
        for (auto jet: jets) {
            if (jet.hadronFlavor()==5){fill1d("bEff_b_den",name,sample,jet.pt(),fillWeight);}
            else if (jet.hadronFlavor()==4){fill1d("bEff_c_den",name,sample,jet.pt(),fillWeight);}
            else if (jet.hadronFlavor()==0){fill1d("bEff_l_den",name,sample,jet.pt(),fillWeight);}
        }
        if (name == "br") {
            int sr = getSR(best_hyp_type,njets,nbjets);
            if (sr>=0)
                fill1d("sr",name,sample,sr,fillWeight);
            int cutflow_counter=4;
            fill1d("cutflow",name,sample,cutflow_counter,fillWeight);
        }
        int cr = getCRbin(nleps, njets, nbjets);
        if( fillFakeCR ){
            fill1d("fakecr",name,sample,cr,fillWeight);
            if (isVR_CR){fill1d("vrcr","vrcr_"+name,sample,cr,fillWeight);}
            if (isVR_CR && fillWeight==weight){fill1d("vrcr","vrcr",sample,cr,fillWeight);}
            if (isVR_CR && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest","vrcrest",sample,cr,fillWeight);}
            }
            if ((isEE||isEFake) && isVR_CR && fillWeight==weight){fill1d("vrcr_ee","vrcr",sample,cr,fillWeight);}
            if ((isEE||isEFake) && isVR_CR && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_ee","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_ee","vrcrest",sample,cr,fillWeight);}
            }
            if ((isEM||isMFake) && isVR_CR && fillWeight==weight){fill1d("vrcr_em","vrcr",sample,cr,fillWeight);}
            if ((isEM||isMFake) && isVR_CR && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_em","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_em","vrcrest",sample,cr,fillWeight);}
            }
            if ((isME||isEFake) && isVR_CR && fillWeight==weight){fill1d("vrcr_me","vrcr",sample,cr,fillWeight);}
            if ((isME||isEFake) && isVR_CR && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_me","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_me","vrcrest",sample,cr,fillWeight);}
            }
            if ((isMM||isMFake) && isVR_CR && fillWeight==weight){fill1d("vrcr_mm","vrcr",sample,cr,fillWeight);}
            if ((isMM||isMFake) && isVR_CR && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_mm","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_mm","vrcrest",sample,cr,fillWeight);}
            }
        }
        if (isVR_SR){fill1d("vrsr","vrsr_"+name,sample,cr,fillWeight);} 
        if(name == "ss" || name == "ml"){
            if (isVR_SR){fill1d("vrsr","vrsr",sample,cr,fillWeight);}
            if (isVR_SR && (isEE||(nleps==3&&isEFake))){fill1d("vrsr_ee","vrsr",sample,cr,fillWeight);}
            if (isVR_SR && (isEM||(nleps==3&&isMFake))){fill1d("vrsr_em","vrsr",sample,cr,fillWeight);}
            if (isVR_SR && (isME||(nleps==3&&isEFake))){fill1d("vrsr_me","vrsr",sample,cr,fillWeight);}
            if (isVR_SR && (isMM||(nleps==3&&isMFake))){fill1d("vrsr_mm","vrsr",sample,cr,fillWeight);}
        }

    } // end loop over regions

    // now fill 2d histograms
    return;
}
