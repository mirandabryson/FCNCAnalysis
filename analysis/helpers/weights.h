#include <fstream>
#include <iostream>
#include "./xsecs.h"
#include "TObjString.h"

using namespace std;

double getEventWeight (string fileName, string sampleName, int year, double sum_wgts, bool verbose=false){
    if (verbose) std::cout << "sampleName: " << fileName << std::endl;
    
    double eventWeight;

    //get name of txt file with number MC events
    TString sName = TString(fileName.c_str());
    TObjArray *tokens = sName.Tokenize("/");
    unsigned int nentries = tokens->GetEntries();
    //cout << sName << endl;

    TString sTag = ((TObjString*)tokens->At(nentries-3))->GetString();
    if (verbose) std::cout << "sTag: " << sTag << std::endl;
    std::string tag = sTag.Data();

    TString sName_short;
    std::string fname;
    if (TString(fileName).Contains("hadoop")) {
        sName_short = ((TObjString*)tokens->At(nentries-2))->GetString();
        if (verbose) std::cout << "sName: " << sName_short << std::endl;
        string fileEnding = "_n_events.txt";
        fname = short_to_long(sName_short.Data(), year)+'_'+tag+fileEnding;
        if (verbose) std::cout << "fname: " << fname << std::endl;
    }
    else if (TString(fileName).Contains("ceph")) {
        sName_short = ((TObjString*)tokens->At(nentries-2))->GetString();
        TObjArray *tmp_string = sName_short.Tokenize(".");
        sName_short = ((TObjString*)(tmp_string->At(0)))->GetString();
        delete tmp_string;
        //sName_short = ((TObjString*)sName_short.Tokenize(".")->At(0) )->GetString();
        if (verbose) std::cout << "sName: " << sName_short << std::endl;
        string fileEnding = "_n_events.txt";
        fname = short_to_long(sName_short.Data(), year)+'_'+tag+fileEnding;
        if (verbose) std::cout << "fname: " << fname << std::endl;
    }
    //get the number of MC events from sample
    ifstream inFile;
    inFile.open("./n_events/"+fname);

    int lineToGet = 2;
    string numEvents;
    for ( int i = 0; i < lineToGet; i++ ){
        std::getline(inFile, numEvents);
        if (verbose) cout << "line " << i << ": "<< numEvents << endl;
    }
    //delete &sName_short;
    // double nEvents = stod(numEvents);
    //cout << "num effective events: " << nEvents << endl;


    //get name of sample for xsec map
    //tag.pop_back();
    //int sampleEnd_xsec = sampleName.find(tag);
    //string endToRemove_xsec = sampleName.substr(sampleEnd_xsec);
    //sampleName.erase(sampleEnd_xsec,endToRemove_xsec.length());
    //sampleName.pop_back();

    //get xsec
    double xsecWeight = 1000 * getXSec(sName_short.Data());
    if (verbose) cout << "xsecWeight: " << xsecWeight << std::endl;
    
    // cout << xsecWeight << endl;
    //calculate weight
    //REMOVED DIVISION IN NEXT LINE TO ACCOMODATE FOR TOTAL SUM_WGTS APPLIED AFTER FILE LOOP IN EVENTLOOPER
    eventWeight = xsecWeight;
    if (verbose) cout << "scale1fb: " << eventWeight << std::endl;
    inFile.close();
    delete tokens; //potential memory leak
    return eventWeight;
    if (verbose) cout << "end of geteventweight" << std::endl;
}//close function
