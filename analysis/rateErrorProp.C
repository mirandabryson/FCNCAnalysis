#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "THn.h"
#include "TTree.h"
// #include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

// #include "../../NanoTools/NanoCORE/Nano.h"
// #include "../../NanoTools/NanoCORE/MetSelections.h"
// #include "../../NanoTools/NanoCORE/Tools/JetCorrector.h"
// #include "../../NanoTools/NanoCORE/tqdm.h"
// #include "../../NanoTools/NanoCORE/Config.h"
// #include "../../NanoTools/NanoCORE/SSSelections.h"

#include <iostream>
#include <iomanip>

// #define DEBUG

// struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
// #ifdef DEBUG
//     #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
// #else
//     #define debug(args...)
// #endif

using namespace std;
// using namespace tas;

TH2D* onesHistogram(Double_t xbins[8], Double_t ybins[4]){
    TH2D* hist_ones = new TH2D("hist_ones","ones",7,xbins,3,ybins);
    hist_ones->SetBinContent(1,1,1);
    hist_ones->SetBinContent(1,2,1);
    hist_ones->SetBinContent(1,3,1);
    hist_ones->SetBinContent(2,1,1);
    hist_ones->SetBinContent(2,2,1);
    hist_ones->SetBinContent(2,3,1);
    hist_ones->SetBinContent(3,1,1);
    hist_ones->SetBinContent(3,2,1);
    hist_ones->SetBinContent(3,3,1);
    hist_ones->SetBinContent(4,1,1);
    hist_ones->SetBinContent(4,2,1);
    hist_ones->SetBinContent(4,3,1);
    hist_ones->SetBinContent(5,1,1);
    hist_ones->SetBinContent(5,2,1);
    hist_ones->SetBinContent(5,3,1);
    hist_ones->SetBinContent(6,1,1);
    hist_ones->SetBinContent(6,2,1);
    hist_ones->SetBinContent(6,3,1);
    hist_ones->SetBinContent(7,1,1);
    hist_ones->SetBinContent(7,2,1);
    hist_ones->SetBinContent(7,3,1);

    hist_ones->SetBinError(1,1,0);
    hist_ones->SetBinError(1,2,0);
    hist_ones->SetBinError(1,3,0);
    hist_ones->SetBinError(2,1,0);
    hist_ones->SetBinError(2,2,0);
    hist_ones->SetBinError(2,3,0);
    hist_ones->SetBinError(3,1,0);
    hist_ones->SetBinError(3,2,0);
    hist_ones->SetBinError(3,3,0);
    hist_ones->SetBinError(4,1,0);
    hist_ones->SetBinError(4,2,0);
    hist_ones->SetBinError(4,3,0);
    hist_ones->SetBinError(5,1,0);
    hist_ones->SetBinError(5,2,0);
    hist_ones->SetBinError(5,3,0);
    hist_ones->SetBinError(6,1,0);
    hist_ones->SetBinError(6,2,0);
    hist_ones->SetBinError(6,3,0);
    hist_ones->SetBinError(7,1,0);
    hist_ones->SetBinError(7,2,0);
    hist_ones->SetBinError(7,3,0);
    return hist_ones;

}

