# FCNCAnalysis

This is a repo for FCNC analysis. 

# Setup 
## One time only
First, fork this repo to your own repository. You can do this by clicking the "fork" button at the top right corner of this page.

In your terminal, run the following command. Please be sure to change YOURGITUSERNAME to the appropriate value.

git clone https://github.com/YOURGITUSERNAME/FCNCAnalysis.git


It is also necessary to setup a CMS environment before you can run the code. It was developed using CMSSW_10_2_9, but should work with most releases. To set up a CMSSW release:

From your home directory, run

cmsrel CMSSW_10_2_9

## Each time you log in
To set up the CMS environment:

cd CMSSW_10_2_9/src
cmsenv

Code for this iteration of the analysis is in the FCNCAnalysis/analysis directory:

cd ~/FCNCAnalysis/analysis

## Once per baby cycle
The first time you run anything, you will first need to run

python eventCounter.py

This will produce an n_events directory which contains information for calculating event weights. This command only needs to be run once per cycle of babies.

# Compilation and Running

Run and compile the event looper with

root -l event_looper.C+
