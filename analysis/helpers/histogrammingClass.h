#ifndef HISTCONTAINER_H
#define HISTCONTAINER_H

#include <string>
#include <map>
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THn.h"
#include "../../../NanoTools/NanoCORE/SSSelections.h"

class HistContainer {
    private:
        std::map<std::string, TH1D*> hists1d_;
        std::map<std::string, TH2D*> hists2d_;
        std::map<std::string, THnF*> hists4d_;
        std::vector<std::string> region_names_;
        // std::vector<double> hct2016bins_ = {0.00839096,0.16095828,0.23802076,0.30112872,0.35890686,0.40959004,
        //                                     0.45495006,0.49485105,0.53074064,0.56373581,0.59406344,0.62193093,
        //                                     0.64864195,0.67240337,0.6958896,0.71846887,0.74127835,0.76474518,
        //                                     0.78961158,0.81917407,0.92583752};
        // std::vector<double> hct2017bins_ = {0.01013761,0.18080988,0.27036899,0.34500748,0.40774285,0.46201145,
        //                                     0.50705061,0.54527005,0.57897817,0.60883559,0.63570691,0.66000933,
        //                                     0.68395044,0.70614237,0.72753026,0.74750743,0.76703324,0.78730723,
        //                                     0.80854434,0.83436951,0.92419791};
        // std::vector<double> hct2018bins_ = {0.00937267,0.1632299,0.24426998,0.31511358,0.37514869,0.42607699,
        //                                     0.47091385,0.51076036,0.54663701,0.57872597,0.60745003,0.63452662,
        //                                     0.65994499,0.68366876,0.7062431,0.72843404,0.74939677,0.77196604,
        //                                     0.79586817,0.82420313,0.9239592};
        // std::vector<double> hut2016bins_ = {0.00914403,0.20008836,0.27453927,0.33164128,0.38055728,0.4258715,
        //                                     0.46638051,0.50288993,0.53577262,0.56536055,0.59404119,0.62042599,
        //                                     0.64466459,0.66833612,0.69075725,0.71255371,0.73426142,0.75719679,
        //                                     0.78224732,0.8122123,0.89962864};
        // std::vector<double> hut2017bins_ = {0.01574082,0.20710103,0.28442863,0.34716104,0.4023868,0.45219769,
        //                                     0.49497075,0.53230496,0.56584992,0.59485136,0.62249219,0.64754287,
        //                                     0.67023137,0.69125564,0.7117676,0.73215165,0.75223584,0.77343385,
        //                                     0.79599154,0.82391778,0.92128563};
        // std::vector<double> hut2018bins_ = {0.00764989,0.19898085,0.27207563,0.33240259,0.3853653,0.43188411,
        //                                     0.47348394,0.51067675,0.54408779,0.57346128,0.60102867,0.62634416,
        //                                     0.65081933,0.6734813,0.69579156,0.71761551,0.7386871,0.76130227,
        //                                     0.78572424,0.81636845,0.91659641};

        std::vector<double> hct2016bins_ = {0.00664381,0.19700572,0.28762238,0.35702177,0.41852485,0.46981504,
                                            0.5140483,0.55344284,0.5878852,0.61896108,0.64749079,0.67274341,
                                            0.69721056,0.71897993,0.74007495,0.7596258,0.77943377,0.80007322,
                                            0.82212229,0.84957791,0.95174003};
        std::vector<double> hct2017bins_ = {0.00315058,0.19431175,0.29736627,0.37752346,0.44127761,0.49327968,
                                            0.53875172,0.57723496,0.61170031,0.64185643,0.66889886,0.6938042,
                                            0.71576739,0.73608911,0.75571284,0.77392217,0.79224801,0.81161177,
                                            0.83241789,0.85775793,0.95619053};
        std::vector<double> hct2018bins_ = {0.00479198,0.17966878,0.27458878,0.35070238,0.41352009,0.46567807,
                                            0.51136807,0.55213587,0.58714796,0.61819961,0.64662389,0.67340356,
                                            0.69772793,0.7197811,0.74084001,0.76107035,0.78023184,0.80087946,
                                            0.82352064,0.85020101,0.95095789};
        std::vector<double> hut2016bins_ = {0.00736403,0.21426591,0.29383466,0.35855735,0.41314251,0.45857105,
                                            0.49965322,0.53653497,0.56925915,0.59906112,0.62709959,0.6521008,
                                            0.67643466,0.69947938,0.72162078,0.7430641,0.76410061,0.78568389,
                                            0.80855299,0.83609562,0.93626601};
        std::vector<double> hut2017bins_ = {0.01559662,0.22217794,0.3075743,0.37751087,0.43626528,0.48550959,
                                            0.52909791,0.56672765,0.60022287,0.62953208,0.6559299,0.68061894,
                                            0.70287784,0.72394461,0.74388685,0.7637161,0.7830119,0.80281474,
                                            0.82358046,0.84841615,0.95985132};
        std::vector<double> hut2018bins_ = {0.00556834,0.20800883,0.29165759,0.3579802,0.41477358,0.46250958,
                                            0.50522264,0.542203,0.57576577,0.60614129,0.63435366,0.65923017,
                                            0.68383075,0.70642107,0.72871006,0.74944134,0.77037494,0.79134813,
                                            0.81379657,0.84081843,0.95217699};
                                            
        std::vector<std::string> getRegionNames();
        std::string getRegionName(int hyp_type, int njets, int  nbjets);
        int getSR(int hyp_type, int njets, int nbjets);
        int getCRbin(int nleps, int njets, int nbjets);
        int getEtaBin(float lep_eta, int lep_id);
        std::vector<int> getDoubleFakeBin(float lep1_pt, float lep1_eta, int lep1_id, float lep2_pt, float lep2_eta, int lep2_id);
        std::vector<int> getDoubleFlipBin(float lep1_pt, float lep1_eta, float lep2_pt, float lep2_eta);
        int counter_;
    public:
        HistContainer () : counter_(0) {region_names_=getRegionNames();}
        void addHist1d(std::string quantity, std::string sample, int nbins, float min, float max, std::string region="");
        void addHist1d(std::string quantity, std::string sample, int nbins, std::vector<double> xbins, std::string region="");
        void addHist2d(std::string quantity, std::string sample, int nbinsx, float xmin, float xmax, int nbinsy, float ymin, float ymax, std::string region="");
        void addHist2d(std::string quantity, std::string sample, int nbinsx, int nbinsy, std::vector<float> xbins, std::vector<float> ybins, std::string region="");
        void addHist4d(std::string quantity, std::string sample, int nbinsx, int nbinsy, std::vector<double> xedges, std::vector<double> yedges, std::string region="");
        void loadHists(std::string sample);
        void sumw2();
        void write();
        void fill1d(std::string quantity, std::string region, std::string sample, float value, float weight=1.);
        void fill2d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float weight=1.);
        void fill4d(std::string quantity, std::string region, std::string sample, float xvalue, float yvalue, float zvalue, float tvalue, float weight=1.);
        void fill(std::string sample, int best_hyp_type, Leptons &leps, Jets &jets, Jets &bjets, 
                float met, float metphi, bool isVR_SR_fake, bool isVR_CR_fake, bool isVR_SR_flip, bool isVR_CR_flip, 
                bool isEE, bool isEM, bool isME, bool isMM, bool isEFake, bool isMFake, bool isEE_flip, 
                bool isEM_flip, float hct_pred=-999, float hut_pred=-999, float weight=1., float crWeight=1.,
                bool doVariations=0, std::map<std::string, float> variationMap = {{"null", 0.}});
};

#endif