TH2D* fillFakeRateHistos(TH2D* inputHisto, string year, string flavor){
    map<vector<int>,vector<float>> electron2016 = {
        {{1,1},{0,0}},{{1,2},{0,0}},{{1,3},{0,0}},
        {{2,1},{0.3017,0.0176}},{{2,2},{0.2834,0.0194}},{{2,3},{0.3555,0.0179}},
        {{3,1},{0.1231,0.0122}},{{3,2},{0.1661,0.0133}},{{3,3},{0.1847,0.0125}},
        {{4,1},{0.1141,0.0078}},{{4,2},{0.1455,0.0080}},{{4,3},{0.1769,0.0072}},
        {{5,1},{0.1586,0.0197}},{{5,2},{0.1496,0.0158}},{{5,3},{0.2030,0.0120}},
        {{6,1},{0.2071,0.0526}},{{6,2},{0.2136,0.0364}},{{6,3},{0.2754,0.0252}},
        {{7,1},{0.3802,0.0991}},{{7,2},{0.2779,0.0805}},{{7,3},{0.2837,0.0449}},
    };
    map<vector<int>,vector<float>> muon2016 = {
        {{1,1},{0.3816,0.0084}},{{1,2},{0.4318,0.0108}},{{1,3},{0.4678,0.0226}},
        {{2,1},{0.1133,0.0057}},{{2,2},{0.1290,0.0077}},{{2,3},{0.1554,0.0176}},
        {{3,1},{0.0789,0.0064}},{{3,2},{0.0940,0.0085}},{{3,3},{0.1229,0.0210}},
        {{4,1},{0.0585,0.0019}},{{4,2},{0.0697,0.0028}},{{4,3},{0.0927,0.0074}},
        {{5,1},{0.0668,0.0042}},{{5,2},{0.0662,0.0051}},{{5,3},{0.0916,0.0147}},
        {{6,1},{0.0704,0.0149}},{{6,2},{0.0829,0.0175}},{{6,3},{0.0723,0.0567}},
        {{7,1},{0.1255,0.0413}},{{7,2},{0.0928,0.0585}},{{7,3},{0.0723,0.0567}},
    };
    map<vector<int>,vector<float>> electron2017 = {
        {{1,1},{0,0}},{{1,2},{0,0}},{{1,3},{0,0}},
        {{2,1},{0.399488,0.114166}},{{2,2},{0.30978,0.156868}},{{2,3},{0.434417,0.117958}},
        {{3,1},{0.134325,0.0453808}},{{3,2},{0.0698102,0.0352557}},{{3,3},{0.176644,0.0566433}},
        {{4,1},{0.0666072,0.01179}},{{4,2},{0.0726379,0.0100706}},{{4,3},{0.127929,0.0137488}},
        {{5,1},{0.0813633,0.0263784}},{{5,2},{0.0947138,0.0220817}},{{5,3},{0.117984,0.0182064}},
        {{6,1},{0.200698,0.0541985}},{{6,2},{0.211528,0.0440799}},{{6,3},{0.202261,0.0301305}},
        {{7,1},{0.179335,0.123434}},{{7,2},{0.214949,0.976225}},{{7,3},{0.335536,0.480083}},
    };
    map<vector<int>,vector<float>> muon2017 = {
        {{1,1},{0,0}},{{1,2},{0,0}},{{1,3},{0,0}},
        {{2,1},{0.456206,0.0663701}},{{2,2},{0.503331,0.0774233}},{{2,3},{0.753583,0.0135457}},
        {{3,1},{0.134961,0.0231227}},{{3,2},{0.201255,0.0318872}},{{3,3},{0.240394,0.0620985}},
        {{4,1},{0.0547376,0.00367513}},{{4,2},{0.0825245,0.00574265}},{{4,3},{0.116965,0.0144333}},
        {{5,1},{0.0320002,0.00574265}},{{5,2},{0.052804,0.00751073}},{{5,3},{0.0977246,0.02035}},
        {{6,1},{0.0326371,0.0173518}},{{6,2},{0.079594,0.0193193}},{{6,3},{0.170545,0.0532072}},
        {{7,1},{0.00868995,0.0517601}},{{7,2},{0.103198,0.0634385}},{{7,3},{0.136619,0.124799}},
    };
    map<vector<int>,vector<float>> electron2018 = {
        {{1,1},{0,0}},{{1,2},{0,0}},{{1,3},{0,0}},
        {{2,1},{0.321581,0.138818}},{{2,2},{0.279748,0.142993}},{{2,3},{0.276902,0.096636}},
        {{3,1},{0.359608,0.0770031}},{{3,2},{0.108563,0.0515106}},{{3,3},{0.172266,0.0431254}},
        {{4,1},{0.0802729,0.0146179}},{{4,2},{0.0795911,0.0138948}},{{4,3},{0.119644,0.014755}},
        {{5,1},{0.00716674,0.0238178}},{{5,2},{0.0847951,0.0258905}},{{5,3},{0.168389,0.0202859}},
        {{6,1},{0.209688,0.051457}},{{6,2},{0.183851,0.499929}},{{6,3},{0.233879,0.0332461}},
        {{7,1},{0.191903,0.176345}},{{7,2},{0.0190088,0.108516}},{{7,3},{0.398765,0.0539019}},
    };
    map<vector<int>,vector<float>> muon2018 = {
        {{1,1},{0,0}},{{1,2},{0,0}},{{1,3},{0,0}},
        {{2,1},{0.557524,0.0767693}},{{2,2},{0.350328,0.124987}},{{2,3},{0.817892,0.173349}},
        {{3,1},{0.169989,0.0300682}},{{3,2},{0.225226,0.0409736}},{{3,3},{0.295034,0.103006}},
        {{4,1},{0.0474851,0.0045089}},{{4,2},{0.0619445,0.0066539}},{{4,3},{0.0733372,0.0172637}},
        {{5,1},{0.0418475,0.00797379}},{{5,2},{0.0341503,0.00988412}},{{5,3},{0.0882309,0.0250095}},
        {{6,1},{0.0142134,0.0285866}},{{6,2},{0.0684098,0.0275173}},{{6,3},{0.157896,0.0955787}},
        {{7,1},{0.0533669,0.0528893}},{{7,2},{0.172812,0.0818124}},{{7,3},{0.157896,0.0955787}},
    };

    map<vector<int>,vector<float>> fillingMap;
    if (year=="2016"){
        if(flavor=="electron"){fillingMap=electron2016;}
        else if (flavor=="muon"){fillingMap=muon2016;}
    }else if (year == "2017"){
        if(flavor=="electron"){fillingMap=electron2017;}
        else if(flavor=="muon"){fillingMap=muon2017;}
    }else if (year=="2018"){
        if(flavor=="electron"){fillingMap=electron2018;}
        else if(flavor=="muon"){fillingMap=muon2018;}
    }else{std::cout << "shouldn't ever be here! check input to fillFakeRateHistos function!" << std::endl;}

    for(int i = 1; i < inputHisto->GetNbinsX()+1; i++){
        for(int j = 1; j < inputHisto->GetNbinsY()+1; j++){
            vector<int> bin = {i,j};
            if (year == "2016" && flavor=="muon"){cout << bin[0] << " " << bin[1] << " " << fillingMap[bin][0] << endl;}
            inputHisto->SetBinContent(i,j,fillingMap[bin][0]);
            inputHisto->SetBinError(i,j,fillingMap[bin][1]);
        }
    }
    return inputHisto;
}

