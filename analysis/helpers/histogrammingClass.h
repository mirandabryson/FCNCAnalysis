#ifndef HISTCONTAINER_H
#define HISTCONTAINER_H

#include <string>
#include <map>
#include "TH1F.h"
#include "TH2F.h"
#include "../../../NanoTools/NanoCORE/SSSelections.h"

class HistContainer {
    private:
        std::map<std::string, TH1F*> hists1d_;
        std::map<std::string, TH2F*> hists2d_;
        std::vector<std::string> region_names_;
        std::vector<std::string> getRegionNames();
        std::string getRegionName(int hyp_type, int njets, int  nbjets);
        int getSR(int hyp_type, int njets, int nbjets);
        int counter_;
    public:
        HistContainer () : counter_(0) {region_names_=getRegionNames();}
        void addHist1d(std::string quantity, std::string sample, int nbins, float min, float max, std::string region="");
        void addHist2d(std::string quantity, std::string sample, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, std::string region="");
        void loadHists(std::string sample);
        void sumw2();
        void write();
        void fill1d(std::string quantity, std::string region, std::string sample, float value, float weight=1.);
        void fill2d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float weight=1.);
        void fill(std::string sample, int best_hyp_type, Leptons &leps, Jets &jets, Jets &bjets, float met, float weight=1.);
};

#endif