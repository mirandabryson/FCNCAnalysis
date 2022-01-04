#include "histogrammingClass.h"


std::string HistContainer::getRegionName(int hyp_type, int njets, int  nbjets) {
    std::vector<std::string> rnames = {"br","mr","ml","mlsf","ss","os","sf","df","mldf"/*,"tronz"*/};
    std::vector<std::string> jnames = {"0j","1j","2j","3j","ge4j"};
    std::vector<std::string> bnames = {"0j","1j","ge2j"};
    //return rnames[hyp_type]+"_"+jnames[std::min(njets,4)]+"_"+bnames[std::min(nbjets,2)];
    return rnames[hyp_type];
}

std::vector<std::string> HistContainer::getRegionNames() {
    std::vector<std::string> rnames = { "br","mr","ml","mlsf","ss","os","sf","df","mldf",
                                        "osest","mlsfest","sfest","mldfest","dfest",
                                        "sfpp","dfpp","mlsfppp","mldfppp",
                                        "sfppest","dfppest","mlsfpppest","mldfpppest",
                                        /*"vrcr","vrcrest","vrsr",
                                         "vrcr_flip","vrcrest_flip","vrsr_flip",*/};

    // std::vector<std::string> rnames = { "PU_up","PU_down",
    //                                     "LepSF_up","LepSF_down",
    //                                     "Trigger_up","Trigger_down",
    //                                     "lf_up","lf_down",
    //                                     "hf_up","hf_down",
    //                                     "hfstats1_up","hfstats1_down",
    //                                     "hfstats2_up","hfstats2_down",
    //                                     "lfstats1_up","lfstats1_down",
    //                                     "lfstats2_up","lfstats2_down",
    //                                     "cferr1_up","cferr1_down",
    //                                     "cferr2_up","cferr2_down",
    //                                     "btag_central",
    //                                     "bTag_up","bTag_down",
    //                                     /*"renorm_scale","pdf_scale"*/};
    // std::vector<std::string> rnames;
    // for(int i = 0; i < 101; i++){
    //     std::string i_str = std::to_string(i);
    //     rnames.push_back(i_str+"_"+i_str+"_pdf_scale");
    // }
    // for(int j = 0; j <= 6; j++){
    //     std::string j_str = std::to_string(j);
    //     rnames.push_back(j_str+"_renorm_scale");
    // }

    return rnames;
}

int HistContainer::getSR(int hyp_type, int njets, int nbjets) {
    // if(hyp_type==2 && njets>3 && nbjets >1){cout << "njets: " << njets << "  nbjets: " << nbjets << "  hyptype: " << hyp_type << endl;}
    if ( !(hyp_type==2 || hyp_type==4) ) return -1;
    int ret=0;
    int joffset = 3;
    if (hyp_type==2){joffset = 4;};
    int offset=(std::min(njets,4)-1)+joffset*std::min(nbjets,2);
    int loffset=0;
    if (hyp_type==2) loffset=10;
    return loffset+offset;
}

int HistContainer::getCRbin(int nleps, int njets, int nbjets) {
    //if ( !(hyp_type==2 || hyp_type==4) ) return -1;
    int ret=0;
    int joffset = 3;
    if (nleps==3){joffset = 4;};
    int offset=(std::min(njets,4)-1)+joffset*std::min(nbjets,2);
    int loffset=0;
    if (nleps==3) loffset=10;
    return loffset+offset;
}

int HistContainer::getEtaBin(float lep_eta, int lep_id) {
    int bin = 0;
    
    if(abs(lep_id)==11){
        if (fabs(lep_eta)>=0.000 && fabs(lep_eta)<0.800) bin = 1;
        if (fabs(lep_eta)>=0.800 && fabs(lep_eta)<1.479) bin = 2;
        if (fabs(lep_eta)>=1.479 && fabs(lep_eta)<2.500) bin = 3;
    }else{
        if (fabs(lep_eta)>=0.000 && fabs(lep_eta)<1.2) bin = 1;
        if (fabs(lep_eta)>=1.2 && fabs(lep_eta)<2.1) bin = 2;
        if (fabs(lep_eta)>=2.1 && fabs(lep_eta)<2.4) bin = 3;
    }
    
    return bin;
}

std::vector<int> HistContainer::getDoubleFakeBin(float lep1_pt, float lep1_eta, int lep1_id, float lep2_pt, float lep2_eta, int lep2_id) {
    // pt: {10.,15.,20.,25.,35.,50.,70.,90.},
    // eta: {0.,0.8,1.479,2.5}
    vector<int> ret = {0,0};
    int lep1_ptBin = 0;
    int lep1_etaBin = 0;
    int lep2_ptBin = 0;
    int lep2_etaBin = 0;

    if (lep1_pt>=10 && lep1_pt<15) lep1_ptBin = 1;
    if (lep1_pt>=15 && lep1_pt<20) lep1_ptBin = 2;
    if (lep1_pt>=20 && lep1_pt<25) lep1_ptBin = 3;
    if (lep1_pt>=25 && lep1_pt<35) lep1_ptBin = 4;
    if (lep1_pt>=35 && lep1_pt<50) lep1_ptBin = 5;
    if (lep1_pt>=50 && lep1_pt<70) lep1_ptBin = 6;
    if (lep1_pt>=70) lep1_ptBin = 7;

    if (lep2_pt>=10 && lep2_pt<15) lep2_ptBin = 1;
    if (lep2_pt>=15 && lep2_pt<20) lep2_ptBin = 2;
    if (lep2_pt>=20 && lep2_pt<25) lep2_ptBin = 3;
    if (lep2_pt>=25 && lep2_pt<35) lep2_ptBin = 4;
    if (lep2_pt>=35 && lep2_pt<50) lep2_ptBin = 5;
    if (lep2_pt>=50 && lep2_pt<70) lep2_ptBin = 6;
    if (lep2_pt>=70) lep2_ptBin = 7;

    if(lep1_id==11){
        if (fabs(lep1_eta)>=0.000 && fabs(lep1_eta)<0.800) lep1_etaBin = 1;
        if (fabs(lep1_eta)>=0.800 && fabs(lep1_eta)<1.479) lep1_etaBin = 2;
        if (fabs(lep1_eta)>=1.479 && fabs(lep1_eta)<2.500) lep1_etaBin = 3;
    }else{
        if (fabs(lep1_eta)>=0.000 && fabs(lep1_eta)<1.2) lep1_etaBin = 1;
        if (fabs(lep1_eta)>=1.2 && fabs(lep1_eta)<2.1) lep1_etaBin = 2;
        if (fabs(lep1_eta)>=2.1 && fabs(lep1_eta)<2.4) lep1_etaBin = 3;
    }

    if(lep2_id==11){
        if (fabs(lep2_eta)>=0.000 && fabs(lep2_eta)<0.800) lep2_etaBin = 1;
        if (fabs(lep2_eta)>=0.800 && fabs(lep2_eta)<1.479) lep2_etaBin = 2;
        if (fabs(lep2_eta)>=1.479 && fabs(lep2_eta)<2.500) lep2_etaBin = 3;
    }else{
        if (fabs(lep2_eta)>=0.000 && fabs(lep2_eta)<1.2) lep2_etaBin = 1;
        if (fabs(lep2_eta)>=1.2 && fabs(lep2_eta)<2.1) lep2_etaBin = 2;
        if (fabs(lep2_eta)>=2.1 && fabs(lep2_eta)<2.4) lep2_etaBin = 3;
    }


    ret[0]=((lep1_ptBin)+(7*(lep1_etaBin-1)));
    ret[1]=((lep2_ptBin)+(7*(lep2_etaBin-1)));


    return ret;
}

