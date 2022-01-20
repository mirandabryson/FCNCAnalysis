#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TCanvas.h"
// #include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

int normalization(std::string inputDir)
{
    std::vector<std::string> years = {"2016", "2017", "2018"};
    // std::vector<std::string> years = {"2016"};

    for (int y = 0; y < years.size(); y++){

        TString tch_fileName = inputDir+"/signal_tch_"+years[y]+"_hists.root";
        TString tuh_fileName = inputDir+"/signal_tuh_"+years[y]+"_hists.root";
        TString rares_fileName = inputDir+"/rares_"+years[y]+"_hists.root";
        TString fakes_fileName = inputDir+"/fakes_mc_"+years[y]+"_hists.root";
        TString flips_fileName = inputDir+"/flips_mc_"+years[y]+"_hists.root";

        std::vector<TString> samples = {tch_fileName,tuh_fileName/*,rares_fileName*/,fakes_fileName,flips_fileName};
        std::vector<std::string> sampNames = {"signal_tch", "signal_tuh"/*, "rares"*/, "fakes_mc", "flips_mc"};

        for(int s = 0; s < samples.size(); s++){
            TFile *inFile = new TFile(samples[s].Data());

            TH1D* tchBDT_temp;
            TH1D* tuhBDT_temp;

            // std::cout << "inside sample loop" << std::endl;
            // std::cout << typeid(samples[s]).name() << std::endl;

            TString tchName = "h_br_bdtScore_hct"+years[y]+"_"+sampNames[s];
            TString tuhName = "h_br_bdtScore_hut"+years[y]+"_"+sampNames[s];

            tchBDT_temp = (TH1D*) inFile->Get(tchName.Data());
            tuhBDT_temp = (TH1D*) inFile->Get(tuhName.Data());

            TH1D* tchBDT = (TH1D*) tchBDT_temp->Clone();
            TH1D* tuhBDT = (TH1D*) tuhBDT_temp->Clone();

            std::cout << "year:\t" << years[y] << std::endl;
            std::cout << "sample:\t" << sampNames[s] << std::endl;
            std::cout << "tch integral:\t" << tchBDT->Integral() << std::endl;
            std::cout << "tuh integral:\t" << tuhBDT->Integral() << std::endl;
            std::cout << "tch integral:\t" << tchBDT->Integral(0,21) << std::endl;
            std::cout << "tuh integral:\t" << tuhBDT->Integral(0,21) << std::endl;
        }
    }
    return 0;
}
