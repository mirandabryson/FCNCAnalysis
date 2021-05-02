#include <fstream>
#include <iostream>
#include "./xsecs.h"

using namespace std;

double getEventWeight (string sampleName){
    
    double eventWeight;

    //get name of txt file with number MC events
    TString sName = TString(sampleName.c_str());
    TObjArray *tokens = sName.Tokenize("/");
    unsigned int nentries = tokens->GetEntries();
    TString str1 = ((TObjString*)tokens->At(nentries-2) )->GetString();
    TString str2 = ((TObjString*)tokens->At(nentries-1) )->GetString();
    std::string sName_short = (str1+"/"+str2).Data();
    int sampleEnd = sName_short.find("/output");
    string endToRemove = sampleName.substr(sampleEnd);
    sampleName.erase(sampleEnd,endToRemove.length());
    TString input_dir = "";
    for (unsigned int idx=0; idx<nentries-2; idx++) {
        input_dir = input_dir+"/"+((TObjString*)tokens->At(idx) )->GetString();
    }
    std::string inputDir = input_dir.Data();
    std::string tag = ((TObjString*)tokens->At(nentries-3) )->GetString().Data();

    string fileEnding = "_n_events.txt";
    sampleName = ((TObjString*)tokens->At(nentries-2) )->GetString().Data();
    sampleName = sampleName+fileEnding;
    //cout << sampleName << endl;

    //get the number of MC events from sample
    ifstream inFile;
    inFile.open("./n_events/"+sampleName);

    int lineToGet = 2;
    string numEvents;
    for ( int i = 0; i < lineToGet; i++ ){
        std::getline(inFile, numEvents);
        //cout << "line " << i << ": "<< numEvents << endl;
    }

    double nEvents = stod(numEvents);
    //cout << "num effective events: " << nEvents << endl;


    //get name of sample for xsec map
    tag.pop_back();
    int sampleEnd_xsec = sampleName.find(tag);
    string endToRemove_xsec = sampleName.substr(sampleEnd_xsec);
    sampleName.erase(sampleEnd_xsec,endToRemove_xsec.length());
    sampleName.pop_back();

    //get xsec
    double xsecWeight = 1000 * getXSec(sampleName);
    
    //calculate weight
    eventWeight = xsecWeight/nEvents;

    return eventWeight;
}//close function
