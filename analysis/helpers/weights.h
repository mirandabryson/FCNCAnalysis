#include <fstream>
#include <iostream>
#include "./xsecs.h"

using namespace std;

double getEventWeight ( string sampleName, string inputDir, string tag, int year ){
    
    double eventWeight;

    //get name of txt file with number MC events
    sampleName.erase(0, inputDir.length());
    //cout << "first call: " << sampleName << endl;
    int sampleEnd = sampleName.find(".root");
    string endToRemove = sampleName.substr(sampleEnd);
    sampleName.erase(sampleEnd,endToRemove.length());
    string xsec_sampleName = sampleName;
    //cout << "second call: " << sampleName << endl;

    string fileEnding = "_n_events.txt";
    sampleName = sampleName+fileEnding;
    //cout << "third call: " << sampleName << endl;

    //get the number of MC events from sample
    ifstream inFile;
    inFile.open("./n_events/"+to_string(year)+"/"+sampleName);

    int lineToGet = 2;
    string numEvents;
    for ( int i = 0; i < lineToGet; i++ ){
        std::getline(inFile, numEvents);
       //cout << "line " << i << ": "<< numEvents << endl;
    }

    double nEvents = stod(numEvents);
    //cout << "num effective events: " << nEvents << endl;

    //get xsec
    double xsecWeight = 1000 * getXSec(xsec_sampleName);
    
    //calculate weight
    eventWeight = xsecWeight/nEvents;

    return eventWeight;
}//close function
