#ifndef HISTCONTAINER_H
#define HISTCONTAINER_H

#include <string>
#include <map>
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THn.h"
#include "../../../NanoTools/NanoCORE/SSSelections.h"

class HistContainer {
    private:
        std::map<std::string, TH1D*> hists1d_;
        std::map<std::string, TH2F*> hists2d_;
        std::map<std::string, THnF*> hists4d_;
        std::vector<std::string> region_names_;
        std::vector<std::string> getRegionNames();
        std::string getRegionName(int hyp_type, int njets, int  nbjets);
        int getSR(int hyp_type, int njets, int nbjets);
        int getCRbin(int nleps, int njets, int nbjets);
        std::vector<int> getDoubleFakeBin(float lep1_pt, float lep1_eta, float lep2_pt, float lep2_eta);
        int counter_;
    public:
        HistContainer () : counter_(0) {region_names_=getRegionNames();}
        void addHist1d(std::string quantity, std::string sample, int nbins, float min, float max, std::string region="");
        void addHist2d(std::string quantity, std::string sample, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, std::string region="");
        void addHist2d(std::string quantity, std::string sample, int nbinsx, int nbinsy, std::vector<float> xbins, std::vector<float> ybins, std::string region="");
        void addHist4d(std::string quantity, std::string sample, int nbinsx, int nbinsy, std::vector<double> xedges, std::vector<double> yedges, std::string region="");
        void loadHists(std::string sample);
        void sumw2();
        void write();
        void fill1d(std::string quantity, std::string region, std::string sample, float value, float weight=1.);
        void fill2d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float weight=1.);
        void fill4d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float zvalue, float tvalue, float weight=1.);
        void fill(std::string sample, int best_hyp_type, Leptons &leps, Jets &jets, Jets &bjets, 
                float met, bool isVR_SR_fake, bool isVR_CR_fake, bool isVR_SR_flip, bool isVR_CR_flip, 
                bool isEE, bool isEM, bool isME, bool isMM, bool isEFake, bool isMFake, bool isEE_flip, 
                bool isEM_flip, float weight=1., float crWeight=1.);
};

#endif