std::vector<int> HistContainer::getDoubleFlipBin(float lep1_pt, float lep1_eta, float lep2_pt, float lep2_eta) {
    // ptbins {15., 40., 60., 80., 100., 200., 300.};
    // etabins {0., 0.8, 1.479, 2.5};
    vector<int> ret = {0,0};
    int lep1_ptBin = 0;
    int lep1_etaBin = 0;
    int lep2_ptBin = 0;
    int lep2_etaBin = 0;

    if (lep1_pt>=15 && lep1_pt<40) lep1_ptBin = 1;
    if (lep1_pt>=40 && lep1_pt<60) lep1_ptBin = 2;
    if (lep1_pt>=60 && lep1_pt<80) lep1_ptBin = 3;
    if (lep1_pt>=80 && lep1_pt<100) lep1_ptBin = 4;
    if (lep1_pt>=100 && lep1_pt<200) lep1_ptBin = 5;
    if (lep1_pt>=200) lep1_ptBin = 6;

    if (lep1_pt>=15 && lep1_pt<40) lep2_ptBin = 1;
    if (lep1_pt>=40 && lep1_pt<60) lep2_ptBin = 2;
    if (lep1_pt>=60 && lep1_pt<80) lep2_ptBin = 3;
    if (lep1_pt>=80 && lep1_pt<100) lep2_ptBin = 4;
    if (lep1_pt>=100 && lep1_pt<200) lep2_ptBin = 5;
    if (lep1_pt>=200) lep2_ptBin = 6;

    if (fabs(lep1_eta)>=0.000 && fabs(lep1_eta)<0.800) lep1_etaBin = 1;
    if (fabs(lep1_eta)>=0.800 && fabs(lep1_eta)<1.479) lep1_etaBin = 2;
    if (fabs(lep1_eta)>=1.479 && fabs(lep1_eta)<2.500) lep1_etaBin = 3;

    if (fabs(lep2_eta)>=0.000 && fabs(lep2_eta)<0.800) lep2_etaBin = 1;
    if (fabs(lep2_eta)>=0.800 && fabs(lep2_eta)<1.479) lep2_etaBin = 2;
    if (fabs(lep2_eta)>=1.479 && fabs(lep2_eta)<2.500) lep2_etaBin = 3;


    ret[0]=((lep1_ptBin)+(6*(lep1_etaBin-1)));
    ret[1]=((lep2_ptBin)+(6*(lep2_etaBin-1)));
    // cout << "xbin: " << ret[0] << "  ybin: " << ret[1] << endl;


    return ret;
}


void HistContainer::addHist1d(std::string quantity, std::string sample, int nbins, float xmin, float xmax, std::string region) {

    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH1D *hist = new TH1D(hname.c_str(),htitle.c_str(),nbins,xmin,xmax);
            hists1d_[htitle] = hist;
        }
    }
    else {
    //     TString tregion(region);
    //     //cout << tregion << endl;
    //     TObjArray* objarray = tregion.Tokenize(" ");
    //     std::vector<std::string> regions;
    //     for (auto obj : *objarray) {
    //         regions.push_back( ((TString*)obj)->Data() );
    //         cout <<  ((TString*)obj)->Data()  << endl;
    //     }
    //     for (auto name : regions) {
    //         cout << name << endl;
    //         std::string htitle = name+"_"+quantity+"_"+sample;
    //         std::string hname = "h_"+name+"_"+quantity+"_"+sample;
    //         TH1D *hist = new TH1D(hname.c_str(),htitle.c_str(),nbins,xmin,xmax);
    //         hists1d_[htitle] = hist;
    //         cout << htitle << "  " << hname << endl;
    //     }
    // }
        
        std::string htitle = region+"_"+quantity+"_"+sample;
        std::string hname = "h_"+region+"_"+quantity+"_"+sample;
        TH1D *hist = new TH1D(hname.c_str(),htitle.c_str(),nbins,xmin,xmax);
        hists1d_[htitle] = hist;
        //cout << htitle << "  " << hname << endl;
    }
    return;
}
void HistContainer::addHist1d(std::string quantity, std::string sample, int nbins, std::vector<double> xbins, std::string region) {

    float xbinsarr[nbins+1];
    for (uint i=0; i<xbins.size(); i++){
        xbinsarr[i] = xbins[i];
    }
    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH1D *hist = new TH1D(hname.c_str(),htitle.c_str(),nbins,xbinsarr);
            hists1d_[htitle] = hist;
        }
    }
    else {

        std::string htitle = region+"_"+quantity+"_"+sample;
        std::string hname = "h_"+region+"_"+quantity+"_"+sample;
        TH1D *hist = new TH1D(hname.c_str(),htitle.c_str(),nbins,xbinsarr);
        hists1d_[htitle] = hist;
        //cout << htitle << "  " << hname << endl;
    }
    return;
}

void HistContainer::addHist2d(std::string quantity, std::string sample, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, std::string region) {
    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH2D *hist = new TH2D(hname.c_str(),htitle.c_str(),nbinsx,xmin,xmax,nbinsy,ymin,ymax);
            hists2d_[htitle] = hist;
        }
    }
    else {
        std::string htitle = region+"_"+quantity+"_"+sample;
        std::string hname = "h_"+region+"_"+quantity+"_"+sample;
        TH2D *hist = new TH2D(hname.c_str(),htitle.c_str(),nbinsx,xmin,xmax,nbinsy,ymin,ymax);
        hists2d_[htitle] = hist;
    }
    return;
}

void HistContainer::addHist2d(std::string quantity, std::string sample, int nbinsx, int nbinsy, std::vector<float> xbins, std::vector<float> ybins, std::string region) {
    float xbinsarr[nbinsx+1];
    float ybinsarr[nbinsy+1];
    for (uint i=0; i<xbins.size(); i++){
        xbinsarr[i] = xbins[i];
    }
    for (uint j=0; j<ybins.size(); j++){
        ybinsarr[j] = ybins[j];
    }
    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            TH2D *hist = new TH2D(hname.c_str(),htitle.c_str(),nbinsx,xbinsarr,nbinsy,ybinsarr);
            hists2d_[htitle] = hist;
        }
    }
    else {
        std::string htitle = region+"_"+quantity+"_"+sample;
        std::string hname = "h_"+region+"_"+quantity+"_"+sample;
        TH2D *hist = new TH2D(hname.c_str(),htitle.c_str(),nbinsx,xbinsarr,nbinsy,ybinsarr);
        hists2d_[htitle] = hist;
    }
    return;
}

