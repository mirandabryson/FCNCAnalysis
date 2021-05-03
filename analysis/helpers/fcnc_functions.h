//header file for fcnc functions
#include <iostream>
#include <cstdlib>
#include <TChain.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>
#include <THStack.h>
#include <TLegend.h>

using namespace std;

float deltaR( float obj1_eta, float obj1_phi, float obj2_eta, float obj2_phi ){
    float deltaEta = obj1_eta - obj2_eta;
    float deltaPhi = obj1_phi - obj2_phi;

    float deltaR = sqrt( pow( deltaEta, 2 ) + pow( deltaPhi, 2 ) );
    
    return deltaR;
}

float mt( float obj1_pt, float obj1_phi, float obj2_pt, float obj2_phi ){
    float mt = sqrt( 2*obj1_pt*obj2_pt * ( 1 - cos(obj1_phi - obj2_phi) ) );
    
    return mt;
}

float coneCorrPt(int year, int id, float lep_pt, float mini_iso, float jet_iso, float pt_rel) {
    float ptrel_cut = 0;
    float miniIso_cut = 0;
    float ptRatio_cut = 0;
    if (year == 2016){
        if(abs(id)==11){
            ptrel_cut = 7.2;
            miniIso_cut = 0.12;
            ptRatio_cut = 0.80;
        }else if(abs(id)==13){
            ptrel_cut = 7.2;
            miniIso_cut = 0.12;
            ptRatio_cut = 0.76;
        }
    }else{
        if(abs(id)==11){
            ptrel_cut = 8.0;
            miniIso_cut = 0.07;
            ptRatio_cut = 0.78;
        }else if(abs(id)==13){
            ptrel_cut = 6.8;
            miniIso_cut = 0.11;
            ptRatio_cut = 0.74;
        }
    }
    float pt_ratio = 1/(jet_iso + 1);

    float jet_pt = lep_pt / pt_ratio;
    if (pt_rel > ptrel_cut) {
        return lep_pt * (1 + std::max(float(0), mini_iso - miniIso_cut));
    } else {
        return std::max(lep_pt, jet_pt * ptRatio_cut);
    }
}

bool passesIso(float mini_iso, float mini_iso_cut, float jet_iso, float pt_ratio_cut, float pt_rel, float pt_rel_cut){
    float pt_ratio = 1/(jet_iso + 1);

    bool pass_miniIso = mini_iso < mini_iso_cut;
    bool pass_pt_ratio = pt_ratio > pt_ratio_cut;
    bool pass_pt_rel = pt_rel > pt_rel_cut;

    return ( pass_miniIso && (pass_pt_ratio || pass_pt_rel) );
}

int isoType(int year, int pdgid, float miniIso, float jetIso, float ptRel){

    int isoType = 0; //1 for fakable, 2 for tight, else 0

    //for muons
    if(abs(pdgid) == 13){
        if (year == 2018 || year == 2017){
            if (passesIso(miniIso, 0.11, jetIso, 0.74, ptRel, 6.8)){
                isoType = 2;
            }else if (miniIso < 0.4){
                isoType = 1;
            }
        }else if(year == 2016){
            if(passesIso(miniIso, 0.16, jetIso, 0.76, ptRel, 7.2)){
                isoType = 2;
            }else if(miniIso < 0.4){
                isoType = 1;
            }
        }//year
    }else if (abs(pdgid)==11){
        if(year == 2018 or year == 2017){
            if (passesIso(miniIso, 0.07, jetIso, 0.78, ptRel, 8.0)){
                isoType = 2;
            }else if (miniIso <= 0.4){
                isoType = 1;
            }
        }else if(year == 2016){
            if (passesIso(miniIso, 0.12, jetIso, 0.80, ptRel, 7.2)){
                isoType = 2;
            }else if (miniIso <= 0.4){
                isoType = 1;
            }
        }//year
    }//lepton flavor check
    return isoType;
}

bool isGoodElectron( float dxy, float dz, float sip3d, float tightCharge, int lostHits, bool convVeto ){

    bool isGood = 0;

    if ( abs(dxy)<0.05 && abs(dz)<0.1 && abs(sip3d)<4 && tightCharge ==2 ){
        if ( lostHits==0 && convVeto==1 ){
            isGood=1;
        }
        else isGood = 0;
    }else isGood = 0;

    return isGood;

}

bool isGoodMuon( float dxy, float dz, float sip3d, float tightCharge, bool mediumID, float chargeQuality ){

    bool isGood = 0;

    if ( abs(dxy)<0.05 && abs(dz)<0.1 && abs(sip3d)<4 && tightCharge ==2 ){
        if ( mediumID == 1 && chargeQuality < 0.2 ){
            isGood = 1;
        }
        else isGood = 0;
    }else isGood = 0;

    return isGood;

}

bool isTightLepton( float pdgid, float pt, float eta, bool isGood, int isoType ){

    bool isTight = 0;
    if ( abs( eta ) < 2.4 && isGood == 1 && isoType == 2 ){
        if ( abs( pdgid ) == 11 && pt > 25 ){
            isTight = 1;
        }else if( abs( pdgid ) == 13 && pt > 20 ){
            isTight = 1;
        }else {
            isTight = 0;
        }
    }else {
        isTight = 0;
    }
    return isTight;

}

