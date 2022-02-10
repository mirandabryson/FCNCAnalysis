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
#include "TKey.h"

#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

int sumhists(std::string inputDir)
{
    std::vector<std::string> years = {"2016", "2017", "2018"};
    // std::vector<std::string> years = {"2016"};

    for (int y = 0; y < years.size(); y++){
        //output file
        TString outputName = inputDir+"/rares_"+years[y]+"_hists.root";
        TFile* outfile = new TFile(outputName.Data(),"recreate");

        cout << "made outfile" << endl;

        //input file names
        TString xg_fileName = inputDir+"/xg_"+years[y]+"_hists.root";
        TString ttvv_fileName = inputDir+"/ttvv_"+years[y]+"_hists.root";
        TString ttx_fileName = inputDir+"/ttx_"+years[y]+"_hists.root";
        TString multiboson_fileName = inputDir+"/multiboson_"+years[y]+"_hists.root";
        TString smallRares_fileName = inputDir+"/smallRares_"+years[y]+"_hists.root";
        TString tthh_fileName = inputDir+"/tthh_"+years[y]+"_hists.root";
        TString ttw_fileName = inputDir+"/ttw_"+years[y]+"_hists.root";

        //load input files
        TFile* infile_xg = new TFile(xg_fileName.Data());
        TFile* infile_ttvv = new TFile(ttvv_fileName.Data());
        TFile* infile_ttx = new TFile(ttx_fileName.Data());
        TFile* infile_multiboson = new TFile(multiboson_fileName.Data());
        TFile* infile_smallRares = new TFile(smallRares_fileName.Data());
        TFile* infile_tthh = new TFile(tthh_fileName.Data());
        TFile* infile_ttw = new TFile(ttw_fileName.Data());

        cout << "loaded input files" << endl;

        //Get list of histograms
        TList *listofkeys =infile_xg->GetListOfKeys();
        TIter histIter(listofkeys);
        TH1D * currentHist = 0;

        //Iterate through histogram names
        while( (currentHist = (TH1D*)histIter.Next()) ){
            //get basic histogram name
            string histName = currentHist->GetName();
            string histTitle = currentHist->GetTitle();
            histName.pop_back();
            histName.pop_back();
            histTitle.pop_back();
            histTitle.pop_back();

            //skip any histograms from wrong year
            if(histName.find(years[y])==std::string::npos) continue;

            cout << "working on histogram " << histName << " with title " << histTitle << endl;

            //names for each subcategory
            TString histName_xg = histName + "xg";
            TString histName_ttvv = histName + "ttvv";
            TString histName_ttx = histName + "ttx";
            TString histName_multiboson = histName + "multiboson";
            TString histName_smallRares = histName + "smallRares";
            TString histName_tthh = histName + "tthh";
            TString histName_ttw = histName + "ttw";

            //get each histogram
            TH1D* hist_xg_temp = (TH1D*) infile_xg->Get(histName_xg.Data());
            TH1D* hist_ttvv_temp = (TH1D*) infile_ttvv->Get(histName_ttvv.Data());
            TH1D* hist_ttx_temp = (TH1D*) infile_ttx->Get(histName_ttx.Data());
            TH1D* hist_multiboson_temp = (TH1D*) infile_multiboson->Get(histName_multiboson.Data());
            TH1D* hist_smallRares_temp = (TH1D*) infile_smallRares->Get(histName_smallRares.Data());
            TH1D* hist_tthh_temp = (TH1D*) infile_tthh->Get(histName_tthh.Data());
            TH1D* hist_ttw_temp = (TH1D*) infile_ttw->Get(histName_ttw.Data());

            //clone each histogram
            TH1D* hist_xg = (TH1D*) hist_xg_temp->Clone();
            TH1D* hist_ttvv = (TH1D*) hist_ttvv_temp->Clone();
            TH1D* hist_ttx = (TH1D*) hist_ttx_temp->Clone();
            TH1D* hist_multiboson = (TH1D*) hist_multiboson_temp->Clone();
            TH1D* hist_smallRares = (TH1D*) hist_smallRares_temp->Clone();
            TH1D* hist_tthh = (TH1D*) hist_tthh_temp->Clone();
            TH1D* hist_ttw = (TH1D*) hist_ttw_temp->Clone();

            cout << "cloned all necessary histograms" << endl;

            //make new rares histogram
            int nBins = hist_xg->GetNbinsX();
            Float_t hist_edges[nBins];
            for(int n = 0; n<nBins+1; n++){
                hist_edges[n]=(hist_xg->GetBinLowEdge(n+1));
            }
            TString histName_rares = histName+"rares";
            TString histTitle_rares = histTitle+"rares";

            cout << "making rares th1d with " << nBins << " bins and " << hist_edges << "edges" << endl;

            TH1D* hist_rares = new TH1D(histName_rares.Data(), histTitle_rares.Data(),nBins,hist_edges);
            hist_rares->Add(hist_xg);
            hist_rares->Add(hist_ttvv);
            hist_rares->Add(hist_ttx);
            hist_rares->Add(hist_multiboson);
            hist_rares->Add(hist_smallRares);
            hist_rares->Add(hist_tthh);
            hist_rares->Add(hist_ttw);

            cout << "added histograms" << endl;

            outfile->cd();
            hist_rares->Write();

            cout << "wrote histograms to outfile" << endl;
        }
    }
    return 0;
}
