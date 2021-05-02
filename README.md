# FCNCAnalysis
mkdir fcnc <br>
cd fcnc <br>
git clone https://github.com/fgolf/FCNCAnalysis.git ana <br>
git clone https://github.com/fgolf/NanoTools.git <br>
pushd . <br>
cd NanoTools/NanoCORE <br>
make -j8 <br>
popd <br>

## build histogrammingClass.C
pushd ana/analysis/helpers <br>
root -b <br>
gROOT->ProcessLine(".L ../../../NanoTools/NanoCORE/NANO_CORE.so"); <br>
.L histogrammingClass.C++ <br>

## checkout plotting tools
popd <br>
pushd ana <br>
git clone https://github.com/aminnj/matplottery.git <br>
popd <br>

## build event looper
pushd ana/analysis <br>
root -b <br>
gROOT->ProcessLine(".L ../../NanoTools/NanoCORE/NANO_CORE.so"); <br>
gROOT->ProcessLine(".L  helpers/histogrammingClass_C.so"); <br>
.L event_looper.C++; <br>
event_looper()
