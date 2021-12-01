#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
// #include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

#include <iostream>
#include <iomanip>


using namespace std;
// using namespace tas;


TH2D* onesHistogram(Double_t xbins[7], Double_t ybins[4]){
    TH2D* hist_ones = new TH2D("hist_ones","ones",6,xbins,3,ybins);
    for(int a = 0; a < 7; a++){
        for(int b = 0; b < 4; b++){
            hist_ones->SetBinContent(a,b,1);
            hist_ones->SetBinError(a,b,0);
        }
    }
    return hist_ones;
}

TH2D* fillFlipRateHistos(TH2D* inputHisto, string year){
    double scale = 1.;
    if(year=="2016"){scale = 1.1128218361769364;}
    if(year=="2017"){scale = 1.4447739510004296;}
    if(year=="2018"){scale = 1.3061565063535605;}

    map<vector<int>,vector<double>> electron2016 = {
        {{1,1},{4.02556047095e-05*scale,3.9183184838e-06*scale}},{{1,2},{0.000191283075539*scale,1.04671211985e-05*scale}},{{1,3},{0.0014808018906*scale,3.30698016443e-05*scale}},
        {{2,1},{3.24184888544e-05*scale,3.55113783018e-06*scale}},{{2,2},{0.000288330168267*scale,1.29495594391e-05*scale}},{{2,3},{0.00190707063301*scale,4.11772636975e-05*scale}},
        {{3,1},{2.72826587544e-05*scale,7.08869241586e-06*scale}},{{3,2},{0.000425901801084*scale,3.54825189691e-05*scale}},{{3,3},{0.00299318101504*scale,0.000118230988153*scale}},
        {{4,1},{0.000111754820026*scale,2.37086576912e-05*scale}},{{4,2},{0.000481357446343*scale,6.05683392889e-05*scale}},{{4,3},{0.00351907105176*scale,0.000213884154333*scale}},
        {{5,1},{8.43473757551e-05*scale,1.81133825762e-05*scale}},{{5,2},{0.000817956862414*scale,7.27846562709e-05*scale}},{{5,3},{0.00515126700964*scale,0.000244608599105*scale}},
        {{6,1},{5.83122836433e-05*scale,4.13001955295e-05*scale}},{{6,2},{0.000517371989468*scale,0.000154530063971*scale}},{{6,3},{0.00661050703454*scale,0.000836941070856*scale}},
    };
    map<vector<int>,vector<double>> electron2017 = {
        {{1,1},{2.38453587652e-05*scale,3.21359412871e-06*scale}},{{1,2},{7.99085449374e-05*scale,7.33356108428e-06*scale}},{{1,3},{0.000712067438702*scale,2.51028034341e-05*scale}},
        {{2,1},{1.91659933248e-05*scale,2.84478887391e-06*scale}},{{2,2},{0.0001166188839*scale,8.66389018595e-06*scale}},{{2,3},{0.000779650545954*scale,2.60352194351e-05*scale}},
        {{3,1},{2.55933306063e-05*scale,7.78728063616e-06*scale}},{{3,2},{0.000175292163676*scale,2.72187879158e-05*scale}},{{3,3},{0.00130593692089*scale,9.34395924239e-05*scale}},
        {{4,1},{3.36222207333e-05*scale,1.23509058561e-05*scale}},{{4,2},{0.000231082811867*scale,4.88664968285e-05*scale}},{{4,3},{0.0017362496487*scale,0.000174139901881*scale}},
        {{5,1},{5.82240178793e-05*scale,1.61381882453e-05*scale}},{{5,2},{0.000378059688439*scale,5.79278577187e-05*scale}},{{5,3},{0.00257346989023*scale,0.000211062431866*scale}},
        {{6,1},{0.000242357736611*scale,0.000109698014086*scale}},{{6,2},{0.000816017591267*scale,0.000269028749398*scale}},{{6,3},{0.00463215704213*scale,0.00104557819978*scale}},
    };
    map<vector<int>,vector<double>> electron2018 = {
        {{1,1},{2.91502811928e-05*scale,3.54576253168e-06*scale}},{{1,2},{0.000114537784561*scale,8.57622206089e-06*scale}},{{1,3},{0.000737718492991*scale,2.61956706819e-05*scale}},
        {{2,1},{2.43389626268e-05*scale,3.19666759313e-06*scale}},{{2,2},{0.000120545701142*scale,8.97151384071e-06*scale}},{{2,3},{0.000911854481931*scale,2.7954941261e-05*scale}},
        {{3,1},{4.00203445913e-05*scale,9.8650423099e-06*scale}},{{3,2},{0.000201819989855*scale,2.8172408285e-05*scale}},{{3,3},{0.00131322856994*scale,8.83883929238e-05*scale}},
        {{4,1},{5.04595724607e-05*scale,1.63169530122e-05*scale}},{{4,2},{0.000310283223174*scale,5.20977373224e-05*scale}},{{4,3},{0.00203571326446*scale,0.000168299550426*scale}},
        {{5,1},{4.47847086164e-05*scale,1.25207275411e-05*scale}},{{5,2},{0.000445696399346*scale,5.22901640093e-05*scale}},{{5,3},{0.00237298940033*scale,0.000158180857166*scale}},
        {{6,1},{9.1849290275e-05*scale,4.29836660284e-05*scale}},{{6,2},{0.000662764740024*scale,0.000166353866483*scale}},{{6,3},{0.00329508417923*scale,0.000542152139961*scale}},
    };

    map<vector<int>,vector<double>> fillingMap;
    if (year=="2016"){
        fillingMap=electron2016;
    }else if (year == "2017"){
        fillingMap=electron2017;
    }else if (year=="2018"){
        fillingMap=electron2018;
    }else{std::cout << "shouldn't ever be here! check input to fillFlipRateHistos function!" << std::endl;}

    for(int i = 1; i < inputHisto->GetNbinsX()+1; i++){
        for(int j = 1; j < inputHisto->GetNbinsY()+1; j++){
            vector<int> bin = {i,j};
            // if (year == "2016" && flavor=="muon"){cout << bin[0] << " " << bin[1] << " " << fillingMap[bin][0] << endl;}
            inputHisto->SetBinContent(i,j,fillingMap[bin][0]);
            inputHisto->SetBinError(i,j,fillingMap[bin][1]);
            // inputHisto->SetBinError(i,j,0);
        }
    }
    return inputHisto;
}

