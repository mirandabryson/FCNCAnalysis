import ROOT
import time
import numpy as np


# Load ntuples
chain = ROOT.TChain("Events")
chain.Add("/home/users/ksalyer/SSValBabies/nano/ttbar_semileptonic_RunIISummer16NanoAODv7_0.root")

print("loaded files")

# useful functions
def deltaR(obj1_eta, obj1_phi, obj2_eta, obj2_phi):
    deltaEta = obj1_eta - obj2_eta
    deltaPhi = obj1_phi - obj2_phi
    
    deltaR = np.sqrt((deltaEta)**2 + (deltaPhi)**2)
    return deltaR

def isTightLepton(event, pdgid, idx):
    if abs(pdgid) == 11:
        pt          = event.Electron_pt[idx]
        eta         = event.Electron_eta[idx]
        miniIso_all = event.Electron_miniPFRelIso_all[idx]
    if abs(pdgid) == 13:
        pt          = event.Muon_pt[idx]
        eta         = event.Muon_eta[idx]
        miniIso_all = event.Muon_miniPFRelIso_all[idx]
        tight_id    = event.Muon_tightId[idx]

    if abs(eta)<2.4:
        if pdgid==11 and pt>25 and miniIso_all < 0.12:
            return True
        elif pdgid==13 and pt>20 and tight_id == 1 and miniIso_all < 0.16:
            return True
        else: return False
    else: return False

def isLooseLepton(event, pdgid, idx):
    if abs(pdgid) == 11:
        pt          = event.Electron_pt[idx]
        eta         = event.Electron_eta[idx]
        miniIso_all = event.Electron_miniPFRelIso_all[idx]
    if abs(pdgid) == 13:
        pt          = event.Muon_pt[idx]
        eta         = event.Muon_eta[idx]
        miniIso_all = event.Muon_miniPFRelIso_all[idx]
        loose_id    = event.Muon_looseId[idx]

    if abs(eta)<2.4:
        if pdgid==11 and pt>25 and miniIso_all > 0.12 and miniIso_all < 0.4:
            return True
        elif pdgid==13 and pt>20 and loose_id == 1 and miniIso_all > 0.12 and miniIso_all < 0.4:
            return True
        else: return False
    else: return False

def isGoodJet(event, idx):
    pt  = event.Jet_pt[idx]
    eta = event.Jet_eta[idx]

    #deltaR = 0.0
    
    if pt > 25 and abs(eta) < 2.4:
        for muon in range(event.nMuon):
            if isTightLepton(event, 13, muon) or isLooseLepton(event, 13, muon):
                #deltaR = deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Muon_eta[muon], event.Muon_phi[muon] )
                if deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Muon_eta[muon], event.Muon_phi[muon] ) < 0.4:
                    return False
                #if deltaR < 0.4:
                #    return False
                else: continue
            else: continue
        for electron in range(event.nElectron):
            if isTightLepton(event, 11, electron) or isLooseLepton(event, 11, electron):
                #deltaR = deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Electron_eta[electron], event.Electron_phi[electron] )
                if deltaR( event.Jet_eta[idx], event.Jet_phi[idx], event.Electron_eta[electron], event.Electron_phi[electron] ) < 0.4:
                    return False
                #if deltaR < 0.4:
                    #return False
                else: continue
            else: continue
        return True
    else: return False
   
def saveFig(hist, hist_name, outdir):
    can = ROOT.TCanvas( "c_"+hist_name, "canvas", 800, 800 )

    pad1 = ROOT.TPad( "pad1", "pad1", 0, 0.3, 1, 1.0 )
    pad1.Draw()

    pad1.cd()
    hist.Draw()

    can.SaveAs(outdir+hist_name+".pdf")
    can.SaveAs(outdir+hist_name+".png")

# main loop
'''branches = chain.GetListOfBranches()
for b in branches:
    bname = b.GetName()
    if bname.count("Jet")>0:
        print bname'''

nEvents = chain.GetEntries()
print("found {0} events".format(nEvents))
counter = 0
h_nJet_trilep   = ROOT.TH1D("h_nJet_trilep",   "nJets", 7, -0.5, 6.5)
h_nJet_SSdilep  = ROOT.TH1D("h_nJet_SSdilep",  "nJets", 7, -0.5, 6.5)
h_nJet_OSdilep  = ROOT.TH1D("h_nJet_OSdilep",  "nJets", 7, -0.5, 6.5)
h_nJet_onelepFO = ROOT.TH1D("h_nJet_onelepFO", "nJets", 7, -0.5, 6.5)
h_nJet_dilepFO  = ROOT.TH1D("h_nJet_dilepFO",  "nJets", 7, -0.5, 6.5)