void HistContainer::addHist4d(std::string quantity, std::string sample, int nbinsx, int nbinsy, std::vector<double> xedges, std::vector<double> yedges, std::string region) {
    const Int_t bins[4] = {nbinsx, nbinsy, nbinsx, nbinsy};
    const Double_t mins[4] = {xedges[0], yedges[0], xedges[0], yedges[0]};
    const Double_t maxs[4] = {xedges[nbinsx+1], yedges[nbinsy+1], xedges[nbinsx+1], yedges[nbinsy+1]};

    Double_t ptbins[nbinsx+1];
    Double_t etabins[nbinsy+1];
    for(uint i = 0; i<xedges.size(); i++){ptbins[i] = xedges[i];}
    for(uint i = 0; i<yedges.size(); i++){etabins[i] = yedges[i];}

    if (region=="") {
        for (auto name : region_names_) {
            std::string htitle = name+"_"+quantity+"_"+sample;
            std::string hname = "h_"+name+"_"+quantity+"_"+sample;
            THnF *hist = new THnF(hname.c_str(),htitle.c_str(),4,bins,mins,maxs);
            hist->SetBinEdges(0,ptbins);
            hist->SetBinEdges(1,etabins);
            hist->SetBinEdges(2,ptbins);
            hist->SetBinEdges(3,etabins);
            // TH2D* hist2D = hist->Projection(1,0);
            // cout << hist2D->GetNbinsX() << " " << hist2D->GetNbinsY() << " " << hist2D->GetXaxis()->GetBinLowEdge(1) << " " << hist2D->GetXaxis()->GetBinLowEdge(6) << endl;
            hists4d_[htitle] = hist;
        }
    }
    else {
        std::string htitle = region+"_"+quantity+"_"+sample;
        std::string hname = "h_"+region+"_"+quantity+"_"+sample;
        THnF *hist = new THnF(hname.c_str(),htitle.c_str(),4,bins,mins,maxs);
        hists4d_[htitle] = hist;
    }
    return;
}

void HistContainer::loadHists(std::string sample) {
    addHist1d("njets",sample,5,-0.5,4.5);
    addHist1d("nbjets",sample,3,-0.5,2.5);
    addHist1d("nleps",sample,5,-0.5,4.5);
    // addHist1d("neles",sample,5,-0.5,4.5);
    // addHist1d("nmus",sample,5,-0.5,4.5);
    // // addHist1d("nvtxs",sample,100,0,100);
    // // addHist1d("elpt_emu",sample,100,0,200);
    addHist1d("llpt",sample,100,0,200);
    addHist1d("ltpt",sample,100,0,200);
    addHist1d("thirdlpt",sample,100,0,200);
    addHist1d("lleta",sample,100,-5.,-5.);
    addHist1d("lteta",sample,100,-5.,-5.);
    addHist1d("thirdleta",sample,100,-5.,-5.);
    addHist1d("lldxy",sample,100,0.,1.);
    addHist1d("ltdxy",sample,100,0.,1.);
    addHist1d("thirdldxy",sample,100,0.,1.);
    addHist1d("lldz",sample,100,0.,1.);
    addHist1d("ltdz",sample,100,0.,1.);
    addHist1d("thirdldz",sample,100,0.,1.);
    addHist1d("llminiiso",sample,16,0.,0.4);
    addHist1d("ltminiiso",sample,16,0.,0.4);
    addHist1d("mll",sample,100,0,200);
    addHist1d("mbl",sample,100,0,200);
    // // // // addHist1d("flipSF_inclMET_mee",sample,20,70,110);
    // // // // addHist1d("flipSF_l50MET_mee",sample,20,70,110);
    // // // addHist1d("flipSF_l50MET_mee",sample,35,55,125);
    // // // addHist1d("flipSF_inclMET_njets",sample,7,-0.5,6.5);
    // // // addHist1d("flipSF_inclMET_nbjets",sample,5,-0.5,4.5);
    // // // addHist1d("flipSF_l50MET_njets",sample,7,-0.5,6.5);
    // // // addHist1d("flipSF_l50MET_nbjets",sample,5,-0.5,4.5);
    addHist1d("ljpt",sample,50,0,500);
    addHist1d("tjpt",sample,50,0,500);
    addHist1d("thirdjpt",sample,50,0,500);
    addHist1d("fwjpt",sample,50,0,500);
    addHist1d("ljbscore",sample,20,0,1);
    addHist1d("tjbscore",sample,20,0,1);
    addHist1d("thirdjbscore",sample,20,0,1);
    addHist1d("lbpt",sample,50,0,500);    
    addHist1d("lbscore",sample,20,0,1);    
    addHist1d("ht",sample,50,0,1000);
    addHist1d("met",sample,20,0,400);
    addHist1d("mt_ll_met",sample,20,0,400);
    addHist1d("mt_tl_met",sample,20,0,400);
    addHist1d("mt_thirdl_met",sample,20,0,400);
    // addHist1d("cutflow",sample,7,0.5,7.5,"br");
    addHist1d("sr",sample,21,0.5,21.5);//,"br");
    addHist1d("ljcscore",sample,20,0,1);
    addHist1d("tjcscore",sample,20,0,1);
    addHist1d("thirdjcscore",sample,20,0,1);
    // addHist1d("weight",sample,40,0,2);
    // addHist1d("sr_syst",sample,21,0.5,21.5);//,"br");
    // addHist1d("lj_syst_bscore",sample,20,0,1);
    // addHist1d("tj_syst_bscore",sample,20,0,1);
    // addHist1d("thirdj_syst_bscore",sample,20,0,1);
    // addHist1d("njOnZ",sample,5,-0.5,4.5);
    // addHist1d("nbjOnZ",sample,3,-0.5,2.5);
    // addHist1d("mOnZ",sample,20,0,400);
    // addHist1d("zll",sample,20,70,110);
    // addHist1d("bdtScoreOnZ_hct2016",sample,20,hct2016bins_);//,"br");
    // addHist1d("bdtScoreOnZ_hut2016",sample,20,hut2016bins_);//,"br");
    // addHist1d("bdtScoreOnZ_hct2017",sample,20,hct2017bins_);//,"br");
    // addHist1d("bdtScoreOnZ_hut2017",sample,20,hut2017bins_);//,"br");
    // addHist1d("bdtScoreOnZ_hct2018",sample,20,hct2018bins_);//,"br");
    // addHist1d("bdtScoreOnZ_hut2018",sample,20,hut2018bins_);//,"br");
    addHist1d("bdtScore_hct2016",sample,20,hct2016bins_);//,"br");
    addHist1d("bdtScore_hut2016",sample,20,hut2016bins_);//,"br");
    addHist1d("bdtScore_hct2017",sample,20,hct2017bins_);//,"br");
    addHist1d("bdtScore_hut2017",sample,20,hut2017bins_);//,"br");
    addHist1d("bdtScore_hct2018",sample,20,hct2018bins_);//,"br");
    addHist1d("bdtScore_hut2018",sample,20,hut2018bins_);//,"br");
    // addHist1d("bdtScore_evenBins_hct",sample,20,0,1);//,"br");
    // addHist1d("bdtScore_evenBins_hut",sample,20,0,1);//,"br");
    // addHist2d("wvshct",sample,40,0,2,20,0,1);//,"br");
    // addHist2d("wvshut",sample,40,0,2,20,0,1);//,"br");
    // addHist1d("bdtScore_syst_hct2016",sample,20,hct2016bins_);//,"br");
    // addHist1d("bdtScore_syst_hut2016",sample,20,hut2016bins_);//,"br");
    // addHist1d("bdtScore_syst_hct2017",sample,20,hct2017bins_);//,"br");
    // addHist1d("bdtScore_syst_hut2017",sample,20,hut2017bins_);//,"br");
    // addHist1d("bdtScore_syst_hct2018",sample,20,hct2018bins_);//,"br");
    // addHist1d("bdtScore_syst_hut2018",sample,20,hut2018bins_);//,"br");
    // // // // addHist1d("flipSFcr_inclMET",sample,18,0.5,18.5);//,"br");
    // // // // addHist1d("flipSFcr_l50MET",sample,18,0.5,18.5);//,"br");
    addHist1d("fakecr",sample,21,0.5,21.5);//,"br");
    // addHist2d("fake2dcr_efake",sample,7,3,{10.,15.,20.,25.,35.,50.,70.,90.},{0,1,2,3});//,"br");
    // addHist2d("fake2dcr_mfake",sample,7,3,{10.,15.,20.,25.,35.,50.,70.,90.},{0,1,2,3});//,"br");
    // addHist2d("fake2dcr_eefake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_emfake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_mmfake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_hct_efake",sample,7,3,{10.,15.,20.,25.,35.,50.,70.,90.},{0,1,2,3});//,"br");
    // addHist2d("fake2dcr_hct_mfake",sample,7,3,{10.,15.,20.,25.,35.,50.,70.,90.},{0,1,2,3});//,"br");
    // addHist2d("fake2dcr_hct_eefake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_hct_emfake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_hct_mmfake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_hut_efake",sample,7,3,{10.,15.,20.,25.,35.,50.,70.,90.},{0,1,2,3});//,"br");
    // addHist2d("fake2dcr_hut_mfake",sample,7,3,{10.,15.,20.,25.,35.,50.,70.,90.},{0,1,2,3});//,"br");
    // addHist2d("fake2dcr_hut_eefake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_hut_emfake",sample,21,0,21,21,0,21);
    // addHist2d("fake2dcr_hut_mmfake",sample,21,0,21,21,0,21);
    // addHist2d("flip2dcr",sample,6,3,{15., 40., 60., 80., 100., 200., 300.},{0., 0.8, 1.479, 2.5});//,"br");
    // addHist2d("flip2d2ecr",sample,18,0,18,18,0,18);//,"br");
    // addHist2d("flip2d_hct_cr",sample,6,3,{15., 40., 60., 80., 100., 200., 300.},{0., 0.8, 1.479, 2.5});//,"br");
    // addHist2d("flip2d_hct_2ecr",sample,18,0,18,18,0,18);//,"br");
    // addHist2d("flip2d_hut_cr",sample,6,3,{15., 40., 60., 80., 100., 200., 300.},{0., 0.8, 1.479, 2.5});//,"br");
    // addHist2d("flip2d_hut_2ecr",sample,18,0,18,18,0,18);//,"br");
    addHist1d("flipcr",sample,21,0.5,21.5);//,"br");
    // // // addHist1d("flavorChannel",sample,4,0.5,4.5);//,"br");

    // addHist1d("valSR_flip",sample,21,0.5,21.5,"vrsr_flip");
    // addHist1d("valCR_flip",sample,21,0.5,21.5,"vrcr_flip");
    // addHist1d("valCRest_flip",sample,21,0.5,21.5,"vrcrest_flip");
    // // // addHist1d("valSR_flip_eeChan",sample,21,0.5,21.5,"vrsr_flip");
    // // // addHist1d("valCR_flip_eeChan",sample,21,0.5,21.5,"vrcr_flip");
    // // // addHist1d("valCRest_flip_eeChan",sample,21,0.5,21.5,"vrcrest_flip");
    // // // addHist1d("valSR_flip_emChan",sample,21,0.5,21.5,"vrsr_flip");
    // // // addHist1d("valCR_flip_emChan",sample,21,0.5,21.5,"vrcr_flip");
    // // // addHist1d("valCRest_flip_emChan",sample,21,0.5,21.5,"vrcrest_flip");

    // addHist1d("vrsr",sample,21,0.5,21.5,"vrsr");
    // addHist1d("vrcr",sample,21,0.5,21.5,"vrcr");
    // addHist1d("vrcrest",sample,21,0.5,21.5,"vrcrest");
    // // addHist1d("vrsr_ee",sample,21,0.5,21.5,"vrsr");
    // // addHist1d("vrcr_ee",sample,21,0.5,21.5,"vrcr");
    // // addHist1d("vrcrest_ee",sample,21,0.5,21.5,"vrcrest");
    // // addHist1d("vrsr_mm",sample,21,0.5,21.5,"vrsr");
    // // addHist1d("vrcr_mm",sample,21,0.5,21.5,"vrcr");
    // // addHist1d("vrcrest_mm",sample,21,0.5,21.5,"vrcrest");
    // // addHist1d("vrsr_em",sample,21,0.5,21.5,"vrsr");
    // // addHist1d("vrcr_em",sample,21,0.5,21.5,"vrcr");
    // // addHist1d("vrcrest_em",sample,21,0.5,21.5,"vrcrest");
    // // addHist1d("vrsr_me",sample,21,0.5,21.5,"vrsr");
    // // addHist1d("vrcr_me",sample,21,0.5,21.5,"vrcr");
    // // addHist1d("vrcrest_me",sample,21,0.5,21.5,"vrcrest");
    return;
}

