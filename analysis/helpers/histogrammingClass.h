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
        sampleHistogram(string sampleName){
            h_srCategories = new TH1F( ("h_srYields_"+sampleName).c_str(), "SR_Yields", 0, 18, 18 );
            h_backgroundTypes = new TH1F( ("h_backgroundTypes_"+sampleName).c_str(),"backgroundCategories", 0, 3, 3 );
        }
        void fillBackgroundTypes(vector<bool>variables){
            bool isFake = variables[0];
            bool isFlip = variables[1];
            bool isOther = variables[2];

            int bin = 5;
            if(isFake) bin = 0;
            if(isFlip) bin = 1;
            if(isOther) bin = 2;

            h_backgroundTypes->AddBinContent(bin);
        }
        void fillSRCategories(int numLep, int numJet, int numB){
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
            h_srCategories->AddBinContent(bin)
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
        sampleHistogram* TTZToLL_M-1to10;
        sampleHistogram* DYJetsToLL_M-10to50;
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
        sampleHistogram* WpWpJJ_EWK-QCD;
        sampleHistogram* VHToNonbb_M125;
        sampleHistogram* tZq_ll_4f_ckm_NLO;
        sampleHistogram* ttHToNonbb_M125;
    public:
        makeSampleHistos(){
            TTGamma_SingleLept = new sampleHistogram("TTGamma_SingleLept");
            TGJets = new sampleHistogram("TGJets");
            TTWJetsToLNu = new sampleHistogram("TTWJetsToLNu");
            WJetsToLNu = new sampleHistogram("WJetsToLNu");
            ST_tWll_5f_LO = new sampleHistogram("ST_tWll_5f_LO");
            TTGamma_Dilept = new sampleHistogram("TTGamma_Dilept");
            TTZToLLNuNu_M10 = new sampleHistogram("TTZToLLNuNu_M10");
            TTZToLL_M-1to10 = new sampleHistogram("TTZToLL_M-1to10");
            DYJetsToLL_M-10to50 = new sampleHistogram("DYJetsToLL_M-10to50");
            DYJetsToLL_M50 = new sampleHistogram("DYJetsToLL_M50");
            ZGToLLG_01J_5f = new sampleHistogram("ZGToLLG_01J_5f");
            ZZTo4L = new sampleHistogram("ZZTo4L");
            ZZZ = new sampleHistogram("ZZZ");
            GluGluHToZZTo4L = new sampleHistogram("GluGluHToZZTo4L");
            GluGluToContinToZZTo2e2mu = new sampleHistogram("GluGluToContinToZZTo2e2mu");
            GluGluToContinToZZTo2e2tau = new sampleHistogram("GluGluToContinToZZTo2e2tau");
            GluGluToContinToZZTo2mu2tau = new sampleHistogram("GluGluToContinToZZTo2mu2tau");
            GluGluToContinToZZTo4e = new sampleHistogram("GluGluToContinToZZTo4e");
            GluGluToContinToZZTo4mu = new sampleHistogram("GluGluToContinToZZTo4mu");
            GluGluToContinToZZTo4tau = new sampleHistogram("GluGluToContinToZZTo4tau");
            WWG = new sampleHistogram("WWG");
            WWTo2L2Nu_DoubleScattering = new sampleHistogram("WWTo2L2Nu_DoubleScattering");
            WWW_4F = new sampleHistogram("WWW_4F");
            WWZ = new sampleHistogram("WWZ");
            WZG = new sampleHistogram("WZG");
            WZTo3LNu = new sampleHistogram("WZTo3LNu");
            WZZ = new sampleHistogram("WZZ");
            TTJets = new sampleHistogram("TTJets");
            TTHH = new sampleHistogram("TTHH");
            TTTJ = new sampleHistogram("TTTJ");
            TTTT = new sampleHistogram("TTTT");
            TTTW = new sampleHistogram("TTTW");
            TTWH = new sampleHistogram("TTWH");
            TTWW = new sampleHistogram("TTWW");
            TTWZ = new sampleHistogram("TTWZ");
            TTZH = new sampleHistogram("TTZH");
            TTZZ = new sampleHistogram("TTZZ");
            WGToLNuG_01J_5f = new sampleHistogram("WGToLNuG_01J_5f");
            WpWpJJ_EWK-QCD = new sampleHistogram("WpWpJJ_EWK-QCD");
            VHToNonbb_M125 = new sampleHistogram("VHToNonbb_M125");
            tZq_ll_4f_ckm_NLO = new sampleHistogram("tZq_ll_4f_ckm_NLO");
            ttHToNonbb_M125 = new sampleHistogram("ttHToNonbb_M125");
        }
        void fillHistos(string sampleName, vector<int>variables, bool isSRYield){
            int TTGamma_SingleLept_idx = sampleName.find("TTGamma_SingleLept");
            int TGJets_idx = sampleName.find("TGJets");
            int TTWJetsToLNu_idx = sampleName.find("TTWJetsToLNu");
            int WJetsToLNu_idx = sampleName.find("WJetsToLNu");
            int ST_tWll_5f_LO_idx = sampleName.find("ST_tWll_5f_LO");
            int TTGamma_Dilept_idx = sampleName.find("TTGamma_Dilept");
            int TTZToLLNuNu_M10_idx = sampleName.find("TTZToLLNuNu_M10");
            int TTZToLL_M-1to10_idx = sampleName.find("TTZToLL_M-1to10");
            int DYJetsToLL_M-10to50_idx = sampleName.find("DYJetsToLL_M-10to50");
            int DYJetsToLL_M50_idx = sampleName.find("DYJetsToLL_M50");
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
            int WpWpJJ_EWK-QCD_idx = sampleName.find("WpWpJJ_EWK-QCD");
            int VHToNonbb_M125_idx = sampleName.find("VHToNonbb_M125");
            int tZq_ll_4f_ckm_NLO_idx = sampleName.find("tZq_ll_4f_ckm_NLO");
            int ttHToNonbb_M125_idx = sampleName.find("ttHToNonbb_M125");

            if(isSRYield){
                int nLep = variables[0];
                int nJet = variables[1];
                int nBs = variables[2];
            }

            if(TTGamma_SingleLept_idx!=-1){
                if(isSRYield){
                    TTGamma_SingleLept->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTGamma_SingleLept->fillBackgroundTypes(variables);
                }
            }else if(TGJets_idx!=-1){
                if(isSRYield){
                    TGJets->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TGJets->fillBackgroundTypes(variables);
                }
            }else if(TTWJetsToLNu_idx!=-1){
                if(isSRYield){
                    TTWJetsToLNu->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTWJetsToLNu->fillBackgroundTypes(variables);
                }
            }else if(WJetsToLNu_idx!=-1){
                if(isSRYield){
                    WJetsToLNu->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WJetsToLNu->fillBackgroundTypes(variables);
                }
            }else if(ST_tWll_5f_LO_idx!=-1){
                if(isSRYield){
                    ST_tWll_5f_LO->fillSRCategories(nLep, nJet, nBs);
                }else{
                    ST_tWll_5f_LO->fillBackgroundTypes(variables);
                }
            }else if(TTGamma_Dilept_idx!=-1){
                if(isSRYield){
                    TTGamma_Dilept->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTGamma_Dilept->fillBackgroundTypes(variables);
                }
            }else if(TTZToLLNuNu_M10_idx!=-1){
                if(isSRYield){
                    TTZToLLNuNu_M10->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTZToLLNuNu_M10->fillBackgroundTypes(variables);
                }
            }else if(TTZToLL_M-1to10_idx!=-1){
                if(isSRYield){
                    TTZToLL_M-1to10->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTZToLL_M-1to10->fillBackgroundTypes(variables);
                }
            }else if(DYJetsToLL_M-10to50_idx!=-1){
                if(isSRYield){
                    DYJetsToLL_M-10to50->fillSRCategories(nLep, nJet, nBs);
                }else{
                    DYJetsToLL_M-10to50->fillBackgroundTypes(variables);
                }
            }else if(DYJetsToLL_M50_idx!=-1){
                if(isSRYield){
                    DYJetsToLL_M50->fillSRCategories(nLep, nJet, nBs);
                }else{
                    DYJetsToLL_M50->fillBackgroundTypes(variables);
                }
            }else if(ZGToLLG_01J_5f_idx!=-1){
                if(isSRYield){
                    ZGToLLG_01J_5f->fillSRCategories(nLep, nJet, nBs);
                }else{
                    ZGToLLG_01J_5f->fillBackgroundTypes(variables);
                }
            }else if(ZZTo4L_idx!=-1){
                if(isSRYield){
                    ZZTo4L->fillSRCategories(nLep, nJet, nBs);
                }else{
                    ZZTo4L->fillBackgroundTypes(variables);
                }
            }else if(ZZZ_idx!=-1){
                if(isSRYield){
                    ZZZ->fillSRCategories(nLep, nJet, nBs);
                }else{
                    ZZZ->fillBackgroundTypes(variables);
                }
            }else if(GluGluHToZZTo4L_idx!=-1){
                if(isSRYield){
                    GluGluHToZZTo4L->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluHToZZTo4L->fillBackgroundTypes(variables);
                }
            }else if(GluGluToContinToZZTo2e2mu_idx!=-1){
                if(isSRYield){
                    GluGluToContinToZZTo2e2mu->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluToContinToZZTo2e2mu->fillBackgroundTypes(variables);
                }
            }else if(GluGluToContinToZZTo2e2tau_idx!=-1){
                if(isSRYield){
                    GluGluToContinToZZTo2e2tau->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluToContinToZZTo2e2tau->fillBackgroundTypes(variables);
                }
            }else if(GluGluToContinToZZTo2mu2tau_idx!=-1){
                if(isSRYield){
                    GluGluToContinToZZTo2mu2tau->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluToContinToZZTo2mu2tau->fillBackgroundTypes(variables);
                }
            }else if(GluGluToContinToZZTo4e_idx!=-1){
                if(isSRYield){
                    GluGluToContinToZZTo4e->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluToContinToZZTo4e->fillBackgroundTypes(variables);
                }
            }else if(GluGluToContinToZZTo4mu_idx!=-1){
                if(isSRYield){
                    GluGluToContinToZZTo4mu->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluToContinToZZTo4mu->fillBackgroundTypes(variables);
                }
            }else if(GluGluToContinToZZTo4tau_idx!=-1){
                if(isSRYield){
                    GluGluToContinToZZTo4tau->fillSRCategories(nLep, nJet, nBs);
                }else{
                    GluGluToContinToZZTo4tau->fillBackgroundTypes(variables);
                }
            }else if(WWG_idx!=-1){
                if(isSRYield){
                    WWG->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WWG->fillBackgroundTypes(variables);
                }
            }else if(WWTo2L2Nu_DoubleScattering_idx!=-1){
                if(isSRYield){
                    WWTo2L2Nu_DoubleScattering->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WWTo2L2Nu_DoubleScattering->fillBackgroundTypes(variables);
                }
            }else if(WWW_4F_idx!=-1){
                if(isSRYield){
                    WWW_4F->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WWW_4F->fillBackgroundTypes(variables);
                }
            }else if(WWZ_idx!=-1){
                if(isSRYield){
                    WWZ->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WWZ->fillBackgroundTypes(variables);
                }
            }else if(WZG_idx!=-1){
                if(isSRYield){
                    WZG->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WZG->fillBackgroundTypes(variables);
                }
            }else if(WZTo3LNu_idx!=-1){
                if(isSRYield){
                    WZTo3LNu->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WZTo3LNu->fillBackgroundTypes(variables);
                }
            }else if(WZZ_idx!=-1){
                if(isSRYield){
                    WZZ->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WZZ->fillBackgroundTypes(variables);
                }
            }else if(TTJets_idx!=-1){
                if(isSRYield){
                    TTJets->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTJets->fillBackgroundTypes(variables);
                }
            }else if(TTHH_idx!=-1){
                if(isSRYield){
                    TTHH->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTHH->fillBackgroundTypes(variables);
                }
            }else if(TTTJ_idx!=-1){
                if(isSRYield){
                    TTTJ->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTTJ->fillBackgroundTypes(variables);
                }
            }else if(TTTT_idx!=-1){
                if(isSRYield){
                    TTTT->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTTT->fillBackgroundTypes(variables);
                }
            }else if(TTTW_idx!=-1){
                if(isSRYield){
                    TTTW->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTTW->fillBackgroundTypes(variables);
                }
            }else if(TTWH_idx!=-1){
                if(isSRYield){
                    TTWH->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTWH->fillBackgroundTypes(variables);
                }
            }else if(TTWW_idx!=-1){
                if(isSRYield){
                    TTWW->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTWW->fillBackgroundTypes(variables);
                }
            }else if(TTWZ_idx!=-1){
                if(isSRYield){
                    TTWZ->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTWZ->fillBackgroundTypes(variables);
                }
            }else if(TTZH_idx!=-1){
                if(isSRYield){
                    TTZH->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTZH->fillBackgroundTypes(variables);
                }
            }else if(TTZZ_idx!=-1){
                if(isSRYield){
                    TTZZ->fillSRCategories(nLep, nJet, nBs);
                }else{
                    TTZZ->fillBackgroundTypes(variables);
                }
            }else if(WGToLNuG_01J_5f_idx!=-1){
                if(isSRYield){
                    WGToLNuG_01J_5f->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WGToLNuG_01J_5f->fillBackgroundTypes(variables);
                }
            }else if(WpWpJJ_EWK-QCD_idx!=-1){
                if(isSRYield){
                    WpWpJJ_EWK-QCD->fillSRCategories(nLep, nJet, nBs);
                }else{
                    WpWpJJ_EWK-QCD->fillBackgroundTypes(variables);
                }
            }else if(VHToNonbb_M125_idx!=-1){
                if(isSRYield){
                    VHToNonbb_M125->fillSRCategories(nLep, nJet, nBs);
                }else{
                    VHToNonbb_M125->fillBackgroundTypes(variables);
                }
            }else if(tZq_ll_4f_ckm_NLO_idx!=-1){
                if(isSRYield){
                    tZq_ll_4f_ckm_NLO->fillSRCategories(nLep, nJet, nBs);
                }else{
                    tZq_ll_4f_ckm_NLO->fillBackgroundTypes(variables);
                }
            }else if(ttHToNonbb_M125_idx!=-1){
                if(isSRYield){
                    ttHToNonbb_M125->fillSRCategories(nLep, nJet, nBs);
                }else{
                    ttHToNonbb_M125->fillBackgroundTypes(variables);
                }
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
            TTZToLL_M-1to10->writeHistograms(outfile);
            DYJetsToLL_M-10to50->writeHistograms(outfile);
            DYJetsToLL_M50->writeHistograms(outfile);
            ZGToLLG_01J_5f->writeHistograms(outfile);
            ZZTo4L->writeHistograms(outfile);
            ZZZ_TuneCP5->writeHistograms(outfile);
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
            WpWpJJ_EWK-QCD->writeHistograms(outfile);
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