h_nBJet_trilep   = ROOT.TH1D("h_nBJet_trilep",   "nb-tagged Jets", 4, -0.5, 3.5)
h_nBJet_SSdilep  = ROOT.TH1D("h_nBJet_SSdilep",  "nb-tagged Jets", 4, -0.5, 3.5)
h_nBJet_OSdilep  = ROOT.TH1D("h_nBJet_OSdilep",  "nb-tagged Jets", 4, -0.5, 3.5)
h_nBJet_onelepFO = ROOT.TH1D("h_nBJet_onelepFO", "nb-tagged Jets", 4, -0.5, 3.5)
h_nBJet_dilepFO  = ROOT.TH1D("h_nBJet_dilepFO",  "nb-tagged Jets", 4, -0.5, 3.5)

print("defined histograms")

start_time = time.time()

nTriLep   = 0
nSSDiLep  = 0
nOSDiLep  = 0
nOneLepFO = 0
nFODiLep  = 0

for event in chain:
    nMuon     = event.nMuon
    muCharge  = event.Muon_charge

    nElectron = event.nElectron
    elCharge  = event.Electron_charge

    njets = event.nJet
    #jetPDGID = event.Jet_partonFlavour
    btag_score = event.Jet_btagDeepFlavB
    jet_pt = event.Jet_pt
    jet_eta = event.Jet_eta

    nBjets          = 0
    nJets           = 0
    nGoodLep        = 0
    nFakeableLep    = 0

    muIdx_tight     = []
    elIdx_tight     = []
    muIdx_loose     = []
    elIdx_loose     = []

    for jet in range(njets):
        if isGoodJet(event, jet):
        #if jet_pt[jet] > 40 and abs(jet_eta[jet]) < 2.4:
            nJets += 1
            if btag_score[jet] > 0.2770:
                nBjets += 1
            else: continue
        else: continue
    
    if nJets>1 and nBjets>=0:

        for mu in range(nMuon):
            if isTightLepton(event, 13, mu):
                nGoodLep += 1
                muIdx_tight.append(mu)
            elif isLooseLepton(event, 13, mu):
                nFakeableLep += 1
                muIdx_loose.append(mu)
            else: continue
        for el in range(nElectron):
            if isTightLepton(event, 11, el):
                nGoodLep+= 1
                elIdx_tight.append(el)
            elif isLooseLepton(event, 11, el):
                nFakeableLep += 1
                elIdx_loose.append(el)
            else: continue
    
    if nGoodLep == 3:
        nTriLep += 1
        h_nJet_trilep.Fill(nJets)
        h_nBJet_trilep.Fill(nBjets)
    
    if nGoodLep == 2:
        if len(muIdx_tight) == 2:
            if muCharge[muIdx_tight[0]]*muCharge[muIdx_tight[1]]>0:
                nSSDiLep += 1
                h_nJet_SSdilep.Fill(nJets)
                h_nBJet_SSdilep.Fill(nBjets)
            else: 
                nOSDiLep += 1
                h_nJet_OSdilep.Fill(nJets)
                h_nBJet_OSdilep.Fill(nBjets)
        elif len(elIdx_tight) == 2:
            if elCharge[elIdx_tight[0]]*elCharge[elIdx_tight[1]]>0:
                nSSDiLep += 1
                h_nJet_SSdilep.Fill(nJets)
                h_nBJet_SSdilep.Fill(nBjets)
            else:
                nOSDiLep += 1
                h_nJet_OSdilep.Fill(nJets)
                h_nBJet_OSdilep.Fill(nBjets)
        elif len(muIdx_tight) == 1:
            if muCharge[muIdx_tight[0]]*elCharge[elIdx_tight[0]]>0:
                nSSDiLep += 1
                h_nJet_SSdilep.Fill(nJets)
                h_nBJet_SSdilep.Fill(nBjets)
            else:
                nOSDiLep += 1
                h_nJet_OSdilep.Fill(nJets)
                h_nBJet_OSdilep.Fill(nBjets)

    if nGoodLep == 1 and nFakeableLep == 1:
        nOneLepFO += 1
        h_nJet_onelepFO.Fill(nJets)
        h_nBJet_onelepFO.Fill(nBjets)

    if nFakeableLep == 2:
        nFODiLep += 1
        h_nJet_dilepFO.Fill(nJets)
        h_nBJet_dilepFO.Fill(nBjets)
    
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

#write histograms
outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots/"
#outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/plots/"

saveFig(h_nJet_trilep, "h_nJet_trilep", outdir)
saveFig(h_nJet_SSdilep, "h_nJet_SSdilep", outdir)
saveFig(h_nJet_OSdilep, "h_nJet_OSdilep", outdir)
saveFig(h_nJet_onelepFO, "h_nJet_onelepFO", outdir)
saveFig(h_nJet_dilepFO, "h_nJet_dilepFO", outdir)

saveFig(h_nBJet_trilep, "h_nBJet_trilep", outdir)
saveFig(h_nBJet_SSdilep, "h_nBJet_SSdilep", outdir)
saveFig(h_nBJet_OSdilep, "h_nBJet_OSdilep", outdir)
saveFig(h_nBJet_onelepFO, "h_nBJet_onelepFO", outdir)
saveFig(h_nBJet_dilepFO, "h_nBJet_dilepFO", outdir)

print("saved histograms")