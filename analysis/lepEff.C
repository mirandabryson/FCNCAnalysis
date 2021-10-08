#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/MetSelections.h"
#include "../../NanoTools/NanoCORE/Tools/JetCorrector.h"
#include "../../NanoTools/NanoCORE/tqdm.h"
#include "../../NanoTools/NanoCORE/Config.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"

#include <iostream>
#include <iomanip>

// #define DEBUG

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
    #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
    #define debug(args...)
#endif

using namespace std;
using namespace tas;

int ScanChain(TChain *ch, int nevents_to_process=-1)
{

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    TFile* eff_output = new TFile("lepeff.root", "recreate");

    Double_t ptbins[10] = {20., 30., 50., 70., 100., 140., 200., 300., 600., 1000.};
    //Double_t ptbins[18] = {20., 25., 30., 35., 40., 45., 50., 60., 70., 80., 90., 100., 120., 150., 200., 300., 400., 600.};
    //Double_t etabins[8] = {0., 0.4, 0.8, 1.2, 1.6, 2., 2.4, 2.8};

    TString algo = "DeepJet";

    TH1D* h2_ElectronEff_Denom = new TH1D("h2_Electron_Denom", TString::Format("lepton efficiency, Denominator, MC, %s, b-jets, #eta vs p_{T}", algo.Data()).Data(), 9, ptbins);
    TH1D* h2_MuonEff_Denom = new TH1D("h2_Muon_Denom", TString::Format("lepton efficiency, Denominator, MC, %s loose, c-jets, #eta vs p_{T}", algo.Data()).Data(), 9, ptbins);
    TH1D* h2_ElectronEff_Num = new TH1D("h2_Electron_tight_Num", TString::Format("lepton efficiency, Numerator, MC, %s tight, b-jets, #eta vs p_{T}", algo.Data()).Data(), 9, ptbins);
    TH1D* h2_MuonEff_Num = new TH1D("h2_Muon_tight_Num", TString::Format("lepton efficiency, Numerator, MC, %s tight, c-jets, #eta vs p_{T}", algo.Data()).Data(), 9, ptbins);
    TH1D* h2_ElectronEff_Eff = new TH1D("h2_Electron_loose_Eff", TString::Format("lepton efficiency, Numerator, MC, %s loose, c-jets, #eta vs p_{T}", algo.Data()).Data(), 9, ptbins);
    TH1D* h2_MuonEff_Eff = new TH1D("h2_Muon_loose_Eff", TString::Format("lepton efficiency, Numerator, MC, %s loose, b-jets, #eta vs p_{T}", algo.Data()).Data(), 9, ptbins);
    
    h2_ElectronEff_Denom->Sumw2();
    h2_MuonEff_Denom->Sumw2();
    h2_ElectronEff_Num->Sumw2();
    h2_MuonEff_Num->Sumw2();
    h2_ElectronEff_Eff->Sumw2();
    h2_MuonEff_Eff->Sumw2();

    while ( (currentFile = (TFile*)fileIter.Next()) )
    {
        TFile *file = TFile::Open( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        TString filename(currentFile->GetTitle());

        tree->SetCacheSize(32*1024*1024);
        tree->SetCacheLearnEntries(100);

        nt.Init(tree);

        // Set up the NanoCORE's common configuration service tool
        gconf.GetConfigs(nt.year());

        for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event)
        {

            nt.GetEntry(event);
            tree->LoadTree(event);

            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            Leptons leptons = getLeptons();
            int nLeps = leptons.size();
            //cout << nLeps << endl;
            for (auto lep : leptons){
                if (lep.genPartFlav()==1||lep.genPartFlav()==15){
                    if (lep.absid()==11){
                        h2_ElectronEff_Denom->Fill(lep.pt());
                        //if (lep.idlevel()==SS::IDLevel::IDfakable||lep.idlevel()==SS::IDLevel::IDtight){
                        if (lep.idlevel()==SS::IDLevel::IDtight){
                            h2_ElectronEff_Num->Fill(lep.pt());
                        }
                    }else if(lep.absid()==13){
                        h2_MuonEff_Denom->Fill(lep.pt());
                        //if (lep.idlevel()==SS::IDLevel::IDfakable||lep.idlevel()==SS::IDLevel::IDtight){
                        if (lep.idlevel()==SS::IDLevel::IDtight){
                            h2_MuonEff_Num->Fill(lep.pt());
                        }
                    }
                }
            }

            if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;
        }
        if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;

        delete file;

    }

    h2_ElectronEff_Eff->Divide(h2_ElectronEff_Num, h2_ElectronEff_Denom, 1, 1, "B");
    h2_MuonEff_Eff->Divide(h2_MuonEff_Num, h2_MuonEff_Denom, 1, 1, "B");

    eff_output->cd();
    h2_ElectronEff_Denom->Write();
    h2_MuonEff_Denom->Write();
    h2_ElectronEff_Num->Write();
    h2_MuonEff_Num->Write();
    h2_ElectronEff_Eff->Write();
    h2_MuonEff_Eff->Write();

    eff_output->Close();

    bar.finish();

    return 0;
}
