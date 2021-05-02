#include "histogrammingClass.h"

std::string HistContainer::getRegionName(int hyp_type, int njets, int  nbjets) {
    std::vector<std::string> rnames = {"br","mr","ml","mlsf","ss","os","sf","df"};
    std::vector<std::string> jnames = {"0j","1j","2j","3j","ge4j"};
    std::vector<std::string> bnames = {"0j","1j","ge2j"};
    //return rnames[hyp_type]+"_"+jnames[std::min(njets,4)]+"_"+bnames[std::min(nbjets,2)];
    return rnames[hyp_type];
}

std::vector<std::string> HistContainer::getRegionNames() {
    std::vector<std::string> rnames = {"br","mr","ml","mlsf","ss","os","sf","df"};
    return rnames;
}

int HistContainer::getSR(int hyp_type, int njets, int nbjets) {
    if ( !(hyp_type==2 || hyp_type==4) ) continue;
    int ret=0;
    int offset=(std::min(njets,4)-1)+3*std::min(nbjets,2);
    int loffset=0;
    if (hyp_type==2) loffset=9;
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
            std::string htitle = region+"_"+quantity+"_"+sample;
            std::string hname = "h_"+region+"_"+quantity+"_"+sample;
            TH1F *hist = new TH1F(hname.c_str(),htitle.c_str(),nbins,xmin,xmax);
            hists1d_[htitle] = hist;
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
            std::string htitle = region+"_"+quantity+"_"+sample;
            std::string hname = "h_"+region+"_"+quantity+"_"+sample;
            TH2F *hist = new TH2F(hname.c_str(),htitle.c_str(),nbinsx,xmin,xmax,nbinsy,ymin,ymax);
            hists2d_[htitle] = hist;
    }
    return;
}

void HistContainer::loadHists(std::string sample) {
    addHist1d("njets",sample,7,-0.5,6.5);
    addHist1d("nbjets",sample,5,-0.5,4.5);
    addHist1d("nleps",sample,5,-0.5,4.5);
    addHist1d("llpt",sample,100,0,200);
    addHist1d("ltpt",sample,100,0,200);
    addHist1d("lleta",sample,100,-5,-5);
    addHist1d("lteta",sample,100,-5,-5);
    addHist1d("mll",sample,100,0,200);
    addHist1d("ljpt",sample,50,0,500);
    addHist1d("lbpt",sample,50,0,500);
    addHist1d("ht",sample,50,0,1000);
    addHist1d("met",sample,20,0,400);
    addHist1d("sr",sample,0.5,18.5,18,"br");
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

void HistContainer::fill1d(std::string region, std::string quantity, std::string sample, float value, float weight) {
    std::map<std::string,TH1F*>::iterator it1d;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {
        if (it1d->first.find(sample)==std::string::npos)  continue;
        if (it1d->first.find(quantity)!=std::string::npos) it1d->second->Fill(value,weight);
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

void HistContainer::fill(std::string sample, int best_hyp_type, Leptons &leps, Jets &jets, Jets &bjets, float met, float weight) {
    // fill 1d histograms first
    std::string rname = getRegionName(best_hyp_type,jets.size(),bjets.size());
    std::vector<std::string> rnames = {"br",rname};
    int njets=jets.size();
    int nbjets=bjets.size();
    for (auto name : rnames) {
        fill1d("njets",name,sample,njets,weight);
        fill1d("nbjets",name,sample,nbjets,weight);
        fill1d("nleps",name,sample,leps.size(),weight);
        fill1d("llpt",name,sample,leps[0].pt(),weight);
        fill1d("ltpt",name,sample,leps[1].pt(),weight);
        fill1d("lleta",name,sample,leps[0].eta(),weight);
        fill1d("lteta",name,sample,leps[1].eta(),weight);
        fill1d("ljpt",name,sample,jets[0].pt(),weight);
        fill1d("met",name,sample,met,weight);
        if (nbjets>0) fill1d("lbpt",name,sample,bjets[0].pt(),weight);
        float ht = get_sum_pt(jets);
        fill1d("ht",name,sample,ht,weight);
        for (unsigned int idx1=0; idx1<leps.size();idx1++) {
            for (unsigned int idx2=idx1+1; idx2<leps.size();idx2++) {
                float mass = (leps[idx1].p4()+leps[idx2].p4()).M();
                fill1d("mll",name,sample,mass,weight);
            }
        }
    }
    fill1d("sr","br",sample,getSR(hyp_type,njets,nbjets),weight)

    // now fill 2d histograms
    return;
}