TH2D* applyFakeRate(TH2D* output, TH2D* CRYields, TH2D* rateHisto, TH2D* ones){
    cout << CRYields->GetBinContent(7,1) << endl;
    cout << rateHisto->GetBinContent(7,1) << endl;
    cout << ones->GetBinContent(7,1) << endl;
    (*output) = (*CRYields)*(*rateHisto);
    cout << output->GetBinContent(7,1) << endl;
    ones->Add(rateHisto,-1);
    cout << ones->GetBinContent(7,1) << endl;
    output->Divide(ones);
    cout << output->GetBinContent(7,1) << endl;
    return output;
}

TH2D* fillDoubleFakeRateHistos(TH2D* fakeRate_lep1, TH2D* fakeRate_lep2, TH2D* ones, string name){
    TH2D* ones_lep1 = (TH2D*) ones->Clone();
    TH2D* ones_lep2 = (TH2D*) ones->Clone();
    ones_lep1->Add(fakeRate_lep1, -1);
    ones_lep2->Add(fakeRate_lep2, -1);
    
    TH2D* fakeWeight_lep1 = (TH2D*) fakeRate_lep1->Clone();
    fakeWeight_lep1->Divide(ones_lep1);
    TH2D* fakeWeight_lep2 = (TH2D*) fakeRate_lep2->Clone();
    fakeWeight_lep2->Divide(ones_lep2);

    TH2D* output = new TH2D(TString::Format("h_doubleFakeWeight_%s",name.c_str()).Data(),TString::Format("h_doubleFakeWeight_%s",name.c_str()).Data(), 21, 0, 21, 21, 0, 21);

    int lep_2_it = 0;
    int lep_1_it = 0;

    for(uint i = 1; i < fakeWeight_lep2->GetNbinsY()+1; i++){
        for(uint j = 1; j < fakeWeight_lep2->GetNbinsX()+1; j++){
            lep_2_it++;
            TH2D* h_temp = (TH2D*) fakeWeight_lep2->Clone();
            for(uint a = 1; a < fakeWeight_lep2->GetNbinsY()+1; a++){
                for(uint b = 1; b < fakeWeight_lep2->GetNbinsX()+1; b++){
                    h_temp->SetBinContent(b,a,fakeWeight_lep2->GetBinContent(j,i));
                    h_temp->SetBinError(b,a,fakeWeight_lep2->GetBinError(j,i));
                }
            }
            h_temp->Multiply(fakeWeight_lep1);
            lep_1_it = 0;
            for(uint a = 1; a < h_temp->GetNbinsY()+1; a++){
                for(uint b = 1; b < h_temp->GetNbinsX()+1; b++){
                    lep_1_it++;
                    output->SetBinContent(lep_1_it,lep_2_it,h_temp->GetBinContent(b,a));
                    output->SetBinError(lep_1_it,lep_2_it,h_temp->GetBinError(b,a));
                }
            }
        }
    }
    return output;
}

