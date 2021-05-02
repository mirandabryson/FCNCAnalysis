# FCNCAnalysis
mkdir fcnc
cd fcnc
git clone https://github.com/fgolf/FCNCAnalysis.git current
git clone https://github.com/fgolf/NanoTools.git
pushd .
cd NanoTools/NanoCORE
make -j8
popd

## build histogrammingClass.C
pushd current/analysis/helpers
root -b
gROOT->ProcessLine(".L ../../../NanoTools/NanoCORE/NANO_CORE.so");
.L histogrammingClass.C++

## checkout plotting tools
popd
pushd current
git clone https://github.com/aminnj/matplottery.git
popd

## build event looper
pushd current/analysis
root -b
gROOT->ProcessLine(".L ../../NanoTools/NanoCORE/NANO_CORE.so");
gROOT->ProcessLine(".L  helpers/histogrammingClass_C.so");
.L event_looper.C++;
event_looper()
