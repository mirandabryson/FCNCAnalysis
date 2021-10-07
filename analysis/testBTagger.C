#pragma GCC diagnostic ignored "-Wsign-compare"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THn.h"
#include "TTree.h"
// #include "TChain.h"
#include "TTreeCache.h"
#include "TTreeCacheUnzip.h"
#include "TTreePerfStats.h"
#include "../../NanoTools/NanoCORE/Tools/btagsf/BTagCalibrationStandalone.h"
#include "../../NanoTools/NanoCORE/Tools/btagsf/BTagCalibrationStandalone.cc"


// #include "../../NanoTools/NanoCORE/Nano.h"
// #include "../../NanoTools/NanoCORE/MetSelections.h"
// #include "../../NanoTools/NanoCORE/Tools/JetCorrector.h"
// #include "../../NanoTools/NanoCORE/tqdm.h"
// #include "../../NanoTools/NanoCORE/Config.h"
// #include "../../NanoTools/NanoCORE/SSSelections.h"

#include <iostream>
#include <iomanip>

// #define DEBUG

// struct debugger { template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; } } dbg;
// #ifdef DEBUG
//     #define debug(args...) do {cerr << #args << ": "; dbg,args; cerr << endl;} while(0)
// #else
//     #define debug(args...)
// #endif

using namespace std;
using namespace std::chrono;

int test()
{
    cout << "in function" << endl;
    auto start = high_resolution_clock::now();

    //csv paths
    string csv_path_2016 = "../../NanoTools/NanoCORE/Tools/btagsf/csv/DeepJet_2016LegacySF_V1.csv";
    string csv_path_2017 = "../../NanoTools/NanoCORE/Tools/btagsf/csv/DeepJet_94XSF_V4_B_F.csv";
    string csv_path_2018 = "../../NanoTools/NanoCORE/Tools/btagsf/csv/DeepJet_102XSF_V3.csv";

    cout << "defined paths to csv files " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << " seconds" << endl;

    // TFile* inputFile = new TFile(csv_path_2016.Data());

    // CSV objects
    BTagCalibration deepjet_csv_2016 = BTagCalibration("csvv1", csv_path_2016);
    cout << "loaded btag calibration " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << " seconds" << endl;
    
    //BTagCalibrationReader deepjet_medium_reader_2016 = BTagCalibrationReader(BTagEntry::OP_RESHAPING,
    //    "central",
    //    {"up_lf","down_lf",
    //    "up_hf","down_hf",
    //    "up_hfstats1","down_hfstats1",
    //    "up_hfstats2","down_hfstats2",
    //    "up_lfstats1","down_lfstats1",
    //    "up_lfstats2","down_lfstats2",
    //    "up_cferr1","down_cferr1",
    //    "up_cferr2","down_cferr2"}
    //    );
    // BTagCalibrationReader up_reader_2016 = BTagCalibrationReader(BTagEntry::OP_RESHAPING, "up");
    // BTagCalibrationReader down_reader_2016 = BTagCalibrationReader(BTagEntry::OP_RESHAPING, "down");
    //cout << "made central, up, and down readers " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << " seconds" << endl;
    
    //deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_B, "iterativefit");
    //cout << "got iterativefit for b " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << " seconds" << endl;
    
    //deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_C, "iterativefit");
    //cout << "got iterativefit for c " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << " seconds" << endl;
    
    //deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_UDSG, "iterativefit");
    //cout << "got iterativefit for light " << duration_cast<seconds>(high_resolution_clock::now() - start).count() << " seconds" << endl;

    // BTagCalibration deepjet_csv_2017 = BTagCalibration("csvv1", csv_path_2017);
    // BTagCalibration deepjet_csv_2018 = BTagCalibration("csvv1", csv_path_2018);
    // Medium reader
    // BTagCalibrationReader deepjet_medium_reader_2016 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
    // BTagCalibrationReader deepjet_medium_reader_2017 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
    // BTagCalibrationReader deepjet_medium_reader_2018 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "central");
    //up
    // BTagCalibrationReader up_reader_2016 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up");
    // BTagCalibrationReader up_reader_2017 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up");
    // BTagCalibrationReader up_reader_2018 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "up");
    //down
    // BTagCalibrationReader down_reader_2016 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down");
    // BTagCalibrationReader down_reader_2017 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down");
    // BTagCalibrationReader down_reader_2018 = BTagCalibrationReader(BTagEntry::OP_MEDIUM, "down");
    //central
    // deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_B, "comb");
    // deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_C, "comb");
    // deepjet_medium_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_UDSG, "incl");
    // deepjet_medium_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_B, "comb");
    // deepjet_medium_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_C, "comb");
    // deepjet_medium_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_UDSG, "incl");
    // deepjet_medium_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_B, "comb");
    // deepjet_medium_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_C, "comb");
    // deepjet_medium_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_UDSG, "incl");
    //up
    // up_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_B, "comb");
    // up_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_C, "comb");
    // up_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_UDSG, "incl");
    // up_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_B, "comb");
    // up_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_C, "comb");
    // up_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_UDSG, "incl");
    // up_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_B, "comb");
    // up_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_C, "comb");
    // up_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_UDSG, "incl");
    //down
    // down_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_B, "comb");
    // down_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_C, "comb");
    // down_reader_2016.load(deepjet_csv_2016, BTagEntry::FLAV_UDSG, "incl");
    // down_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_B, "comb");
    // down_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_C, "comb");
    // down_reader_2017.load(deepjet_csv_2017, BTagEntry::FLAV_UDSG, "incl");
    // down_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_B, "comb");
    // down_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_C, "comb");
    // down_reader_2018.load(deepjet_csv_2018, BTagEntry::FLAV_UDSG, "incl");

    return 0;
}
