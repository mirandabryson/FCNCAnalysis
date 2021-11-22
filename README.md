# FCNCAnalysis
mkdir fcnc <br>
cd fcnc <br>
git clone https://github.com/ksalyer/FCNCAnalysis.git ana <br>
cd FCNCAnalysis <br>
git checkout franksFork <br>
cd .. <br>
git clone https://github.com/ksalyer/NanoTools.git <br>
pushd . <br>
cd NanoTools/NanoCORE <br>
make -j8 <br>
popd <br>

## build histogrammingClass.C
pushd ana/analysis/helpers <br>
root -b <br>
gROOT->ProcessLine(".L ../../../NanoTools/NanoCORE/NANO_CORE.so"); <br>
.L histogrammingClass.C++ <br>
popd <br>

## checkout plotting tools
pushd ana <br>
git clone https://github.com/aminnj/matplottery.git <br>
popd <br>

## build analysis looper
pushd ana/analysis <br>
root -b <br>
gROOT->ProcessLine(".L ../../NanoTools/NanoCORE/NANO_CORE.so"); <br>
gROOT->ProcessLine(".L  helpers/histogrammingClass_C.so"); <br>
.L event_looper.C++; <br>
event_looper()