void HistContainer::sumw2() {
    std::map<std::string,TH1D*>::iterator it1d;
    std::map<std::string,TH2D*>::iterator it2d;
    std::map<std::string,THnF*>::iterator it4d;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {it1d->second->Sumw2();}
    for (it2d=hists2d_.begin();it2d!=hists2d_.end();it2d++) {it2d->second->Sumw2();}
    for (it4d=hists4d_.begin();it4d!=hists4d_.end();it4d++) {it4d->second->Sumw2();}
    return;
}

void HistContainer::write() {
    std::map<std::string,TH1D*>::iterator it1d;
    std::map<std::string,TH2D*>::iterator it2d;
    std::map<std::string,THnF*>::iterator it4d;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {it1d->second->Write();}
    for (it2d=hists2d_.begin();it2d!=hists2d_.end();it2d++) {it2d->second->Write();}
    for (it4d=hists4d_.begin();it4d!=hists4d_.end();it4d++) {it4d->second->Write();}
    return;
}

void HistContainer::fill1d(std::string quantity, std::string region, std::string sample, float value, float weight) {
    std::map<std::string,TH1D*>::iterator it1d;
    // cout << quantity << " " << region << " " << sample << endl;
    for (it1d=hists1d_.begin();it1d!=hists1d_.end();it1d++) {
        //cout << it1d->first << endl;
        if (it1d->first.find(sample)==std::string::npos)  continue;
        if (it1d->first.find(quantity)==std::string::npos) continue;
        if (it1d->first.find(region)==std::string::npos) continue;
        if (region.find("pp")==std::string::npos && it1d->first.find("pp")!=std::string::npos) continue;
        if (region.find("est")==std::string::npos && it1d->first.find("est")!=std::string::npos) continue;
        if (quantity.find("mll")!=std::string::npos){
            if (region.find("ml")==std::string::npos && (it1d->first.find("mlsf")!=std::string::npos||it1d->first.find("mldf")!=std::string::npos)) continue;
        }else{
            if (region.find("ml")==std::string::npos && it1d->first.find("ml")!=std::string::npos) continue;
        }
        if (region.find("vr")==std::string::npos && it1d->first.find("vr")!=std::string::npos) continue;
        if (quantity.find("Chan")==std::string::npos && it1d->first.find("Chan")!=std::string::npos) continue;
        it1d->second->Fill(value,weight);
        // cout << "filled " << it1d->first << " with weight " << weight << " for event " << nt.event() << " in bin " << value << endl;
        /*if (region.find("vrcr")!=std::string::npos){
            std::cout << "Filling hist " << quantity << " with value " << value << " and weight " << weight << std::endl;
        }*/
    }
}

