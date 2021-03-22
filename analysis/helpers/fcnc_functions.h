//header file for fcnc functions
#include <iostream>
#include <cstdlib>
#include <TChain.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TPad.h>
#include <THStack.h>
#include <TLegend.h>

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

bool isTightLepton( float pdgid, float pt, float eta, float miniIso_all, bool tight_id ){

    bool isTight = 0;
    if ( abs( eta ) < 2.4 ){
        if ( abs( pdgid ) == 11 && pt > 25 && miniIso_all < 0.12 ){
            isTight = 1;
        }else if( abs( pdgid ) ==13 && pt > 20 && tight_id == 1 and miniIso_all < 0.16 ){
            isTight = 1;
        }else {
            isTight = 0;
        }
    }else {
        isTight = 0;
    }
    return isTight;

}

bool isLooseLepton( float pdgid, float pt, float eta, float miniIso_all, bool loose_id ){
    
    bool isLoose = 0;
    if ( abs( eta ) <2.4 ){
        if ( pdgid==11 and pt>25 and miniIso_all > 0.12 and miniIso_all < 0.4 ){
            isLoose = 1;
        }else if ( pdgid==13 and pt>20 and loose_id == 1 and miniIso_all > 0.12 and miniIso_all < 0.4 ){
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

/*void saveFig(vector<TH1F> v_hist, string hist_name, string outdir){

    vector< TH1F > v_hist_new;
    int max_idx = 0;
    int max_val = 0;
    for (uint i = 0; i < v_hist.size(); i++){
        if(v_hist[i].GetMaximum()>max_val){
            max_val = v_hist[i].GetMaximum();
            max_idx = i;
        }
    }

    v_hist_new.push_back(v_hist[max_idx]);
    for(int j = 0; j < max_idx; j++){
        v_hist_new.push_back(v_hist[j]);
    }
    for(int k = v_hist.size(); k > max_idx; k--){
        v_hist_new.push_back(v_hist[k]);
    }


    auto can = new TCanvas( "c", "c", 800, 800 );

    TPad *pad1 = new TPad( "pad1", "pad1", 0, 0.3, 1, 1.0 );
    pad1->Draw();

    pad1->cd();
    for(uint h = 0; h < v_hist_new.size(); h++){
        if (h==0){
            v_hist_new[h].Draw();
        }else{
            v_hist_new[h].Draw("same");
        }
    }

    string filename = outdir.append(hist_name);
    string filename_pdf = filename.append(".pdf");
    string filename_png = filename.append(".png");

    can->SaveAs(filename_pdf.c_str());
    can->SaveAs(filename_png.c_str());
}*/

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