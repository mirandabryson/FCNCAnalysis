#!/bin/bash
##
## checkout and build tools and core for nano
##
CURRENT_DIR=`pwd`
pushd ../
git clone https://github.com/fgolf/NanoTools.git 
pushd NanoTools/NanoCORE 
make -j8 
echo $?
popd 
##
## checkout and build histogramming tools
##
pushd current/analysis/helpers 
root -b -l -q compile.C
#gROOT->ProcessLine(".L ../../../NanoTools/NanoCORE/NANO_CORE.so"); 
#.L histogrammingClass.C++ 
echo $?
popd
##
## checkout plotting tools
##
pushd ana 
git clone https://github.com/aminnj/matplottery.git 
popd 
##
## checkout and build analysis looper
##
pushd ana/analysis
root -b -l -q compile.C
#gROOT->ProcessLine(".L ../../NanoTools/NanoCORE/NANO_CORE.so");
#gROOT->ProcessLine(".L  helpers/histogrammingClass_C.so");
#.L event_looper.C++;
#event_looper()