TH2D* applyDoubleFakeRate(TH2D* outputHisto, TH2D* inputHisto, TH2D* weightHisto){
    (*outputHisto) = (*inputHisto)*(*weightHisto);
    return outputHisto;
}


int rateMultiplication(std::string inputDir)
{
    TFile* outputFile = new TFile("./fakesProp_hists.root","recreate"); 

    std::vector<std::string> years = {"2016", "2017", "2018"};
    // std::vector<std::string> years = {"2016"};

    Double_t ptbins[8]  = {10., 15., 20., 25., 35., 50., 70., 90.};
    Double_t etabins[4] = {0., 0.8, 1.479, 2.5};

    for (int y = 0; y < years.size(); y++){

        TString fileName = inputDir+"/data_"+years[y]+"_hists.root";

        TFile* inputFile = new TFile(fileName.Data());

        TH2D* sf_e_in_temp = (TH2D*) inputFile->Get("h_sf_fake2dcr_efake_data");
        TH2D* sf_m_in_temp = (TH2D*) inputFile->Get("h_sf_fake2dcr_mfake_data");
        TH2D* mlsf_e_in_temp = (TH2D*) inputFile->Get("h_mlsf_fake2dcr_efake_data");
        TH2D* mlsf_m_in_temp = (TH2D*) inputFile->Get("h_mlsf_fake2dcr_mfake_data");
        TH2D* df_ee_in_temp = (TH2D*) inputFile->Get("h_df_fake2dcr_eefake_data");
        TH2D* df_em_in_temp = (TH2D*) inputFile->Get("h_df_fake2dcr_emfake_data");
        TH2D* df_mm_in_temp = (TH2D*) inputFile->Get("h_df_fake2dcr_mmfake_data");
        TH2D* mldf_ee_in_temp = (TH2D*) inputFile->Get("h_mldf_fake2dcr_eefake_data");
        TH2D* mldf_em_in_temp = (TH2D*) inputFile->Get("h_mldf_fake2dcr_emfake_data");
        TH2D* mldf_mm_in_temp = (TH2D*) inputFile->Get("h_mldf_fake2dcr_mmfake_data");

        TH2D* sf_e_in = (TH2D*) sf_e_in_temp->Clone(TString::Format("h_sf_e_%s",years[y].c_str()).Data());
        TH2D* sf_m_in = (TH2D*) sf_m_in_temp->Clone(TString::Format("h_sf_m_%s",years[y].c_str()).Data());
        TH2D* mlsf_e_in = (TH2D*) mlsf_e_in_temp->Clone(TString::Format("h_mlsf_e_%s",years[y].c_str()).Data());
        TH2D* mlsf_m_in = (TH2D*) mlsf_m_in_temp->Clone(TString::Format("h_mlsf_m_%s",years[y].c_str()).Data());
        TH2D* df_ee_in = (TH2D*) df_ee_in_temp->Clone(TString::Format("h_df_ee_%s",years[y].c_str()).Data());
        TH2D* df_em_in = (TH2D*) df_em_in_temp->Clone(TString::Format("h_df_em_%s",years[y].c_str()).Data());
        TH2D* df_mm_in = (TH2D*) df_mm_in_temp->Clone(TString::Format("h_df_mm_%s",years[y].c_str()).Data());
        TH2D* mldf_ee_in = (TH2D*) mldf_ee_in_temp->Clone(TString::Format("h_mldf_ee_%s",years[y].c_str()).Data());
        TH2D* mldf_em_in = (TH2D*) mldf_em_in_temp->Clone(TString::Format("h_mldf_em_%s",years[y].c_str()).Data());
        TH2D* mldf_mm_in = (TH2D*) mldf_mm_in_temp->Clone(TString::Format("h_mldf_mm_%s",years[y].c_str()).Data());

        TH2D* e_fakeRate_hist = new TH2D(TString::Format("e_fakeRate_%s",years[y].c_str()).Data(),"electron_fakeRate", 7, ptbins, 3, etabins);
        TH2D* m_fakeRate_hist = new TH2D(TString::Format("m_fakeRate_%s",years[y].c_str()).Data(),"muon_fakeRate", 7, ptbins, 3, etabins);
        TH2D* ee_fakeRate_hist = new TH2D(TString::Format("ee_fakeRate_%s",years[y].c_str()).Data(),"ee_fakeRate", 21, 0, 21, 21, 0, 21);
        TH2D* em_fakeRate_hist = new TH2D(TString::Format("em_fakeRate_%s",years[y].c_str()).Data(),"em_fakeRate", 21, 0, 21, 21, 0, 21);
        TH2D* mm_fakeRate_hist = new TH2D(TString::Format("mm_fakeRate_%s",years[y].c_str()).Data(),"mm_fakeRate", 21, 0, 21, 21, 0, 21);

        TH2D* sf_e_hist = new TH2D(TString::Format("sf_e_hist_%s",years[y].c_str()).Data(), "sf_e_flavor_estimate", 7, ptbins, 3, etabins);
        TH2D* sf_m_hist = new TH2D(TString::Format("sf_m_hist_%s",years[y].c_str()).Data(), "sf_m_flavor_estimate", 7, ptbins, 3, etabins);
        TH2D* mlsf_e_hist = new TH2D(TString::Format("mlsf_e_hist_%s",years[y].c_str()).Data(), "mlsf_e_flavor_estimate", 7, ptbins, 3, etabins);
        TH2D* mlsf_m_hist = new TH2D(TString::Format("mlsf_m_hist_%s",years[y].c_str()).Data(), "mlsf_m_flavor_estimate", 7, ptbins, 3, etabins);
        TH2D* df_ee_hist = new TH2D(TString::Format("df_ee_hist_%s",years[y].c_str()).Data(), "df_ee_flavor_estimate", 21, 0, 21, 21, 0, 21);
        TH2D* df_em_hist = new TH2D(TString::Format("df_em_hist_%s",years[y].c_str()).Data(), "df_em_flavor_estimate", 21, 0, 21, 21, 0, 21);
        TH2D* df_mm_hist = new TH2D(TString::Format("df_mm_hist_%s",years[y].c_str()).Data(), "df_mm_flavor_estimate", 21, 0, 21, 21, 0, 21);
        TH2D* mldf_ee_hist = new TH2D(TString::Format("mldf_ee_hist_%s",years[y].c_str()).Data(), "mldf_ee_flavor_estimate", 21, 0, 21, 21, 0, 21);
        TH2D* mldf_em_hist = new TH2D(TString::Format("mldf_em_hist_%s",years[y].c_str()).Data(), "mldf_em_flavor_estimate", 21, 0, 21, 21, 0, 21);
        TH2D* mldf_mm_hist = new TH2D(TString::Format("mldf_mm_hist_%s",years[y].c_str()).Data(), "mldf_mm_flavor_estimate", 21, 0, 21, 21, 0, 21);

        TH2D* sf_hist = new TH2D(TString::Format("sf_hist_%s",years[y].c_str()).Data(), "sf_estimate", 7, ptbins, 3, etabins);
        TH2D* df_hist = new TH2D(TString::Format("df_hist_%s",years[y].c_str()).Data(), "df_estimate", 21, 0, 21, 21, 0, 21);

        TH2D* hist_ones = onesHistogram(ptbins,etabins);

        sf_e_hist->Sumw2();
        sf_m_hist->Sumw2();
        mlsf_e_hist->Sumw2();
        mlsf_m_hist->Sumw2();

        e_fakeRate_hist->Sumw2();
        m_fakeRate_hist->Sumw2();


        fillFakeRateHistos(e_fakeRate_hist, years[y], "electron");
        fillFakeRateHistos(m_fakeRate_hist, years[y], "muon");
        ee_fakeRate_hist = fillDoubleFakeRateHistos(e_fakeRate_hist, e_fakeRate_hist, hist_ones, "ee");
        em_fakeRate_hist = fillDoubleFakeRateHistos(e_fakeRate_hist, m_fakeRate_hist, hist_ones, "em");
        mm_fakeRate_hist = fillDoubleFakeRateHistos(m_fakeRate_hist, m_fakeRate_hist, hist_ones, "mm");

        //sf events
        applyFakeRate(sf_e_hist,sf_e_in,e_fakeRate_hist,hist_ones);
        hist_ones->Delete();
        hist_ones = onesHistogram(ptbins,etabins);
        applyFakeRate(sf_m_hist,sf_m_in,m_fakeRate_hist,hist_ones);
        hist_ones->Delete();
        hist_ones = onesHistogram(ptbins,etabins);
        applyFakeRate(mlsf_e_hist,mlsf_e_in,e_fakeRate_hist,hist_ones);
        hist_ones->Delete();
        hist_ones = onesHistogram(ptbins,etabins);
        applyFakeRate(mlsf_m_hist,mlsf_m_in,m_fakeRate_hist,hist_ones);
        hist_ones->Delete();
        hist_ones = onesHistogram(ptbins,etabins);

        sf_hist->Add(sf_e_hist);
        sf_hist->Add(sf_m_hist);
        sf_hist->Add(mlsf_e_hist);
        sf_hist->Add(mlsf_m_hist);

        //df events
        applyDoubleFakeRate(df_ee_hist,df_ee_in,ee_fakeRate_hist);
        applyDoubleFakeRate(df_em_hist,df_em_in,em_fakeRate_hist);
        applyDoubleFakeRate(df_mm_hist,df_mm_in,mm_fakeRate_hist);
        applyDoubleFakeRate(mldf_ee_hist,mldf_ee_in,ee_fakeRate_hist);
        applyDoubleFakeRate(mldf_em_hist,mldf_em_in,em_fakeRate_hist);
        applyDoubleFakeRate(mldf_mm_hist,mldf_mm_in,mm_fakeRate_hist);

        df_hist->Add(df_ee_hist);
        df_hist->Add(df_em_hist);
        df_hist->Add(df_mm_hist);
        df_hist->Add(mldf_ee_hist);
        df_hist->Add(mldf_em_hist);
        df_hist->Add(mldf_mm_hist);

        outputFile->cd();
        sf_hist->Write();
        df_hist->Write();
        sf_e_hist->Write();
        sf_m_hist->Write();
        mlsf_e_hist->Write();
        mlsf_m_hist->Write();
        df_ee_hist->Write();
        df_em_hist->Write();
        df_mm_hist->Write();
        mldf_ee_hist->Write();
        mldf_em_hist->Write();
        mldf_mm_hist->Write();

        sf_e_in_temp->Delete();
        sf_m_in_temp->Delete();
        mlsf_e_in_temp->Delete();
        mlsf_m_in_temp->Delete();
        df_ee_in_temp->Delete();
        df_em_in_temp->Delete();
        df_mm_in_temp->Delete();
        mldf_ee_in_temp->Delete();
        mldf_em_in_temp->Delete();
        mldf_mm_in_temp->Delete();


    }

    return 0;
}
