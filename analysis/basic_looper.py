import ROOT
import time


# Load ntuples
chain = ROOT.TChain("Events")
chain.Add("/home/users/ksalyer/SSValBabies/nano/ttbar_semileptonic_RunIISummer16NanoAODv7_0.root")

print("loaded files")

# useful functions

# main loop
"""branches = chain.GetListOfBranches()
for b in branches:
    bname = b.GetName()
    if bname.count("Muon_")>0:
        print bname"""

nEvents = chain.GetEntries()
print("found {0} events".format(nEvents))
counter = 0
start_time = time.time()

nTriLep   = 0
nSSDiLep  = 0
nOSDiLep  = 0
nOneLepFO = 0
nFODiLep  = 0

for event in chain:
    nMuon     = event.nMuon
    muCharge  = event.Muon_charge
    muPt      = event.Muon_pt
    muEta     = event.Muon_eta
    muTight   = event.Muon_tightId
    muLoose   = event.Muon_looseId
    muMiniIso_all = event.Muon_miniPFRelIso_all
    muMiniIso_chg = event.Muon_miniPFRelIso_chg
    muRelIso03_all = event.Muon_pfRelIso03_all
    muRelIso03_chg = event.Muon_pfRelIso03_chg
    muRelIso04_all = event.Muon_pfRelIso04_all


    nElectron = event.nElectron
    elCharge  = event.Electron_charge
    elPt      = event.Electron_pt
    elEta     = event.Electron_eta
    #elTight   = event.Electron_tightId
    elMiniIso_all = event.Electron_miniPFRelIso_all
    elMiniIso_chg = event.Electron_miniPFRelIso_chg
    elRelIso03_all = event.Electron_pfRelIso03_all
    elRelIso03_chg = event.Electron_pfRelIso03_chg
    #elRelIso04_all = event.Electron_pfRelIso04_all

    nGoodLep        = 0
    nFakeableLep    = 0
    muIdx_tight     = []
    elIdx_tight     = []
    muIdx_loose     = []
    elIdx_loose     = []

    for mu in range(nMuon):
        if muPt[mu]>20 and muEta[mu]<2.4 and muTight[mu]==1 and muMiniIso_all[mu] < 0.12:
            nGoodLep += 1
            muIdx_tight.append(mu)
        elif muPt[mu]>20 and muEta[mu]<2.4 and muLoose[mu]==1 and muMiniIso_all[mu] > 0.12 and muMiniIso_all[mu] < 0.15:
            nFakeableLep += 1
            muIdx_loose.append(mu)
        else: continue
    for el in range(nElectron):
        if elPt[el]>25 and elEta[el]<2.4 and elMiniIso_all[el] < 0.15: #and elTight==1:
            nGoodLep+= 1
            elIdx_tight.append(el)
        elif elPt[el]>25 and elEta[el]<2.4 and elMiniIso_all[el] > 0.15 and elMiniIso_all[el] < 0.18:# and elLoose==1:
            nFakeableLep += 1
            elIdx_loose.append(el)
        else: continue
    
    if nGoodLep == 3:
        nTriLep += 1
    
    if nGoodLep == 2:
        if len(muIdx_tight) == 2:
            if muCharge[muIdx_tight[0]]*muCharge[muIdx_tight[1]]>0:
                nSSDiLep += 1
            else: 
                nOSDiLep += 1
        elif len(elIdx_tight) == 2:
            if elCharge[elIdx_tight[0]]*elCharge[elIdx_tight[1]]>0:
                nSSDiLep += 1
            else:
                nOSDiLep += 1
        elif len(muIdx_tight) == 1:
            if muCharge[muIdx_tight[0]]*elCharge[elIdx_tight[0]]>0:
                nSSDiLep += 1
            else:
                nOSDiLep += 1

    if nGoodLep == 1 and nFakeableLep == 1:
        nOneLepFO += 1

    if nFakeableLep == 2:
        nFODiLep += 1
    
    counter += 1
    if counter % 10000 == 0:
        print("done {0} events of {1}".format(counter,nEvents))
    current_time = time.time()

print("TriLep: {0}".format(nTriLep))
print("SS DiLep: {0}".format(nSSDiLep))
print("OS DiLep: {0}".format(nOSDiLep))
print("One Lep with FO: {0}".format(nOneLepFO))
print("FO DiLep: {0}".format(nFODiLep))
print("total filtered: {0}".format(nTriLep+nSSDiLep+nOSDiLep))

print("processed {0} events in {1} minutes".format(nEvents,(current_time-start_time)/60))
