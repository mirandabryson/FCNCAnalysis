{
    gSystem->SetAclicMode(TSystem::kDebug);
    gROOT->ProcessLine(".L ../../NanoTools/NanoCORE/NANO_CORE.so");
    gROOT->ProcessLine(".L helpers/histogrammingClass.C+");
    gROOT->ProcessLine(".L event_looper.C+");
    TString sample_path = "/nfs-7/userdata/ksalyer/fcnc/fcnc_v6_SRonly_5may2021/2018/ttjets.root";
    TChain *chain = new TChain("Events");
    chain->Add(sample_path.Data());
    chain->SetTitle("ttjets");
    TString options="Data2018 printDebugFile ";
    event_looper(chain,options,10);
}
