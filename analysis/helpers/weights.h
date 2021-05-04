#include <fstream>
#include <iostream>
#include "./xsecs.h"

using namespace std;

double getEventWeight (string fileName, string sampleName, bool verbose=false){
    if (verbose) std::cout << "sampleName: " << fileName << std::endl;
    
    double eventWeight;

    //get name of txt file with number MC events
    TString sName = TString(fileName.c_str());
    TObjArray *tokens = sName.Tokenize("/");
    unsigned int nentries = tokens->GetEntries();

    TString sName_short;
    std::string fname;
    if (TString(fileName).Contains("hadoop")) {
        sName_short = ((TObjString*)tokens->At(nentries-2) )->GetString();
        if (verbose) std::cout << "sName: " << sName_short << std::endl;
        string fileEnding = "_n_events.txt";
        fname = sName_short.Data()+fileEnding;
        if (verbose) std::cout << "fname: " << fname << std::endl;
    }
    else if (TString(fileName).Contains("nfs")) {
        sName_short = ((TObjString*)tokens->At(nentries-1) )->GetString();
        sName_short = ( (TObjString*)sName_short.Tokenize(".")->At(0) )->GetString();
        if (verbose) std::cout << "sName: " << sName_short << std::endl;
        string fileEnding = "_n_events.txt";
        fname = sName_short.Data()+fileEnding;
        if (verbose) std::cout << "fname: " << fname << std::endl;
    }

    TString sTag = ((TObjString*)tokens->At(nentries-3) )->GetString();
    if (verbose) std::cout << "sTag: " << sTag << std::endl;
    std::string tag = sTag.Data();

    //get the number of MC events from sample
    ifstream inFile;
    inFile.open("./n_events/"+fname);

    int lineToGet = 2;
    string numEvents;
    for ( int i = 0; i < lineToGet; i++ ){
        std::getline(inFile, numEvents);
        if (verbose) cout << "line " << i << ": "<< numEvents << endl;
    }

    double nEvents = stod(numEvents);
    //cout << "num effective events: " << nEvents << endl;


    //get name of sample for xsec map
    //tag.pop_back();
    //int sampleEnd_xsec = sampleName.find(tag);
    //string endToRemove_xsec = sampleName.substr(sampleEnd_xsec);
    //sampleName.erase(sampleEnd_xsec,endToRemove_xsec.length());
    //sampleName.pop_back();

    //get xsec
    double xsecWeight = 1000 * getXSec(sampleName);
    if (verbose) cout << "xsecWeight: " << xsecWeight << std::endl;
    
    //calculate weight
    eventWeight = xsecWeight/nEvents;

    return eventWeight;
}//close function