TH2D* applyFlipRate(TH2D* output, TH2D* CRYields, TH2D* rateHisto, TH2D* ones){
    (*output) = (*CRYields)*(*rateHisto);
    ones->Add(rateHisto,-1);
    output->Divide(ones);
    return output;
}

TH2D* fillDoubleFlipRateHistos(TH2D* flipRate, TH2D* ones, string name){
    TH2D* ones_lep1 = (TH2D*) ones->Clone();
    TH2D* ones_lep2 = (TH2D*) ones->Clone();
    ones_lep1->Add(flipRate, -1);
    ones_lep2->Add(flipRate, -1);
    
    TH2D* flipWeight_lep1 = (TH2D*) flipRate->Clone();
    flipWeight_lep1->Divide(ones_lep1);
    TH2D* flipWeight_lep2 = (TH2D*) flipRate->Clone();
    flipWeight_lep2->Divide(ones_lep2);

    TH2D* output = new TH2D(TString::Format("h_doubleFlipWeight_%s",name.c_str()).Data(),TString::Format("h_doubleFlipWeight_%s",name.c_str()).Data(), 18, 0, 18, 18, 0, 18);

    int lep_2_it = 0;
    int lep_1_it = 0;

    for(uint i = 1; i < flipWeight_lep2->GetNbinsY()+1; i++){
        for(uint j = 1; j < flipWeight_lep2->GetNbinsX()+1; j++){
            lep_2_it++;
            TH2D* h_temp = (TH2D*) flipWeight_lep2->Clone();
            for(uint a = 1; a < flipWeight_lep2->GetNbinsY()+1; a++){
                for(uint b = 1; b < flipWeight_lep2->GetNbinsX()+1; b++){
                    h_temp->SetBinContent(b,a,flipWeight_lep2->GetBinContent(j,i));
                    h_temp->SetBinError(b,a,flipWeight_lep2->GetBinError(j,i));
                }
            }
            h_temp->Add(flipWeight_lep1);
            lep_1_it = 0;
            for(uint a = 1; a < h_temp->GetNbinsY()+1; a++){
                for(uint b = 1; b < h_temp->GetNbinsX()+1; b++){
                    lep_1_it++;
                    output->SetBinContent(lep_1_it,lep_2_it,h_temp->GetBinContent(b,a));
                    output->SetBinError(lep_1_it,lep_2_it,h_temp->GetBinError(b,a));
                    output->SetBinError(lep_1_it,lep_2_it,0);
                }
            }
        }
    }
    return output;
}

TH2D* applyDoubleFlipRate(TH2D* outputHisto, TH2D* inputHisto, TH2D* weightHisto){
    (*outputHisto) = (*inputHisto)*(*weightHisto);
    return outputHisto;
}

std::vector<double> integral(TH2D* inputHisto){
    double errVar = 0;
    double integral = 0;
    int xbins = inputHisto->GetNbinsX();
    int ybins = inputHisto->GetNbinsY();

    integral = inputHisto->IntegralAndError(0,xbins,0,ybins,errVar);
    cout << "integral: " << integral << "   error: " << errVar << "   percentage: " << errVar/integral*100 << endl;
    vector<double> ret;
    ret.push_back(integral);
    ret.push_back(errVar);
    return ret;
}

