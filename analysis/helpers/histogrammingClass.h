void makeHistogram(string variableName, string numLep, string numJet, string numB, string sampleName, int nBins, float xMin, float xMax, vector<float> content, vector<float> weight, TFile* &outFile){
    
    string histoName = "h_"+variableName+"_"+numLep+"_"+numJet+"_"+numB+"_"+sampleName;
    auto histo = new TH1F( histoName.c_str(), variableName, nBins, xMin, xMax );

    int numEntries = content.size();

    for( int i = 0; i<=numEntries; i++ ){
        histo->Fill(content[i], weight[i]);
    }

    if (outFile.is_open){
        histo->Write();
    }

}