void HistContainer::fill2d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float weight) {
    // cout << xvalue << " " << yvalue << " " << quantity << " " << region << " " << sample << endl;
    std::map<std::string,TH2D*>::iterator it2d;
    for (it2d=hists2d_.begin();it2d!=hists2d_.end();it2d++) {
        if (it2d->first.find(sample)==std::string::npos)  continue;
        // cout << "passed sample cut " << it2d->first << endl;
        if (it2d->first.find(quantity)==std::string::npos) continue;
        // cout << "passed quantity cut " << it2d->first << endl;
        if (it2d->first.find(region)==std::string::npos) continue;
        // cout << "passed region cut " << it2d->first << endl;
        if (region.find("pp")==std::string::npos && it2d->first.find("pp")!=std::string::npos) continue;
        // cout << "passed pp cut " << it2d->first << endl;
        if (region.find("est")==std::string::npos && it2d->first.find("est")!=std::string::npos) continue;
        // cout << "passed est cut " << it2d->first << endl;
        if (region.find("ml")==std::string::npos && it2d->first.find("ml")!=std::string::npos) continue;
        // cout << "passed ml cut " << it2d->first << endl;
        if (it2d->first.find(quantity)!=std::string::npos) {
            // cout << it2d->first << endl;
            it2d->second->Fill(xvalue,yvalue,weight);
        }
        // cout << "filled " << it2d->first << " with weight " << weight << " for event " << nt.event() << endl;
        // cout << "filled " << it2d->first << " in bin " << xvalue << ", " << yvalue << "   " << it2d->second->FindBin(xvalue,yvalue) << endl;
    }
}

void HistContainer::fill4d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float zvalue, float tvalue, float weight) {
    const Double_t bin[4] = {xvalue,yvalue,zvalue,tvalue};
    std::map<std::string,THnF*>::iterator it4d;
    for (it4d=hists4d_.begin();it4d!=hists4d_.end();it4d++) {
        if (it4d->first.find(sample)==std::string::npos)  continue;
        if (it4d->first.find(quantity)==std::string::npos) continue;
        if (it4d->first.find(region)==std::string::npos) continue;
        if (region.find("pp")==std::string::npos && it4d->first.find("pp")!=std::string::npos) continue;
        if (region.find("est")==std::string::npos && it4d->first.find("est")!=std::string::npos) continue;
        if (region.find("ml")==std::string::npos && it4d->first.find("ml")!=std::string::npos) continue;
        if (it4d->first.find(quantity)!=std::string::npos) {
            // cout << it4d->first << endl;
            it4d->second->Fill(bin,weight);
        }
        // cout << "filled " << it4d->first << " with weight " << weight << " for event " << nt.event() << endl;
    }
}

float get_sum_pt(Jets  &jets) {
    float ret = 0.;
    for (unsigned int idx=0; idx<jets.size();idx++) {
        ret += jets[idx].pt();
    }
    return ret;
}