int rateMultiplication(std::string inputDir)
{
    std::string outputFileName = inputDir+"/flipProp_hct_hists.root";
    TFile* outputFile = new TFile(outputFileName.c_str(),"recreate"); 

    std::vector<std::string> years = {"2016", "2017", "2018"};

    Double_t ptbins[7]  = {15., 40., 60., 80., 100., 200., 300.};
    Double_t etabins[4] = {0., 0.8, 1.479, 2.5};

    for (int y = 0; y < years.size(); y++){

        TString fileName = inputDir+"/data_"+years[y]+"_hists.root";

        TFile* inputFile = new TFile(fileName.Data());

        TH2D* os_e_in_temp  = (TH2D*) inputFile->Get("h_os_flip2d_hct_cr_data");
        TH2D* os_ee_in_temp  = (TH2D*) inputFile->Get("h_os_flip2d_hct_2ecr_data");

        TH2D* os_e_in = (TH2D*) os_e_in_temp->Clone(TString::Format("h_os_e_in_%s",years[y].c_str()).Data());
        TH2D* os_ee_in = (TH2D*) os_ee_in_temp->Clone(TString::Format("h_os_ee_in_%s",years[y].c_str()).Data());

        TH2D* e_flipRate_hist   = new TH2D(TString::Format("e_flipRate_%s",years[y].c_str()).Data(),"e_flipRate", 6, ptbins, 3, etabins);
        TH2D* ee_flipRate_hist   = new TH2D(TString::Format("ee_flipRate_%s",years[y].c_str()).Data(),"ee_flipRate", 18,0,18,18,0,18);

        TH2D* os_e_hist     = new TH2D(TString::Format("os_e_hist_%s",years[y].c_str()).Data(), "os_e_flavor_estimate", 6, ptbins, 3, etabins);
        TH2D* os_ee_hist     = new TH2D(TString::Format("os_ee_hist_%s",years[y].c_str()).Data(), "os_ee_flavor_estimate", 18,0,18,18,0,18);

        TH2D* os_1e_hist   = new TH2D(TString::Format("os_1e_hist_%s",years[y].c_str()).Data(), "os_estimate", 6, ptbins, 3, etabins);
        TH2D* oscr_1e_hist = new TH2D(TString::Format("oscr_1e_hist_%s",years[y].c_str()).Data(), "os_crYields", 6, ptbins, 3, etabins);
        TH2D* os_2e_hist   = new TH2D(TString::Format("os_2e_hist_%s",years[y].c_str()).Data(), "os2e_estimate", 18,0,18,18,0,18);
        TH2D* oscr_2e_hist = new TH2D(TString::Format("oscr_2e_hist_%s",years[y].c_str()).Data(), "os2e_crYields", 18,0,18,18,0,18);

        TH2D* e_hist_ones = onesHistogram(ptbins,etabins);

        os_e_hist->Sumw2();
        os_ee_hist->Sumw2();

        e_flipRate_hist->Sumw2();
        ee_flipRate_hist->Sumw2();


        fillFlipRateHistos(e_flipRate_hist, years[y]);
        ee_flipRate_hist = fillDoubleFlipRateHistos(e_flipRate_hist, e_hist_ones, years[y]);

        for(int r = 0; r < 4; r++){
            for(int c = 0; c < 7; c++){
                os_e_in->SetBinError(c,r,0);
            }
        }

        for(int r = 0; r < 19; r++){
            for(int c = 0; c < 19; c++){
                os_ee_in->SetBinError(c,r,0);
            }
        }

        // cout << "1e CR stats: ";
        // std::vector<double> vec_1eCR = integral(os_e_in);
        // cout << endl;
        // cout << "2e CR stats: ";
        // std::vector<double> vec_2eCR = integral(os_ee_in);
        // cout << endl;

        //1e events
        oscr_1e_hist->Add(os_e_in);
        applyFlipRate(os_e_hist,os_e_in,e_flipRate_hist,e_hist_ones);
        e_hist_ones->Delete();
        e_hist_ones = onesHistogram(ptbins,etabins);

        cout << "1e: ";
        std::vector<double> vec_1e;
        vec_1e = integral(os_e_hist);
        cout << endl;

        //2e events
        oscr_2e_hist->Add(os_ee_in);
        applyDoubleFlipRate(os_ee_hist,os_ee_in,ee_flipRate_hist);

        cout << "2e: ";
        std::vector<double> vec_2e;
        vec_2e = integral(os_ee_hist);
        cout << endl;

        cout << "1e+2e: " << vec_1e[0]+vec_2e[0] << " +/- " << sqrt(pow(vec_1e[1],2)+pow(vec_2e[1],2)) << " as percentage: " << sqrt(pow(vec_1e[1],2)+pow(vec_2e[1],2))/(vec_1e[0]+vec_2e[0])*100 << endl;


        outputFile->cd();
        os_1e_hist->Write();
        os_2e_hist->Write();
        os_e_hist->Write();
        os_ee_hist->Write();
        e_flipRate_hist->Write();
        ee_flipRate_hist->Write();

        os_e_in_temp->Delete();
        os_ee_in_temp->Delete();


    }

    return 0;
}
