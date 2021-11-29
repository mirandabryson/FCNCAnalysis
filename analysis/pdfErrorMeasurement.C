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


int pdfError(std::string inputDir, bool isBDT=0)
{
    std::string outputTxtFileName = inputDir+"/pdfErrorOutput.txt";
    ofstream outputTxtFile (outputTxtFileName.c_str());
    // TFile* outputTxtFile = new TFile(outputTxtFileName.c_str(),"recreate"); 

    // std::vector<std::string> years = {"2016", "2017", "2018"};
    std::vector<std::string> years = {"2016"};
    std::vector<std::string> samples;
    if(isBDT){samples = {"signal_tch","signal_tuh","rares_tch","rares_tuh"};}
    else{samples = {"signal_tch","signal_tuh","rares"};}
    std::vector<float> tuhScales = {1.,0.173061,1.04433,0.154513,1.00851,0.0340528,1.02598,0.964487,0.0837268,1.00252,
                                    1.06095,0.118896,0.851838,0.0360263,0.863192,1.02527,1.03578,1.01024,0.867273,0.350178,
                                    0.0346282,0.997886,0.136668,0.538447,0.0795671,0.877956,0.93457,1.01015,0.942823,0.285507,
                                    0.3712,0.511653,0.27039,0.748098,1.03028,1.01651,0.010258,1.02918,1.01781,0.0949934,
                                    0.514596,0.060455,0.485153,1.01051,1.00946,1.01039,0.20011,0.484449,0.975955,1.01938,
                                    0.106196,0.883983,0.0414871,0.641944,0.793193,1.01583,0.81924,0.695235,0.0103493,0.431149,
                                    1.00546,1.00251,0.0128327,0.865042,0.0688829,0.0737047,0.0400489,0.890453,0.586563,1.00988,
                                    1.00641,0.660502,0.0693972,1.01134,0.34503,1.02698,1.02032,1.07989,0.0811073,1.0223,
                                    0.81964,0.045889,0.0294785,1.00539,0.0148912,0.494365,0.0117779,0.597911,0.21107,0.436732,
                                    0.0802873,0.756001,1.02372,0.27099,0.440053,0.673136,1.01349,0.655437,0.080912,0.754459,1.0272
                                    };
    std::vector<float> tchScales = {1.,0.0328721,1.08654,0.461469,1.00164,0.0477424,0.68778,0.947524,0.176,0.322479,
                                    1.11387,0.968236,0.0403011,0.0755094,0.214923,0.735651,1.08058,0.167903,0.82221,0.611512,
                                    0.17191,0.99535,1.0332,0.131292,1.05622,0.835532,0.897847,1.00421,0.902104,0.164205,
                                    1.05091,0.0464163,0.231554,0.348393,1.06965,1.05473,0.0100952,0.805646,0.327187,0.481458,
                                    0.373283,0.0360673,1.01056,0.982612,1.02289,0.986858,0.399886,0.0465935,0.938527,1.06644,
                                    0.0725113,0.41891,0.115623,0.989001,0.731528,0.324871,0.586183,0.81397,0.655092,0.782229,
                                    1.02045,0.991395,0.021971,0.932687,0.0856454,0.14217,0.0641687,0.816378,0.967449,1.01247,
                                    1.03106,0.997561,0.0576365,0.986075,1.01347,1.00207,0.938942,1.11939,0.055062,1.03432,
                                    0.682735,0.103491,0.0756117,0.943854,0.93599,0.683066,0.0207498,0.831684,0.189688,0.824395,
                                    0.120751,0.622781,0.0346739,0.0635013,0.575956,0.332667,1.01617,1.05006,0.577232,0.77237,1.03778
                                    };
    std::vector<float> raresScales = {1.,0.933492,0.921578,0.924836,1.02245,0.943338,0.924071,0.936837,0.925411,0.908718,
                                    0.92653,0.935804,0.921771,0.920284,0.922815,0.938389,0.934503,0.952943,0.929527,0.938164,
                                    0.911275,0.9234,0.895399,0.927057,0.930104,0.919005,0.945019,0.927326,0.944899,0.926715,
                                    0.917117,0.912887,0.91916,0.0,8.12434e-21,0.937238,3.71488e-27,3.85734e-29,2.29419e-24,6.26747e-18,
                                    2.02534e-30,1.12831e-28,2.03049e-27,1.4345e-31,1.62374e-27,6.08819e-29,0.,4.69105e-18,-1.91607e-29,1.67652e-25,
                                    2.24956e-24,3.33295e-20,2.98846e-27,3.12586e-23,6.23285e-26,1.25813e-22,0.931486,1.93034e-24,2.03642e-27,4.18076e-05,
                                    4.96369e-23,0.,3.10314e-14,1.9857e-22,1.01941e-21,3.04667e-24,3.2101e-27,3.12142e-20,9.65609e-07,7.85026e-19,
                                    0.,0.,0.,0.,0.,0.,7.93863e-16,7.84756e-19,1.88238e-19,6.78836e-27,
                                    2.92116e-26,1.13623e-22,7.2245e-27,4.84006e-28,0.937123,6.28569e-14,1.34404e-14,3.54339e-06,6.59349e-14,1.79163e-22,
                                    1.14025e-26,7.63912e-28,1.73193e-14,1.234e-17,1.6721e-17,1.67043e-17,7.36883e-24,  0.,1.67288e-17,0.961833,2.17549e-31
                                    };



    for (int y = 0; y < years.size(); y++){

        TString tch_fileName = inputDir+"/signal_tch_"+years[y]+"_hists.root";
        TString tuh_fileName = inputDir+"/signal_tuh_"+years[y]+"_hists.root";
        TString rares_fileName = inputDir+"/rares_"+years[y]+"_hists.root";

        TFile* tchFile = new TFile(tch_fileName.Data());
        TFile* tuhFile = new TFile(tuh_fileName.Data());
        TFile* raresFile = new TFile(rares_fileName.Data());

        string histName;
        string samp;


        for (int s = 0; s < samples.size(); s++){
            TFile* file;
            std::vector<float> scales;
            if(samples[s]=="signal_tch"){
                file = tchFile;
                scales = tchScales;
                if(isBDT){histName = "bdtScore_syst_hct"+years[y];}
                else{histName = "sr_syst";}
                samp = "signal_tch";
            }
            if(samples[s]=="signal_tuh"){
                file = tuhFile;
                scales = tuhScales;
                if(isBDT){histName = "bdtScore_syst_hut"+years[y];}
                else{histName = "sr_syst";}
                samp = "signal_tuh";
            }
            if(samples[s]=="rares"){
                file = raresFile;
                scales = raresScales;
                histName = "sr_syst";
                samp = "rares";
            }
            if(samples[s]=="rares_tch"){
                file = raresFile;
                scales = raresScales;
                histName = "bdtScore_syst_hct"+years[y];
                samp = "rares";
            }
            if(samples[s]=="rares_tuh"){
                file = raresFile;
                scales = raresScales;
                histName = "bdtScore_syst_hut"+years[y];
                samp = "rares";
            }

            std::cout << samples[s] << std::endl;

            TH1D* temp_0 = (TH1D*) file->Get(TString("h_0_0_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_1 = (TH1D*) file->Get(TString("h_1_1_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_2 = (TH1D*) file->Get(TString("h_2_2_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_3 = (TH1D*) file->Get(TString("h_3_3_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_4 = (TH1D*) file->Get(TString("h_4_4_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_5 = (TH1D*) file->Get(TString("h_5_5_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_6 = (TH1D*) file->Get(TString("h_6_6_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_7 = (TH1D*) file->Get(TString("h_7_7_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_8 = (TH1D*) file->Get(TString("h_8_8_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_9 = (TH1D*) file->Get(TString("h_9_9_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_10 = (TH1D*) file->Get(TString("h_10_10_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_11 = (TH1D*) file->Get(TString("h_11_11_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_12 = (TH1D*) file->Get(TString("h_12_12_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_13 = (TH1D*) file->Get(TString("h_13_13_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_14 = (TH1D*) file->Get(TString("h_14_14_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_15 = (TH1D*) file->Get(TString("h_15_15_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_16 = (TH1D*) file->Get(TString("h_16_16_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_17 = (TH1D*) file->Get(TString("h_17_17_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_18 = (TH1D*) file->Get(TString("h_18_18_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_19 = (TH1D*) file->Get(TString("h_19_19_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_20 = (TH1D*) file->Get(TString("h_20_20_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_21 = (TH1D*) file->Get(TString("h_21_21_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_22 = (TH1D*) file->Get(TString("h_22_22_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_23 = (TH1D*) file->Get(TString("h_23_23_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_24 = (TH1D*) file->Get(TString("h_24_24_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_25 = (TH1D*) file->Get(TString("h_25_25_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_26 = (TH1D*) file->Get(TString("h_26_26_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_27 = (TH1D*) file->Get(TString("h_27_27_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_28 = (TH1D*) file->Get(TString("h_28_28_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_29 = (TH1D*) file->Get(TString("h_29_29_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_30 = (TH1D*) file->Get(TString("h_30_30_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_31 = (TH1D*) file->Get(TString("h_31_31_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_32 = (TH1D*) file->Get(TString("h_32_32_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_33 = (TH1D*) file->Get(TString("h_33_33_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_34 = (TH1D*) file->Get(TString("h_34_34_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_35 = (TH1D*) file->Get(TString("h_35_35_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_36 = (TH1D*) file->Get(TString("h_36_36_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_37 = (TH1D*) file->Get(TString("h_37_37_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_38 = (TH1D*) file->Get(TString("h_38_38_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_39 = (TH1D*) file->Get(TString("h_39_39_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_40 = (TH1D*) file->Get(TString("h_40_40_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_41 = (TH1D*) file->Get(TString("h_41_41_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_42 = (TH1D*) file->Get(TString("h_42_42_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_43 = (TH1D*) file->Get(TString("h_43_43_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_44 = (TH1D*) file->Get(TString("h_44_44_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_45 = (TH1D*) file->Get(TString("h_45_45_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_46 = (TH1D*) file->Get(TString("h_46_46_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_47 = (TH1D*) file->Get(TString("h_47_47_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_48 = (TH1D*) file->Get(TString("h_48_48_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_49 = (TH1D*) file->Get(TString("h_49_49_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_50 = (TH1D*) file->Get(TString("h_50_50_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_51 = (TH1D*) file->Get(TString("h_51_51_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_52 = (TH1D*) file->Get(TString("h_52_52_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_53 = (TH1D*) file->Get(TString("h_53_53_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_54 = (TH1D*) file->Get(TString("h_54_54_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_55 = (TH1D*) file->Get(TString("h_55_55_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_56 = (TH1D*) file->Get(TString("h_56_56_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_57 = (TH1D*) file->Get(TString("h_57_57_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_58 = (TH1D*) file->Get(TString("h_58_58_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_59 = (TH1D*) file->Get(TString("h_59_59_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_60 = (TH1D*) file->Get(TString("h_60_60_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_61 = (TH1D*) file->Get(TString("h_61_61_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_62 = (TH1D*) file->Get(TString("h_62_62_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_63 = (TH1D*) file->Get(TString("h_63_63_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_64 = (TH1D*) file->Get(TString("h_64_64_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_65 = (TH1D*) file->Get(TString("h_65_65_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_66 = (TH1D*) file->Get(TString("h_66_66_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_67 = (TH1D*) file->Get(TString("h_67_67_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_68 = (TH1D*) file->Get(TString("h_68_68_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_69 = (TH1D*) file->Get(TString("h_69_69_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_70 = (TH1D*) file->Get(TString("h_70_70_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_71 = (TH1D*) file->Get(TString("h_71_71_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_72 = (TH1D*) file->Get(TString("h_72_72_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_73 = (TH1D*) file->Get(TString("h_73_73_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_74 = (TH1D*) file->Get(TString("h_74_74_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_75 = (TH1D*) file->Get(TString("h_75_75_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_76 = (TH1D*) file->Get(TString("h_76_76_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_77 = (TH1D*) file->Get(TString("h_77_77_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_78 = (TH1D*) file->Get(TString("h_78_78_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_79 = (TH1D*) file->Get(TString("h_79_79_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_80 = (TH1D*) file->Get(TString("h_80_80_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_81 = (TH1D*) file->Get(TString("h_81_81_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_82 = (TH1D*) file->Get(TString("h_82_82_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_83 = (TH1D*) file->Get(TString("h_83_83_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_84 = (TH1D*) file->Get(TString("h_84_84_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_85 = (TH1D*) file->Get(TString("h_85_85_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_86 = (TH1D*) file->Get(TString("h_86_86_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_87 = (TH1D*) file->Get(TString("h_87_87_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_88 = (TH1D*) file->Get(TString("h_88_88_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_89 = (TH1D*) file->Get(TString("h_89_89_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_90 = (TH1D*) file->Get(TString("h_90_90_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_91 = (TH1D*) file->Get(TString("h_91_91_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_92 = (TH1D*) file->Get(TString("h_92_92_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_93 = (TH1D*) file->Get(TString("h_93_93_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_94 = (TH1D*) file->Get(TString("h_94_94_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_95 = (TH1D*) file->Get(TString("h_95_95_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_96 = (TH1D*) file->Get(TString("h_96_96_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_97 = (TH1D*) file->Get(TString("h_97_97_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_98 = (TH1D*) file->Get(TString("h_98_98_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_99 = (TH1D*) file->Get(TString("h_99_99_pdf_scale_"+histName+"_"+samp).Data());
            TH1D* temp_100 = (TH1D*) file->Get(TString("h_100_100_pdf_scale_"+histName+"_"+samp).Data());

            std::cout << "got histos" << std::endl;

            TH1D* pdf_0 = (TH1D*) temp_0->Clone();
            TH1D* pdf_1 = (TH1D*) temp_1->Clone();
            TH1D* pdf_2 = (TH1D*) temp_2->Clone();
            TH1D* pdf_3 = (TH1D*) temp_3->Clone();
            TH1D* pdf_4 = (TH1D*) temp_4->Clone();
            TH1D* pdf_5 = (TH1D*) temp_5->Clone();
            TH1D* pdf_6 = (TH1D*) temp_6->Clone();
            TH1D* pdf_7 = (TH1D*) temp_7->Clone();
            TH1D* pdf_8 = (TH1D*) temp_8->Clone();
            TH1D* pdf_9 = (TH1D*) temp_9->Clone();
            TH1D* pdf_10 = (TH1D*) temp_10->Clone();
            TH1D* pdf_11 = (TH1D*) temp_11->Clone();
            TH1D* pdf_12 = (TH1D*) temp_12->Clone();
            TH1D* pdf_13 = (TH1D*) temp_13->Clone();
            TH1D* pdf_14 = (TH1D*) temp_14->Clone();
            TH1D* pdf_15 = (TH1D*) temp_15->Clone();
            TH1D* pdf_16 = (TH1D*) temp_16->Clone();
            TH1D* pdf_17 = (TH1D*) temp_17->Clone();
            TH1D* pdf_18 = (TH1D*) temp_18->Clone();
            TH1D* pdf_19 = (TH1D*) temp_19->Clone();
            TH1D* pdf_20 = (TH1D*) temp_20->Clone();
            TH1D* pdf_21 = (TH1D*) temp_21->Clone();
            TH1D* pdf_22 = (TH1D*) temp_22->Clone();
            TH1D* pdf_23 = (TH1D*) temp_23->Clone();
            TH1D* pdf_24 = (TH1D*) temp_24->Clone();
            TH1D* pdf_25 = (TH1D*) temp_25->Clone();
            TH1D* pdf_26 = (TH1D*) temp_26->Clone();
            TH1D* pdf_27 = (TH1D*) temp_27->Clone();
            TH1D* pdf_28 = (TH1D*) temp_28->Clone();
            TH1D* pdf_29 = (TH1D*) temp_29->Clone();
            TH1D* pdf_30 = (TH1D*) temp_30->Clone();
            TH1D* pdf_31 = (TH1D*) temp_31->Clone();
            TH1D* pdf_32 = (TH1D*) temp_32->Clone();
            TH1D* pdf_33 = (TH1D*) temp_33->Clone();
            TH1D* pdf_34 = (TH1D*) temp_34->Clone();
            TH1D* pdf_35 = (TH1D*) temp_35->Clone();
            TH1D* pdf_36 = (TH1D*) temp_36->Clone();
            TH1D* pdf_37 = (TH1D*) temp_37->Clone();
            TH1D* pdf_38 = (TH1D*) temp_38->Clone();
            TH1D* pdf_39 = (TH1D*) temp_39->Clone();
            TH1D* pdf_40 = (TH1D*) temp_40->Clone();
            TH1D* pdf_41 = (TH1D*) temp_41->Clone();
            TH1D* pdf_42 = (TH1D*) temp_42->Clone();
            TH1D* pdf_43 = (TH1D*) temp_43->Clone();
            TH1D* pdf_44 = (TH1D*) temp_44->Clone();
            TH1D* pdf_45 = (TH1D*) temp_45->Clone();
            TH1D* pdf_46 = (TH1D*) temp_46->Clone();
            TH1D* pdf_47 = (TH1D*) temp_47->Clone();
            TH1D* pdf_48 = (TH1D*) temp_48->Clone();
            TH1D* pdf_49 = (TH1D*) temp_49->Clone();
            TH1D* pdf_50 = (TH1D*) temp_50->Clone();
            TH1D* pdf_51 = (TH1D*) temp_51->Clone();
            TH1D* pdf_52 = (TH1D*) temp_52->Clone();
            TH1D* pdf_53 = (TH1D*) temp_53->Clone();
            TH1D* pdf_54 = (TH1D*) temp_54->Clone();
            TH1D* pdf_55 = (TH1D*) temp_55->Clone();
            TH1D* pdf_56 = (TH1D*) temp_56->Clone();
            TH1D* pdf_57 = (TH1D*) temp_57->Clone();
            TH1D* pdf_58 = (TH1D*) temp_58->Clone();
            TH1D* pdf_59 = (TH1D*) temp_59->Clone();
            TH1D* pdf_60 = (TH1D*) temp_60->Clone();
            TH1D* pdf_61 = (TH1D*) temp_61->Clone();
            TH1D* pdf_62 = (TH1D*) temp_62->Clone();
            TH1D* pdf_63 = (TH1D*) temp_63->Clone();
            TH1D* pdf_64 = (TH1D*) temp_64->Clone();
            TH1D* pdf_65 = (TH1D*) temp_65->Clone();
            TH1D* pdf_66 = (TH1D*) temp_66->Clone();
            TH1D* pdf_67 = (TH1D*) temp_67->Clone();
            TH1D* pdf_68 = (TH1D*) temp_68->Clone();
            TH1D* pdf_69 = (TH1D*) temp_69->Clone();
            TH1D* pdf_70 = (TH1D*) temp_70->Clone();
            TH1D* pdf_71 = (TH1D*) temp_71->Clone();
            TH1D* pdf_72 = (TH1D*) temp_72->Clone();
            TH1D* pdf_73 = (TH1D*) temp_73->Clone();
            TH1D* pdf_74 = (TH1D*) temp_74->Clone();
            TH1D* pdf_75 = (TH1D*) temp_75->Clone();
            TH1D* pdf_76 = (TH1D*) temp_76->Clone();
            TH1D* pdf_77 = (TH1D*) temp_77->Clone();
            TH1D* pdf_78 = (TH1D*) temp_78->Clone();
            TH1D* pdf_79 = (TH1D*) temp_79->Clone();
            TH1D* pdf_80 = (TH1D*) temp_80->Clone();
            TH1D* pdf_81 = (TH1D*) temp_81->Clone();
            TH1D* pdf_82 = (TH1D*) temp_82->Clone();
            TH1D* pdf_83 = (TH1D*) temp_83->Clone();
            TH1D* pdf_84 = (TH1D*) temp_84->Clone();
            TH1D* pdf_85 = (TH1D*) temp_85->Clone();
            TH1D* pdf_86 = (TH1D*) temp_86->Clone();
            TH1D* pdf_87 = (TH1D*) temp_87->Clone();
            TH1D* pdf_88 = (TH1D*) temp_88->Clone();
            TH1D* pdf_89 = (TH1D*) temp_89->Clone();
            TH1D* pdf_90 = (TH1D*) temp_90->Clone();
            TH1D* pdf_91 = (TH1D*) temp_91->Clone();
            TH1D* pdf_92 = (TH1D*) temp_92->Clone();
            TH1D* pdf_93 = (TH1D*) temp_93->Clone();
            TH1D* pdf_94 = (TH1D*) temp_94->Clone();
            TH1D* pdf_95 = (TH1D*) temp_95->Clone();
            TH1D* pdf_96 = (TH1D*) temp_96->Clone();
            TH1D* pdf_97 = (TH1D*) temp_97->Clone();
            TH1D* pdf_98 = (TH1D*) temp_98->Clone();
            TH1D* pdf_99 = (TH1D*) temp_99->Clone();
            TH1D* pdf_100 = (TH1D*) temp_100->Clone();

            std::cout << "cloned histos" << std::endl;

            pdf_0->Scale(scales[0]);
            pdf_1->Scale(scales[1]);
            pdf_2->Scale(scales[2]);
            pdf_3->Scale(scales[3]);
            pdf_4->Scale(scales[4]);
            pdf_5->Scale(scales[5]);
            pdf_6->Scale(scales[6]);
            pdf_7->Scale(scales[7]);
            pdf_8->Scale(scales[8]);
            pdf_9->Scale(scales[9]);
            pdf_10->Scale(scales[10]);
            pdf_11->Scale(scales[11]);
            pdf_12->Scale(scales[12]);
            pdf_13->Scale(scales[13]);
            pdf_14->Scale(scales[14]);
            pdf_15->Scale(scales[15]);
            pdf_16->Scale(scales[16]);
            pdf_17->Scale(scales[17]);
            pdf_18->Scale(scales[18]);
            pdf_19->Scale(scales[19]);
            pdf_20->Scale(scales[20]);
            pdf_21->Scale(scales[21]);
            pdf_22->Scale(scales[22]);
            pdf_23->Scale(scales[23]);
            pdf_24->Scale(scales[24]);
            pdf_25->Scale(scales[25]);
            pdf_26->Scale(scales[26]);
            pdf_27->Scale(scales[27]);
            pdf_28->Scale(scales[28]);
            pdf_29->Scale(scales[29]);
            pdf_30->Scale(scales[30]);
            pdf_31->Scale(scales[31]);
            pdf_32->Scale(scales[32]);
            pdf_33->Scale(scales[33]);
            pdf_34->Scale(scales[34]);
            pdf_35->Scale(scales[35]);
            pdf_36->Scale(scales[36]);
            pdf_37->Scale(scales[37]);
            pdf_38->Scale(scales[38]);
            pdf_39->Scale(scales[39]);
            pdf_40->Scale(scales[40]);
            pdf_41->Scale(scales[41]);
            pdf_42->Scale(scales[42]);
            pdf_43->Scale(scales[43]);
            pdf_44->Scale(scales[44]);
            pdf_45->Scale(scales[45]);
            pdf_46->Scale(scales[46]);
            pdf_47->Scale(scales[47]);
            pdf_48->Scale(scales[48]);
            pdf_49->Scale(scales[49]);
            pdf_50->Scale(scales[50]);
            pdf_51->Scale(scales[51]);
            pdf_52->Scale(scales[52]);
            pdf_53->Scale(scales[53]);
            pdf_54->Scale(scales[54]);
            pdf_55->Scale(scales[55]);
            pdf_56->Scale(scales[56]);
            pdf_57->Scale(scales[57]);
            pdf_58->Scale(scales[58]);
            pdf_59->Scale(scales[59]);
            pdf_60->Scale(scales[60]);
            pdf_61->Scale(scales[61]);
            pdf_62->Scale(scales[62]);
            pdf_63->Scale(scales[63]);
            pdf_64->Scale(scales[64]);
            pdf_65->Scale(scales[65]);
            pdf_66->Scale(scales[66]);
            pdf_67->Scale(scales[67]);
            pdf_68->Scale(scales[68]);
            pdf_69->Scale(scales[69]);
            pdf_70->Scale(scales[70]);
            pdf_71->Scale(scales[71]);
            pdf_72->Scale(scales[72]);
            pdf_73->Scale(scales[73]);
            pdf_74->Scale(scales[74]);
            pdf_75->Scale(scales[75]);
            pdf_76->Scale(scales[76]);
            pdf_77->Scale(scales[77]);
            pdf_78->Scale(scales[78]);
            pdf_79->Scale(scales[79]);
            pdf_80->Scale(scales[80]);
            pdf_81->Scale(scales[81]);
            pdf_82->Scale(scales[82]);
            pdf_83->Scale(scales[83]);
            pdf_84->Scale(scales[84]);
            pdf_85->Scale(scales[85]);
            pdf_86->Scale(scales[86]);
            pdf_87->Scale(scales[87]);
            pdf_88->Scale(scales[88]);
            pdf_89->Scale(scales[89]);
            pdf_90->Scale(scales[90]);
            pdf_91->Scale(scales[91]);
            pdf_92->Scale(scales[92]);
            pdf_93->Scale(scales[93]);
            pdf_94->Scale(scales[94]);
            pdf_95->Scale(scales[95]);
            pdf_96->Scale(scales[96]);
            pdf_97->Scale(scales[97]);
            pdf_98->Scale(scales[98]);
            pdf_99->Scale(scales[99]);
            pdf_100->Scale(scales[100]);

            std::cout << "scaled histos" << std::endl;

            std::vector<TH1D*> histograms = {
                pdf_0,pdf_1,pdf_2,pdf_3,pdf_4,pdf_5,pdf_6,pdf_7,pdf_8,pdf_9,
                pdf_10,pdf_11,pdf_12,pdf_13,pdf_14,pdf_15,pdf_16,pdf_17,pdf_18,pdf_19,
                pdf_20,pdf_21,pdf_22,pdf_23,pdf_24,pdf_25,pdf_26,pdf_27,pdf_28,pdf_29,
                pdf_30,pdf_31,pdf_32,pdf_33,pdf_34,pdf_35,pdf_36,pdf_37,pdf_38,pdf_39,
                pdf_40,pdf_41,pdf_42,pdf_43,pdf_44,pdf_45,pdf_46,pdf_47,pdf_48,pdf_49,
                pdf_50,pdf_51,pdf_52,pdf_53,pdf_54,pdf_55,pdf_56,pdf_57,pdf_58,pdf_59,
                pdf_60,pdf_61,pdf_62,pdf_63,pdf_64,pdf_65,pdf_66,pdf_67,pdf_68,pdf_69,
                pdf_70,pdf_71,pdf_72,pdf_73,pdf_74,pdf_75,pdf_76,pdf_77,pdf_78,pdf_79,
                pdf_80,pdf_81,pdf_82,pdf_83,pdf_84,pdf_85,pdf_86,pdf_87,pdf_88,pdf_89,
                pdf_90,pdf_91,pdf_92,pdf_93,pdf_94,pdf_95,pdf_96,pdf_97,pdf_98,pdf_99,pdf_100
            };

            std::vector<float> upVariations;
            std::vector<float> downVariations;

            for (int b=1; b<pdf_0->GetNbinsX()+1; b++){
                std::vector<float> srVariation;
                for (int h=0; h<histograms.size(); h++){
                    srVariation.push_back(histograms[h]->GetBinContent(b));
                    // std::cout << "pdf" << h << " " << histograms[h]->GetBinContent(b) << std::endl;
                }
                std::sort(srVariation.begin(),srVariation.end());
                std::cout << srVariation[83] << " " << srVariation[15] << " " << pdf_0->GetBinContent(b) << std::endl;
                upVariations.push_back(srVariation[83]/pdf_0->GetBinContent(b));
                downVariations.push_back(srVariation[15]/pdf_0->GetBinContent(b));
            }

            std::cout << "got variations" << std::endl;

            if(outputTxtFile.is_open()){
                outputTxtFile << samples[s] << ":";
                for(int i = 0; i < upVariations.size(); i++){
                    if(samp=="rares"){
                        outputTxtFile << "\t" << 1.+(1.-upVariations[i]) << "/" << upVariations[i];
                    }else{
                        std::cout << downVariations[i] << " " << upVariations[i] << std::endl;
                        outputTxtFile << "\t" << 1.-downVariations[i] << "/" << upVariations[i];
                    }
                }
                outputTxtFile << endl;
            }

            std::cout << "wrote to txt file" << std::endl;

            temp_0->Delete();
            temp_1->Delete();
            temp_2->Delete();
            temp_3->Delete();
            temp_4->Delete();
            temp_5->Delete();
            temp_6->Delete();
            temp_7->Delete();
            temp_8->Delete();
            temp_9->Delete();
            temp_10->Delete();
            temp_11->Delete();
            temp_12->Delete();
            temp_13->Delete();
            temp_14->Delete();
            temp_15->Delete();
            temp_16->Delete();
            temp_17->Delete();
            temp_18->Delete();
            temp_19->Delete();
            temp_20->Delete();
            temp_21->Delete();
            temp_22->Delete();
            temp_23->Delete();
            temp_24->Delete();
            temp_25->Delete();
            temp_26->Delete();
            temp_27->Delete();
            temp_28->Delete();
            temp_29->Delete();
            temp_30->Delete();
            temp_31->Delete();
            temp_32->Delete();
            temp_33->Delete();
            temp_34->Delete();
            temp_35->Delete();
            temp_36->Delete();
            temp_37->Delete();
            temp_38->Delete();
            temp_39->Delete();
            temp_40->Delete();
            temp_41->Delete();
            temp_42->Delete();
            temp_43->Delete();
            temp_44->Delete();
            temp_45->Delete();
            temp_46->Delete();
            temp_47->Delete();
            temp_48->Delete();
            temp_49->Delete();
            temp_50->Delete();
            temp_51->Delete();
            temp_52->Delete();
            temp_53->Delete();
            temp_54->Delete();
            temp_55->Delete();
            temp_56->Delete();
            temp_57->Delete();
            temp_58->Delete();
            temp_59->Delete();
            temp_60->Delete();
            temp_61->Delete();
            temp_62->Delete();
            temp_63->Delete();
            temp_64->Delete();
            temp_65->Delete();
            temp_66->Delete();
            temp_67->Delete();
            temp_68->Delete();
            temp_69->Delete();
            temp_70->Delete();
            temp_71->Delete();
            temp_72->Delete();
            temp_73->Delete();
            temp_74->Delete();
            temp_75->Delete();
            temp_76->Delete();
            temp_77->Delete();
            temp_78->Delete();
            temp_79->Delete();
            temp_80->Delete();
            temp_81->Delete();
            temp_82->Delete();
            temp_83->Delete();
            temp_84->Delete();
            temp_85->Delete();
            temp_86->Delete();
            temp_87->Delete();
            temp_88->Delete();
            temp_89->Delete();
            temp_90->Delete();
            temp_91->Delete();
            temp_92->Delete();
            temp_93->Delete();
            temp_94->Delete();
            temp_95->Delete();
            temp_96->Delete();
            temp_97->Delete();
            temp_98->Delete();
            temp_99->Delete();
            temp_100->Delete();
        }

    }

    return 0;
}
