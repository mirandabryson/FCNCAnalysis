#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"

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

int findKappa()
{

    string outdir = "./kappaCalculationOutputs/";
    map<string,float> limits = {
        {"tch2016",0.3350},
        {"tch2017",0.3281},
        {"tch2018",0.2236},
        {"tuh2016",0.2764},
        {"tuh2017",0.2666},
        {"tuh2018",0.1782},
        {"tchRun2",0.1616},
        {"tuhRun2",0.1260},
        {"samsTUHRun2",0.019},
        {"tch2016_bdt",0.1724},
        {"tch2017_bdt",0.1182},
        {"tch2018_bdt",0.1060},
        {"tuh2016_bdt",0.1523},
        {"tuh2017_bdt",0.0972},
        {"tuh2018_bdt",0.0933},
        {"tchRun2_bdt",0.0684},
        {"tuhRun2_bdt",0.0610}
    };
    map<string,float> minus1sigma = {
        {"tch2016",0.2409},
        {"tch2017",0.2360},
        {"tch2018",0.1603},
        {"tuh2016",0.2001},
        {"tuh2017",0.1946},
        {"tuh2018",0.1290},
        {"tchRun2",0.1162},
        {"tuhRun2",0.0909},
        {"tch2016_bdt",0.1193},
        {"tch2017_bdt",0.0815},
        {"tch2018_bdt",0.0731},
        {"tuh2016_bdt",0.1049},
        {"tuh2017_bdt",0.0670},
        {"tuh2018_bdt",0.0640},
        {"tchRun2_bdt",0.0473},
        {"tuhRun2_bdt",0.0423}
    };
    map<string,float> plus1sigma = {
        {"tch2016",0.4698},
        {"tch2017",0.4563},
        {"tch2018",0.3137},
        {"tuh2016",0.3854},
        {"tuh2017",0.3665},
        {"tuh2018",0.2478},
        {"tchRun2",0.2273},
        {"tuhRun2",0.1757},
        {"tch2016_bdt",0.2582},
        {"tch2017_bdt",0.1785},
        {"tch2018_bdt",0.1600},
        {"tuh2016_bdt",0.2282},
        {"tuh2017_bdt",0.1471},
        {"tuh2018_bdt",0.1397},
        {"tchRun2_bdt",0.1024},
        {"tuhRun2_bdt",0.0912}
    };
    map<string,float> minus2sigma = {
        {"tch2016",0.1806},
        {"tch2017",0.1769},
        {"tch2018",0.1197},
        {"tuh2016",0.1511},
        {"tuh2017",0.1468},
        {"tuh2018",0.0975},
        {"tchRun2",0.0871},
        {"tuhRun2",0.0684},
        {"tch2016_bdt",0.0875},
        {"tch2017_bdt",0.0595},
        {"tch2018_bdt",0.0534},
        {"tuh2016_bdt",0.0774},
        {"tuh2017_bdt",0.0490},
        {"tuh2018_bdt",0.0470},
        {"tchRun2_bdt",0.0347},
        {"tuhRun2_bdt",0.0310}
    };
    map<string,float> plus2sigma = {
        {"tch2016",0.6349},
        {"tch2017",0.6065},
        {"tch2018",0.4267},
        {"tuh2016",0.5152},
        {"tuh2017",0.4810},
        {"tuh2018",0.3317},
        {"tchRun2",0.3068},
        {"tuhRun2",0.2364},
        {"tch2016_bdt",0.3818},
        {"tch2017_bdt",0.2654},
        {"tch2018_bdt",0.2379},
        {"tuh2016_bdt",0.3375},
        {"tuh2017_bdt",0.2184},
        {"tuh2018_bdt",0.2077},
        {"tchRun2_bdt",0.1514},
        {"tuhRun2_bdt",0.1347}
    };

    float gamma_t = 1.32158;
    float gamma_hqt = 0.1904;

    cout << "central kappas: " << endl;
    for (const auto& [key, limit]:limits){
        cout << key << "\t" << sqrt((limit/100.)*(gamma_t/gamma_hqt)) << endl;
    }

    cout << endl << "plus1sigma kappas: " << endl;
    for (const auto& [key, plus1sigma]:plus1sigma){
        cout << key << "\t" << sqrt((plus1sigma/100.)*(gamma_t/gamma_hqt)) << endl;
    }

    cout << endl << "minus1sigma kappas: " << endl;
    for (const auto& [key, minus1sigma]:minus1sigma){
        cout << key << "\t" << sqrt((minus1sigma/100.)*(gamma_t/gamma_hqt)) << endl;
    }

    vector<string> years = {"2016","2017","2018","Run2"};

    for (int y = 0; y < years.size(); y++){
        TGraph *gr_2sigma = new TGraph();
        TGraph *gr_1sigma = new TGraph();
        // TGraph *gr_2sigma_kappa = new TGraph();
        // TGraph *gr_1sigma_kappa = new TGraph();

        TF1 *f_limits = new TF1("f_limits","[0]*x+[1]",0,limits["tuh"+years[y]]);
        // TF1 *f_kappa = new TF1("f_limits","sqrt((x/100)*[0])",0,limits["tuh"+years[y]]);

        f_limits->SetLineColor(kBlack);
        // f_kappa->SetLineColor(kBlack);

        TCanvas *c_limits = new TCanvas("c_limits", "limits", 600,600);
        // TCanvas *c_kappa = new TCanvas("c_kappa", "kappa", 600,600);
        float slope_limits = limits["tch"+years[y]]/(-limits["tuh"+years[y]]);

        f_limits->SetParameter(0,slope_limits);
        f_limits->SetParameter(1,limits["tch"+years[y]]);
        // f_kappa->SetParameter(0,gamma_t/gamma_hqt);

        c_limits->cd();
        gr_2sigma->SetFillColor(kYellow);
        gr_2sigma->SetFillStyle(1001);
        f_limits->Draw();
        f_limits->GetYaxis()->SetRangeUser(0.,0.7);
        f_limits->GetHistogram()->GetXaxis()->SetLimits(0.,plus2sigma["tuh"+years[y]]);
        f_limits->GetHistogram()->SetTitle("Limits");
        f_limits->GetHistogram()->GetXaxis()->SetTitle("BR(tuH)");
        f_limits->GetHistogram()->GetYaxis()->SetTitle("BR(tcH)");
        f_limits->GetHistogram()->Draw("");
        gr_2sigma->SetPoint(0,0,plus2sigma["tch"+years[y]]);
        gr_2sigma->SetPoint(1,plus2sigma["tuh"+years[y]],0);
        gr_2sigma->SetPoint(2,minus2sigma["tuh"+years[y]],0);
        gr_2sigma->SetPoint(3,0,minus2sigma["tch"+years[y]]);
        gr_2sigma->Draw("f");
        gr_2sigma->GetXaxis()->SetRangeUser(0.0,1.0);

        gr_1sigma->SetFillColor(kGreen);
        gr_1sigma->SetFillStyle(1001);
        gr_1sigma->SetPoint(0,0,plus1sigma["tch"+years[y]]);
        gr_1sigma->SetPoint(1,plus1sigma["tuh"+years[y]],0);
        gr_1sigma->SetPoint(2,minus1sigma["tuh"+years[y]],0);
        gr_1sigma->SetPoint(3,0,minus1sigma["tch"+years[y]]);
        gr_1sigma->Draw("f");

        f_limits->Draw("SAME");

        TLegend *leg = new TLegend(0.9,0.7,0.48,0.9);
        leg->AddEntry("gr_2sigma","+/- 2 sigma","f");
        leg->AddEntry("gr_1sigma","+/- 1 sigma","f");
        leg->AddEntry("f_limits","Expected Limits");
        leg->Draw();


        // c_kappa->cd();
        // gr_2sigma_kappa->SetFillColor(kYellow);
        // gr_2sigma_kappa->SetFillStyle(1001);
        // f_kappa->Draw();
        // f_kappa->GetYaxis()->SetRangeUser(0.,0.7);
        // f_kappa->GetHistogram()->GetXaxis()->SetLimits(0.,plus2sigma["tuh"+years[y]]);
        // f_kappa->GetHistogram()->Draw("");
        // gr_2sigma_kappa->SetPoint(0,0,f_kappa->Eval(plus2sigma["tch"+years[y]]));
        // gr_2sigma_kappa->SetPoint(1,f_kappa->Eval(plus2sigma["tuh"+years[y]]),0);
        // gr_2sigma_kappa->SetPoint(2,f_kappa->Eval(minus2sigma["tuh"+years[y]]),0);
        // gr_2sigma_kappa->SetPoint(3,0,f_kappa->Eval(minus2sigma["tch"+years[y]]));
        // gr_2sigma_kappa->Draw("fc");
        // gr_2sigma_kappa->GetXaxis()->SetRangeUser(0.0,1.0);

        // gr_1sigma_kappa->SetFillColor(kGreen);
        // gr_1sigma_kappa->SetFillStyle(1001);
        // gr_1sigma_kappa->SetPoint(0,0,f_kappa->Eval(plus1sigma["tch"+years[y]]));
        // gr_1sigma_kappa->SetPoint(1,f_kappa->Eval(plus1sigma["tuh"+years[y]]),0);
        // gr_1sigma_kappa->SetPoint(2,f_kappa->Eval(minus1sigma["tuh"+years[y]]),0);
        // gr_1sigma_kappa->SetPoint(3,0,f_kappa->Eval(minus1sigma["tch"+years[y]]));
        // gr_1sigma_kappa->Draw("fc");

        // f_kappa->Draw("SAME");

        c_limits->SaveAs(TString::Format("%slimits%s.pdf",outdir.c_str(),years[y].c_str()).Data());
        // c_kappa->SaveAs(TString::Format("%skappa%s.pdf",outdir.c_str(),years[y].c_str()).Data());
        delete c_limits;
        // delete c_kappa;
    }

    return 0;
}