void HistContainer::fill(std::string sample, int best_hyp_type, Leptons &leps, Jets &jets, Jets &bjets, 
                        float met, float metphi, bool isVR_SR_fake, bool isVR_CR_fake, bool isVR_SR_flip, bool isVR_CR_flip, 
                        bool isEE, bool isEM, bool isME, bool isMM, bool isEFake, bool isMFake, bool isEE_flip, 
                        bool isEM_flip, float hct_pred, float hut_pred, float weight, float crWeight,
                        bool doVariations, std::map<std::string, float> variationMap) {
    float fillWeight = 0;
    bool fillFakeCR = false;
    // fill 1d histograms first
    std::string rname = getRegionName(best_hyp_type,jets.size(),bjets.size());
    // std::cout << "SR: " << rname << std::endl;
    std::vector<std::string> rnames = {rname};
    if(doVariations){rnames = getRegionNames();}
    std::vector<std::string> brmap = {"ml","ss"};
    if ( rname=="ml" || rname=="ss") rnames.push_back("br");
    if ( rname=="os" ) {rnames.push_back("osest");}
    if ( rname=="mlsf" ) {rnames.push_back("mlsfest");}
    if ( rname=="sf" ) {rnames.push_back("sfest");}
    if ( rname=="df" ) {rnames.push_back("dfest");}
    if ( rname=="mldf" ) {rnames.push_back("mldfest");}
    if ( rname=="sf"||rname=="df"||rname=="mlsf"||rname=="mldf" ) {fillFakeCR = true;}
    //if ( rname=="vrcr_sf"||rname=="vrcr_df"||rname=="vrcr_mlsf"||rname=="vrcr_mldf" ) {fillFakeVRCR = true;}
    //if ( rname=="vrsr_sf"||rname=="vrsr_df"||rname=="vrsr_mlsf"||rname=="vrsr_mldf" ) {fillFakeVRSR = true;}
    //std::cout << "# SRs: " << rnames.size() << std::endl;
    int njets=jets.size();
    int nbjets=bjets.size();
    int nleps=leps.size();
    int neles=0;
    int nmus=0;
    int nPrompt=0;
    int flavChannelVal = 0;
    int ntight = 0;
    int nloose = 0;
    bool onZPeak = 0;
    bool diEl = 0;
    bool isSS = 0;
    Leptons fakeLeps;
    Leptons flipLeps;
    std::vector<int> bin;
    for (auto lep: leps) {
        if(lep.idlevel()==SS::IDLevel::IDtight){ntight++;}
        if(lep.idlevel()<SS::IDLevel::IDtight){nloose++;}
        if (lep.genPartFlav()==1 || lep.genPartFlav()==15){nPrompt++;}

        if (lep.absid()==11){
            neles++;
            if(lep.idlevel()==SS::IDLevel::IDfakable && lep.idlevel()!=SS::IDLevel::IDtight){fakeLeps.push_back(lep);}
            if(lep.idlevel()==SS::IDLevel::IDtight){flipLeps.push_back(lep);}
        }
        else if (lep.absid()==13){
            nmus++;
            if(lep.idlevel()==SS::IDLevel::IDfakable && lep.idlevel()!=SS::IDLevel::IDtight){fakeLeps.push_back(lep);}
        }
    }
    if(neles==2&&nmus==0){flavChannelVal=1;}
    else if(neles==0&&nmus==2){flavChannelVal=2;}
    else if(neles==1&&nmus==1&&leps[0].absid()==11){flavChannelVal=3;}
    else if(neles==1&&nmus==1&&leps[0].absid()==13){flavChannelVal=4;}

    float mostForwardJet = 0;
    float mostForwardPt = 0;
    for (auto j: jets){
        if(abs(j.eta())>mostForwardJet){
            mostForwardJet = abs(j.eta());
            mostForwardPt = j.pt();
        }
    }

    float mt_LeadLep_MET, mt_SubLeadLep_MET, mt_SubSubLeadLep_MET;
    mt_LeadLep_MET = TMath::Sqrt(2*leps[0].pt()*met * (1 - TMath::Cos(leps[0].phi()-metphi)));
    mt_SubLeadLep_MET = TMath::Sqrt(2*leps[1].pt()*met * (1 - TMath::Cos(leps[1].phi()-metphi)));
    if(leps.size()>2){mt_SubSubLeadLep_MET = TMath::Sqrt(2*leps[2].pt()*met * (1 - TMath::Cos(leps[2].phi()-metphi)));}

    float mbl = 0.;
    float mass = 0.;
    if(leps.size()==2 && (leps[0].p4()+leps[1].p4()).M()>75 && (leps[0].p4()+leps[1].p4()).M()<105){
    // if(leps.size()==2 && (leps[0].p4()+leps[1].p4()).M()>55 && (leps[0].p4()+leps[1].p4()).M()<125){
        onZPeak=1;
        mass = (leps[0].p4()+leps[1].p4()).M();
    }
    if(leps.size()==2 && leps[0].absid()==11 && leps[1].absid()==11){diEl=1;}
    if(leps.size()==2 && leps[0].charge()==leps[1].charge()){isSS=1;}

    bool trilepOnZ = 0;
    float zll_val = 0.;
    if(ntight==3 && nloose==0){
        if( (leps[0].p4()+leps[1].p4()).M()>75 && (leps[0].p4()+leps[1].p4()).M()<105 && 
            leps[0].charge()+leps[1].charge()==0 && leps[0].absid()==leps[1].absid() ) {
            trilepOnZ=1;
            zll_val = (leps[0].p4()+leps[1].p4()).M();
        }
        if( (leps[0].p4()+leps[2].p4()).M()>75 && (leps[0].p4()+leps[2].p4()).M()<105 && 
            leps[0].charge()+leps[2].charge()==0 && leps[0].absid()==leps[2].absid() ) {
            trilepOnZ=1;
            zll_val = (leps[0].p4()+leps[2].p4()).M();
        }
        if( (leps[1].p4()+leps[2].p4()).M()>75 && (leps[1].p4()+leps[2].p4()).M()<105 && 
            leps[1].charge()+leps[2].charge()==0 && leps[1].absid()==leps[2].absid() ) {
            trilepOnZ=1;
            zll_val = (leps[1].p4()+leps[2].p4()).M();
        }
    }

    if ( rname=="sf" && nPrompt==2 ){
        rnames.push_back("sfpp");
        rnames.push_back("sfppest");}
    if ( rname=="df" && nPrompt==2 ){
        rnames.push_back("dfpp");
        rnames.push_back("dfppest");}
    if ( rname=="mlsf" && nPrompt==3 ){
        rnames.push_back("mlsfppp");
        rnames.push_back("mlsfpppest");}
    if ( rname=="mldf" && nPrompt==3 ){
        rnames.push_back("mldfppp");
        rnames.push_back("mldfpppest");}

    for (auto name : rnames) {
        if(onZPeak && diEl && isSS){continue;}

        //for filling systematic variations:
        if(doVariations && (best_hyp_type==2 || best_hyp_type==4) ){
            int sr = getSR(best_hyp_type,njets,nbjets);
            fill1d("sr_syst",name,sample,sr,variationMap[name]);
            fill1d("lj_syst_bscore",name,sample,jets[0].bdisc(),variationMap[name]);
            if(njets>=2){fill1d("tj_syst_bscore",name,sample,jets[1].bdisc(),variationMap[name]);}
            if(njets>=3){fill1d("thirdj_syst_bscore",name,sample,jets[2].bdisc(),variationMap[name]);}
            if(hct_pred!=-999){fill1d("bdtScore_syst_hct",name,sample,hct_pred,variationMap[name]);}
            if(hut_pred!=-999){fill1d("bdtScore_syst_hut",name,sample,hut_pred,variationMap[name]);}
            // cout << "filled " << name << " with weight " << variationMap[name] << endl;
            // if(isnan(variationMap[name])){cout << "nan weight: " << name << " event: " << nt.event() << endl;}
        }

        if (name=="br") {
            counter_++;
            //std::cout << "Filled br histograms for " << counter_ << " time" << std::endl;
        }
        if ( name.find("est")==std::string::npos ) {fillWeight = weight;}
        else if (name.find("est")!=std::string::npos) {fillWeight = crWeight;}

        if(sample=="data" && name.find("est")==std::string::npos && !(fillWeight==1 || fillWeight==0)) {cout << "data weighted! " << weight << " " << crWeight << " " << fillWeight << endl;}

        //std::cout << "Filling histograms for region " << name << std::endl;
        fill1d("njets",name,sample,njets,fillWeight);
        if(nbjets==1){fill1d("nj1b",name,sample,njets,fillWeight);}
        if(nbjets>1){fill1d("nj2b",name,sample,njets,fillWeight);}
        fill1d("flavorChannel",name,sample,flavChannelVal,fillWeight);
        fill1d("nbjets",name,sample,nbjets,fillWeight);
        fill1d("nleps",name,sample,nleps,fillWeight);
        fill1d("neles",name,sample,neles,fillWeight);
        fill1d("nmus",name,sample,nmus,fillWeight);
        fill1d("nvtxs",name,sample,nt.PV_npvsGood(),fillWeight);
        if(hct_pred!=-999){
            fill1d("bdtScore_hct",name,sample,hct_pred,fillWeight);
            fill1d("bdtScore_evenBins_hct",name,sample,hct_pred,fillWeight);
            fill2d("wvshct",name,sample,fillWeight,hct_pred,1);
        }
        if(hut_pred!=-999){
            fill1d("bdtScore_hut",name,sample,hut_pred,fillWeight);
            fill1d("bdtScore_evenBins_hut",name,sample,hut_pred,fillWeight);
            fill2d("wvshut",name,sample,fillWeight,hut_pred,1);
        }
        if(hct_pred!=-999&&trilepOnZ){fill1d("bdtScoreOnZ_hct",name,sample,hct_pred,fillWeight);}
        if(hut_pred!=-999&&trilepOnZ){fill1d("bdtScoreOnZ_hut",name,sample,hut_pred,fillWeight);}
        if((hut_pred!=-999||hct_pred!=-999)&&trilepOnZ){
            fill1d("njOnZ",name,sample,njets,fillWeight);
            fill1d("nbjOnZ",name,sample,nbjets,fillWeight);
            fill1d("mOnZ",name,sample,met,fillWeight);
            fill1d("zll",name,sample,zll_val,fillWeight);
        }
        if(leps.size()==2){
            if ((leps[0].absid()==11&&leps[1].absid()==13)||(leps[0].absid()==13&&leps[1].absid()==11)){fill1d("elpt_emu",name,sample,leps[0].pt(),fillWeight);}
        }
        fill1d("llpt",name,sample,leps[0].pt(),fillWeight);
        fill1d("ltpt",name,sample,leps[1].pt(),fillWeight);
        fill1d("thirdlpt",name,sample,leps[2].pt(),fillWeight);
        fill1d("fwjpt",name,sample,mostForwardPt,fillWeight);
        if (fakeLeps.size()==1){
            float lep1_pt = fakeLeps[0].conecorrpt();
            if(lep1_pt>70){lep1_pt=80.;}
            if (fakeLeps[0].absid()==11){
                float bin = getEtaBin(fakeLeps[0].eta(), fakeLeps[0].absid());
                fill2d("fake2dcr_efake",name,sample,lep1_pt,bin-0.5,fillWeight);
                if(hct_pred!=-999){fill2d("fake2dcr_hct_efake",name,sample,lep1_pt,bin-0.5,fillWeight);}
                if(hut_pred!=-999){fill2d("fake2dcr_hut_efake",name,sample,lep1_pt,bin-0.5,fillWeight);}
            }
            if (fakeLeps[0].absid()==13){
                float bin = getEtaBin(fakeLeps[0].eta(), fakeLeps[0].absid());
                fill2d("fake2dcr_mfake",name,sample,lep1_pt,bin-0.5,fillWeight);
                if(hct_pred!=-999){fill2d("fake2dcr_hct_mfake",name,sample,lep1_pt,bin-0.5,fillWeight);}
                if(hut_pred!=-999){fill2d("fake2dcr_hut_mfake",name,sample,lep1_pt,bin-0.5,fillWeight);}
            }
        }else if (fakeLeps.size() == 2){
            float lep1_pt = fakeLeps[0].conecorrpt();
            if(lep1_pt>70){lep1_pt=80.;}
            float lep2_pt = fakeLeps[1].conecorrpt();
            if(lep2_pt>70){lep2_pt=80.;}
            if (fakeLeps[0].absid()==11 && fakeLeps[1].absid()==11){
                bin = getDoubleFakeBin(lep1_pt,fakeLeps[0].eta(),fakeLeps[0].absid(),lep2_pt,fakeLeps[1].eta(),fakeLeps[1].absid());
                fill2d("fake2dcr_eefake",name,sample,bin[0],bin[1],fillWeight);
                if(hct_pred!=-999){fill2d("fake2dcr_hct_eefake",name,sample,bin[0],bin[1],fillWeight);}
                if(hut_pred!=-999){fill2d("fake2dcr_hut_eefake",name,sample,bin[0],bin[1],fillWeight);}
            }else if (fakeLeps[0].absid()==11 && fakeLeps[1].absid()==13){
                bin = getDoubleFakeBin(lep1_pt,fakeLeps[0].eta(),fakeLeps[0].absid(),lep2_pt,fakeLeps[1].eta(),fakeLeps[1].absid());
                fill2d("fake2dcr_emfake",name,sample,bin[0],bin[1],fillWeight);
                if(hct_pred!=-999){fill2d("fake2dcr_hct_emfake",name,sample,bin[0],bin[1],fillWeight);}
                if(hut_pred!=-999){fill2d("fake2dcr_hut_emfake",name,sample,bin[0],bin[1],fillWeight);}
            }else if (fakeLeps[0].absid()==13 && fakeLeps[1].absid()==11){
                bin = getDoubleFakeBin(lep2_pt,fakeLeps[1].eta(),fakeLeps[1].absid(),lep1_pt,fakeLeps[0].eta(),fakeLeps[0].absid());
                fill2d("fake2dcr_emfake",name,sample,bin[0],bin[1],fillWeight);
                if(hct_pred!=-999){fill2d("fake2dcr_hct_emfake",name,sample,bin[0],bin[1],fillWeight);}
                if(hut_pred!=-999){fill2d("fake2dcr_hut_emfake",name,sample,bin[0],bin[1],fillWeight);}
            }else if (fakeLeps[0].absid()==13 && fakeLeps[1].absid()==13){
                bin = getDoubleFakeBin(lep1_pt,fakeLeps[0].eta(),fakeLeps[0].absid(),lep2_pt,fakeLeps[1].eta(),fakeLeps[1].absid());
                fill2d("fake2dcr_mmfake",name,sample,bin[0],bin[1],fillWeight);
                if(hct_pred!=-999){fill2d("fake2dcr_hct_mmfake",name,sample,bin[0],bin[1],fillWeight);}
                if(hut_pred!=-999){fill2d("fake2dcr_hut_mmfake",name,sample,bin[0],bin[1],fillWeight);}
            }
        }
        if (flipLeps.size()==1){
            float lep1_pt = flipLeps[0].pt();
            if(lep1_pt>200){lep1_pt=250.;}
            fill2d("flip2dcr",name,sample,lep1_pt,abs(flipLeps[0].eta()),fillWeight);
            if(hct_pred!=-999){fill2d("flip2d_hct_cr",name,sample,lep1_pt,abs(flipLeps[0].eta()),fillWeight);}
            if(hut_pred!=-999){fill2d("flip2d_hut_cr",name,sample,lep1_pt,abs(flipLeps[0].eta()),fillWeight);}
        }else if (flipLeps.size()==2){
            // cout << "in double flip loop " << nt.event() << endl;
            bin = getDoubleFlipBin(flipLeps[0].pt(),flipLeps[0].eta(),flipLeps[1].pt(),flipLeps[1].eta());
            // cout << bin[0] << "  " << bin[1] << endl;
            fill2d("flip2d2ecr",name,sample,bin[0],bin[1],fillWeight);
            if(hct_pred!=999){fill2d("flip2d_hct_2ecr",name,sample,bin[0],bin[1],fillWeight);}
            if(hut_pred!=999){fill2d("flip2d_hut_2ecr",name,sample,bin[0],bin[1],fillWeight);}
        }
        fill1d("lleta",name,sample,leps[0].eta(),fillWeight);
        fill1d("lteta",name,sample,leps[1].eta(),fillWeight);
        fill1d("thirdleta",name,sample,leps[2].eta(),fillWeight);
        fill1d("lldxy",name,sample,leps[0].dxy(),fillWeight);
        fill1d("ltdxy",name,sample,leps[1].dxy(),fillWeight);
        fill1d("thirdldxy",name,sample,leps[2].dxy(),fillWeight);
        fill1d("lldz",name,sample,leps[0].dz(),fillWeight);
        fill1d("ltdz",name,sample,leps[1].dz(),fillWeight);
        fill1d("thirdldz",name,sample,leps[2].dz(),fillWeight);
        fill1d("llminiiso",name,sample,leps[0].miniIso(),fillWeight);
        fill1d("ltminiiso",name,sample,leps[1].miniIso(),fillWeight);
        fill1d("ljpt",name,sample,jets[0].pt(),fillWeight);
        fill1d("tjpt",name,sample,jets[1].pt(),fillWeight);
        fill1d("thirdjpt",name,sample,jets[2].pt(),fillWeight);
        fill1d("ljbscore",name,sample,jets[0].bdisc(),fillWeight);
        fill1d("ljcscore",name,sample,jets[0].cdisc(),fillWeight);
        fill1d("weight",name,sample,fillWeight,1);
        // fill1d("tjbscore",name,sample,jets[1].bdisc(),fillWeight);
        if(njets>=2){
            fill1d("tjbscore",name,sample,jets[1].bdisc(),fillWeight);
            fill1d("tjcscore",name,sample,jets[1].cdisc(),fillWeight);
        }
        // else if(nbjets>0){fill1d("tjbscore",name,sample,bjets[0].bdisc(),fillWeight);}
        if(njets>=3){
            fill1d("thirdjbscore",name,sample,jets[2].bdisc(),fillWeight);
            fill1d("thirdjcscore",name,sample,jets[2].cdisc(),fillWeight);
        }
        fill1d("met",name,sample,met,fillWeight);
        if (nbjets>0){
            fill1d("lbpt",name,sample,bjets[0].pt(),fillWeight);
            fill1d("lbscore",name,sample,bjets[0].bdisc(),fillWeight);
            mbl = (leps[0].p4()+bjets[0].p4()).M();
            fill1d("mbl",name,sample,mbl,fillWeight);
        }
        float ht = get_sum_pt(jets);
        fill1d("ht",name,sample,ht,fillWeight);
        fill1d("mt_ll_met",name,sample,mt_LeadLep_MET,fillWeight);
        fill1d("mt_tl_met",name,sample,mt_SubLeadLep_MET,fillWeight);
        if(leps.size()>2){fill1d("mt_thirdl_met",name,sample,mt_SubSubLeadLep_MET,fillWeight);}
        fill1d("mll",name,sample,(leps[0].p4()+leps[1].p4()).M(),fillWeight);
        // if (fillWeight == weight && name != "br"){
        //     //fill weight requirement prevents filling with the estimate weight (i.e. fake or flip weight)
        //     //name requirement prevents double-filling for ss or ml events

        //     //this fills mll 3 times for ml events, so commenting it out
        //     cout << "mll for event: " << nt.event() << endl;
        //     for (unsigned int idx1=0; idx1<leps.size();idx1++) {
        //         cout << "   index 1: " << idx1 << endl;
        //         for (unsigned int idx2=idx1+1; idx2<leps.size();idx2++) {
        //             cout << "   index 2: " << idx2 << endl;
        //             float mass = (leps[idx1].p4()+leps[idx2].p4()).M();
        //             cout << "   mass: " << mass << endl;
        //             fill1d("mll",name,sample,mass,fillWeight);
        //             //cout << "filling mll for event " << nt.event() << " and region " << name << endl;
        //         }
        //     }

        //     //this fills mll with the leading two leptons. because best_hyp is fed to this function, this is the ss or os leptons in 2l events
        //     //FIX ME: probably does not behave how we want for >2l cases
        //     //cout << "leading 2 best_hyps for region " << name << endl;
        //     //cout << "   id 1: " << leps[0].id() << " and id 2: " << leps[1].id() << endl;
        //     mass = (leps[0].p4()+leps[1].p4()).M();
        //     //cout << "   mll: " << mass << endl;
        //     //cout << "   filled mll plot for event " << nt.event() << " with " << mass << endl;
            
        //     // cout << "filling mll for " << name << " " << sample << " " << nt.event() << endl;
        //     fill1d("mll",name,sample,mass,fillWeight);
        // }
        if (name == "br") {

            int sr = getSR(best_hyp_type,njets,nbjets);
            // if(!(diEl&&onZPeak&&isSS)){fill1d("cutflow","br",sample,11,fillWeight);}
            if (sr>=0 && !(diEl && onZPeak && isSS)){

                fill1d("cutflow","br",sample,7,fillWeight);
                // if (nt.MET_pt()>=50){fill1d("cutflow","br",sample,13,fillWeight);}
                // if (nbjets>0){fill1d("cutflow","br",sample,14,fillWeight);}
                // if (nbjets>0&&nt.MET_pt()>=50){fill1d("cutflow","br",sample,15,fillWeight);}

                fill1d("sr",name,sample,sr,fillWeight);
            }
            //int cutflow_counter=4;
            //fill1d("cutflow",name,sample,cutflow_counter,fillWeight);
        } 
        int cr = getCRbin(nleps, njets, nbjets);
        if ((name == "ss"||name == "os"||name == "osest") && onZPeak && diEl){
            //mass = (leps[0].p4()+leps[1].p4()).M();
            fill1d("flipSFcr_inclMET",name,sample,cr,fillWeight);
            if(nbjets==0){
                fill1d("flipSF_inclMET_mee",name,sample,mass,fillWeight);
                fill1d("flipSF_inclMET_njets",name,sample,njets,fillWeight);
                fill1d("flipSF_inclMET_nbjets",name,sample,nbjets,fillWeight);
            }
            float met_ = 0.;
            if(nt.year()==2017){met_=nt.METFixEE2017_T1_pt();}
            else{met_=nt.MET_pt();}
            if(met<50.){
                fill1d("flipSFcr_l50MET",name,sample,cr,fillWeight);
                if(nbjets==0){
                    fill1d("flipSF_l50MET_mee",name,sample,mass,fillWeight);
                    fill1d("flipSF_l50MET_njets",name,sample,njets,fillWeight);
                    fill1d("flipSF_l50MET_nbjets",name,sample,nbjets,fillWeight);
                }
            }
        }
        //fill the fake estimation plots
        if( fillFakeCR ){
            fill1d("fakecr",name,sample,cr,fillWeight);
            //if (isVR_CR_fake){fill1d("vrcr","vrcr_"+name,sample,cr,fillWeight);}
            if (isVR_CR_fake && fillWeight==weight){fill1d("vrcr","vrcr",sample,cr,fillWeight);}
            if (isVR_CR_fake && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest","vrcrest",sample,cr,fillWeight);}
            }
            if ((isEE||isEFake) && isVR_CR_fake && fillWeight==weight){fill1d("vrcr_ee","vrcr",sample,cr,fillWeight);}
            if ((isEE||isEFake) && isVR_CR_fake && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_ee","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_ee","vrcrest",sample,cr,fillWeight);}
            }
            if ((isEM||isMFake) && isVR_CR_fake && fillWeight==weight){fill1d("vrcr_em","vrcr",sample,cr,fillWeight);}
            if ((isEM||isMFake) && isVR_CR_fake && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_em","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_em","vrcrest",sample,cr,fillWeight);}
            }
            if ((isME||isEFake) && isVR_CR_fake && fillWeight==weight){fill1d("vrcr_me","vrcr",sample,cr,fillWeight);}
            if ((isME||isEFake) && isVR_CR_fake && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_me","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_me","vrcrest",sample,cr,fillWeight);}
            }
            if ((isMM||isMFake) && isVR_CR_fake && fillWeight==weight){fill1d("vrcr_mm","vrcr",sample,cr,fillWeight);}
            if ((isMM||isMFake) && isVR_CR_fake && fillWeight==crWeight){
                if (name=="dfest"||name=="mldfest"){
                    fillWeight = -1*fillWeight;
                    fill1d("vrcrest_mm","vrcrest",sample,cr,fillWeight);
                }else{fill1d("vrcrest_mm","vrcrest",sample,cr,fillWeight);}
            }
        }
        //if (isVR_SR_fake){fill1d("vrsr","vrsr_"+name,sample,cr,fillWeight);} 
        if(name == "ss" || name == "ml"){
            if (isVR_SR_fake){fill1d("vrsr","vrsr",sample,cr,fillWeight);}
            if (isVR_SR_fake && (isEE||(nleps==3&&isEFake))){fill1d("vrsr_ee","vrsr",sample,cr,fillWeight);}
            if (isVR_SR_fake && (isEM||(nleps==3&&isMFake))){fill1d("vrsr_em","vrsr",sample,cr,fillWeight);}
            if (isVR_SR_fake && (isME||(nleps==3&&isEFake))){fill1d("vrsr_me","vrsr",sample,cr,fillWeight);}
            if (isVR_SR_fake && (isMM||(nleps==3&&isMFake))){fill1d("vrsr_mm","vrsr",sample,cr,fillWeight);}
        }
        //fill flip estimation plots
        if( name=="os"||name=="osest" ){
            fill1d("flipcr",name,sample,cr,fillWeight);
            if (isVR_CR_flip && fillWeight==weight){fill1d("valCR_flip","vrcr_flip",sample,cr,fillWeight);}
            if (isVR_CR_flip && fillWeight==crWeight){fill1d("valCRest_flip","vrcrest_flip",sample,cr,fillWeight);}
            if (isVR_CR_flip && isEE_flip && fillWeight==weight){fill1d("valCR_flip_eeChan","vrcr_flip",sample,cr,fillWeight);}
            if (isVR_CR_flip && isEE_flip && fillWeight==crWeight){fill1d("valCRest_flip_eeChan","vrcrest_flip",sample,cr,fillWeight);}
            if (isVR_CR_flip && isEM_flip && fillWeight==weight){fill1d("valCR_flip_emChan","vrcr_flip",sample,cr,fillWeight);}
            if (isVR_CR_flip && isEM_flip && fillWeight==crWeight){fill1d("valCRest_flip_emChan","vrcrest_flip",sample,cr,fillWeight);}
        }
        //if (isVR_SR_flip){fill1d("vrsr","vrsr_"+name,sample,cr,fillWeight);} 
        if(name == "ss" || name == "ml"){
            if (isVR_SR_flip){fill1d("valSR_flip","vrsr_flip",sample,cr,fillWeight);}
            if (isVR_SR_flip && isEE_flip){fill1d("valSR_flip_eeChan","vrsr_flip",sample,cr,fillWeight);}
            if (isVR_SR_flip && isEM_flip){fill1d("valSR_flip_emChan","vrsr_flip",sample,cr,fillWeight);}
        }

    } // end loop over regions

    // now fill 2d histograms
    return;
}
