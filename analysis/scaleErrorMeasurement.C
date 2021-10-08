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

int scaleError(std::string inputDir)
{
    std::string outputFileName = inputDir+"/scaleErrorOutput.root";
    TFile* outputFile = new TFile(outputFileName.c_str(),"recreate"); 
    std::string outputTxtFileName = inputDir+"/scaleErrorOutput.txt";
    ofstream outputTxtFile (outputTxtFileName.c_str());
    // TFile* outputTxtFile = new TFile(outputTxtFileName.c_str(),"recreate"); 

    // std::vector<std::string> years = {"2016", "2017", "2018"};
    std::vector<std::string> years = {"2016"};

    for (int y = 0; y < years.size(); y++){

        TString tch_fileName = inputDir+"/signal_tch_"+years[y]+"_hists.root";
        TString tuh_fileName = inputDir+"/signal_tuh_"+years[y]+"_hists.root";
        TString rares_fileName = inputDir+"/rares_"+years[y]+"_hists.root";

        TFile* tchFile = new TFile(tch_fileName.Data());
        TFile* tuhFile = new TFile(tuh_fileName.Data());
        TFile* raresFile = new TFile(rares_fileName.Data());

        TH2D* tch0_temp = (TH2D*) tchFile->Get("h_0_renorm_scale_sr_syst_signal_tch");
        TH2D* tch1_temp = (TH2D*) tchFile->Get("h_1_renorm_scale_sr_syst_signal_tch");
        TH2D* tch2_temp = (TH2D*) tchFile->Get("h_2_renorm_scale_sr_syst_signal_tch");
        TH2D* tch3_temp = (TH2D*) tchFile->Get("h_3_renorm_scale_sr_syst_signal_tch");
        TH2D* tch4_temp = (TH2D*) tchFile->Get("h_4_renorm_scale_sr_syst_signal_tch");
        TH2D* tch5_temp = (TH2D*) tchFile->Get("h_5_renorm_scale_sr_syst_signal_tch");
        TH2D* tch6_temp = (TH2D*) tchFile->Get("h_6_renorm_scale_sr_syst_signal_tch");

        TH2D* tuh0_temp = (TH2D*) tuhFile->Get("h_0_renorm_scale_sr_syst_signal_tuh");
        TH2D* tuh1_temp = (TH2D*) tuhFile->Get("h_1_renorm_scale_sr_syst_signal_tuh");
        TH2D* tuh2_temp = (TH2D*) tuhFile->Get("h_2_renorm_scale_sr_syst_signal_tuh");
        TH2D* tuh3_temp = (TH2D*) tuhFile->Get("h_3_renorm_scale_sr_syst_signal_tuh");
        TH2D* tuh4_temp = (TH2D*) tuhFile->Get("h_4_renorm_scale_sr_syst_signal_tuh");
        TH2D* tuh5_temp = (TH2D*) tuhFile->Get("h_5_renorm_scale_sr_syst_signal_tuh");
        TH2D* tuh6_temp = (TH2D*) tuhFile->Get("h_6_renorm_scale_sr_syst_signal_tuh");

        TH2D* rares0_temp = (TH2D*) raresFile->Get("h_0_renorm_scale_sr_syst_rares");
        TH2D* rares1_temp = (TH2D*) raresFile->Get("h_1_renorm_scale_sr_syst_rares");
        TH2D* rares2_temp = (TH2D*) raresFile->Get("h_2_renorm_scale_sr_syst_rares");
        TH2D* rares3_temp = (TH2D*) raresFile->Get("h_3_renorm_scale_sr_syst_rares");
        TH2D* rares4_temp = (TH2D*) raresFile->Get("h_4_renorm_scale_sr_syst_rares");
        TH2D* rares5_temp = (TH2D*) raresFile->Get("h_5_renorm_scale_sr_syst_rares");
        TH2D* rares6_temp = (TH2D*) raresFile->Get("h_6_renorm_scale_sr_syst_rares");

        TH2D* tch0      = (TH2D*) tch0_temp->Clone();
        TH2D* tch1      = (TH2D*) tch1_temp->Clone();
        TH2D* tch2      = (TH2D*) tch2_temp->Clone();
        TH2D* tch3      = (TH2D*) tch3_temp->Clone();
        TH2D* tch4      = (TH2D*) tch4_temp->Clone();
        TH2D* tch5      = (TH2D*) tch5_temp->Clone();
        TH2D* tch6      = (TH2D*) tch6_temp->Clone();

        TH2D* tuh0      = (TH2D*) tuh0_temp->Clone();
        TH2D* tuh1      = (TH2D*) tuh1_temp->Clone();
        TH2D* tuh2      = (TH2D*) tuh2_temp->Clone();
        TH2D* tuh3      = (TH2D*) tuh3_temp->Clone();
        TH2D* tuh4      = (TH2D*) tuh4_temp->Clone();
        TH2D* tuh5      = (TH2D*) tuh5_temp->Clone();
        TH2D* tuh6      = (TH2D*) tuh6_temp->Clone();

        TH2D* rares0      = (TH2D*) rares0_temp->Clone();
        TH2D* rares1      = (TH2D*) rares1_temp->Clone();
        TH2D* rares2      = (TH2D*) rares2_temp->Clone();
        TH2D* rares3      = (TH2D*) rares3_temp->Clone();
        TH2D* rares4      = (TH2D*) rares4_temp->Clone();
        TH2D* rares5      = (TH2D*) rares5_temp->Clone();
        TH2D* rares6      = (TH2D*) rares6_temp->Clone();

        // cout << "tch0 normalization: " << 1./tch0->Integral() << endl;
        // cout << "tch1 normalization: " << 1./tch1->Integral() << endl;
        // cout << "tch2 normalization: " << 1./tch2->Integral() << endl;
        // cout << "tch3 normalization: " << 1./tch3->Integral() << endl;
        // cout << "tch4 normalization: " << 1./tch4->Integral() << endl;
        // cout << "tch5 normalization: " << 1./tch5->Integral() << endl;
        // cout << "tch6 normalization: " << 1./tch6->Integral() << endl;

        // cout << "tuh0 normalization: " << 1./tuh0->Integral() << endl;
        // cout << "tuh1 normalization: " << 1./tuh1->Integral() << endl;
        // cout << "tuh2 normalization: " << 1./tuh2->Integral() << endl;
        // cout << "tuh3 normalization: " << 1./tuh3->Integral() << endl;
        // cout << "tuh4 normalization: " << 1./tuh4->Integral() << endl;
        // cout << "tuh5 normalization: " << 1./tuh5->Integral() << endl;
        // cout << "tuh6 normalization: " << 1./tuh6->Integral() << endl;

        tch0->Scale(1.);
        tch1->Scale(0.833394);
        tch2->Scale(0.858535);
        tch3->Scale(0.972615);
        tch4->Scale(1.03886);
        tch5->Scale(1.13677);
        tch6->Scale(1.17921);

        tuh0->Scale(1.);
        tuh1->Scale(0.817184);
        tuh2->Scale(0.858594);
        tuh3->Scale(0.952625);
        tuh4->Scale(1.05665);
        tuh5->Scale(1.13681);
        tuh6->Scale(1.20029);

        rares0->Scale(1.);
        rares1->Scale(1.0085);
        rares2->Scale(0.958036);
        rares3->Scale(1.06402);
        rares4->Scale(0.962392);
        rares5->Scale(1.03512);
        rares6->Scale(0.987866);

        // tch0->Scale(1./tch0->Integral());
        // tch1->Scale(1./tch1->Integral());
        // tch2->Scale(1./tch2->Integral());
        // tch3->Scale(1./tch3->Integral());
        // tch4->Scale(1./tch4->Integral());
        // tch5->Scale(1./tch5->Integral());
        // tch6->Scale(1./tch6->Integral());

        // tuh0->Scale(1./tuh0->Integral());
        // tuh1->Scale(1./tuh1->Integral());
        // tuh2->Scale(1./tuh2->Integral());
        // tuh3->Scale(1./tuh3->Integral());
        // tuh4->Scale(1./tuh4->Integral());
        // tuh5->Scale(1./tuh5->Integral());
        // tuh6->Scale(1./tuh6->Integral());


        vector<double> tch1_vec;
        vector<double> tch2_vec;
        vector<double> tch3_vec;
        vector<double> tch4_vec;
        vector<double> tch5_vec;
        vector<double> tch6_vec;
        for(int i = 0; i < 22; i++){
            tch1_vec.push_back(tch1->GetBinContent(i)/tch0->GetBinContent(i));
            tch2_vec.push_back(tch2->GetBinContent(i)/tch0->GetBinContent(i));
            tch3_vec.push_back(tch3->GetBinContent(i)/tch0->GetBinContent(i));
            tch4_vec.push_back(tch4->GetBinContent(i)/tch0->GetBinContent(i));
            tch5_vec.push_back(tch5->GetBinContent(i)/tch0->GetBinContent(i));
            tch6_vec.push_back(tch6->GetBinContent(i)/tch0->GetBinContent(i));
        }
        vector< vector<double> > tch_vecs = {tch1_vec,tch2_vec,tch3_vec,tch4_vec,tch5_vec,tch6_vec};

        vector<double> tuh1_vec;
        vector<double> tuh2_vec;
        vector<double> tuh3_vec;
        vector<double> tuh4_vec;
        vector<double> tuh5_vec;
        vector<double> tuh6_vec;
        for(int i = 0; i < 22; i++){
            tuh1_vec.push_back(tuh1->GetBinContent(i)/tuh0->GetBinContent(i));
            tuh2_vec.push_back(tuh2->GetBinContent(i)/tuh0->GetBinContent(i));
            tuh3_vec.push_back(tuh3->GetBinContent(i)/tuh0->GetBinContent(i));
            tuh4_vec.push_back(tuh4->GetBinContent(i)/tuh0->GetBinContent(i));
            tuh5_vec.push_back(tuh5->GetBinContent(i)/tuh0->GetBinContent(i));
            tuh6_vec.push_back(tuh6->GetBinContent(i)/tuh0->GetBinContent(i));
        }
        vector< vector<double> > tuh_vecs = {tuh1_vec,tuh2_vec,tuh3_vec,tuh4_vec,tuh5_vec,tuh6_vec};

        vector<double> rares1_vec;
        vector<double> rares2_vec;
        vector<double> rares3_vec;
        vector<double> rares4_vec;
        vector<double> rares5_vec;
        vector<double> rares6_vec;
        for(int i = 0; i < 22; i++){
            rares1_vec.push_back(rares1->GetBinContent(i)/rares0->GetBinContent(i));
            rares2_vec.push_back(rares2->GetBinContent(i)/rares0->GetBinContent(i));
            rares3_vec.push_back(rares3->GetBinContent(i)/rares0->GetBinContent(i));
            rares4_vec.push_back(rares4->GetBinContent(i)/rares0->GetBinContent(i));
            rares5_vec.push_back(rares5->GetBinContent(i)/rares0->GetBinContent(i));
            rares6_vec.push_back(rares6->GetBinContent(i)/rares0->GetBinContent(i));
        }
        vector< vector<double> > rares_vecs = {rares1_vec,rares2_vec,rares3_vec,rares4_vec,rares5_vec,rares6_vec};

        if(outputTxtFile.is_open()){
            outputTxtFile << "tch:";
            for (int i = 0; i < tch_vecs[0].size(); i++){
                float biggestUnc = 0.;
                float uncertainty = 0.;
                for (int j = 0; j < tch_vecs.size(); j++){
                    if (fabs(tch_vecs[j][i]-1.)>biggestUnc){
                        biggestUnc = fabs(tch_vecs[j][i]-1.);
                        uncertainty = tch_vecs[j][i];
                    }
                }
                outputTxtFile << "\t" << uncertainty;
            }
            outputTxtFile << endl;


            outputTxtFile << "tuh:";
            for (int i = 0; i < tuh_vecs[0].size(); i++){
                float biggestUnc = 0.;
                float uncertainty = 0.;
                for (int j = 0; j < tuh_vecs.size(); j++){
                    if (fabs(tuh_vecs[j][i]-1.)>biggestUnc){
                        biggestUnc = fabs(tuh_vecs[j][i]-1.);
                        uncertainty = tuh_vecs[j][i];
                    }
                }
                outputTxtFile << "\t" << uncertainty;
            }
            outputTxtFile << endl;


            outputTxtFile << "rares:";
            for (int i = 0; i < rares_vecs[0].size(); i++){
                float biggestUnc = 0.;
                float uncertainty = 0.;
                for (int j = 0; j < rares_vecs.size(); j++){
                    if (fabs(rares_vecs[j][i]-1.)>biggestUnc){
                        biggestUnc = fabs(rares_vecs[j][i]-1.);
                        uncertainty = rares_vecs[j][i];
                    }
                }
                outputTxtFile << "\t" << uncertainty;
            }
            outputTxtFile << endl;
        }

        tch0->SetLineColor(kBlue);
        tch1->SetLineColor(kRed);
        tch2->SetLineColor(kGreen);
        tch3->SetLineColor(kViolet);
        tch4->SetLineColor(kPink);
        tch5->SetLineColor(kMagenta);
        tch6->SetLineColor(kBlack);

        tuh0->SetLineColor(kBlue);
        tuh1->SetLineColor(kRed);
        tuh2->SetLineColor(kGreen);
        tuh3->SetLineColor(kViolet);
        tuh4->SetLineColor(kPink);
        tuh5->SetLineColor(kMagenta);
        tuh6->SetLineColor(kBlack);

        rares0->SetLineColor(kBlue);
        rares1->SetLineColor(kRed);
        rares2->SetLineColor(kGreen);
        rares3->SetLineColor(kViolet);
        rares4->SetLineColor(kPink);
        rares5->SetLineColor(kMagenta);
        rares6->SetLineColor(kBlack);

        auto c_tch = new TCanvas("tch","tch",600,600);
        auto c_tuh = new TCanvas("tuh","tuh",600,600);
        auto c_rares = new TCanvas("rares","rares",600,600);

        c_tch->cd();
        tch0->Draw();
        tch1->Draw("same");
        tch2->Draw("same");
        tch3->Draw("same");
        tch4->Draw("same");
        tch5->Draw("same");
        tch6->Draw("same");

        c_tuh->cd();
        tuh0->Draw();
        tuh1->Draw("same");
        tuh2->Draw("same");
        tuh3->Draw("same");
        tuh4->Draw("same");
        tuh5->Draw("same");
        tuh6->Draw("same");

        c_rares->cd();
        rares0->Draw();
        rares1->Draw("same");
        rares2->Draw("same");
        rares3->Draw("same");
        rares4->Draw("same");
        rares5->Draw("same");
        rares6->Draw("same");

        outputFile->cd();
        c_tch->Write();
        c_tuh->Write();
        c_rares->Write();

        tch0_temp->Delete();
        tch1_temp->Delete();
        tch2_temp->Delete();
        tch3_temp->Delete();
        tch4_temp->Delete();
        tch5_temp->Delete();
        tch6_temp->Delete();

        tuh0_temp->Delete();
        tuh1_temp->Delete();
        tuh2_temp->Delete();
        tuh3_temp->Delete();
        tuh4_temp->Delete();
        tuh5_temp->Delete();
        tuh6_temp->Delete();

        rares0_temp->Delete();
        rares1_temp->Delete();
        rares2_temp->Delete();
        rares3_temp->Delete();
        rares4_temp->Delete();
        rares5_temp->Delete();
        rares6_temp->Delete();


    }

    return 0;
}
