# FCNCAnalysis
git clone https://github.com/fgolf/FCNCAnalysis.git
git clone https://github.com/fgolf/NanoTools.git
pushd .
cd NanoTools/NanoCORE
make -j8
popd
cd FCNCAnalysis/analysis/helpers

## build histogrammingClass.C
root -b
gROOT->ProcessLine(".L ../../../NanoTools/NanoCORE/libNANO_CORE.so");
.L histogrammingClass.C++
cd ..

## build event looper
root -b
gROOT->ProcessLine(".L ../../NanoTools/NanoCORE/libNANO_CORE.so");
gROOT->ProcessLine(".L  helpers/histogrammingClass_C.so");
.L event_looper.C++;
event_looper()
