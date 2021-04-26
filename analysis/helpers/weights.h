#include <fstream>
#include <iostream>
#include "./xsecs.h"

using namespace std;

double getEventWeight ( string sampleName, string inputDir, string tag ){
    
    double eventWeight;

    //get name of txt file with number MC events
    sampleName.erase(0, inputDir.length());
    //cout << sampleName << endl;
    int sampleEnd = sampleName.find("/output");
    string endToRemove = sampleName.substr(sampleEnd);
    sampleName.erase(sampleEnd,endToRemove.length());
    //cout << sampleName << endl;

    string fileEnding = "_n_events.txt";
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
