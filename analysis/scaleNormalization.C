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

int findNormalization(TChain *ch, int nevents_to_process=-1)
{

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    TFile* scale_output = new TFile("scaleNormalization.root", "recreate");

    TH1D* h_scale0 = new TH1D("h_scale0", "h_scale0", 100, 0,1000);
    TH1D* h_scale1 = new TH1D("h_scale1", "h_scale1", 100, 0,1000);
    TH1D* h_scale2 = new TH1D("h_scale2", "h_scale2", 100, 0,1000);
    TH1D* h_scale3 = new TH1D("h_scale3", "h_scale3", 100, 0,1000);
    TH1D* h_scale4 = new TH1D("h_scale4", "h_scale4", 100, 0,1000);
    TH1D* h_scale5 = new TH1D("h_scale5", "h_scale5", 100, 0,1000);
    TH1D* h_scale6 = new TH1D("h_scale6", "h_scale6", 100, 0,1000);

    h_scale0->Sumw2();
    h_scale1->Sumw2();
    h_scale2->Sumw2();
    h_scale3->Sumw2();
    h_scale4->Sumw2();
    h_scale5->Sumw2();
    h_scale6->Sumw2();

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

            //LHEScaleWeight indicies: 0,1,3,4,5,7,8
            //central is index 4

            h_scale0->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[4]);
            h_scale1->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[0]);
            h_scale2->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[1]);
            h_scale3->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[3]);
            h_scale4->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[5]);
            h_scale5->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[7]);
            h_scale6->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEScaleWeight()[8]);

            if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;
        }
        if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;

        delete file;

    }

    cout << "central: " << h_scale0->Integral() << endl;
    cout << "scale1: " << h_scale1->Integral() << "    " << h_scale0->Integral()/h_scale1->Integral() << endl;
    cout << "scale2: " << h_scale2->Integral() << "    " << h_scale0->Integral()/h_scale2->Integral() << endl;
    cout << "scale3: " << h_scale3->Integral() << "    " << h_scale0->Integral()/h_scale3->Integral() << endl;
    cout << "scale4: " << h_scale4->Integral() << "    " << h_scale0->Integral()/h_scale4->Integral() << endl;
    cout << "scale5: " << h_scale5->Integral() << "    " << h_scale0->Integral()/h_scale5->Integral() << endl;
    cout << "scale6: " << h_scale6->Integral() << "    " << h_scale0->Integral()/h_scale6->Integral() << endl;


    scale_output->cd();
    h_scale0->Write();
    h_scale1->Write();
    h_scale2->Write();
    h_scale3->Write();
    h_scale4->Write();
    h_scale5->Write();
    h_scale6->Write();

    scale_output->Close();

    bar.finish();

    return 0;
}
