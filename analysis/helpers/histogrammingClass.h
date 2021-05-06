#include <TH1F.h>
#include <TFile.h>

class categoryHistogram{
    private:
        TH1F* h_nJet;
        TH1F* h_nBJet;
        TH1F* h_nGoodLeps;
        TH1F* h_leadLepPt;
        TH1F* h_leadLepEta;
        TH1F* h_leadLepMass;
        TH1F* h_leadLepMiniIso;
        TH1F* h_leadLepPtRel;
        TH1F* h_leadLepPtRatio;
        TH1F* h_leadJetPt;
        TH1F* h_leadBPt;
        TH1F* h_leadBMass;
        TH1F* h_jetHT;
        TH1F* h_MET;
        TH1F* h_minMT;
        TH1F* h_MT_b_MET;

    public:
        /*int nJet;
        int nBJet;
        int nLep;
        int nFO;
        bool isSS;
        bool isSF;*/

        //constructor will create all histograms for each region category
        categoryHistogram(string numLep, string numJet, string numB, string sampleName){
            h_nJet = new TH1F( ("h_nJet_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "nJets", 7, -0.5, 6.5 );
            h_nBJet = new TH1F( ("h_nBJet_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "nBjets", 4, -0.5, 3.5 );
            h_nGoodLeps = new TH1F( ("h_nGoodLeps_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "nGoodLeps", 6, -0.5, 5.5 );
            h_leadLepPt = new TH1F( ("h_leadLepPt_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadLepPt", 50, 0, 500 );
            h_leadLepEta = new TH1F( ("h_leadLepEta_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadLepEta", 20, -5, 5 );
            h_leadLepMass = new TH1F( ("h_leadLepMass_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadLepMass", 500, 0, 1 );
            h_leadLepMiniIso = new TH1F( ("h_leadLepMiniIso_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadLepMiniIso", 10, 0, 0.5 );
            h_leadLepPtRel = new TH1F( ("h_leadLepPtRel_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadLepPtRel", 50, 0, 10 );
            h_leadLepPtRatio = new TH1F( ("h_leadLepPtRatio_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadLepPtRatio", 50, 0, 5 );
            h_leadJetPt = new TH1F( ("h_leadJetPt_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadJetPt", 50, 0, 500 );
            h_leadBPt = new TH1F( ("h_leadBPt_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadBPt", 50, 0, 500 );
            h_leadBMass = new TH1F( ("h_leadBMass_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "leadBMass", 50, 0, 500 );
            h_jetHT = new TH1F( ("h_jetHT_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "jetHT", 100, 0, 1000 );
            h_MET = new TH1F( ("h_MET_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "MET", 50, 0, 500 );
            h_minMT = new TH1F( ("h_minMT_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "minMT", 50, 0, 500 );
            h_MT_b_MET = new TH1F( ("h_MT_b_MET_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName).c_str(), "MT_b_MET", 50, 0, 500 );
        } 
        categoryHistogram(){} 

        //methods to fill and save histograms
        void fillHistogram(vector<float> variables, float weight){
            h_nJet->Fill(variables[0], weight);
            h_nBJet->Fill(variables[1], weight);
            h_nGoodLeps->Fill(variables[2], weight);
            h_leadLepPt->Fill(variables[3], weight);
            h_leadLepEta->Fill(variables[4], weight);
            h_leadLepMass->Fill(variables[5], weight);
            h_leadLepMiniIso->Fill(variables[6], weight);
            h_leadLepPtRel->Fill(variables[7], weight);
            h_leadLepPtRatio->Fill(variables[8], weight);
            h_leadJetPt->Fill(variables[9], weight);
            h_leadBPt->Fill(variables[10], weight);
            h_leadBMass->Fill(variables[11], weight);
            h_jetHT->Fill(variables[12], weight);
            h_MET->Fill(variables[13], weight);
            h_minMT->Fill(variables[14], weight);
            h_MT_b_MET->Fill(variables[15], weight);
        }

        void writeHistogram(TFile* &outfile){
            if (outfile->IsOpen()){
                h_nJet->Write();
                h_nBJet->Write();
                h_nGoodLeps->Write();
                h_leadLepPt->Write();
                h_leadLepEta->Write();
                h_leadLepMass->Write();
                h_leadLepMiniIso->Write();
                h_leadLepPtRel->Write();
                h_leadLepPtRatio->Write();
                h_leadJetPt->Write();
                h_leadBPt->Write();
                h_leadBMass->Write();
                h_jetHT->Write();
                h_MET->Write();
                h_minMT->Write();
                h_MT_b_MET->Write();
            }
        }

};






class sampleHistogram{
    private:
        TH1F* h_srCategories;
        TH1F* h_backgroundTypes;
    public:
        sampleHistogram(string sampleName, string category){
            h_srCategories = new TH1F( ("h_srYields_"+sampleName+"_"+category).c_str(), "SR_Yields", 20, 0, 20 );
            h_backgroundTypes = new TH1F( ("h_backgroundTypes_"+sampleName+"_"+category).c_str(),"backgroundCategories", 5, 0, 5 );
        }
        void fillBackgroundTypes(vector<bool>variables, float weight){
            bool isFake = variables[0];
            bool isFlip = variables[1];
            bool isOther = variables[2];

            int bin = 5;
            if(isFake) bin = 0;
            if(isFlip) bin = 1;
            if(isOther) bin = 2;

            h_backgroundTypes->AddBinContent(bin, weight);
        }
        void fillSRCategories(int numLep, int numJet, int numB, float weight){
            int bin = 20;
            if(numLep>2){
                if(numJet==2){
                    if(numB==0){
                        bin = 0;
                    }else if(numB==1){
                        bin = 1;
                    }else if(numB==2){
                        bin = 2;
                    }
                }else if(numJet==3){
                    if(numB==0){
                        bin = 3;
                    }else if(numB==1){
                        bin = 4;
                    }else if(numB==2){
                        bin = 5;
                    }
                }else if(numJet>=4){
                    if(numB==0){
                        bin = 6;
                    }else if(numB==1){
                        bin = 7;
                    }else if(numB==2){
                        bin = 8;
                    }
                }
            }else if(numLep==2){
                if(numJet==2){
                    if(numB==0){
                        bin = 9;
                    }else if(numB==1){
                        bin = 10;
                    }else if(numB==2){
                        bin = 11;
                    }
                }else if(numJet==3){
                    if(numB==0){
                        bin = 12;
                    }else if(numB==1){
                        bin = 13;
                    }else if(numB==2){
                        bin = 14;
                    }
                }else if(numJet>=4){
                    if(numB==0){
                        bin = 15;
                    }else if(numB==1){
                        bin = 16;
                    }else if(numB==2){
                        bin = 17;
                    }
                }
            }//close lepton number check
            h_srCategories->AddBinContent(bin, weight);
        }
        void writeHistograms(TFile* &outfile){
            if(outfile->IsOpen()){
                h_srCategories->Write();
                h_backgroundTypes->Write();
            }
        }
};






class makeSampleHistos{
    private:
        sampleHistogram* TTGamma_SingleLept;
        sampleHistogram* TGJets;
        sampleHistogram* TTWJetsToLNu;
        sampleHistogram* WJetsToLNu;
        sampleHistogram* ST_tWll_5f_LO;
        sampleHistogram* TTGamma_Dilept;
        sampleHistogram* TTZToLLNuNu_M10;
        sampleHistogram* TTZToLL_M1to10;
        sampleHistogram* DYJetsToLL_M10to50;
        sampleHistogram* DYJetsToLL_M50;
        sampleHistogram* ZGToLLG_01J_5f;
        sampleHistogram* ZZTo4L;
        sampleHistogram* ZZZ;
        sampleHistogram* GluGluHToZZTo4L;
        sampleHistogram* GluGluToContinToZZTo2e2mu;
        sampleHistogram* GluGluToContinToZZTo2e2tau;
        sampleHistogram* GluGluToContinToZZTo2mu2tau;
        sampleHistogram* GluGluToContinToZZTo4e;
        sampleHistogram* GluGluToContinToZZTo4mu;
        sampleHistogram* GluGluToContinToZZTo4tau;
        sampleHistogram* WWG;
        sampleHistogram* WWTo2L2Nu_DoubleScattering;
        sampleHistogram* WWW_4F;
        sampleHistogram* WWZ;
        sampleHistogram* WZG;
        sampleHistogram* WZTo3LNu;
        sampleHistogram* WZZ;
        sampleHistogram* TTJets;
        sampleHistogram* TTHH;
        sampleHistogram* TTTJ;
        sampleHistogram* TTTT;
        sampleHistogram* TTTW;
        sampleHistogram* TTWH;
        sampleHistogram* TTWW;
        sampleHistogram* TTWZ;
        sampleHistogram* TTZH;
        sampleHistogram* TTZZ;
        sampleHistogram* WGToLNuG_01J_5f;
        sampleHistogram* WpWpJJ_EWKQCD;
        sampleHistogram* VHToNonbb_M125;
        sampleHistogram* tZq_ll_4f_ckm_NLO;
        sampleHistogram* ttHToNonbb_M125;
    public:
        makeSampleHistos(string category){
            TTGamma_SingleLept          = new sampleHistogram("TTGamma_SingleLept", category);
            TGJets                      = new sampleHistogram("TGJets", category);
            TTWJetsToLNu                = new sampleHistogram("TTWJetsToLNu", category);
            WJetsToLNu                  = new sampleHistogram("WJetsToLNu", category);
            ST_tWll_5f_LO               = new sampleHistogram("ST_tWll_5f_LO", category);
            TTGamma_Dilept              = new sampleHistogram("TTGamma_Dilept", category);
            TTZToLLNuNu_M10             = new sampleHistogram("TTZToLLNuNu_M10", category);
            TTZToLL_M1to10              = new sampleHistogram("TTZToLL_M1to10", category);
            DYJetsToLL_M10to50          = new sampleHistogram("DYJetsToLL_M10to50", category);
            DYJetsToLL_M50              = new sampleHistogram("DYJetsToLL_M50", category);
            ZGToLLG_01J_5f              = new sampleHistogram("ZGToLLG_01J_5f", category);
            ZZTo4L                      = new sampleHistogram("ZZTo4L", category);
            ZZZ                         = new sampleHistogram("ZZZ", category);
            GluGluHToZZTo4L             = new sampleHistogram("GluGluHToZZTo4L", category);
            GluGluToContinToZZTo2e2mu   = new sampleHistogram("GluGluToContinToZZTo2e2mu", category);
            GluGluToContinToZZTo2e2tau  = new sampleHistogram("GluGluToContinToZZTo2e2tau", category);
            GluGluToContinToZZTo2mu2tau = new sampleHistogram("GluGluToContinToZZTo2mu2tau", category);
            GluGluToContinToZZTo4e      = new sampleHistogram("GluGluToContinToZZTo4e", category);
            GluGluToContinToZZTo4mu     = new sampleHistogram("GluGluToContinToZZTo4mu", category);
            GluGluToContinToZZTo4tau    = new sampleHistogram("GluGluToContinToZZTo4tau", category);
            WWG                         = new sampleHistogram("WWG", category);
            WWTo2L2Nu_DoubleScattering  = new sampleHistogram("WWTo2L2Nu_DoubleScattering", category);
            WWW_4F                      = new sampleHistogram("WWW_4F", category);
            WWZ                         = new sampleHistogram("WWZ", category);
            WZG                         = new sampleHistogram("WZG", category);
            WZTo3LNu                    = new sampleHistogram("WZTo3LNu", category);
            WZZ                         = new sampleHistogram("WZZ", category);
            TTJets                      = new sampleHistogram("TTJets", category);
            TTHH                        = new sampleHistogram("TTHH", category);
            TTTJ                        = new sampleHistogram("TTTJ", category);
            TTTT                        = new sampleHistogram("TTTT", category);
            TTTW                        = new sampleHistogram("TTTW", category);
            TTWH                        = new sampleHistogram("TTWH", category);
            TTWW                        = new sampleHistogram("TTWW", category);
            TTWZ                        = new sampleHistogram("TTWZ", category);
            TTZH                        = new sampleHistogram("TTZH", category);
            TTZZ                        = new sampleHistogram("TTZZ", category);
            WGToLNuG_01J_5f             = new sampleHistogram("WGToLNuG_01J_5f", category);
            WpWpJJ_EWKQCD               = new sampleHistogram("WpWpJJ_EWKQCD", category);
            VHToNonbb_M125              = new sampleHistogram("VHToNonbb_M125", category);
            tZq_ll_4f_ckm_NLO           = new sampleHistogram("tZq_ll_4f_ckm_NLO", category);
            ttHToNonbb_M125             = new sampleHistogram("ttHToNonbb_M125", category);
        }
        void fillHistos(string sampleName, vector<int>variables, float weight){
            int TTGamma_SingleLept_idx = sampleName.find("TTGamma_SingleLept");
            int TGJets_idx = sampleName.find("TGJets");
            int TTWJetsToLNu_idx = sampleName.find("TTWJetsToLNu");
            int WJetsToLNu_idx = sampleName.find("WJetsToLNu");
            int ST_tWll_5f_LO_idx = sampleName.find("ST_tWll_5f_LO");
            int TTGamma_Dilept_idx = sampleName.find("TTGamma_Dilept");
            int TTZToLLNuNu_M10_idx = sampleName.find("TTZToLLNuNu_M-10");
            int TTZToLL_M1to10_idx = sampleName.find("TTZToLL_M-1to10");
            int DYJetsToLL_M10to50_idx = sampleName.find("DYJetsToLL_M-10to50");
            int DYJetsToLL_M50_idx = sampleName.find("DYJetsToLL_M-50");
            int ZGToLLG_01J_5f_idx = sampleName.find("ZGToLLG_01J_5f");
            int ZZTo4L_idx = sampleName.find("ZZTo4L");
            int ZZZ_idx = sampleName.find("ZZZ");
            int GluGluHToZZTo4L_idx = sampleName.find("GluGluHToZZTo4L");
            int GluGluToContinToZZTo2e2mu_idx = sampleName.find("GluGluToContinToZZTo2e2mu");
            int GluGluToContinToZZTo2e2tau_idx = sampleName.find("GluGluToContinToZZTo2e2tau");
            int GluGluToContinToZZTo2mu2tau_idx = sampleName.find("GluGluToContinToZZTo2mu2tau");
            int GluGluToContinToZZTo4e_idx = sampleName.find("GluGluToContinToZZTo4e");
            int GluGluToContinToZZTo4mu_idx = sampleName.find("GluGluToContinToZZTo4mu");
            int GluGluToContinToZZTo4tau_idx = sampleName.find("GluGluToContinToZZTo4tau");
            int WWG_idx = sampleName.find("WWG");
            int WWTo2L2Nu_DoubleScattering_idx = sampleName.find("WWTo2L2Nu_DoubleScattering");
            int WWW_4F_idx = sampleName.find("WWW_4F");
            int WWZ_idx = sampleName.find("WWZ");
            int WZG_idx = sampleName.find("WZG");
            int WZTo3LNu_idx = sampleName.find("WZTo3LNu");
            int WZZ_idx = sampleName.find("WZZ");
            int TTJets_idx = sampleName.find("TTJets");
            int TTHH_idx = sampleName.find("TTHH");
            int TTTJ_idx = sampleName.find("TTTJ");
            int TTTT_idx = sampleName.find("TTTT");
            int TTTW_idx = sampleName.find("TTTW");
            int TTWH_idx = sampleName.find("TTWH");
            int TTWW_idx = sampleName.find("TTWW");
            int TTWZ_idx = sampleName.find("TTWZ");
            int TTZH_idx = sampleName.find("TTZH");
            int TTZZ_idx = sampleName.find("TTZZ");
            int WGToLNuG_01J_5f_idx = sampleName.find("WGToLNuG_01J_5f");
            int WpWpJJ_EWKQCD_idx = sampleName.find("WpWpJJ_EWK-QCD");
            int VHToNonbb_M125_idx = sampleName.find("VHToNonbb_M125");
            int tZq_ll_4f_ckm_NLO_idx = sampleName.find("tZq_ll_4f_ckm_NLO");
            int ttHToNonbb_M125_idx = sampleName.find("ttHToNonbb_M125");

            vector<bool> bkgTypeVars = {bool(variables[0]),bool(variables[1]),bool(variables[2])};
            int nLep = variables[3];
            int nJet = variables[4];
            int nBs = variables[5];

            if(TTGamma_SingleLept_idx!=-1){
                TTGamma_SingleLept->fillSRCategories(nLep, nJet, nBs, weight);
                TTGamma_SingleLept->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TGJets_idx!=-1){
                TGJets->fillSRCategories(nLep, nJet, nBs, weight);
                TGJets->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTWJetsToLNu_idx!=-1){
                TTWJetsToLNu->fillSRCategories(nLep, nJet, nBs, weight);
                TTWJetsToLNu->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WJetsToLNu_idx!=-1){
                WJetsToLNu->fillSRCategories(nLep, nJet, nBs, weight);
                WJetsToLNu->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(ST_tWll_5f_LO_idx!=-1){
                ST_tWll_5f_LO->fillSRCategories(nLep, nJet, nBs, weight);
                ST_tWll_5f_LO->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTGamma_Dilept_idx!=-1){
                TTGamma_Dilept->fillSRCategories(nLep, nJet, nBs, weight);
                TTGamma_Dilept->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTZToLLNuNu_M10_idx!=-1){
                TTZToLLNuNu_M10->fillSRCategories(nLep, nJet, nBs, weight);
                TTZToLLNuNu_M10->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTZToLL_M1to10_idx!=-1){
                TTZToLL_M1to10->fillSRCategories(nLep, nJet, nBs, weight);
                TTZToLL_M1to10->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(DYJetsToLL_M10to50_idx!=-1){
                DYJetsToLL_M10to50->fillSRCategories(nLep, nJet, nBs, weight);
                DYJetsToLL_M10to50->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(DYJetsToLL_M50_idx!=-1){
                DYJetsToLL_M50->fillSRCategories(nLep, nJet, nBs, weight);
                DYJetsToLL_M50->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(ZGToLLG_01J_5f_idx!=-1){
                ZGToLLG_01J_5f->fillSRCategories(nLep, nJet, nBs, weight);
                ZGToLLG_01J_5f->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(ZZTo4L_idx!=-1){
                ZZTo4L->fillSRCategories(nLep, nJet, nBs, weight);
                ZZTo4L->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(ZZZ_idx!=-1){
                ZZZ->fillSRCategories(nLep, nJet, nBs, weight);
                ZZZ->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluHToZZTo4L_idx!=-1){
                GluGluHToZZTo4L->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluHToZZTo4L->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluToContinToZZTo2e2mu_idx!=-1){
                GluGluToContinToZZTo2e2mu->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluToContinToZZTo2e2mu->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluToContinToZZTo2e2tau_idx!=-1){
                GluGluToContinToZZTo2e2tau->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluToContinToZZTo2e2tau->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluToContinToZZTo2mu2tau_idx!=-1){
                GluGluToContinToZZTo2mu2tau->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluToContinToZZTo2mu2tau->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluToContinToZZTo4e_idx!=-1){
                GluGluToContinToZZTo4e->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluToContinToZZTo4e->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluToContinToZZTo4mu_idx!=-1){
                GluGluToContinToZZTo4mu->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluToContinToZZTo4mu->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(GluGluToContinToZZTo4tau_idx!=-1){
                GluGluToContinToZZTo4tau->fillSRCategories(nLep, nJet, nBs, weight);
                GluGluToContinToZZTo4tau->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WWG_idx!=-1){
                WWG->fillSRCategories(nLep, nJet, nBs, weight);
                WWG->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WWTo2L2Nu_DoubleScattering_idx!=-1){
                WWTo2L2Nu_DoubleScattering->fillSRCategories(nLep, nJet, nBs, weight);
                WWTo2L2Nu_DoubleScattering->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WWW_4F_idx!=-1){
                WWW_4F->fillSRCategories(nLep, nJet, nBs, weight);
                WWW_4F->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WWZ_idx!=-1){
                WWZ->fillSRCategories(nLep, nJet, nBs, weight);
                WWZ->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WZG_idx!=-1){
                WZG->fillSRCategories(nLep, nJet, nBs, weight);
                WZG->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WZTo3LNu_idx!=-1){
                WZTo3LNu->fillSRCategories(nLep, nJet, nBs, weight);
                WZTo3LNu->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WZZ_idx!=-1){
                WZZ->fillSRCategories(nLep, nJet, nBs, weight);
                WZZ->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTJets_idx!=-1){
                TTJets->fillSRCategories(nLep, nJet, nBs, weight);
                TTJets->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTHH_idx!=-1){
                TTHH->fillSRCategories(nLep, nJet, nBs, weight);
                TTHH->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTTJ_idx!=-1){
                TTTJ->fillSRCategories(nLep, nJet, nBs, weight);
                TTTJ->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTTT_idx!=-1){
                TTTT->fillSRCategories(nLep, nJet, nBs, weight);
                TTTT->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTTW_idx!=-1){
                TTTW->fillSRCategories(nLep, nJet, nBs, weight);
                TTTW->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTWH_idx!=-1){
                TTWH->fillSRCategories(nLep, nJet, nBs, weight);
                TTWH->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTWW_idx!=-1){
                TTWW->fillSRCategories(nLep, nJet, nBs, weight);
                TTWW->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTWZ_idx!=-1){
                TTWZ->fillSRCategories(nLep, nJet, nBs, weight);
                TTWZ->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTZH_idx!=-1){
                TTZH->fillSRCategories(nLep, nJet, nBs, weight);
                TTZH->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(TTZZ_idx!=-1){
                TTZZ->fillSRCategories(nLep, nJet, nBs, weight);
                TTZZ->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WGToLNuG_01J_5f_idx!=-1){
                WGToLNuG_01J_5f->fillSRCategories(nLep, nJet, nBs, weight);
                WGToLNuG_01J_5f->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(WpWpJJ_EWKQCD_idx!=-1){
                WpWpJJ_EWKQCD->fillSRCategories(nLep, nJet, nBs, weight);
                WpWpJJ_EWKQCD->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(VHToNonbb_M125_idx!=-1){
                VHToNonbb_M125->fillSRCategories(nLep, nJet, nBs, weight);
                VHToNonbb_M125->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(tZq_ll_4f_ckm_NLO_idx!=-1){
                tZq_ll_4f_ckm_NLO->fillSRCategories(nLep, nJet, nBs, weight);
                tZq_ll_4f_ckm_NLO->fillBackgroundTypes(bkgTypeVars, weight);
            }else if(ttHToNonbb_M125_idx!=-1){
                ttHToNonbb_M125->fillSRCategories(nLep, nJet, nBs, weight);
                ttHToNonbb_M125->fillBackgroundTypes(bkgTypeVars, weight);
            }
        }
        void writeHistos(TFile* &outfile){
            TTGamma_SingleLept->writeHistograms(outfile);
            TGJets->writeHistograms(outfile);
            TTWJetsToLNu->writeHistograms(outfile);
            WJetsToLNu->writeHistograms(outfile);
            ST_tWll_5f_LO->writeHistograms(outfile);
            TTGamma_Dilept->writeHistograms(outfile);
            TTZToLLNuNu_M10->writeHistograms(outfile);
            TTZToLL_M1to10->writeHistograms(outfile);
            DYJetsToLL_M10to50->writeHistograms(outfile);
            DYJetsToLL_M50->writeHistograms(outfile);
            ZGToLLG_01J_5f->writeHistograms(outfile);
            ZZTo4L->writeHistograms(outfile);
            ZZZ->writeHistograms(outfile);
            GluGluHToZZTo4L->writeHistograms(outfile);
            GluGluToContinToZZTo2e2mu->writeHistograms(outfile);
            GluGluToContinToZZTo2e2tau->writeHistograms(outfile);
            GluGluToContinToZZTo2mu2tau->writeHistograms(outfile);
            GluGluToContinToZZTo4e->writeHistograms(outfile);
            GluGluToContinToZZTo4mu->writeHistograms(outfile);
            GluGluToContinToZZTo4tau->writeHistograms(outfile);
            WWG->writeHistograms(outfile);
            WWTo2L2Nu_DoubleScattering->writeHistograms(outfile);
            WWW_4F->writeHistograms(outfile);
            WWZ->writeHistograms(outfile);
            WZG->writeHistograms(outfile);
            WZTo3LNu->writeHistograms(outfile);
            WZZ->writeHistograms(outfile);
            TTJets->writeHistograms(outfile);
            TTHH->writeHistograms(outfile);
            TTTJ->writeHistograms(outfile);
            TTTT->writeHistograms(outfile);
            TTTW->writeHistograms(outfile);
            TTWH->writeHistograms(outfile);
            TTWW->writeHistograms(outfile);
            TTWZ->writeHistograms(outfile);
            TTZH->writeHistograms(outfile);
            TTZZ->writeHistograms(outfile);
            WGToLNuG_01J_5f->writeHistograms(outfile);
            WpWpJJ_EWKQCD->writeHistograms(outfile);
            VHToNonbb_M125->writeHistograms(outfile);
            tZq_ll_4f_ckm_NLO->writeHistograms(outfile);
            ttHToNonbb_M125->writeHistograms(outfile);
        }
};





class makeHistograms{
    private:
        categoryHistogram* trilep_2j_0b_fakes;
        categoryHistogram* trilep_2j_1b_fakes;
        categoryHistogram* trilep_2j_ge2b_fakes;
        categoryHistogram* trilep_3j_0b_fakes;
        categoryHistogram* trilep_3j_1b_fakes;
        categoryHistogram* trilep_3j_ge2b_fakes;
        categoryHistogram* trilep_ge4j_0b_fakes;
        categoryHistogram* trilep_ge4j_1b_fakes;
        categoryHistogram* trilep_ge4j_ge2b_fakes;

        categoryHistogram* SS_SF_dilep_2j_0b_fakes;
        categoryHistogram* SS_SF_dilep_2j_1b_fakes;
        categoryHistogram* SS_SF_dilep_2j_ge2b_fakes;
        categoryHistogram* SS_SF_dilep_3j_0b_fakes;
        categoryHistogram* SS_SF_dilep_3j_1b_fakes;
        categoryHistogram* SS_SF_dilep_3j_ge2b_fakes;
        categoryHistogram* SS_SF_dilep_ge4j_0b_fakes;
        categoryHistogram* SS_SF_dilep_ge4j_1b_fakes;
        categoryHistogram* SS_SF_dilep_ge4j_ge2b_fakes;

        categoryHistogram* SS_OF_dilep_2j_0b_fakes;
        categoryHistogram* SS_OF_dilep_2j_1b_fakes;
        categoryHistogram* SS_OF_dilep_2j_ge2b_fakes;
        categoryHistogram* SS_OF_dilep_3j_0b_fakes;
        categoryHistogram* SS_OF_dilep_3j_1b_fakes;
        categoryHistogram* SS_OF_dilep_3j_ge2b_fakes;
        categoryHistogram* SS_OF_dilep_ge4j_0b_fakes;
        categoryHistogram* SS_OF_dilep_ge4j_1b_fakes;
        categoryHistogram* SS_OF_dilep_ge4j_ge2b_fakes;

        categoryHistogram* OS_SF_dilep_2j_0b_fakes;
        categoryHistogram* OS_SF_dilep_2j_1b_fakes;
        categoryHistogram* OS_SF_dilep_2j_ge2b_fakes;
        categoryHistogram* OS_SF_dilep_3j_0b_fakes;
        categoryHistogram* OS_SF_dilep_3j_1b_fakes;
        categoryHistogram* OS_SF_dilep_3j_ge2b_fakes;
        categoryHistogram* OS_SF_dilep_ge4j_0b_fakes;
        categoryHistogram* OS_SF_dilep_ge4j_1b_fakes;
        categoryHistogram* OS_SF_dilep_ge4j_ge2b_fakes;

        categoryHistogram* OS_OF_dilep_2j_0b_fakes;
        categoryHistogram* OS_OF_dilep_2j_1b_fakes;
        categoryHistogram* OS_OF_dilep_2j_ge2b_fakes;
        categoryHistogram* OS_OF_dilep_3j_0b_fakes;
        categoryHistogram* OS_OF_dilep_3j_1b_fakes;
        categoryHistogram* OS_OF_dilep_3j_ge2b_fakes;
        categoryHistogram* OS_OF_dilep_ge4j_0b_fakes;
        categoryHistogram* OS_OF_dilep_ge4j_1b_fakes;
        categoryHistogram* OS_OF_dilep_ge4j_ge2b_fakes;

        categoryHistogram* SS_SF_flipEst_2j_0b_fakes;
        categoryHistogram* SS_SF_flipEst_2j_1b_fakes;
        categoryHistogram* SS_SF_flipEst_2j_ge2b_fakes;
        categoryHistogram* SS_SF_flipEst_3j_0b_fakes;
        categoryHistogram* SS_SF_flipEst_3j_1b_fakes;
        categoryHistogram* SS_SF_flipEst_3j_ge2b_fakes;
        categoryHistogram* SS_SF_flipEst_ge4j_0b_fakes;
        categoryHistogram* SS_SF_flipEst_ge4j_1b_fakes;
        categoryHistogram* SS_SF_flipEst_ge4j_ge2b_fakes;

        categoryHistogram* SS_OF_flipEst_2j_0b_fakes;
        categoryHistogram* SS_OF_flipEst_2j_1b_fakes;
        categoryHistogram* SS_OF_flipEst_2j_ge2b_fakes;
        categoryHistogram* SS_OF_flipEst_3j_0b_fakes;
        categoryHistogram* SS_OF_flipEst_3j_1b_fakes;
        categoryHistogram* SS_OF_flipEst_3j_ge2b_fakes;
        categoryHistogram* SS_OF_flipEst_ge4j_0b_fakes;
        categoryHistogram* SS_OF_flipEst_ge4j_1b_fakes;
        categoryHistogram* SS_OF_flipEst_ge4j_ge2b_fakes;

        categoryHistogram* onelepFO_2j_0b_fakes;
        categoryHistogram* onelepFO_2j_1b_fakes;
        categoryHistogram* onelepFO_2j_ge2b_fakes;
        categoryHistogram* onelepFO_3j_0b_fakes;
        categoryHistogram* onelepFO_3j_1b_fakes;
        categoryHistogram* onelepFO_3j_ge2b_fakes;
        categoryHistogram* onelepFO_ge4j_0b_fakes;
        categoryHistogram* onelepFO_ge4j_1b_fakes;
        categoryHistogram* onelepFO_ge4j_ge2b_fakes;

        categoryHistogram* dilepFO_2j_0b_fakes;
        categoryHistogram* dilepFO_2j_1b_fakes;
        categoryHistogram* dilepFO_2j_ge2b_fakes;
        categoryHistogram* dilepFO_3j_0b_fakes;
        categoryHistogram* dilepFO_3j_1b_fakes;
        categoryHistogram* dilepFO_3j_ge2b_fakes;
        categoryHistogram* dilepFO_ge4j_0b_fakes;
        categoryHistogram* dilepFO_ge4j_1b_fakes;
        categoryHistogram* dilepFO_ge4j_ge2b_fakes;

        categoryHistogram* fakeEst_from1FOCR_2j_0b_fakes;
        categoryHistogram* fakeEst_from1FOCR_2j_1b_fakes;
        categoryHistogram* fakeEst_from1FOCR_2j_ge2b_fakes;
        categoryHistogram* fakeEst_from1FOCR_3j_0b_fakes;
        categoryHistogram* fakeEst_from1FOCR_3j_1b_fakes;
        categoryHistogram* fakeEst_from1FOCR_3j_ge2b_fakes;
        categoryHistogram* fakeEst_from1FOCR_ge4j_0b_fakes;
        categoryHistogram* fakeEst_from1FOCR_ge4j_1b_fakes;
        categoryHistogram* fakeEst_from1FOCR_ge4j_ge2b_fakes;

        categoryHistogram* fakeEst_from2FOCR_2j_0b_fakes;
        categoryHistogram* fakeEst_from2FOCR_2j_1b_fakes;
        categoryHistogram* fakeEst_from2FOCR_2j_ge2b_fakes;
        categoryHistogram* fakeEst_from2FOCR_3j_0b_fakes;
        categoryHistogram* fakeEst_from2FOCR_3j_1b_fakes;
        categoryHistogram* fakeEst_from2FOCR_3j_ge2b_fakes;
        categoryHistogram* fakeEst_from2FOCR_ge4j_0b_fakes;
        categoryHistogram* fakeEst_from2FOCR_ge4j_1b_fakes;
        categoryHistogram* fakeEst_from2FOCR_ge4j_ge2b_fakes;



        categoryHistogram* trilep_2j_0b_flips;
        categoryHistogram* trilep_2j_1b_flips;
        categoryHistogram* trilep_2j_ge2b_flips;
        categoryHistogram* trilep_3j_0b_flips;
        categoryHistogram* trilep_3j_1b_flips;
        categoryHistogram* trilep_3j_ge2b_flips;
        categoryHistogram* trilep_ge4j_0b_flips;
        categoryHistogram* trilep_ge4j_1b_flips;
        categoryHistogram* trilep_ge4j_ge2b_flips;

        categoryHistogram* SS_SF_dilep_2j_0b_flips;
        categoryHistogram* SS_SF_dilep_2j_1b_flips;
        categoryHistogram* SS_SF_dilep_2j_ge2b_flips;
        categoryHistogram* SS_SF_dilep_3j_0b_flips;
        categoryHistogram* SS_SF_dilep_3j_1b_flips;
        categoryHistogram* SS_SF_dilep_3j_ge2b_flips;
        categoryHistogram* SS_SF_dilep_ge4j_0b_flips;
        categoryHistogram* SS_SF_dilep_ge4j_1b_flips;
        categoryHistogram* SS_SF_dilep_ge4j_ge2b_flips;

        categoryHistogram* SS_OF_dilep_2j_0b_flips;
        categoryHistogram* SS_OF_dilep_2j_1b_flips;
        categoryHistogram* SS_OF_dilep_2j_ge2b_flips;
        categoryHistogram* SS_OF_dilep_3j_0b_flips;
        categoryHistogram* SS_OF_dilep_3j_1b_flips;
        categoryHistogram* SS_OF_dilep_3j_ge2b_flips;
        categoryHistogram* SS_OF_dilep_ge4j_0b_flips;
        categoryHistogram* SS_OF_dilep_ge4j_1b_flips;
        categoryHistogram* SS_OF_dilep_ge4j_ge2b_flips;

        categoryHistogram* OS_SF_dilep_2j_0b_flips;
        categoryHistogram* OS_SF_dilep_2j_1b_flips;
        categoryHistogram* OS_SF_dilep_2j_ge2b_flips;
        categoryHistogram* OS_SF_dilep_3j_0b_flips;
        categoryHistogram* OS_SF_dilep_3j_1b_flips;
        categoryHistogram* OS_SF_dilep_3j_ge2b_flips;
        categoryHistogram* OS_SF_dilep_ge4j_0b_flips;
        categoryHistogram* OS_SF_dilep_ge4j_1b_flips;
        categoryHistogram* OS_SF_dilep_ge4j_ge2b_flips;

        categoryHistogram* OS_OF_dilep_2j_0b_flips;
        categoryHistogram* OS_OF_dilep_2j_1b_flips;
        categoryHistogram* OS_OF_dilep_2j_ge2b_flips;
        categoryHistogram* OS_OF_dilep_3j_0b_flips;
        categoryHistogram* OS_OF_dilep_3j_1b_flips;
        categoryHistogram* OS_OF_dilep_3j_ge2b_flips;
        categoryHistogram* OS_OF_dilep_ge4j_0b_flips;
        categoryHistogram* OS_OF_dilep_ge4j_1b_flips;
        categoryHistogram* OS_OF_dilep_ge4j_ge2b_flips;

        categoryHistogram* SS_SF_flipEst_2j_0b_flips;
        categoryHistogram* SS_SF_flipEst_2j_1b_flips;
        categoryHistogram* SS_SF_flipEst_2j_ge2b_flips;
        categoryHistogram* SS_SF_flipEst_3j_0b_flips;
        categoryHistogram* SS_SF_flipEst_3j_1b_flips;
        categoryHistogram* SS_SF_flipEst_3j_ge2b_flips;
        categoryHistogram* SS_SF_flipEst_ge4j_0b_flips;
        categoryHistogram* SS_SF_flipEst_ge4j_1b_flips;
        categoryHistogram* SS_SF_flipEst_ge4j_ge2b_flips;

        categoryHistogram* SS_OF_flipEst_2j_0b_flips;
        categoryHistogram* SS_OF_flipEst_2j_1b_flips;
        categoryHistogram* SS_OF_flipEst_2j_ge2b_flips;
        categoryHistogram* SS_OF_flipEst_3j_0b_flips;
        categoryHistogram* SS_OF_flipEst_3j_1b_flips;
        categoryHistogram* SS_OF_flipEst_3j_ge2b_flips;
        categoryHistogram* SS_OF_flipEst_ge4j_0b_flips;
        categoryHistogram* SS_OF_flipEst_ge4j_1b_flips;
        categoryHistogram* SS_OF_flipEst_ge4j_ge2b_flips;

        categoryHistogram* onelepFO_2j_0b_flips;
        categoryHistogram* onelepFO_2j_1b_flips;
        categoryHistogram* onelepFO_2j_ge2b_flips;
        categoryHistogram* onelepFO_3j_0b_flips;
        categoryHistogram* onelepFO_3j_1b_flips;
        categoryHistogram* onelepFO_3j_ge2b_flips;
        categoryHistogram* onelepFO_ge4j_0b_flips;
        categoryHistogram* onelepFO_ge4j_1b_flips;
        categoryHistogram* onelepFO_ge4j_ge2b_flips;

        categoryHistogram* dilepFO_2j_0b_flips;
        categoryHistogram* dilepFO_2j_1b_flips;
        categoryHistogram* dilepFO_2j_ge2b_flips;
        categoryHistogram* dilepFO_3j_0b_flips;
        categoryHistogram* dilepFO_3j_1b_flips;
        categoryHistogram* dilepFO_3j_ge2b_flips;
        categoryHistogram* dilepFO_ge4j_0b_flips;
        categoryHistogram* dilepFO_ge4j_1b_flips;
        categoryHistogram* dilepFO_ge4j_ge2b_flips;

        categoryHistogram* fakeEst_from1FOCR_2j_0b_flips;
        categoryHistogram* fakeEst_from1FOCR_2j_1b_flips;
        categoryHistogram* fakeEst_from1FOCR_2j_ge2b_flips;
        categoryHistogram* fakeEst_from1FOCR_3j_0b_flips;
        categoryHistogram* fakeEst_from1FOCR_3j_1b_flips;
        categoryHistogram* fakeEst_from1FOCR_3j_ge2b_flips;
        categoryHistogram* fakeEst_from1FOCR_ge4j_0b_flips;
        categoryHistogram* fakeEst_from1FOCR_ge4j_1b_flips;
        categoryHistogram* fakeEst_from1FOCR_ge4j_ge2b_flips;

        categoryHistogram* fakeEst_from2FOCR_2j_0b_flips;
        categoryHistogram* fakeEst_from2FOCR_2j_1b_flips;
        categoryHistogram* fakeEst_from2FOCR_2j_ge2b_flips;
        categoryHistogram* fakeEst_from2FOCR_3j_0b_flips;
        categoryHistogram* fakeEst_from2FOCR_3j_1b_flips;
        categoryHistogram* fakeEst_from2FOCR_3j_ge2b_flips;
        categoryHistogram* fakeEst_from2FOCR_ge4j_0b_flips;
        categoryHistogram* fakeEst_from2FOCR_ge4j_1b_flips;
        categoryHistogram* fakeEst_from2FOCR_ge4j_ge2b_flips;


        categoryHistogram* trilep_2j_0b_other;
        categoryHistogram* trilep_2j_1b_other;
        categoryHistogram* trilep_2j_ge2b_other;
        categoryHistogram* trilep_3j_0b_other;
        categoryHistogram* trilep_3j_1b_other;
        categoryHistogram* trilep_3j_ge2b_other;
        categoryHistogram* trilep_ge4j_0b_other;
        categoryHistogram* trilep_ge4j_1b_other;
        categoryHistogram* trilep_ge4j_ge2b_other;

        categoryHistogram* SS_SF_dilep_2j_0b_other;
        categoryHistogram* SS_SF_dilep_2j_1b_other;
        categoryHistogram* SS_SF_dilep_2j_ge2b_other;
        categoryHistogram* SS_SF_dilep_3j_0b_other;
        categoryHistogram* SS_SF_dilep_3j_1b_other;
        categoryHistogram* SS_SF_dilep_3j_ge2b_other;
        categoryHistogram* SS_SF_dilep_ge4j_0b_other;
        categoryHistogram* SS_SF_dilep_ge4j_1b_other;
        categoryHistogram* SS_SF_dilep_ge4j_ge2b_other;

        categoryHistogram* SS_OF_dilep_2j_0b_other;
        categoryHistogram* SS_OF_dilep_2j_1b_other;
        categoryHistogram* SS_OF_dilep_2j_ge2b_other;
        categoryHistogram* SS_OF_dilep_3j_0b_other;
        categoryHistogram* SS_OF_dilep_3j_1b_other;
        categoryHistogram* SS_OF_dilep_3j_ge2b_other;
        categoryHistogram* SS_OF_dilep_ge4j_0b_other;
        categoryHistogram* SS_OF_dilep_ge4j_1b_other;
        categoryHistogram* SS_OF_dilep_ge4j_ge2b_other;

        categoryHistogram* OS_SF_dilep_2j_0b_other;
        categoryHistogram* OS_SF_dilep_2j_1b_other;
        categoryHistogram* OS_SF_dilep_2j_ge2b_other;
        categoryHistogram* OS_SF_dilep_3j_0b_other;
        categoryHistogram* OS_SF_dilep_3j_1b_other;
        categoryHistogram* OS_SF_dilep_3j_ge2b_other;
        categoryHistogram* OS_SF_dilep_ge4j_0b_other;
        categoryHistogram* OS_SF_dilep_ge4j_1b_other;
        categoryHistogram* OS_SF_dilep_ge4j_ge2b_other;

        categoryHistogram* OS_OF_dilep_2j_0b_other;
        categoryHistogram* OS_OF_dilep_2j_1b_other;
        categoryHistogram* OS_OF_dilep_2j_ge2b_other;
        categoryHistogram* OS_OF_dilep_3j_0b_other;
        categoryHistogram* OS_OF_dilep_3j_1b_other;
        categoryHistogram* OS_OF_dilep_3j_ge2b_other;
        categoryHistogram* OS_OF_dilep_ge4j_0b_other;
        categoryHistogram* OS_OF_dilep_ge4j_1b_other;
        categoryHistogram* OS_OF_dilep_ge4j_ge2b_other;

        categoryHistogram* SS_SF_flipEst_2j_0b_other;
        categoryHistogram* SS_SF_flipEst_2j_1b_other;
        categoryHistogram* SS_SF_flipEst_2j_ge2b_other;
        categoryHistogram* SS_SF_flipEst_3j_0b_other;
        categoryHistogram* SS_SF_flipEst_3j_1b_other;
        categoryHistogram* SS_SF_flipEst_3j_ge2b_other;
        categoryHistogram* SS_SF_flipEst_ge4j_0b_other;
        categoryHistogram* SS_SF_flipEst_ge4j_1b_other;
        categoryHistogram* SS_SF_flipEst_ge4j_ge2b_other;

        categoryHistogram* SS_OF_flipEst_2j_0b_other;
        categoryHistogram* SS_OF_flipEst_2j_1b_other;
        categoryHistogram* SS_OF_flipEst_2j_ge2b_other;
        categoryHistogram* SS_OF_flipEst_3j_0b_other;
        categoryHistogram* SS_OF_flipEst_3j_1b_other;
        categoryHistogram* SS_OF_flipEst_3j_ge2b_other;
        categoryHistogram* SS_OF_flipEst_ge4j_0b_other;
        categoryHistogram* SS_OF_flipEst_ge4j_1b_other;
        categoryHistogram* SS_OF_flipEst_ge4j_ge2b_other;

        categoryHistogram* onelepFO_2j_0b_other;
        categoryHistogram* onelepFO_2j_1b_other;
        categoryHistogram* onelepFO_2j_ge2b_other;
        categoryHistogram* onelepFO_3j_0b_other;
        categoryHistogram* onelepFO_3j_1b_other;
        categoryHistogram* onelepFO_3j_ge2b_other;
        categoryHistogram* onelepFO_ge4j_0b_other;
        categoryHistogram* onelepFO_ge4j_1b_other;
        categoryHistogram* onelepFO_ge4j_ge2b_other;

        categoryHistogram* dilepFO_2j_0b_other;
        categoryHistogram* dilepFO_2j_1b_other;
        categoryHistogram* dilepFO_2j_ge2b_other;
        categoryHistogram* dilepFO_3j_0b_other;
        categoryHistogram* dilepFO_3j_1b_other;
        categoryHistogram* dilepFO_3j_ge2b_other;
        categoryHistogram* dilepFO_ge4j_0b_other;
        categoryHistogram* dilepFO_ge4j_1b_other;
        categoryHistogram* dilepFO_ge4j_ge2b_other;

        categoryHistogram* fakeEst_from1FOCR_2j_0b_other;
        categoryHistogram* fakeEst_from1FOCR_2j_1b_other;
        categoryHistogram* fakeEst_from1FOCR_2j_ge2b_other;
        categoryHistogram* fakeEst_from1FOCR_3j_0b_other;
        categoryHistogram* fakeEst_from1FOCR_3j_1b_other;
        categoryHistogram* fakeEst_from1FOCR_3j_ge2b_other;
        categoryHistogram* fakeEst_from1FOCR_ge4j_0b_other;
        categoryHistogram* fakeEst_from1FOCR_ge4j_1b_other;
        categoryHistogram* fakeEst_from1FOCR_ge4j_ge2b_other;

        categoryHistogram* fakeEst_from2FOCR_2j_0b_other;
        categoryHistogram* fakeEst_from2FOCR_2j_1b_other;
        categoryHistogram* fakeEst_from2FOCR_2j_ge2b_other;
        categoryHistogram* fakeEst_from2FOCR_3j_0b_other;
        categoryHistogram* fakeEst_from2FOCR_3j_1b_other;
        categoryHistogram* fakeEst_from2FOCR_3j_ge2b_other;
        categoryHistogram* fakeEst_from2FOCR_ge4j_0b_other;
        categoryHistogram* fakeEst_from2FOCR_ge4j_1b_other;
        categoryHistogram* fakeEst_from2FOCR_ge4j_ge2b_other;



        categoryHistogram* trilep_2j_0b;
        categoryHistogram* trilep_2j_1b;
        categoryHistogram* trilep_2j_ge2b;
        categoryHistogram* trilep_3j_0b;
        categoryHistogram* trilep_3j_1b;
        categoryHistogram* trilep_3j_ge2b;
        categoryHistogram* trilep_ge4j_0b;
        categoryHistogram* trilep_ge4j_1b;
        categoryHistogram* trilep_ge4j_ge2b;

        categoryHistogram* SS_SF_dilep_2j_0b;
        categoryHistogram* SS_SF_dilep_2j_1b;
        categoryHistogram* SS_SF_dilep_2j_ge2b;
        categoryHistogram* SS_SF_dilep_3j_0b;
        categoryHistogram* SS_SF_dilep_3j_1b;
        categoryHistogram* SS_SF_dilep_3j_ge2b;
        categoryHistogram* SS_SF_dilep_ge4j_0b;
        categoryHistogram* SS_SF_dilep_ge4j_1b;
        categoryHistogram* SS_SF_dilep_ge4j_ge2b;

        categoryHistogram* SS_OF_dilep_2j_0b;
        categoryHistogram* SS_OF_dilep_2j_1b;
        categoryHistogram* SS_OF_dilep_2j_ge2b;
        categoryHistogram* SS_OF_dilep_3j_0b;
        categoryHistogram* SS_OF_dilep_3j_1b;
        categoryHistogram* SS_OF_dilep_3j_ge2b;
        categoryHistogram* SS_OF_dilep_ge4j_0b;
        categoryHistogram* SS_OF_dilep_ge4j_1b;
        categoryHistogram* SS_OF_dilep_ge4j_ge2b;

        categoryHistogram* OS_SF_dilep_2j_0b;
        categoryHistogram* OS_SF_dilep_2j_1b;
        categoryHistogram* OS_SF_dilep_2j_ge2b;
        categoryHistogram* OS_SF_dilep_3j_0b;
        categoryHistogram* OS_SF_dilep_3j_1b;
        categoryHistogram* OS_SF_dilep_3j_ge2b;
        categoryHistogram* OS_SF_dilep_ge4j_0b;
        categoryHistogram* OS_SF_dilep_ge4j_1b;
        categoryHistogram* OS_SF_dilep_ge4j_ge2b;

        categoryHistogram* OS_OF_dilep_2j_0b;
        categoryHistogram* OS_OF_dilep_2j_1b;
        categoryHistogram* OS_OF_dilep_2j_ge2b;
        categoryHistogram* OS_OF_dilep_3j_0b;
        categoryHistogram* OS_OF_dilep_3j_1b;
        categoryHistogram* OS_OF_dilep_3j_ge2b;
        categoryHistogram* OS_OF_dilep_ge4j_0b;
        categoryHistogram* OS_OF_dilep_ge4j_1b;
        categoryHistogram* OS_OF_dilep_ge4j_ge2b;

        categoryHistogram* SS_SF_flipEst_2j_0b;
        categoryHistogram* SS_SF_flipEst_2j_1b;
        categoryHistogram* SS_SF_flipEst_2j_ge2b;
        categoryHistogram* SS_SF_flipEst_3j_0b;
        categoryHistogram* SS_SF_flipEst_3j_1b;
        categoryHistogram* SS_SF_flipEst_3j_ge2b;
        categoryHistogram* SS_SF_flipEst_ge4j_0b;
        categoryHistogram* SS_SF_flipEst_ge4j_1b;
        categoryHistogram* SS_SF_flipEst_ge4j_ge2b;

        categoryHistogram* SS_OF_flipEst_2j_0b;
        categoryHistogram* SS_OF_flipEst_2j_1b;
        categoryHistogram* SS_OF_flipEst_2j_ge2b;
        categoryHistogram* SS_OF_flipEst_3j_0b;
        categoryHistogram* SS_OF_flipEst_3j_1b;
        categoryHistogram* SS_OF_flipEst_3j_ge2b;
        categoryHistogram* SS_OF_flipEst_ge4j_0b;
        categoryHistogram* SS_OF_flipEst_ge4j_1b;
        categoryHistogram* SS_OF_flipEst_ge4j_ge2b;

        categoryHistogram* onelepFO_2j_0b;
        categoryHistogram* onelepFO_2j_1b;
        categoryHistogram* onelepFO_2j_ge2b;
        categoryHistogram* onelepFO_3j_0b;
        categoryHistogram* onelepFO_3j_1b;
        categoryHistogram* onelepFO_3j_ge2b;
        categoryHistogram* onelepFO_ge4j_0b;
        categoryHistogram* onelepFO_ge4j_1b;
        categoryHistogram* onelepFO_ge4j_ge2b;

        categoryHistogram* dilepFO_2j_0b;
        categoryHistogram* dilepFO_2j_1b;
        categoryHistogram* dilepFO_2j_ge2b;
        categoryHistogram* dilepFO_3j_0b;
        categoryHistogram* dilepFO_3j_1b;
        categoryHistogram* dilepFO_3j_ge2b;
        categoryHistogram* dilepFO_ge4j_0b;
        categoryHistogram* dilepFO_ge4j_1b;
        categoryHistogram* dilepFO_ge4j_ge2b;

        categoryHistogram* fakeEst_from1FOCR_2j_0b;
        categoryHistogram* fakeEst_from1FOCR_2j_1b;
        categoryHistogram* fakeEst_from1FOCR_2j_ge2b;
        categoryHistogram* fakeEst_from1FOCR_3j_0b;
        categoryHistogram* fakeEst_from1FOCR_3j_1b;
        categoryHistogram* fakeEst_from1FOCR_3j_ge2b;
        categoryHistogram* fakeEst_from1FOCR_ge4j_0b;
        categoryHistogram* fakeEst_from1FOCR_ge4j_1b;
        categoryHistogram* fakeEst_from1FOCR_ge4j_ge2b;

        categoryHistogram* fakeEst_from2FOCR_2j_0b;
        categoryHistogram* fakeEst_from2FOCR_2j_1b;
        categoryHistogram* fakeEst_from2FOCR_2j_ge2b;
        categoryHistogram* fakeEst_from2FOCR_3j_0b;
        categoryHistogram* fakeEst_from2FOCR_3j_1b;
        categoryHistogram* fakeEst_from2FOCR_3j_ge2b;
        categoryHistogram* fakeEst_from2FOCR_ge4j_0b;
        categoryHistogram* fakeEst_from2FOCR_ge4j_1b;
        categoryHistogram* fakeEst_from2FOCR_ge4j_ge2b;


    public:
        makeHistograms(string category){
            if (category == "background"){

                //***********************************************************
                //***********************************************************
                //***********************************************************
                //SR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                trilep_2j_0b_fakes      = new categoryHistogram("trilep","2j","0b","fakes");
                trilep_2j_1b_fakes      = new categoryHistogram("trilep","2j","1b","fakes");
                trilep_2j_ge2b_fakes    = new categoryHistogram("trilep","2j","ge2b","fakes");
                trilep_3j_0b_fakes      = new categoryHistogram("trilep","3j","0b","fakes");
                trilep_3j_1b_fakes      = new categoryHistogram("trilep","3j","1b","fakes");
                trilep_3j_ge2b_fakes    = new categoryHistogram("trilep","3j","ge2b","fakes");
                trilep_ge4j_0b_fakes    = new categoryHistogram("trilep","ge4j","0b","fakes");
                trilep_ge4j_1b_fakes    = new categoryHistogram("trilep","ge4j","1b","fakes");
                trilep_ge4j_ge2b_fakes  = new categoryHistogram("trilep","ge4j","ge2b","fakes");

                SS_SF_dilep_2j_0b_fakes     = new categoryHistogram("SS_SF_dilep","2j","0b","fakes");
                SS_SF_dilep_2j_1b_fakes     = new categoryHistogram("SS_SF_dilep","2j","1b","fakes");
                SS_SF_dilep_2j_ge2b_fakes   = new categoryHistogram("SS_SF_dilep","2j","ge2b","fakes");
                SS_SF_dilep_3j_0b_fakes     = new categoryHistogram("SS_SF_dilep","3j","0b","fakes");
                SS_SF_dilep_3j_1b_fakes     = new categoryHistogram("SS_SF_dilep","3j","1b","fakes");
                SS_SF_dilep_3j_ge2b_fakes   = new categoryHistogram("SS_SF_dilep","3j","ge2b","fakes");
                SS_SF_dilep_ge4j_0b_fakes   = new categoryHistogram("SS_SF_dilep","ge4j","0b","fakes");
                SS_SF_dilep_ge4j_1b_fakes   = new categoryHistogram("SS_SF_dilep","ge4j","1b","fakes");
                SS_SF_dilep_ge4j_ge2b_fakes = new categoryHistogram("SS_SF_dilep","ge4j","ge2b","fakes");

                SS_OF_dilep_2j_0b_fakes     = new categoryHistogram("SS_OF_dilep","2j","0b","fakes");
                SS_OF_dilep_2j_1b_fakes     = new categoryHistogram("SS_OF_dilep","2j","1b","fakes");
                SS_OF_dilep_2j_ge2b_fakes   = new categoryHistogram("SS_OF_dilep","2j","ge2b","fakes");
                SS_OF_dilep_3j_0b_fakes     = new categoryHistogram("SS_OF_dilep","3j","0b","fakes");
                SS_OF_dilep_3j_1b_fakes     = new categoryHistogram("SS_OF_dilep","3j","1b","fakes");
                SS_OF_dilep_3j_ge2b_fakes   = new categoryHistogram("SS_OF_dilep","3j","ge2b","fakes");
                SS_OF_dilep_ge4j_0b_fakes   = new categoryHistogram("SS_OF_dilep","ge4j","0b","fakes");
                SS_OF_dilep_ge4j_1b_fakes   = new categoryHistogram("SS_OF_dilep","ge4j","1b","fakes");
                SS_OF_dilep_ge4j_ge2b_fakes = new categoryHistogram("SS_OF_dilep","ge4j","ge2b","fakes");

                
                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FLIP CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                OS_SF_dilep_2j_0b_fakes     = new categoryHistogram("OS_SF_dilep","2j","0b","fakes");
                OS_SF_dilep_2j_1b_fakes     = new categoryHistogram("OS_SF_dilep","2j","1b","fakes");
                OS_SF_dilep_2j_ge2b_fakes   = new categoryHistogram("OS_SF_dilep","2j","ge2b","fakes");
                OS_SF_dilep_3j_0b_fakes     = new categoryHistogram("OS_SF_dilep","3j","0b","fakes");
                OS_SF_dilep_3j_1b_fakes     = new categoryHistogram("OS_SF_dilep","3j","1b","fakes");
                OS_SF_dilep_3j_ge2b_fakes   = new categoryHistogram("OS_SF_dilep","3j","ge2b","fakes");
                OS_SF_dilep_ge4j_0b_fakes   = new categoryHistogram("OS_SF_dilep","ge4j","0b","fakes");
                OS_SF_dilep_ge4j_1b_fakes   = new categoryHistogram("OS_SF_dilep","ge4j","1b","fakes");
                OS_SF_dilep_ge4j_ge2b_fakes = new categoryHistogram("OS_SF_dilep","ge4j","ge2b","fakes");

                OS_OF_dilep_2j_0b_fakes     = new categoryHistogram("OS_OF_dilep","2j","0b","fakes");
                OS_OF_dilep_2j_1b_fakes     = new categoryHistogram("OS_OF_dilep","2j","1b","fakes");
                OS_OF_dilep_2j_ge2b_fakes   = new categoryHistogram("OS_OF_dilep","2j","ge2b","fakes");
                OS_OF_dilep_3j_0b_fakes     = new categoryHistogram("OS_OF_dilep","3j","0b","fakes");
                OS_OF_dilep_3j_1b_fakes     = new categoryHistogram("OS_OF_dilep","3j","1b","fakes");
                OS_OF_dilep_3j_ge2b_fakes   = new categoryHistogram("OS_OF_dilep","3j","ge2b","fakes");
                OS_OF_dilep_ge4j_0b_fakes   = new categoryHistogram("OS_OF_dilep","ge4j","0b","fakes");
                OS_OF_dilep_ge4j_1b_fakes   = new categoryHistogram("OS_OF_dilep","ge4j","1b","fakes");
                OS_OF_dilep_ge4j_ge2b_fakes = new categoryHistogram("OS_OF_dilep","ge4j","ge2b","fakes");

                SS_SF_flipEst_2j_0b_fakes     = new categoryHistogram("SS_SF_flipEst","2j","0b","fakes");
                SS_SF_flipEst_2j_1b_fakes     = new categoryHistogram("SS_SF_flipEst","2j","1b","fakes");
                SS_SF_flipEst_2j_ge2b_fakes   = new categoryHistogram("SS_SF_flipEst","2j","ge2b","fakes");
                SS_SF_flipEst_3j_0b_fakes     = new categoryHistogram("SS_SF_flipEst","3j","0b","fakes");
                SS_SF_flipEst_3j_1b_fakes     = new categoryHistogram("SS_SF_flipEst","3j","1b","fakes");
                SS_SF_flipEst_3j_ge2b_fakes   = new categoryHistogram("SS_SF_flipEst","3j","ge2b","fakes");
                SS_SF_flipEst_ge4j_0b_fakes   = new categoryHistogram("SS_SF_flipEst","ge4j","0b","fakes");
                SS_SF_flipEst_ge4j_1b_fakes   = new categoryHistogram("SS_SF_flipEst","ge4j","1b","fakes");
                SS_SF_flipEst_ge4j_ge2b_fakes = new categoryHistogram("SS_SF_flipEst","ge4j","ge2b","fakes");

                SS_OF_flipEst_2j_0b_fakes     = new categoryHistogram("SS_OF_flipEst","2j","0b","fakes");
                SS_OF_flipEst_2j_1b_fakes     = new categoryHistogram("SS_OF_flipEst","2j","1b","fakes");
                SS_OF_flipEst_2j_ge2b_fakes   = new categoryHistogram("SS_OF_flipEst","2j","ge2b","fakes");
                SS_OF_flipEst_3j_0b_fakes     = new categoryHistogram("SS_OF_flipEst","3j","0b","fakes");
                SS_OF_flipEst_3j_1b_fakes     = new categoryHistogram("SS_OF_flipEst","3j","1b","fakes");
                SS_OF_flipEst_3j_ge2b_fakes   = new categoryHistogram("SS_OF_flipEst","3j","ge2b","fakes");
                SS_OF_flipEst_ge4j_0b_fakes   = new categoryHistogram("SS_OF_flipEst","ge4j","0b","fakes");
                SS_OF_flipEst_ge4j_1b_fakes   = new categoryHistogram("SS_OF_flipEst","ge4j","1b","fakes");
                SS_OF_flipEst_ge4j_ge2b_fakes = new categoryHistogram("SS_OF_flipEst","ge4j","ge2b","fakes");


                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FAKE CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                onelepFO_2j_0b_fakes        = new categoryHistogram("onelepFO","2j","0b","fakes");
                onelepFO_2j_1b_fakes        = new categoryHistogram("onelepFO","2j","1b","fakes");
                onelepFO_2j_ge2b_fakes      = new categoryHistogram("onelepFO","2j","ge2b","fakes");
                onelepFO_3j_0b_fakes        = new categoryHistogram("onelepFO","3j","0b","fakes");
                onelepFO_3j_1b_fakes        = new categoryHistogram("onelepFO","3j","1b","fakes");
                onelepFO_3j_ge2b_fakes      = new categoryHistogram("onelepFO","3j","ge2b","fakes");
                onelepFO_ge4j_0b_fakes      = new categoryHistogram("onelepFO","ge4j","0b","fakes");
                onelepFO_ge4j_1b_fakes      = new categoryHistogram("onelepFO","ge4j","1b","fakes");
                onelepFO_ge4j_ge2b_fakes    = new categoryHistogram("onelepFO","ge4j","ge2b","fakes");

                dilepFO_2j_0b_fakes         = new categoryHistogram("dilepFO","2j","0b","fakes");
                dilepFO_2j_1b_fakes         = new categoryHistogram("dilepFO","2j","1b","fakes");
                dilepFO_2j_ge2b_fakes       = new categoryHistogram("dilepFO","2j","ge2b","fakes");
                dilepFO_3j_0b_fakes         = new categoryHistogram("dilepFO","3j","0b","fakes");
                dilepFO_3j_1b_fakes         = new categoryHistogram("dilepFO","3j","1b","fakes");
                dilepFO_3j_ge2b_fakes       = new categoryHistogram("dilepFO","3j","ge2b","fakes");
                dilepFO_ge4j_0b_fakes       = new categoryHistogram("dilepFO","ge4j","0b","fakes");
                dilepFO_ge4j_1b_fakes       = new categoryHistogram("dilepFO","ge4j","1b","fakes");
                dilepFO_ge4j_ge2b_fakes     = new categoryHistogram("dilepFO","ge4j","ge2b","fakes");

                fakeEst_from1FOCR_2j_0b_fakes        = new categoryHistogram("fakeEst_from1FOCR","2j","0b","fakes");
                fakeEst_from1FOCR_2j_1b_fakes        = new categoryHistogram("fakeEst_from1FOCR","2j","1b","fakes");
                fakeEst_from1FOCR_2j_ge2b_fakes      = new categoryHistogram("fakeEst_from1FOCR","2j","ge2b","fakes");
                fakeEst_from1FOCR_3j_0b_fakes        = new categoryHistogram("fakeEst_from1FOCR","3j","0b","fakes");
                fakeEst_from1FOCR_3j_1b_fakes        = new categoryHistogram("fakeEst_from1FOCR","3j","1b","fakes");
                fakeEst_from1FOCR_3j_ge2b_fakes      = new categoryHistogram("fakeEst_from1FOCR","3j","ge2b","fakes");
                fakeEst_from1FOCR_ge4j_0b_fakes      = new categoryHistogram("fakeEst_from1FOCR","ge4j","0b","fakes");
                fakeEst_from1FOCR_ge4j_1b_fakes      = new categoryHistogram("fakeEst_from1FOCR","ge4j","1b","fakes");
                fakeEst_from1FOCR_ge4j_ge2b_fakes    = new categoryHistogram("fakeEst_from1FOCR","ge4j","ge2b","fakes");

                fakeEst_from2FOCR_2j_0b_fakes         = new categoryHistogram("fakeEst_from2FOCR","2j","0b","fakes");
                fakeEst_from2FOCR_2j_1b_fakes         = new categoryHistogram("fakeEst_from2FOCR","2j","1b","fakes");
                fakeEst_from2FOCR_2j_ge2b_fakes       = new categoryHistogram("fakeEst_from2FOCR","2j","ge2b","fakes");
                fakeEst_from2FOCR_3j_0b_fakes         = new categoryHistogram("fakeEst_from2FOCR","3j","0b","fakes");
                fakeEst_from2FOCR_3j_1b_fakes         = new categoryHistogram("fakeEst_from2FOCR","3j","1b","fakes");
                fakeEst_from2FOCR_3j_ge2b_fakes       = new categoryHistogram("fakeEst_from2FOCR","3j","ge2b","fakes");
                fakeEst_from2FOCR_ge4j_0b_fakes       = new categoryHistogram("fakeEst_from2FOCR","ge4j","0b","fakes");
                fakeEst_from2FOCR_ge4j_1b_fakes       = new categoryHistogram("fakeEst_from2FOCR","ge4j","1b","fakes");
                fakeEst_from2FOCR_ge4j_ge2b_fakes     = new categoryHistogram("fakeEst_from2FOCR","ge4j","ge2b","fakes");



                //***********************************************************
                //***********************************************************
                //***********************************************************
                //SR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                trilep_2j_0b_flips      = new categoryHistogram("trilep","2j","0b","flips");
                trilep_2j_1b_flips      = new categoryHistogram("trilep","2j","1b","flips");
                trilep_2j_ge2b_flips    = new categoryHistogram("trilep","2j","ge2b","flips");
                trilep_3j_0b_flips      = new categoryHistogram("trilep","3j","0b","flips");
                trilep_3j_1b_flips      = new categoryHistogram("trilep","3j","1b","flips");
                trilep_3j_ge2b_flips    = new categoryHistogram("trilep","3j","ge2b","flips");
                trilep_ge4j_0b_flips    = new categoryHistogram("trilep","ge4j","0b","flips");
                trilep_ge4j_1b_flips    = new categoryHistogram("trilep","ge4j","1b","flips");
                trilep_ge4j_ge2b_flips  = new categoryHistogram("trilep","ge4j","ge2b","flips");

                SS_SF_dilep_2j_0b_flips     = new categoryHistogram("SS_SF_dilep","2j","0b","flips");
                SS_SF_dilep_2j_1b_flips     = new categoryHistogram("SS_SF_dilep","2j","1b","flips");
                SS_SF_dilep_2j_ge2b_flips   = new categoryHistogram("SS_SF_dilep","2j","ge2b","flips");
                SS_SF_dilep_3j_0b_flips     = new categoryHistogram("SS_SF_dilep","3j","0b","flips");
                SS_SF_dilep_3j_1b_flips     = new categoryHistogram("SS_SF_dilep","3j","1b","flips");
                SS_SF_dilep_3j_ge2b_flips   = new categoryHistogram("SS_SF_dilep","3j","ge2b","flips");
                SS_SF_dilep_ge4j_0b_flips   = new categoryHistogram("SS_SF_dilep","ge4j","0b","flips");
                SS_SF_dilep_ge4j_1b_flips   = new categoryHistogram("SS_SF_dilep","ge4j","1b","flips");
                SS_SF_dilep_ge4j_ge2b_flips = new categoryHistogram("SS_SF_dilep","ge4j","ge2b","flips");

                SS_OF_dilep_2j_0b_flips     = new categoryHistogram("SS_OF_dilep","2j","0b","flips");
                SS_OF_dilep_2j_1b_flips     = new categoryHistogram("SS_OF_dilep","2j","1b","flips");
                SS_OF_dilep_2j_ge2b_flips   = new categoryHistogram("SS_OF_dilep","2j","ge2b","flips");
                SS_OF_dilep_3j_0b_flips     = new categoryHistogram("SS_OF_dilep","3j","0b","flips");
                SS_OF_dilep_3j_1b_flips     = new categoryHistogram("SS_OF_dilep","3j","1b","flips");
                SS_OF_dilep_3j_ge2b_flips   = new categoryHistogram("SS_OF_dilep","3j","ge2b","flips");
                SS_OF_dilep_ge4j_0b_flips   = new categoryHistogram("SS_OF_dilep","ge4j","0b","flips");
                SS_OF_dilep_ge4j_1b_flips   = new categoryHistogram("SS_OF_dilep","ge4j","1b","flips");
                SS_OF_dilep_ge4j_ge2b_flips = new categoryHistogram("SS_OF_dilep","ge4j","ge2b","flips");

                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FLIP CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                OS_SF_dilep_2j_0b_flips     = new categoryHistogram("OS_SF_dilep","2j","0b","flips");
                OS_SF_dilep_2j_1b_flips     = new categoryHistogram("OS_SF_dilep","2j","1b","flips");
                OS_SF_dilep_2j_ge2b_flips   = new categoryHistogram("OS_SF_dilep","2j","ge2b","flips");
                OS_SF_dilep_3j_0b_flips     = new categoryHistogram("OS_SF_dilep","3j","0b","flips");
                OS_SF_dilep_3j_1b_flips     = new categoryHistogram("OS_SF_dilep","3j","1b","flips");
                OS_SF_dilep_3j_ge2b_flips   = new categoryHistogram("OS_SF_dilep","3j","ge2b","flips");
                OS_SF_dilep_ge4j_0b_flips   = new categoryHistogram("OS_SF_dilep","ge4j","0b","flips");
                OS_SF_dilep_ge4j_1b_flips   = new categoryHistogram("OS_SF_dilep","ge4j","1b","flips");
                OS_SF_dilep_ge4j_ge2b_flips = new categoryHistogram("OS_SF_dilep","ge4j","ge2b","flips");

                OS_OF_dilep_2j_0b_flips     = new categoryHistogram("OS_OF_dilep","2j","0b","flips");
                OS_OF_dilep_2j_1b_flips     = new categoryHistogram("OS_OF_dilep","2j","1b","flips");
                OS_OF_dilep_2j_ge2b_flips   = new categoryHistogram("OS_OF_dilep","2j","ge2b","flips");
                OS_OF_dilep_3j_0b_flips     = new categoryHistogram("OS_OF_dilep","3j","0b","flips");
                OS_OF_dilep_3j_1b_flips     = new categoryHistogram("OS_OF_dilep","3j","1b","flips");
                OS_OF_dilep_3j_ge2b_flips   = new categoryHistogram("OS_OF_dilep","3j","ge2b","flips");
                OS_OF_dilep_ge4j_0b_flips   = new categoryHistogram("OS_OF_dilep","ge4j","0b","flips");
                OS_OF_dilep_ge4j_1b_flips   = new categoryHistogram("OS_OF_dilep","ge4j","1b","flips");
                OS_OF_dilep_ge4j_ge2b_flips = new categoryHistogram("OS_OF_dilep","ge4j","ge2b","flips");

                SS_SF_flipEst_2j_0b_flips     = new categoryHistogram("SS_SF_flipEst","2j","0b","flips");
                SS_SF_flipEst_2j_1b_flips     = new categoryHistogram("SS_SF_flipEst","2j","1b","flips");
                SS_SF_flipEst_2j_ge2b_flips   = new categoryHistogram("SS_SF_flipEst","2j","ge2b","flips");
                SS_SF_flipEst_3j_0b_flips     = new categoryHistogram("SS_SF_flipEst","3j","0b","flips");
                SS_SF_flipEst_3j_1b_flips     = new categoryHistogram("SS_SF_flipEst","3j","1b","flips");
                SS_SF_flipEst_3j_ge2b_flips   = new categoryHistogram("SS_SF_flipEst","3j","ge2b","flips");
                SS_SF_flipEst_ge4j_0b_flips   = new categoryHistogram("SS_SF_flipEst","ge4j","0b","flips");
                SS_SF_flipEst_ge4j_1b_flips   = new categoryHistogram("SS_SF_flipEst","ge4j","1b","flips");
                SS_SF_flipEst_ge4j_ge2b_flips = new categoryHistogram("SS_SF_flipEst","ge4j","ge2b","flips");

                SS_OF_flipEst_2j_0b_flips     = new categoryHistogram("SS_OF_flipEst","2j","0b","flips");
                SS_OF_flipEst_2j_1b_flips     = new categoryHistogram("SS_OF_flipEst","2j","1b","flips");
                SS_OF_flipEst_2j_ge2b_flips   = new categoryHistogram("SS_OF_flipEst","2j","ge2b","flips");
                SS_OF_flipEst_3j_0b_flips     = new categoryHistogram("SS_OF_flipEst","3j","0b","flips");
                SS_OF_flipEst_3j_1b_flips     = new categoryHistogram("SS_OF_flipEst","3j","1b","flips");
                SS_OF_flipEst_3j_ge2b_flips   = new categoryHistogram("SS_OF_flipEst","3j","ge2b","flips");
                SS_OF_flipEst_ge4j_0b_flips   = new categoryHistogram("SS_OF_flipEst","ge4j","0b","flips");
                SS_OF_flipEst_ge4j_1b_flips   = new categoryHistogram("SS_OF_flipEst","ge4j","1b","flips");
                SS_OF_flipEst_ge4j_ge2b_flips = new categoryHistogram("SS_OF_flipEst","ge4j","ge2b","flips");


                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FAKE CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                onelepFO_2j_0b_flips        = new categoryHistogram("onelepFO","2j","0b","flips");
                onelepFO_2j_1b_flips        = new categoryHistogram("onelepFO","2j","1b","flips");
                onelepFO_2j_ge2b_flips      = new categoryHistogram("onelepFO","2j","ge2b","flips");
                onelepFO_3j_0b_flips        = new categoryHistogram("onelepFO","3j","0b","flips");
                onelepFO_3j_1b_flips        = new categoryHistogram("onelepFO","3j","1b","flips");
                onelepFO_3j_ge2b_flips      = new categoryHistogram("onelepFO","3j","ge2b","flips");
                onelepFO_ge4j_0b_flips      = new categoryHistogram("onelepFO","ge4j","0b","flips");
                onelepFO_ge4j_1b_flips      = new categoryHistogram("onelepFO","ge4j","1b","flips");
                onelepFO_ge4j_ge2b_flips    = new categoryHistogram("onelepFO","ge4j","ge2b","flips");

                dilepFO_2j_0b_flips         = new categoryHistogram("dilepFO","2j","0b","flips");
                dilepFO_2j_1b_flips         = new categoryHistogram("dilepFO","2j","1b","flips");
                dilepFO_2j_ge2b_flips       = new categoryHistogram("dilepFO","2j","ge2b","flips");
                dilepFO_3j_0b_flips         = new categoryHistogram("dilepFO","3j","0b","flips");
                dilepFO_3j_1b_flips         = new categoryHistogram("dilepFO","3j","1b","flips");
                dilepFO_3j_ge2b_flips       = new categoryHistogram("dilepFO","3j","ge2b","flips");
                dilepFO_ge4j_0b_flips       = new categoryHistogram("dilepFO","ge4j","0b","flips");
                dilepFO_ge4j_1b_flips       = new categoryHistogram("dilepFO","ge4j","1b","flips");
                dilepFO_ge4j_ge2b_flips     = new categoryHistogram("dilepFO","ge4j","ge2b","flips");

                fakeEst_from1FOCR_2j_0b_flips        = new categoryHistogram("fakeEst_from1FOCR","2j","0b","flips");
                fakeEst_from1FOCR_2j_1b_flips        = new categoryHistogram("fakeEst_from1FOCR","2j","1b","flips");
                fakeEst_from1FOCR_2j_ge2b_flips      = new categoryHistogram("fakeEst_from1FOCR","2j","ge2b","flips");
                fakeEst_from1FOCR_3j_0b_flips        = new categoryHistogram("fakeEst_from1FOCR","3j","0b","flips");
                fakeEst_from1FOCR_3j_1b_flips        = new categoryHistogram("fakeEst_from1FOCR","3j","1b","flips");
                fakeEst_from1FOCR_3j_ge2b_flips      = new categoryHistogram("fakeEst_from1FOCR","3j","ge2b","flips");
                fakeEst_from1FOCR_ge4j_0b_flips      = new categoryHistogram("fakeEst_from1FOCR","ge4j","0b","flips");
                fakeEst_from1FOCR_ge4j_1b_flips      = new categoryHistogram("fakeEst_from1FOCR","ge4j","1b","flips");
                fakeEst_from1FOCR_ge4j_ge2b_flips    = new categoryHistogram("fakeEst_from1FOCR","ge4j","ge2b","flips");

                fakeEst_from2FOCR_2j_0b_flips         = new categoryHistogram("fakeEst_from2FOCR","2j","0b","flips");
                fakeEst_from2FOCR_2j_1b_flips         = new categoryHistogram("fakeEst_from2FOCR","2j","1b","flips");
                fakeEst_from2FOCR_2j_ge2b_flips       = new categoryHistogram("fakeEst_from2FOCR","2j","ge2b","flips");
                fakeEst_from2FOCR_3j_0b_flips         = new categoryHistogram("fakeEst_from2FOCR","3j","0b","flips");
                fakeEst_from2FOCR_3j_1b_flips         = new categoryHistogram("fakeEst_from2FOCR","3j","1b","flips");
                fakeEst_from2FOCR_3j_ge2b_flips       = new categoryHistogram("fakeEst_from2FOCR","3j","ge2b","flips");
                fakeEst_from2FOCR_ge4j_0b_flips       = new categoryHistogram("fakeEst_from2FOCR","ge4j","0b","flips");
                fakeEst_from2FOCR_ge4j_1b_flips       = new categoryHistogram("fakeEst_from2FOCR","ge4j","1b","flips");
                fakeEst_from2FOCR_ge4j_ge2b_flips     = new categoryHistogram("fakeEst_from2FOCR","ge4j","ge2b","flips");



                //***********************************************************
                //***********************************************************
                //***********************************************************
                //SR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                trilep_2j_0b_other      = new categoryHistogram("trilep","2j","0b","other");
                trilep_2j_1b_other      = new categoryHistogram("trilep","2j","1b","other");
                trilep_2j_ge2b_other    = new categoryHistogram("trilep","2j","ge2b","other");
                trilep_3j_0b_other      = new categoryHistogram("trilep","3j","0b","other");
                trilep_3j_1b_other      = new categoryHistogram("trilep","3j","1b","other");
                trilep_3j_ge2b_other    = new categoryHistogram("trilep","3j","ge2b","other");
                trilep_ge4j_0b_other    = new categoryHistogram("trilep","ge4j","0b","other");
                trilep_ge4j_1b_other    = new categoryHistogram("trilep","ge4j","1b","other");
                trilep_ge4j_ge2b_other  = new categoryHistogram("trilep","ge4j","ge2b","other");

                SS_SF_dilep_2j_0b_other     = new categoryHistogram("SS_SF_dilep","2j","0b","other");
                SS_SF_dilep_2j_1b_other     = new categoryHistogram("SS_SF_dilep","2j","1b","other");
                SS_SF_dilep_2j_ge2b_other   = new categoryHistogram("SS_SF_dilep","2j","ge2b","other");
                SS_SF_dilep_3j_0b_other     = new categoryHistogram("SS_SF_dilep","3j","0b","other");
                SS_SF_dilep_3j_1b_other     = new categoryHistogram("SS_SF_dilep","3j","1b","other");
                SS_SF_dilep_3j_ge2b_other   = new categoryHistogram("SS_SF_dilep","3j","ge2b","other");
                SS_SF_dilep_ge4j_0b_other   = new categoryHistogram("SS_SF_dilep","ge4j","0b","other");
                SS_SF_dilep_ge4j_1b_other   = new categoryHistogram("SS_SF_dilep","ge4j","1b","other");
                SS_SF_dilep_ge4j_ge2b_other = new categoryHistogram("SS_SF_dilep","ge4j","ge2b","other");

                SS_OF_dilep_2j_0b_other     = new categoryHistogram("SS_OF_dilep","2j","0b","other");
                SS_OF_dilep_2j_1b_other     = new categoryHistogram("SS_OF_dilep","2j","1b","other");
                SS_OF_dilep_2j_ge2b_other   = new categoryHistogram("SS_OF_dilep","2j","ge2b","other");
                SS_OF_dilep_3j_0b_other     = new categoryHistogram("SS_OF_dilep","3j","0b","other");
                SS_OF_dilep_3j_1b_other     = new categoryHistogram("SS_OF_dilep","3j","1b","other");
                SS_OF_dilep_3j_ge2b_other   = new categoryHistogram("SS_OF_dilep","3j","ge2b","other");
                SS_OF_dilep_ge4j_0b_other   = new categoryHistogram("SS_OF_dilep","ge4j","0b","other");
                SS_OF_dilep_ge4j_1b_other   = new categoryHistogram("SS_OF_dilep","ge4j","1b","other");
                SS_OF_dilep_ge4j_ge2b_other = new categoryHistogram("SS_OF_dilep","ge4j","ge2b","other");

                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FLIP CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                OS_SF_dilep_2j_0b_other     = new categoryHistogram("OS_SF_dilep","2j","0b","other");
                OS_SF_dilep_2j_1b_other     = new categoryHistogram("OS_SF_dilep","2j","1b","other");
                OS_SF_dilep_2j_ge2b_other   = new categoryHistogram("OS_SF_dilep","2j","ge2b","other");
                OS_SF_dilep_3j_0b_other     = new categoryHistogram("OS_SF_dilep","3j","0b","other");
                OS_SF_dilep_3j_1b_other     = new categoryHistogram("OS_SF_dilep","3j","1b","other");
                OS_SF_dilep_3j_ge2b_other   = new categoryHistogram("OS_SF_dilep","3j","ge2b","other");
                OS_SF_dilep_ge4j_0b_other   = new categoryHistogram("OS_SF_dilep","ge4j","0b","other");
                OS_SF_dilep_ge4j_1b_other   = new categoryHistogram("OS_SF_dilep","ge4j","1b","other");
                OS_SF_dilep_ge4j_ge2b_other = new categoryHistogram("OS_SF_dilep","ge4j","ge2b","other");

                OS_OF_dilep_2j_0b_other     = new categoryHistogram("OS_OF_dilep","2j","0b","other");
                OS_OF_dilep_2j_1b_other     = new categoryHistogram("OS_OF_dilep","2j","1b","other");
                OS_OF_dilep_2j_ge2b_other   = new categoryHistogram("OS_OF_dilep","2j","ge2b","other");
                OS_OF_dilep_3j_0b_other     = new categoryHistogram("OS_OF_dilep","3j","0b","other");
                OS_OF_dilep_3j_1b_other     = new categoryHistogram("OS_OF_dilep","3j","1b","other");
                OS_OF_dilep_3j_ge2b_other   = new categoryHistogram("OS_OF_dilep","3j","ge2b","other");
                OS_OF_dilep_ge4j_0b_other   = new categoryHistogram("OS_OF_dilep","ge4j","0b","other");
                OS_OF_dilep_ge4j_1b_other   = new categoryHistogram("OS_OF_dilep","ge4j","1b","other");
                OS_OF_dilep_ge4j_ge2b_other = new categoryHistogram("OS_OF_dilep","ge4j","ge2b","other");

                SS_SF_flipEst_2j_0b_other     = new categoryHistogram("SS_SF_flipEst","2j","0b","other");
                SS_SF_flipEst_2j_1b_other     = new categoryHistogram("SS_SF_flipEst","2j","1b","other");
                SS_SF_flipEst_2j_ge2b_other   = new categoryHistogram("SS_SF_flipEst","2j","ge2b","other");
                SS_SF_flipEst_3j_0b_other     = new categoryHistogram("SS_SF_flipEst","3j","0b","other");
                SS_SF_flipEst_3j_1b_other     = new categoryHistogram("SS_SF_flipEst","3j","1b","other");
                SS_SF_flipEst_3j_ge2b_other   = new categoryHistogram("SS_SF_flipEst","3j","ge2b","other");
                SS_SF_flipEst_ge4j_0b_other   = new categoryHistogram("SS_SF_flipEst","ge4j","0b","other");
                SS_SF_flipEst_ge4j_1b_other   = new categoryHistogram("SS_SF_flipEst","ge4j","1b","other");
                SS_SF_flipEst_ge4j_ge2b_other = new categoryHistogram("SS_SF_flipEst","ge4j","ge2b","other");

                SS_OF_flipEst_2j_0b_other     = new categoryHistogram("SS_OF_flipEst","2j","0b","other");
                SS_OF_flipEst_2j_1b_other     = new categoryHistogram("SS_OF_flipEst","2j","1b","other");
                SS_OF_flipEst_2j_ge2b_other   = new categoryHistogram("SS_OF_flipEst","2j","ge2b","other");
                SS_OF_flipEst_3j_0b_other     = new categoryHistogram("SS_OF_flipEst","3j","0b","other");
                SS_OF_flipEst_3j_1b_other     = new categoryHistogram("SS_OF_flipEst","3j","1b","other");
                SS_OF_flipEst_3j_ge2b_other   = new categoryHistogram("SS_OF_flipEst","3j","ge2b","other");
                SS_OF_flipEst_ge4j_0b_other   = new categoryHistogram("SS_OF_flipEst","ge4j","0b","other");
                SS_OF_flipEst_ge4j_1b_other   = new categoryHistogram("SS_OF_flipEst","ge4j","1b","other");
                SS_OF_flipEst_ge4j_ge2b_other = new categoryHistogram("SS_OF_flipEst","ge4j","ge2b","other");


                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FAKE CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                onelepFO_2j_0b_other        = new categoryHistogram("onelepFO","2j","0b","other");
                onelepFO_2j_1b_other        = new categoryHistogram("onelepFO","2j","1b","other");
                onelepFO_2j_ge2b_other      = new categoryHistogram("onelepFO","2j","ge2b","other");
                onelepFO_3j_0b_other        = new categoryHistogram("onelepFO","3j","0b","other");
                onelepFO_3j_1b_other        = new categoryHistogram("onelepFO","3j","1b","other");
                onelepFO_3j_ge2b_other      = new categoryHistogram("onelepFO","3j","ge2b","other");
                onelepFO_ge4j_0b_other      = new categoryHistogram("onelepFO","ge4j","0b","other");
                onelepFO_ge4j_1b_other      = new categoryHistogram("onelepFO","ge4j","1b","other");
                onelepFO_ge4j_ge2b_other    = new categoryHistogram("onelepFO","ge4j","ge2b","other");

                dilepFO_2j_0b_other         = new categoryHistogram("dilepFO","2j","0b","other");
                dilepFO_2j_1b_other         = new categoryHistogram("dilepFO","2j","1b","other");
                dilepFO_2j_ge2b_other       = new categoryHistogram("dilepFO","2j","ge2b","other");
                dilepFO_3j_0b_other         = new categoryHistogram("dilepFO","3j","0b","other");
                dilepFO_3j_1b_other         = new categoryHistogram("dilepFO","3j","1b","other");
                dilepFO_3j_ge2b_other       = new categoryHistogram("dilepFO","3j","ge2b","other");
                dilepFO_ge4j_0b_other       = new categoryHistogram("dilepFO","ge4j","0b","other");
                dilepFO_ge4j_1b_other       = new categoryHistogram("dilepFO","ge4j","1b","other");
                dilepFO_ge4j_ge2b_other     = new categoryHistogram("dilepFO","ge4j","ge2b","other");

                fakeEst_from1FOCR_2j_0b_other        = new categoryHistogram("fakeEst_from1FOCR","2j","0b","other");
                fakeEst_from1FOCR_2j_1b_other        = new categoryHistogram("fakeEst_from1FOCR","2j","1b","other");
                fakeEst_from1FOCR_2j_ge2b_other      = new categoryHistogram("fakeEst_from1FOCR","2j","ge2b","other");
                fakeEst_from1FOCR_3j_0b_other        = new categoryHistogram("fakeEst_from1FOCR","3j","0b","other");
                fakeEst_from1FOCR_3j_1b_other        = new categoryHistogram("fakeEst_from1FOCR","3j","1b","other");
                fakeEst_from1FOCR_3j_ge2b_other      = new categoryHistogram("fakeEst_from1FOCR","3j","ge2b","other");
                fakeEst_from1FOCR_ge4j_0b_other      = new categoryHistogram("fakeEst_from1FOCR","ge4j","0b","other");
                fakeEst_from1FOCR_ge4j_1b_other      = new categoryHistogram("fakeEst_from1FOCR","ge4j","1b","other");
                fakeEst_from1FOCR_ge4j_ge2b_other    = new categoryHistogram("fakeEst_from1FOCR","ge4j","ge2b","other");

                fakeEst_from2FOCR_2j_0b_other         = new categoryHistogram("fakeEst_from2FOCR","2j","0b","other");
                fakeEst_from2FOCR_2j_1b_other         = new categoryHistogram("fakeEst_from2FOCR","2j","1b","other");
                fakeEst_from2FOCR_2j_ge2b_other       = new categoryHistogram("fakeEst_from2FOCR","2j","ge2b","other");
                fakeEst_from2FOCR_3j_0b_other         = new categoryHistogram("fakeEst_from2FOCR","3j","0b","other");
                fakeEst_from2FOCR_3j_1b_other         = new categoryHistogram("fakeEst_from2FOCR","3j","1b","other");
                fakeEst_from2FOCR_3j_ge2b_other       = new categoryHistogram("fakeEst_from2FOCR","3j","ge2b","other");
                fakeEst_from2FOCR_ge4j_0b_other       = new categoryHistogram("fakeEst_from2FOCR","ge4j","0b","other");
                fakeEst_from2FOCR_ge4j_1b_other       = new categoryHistogram("fakeEst_from2FOCR","ge4j","1b","other");
                fakeEst_from2FOCR_ge4j_ge2b_other     = new categoryHistogram("fakeEst_from2FOCR","ge4j","ge2b","other");

            }else{
                //***********************************************************
                //***********************************************************
                //***********************************************************
                //SR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                trilep_2j_0b      = new categoryHistogram("trilep","2j","0b",category);
                trilep_2j_1b      = new categoryHistogram("trilep","2j","1b",category);
                trilep_2j_ge2b    = new categoryHistogram("trilep","2j","ge2b",category);
                trilep_3j_0b      = new categoryHistogram("trilep","3j","0b",category);
                trilep_3j_1b      = new categoryHistogram("trilep","3j","1b",category);
                trilep_3j_ge2b    = new categoryHistogram("trilep","3j","ge2b",category);
                trilep_ge4j_0b    = new categoryHistogram("trilep","ge4j","0b",category);
                trilep_ge4j_1b    = new categoryHistogram("trilep","ge4j","1b",category);
                trilep_ge4j_ge2b  = new categoryHistogram("trilep","ge4j","ge2b",category);

                SS_SF_dilep_2j_0b     = new categoryHistogram("SS_SF_dilep","2j","0b",category);
                SS_SF_dilep_2j_1b     = new categoryHistogram("SS_SF_dilep","2j","1b",category);
                SS_SF_dilep_2j_ge2b   = new categoryHistogram("SS_SF_dilep","2j","ge2b",category);
                SS_SF_dilep_3j_0b     = new categoryHistogram("SS_SF_dilep","3j","0b",category);
                SS_SF_dilep_3j_1b     = new categoryHistogram("SS_SF_dilep","3j","1b",category);
                SS_SF_dilep_3j_ge2b   = new categoryHistogram("SS_SF_dilep","3j","ge2b",category);
                SS_SF_dilep_ge4j_0b   = new categoryHistogram("SS_SF_dilep","ge4j","0b",category);
                SS_SF_dilep_ge4j_1b   = new categoryHistogram("SS_SF_dilep","ge4j","1b",category);
                SS_SF_dilep_ge4j_ge2b = new categoryHistogram("SS_SF_dilep","ge4j","ge2b",category);

                SS_OF_dilep_2j_0b     = new categoryHistogram("SS_OF_dilep","2j","0b",category);
                SS_OF_dilep_2j_1b     = new categoryHistogram("SS_OF_dilep","2j","1b",category);
                SS_OF_dilep_2j_ge2b   = new categoryHistogram("SS_OF_dilep","2j","ge2b",category);
                SS_OF_dilep_3j_0b     = new categoryHistogram("SS_OF_dilep","3j","0b",category);
                SS_OF_dilep_3j_1b     = new categoryHistogram("SS_OF_dilep","3j","1b",category);
                SS_OF_dilep_3j_ge2b   = new categoryHistogram("SS_OF_dilep","3j","ge2b",category);
                SS_OF_dilep_ge4j_0b   = new categoryHistogram("SS_OF_dilep","ge4j","0b",category);
                SS_OF_dilep_ge4j_1b   = new categoryHistogram("SS_OF_dilep","ge4j","1b",category);
                SS_OF_dilep_ge4j_ge2b = new categoryHistogram("SS_OF_dilep","ge4j","ge2b",category);

                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FLIP CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                OS_SF_dilep_2j_0b     = new categoryHistogram("OS_SF_dilep","2j","0b",category);
                OS_SF_dilep_2j_1b     = new categoryHistogram("OS_SF_dilep","2j","1b",category);
                OS_SF_dilep_2j_ge2b   = new categoryHistogram("OS_SF_dilep","2j","ge2b",category);
                OS_SF_dilep_3j_0b     = new categoryHistogram("OS_SF_dilep","3j","0b",category);
                OS_SF_dilep_3j_1b     = new categoryHistogram("OS_SF_dilep","3j","1b",category);
                OS_SF_dilep_3j_ge2b   = new categoryHistogram("OS_SF_dilep","3j","ge2b",category);
                OS_SF_dilep_ge4j_0b   = new categoryHistogram("OS_SF_dilep","ge4j","0b",category);
                OS_SF_dilep_ge4j_1b   = new categoryHistogram("OS_SF_dilep","ge4j","1b",category);
                OS_SF_dilep_ge4j_ge2b = new categoryHistogram("OS_SF_dilep","ge4j","ge2b",category);

                OS_OF_dilep_2j_0b     = new categoryHistogram("OS_OF_dilep","2j","0b",category);
                OS_OF_dilep_2j_1b     = new categoryHistogram("OS_OF_dilep","2j","1b",category);
                OS_OF_dilep_2j_ge2b   = new categoryHistogram("OS_OF_dilep","2j","ge2b",category);
                OS_OF_dilep_3j_0b     = new categoryHistogram("OS_OF_dilep","3j","0b",category);
                OS_OF_dilep_3j_1b     = new categoryHistogram("OS_OF_dilep","3j","1b",category);
                OS_OF_dilep_3j_ge2b   = new categoryHistogram("OS_OF_dilep","3j","ge2b",category);
                OS_OF_dilep_ge4j_0b   = new categoryHistogram("OS_OF_dilep","ge4j","0b",category);
                OS_OF_dilep_ge4j_1b   = new categoryHistogram("OS_OF_dilep","ge4j","1b",category);
                OS_OF_dilep_ge4j_ge2b = new categoryHistogram("OS_OF_dilep","ge4j","ge2b",category);

                SS_SF_flipEst_2j_0b     = new categoryHistogram("SS_SF_flipEst","2j","0b",category);
                SS_SF_flipEst_2j_1b     = new categoryHistogram("SS_SF_flipEst","2j","1b",category);
                SS_SF_flipEst_2j_ge2b   = new categoryHistogram("SS_SF_flipEst","2j","ge2b",category);
                SS_SF_flipEst_3j_0b     = new categoryHistogram("SS_SF_flipEst","3j","0b",category);
                SS_SF_flipEst_3j_1b     = new categoryHistogram("SS_SF_flipEst","3j","1b",category);
                SS_SF_flipEst_3j_ge2b   = new categoryHistogram("SS_SF_flipEst","3j","ge2b",category);
                SS_SF_flipEst_ge4j_0b   = new categoryHistogram("SS_SF_flipEst","ge4j","0b",category);
                SS_SF_flipEst_ge4j_1b   = new categoryHistogram("SS_SF_flipEst","ge4j","1b",category);
                SS_SF_flipEst_ge4j_ge2b = new categoryHistogram("SS_SF_flipEst","ge4j","ge2b",category);

                SS_OF_flipEst_2j_0b     = new categoryHistogram("SS_OF_flipEst","2j","0b",category);
                SS_OF_flipEst_2j_1b     = new categoryHistogram("SS_OF_flipEst","2j","1b",category);
                SS_OF_flipEst_2j_ge2b   = new categoryHistogram("SS_OF_flipEst","2j","ge2b",category);
                SS_OF_flipEst_3j_0b     = new categoryHistogram("SS_OF_flipEst","3j","0b",category);
                SS_OF_flipEst_3j_1b     = new categoryHistogram("SS_OF_flipEst","3j","1b",category);
                SS_OF_flipEst_3j_ge2b   = new categoryHistogram("SS_OF_flipEst","3j","ge2b",category);
                SS_OF_flipEst_ge4j_0b   = new categoryHistogram("SS_OF_flipEst","ge4j","0b",category);
                SS_OF_flipEst_ge4j_1b   = new categoryHistogram("SS_OF_flipEst","ge4j","1b",category);
                SS_OF_flipEst_ge4j_ge2b = new categoryHistogram("SS_OF_flipEst","ge4j","ge2b",category);


                //***********************************************************
                //***********************************************************
                //***********************************************************
                //FAKE CR
                //***********************************************************
                //***********************************************************
                //***********************************************************
                onelepFO_2j_0b        = new categoryHistogram("onelepFO","2j","0b",category);
                onelepFO_2j_1b        = new categoryHistogram("onelepFO","2j","1b",category);
                onelepFO_2j_ge2b      = new categoryHistogram("onelepFO","2j","ge2b",category);
                onelepFO_3j_0b        = new categoryHistogram("onelepFO","3j","0b",category);
                onelepFO_3j_1b        = new categoryHistogram("onelepFO","3j","1b",category);
                onelepFO_3j_ge2b      = new categoryHistogram("onelepFO","3j","ge2b",category);
                onelepFO_ge4j_0b      = new categoryHistogram("onelepFO","ge4j","0b",category);
                onelepFO_ge4j_1b      = new categoryHistogram("onelepFO","ge4j","1b",category);
                onelepFO_ge4j_ge2b    = new categoryHistogram("onelepFO","ge4j","ge2b",category);

                dilepFO_2j_0b         = new categoryHistogram("dilepFO","2j","0b",category);
                dilepFO_2j_1b         = new categoryHistogram("dilepFO","2j","1b",category);
                dilepFO_2j_ge2b       = new categoryHistogram("dilepFO","2j","ge2b",category);
                dilepFO_3j_0b         = new categoryHistogram("dilepFO","3j","0b",category);
                dilepFO_3j_1b         = new categoryHistogram("dilepFO","3j","1b",category);
                dilepFO_3j_ge2b       = new categoryHistogram("dilepFO","3j","ge2b",category);
                dilepFO_ge4j_0b       = new categoryHistogram("dilepFO","ge4j","0b",category);
                dilepFO_ge4j_1b       = new categoryHistogram("dilepFO","ge4j","1b",category);
                dilepFO_ge4j_ge2b     = new categoryHistogram("dilepFO","ge4j","ge2b",category);

                fakeEst_from1FOCR_2j_0b        = new categoryHistogram("fakeEst_from1FOCR","2j","0b",category);
                fakeEst_from1FOCR_2j_1b        = new categoryHistogram("fakeEst_from1FOCR","2j","1b",category);
                fakeEst_from1FOCR_2j_ge2b      = new categoryHistogram("fakeEst_from1FOCR","2j","ge2b",category);
                fakeEst_from1FOCR_3j_0b        = new categoryHistogram("fakeEst_from1FOCR","3j","0b",category);
                fakeEst_from1FOCR_3j_1b        = new categoryHistogram("fakeEst_from1FOCR","3j","1b",category);
                fakeEst_from1FOCR_3j_ge2b      = new categoryHistogram("fakeEst_from1FOCR","3j","ge2b",category);
                fakeEst_from1FOCR_ge4j_0b      = new categoryHistogram("fakeEst_from1FOCR","ge4j","0b",category);
                fakeEst_from1FOCR_ge4j_1b      = new categoryHistogram("fakeEst_from1FOCR","ge4j","1b",category);
                fakeEst_from1FOCR_ge4j_ge2b    = new categoryHistogram("fakeEst_from1FOCR","ge4j","ge2b",category);

                fakeEst_from2FOCR_2j_0b         = new categoryHistogram("fakeEst_from2FOCR","2j","0b",category);
                fakeEst_from2FOCR_2j_1b         = new categoryHistogram("fakeEst_from2FOCR","2j","1b",category);
                fakeEst_from2FOCR_2j_ge2b       = new categoryHistogram("fakeEst_from2FOCR","2j","ge2b",category);
                fakeEst_from2FOCR_3j_0b         = new categoryHistogram("fakeEst_from2FOCR","3j","0b",category);
                fakeEst_from2FOCR_3j_1b         = new categoryHistogram("fakeEst_from2FOCR","3j","1b",category);
                fakeEst_from2FOCR_3j_ge2b       = new categoryHistogram("fakeEst_from2FOCR","3j","ge2b",category);
                fakeEst_from2FOCR_ge4j_0b       = new categoryHistogram("fakeEst_from2FOCR","ge4j","0b",category);
                fakeEst_from2FOCR_ge4j_1b       = new categoryHistogram("fakeEst_from2FOCR","ge4j","1b",category);
                fakeEst_from2FOCR_ge4j_ge2b     = new categoryHistogram("fakeEst_from2FOCR","ge4j","ge2b",category);

            }
        }

        //methods to fill and save histograms
        void fill(vector<float> variablesForFilling, float weight, float crWeight, int nJets, int nBjets, int nGoodLep, int nFakeableLep, vector<int> muCharge_tight, vector<int> elCharge_tight, bool isSSFO, bool isFake, bool isFlip, bool isSMSS, bool isSignal){
            
            if(isFake == 1){
                if (nJets==2){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==2
                if (nJets==3){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==3
                if (nJets>=4){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_0b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_0b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_1b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_1b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_ge2b_fakes->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njets>=4
            }else if(isFlip == 1){
                if (nJets==2){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==2
                if (nJets==3){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==3
                if (nJets>=4){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_0b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_0b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_1b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_1b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_ge2b_flips->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_ge2b_flips->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njets>=4
            }else if(isSMSS == 1){
                if (nJets==2){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_0b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_0b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_0b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_0b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_1b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_1b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_1b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_1b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==2
                if (nJets==3){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_0b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_0b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_0b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_0b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_1b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_1b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_1b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_1b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==3
                if (nJets>=4){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_0b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_0b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_1b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_1b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_ge2b_other->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_ge2b_other->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njets>=4
            }else{
                if (nJets==2){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_2j_0b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_0b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_0b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_0b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_0b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_0b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_0b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_2j_1b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_1b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_1b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_1b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_1b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_1b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_1b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_2j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_2j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_2j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_2j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_2j_ge2b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_2j_ge2b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_2j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_2j_ge2b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_2j_ge2b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==2
                if (nJets==3){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_3j_0b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_0b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_0b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_0b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_0b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_0b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_0b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_3j_1b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_1b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_1b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_1b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_1b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_1b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_1b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_3j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_3j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_3j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_3j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_3j_ge2b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_3j_ge2b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_3j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_3j_ge2b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_3j_ge2b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njet==3
                if (nJets>=4){
                    if (nBjets==0){
                        if (nGoodLep>=3){
                            trilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_0b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_0b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_0b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_0b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_0b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_0b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_0b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_0b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets==1){
                        if (nGoodLep>=3){
                            trilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_1b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_1b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_1b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_1b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_1b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_1b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_1b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_1b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }else if (nBjets>=2){
                        if (nGoodLep>=3){
                            trilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                        }
                        if (nGoodLep == 2){
                            if (muCharge_tight.size() == 2){
                                if (muCharge_tight[0]*muCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (elCharge_tight.size() == 2) {
                                if (elCharge_tight[0]*elCharge_tight[1]>0){
                                    SS_SF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{ 
                                    if (crWeight != 0){
                                        SS_SF_flipEst_ge4j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_SF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_SF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }else if (muCharge_tight.size() == 1) {
                                if (muCharge_tight[0]*elCharge_tight[0]>0){
                                    SS_OF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                }else{
                                    if (crWeight != 0){
                                        SS_OF_flipEst_ge4j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                        OS_OF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }else{
                                        OS_OF_dilep_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                                    }
                                }
                            }
                        }
                        if (nGoodLep==1 && nFakeableLep==1 && isSSFO){
                            if (crWeight != 0){
                                fakeEst_from1FOCR_ge4j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                onelepFO_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                            }else{
                                onelepFO_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                        if (nFakeableLep==2 && isSSFO){
                            if(crWeight != 0){
                                fakeEst_from2FOCR_ge4j_ge2b->fillHistogram(variablesForFilling, crWeight);
                                dilepFO_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                            }else{
                                dilepFO_ge4j_ge2b->fillHistogram(variablesForFilling, weight);
                            }
                        }
                    }
                }//njets>=4
            }
        }//function close

        void write(string sampleName, TFile* &outfile){
            if (sampleName == "background"){
                trilep_2j_0b_fakes->writeHistogram(outfile);
                trilep_2j_1b_fakes->writeHistogram(outfile);
                trilep_2j_ge2b_fakes->writeHistogram(outfile);
                trilep_3j_0b_fakes->writeHistogram(outfile);
                trilep_3j_1b_fakes->writeHistogram(outfile);
                trilep_3j_ge2b_fakes->writeHistogram(outfile);
                trilep_ge4j_0b_fakes->writeHistogram(outfile);
                trilep_ge4j_1b_fakes->writeHistogram(outfile);
                trilep_ge4j_ge2b_fakes->writeHistogram(outfile);

                SS_SF_dilep_2j_0b_fakes->writeHistogram(outfile);
                SS_SF_dilep_2j_1b_fakes->writeHistogram(outfile);
                SS_SF_dilep_2j_ge2b_fakes->writeHistogram(outfile);
                SS_SF_dilep_3j_0b_fakes->writeHistogram(outfile);
                SS_SF_dilep_3j_1b_fakes->writeHistogram(outfile);
                SS_SF_dilep_3j_ge2b_fakes->writeHistogram(outfile);
                SS_SF_dilep_ge4j_0b_fakes->writeHistogram(outfile);
                SS_SF_dilep_ge4j_1b_fakes->writeHistogram(outfile);
                SS_SF_dilep_ge4j_ge2b_fakes->writeHistogram(outfile);

                SS_OF_dilep_2j_0b_fakes->writeHistogram(outfile);
                SS_OF_dilep_2j_1b_fakes->writeHistogram(outfile);
                SS_OF_dilep_2j_ge2b_fakes->writeHistogram(outfile);
                SS_OF_dilep_3j_0b_fakes->writeHistogram(outfile);
                SS_OF_dilep_3j_1b_fakes->writeHistogram(outfile);
                SS_OF_dilep_3j_ge2b_fakes->writeHistogram(outfile);
                SS_OF_dilep_ge4j_0b_fakes->writeHistogram(outfile);
                SS_OF_dilep_ge4j_1b_fakes->writeHistogram(outfile);
                SS_OF_dilep_ge4j_ge2b_fakes->writeHistogram(outfile);

                OS_SF_dilep_2j_0b_fakes->writeHistogram(outfile);
                OS_SF_dilep_2j_1b_fakes->writeHistogram(outfile);
                OS_SF_dilep_2j_ge2b_fakes->writeHistogram(outfile);
                OS_SF_dilep_3j_0b_fakes->writeHistogram(outfile);
                OS_SF_dilep_3j_1b_fakes->writeHistogram(outfile);
                OS_SF_dilep_3j_ge2b_fakes->writeHistogram(outfile);
                OS_SF_dilep_ge4j_0b_fakes->writeHistogram(outfile);
                OS_SF_dilep_ge4j_1b_fakes->writeHistogram(outfile);
                OS_SF_dilep_ge4j_ge2b_fakes->writeHistogram(outfile);

                OS_OF_dilep_2j_0b_fakes->writeHistogram(outfile);
                OS_OF_dilep_2j_1b_fakes->writeHistogram(outfile);
                OS_OF_dilep_2j_ge2b_fakes->writeHistogram(outfile);
                OS_OF_dilep_3j_0b_fakes->writeHistogram(outfile);
                OS_OF_dilep_3j_1b_fakes->writeHistogram(outfile);
                OS_OF_dilep_3j_ge2b_fakes->writeHistogram(outfile);
                OS_OF_dilep_ge4j_0b_fakes->writeHistogram(outfile);
                OS_OF_dilep_ge4j_1b_fakes->writeHistogram(outfile);
                OS_OF_dilep_ge4j_ge2b_fakes->writeHistogram(outfile);

                SS_SF_flipEst_2j_0b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_2j_1b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_2j_ge2b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_3j_0b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_3j_1b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_3j_ge2b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_0b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_1b_fakes->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_ge2b_fakes->writeHistogram(outfile);

                SS_OF_flipEst_2j_0b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_2j_1b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_2j_ge2b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_3j_0b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_3j_1b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_3j_ge2b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_0b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_1b_fakes->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_ge2b_fakes->writeHistogram(outfile);

                onelepFO_2j_0b_fakes->writeHistogram(outfile);
                onelepFO_2j_1b_fakes->writeHistogram(outfile);
                onelepFO_2j_ge2b_fakes->writeHistogram(outfile);
                onelepFO_3j_0b_fakes->writeHistogram(outfile);
                onelepFO_3j_1b_fakes->writeHistogram(outfile);
                onelepFO_3j_ge2b_fakes->writeHistogram(outfile);
                onelepFO_ge4j_0b_fakes->writeHistogram(outfile);
                onelepFO_ge4j_1b_fakes->writeHistogram(outfile);
                onelepFO_ge4j_ge2b_fakes->writeHistogram(outfile);

                dilepFO_2j_0b_fakes->writeHistogram(outfile);
                dilepFO_2j_1b_fakes->writeHistogram(outfile);
                dilepFO_2j_ge2b_fakes->writeHistogram(outfile);
                dilepFO_3j_0b_fakes->writeHistogram(outfile);
                dilepFO_3j_1b_fakes->writeHistogram(outfile);
                dilepFO_3j_ge2b_fakes->writeHistogram(outfile);
                dilepFO_ge4j_0b_fakes->writeHistogram(outfile);
                dilepFO_ge4j_1b_fakes->writeHistogram(outfile);
                dilepFO_ge4j_ge2b_fakes->writeHistogram(outfile);

                fakeEst_from1FOCR_2j_0b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_1b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_ge2b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_0b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_1b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_ge2b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_0b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_1b_fakes->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_ge2b_fakes->writeHistogram(outfile);

                fakeEst_from2FOCR_2j_0b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_1b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_ge2b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_0b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_1b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_ge2b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_0b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_1b_fakes->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_ge2b_fakes->writeHistogram(outfile);



                trilep_2j_0b_flips->writeHistogram(outfile);
                trilep_2j_1b_flips->writeHistogram(outfile);
                trilep_2j_ge2b_flips->writeHistogram(outfile);
                trilep_3j_0b_flips->writeHistogram(outfile);
                trilep_3j_1b_flips->writeHistogram(outfile);
                trilep_3j_ge2b_flips->writeHistogram(outfile);
                trilep_ge4j_0b_flips->writeHistogram(outfile);
                trilep_ge4j_1b_flips->writeHistogram(outfile);
                trilep_ge4j_ge2b_flips->writeHistogram(outfile);

                SS_SF_dilep_2j_0b_flips->writeHistogram(outfile);
                SS_SF_dilep_2j_1b_flips->writeHistogram(outfile);
                SS_SF_dilep_2j_ge2b_flips->writeHistogram(outfile);
                SS_SF_dilep_3j_0b_flips->writeHistogram(outfile);
                SS_SF_dilep_3j_1b_flips->writeHistogram(outfile);
                SS_SF_dilep_3j_ge2b_flips->writeHistogram(outfile);
                SS_SF_dilep_ge4j_0b_flips->writeHistogram(outfile);
                SS_SF_dilep_ge4j_1b_flips->writeHistogram(outfile);
                SS_SF_dilep_ge4j_ge2b_flips->writeHistogram(outfile);

                SS_OF_dilep_2j_0b_flips->writeHistogram(outfile);
                SS_OF_dilep_2j_1b_flips->writeHistogram(outfile);
                SS_OF_dilep_2j_ge2b_flips->writeHistogram(outfile);
                SS_OF_dilep_3j_0b_flips->writeHistogram(outfile);
                SS_OF_dilep_3j_1b_flips->writeHistogram(outfile);
                SS_OF_dilep_3j_ge2b_flips->writeHistogram(outfile);
                SS_OF_dilep_ge4j_0b_flips->writeHistogram(outfile);
                SS_OF_dilep_ge4j_1b_flips->writeHistogram(outfile);
                SS_OF_dilep_ge4j_ge2b_flips->writeHistogram(outfile);

                OS_SF_dilep_2j_0b_flips->writeHistogram(outfile);
                OS_SF_dilep_2j_1b_flips->writeHistogram(outfile);
                OS_SF_dilep_2j_ge2b_flips->writeHistogram(outfile);
                OS_SF_dilep_3j_0b_flips->writeHistogram(outfile);
                OS_SF_dilep_3j_1b_flips->writeHistogram(outfile);
                OS_SF_dilep_3j_ge2b_flips->writeHistogram(outfile);
                OS_SF_dilep_ge4j_0b_flips->writeHistogram(outfile);
                OS_SF_dilep_ge4j_1b_flips->writeHistogram(outfile);
                OS_SF_dilep_ge4j_ge2b_flips->writeHistogram(outfile);

                OS_OF_dilep_2j_0b_flips->writeHistogram(outfile);
                OS_OF_dilep_2j_1b_flips->writeHistogram(outfile);
                OS_OF_dilep_2j_ge2b_flips->writeHistogram(outfile);
                OS_OF_dilep_3j_0b_flips->writeHistogram(outfile);
                OS_OF_dilep_3j_1b_flips->writeHistogram(outfile);
                OS_OF_dilep_3j_ge2b_flips->writeHistogram(outfile);
                OS_OF_dilep_ge4j_0b_flips->writeHistogram(outfile);
                OS_OF_dilep_ge4j_1b_flips->writeHistogram(outfile);
                OS_OF_dilep_ge4j_ge2b_flips->writeHistogram(outfile);

                SS_SF_flipEst_2j_0b_flips->writeHistogram(outfile);
                SS_SF_flipEst_2j_1b_flips->writeHistogram(outfile);
                SS_SF_flipEst_2j_ge2b_flips->writeHistogram(outfile);
                SS_SF_flipEst_3j_0b_flips->writeHistogram(outfile);
                SS_SF_flipEst_3j_1b_flips->writeHistogram(outfile);
                SS_SF_flipEst_3j_ge2b_flips->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_0b_flips->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_1b_flips->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_ge2b_flips->writeHistogram(outfile);

                SS_OF_flipEst_2j_0b_flips->writeHistogram(outfile);
                SS_OF_flipEst_2j_1b_flips->writeHistogram(outfile);
                SS_OF_flipEst_2j_ge2b_flips->writeHistogram(outfile);
                SS_OF_flipEst_3j_0b_flips->writeHistogram(outfile);
                SS_OF_flipEst_3j_1b_flips->writeHistogram(outfile);
                SS_OF_flipEst_3j_ge2b_flips->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_0b_flips->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_1b_flips->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_ge2b_flips->writeHistogram(outfile);

                onelepFO_2j_0b_flips->writeHistogram(outfile);
                onelepFO_2j_1b_flips->writeHistogram(outfile);
                onelepFO_2j_ge2b_flips->writeHistogram(outfile);
                onelepFO_3j_0b_flips->writeHistogram(outfile);
                onelepFO_3j_1b_flips->writeHistogram(outfile);
                onelepFO_3j_ge2b_flips->writeHistogram(outfile);
                onelepFO_ge4j_0b_flips->writeHistogram(outfile);
                onelepFO_ge4j_1b_flips->writeHistogram(outfile);
                onelepFO_ge4j_ge2b_flips->writeHistogram(outfile);

                dilepFO_2j_0b_flips->writeHistogram(outfile);
                dilepFO_2j_1b_flips->writeHistogram(outfile);
                dilepFO_2j_ge2b_flips->writeHistogram(outfile);
                dilepFO_3j_0b_flips->writeHistogram(outfile);
                dilepFO_3j_1b_flips->writeHistogram(outfile);
                dilepFO_3j_ge2b_flips->writeHistogram(outfile);
                dilepFO_ge4j_0b_flips->writeHistogram(outfile);
                dilepFO_ge4j_1b_flips->writeHistogram(outfile);
                dilepFO_ge4j_ge2b_flips->writeHistogram(outfile);

                fakeEst_from1FOCR_2j_0b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_1b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_ge2b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_0b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_1b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_ge2b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_0b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_1b_flips->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_ge2b_flips->writeHistogram(outfile);

                fakeEst_from2FOCR_2j_0b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_1b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_ge2b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_0b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_1b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_ge2b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_0b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_1b_flips->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_ge2b_flips->writeHistogram(outfile);



                trilep_2j_0b_other->writeHistogram(outfile);
                trilep_2j_1b_other->writeHistogram(outfile);
                trilep_2j_ge2b_other->writeHistogram(outfile);
                trilep_3j_0b_other->writeHistogram(outfile);
                trilep_3j_1b_other->writeHistogram(outfile);
                trilep_3j_ge2b_other->writeHistogram(outfile);
                trilep_ge4j_0b_other->writeHistogram(outfile);
                trilep_ge4j_1b_other->writeHistogram(outfile);
                trilep_ge4j_ge2b_other->writeHistogram(outfile);

                SS_SF_dilep_2j_0b_other->writeHistogram(outfile);
                SS_SF_dilep_2j_1b_other->writeHistogram(outfile);
                SS_SF_dilep_2j_ge2b_other->writeHistogram(outfile);
                SS_SF_dilep_3j_0b_other->writeHistogram(outfile);
                SS_SF_dilep_3j_1b_other->writeHistogram(outfile);
                SS_SF_dilep_3j_ge2b_other->writeHistogram(outfile);
                SS_SF_dilep_ge4j_0b_other->writeHistogram(outfile);
                SS_SF_dilep_ge4j_1b_other->writeHistogram(outfile);
                SS_SF_dilep_ge4j_ge2b_other->writeHistogram(outfile);

                SS_OF_dilep_2j_0b_other->writeHistogram(outfile);
                SS_OF_dilep_2j_1b_other->writeHistogram(outfile);
                SS_OF_dilep_2j_ge2b_other->writeHistogram(outfile);
                SS_OF_dilep_3j_0b_other->writeHistogram(outfile);
                SS_OF_dilep_3j_1b_other->writeHistogram(outfile);
                SS_OF_dilep_3j_ge2b_other->writeHistogram(outfile);
                SS_OF_dilep_ge4j_0b_other->writeHistogram(outfile);
                SS_OF_dilep_ge4j_1b_other->writeHistogram(outfile);
                SS_OF_dilep_ge4j_ge2b_other->writeHistogram(outfile);

                OS_SF_dilep_2j_0b_other->writeHistogram(outfile);
                OS_SF_dilep_2j_1b_other->writeHistogram(outfile);
                OS_SF_dilep_2j_ge2b_other->writeHistogram(outfile);
                OS_SF_dilep_3j_0b_other->writeHistogram(outfile);
                OS_SF_dilep_3j_1b_other->writeHistogram(outfile);
                OS_SF_dilep_3j_ge2b_other->writeHistogram(outfile);
                OS_SF_dilep_ge4j_0b_other->writeHistogram(outfile);
                OS_SF_dilep_ge4j_1b_other->writeHistogram(outfile);
                OS_SF_dilep_ge4j_ge2b_other->writeHistogram(outfile);

                OS_OF_dilep_2j_0b_other->writeHistogram(outfile);
                OS_OF_dilep_2j_1b_other->writeHistogram(outfile);
                OS_OF_dilep_2j_ge2b_other->writeHistogram(outfile);
                OS_OF_dilep_3j_0b_other->writeHistogram(outfile);
                OS_OF_dilep_3j_1b_other->writeHistogram(outfile);
                OS_OF_dilep_3j_ge2b_other->writeHistogram(outfile);
                OS_OF_dilep_ge4j_0b_other->writeHistogram(outfile);
                OS_OF_dilep_ge4j_1b_other->writeHistogram(outfile);
                OS_OF_dilep_ge4j_ge2b_other->writeHistogram(outfile);

                SS_SF_flipEst_2j_0b_other->writeHistogram(outfile);
                SS_SF_flipEst_2j_1b_other->writeHistogram(outfile);
                SS_SF_flipEst_2j_ge2b_other->writeHistogram(outfile);
                SS_SF_flipEst_3j_0b_other->writeHistogram(outfile);
                SS_SF_flipEst_3j_1b_other->writeHistogram(outfile);
                SS_SF_flipEst_3j_ge2b_other->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_0b_other->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_1b_other->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_ge2b_other->writeHistogram(outfile);

                SS_OF_flipEst_2j_0b_other->writeHistogram(outfile);
                SS_OF_flipEst_2j_1b_other->writeHistogram(outfile);
                SS_OF_flipEst_2j_ge2b_other->writeHistogram(outfile);
                SS_OF_flipEst_3j_0b_other->writeHistogram(outfile);
                SS_OF_flipEst_3j_1b_other->writeHistogram(outfile);
                SS_OF_flipEst_3j_ge2b_other->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_0b_other->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_1b_other->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_ge2b_other->writeHistogram(outfile);

                onelepFO_2j_0b_other->writeHistogram(outfile);
                onelepFO_2j_1b_other->writeHistogram(outfile);
                onelepFO_2j_ge2b_other->writeHistogram(outfile);
                onelepFO_3j_0b_other->writeHistogram(outfile);
                onelepFO_3j_1b_other->writeHistogram(outfile);
                onelepFO_3j_ge2b_other->writeHistogram(outfile);
                onelepFO_ge4j_0b_other->writeHistogram(outfile);
                onelepFO_ge4j_1b_other->writeHistogram(outfile);
                onelepFO_ge4j_ge2b_other->writeHistogram(outfile);

                dilepFO_2j_0b_other->writeHistogram(outfile);
                dilepFO_2j_1b_other->writeHistogram(outfile);
                dilepFO_2j_ge2b_other->writeHistogram(outfile);
                dilepFO_3j_0b_other->writeHistogram(outfile);
                dilepFO_3j_1b_other->writeHistogram(outfile);
                dilepFO_3j_ge2b_other->writeHistogram(outfile);
                dilepFO_ge4j_0b_other->writeHistogram(outfile);
                dilepFO_ge4j_1b_other->writeHistogram(outfile);
                dilepFO_ge4j_ge2b_other->writeHistogram(outfile);

                fakeEst_from1FOCR_2j_0b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_1b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_ge2b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_0b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_1b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_ge2b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_0b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_1b_other->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_ge2b_other->writeHistogram(outfile);

                fakeEst_from2FOCR_2j_0b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_1b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_ge2b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_0b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_1b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_ge2b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_0b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_1b_other->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_ge2b_other->writeHistogram(outfile);

            }else{

                trilep_2j_0b->writeHistogram(outfile);
                trilep_2j_1b->writeHistogram(outfile);
                trilep_2j_ge2b->writeHistogram(outfile);
                trilep_3j_0b->writeHistogram(outfile);
                trilep_3j_1b->writeHistogram(outfile);
                trilep_3j_ge2b->writeHistogram(outfile);
                trilep_ge4j_0b->writeHistogram(outfile);
                trilep_ge4j_1b->writeHistogram(outfile);
                trilep_ge4j_ge2b->writeHistogram(outfile);

                SS_SF_dilep_2j_0b->writeHistogram(outfile);
                SS_SF_dilep_2j_1b->writeHistogram(outfile);
                SS_SF_dilep_2j_ge2b->writeHistogram(outfile);
                SS_SF_dilep_3j_0b->writeHistogram(outfile);
                SS_SF_dilep_3j_1b->writeHistogram(outfile);
                SS_SF_dilep_3j_ge2b->writeHistogram(outfile);
                SS_SF_dilep_ge4j_0b->writeHistogram(outfile);
                SS_SF_dilep_ge4j_1b->writeHistogram(outfile);
                SS_SF_dilep_ge4j_ge2b->writeHistogram(outfile);

                SS_OF_dilep_2j_0b->writeHistogram(outfile);
                SS_OF_dilep_2j_1b->writeHistogram(outfile);
                SS_OF_dilep_2j_ge2b->writeHistogram(outfile);
                SS_OF_dilep_3j_0b->writeHistogram(outfile);
                SS_OF_dilep_3j_1b->writeHistogram(outfile);
                SS_OF_dilep_3j_ge2b->writeHistogram(outfile);
                SS_OF_dilep_ge4j_0b->writeHistogram(outfile);
                SS_OF_dilep_ge4j_1b->writeHistogram(outfile);
                SS_OF_dilep_ge4j_ge2b->writeHistogram(outfile);

                OS_SF_dilep_2j_0b->writeHistogram(outfile);
                OS_SF_dilep_2j_1b->writeHistogram(outfile);
                OS_SF_dilep_2j_ge2b->writeHistogram(outfile);
                OS_SF_dilep_3j_0b->writeHistogram(outfile);
                OS_SF_dilep_3j_1b->writeHistogram(outfile);
                OS_SF_dilep_3j_ge2b->writeHistogram(outfile);
                OS_SF_dilep_ge4j_0b->writeHistogram(outfile);
                OS_SF_dilep_ge4j_1b->writeHistogram(outfile);
                OS_SF_dilep_ge4j_ge2b->writeHistogram(outfile);

                OS_OF_dilep_2j_0b->writeHistogram(outfile);
                OS_OF_dilep_2j_1b->writeHistogram(outfile);
                OS_OF_dilep_2j_ge2b->writeHistogram(outfile);
                OS_OF_dilep_3j_0b->writeHistogram(outfile);
                OS_OF_dilep_3j_1b->writeHistogram(outfile);
                OS_OF_dilep_3j_ge2b->writeHistogram(outfile);
                OS_OF_dilep_ge4j_0b->writeHistogram(outfile);
                OS_OF_dilep_ge4j_1b->writeHistogram(outfile);
                OS_OF_dilep_ge4j_ge2b->writeHistogram(outfile);

                SS_SF_flipEst_2j_0b->writeHistogram(outfile);
                SS_SF_flipEst_2j_1b->writeHistogram(outfile);
                SS_SF_flipEst_2j_ge2b->writeHistogram(outfile);
                SS_SF_flipEst_3j_0b->writeHistogram(outfile);
                SS_SF_flipEst_3j_1b->writeHistogram(outfile);
                SS_SF_flipEst_3j_ge2b->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_0b->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_1b->writeHistogram(outfile);
                SS_SF_flipEst_ge4j_ge2b->writeHistogram(outfile);

                SS_OF_flipEst_2j_0b->writeHistogram(outfile);
                SS_OF_flipEst_2j_1b->writeHistogram(outfile);
                SS_OF_flipEst_2j_ge2b->writeHistogram(outfile);
                SS_OF_flipEst_3j_0b->writeHistogram(outfile);
                SS_OF_flipEst_3j_1b->writeHistogram(outfile);
                SS_OF_flipEst_3j_ge2b->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_0b->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_1b->writeHistogram(outfile);
                SS_OF_flipEst_ge4j_ge2b->writeHistogram(outfile);

                onelepFO_2j_0b->writeHistogram(outfile);
                onelepFO_2j_1b->writeHistogram(outfile);
                onelepFO_2j_ge2b->writeHistogram(outfile);
                onelepFO_3j_0b->writeHistogram(outfile);
                onelepFO_3j_1b->writeHistogram(outfile);
                onelepFO_3j_ge2b->writeHistogram(outfile);
                onelepFO_ge4j_0b->writeHistogram(outfile);
                onelepFO_ge4j_1b->writeHistogram(outfile);
                onelepFO_ge4j_ge2b->writeHistogram(outfile);

                dilepFO_2j_0b->writeHistogram(outfile);
                dilepFO_2j_1b->writeHistogram(outfile);
                dilepFO_2j_ge2b->writeHistogram(outfile);
                dilepFO_3j_0b->writeHistogram(outfile);
                dilepFO_3j_1b->writeHistogram(outfile);
                dilepFO_3j_ge2b->writeHistogram(outfile);
                dilepFO_ge4j_0b->writeHistogram(outfile);
                dilepFO_ge4j_1b->writeHistogram(outfile);
                dilepFO_ge4j_ge2b->writeHistogram(outfile);

                fakeEst_from1FOCR_2j_0b->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_1b->writeHistogram(outfile);
                fakeEst_from1FOCR_2j_ge2b->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_0b->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_1b->writeHistogram(outfile);
                fakeEst_from1FOCR_3j_ge2b->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_0b->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_1b->writeHistogram(outfile);
                fakeEst_from1FOCR_ge4j_ge2b->writeHistogram(outfile);

                fakeEst_from2FOCR_2j_0b->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_1b->writeHistogram(outfile);
                fakeEst_from2FOCR_2j_ge2b->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_0b->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_1b->writeHistogram(outfile);
                fakeEst_from2FOCR_3j_ge2b->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_0b->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_1b->writeHistogram(outfile);
                fakeEst_from2FOCR_ge4j_ge2b->writeHistogram(outfile);

            }

        }



};