bool isLooseLepton( float pdgid, float pt, float eta, bool isGood, int isoType ){
    
    bool isLoose = 0;
    if ( abs( eta ) <2.4 && isGood == 1 && isoType == 1 ){
        if ( pdgid==11 && pt>25 ){
            isLoose = 1;
        }else if ( pdgid==13 && pt>20 ){
            isLoose = 1;
        }else {
            isLoose = 0;
        }
    }else {
        isLoose = 0;
    }
    return isLoose;
}

bool isGoodJet(float pt, float eta){
  
    bool isGood = 0;
    
    if ( pt > 25 && abs( eta ) < 2.4 ){      
        isGood = 1;
    }else{
        isGood = 0;
    }
    return isGood;
}

bool electronID(int year, float eta, float pt, float mva_in, string idType){
    bool isLoose = 0;
    bool isTight = 0;

    float mva_cut = -999;
    float mva = 0;
    if ( year==2018 ){
        mva = log((1+mva_in)/(1-mva_in))/2;
    }else{
        mva = mva_in;
    }

    if ( year==2018 ){
        if ( abs( eta ) > 0 && abs( eta ) < 0.8 ){
            if ( pt > 5 && pt < 10 ){
                if ( idType == "loose" && mva > 0.053 ){
                    isLoose = 1;
                }else if ( idType == "tight" ){
                    //there is no tight WP for this, so I will set this automatically to true
                    isTight = 1;
                }//tight or loose
            }else if ( pt > 10 && pt < 25 ){
                if ( idType == "loose" ){
                    mva_cut = ( -0.106 + (0.062*(pt-10)) );
                    if ( mva > mva_cut ){
                        isLoose = 1;
                    }//mva cut
                }else if ( idType == "tight" ){
                    mva_cut = ( 4.277 + (0.112*(pt-10)) );
                    if (mva > mva_cut){
                        isTight = 1;
                    }//mva cut
                }//tight or loose
            }else if ( pt > 25 ){
                if ( idType == "loose" && mva > -0.106 ){
                    isLoose = 1;
                }else if ( idType == "tight" && mva > 4.277 ){
                    isTight = 1;
                }//tight or loose
            }//pt

        }else if( abs( eta ) > 0.8 && abs( eta ) < 1.479 ){
            if ( pt > 5 && pt < 10 ){
                if ( idType == "loose" && mva > -0.434 ){
                    isLoose = 1;
                }else if ( idType == "tight" ){
                    //there is no tight WP for this, so I will set this automatically to true
                    isTight = 1;
                }//tight or loose
            }else if ( pt > 10 && pt < 25 ){
                if ( idType == "loose" ){
                    mva_cut = ( -0.769 + (0.038*(pt-10)) );
                    if ( mva > mva_cut ){
                        isLoose = 1;
                    }//mva cut
                }else if ( idType == "tight" ){
                    mva_cut = ( 3.152 + (0.060*(pt-10)) );
                    if (mva > mva_cut){
                        isTight = 1;
                    }//mva cut
                }//tight or loose
            }else if ( pt > 25 ){
                if ( idType == "loose" && mva > -0.769 ){
                    isLoose = 1;
                }else if ( idType == "tight" && mva > 3.152 ){
                    isTight = 1;
                }//tight or loose
            }//pt

        }else if( abs( eta ) > 1.279 && abs( eta ) < 2.5 ){
            if ( pt > 5 && pt < 10 ){
                if ( idType == "loose" && mva > -0.956 ){
                    isLoose = 1;
                }else if ( idType == "tight" ){
                    //there is no tight WP for this, so I will set this automatically to true
                    isTight = 1;
                }//tight or loose
            }else if ( pt > 10 && pt < 25 ){
                if ( idType == "loose" ){
                    mva_cut = ( -1.461 + (0.042*(pt-10)) );
                    if ( mva > mva_cut ){
                        isLoose = 1;
                    }//mva cut
                }else if ( idType == "tight" ){
                    mva_cut = ( 2.359 + (0.087*(pt-10)) );
                    if (mva > mva_cut){
                        isTight = 1;
                    }//mva cut
                }//tight or loose
            }else if ( pt > 25 ){
                if ( idType == "loose" && mva > -1.461 ){
                    isLoose = 1;
                }else if ( idType == "tight" && mva > 2.359 ){
                    isTight = 1;
                }//tight or loose
            }//pt
        }//eta
    }//year

    if ( idType == "tight" ){
        return isTight;
    }else if ( idType == "loose" ){
        return isLoose;
    }else return 0;
}

void saveFig(THStack* &hists, TLegend* &leg, string hist_name, string outdir){

    auto can = new TCanvas( "c", "c", 800, 800 );

    TPad *pad1 = new TPad( "pad1", "pad1", 0, 0.3, 1, 1.0 );
    pad1->Draw();
    pad1->SetLogy();

    pad1->cd();
    hists->Draw("pfc nostack");
    leg->Draw();
    //pad1->BuildLegend(0.7, 0.7, 0.89, 0.89);

    string filename = outdir.append(hist_name);

    string filename_pdf = filename;
    filename_pdf = filename_pdf.append(".pdf");

    string filename_png = filename;
    filename_png = filename_png.append(".png");

    can->SaveAs(filename_pdf.c_str());
    can->SaveAs(filename_png.c_str());
}
