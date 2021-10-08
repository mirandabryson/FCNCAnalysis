#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TTree.h"
#include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"

#include "../../NanoTools/NanoCORE/Nano.h"
#include "../../NanoTools/NanoCORE/MetSelections.h"
#include "../../NanoTools/NanoCORE/Tools/JetCorrector.h"
#include "../../NanoTools/NanoCORE/tqdm.h"
#include "../../NanoTools/NanoCORE/Config.h"
#include "../../NanoTools/NanoCORE/SSSelections.h"

#include <iostream>
#include <iomanip>

// #define DEBUG

struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
#ifdef DEBUG
    #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
#else
    #define debug(args...)
#endif

using namespace std;
using namespace tas;

int findNormalization(TChain *ch, int nevents_to_process=-1)
{

    int nEventsTotal = 0;
    int nEventsChain = ch->GetEntries();
    TFile *currentFile = 0;
    TObjArray *listOfFiles = ch->GetListOfFiles();
    TIter fileIter(listOfFiles);
    tqdm bar;

    // TFile* scale_output = new TFile("scaleNormalization.root", "recreate");

    TH1D* h_pdf0 = new TH1D("h_pdf0", "h_pdf0", 1, 0,1000);
    TH1D* h_pdf1 = new TH1D("h_pdf1", "h_pdf1", 1, 0,1000);
    TH1D* h_pdf2 = new TH1D("h_pdf2", "h_pdf2", 1, 0,1000);
    TH1D* h_pdf3 = new TH1D("h_pdf3", "h_pdf3", 1, 0,1000);
    TH1D* h_pdf4 = new TH1D("h_pdf4", "h_pdf4", 1, 0,1000);
    TH1D* h_pdf5 = new TH1D("h_pdf5", "h_pdf5", 1, 0,1000);
    TH1D* h_pdf6 = new TH1D("h_pdf6", "h_pdf6", 1, 0,1000);
    TH1D* h_pdf7 = new TH1D("h_pdf7", "h_pdf7", 1, 0,1000);
    TH1D* h_pdf8 = new TH1D("h_pdf8", "h_pdf8", 1, 0,1000);
    TH1D* h_pdf9 = new TH1D("h_pdf9", "h_pdf9", 1, 0,1000);
    TH1D* h_pdf10 = new TH1D("h_pdf10", "h_pdf10", 1, 0,1000);
    TH1D* h_pdf11 = new TH1D("h_pdf11", "h_pdf11", 1, 0,1000);
    TH1D* h_pdf12 = new TH1D("h_pdf12", "h_pdf12", 1, 0,1000);
    TH1D* h_pdf13 = new TH1D("h_pdf13", "h_pdf13", 1, 0,1000);
    TH1D* h_pdf14 = new TH1D("h_pdf14", "h_pdf14", 1, 0,1000);
    TH1D* h_pdf15 = new TH1D("h_pdf15", "h_pdf15", 1, 0,1000);
    TH1D* h_pdf16 = new TH1D("h_pdf16", "h_pdf16", 1, 0,1000);
    TH1D* h_pdf17 = new TH1D("h_pdf17", "h_pdf17", 1, 0,1000);
    TH1D* h_pdf18 = new TH1D("h_pdf18", "h_pdf18", 1, 0,1000);
    TH1D* h_pdf19 = new TH1D("h_pdf19", "h_pdf19", 1, 0,1000);
    TH1D* h_pdf20 = new TH1D("h_pdf20", "h_pdf20", 1, 0,1000);
    TH1D* h_pdf21 = new TH1D("h_pdf21", "h_pdf21", 1, 0,1000);
    TH1D* h_pdf22 = new TH1D("h_pdf22", "h_pdf22", 1, 0,1000);
    TH1D* h_pdf23 = new TH1D("h_pdf23", "h_pdf23", 1, 0,1000);
    TH1D* h_pdf24 = new TH1D("h_pdf24", "h_pdf24", 1, 0,1000);
    TH1D* h_pdf25 = new TH1D("h_pdf25", "h_pdf25", 1, 0,1000);
    TH1D* h_pdf26 = new TH1D("h_pdf26", "h_pdf26", 1, 0,1000);
    TH1D* h_pdf27 = new TH1D("h_pdf27", "h_pdf27", 1, 0,1000);
    TH1D* h_pdf28 = new TH1D("h_pdf28", "h_pdf28", 1, 0,1000);
    TH1D* h_pdf29 = new TH1D("h_pdf29", "h_pdf29", 1, 0,1000);
    TH1D* h_pdf30 = new TH1D("h_pdf30", "h_pdf30", 1, 0,1000);
    TH1D* h_pdf31 = new TH1D("h_pdf31", "h_pdf31", 1, 0,1000);
    TH1D* h_pdf32 = new TH1D("h_pdf32", "h_pdf32", 1, 0,1000);
    TH1D* h_pdf33 = new TH1D("h_pdf33", "h_pdf33", 1, 0,1000);
    TH1D* h_pdf34 = new TH1D("h_pdf34", "h_pdf34", 1, 0,1000);
    TH1D* h_pdf35 = new TH1D("h_pdf35", "h_pdf35", 1, 0,1000);
    TH1D* h_pdf36 = new TH1D("h_pdf36", "h_pdf36", 1, 0,1000);
    TH1D* h_pdf37 = new TH1D("h_pdf37", "h_pdf37", 1, 0,1000);
    TH1D* h_pdf38 = new TH1D("h_pdf38", "h_pdf38", 1, 0,1000);
    TH1D* h_pdf39 = new TH1D("h_pdf39", "h_pdf39", 1, 0,1000);
    TH1D* h_pdf40 = new TH1D("h_pdf40", "h_pdf40", 1, 0,1000);
    TH1D* h_pdf41 = new TH1D("h_pdf41", "h_pdf41", 1, 0,1000);
    TH1D* h_pdf42 = new TH1D("h_pdf42", "h_pdf42", 1, 0,1000);
    TH1D* h_pdf43 = new TH1D("h_pdf43", "h_pdf43", 1, 0,1000);
    TH1D* h_pdf44 = new TH1D("h_pdf44", "h_pdf44", 1, 0,1000);
    TH1D* h_pdf45 = new TH1D("h_pdf45", "h_pdf45", 1, 0,1000);
    TH1D* h_pdf46 = new TH1D("h_pdf46", "h_pdf46", 1, 0,1000);
    TH1D* h_pdf47 = new TH1D("h_pdf47", "h_pdf47", 1, 0,1000);
    TH1D* h_pdf48 = new TH1D("h_pdf48", "h_pdf48", 1, 0,1000);
    TH1D* h_pdf49 = new TH1D("h_pdf49", "h_pdf49", 1, 0,1000);
    TH1D* h_pdf50 = new TH1D("h_pdf50", "h_pdf50", 1, 0,1000);
    TH1D* h_pdf51 = new TH1D("h_pdf51", "h_pdf51", 1, 0,1000);
    TH1D* h_pdf52 = new TH1D("h_pdf52", "h_pdf52", 1, 0,1000);
    TH1D* h_pdf53 = new TH1D("h_pdf53", "h_pdf53", 1, 0,1000);
    TH1D* h_pdf54 = new TH1D("h_pdf54", "h_pdf54", 1, 0,1000);
    TH1D* h_pdf55 = new TH1D("h_pdf55", "h_pdf55", 1, 0,1000);
    TH1D* h_pdf56 = new TH1D("h_pdf56", "h_pdf56", 1, 0,1000);
    TH1D* h_pdf57 = new TH1D("h_pdf57", "h_pdf57", 1, 0,1000);
    TH1D* h_pdf58 = new TH1D("h_pdf58", "h_pdf58", 1, 0,1000);
    TH1D* h_pdf59 = new TH1D("h_pdf59", "h_pdf59", 1, 0,1000);
    TH1D* h_pdf60 = new TH1D("h_pdf60", "h_pdf60", 1, 0,1000);
    TH1D* h_pdf61 = new TH1D("h_pdf61", "h_pdf61", 1, 0,1000);
    TH1D* h_pdf62 = new TH1D("h_pdf62", "h_pdf62", 1, 0,1000);
    TH1D* h_pdf63 = new TH1D("h_pdf63", "h_pdf63", 1, 0,1000);
    TH1D* h_pdf64 = new TH1D("h_pdf64", "h_pdf64", 1, 0,1000);
    TH1D* h_pdf65 = new TH1D("h_pdf65", "h_pdf65", 1, 0,1000);
    TH1D* h_pdf66 = new TH1D("h_pdf66", "h_pdf66", 1, 0,1000);
    TH1D* h_pdf67 = new TH1D("h_pdf67", "h_pdf67", 1, 0,1000);
    TH1D* h_pdf68 = new TH1D("h_pdf68", "h_pdf68", 1, 0,1000);
    TH1D* h_pdf69 = new TH1D("h_pdf69", "h_pdf69", 1, 0,1000);
    TH1D* h_pdf70 = new TH1D("h_pdf70", "h_pdf70", 1, 0,1000);
    TH1D* h_pdf71 = new TH1D("h_pdf71", "h_pdf71", 1, 0,1000);
    TH1D* h_pdf72 = new TH1D("h_pdf72", "h_pdf72", 1, 0,1000);
    TH1D* h_pdf73 = new TH1D("h_pdf73", "h_pdf73", 1, 0,1000);
    TH1D* h_pdf74 = new TH1D("h_pdf74", "h_pdf74", 1, 0,1000);
    TH1D* h_pdf75 = new TH1D("h_pdf75", "h_pdf75", 1, 0,1000);
    TH1D* h_pdf76 = new TH1D("h_pdf76", "h_pdf76", 1, 0,1000);
    TH1D* h_pdf77 = new TH1D("h_pdf77", "h_pdf77", 1, 0,1000);
    TH1D* h_pdf78 = new TH1D("h_pdf78", "h_pdf78", 1, 0,1000);
    TH1D* h_pdf79 = new TH1D("h_pdf79", "h_pdf79", 1, 0,1000);
    TH1D* h_pdf80 = new TH1D("h_pdf80", "h_pdf80", 1, 0,1000);
    TH1D* h_pdf81 = new TH1D("h_pdf81", "h_pdf81", 1, 0,1000);
    TH1D* h_pdf82 = new TH1D("h_pdf82", "h_pdf82", 1, 0,1000);
    TH1D* h_pdf83 = new TH1D("h_pdf83", "h_pdf83", 1, 0,1000);
    TH1D* h_pdf84 = new TH1D("h_pdf84", "h_pdf84", 1, 0,1000);
    TH1D* h_pdf85 = new TH1D("h_pdf85", "h_pdf85", 1, 0,1000);
    TH1D* h_pdf86 = new TH1D("h_pdf86", "h_pdf86", 1, 0,1000);
    TH1D* h_pdf87 = new TH1D("h_pdf87", "h_pdf87", 1, 0,1000);
    TH1D* h_pdf88 = new TH1D("h_pdf88", "h_pdf88", 1, 0,1000);
    TH1D* h_pdf89 = new TH1D("h_pdf89", "h_pdf89", 1, 0,1000);
    TH1D* h_pdf90 = new TH1D("h_pdf90", "h_pdf90", 1, 0,1000);
    TH1D* h_pdf91 = new TH1D("h_pdf91", "h_pdf91", 1, 0,1000);
    TH1D* h_pdf92 = new TH1D("h_pdf92", "h_pdf92", 1, 0,1000);
    TH1D* h_pdf93 = new TH1D("h_pdf93", "h_pdf93", 1, 0,1000);
    TH1D* h_pdf94 = new TH1D("h_pdf94", "h_pdf94", 1, 0,1000);
    TH1D* h_pdf95 = new TH1D("h_pdf95", "h_pdf95", 1, 0,1000);
    TH1D* h_pdf96 = new TH1D("h_pdf96", "h_pdf96", 1, 0,1000);
    TH1D* h_pdf97 = new TH1D("h_pdf97", "h_pdf97", 1, 0,1000);
    TH1D* h_pdf98 = new TH1D("h_pdf98", "h_pdf98", 1, 0,1000);
    TH1D* h_pdf99 = new TH1D("h_pdf99", "h_pdf99", 1, 0,1000);
    TH1D* h_pdf100 = new TH1D("h_pdf100", "h_pdf100", 1, 0,1000);

    h_pdf0->Sumw2();
    h_pdf1->Sumw2();
    h_pdf2->Sumw2();
    h_pdf3->Sumw2();
    h_pdf4->Sumw2();
    h_pdf5->Sumw2();
    h_pdf6->Sumw2();
    h_pdf7->Sumw2();
    h_pdf8->Sumw2();
    h_pdf9->Sumw2();
    h_pdf10->Sumw2();
    h_pdf11->Sumw2();
    h_pdf12->Sumw2();
    h_pdf13->Sumw2();
    h_pdf14->Sumw2();
    h_pdf15->Sumw2();
    h_pdf16->Sumw2();
    h_pdf17->Sumw2();
    h_pdf18->Sumw2();
    h_pdf19->Sumw2();
    h_pdf20->Sumw2();
    h_pdf21->Sumw2();
    h_pdf22->Sumw2();
    h_pdf23->Sumw2();
    h_pdf24->Sumw2();
    h_pdf25->Sumw2();
    h_pdf26->Sumw2();
    h_pdf27->Sumw2();
    h_pdf28->Sumw2();
    h_pdf29->Sumw2();
    h_pdf30->Sumw2();
    h_pdf31->Sumw2();
    h_pdf32->Sumw2();
    h_pdf33->Sumw2();
    h_pdf34->Sumw2();
    h_pdf35->Sumw2();
    h_pdf36->Sumw2();
    h_pdf37->Sumw2();
    h_pdf38->Sumw2();
    h_pdf39->Sumw2();
    h_pdf40->Sumw2();
    h_pdf41->Sumw2();
    h_pdf42->Sumw2();
    h_pdf43->Sumw2();
    h_pdf44->Sumw2();
    h_pdf45->Sumw2();
    h_pdf46->Sumw2();
    h_pdf47->Sumw2();
    h_pdf48->Sumw2();
    h_pdf49->Sumw2();
    h_pdf50->Sumw2();
    h_pdf51->Sumw2();
    h_pdf52->Sumw2();
    h_pdf53->Sumw2();
    h_pdf54->Sumw2();
    h_pdf55->Sumw2();
    h_pdf56->Sumw2();
    h_pdf57->Sumw2();
    h_pdf58->Sumw2();
    h_pdf59->Sumw2();
    h_pdf60->Sumw2();
    h_pdf61->Sumw2();
    h_pdf62->Sumw2();
    h_pdf63->Sumw2();
    h_pdf64->Sumw2();
    h_pdf65->Sumw2();
    h_pdf66->Sumw2();
    h_pdf67->Sumw2();
    h_pdf68->Sumw2();
    h_pdf69->Sumw2();
    h_pdf70->Sumw2();
    h_pdf71->Sumw2();
    h_pdf72->Sumw2();
    h_pdf73->Sumw2();
    h_pdf74->Sumw2();
    h_pdf75->Sumw2();
    h_pdf76->Sumw2();
    h_pdf77->Sumw2();
    h_pdf78->Sumw2();
    h_pdf79->Sumw2();
    h_pdf80->Sumw2();
    h_pdf81->Sumw2();
    h_pdf82->Sumw2();
    h_pdf83->Sumw2();
    h_pdf84->Sumw2();
    h_pdf85->Sumw2();
    h_pdf86->Sumw2();
    h_pdf87->Sumw2();
    h_pdf88->Sumw2();
    h_pdf89->Sumw2();
    h_pdf90->Sumw2();
    h_pdf91->Sumw2();
    h_pdf92->Sumw2();
    h_pdf93->Sumw2();
    h_pdf94->Sumw2();
    h_pdf95->Sumw2();
    h_pdf96->Sumw2();
    h_pdf97->Sumw2();
    h_pdf98->Sumw2();
    h_pdf99->Sumw2();
    h_pdf100->Sumw2();

    while ( (currentFile = (TFile*)fileIter.Next()) )
    {
        TFile *file = TFile::Open( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        TString filename(currentFile->GetTitle());

        tree->SetCacheSize(32*1024*1024);
        tree->SetCacheLearnEntries(100);

        nt.Init(tree);

        // Set up the NanoCORE's common configuration service tool
        gconf.GetConfigs(nt.year());

        for( unsigned int event = 0; event < tree->GetEntriesFast(); ++event)
        {

            nt.GetEntry(event);
            tree->LoadTree(event);

            nEventsTotal++;
            bar.progress(nEventsTotal, nEventsChain);

            h_pdf0->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[0]);
            h_pdf1->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[1]);
            h_pdf2->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[2]);
            h_pdf3->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[3]);
            h_pdf4->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[4]);
            h_pdf5->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[5]);
            h_pdf6->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[6]);
            h_pdf7->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[7]);
            h_pdf8->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[8]);
            h_pdf9->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[9]);
            h_pdf10->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[10]);
            h_pdf11->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[11]);
            h_pdf12->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[12]);
            h_pdf13->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[13]);
            h_pdf14->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[14]);
            h_pdf15->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[15]);
            h_pdf16->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[16]);
            h_pdf17->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[17]);
            h_pdf18->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[18]);
            h_pdf19->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[19]);
            h_pdf20->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[20]);
            h_pdf21->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[21]);
            h_pdf22->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[22]);
            h_pdf23->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[23]);
            h_pdf24->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[24]);
            h_pdf25->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[25]);
            h_pdf26->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[26]);
            h_pdf27->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[27]);
            h_pdf28->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[28]);
            h_pdf29->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[29]);
            h_pdf30->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[30]);
            h_pdf31->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[31]);
            h_pdf32->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[32]);
            h_pdf33->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[33]);
            h_pdf34->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[34]);
            h_pdf35->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[35]);
            h_pdf36->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[36]);
            h_pdf37->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[37]);
            h_pdf38->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[38]);
            h_pdf39->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[39]);
            h_pdf40->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[40]);
            h_pdf41->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[41]);
            h_pdf42->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[42]);
            h_pdf43->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[43]);
            h_pdf44->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[44]);
            h_pdf45->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[45]);
            h_pdf46->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[46]);
            h_pdf47->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[47]);
            h_pdf48->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[48]);
            h_pdf49->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[49]);
            h_pdf50->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[50]);
            h_pdf51->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[51]);
            h_pdf52->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[52]);
            h_pdf53->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[53]);
            h_pdf54->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[54]);
            h_pdf55->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[55]);
            h_pdf56->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[56]);
            h_pdf57->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[57]);
            h_pdf58->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[58]);
            h_pdf59->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[59]);
            h_pdf60->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[60]);
            h_pdf61->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[61]);
            h_pdf62->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[62]);
            h_pdf63->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[63]);
            h_pdf64->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[64]);
            h_pdf65->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[65]);
            h_pdf66->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[66]);
            h_pdf67->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[67]);
            h_pdf68->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[68]);
            h_pdf69->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[69]);
            h_pdf70->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[70]);
            h_pdf71->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[71]);
            h_pdf72->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[72]);
            h_pdf73->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[73]);
            h_pdf74->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[74]);
            h_pdf75->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[75]);
            h_pdf76->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[76]);
            h_pdf77->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[77]);
            h_pdf78->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[78]);
            h_pdf79->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[79]);
            h_pdf80->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[80]);
            h_pdf81->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[81]);
            h_pdf82->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[82]);
            h_pdf83->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[83]);
            h_pdf84->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[84]);
            h_pdf85->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[85]);
            h_pdf86->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[86]);
            h_pdf87->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[87]);
            h_pdf88->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[88]);
            h_pdf89->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[89]);
            h_pdf90->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[90]);
            h_pdf91->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[91]);
            h_pdf92->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[92]);
            h_pdf93->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[93]);
            h_pdf94->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[94]);
            h_pdf95->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[95]);
            h_pdf96->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[96]);
            h_pdf97->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[97]);
            h_pdf98->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[98]);
            h_pdf99->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[99]);
            h_pdf100->Fill(nt.MET_pt(),nt.Generator_weight()*nt.LHEPdfWeight()[100]);

            if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;
        }
        if (nevents_to_process > 0 and nEventsTotal > nevents_to_process) break;

        delete file;

    }

    cout << "central: " << h_pdf0->Integral() << endl;
    cout << "pdf1: " << h_pdf1->Integral() << "    " << h_pdf0->Integral()/h_pdf1->Integral() << endl;
    cout << "pdf2: " << h_pdf2->Integral() << "    " << h_pdf0->Integral()/h_pdf2->Integral() << endl;
    cout << "pdf3: " << h_pdf3->Integral() << "    " << h_pdf0->Integral()/h_pdf3->Integral() << endl;
    cout << "pdf4: " << h_pdf4->Integral() << "    " << h_pdf0->Integral()/h_pdf4->Integral() << endl;
    cout << "pdf5: " << h_pdf5->Integral() << "    " << h_pdf0->Integral()/h_pdf5->Integral() << endl;
    cout << "pdf6: " << h_pdf6->Integral() << "    " << h_pdf0->Integral()/h_pdf6->Integral() << endl;
    cout << "pdf7: " << h_pdf7->Integral() << "    " << h_pdf0->Integral()/h_pdf7->Integral() << endl;
    cout << "pdf8: " << h_pdf8->Integral() << "    " << h_pdf0->Integral()/h_pdf8->Integral() << endl;
    cout << "pdf9: " << h_pdf9->Integral() << "    " << h_pdf0->Integral()/h_pdf9->Integral() << endl;
    cout << "pdf10: " << h_pdf10->Integral() << "    " << h_pdf0->Integral()/h_pdf10->Integral() << endl;
    cout << "pdf11: " << h_pdf11->Integral() << "    " << h_pdf0->Integral()/h_pdf11->Integral() << endl;
    cout << "pdf12: " << h_pdf12->Integral() << "    " << h_pdf0->Integral()/h_pdf12->Integral() << endl;
    cout << "pdf13: " << h_pdf13->Integral() << "    " << h_pdf0->Integral()/h_pdf13->Integral() << endl;
    cout << "pdf14: " << h_pdf14->Integral() << "    " << h_pdf0->Integral()/h_pdf14->Integral() << endl;
    cout << "pdf15: " << h_pdf15->Integral() << "    " << h_pdf0->Integral()/h_pdf15->Integral() << endl;
    cout << "pdf16: " << h_pdf16->Integral() << "    " << h_pdf0->Integral()/h_pdf16->Integral() << endl;
    cout << "pdf17: " << h_pdf17->Integral() << "    " << h_pdf0->Integral()/h_pdf17->Integral() << endl;
    cout << "pdf18: " << h_pdf18->Integral() << "    " << h_pdf0->Integral()/h_pdf18->Integral() << endl;
    cout << "pdf19: " << h_pdf19->Integral() << "    " << h_pdf0->Integral()/h_pdf19->Integral() << endl;
    cout << "pdf20: " << h_pdf20->Integral() << "    " << h_pdf0->Integral()/h_pdf20->Integral() << endl;
    cout << "pdf21: " << h_pdf21->Integral() << "    " << h_pdf0->Integral()/h_pdf21->Integral() << endl;
    cout << "pdf22: " << h_pdf22->Integral() << "    " << h_pdf0->Integral()/h_pdf22->Integral() << endl;
    cout << "pdf23: " << h_pdf23->Integral() << "    " << h_pdf0->Integral()/h_pdf23->Integral() << endl;
    cout << "pdf24: " << h_pdf24->Integral() << "    " << h_pdf0->Integral()/h_pdf24->Integral() << endl;
    cout << "pdf25: " << h_pdf25->Integral() << "    " << h_pdf0->Integral()/h_pdf25->Integral() << endl;
    cout << "pdf26: " << h_pdf26->Integral() << "    " << h_pdf0->Integral()/h_pdf26->Integral() << endl;
    cout << "pdf27: " << h_pdf27->Integral() << "    " << h_pdf0->Integral()/h_pdf27->Integral() << endl;
    cout << "pdf28: " << h_pdf28->Integral() << "    " << h_pdf0->Integral()/h_pdf28->Integral() << endl;
    cout << "pdf29: " << h_pdf29->Integral() << "    " << h_pdf0->Integral()/h_pdf29->Integral() << endl;
    cout << "pdf30: " << h_pdf30->Integral() << "    " << h_pdf0->Integral()/h_pdf30->Integral() << endl;
    cout << "pdf31: " << h_pdf31->Integral() << "    " << h_pdf0->Integral()/h_pdf31->Integral() << endl;
    cout << "pdf32: " << h_pdf32->Integral() << "    " << h_pdf0->Integral()/h_pdf32->Integral() << endl;
    cout << "pdf33: " << h_pdf33->Integral() << "    " << h_pdf0->Integral()/h_pdf33->Integral() << endl;
    cout << "pdf34: " << h_pdf34->Integral() << "    " << h_pdf0->Integral()/h_pdf34->Integral() << endl;
    cout << "pdf35: " << h_pdf35->Integral() << "    " << h_pdf0->Integral()/h_pdf35->Integral() << endl;
    cout << "pdf36: " << h_pdf36->Integral() << "    " << h_pdf0->Integral()/h_pdf36->Integral() << endl;
    cout << "pdf37: " << h_pdf37->Integral() << "    " << h_pdf0->Integral()/h_pdf37->Integral() << endl;
    cout << "pdf38: " << h_pdf38->Integral() << "    " << h_pdf0->Integral()/h_pdf38->Integral() << endl;
    cout << "pdf39: " << h_pdf39->Integral() << "    " << h_pdf0->Integral()/h_pdf39->Integral() << endl;
    cout << "pdf40: " << h_pdf40->Integral() << "    " << h_pdf0->Integral()/h_pdf40->Integral() << endl;
    cout << "pdf41: " << h_pdf41->Integral() << "    " << h_pdf0->Integral()/h_pdf41->Integral() << endl;
    cout << "pdf42: " << h_pdf42->Integral() << "    " << h_pdf0->Integral()/h_pdf42->Integral() << endl;
    cout << "pdf43: " << h_pdf43->Integral() << "    " << h_pdf0->Integral()/h_pdf43->Integral() << endl;
    cout << "pdf44: " << h_pdf44->Integral() << "    " << h_pdf0->Integral()/h_pdf44->Integral() << endl;
    cout << "pdf45: " << h_pdf45->Integral() << "    " << h_pdf0->Integral()/h_pdf45->Integral() << endl;
    cout << "pdf46: " << h_pdf46->Integral() << "    " << h_pdf0->Integral()/h_pdf46->Integral() << endl;
    cout << "pdf47: " << h_pdf47->Integral() << "    " << h_pdf0->Integral()/h_pdf47->Integral() << endl;
    cout << "pdf48: " << h_pdf48->Integral() << "    " << h_pdf0->Integral()/h_pdf48->Integral() << endl;
    cout << "pdf49: " << h_pdf49->Integral() << "    " << h_pdf0->Integral()/h_pdf49->Integral() << endl;
    cout << "pdf50: " << h_pdf50->Integral() << "    " << h_pdf0->Integral()/h_pdf50->Integral() << endl;
    cout << "pdf51: " << h_pdf51->Integral() << "    " << h_pdf0->Integral()/h_pdf51->Integral() << endl;
    cout << "pdf52: " << h_pdf52->Integral() << "    " << h_pdf0->Integral()/h_pdf52->Integral() << endl;
    cout << "pdf53: " << h_pdf53->Integral() << "    " << h_pdf0->Integral()/h_pdf53->Integral() << endl;
    cout << "pdf54: " << h_pdf54->Integral() << "    " << h_pdf0->Integral()/h_pdf54->Integral() << endl;
    cout << "pdf55: " << h_pdf55->Integral() << "    " << h_pdf0->Integral()/h_pdf55->Integral() << endl;
    cout << "pdf56: " << h_pdf56->Integral() << "    " << h_pdf0->Integral()/h_pdf56->Integral() << endl;
    cout << "pdf57: " << h_pdf57->Integral() << "    " << h_pdf0->Integral()/h_pdf57->Integral() << endl;
    cout << "pdf58: " << h_pdf58->Integral() << "    " << h_pdf0->Integral()/h_pdf58->Integral() << endl;
    cout << "pdf59: " << h_pdf59->Integral() << "    " << h_pdf0->Integral()/h_pdf59->Integral() << endl;
    cout << "pdf60: " << h_pdf60->Integral() << "    " << h_pdf0->Integral()/h_pdf60->Integral() << endl;
    cout << "pdf61: " << h_pdf61->Integral() << "    " << h_pdf0->Integral()/h_pdf61->Integral() << endl;
    cout << "pdf62: " << h_pdf62->Integral() << "    " << h_pdf0->Integral()/h_pdf62->Integral() << endl;
    cout << "pdf63: " << h_pdf63->Integral() << "    " << h_pdf0->Integral()/h_pdf63->Integral() << endl;
    cout << "pdf64: " << h_pdf64->Integral() << "    " << h_pdf0->Integral()/h_pdf64->Integral() << endl;
    cout << "pdf65: " << h_pdf65->Integral() << "    " << h_pdf0->Integral()/h_pdf65->Integral() << endl;
    cout << "pdf66: " << h_pdf66->Integral() << "    " << h_pdf0->Integral()/h_pdf66->Integral() << endl;
    cout << "pdf67: " << h_pdf67->Integral() << "    " << h_pdf0->Integral()/h_pdf67->Integral() << endl;
    cout << "pdf68: " << h_pdf68->Integral() << "    " << h_pdf0->Integral()/h_pdf68->Integral() << endl;
    cout << "pdf69: " << h_pdf69->Integral() << "    " << h_pdf0->Integral()/h_pdf69->Integral() << endl;
    cout << "pdf70: " << h_pdf70->Integral() << "    " << h_pdf0->Integral()/h_pdf70->Integral() << endl;
    cout << "pdf71: " << h_pdf71->Integral() << "    " << h_pdf0->Integral()/h_pdf71->Integral() << endl;
    cout << "pdf72: " << h_pdf72->Integral() << "    " << h_pdf0->Integral()/h_pdf72->Integral() << endl;
    cout << "pdf73: " << h_pdf73->Integral() << "    " << h_pdf0->Integral()/h_pdf73->Integral() << endl;
    cout << "pdf74: " << h_pdf74->Integral() << "    " << h_pdf0->Integral()/h_pdf74->Integral() << endl;
    cout << "pdf75: " << h_pdf75->Integral() << "    " << h_pdf0->Integral()/h_pdf75->Integral() << endl;
    cout << "pdf76: " << h_pdf76->Integral() << "    " << h_pdf0->Integral()/h_pdf76->Integral() << endl;
    cout << "pdf77: " << h_pdf77->Integral() << "    " << h_pdf0->Integral()/h_pdf77->Integral() << endl;
    cout << "pdf78: " << h_pdf78->Integral() << "    " << h_pdf0->Integral()/h_pdf78->Integral() << endl;
    cout << "pdf79: " << h_pdf79->Integral() << "    " << h_pdf0->Integral()/h_pdf79->Integral() << endl;
    cout << "pdf80: " << h_pdf80->Integral() << "    " << h_pdf0->Integral()/h_pdf80->Integral() << endl;
    cout << "pdf81: " << h_pdf81->Integral() << "    " << h_pdf0->Integral()/h_pdf81->Integral() << endl;
    cout << "pdf82: " << h_pdf82->Integral() << "    " << h_pdf0->Integral()/h_pdf82->Integral() << endl;
    cout << "pdf83: " << h_pdf83->Integral() << "    " << h_pdf0->Integral()/h_pdf83->Integral() << endl;
    cout << "pdf84: " << h_pdf84->Integral() << "    " << h_pdf0->Integral()/h_pdf84->Integral() << endl;
    cout << "pdf85: " << h_pdf85->Integral() << "    " << h_pdf0->Integral()/h_pdf85->Integral() << endl;
    cout << "pdf86: " << h_pdf86->Integral() << "    " << h_pdf0->Integral()/h_pdf86->Integral() << endl;
    cout << "pdf87: " << h_pdf87->Integral() << "    " << h_pdf0->Integral()/h_pdf87->Integral() << endl;
    cout << "pdf88: " << h_pdf88->Integral() << "    " << h_pdf0->Integral()/h_pdf88->Integral() << endl;
    cout << "pdf89: " << h_pdf89->Integral() << "    " << h_pdf0->Integral()/h_pdf89->Integral() << endl;
    cout << "pdf90: " << h_pdf90->Integral() << "    " << h_pdf0->Integral()/h_pdf90->Integral() << endl;
    cout << "pdf91: " << h_pdf91->Integral() << "    " << h_pdf0->Integral()/h_pdf91->Integral() << endl;
    cout << "pdf92: " << h_pdf92->Integral() << "    " << h_pdf0->Integral()/h_pdf92->Integral() << endl;
    cout << "pdf93: " << h_pdf93->Integral() << "    " << h_pdf0->Integral()/h_pdf93->Integral() << endl;
    cout << "pdf94: " << h_pdf94->Integral() << "    " << h_pdf0->Integral()/h_pdf94->Integral() << endl;
    cout << "pdf95: " << h_pdf95->Integral() << "    " << h_pdf0->Integral()/h_pdf95->Integral() << endl;
    cout << "pdf96: " << h_pdf96->Integral() << "    " << h_pdf0->Integral()/h_pdf96->Integral() << endl;
    cout << "pdf97: " << h_pdf97->Integral() << "    " << h_pdf0->Integral()/h_pdf97->Integral() << endl;
    cout << "pdf98: " << h_pdf98->Integral() << "    " << h_pdf0->Integral()/h_pdf98->Integral() << endl;
    cout << "pdf99: " << h_pdf99->Integral() << "    " << h_pdf0->Integral()/h_pdf99->Integral() << endl;
    cout << "pdf100: " << h_pdf100->Integral() << "    " << h_pdf0->Integral()/h_pdf100->Integral() << endl;


    // scale_output->cd();
    // h_scale0->Write();
    // h_scale1->Write();
    // h_scale2->Write();
    // h_scale3->Write();
    // h_scale4->Write();
    // h_scale5->Write();
    // h_scale6->Write();

    // scale_output->Close();

    bar.finish();

    return 0;
}
