import ROOT
import time
import numpy as np


# Load histograms
inFile = ROOT.TFile.Open("plots/outputHistos.root")
print("loaded files")

# useful functions   
def saveFig(hist, histColors, hist_name, outdir):
    can = ROOT.TCanvas( "c_"+hist_name, "canvas", 800, 800 )

    pad1 = ROOT.TPad( "pad1", "pad1", 0, 0.3, 1, 1.0 )
    pad1.Draw()

    pad1.cd()

    counter = 0
    for h, c in zip(hist, histColors):
        h.SetLineColor(c)
        h.SetLineWidth(2)
        if counter == 0:
            h.DrawNormalized()
        else:
            h.DrawNormalized("same")
        counter += 1


    can.SaveAs(outdir+hist_name+".pdf")
    can.SaveAs(outdir+hist_name+".png")

# main loop
processTypes = ["fakes",
                "flips",
                "rareSM",
                "GluGlu",
                "signal"
                ]
processColors = [ROOT.kRed,
                 ROOT.kBlue,
                 ROOT.kOrange,
                 ROOT.kPink,
                 ROOT.kGreen
                ]

nJet_trilep = []
nJet_SSdilep = []
nJet_OSdilep = []
nJet_onelepFO = []
nJet_dilepFO = []

for p in processTypes:

    h_nJet_trilep   = ROOT.TH1F("h_nJet_trilep", "nJet", 7, -0.5, 6.5)
    h_nJet_SSdilep  = ROOT.TH1D("h_nJet_SSdilep",  "nJets", 7, -0.5, 6.5)
    h_nJet_OSdilep  = ROOT.TH1D("h_nJet_OSdilep",  "nJets", 7, -0.5, 6.5)
    h_nJet_onelepFO = ROOT.TH1D("h_nJet_onelepFO", "nJets", 7, -0.5, 6.5)
    h_nJet_dilepFO  = ROOT.TH1D("h_nJet_dilepFO",  "nJets", 7, -0.5, 6.5)
    
    h_nBJet_trilep   = ROOT.TH1D("h_nBJet_trilep",   "nb-tagged Jets", 4, -0.5, 3.5)
    h_nBJet_SSdilep  = ROOT.TH1D("h_nBJet_SSdilep",  "nb-tagged Jets", 4, -0.5, 3.5)
    h_nBJet_OSdilep  = ROOT.TH1D("h_nBJet_OSdilep",  "nb-tagged Jets", 4, -0.5, 3.5)
    h_nBJet_onelepFO = ROOT.TH1D("h_nBJet_onelepFO", "nb-tagged Jets", 4, -0.5, 3.5)
    h_nBJet_dilepFO  = ROOT.TH1D("h_nBJet_dilepFO",  "nb-tagged Jets", 4, -0.5, 3.5)
    
    
    h_nJet_trilep   = inFile.Get("h_nJet_trilep"+"_"+p)
    h_nJet_SSdilep  = inFile.Get("h_nJet_SSdilep"+"_"+p)
    h_nJet_OSdilep  = inFile.Get("h_nJet_OSdilep"+"_"+p)
    h_nJet_onelepFO = inFile.Get("h_nJet_onelepFO"+"_"+p)
    h_nJet_dilepFO  = inFile.Get("h_nJet_dilepFO"+"_"+p)
    
    h_nBJet_trilep   = inFile.Get("h_nBJet_trilep"+"_"+p)
    h_nBJet_SSdilep  = inFile.Get("h_nBJet_SSdilep"+"_"+p)
    h_nBJet_OSdilep  = inFile.Get("h_nBJet_OSdilep"+"_"+p)
    h_nBJet_onelepFO = inFile.Get("h_nBJet_onelepFO"+"_"+p)
    h_nBJet_dilepFO  = inFile.Get("h_nBJet_dilepFO"+"_"+p)

    nJet_trilep.append(h_nJet_trilep)
    nJet_SSdilep.append(h_nJet_SSdilep)
    nJet_OSdilep.append(h_nJet_OSdilep)
    nJet_onelepFO.append(h_nJet_onelepFO)
    nJet_dilepFO.append(h_nJet_dilepFO)

print("defined histograms")


#write histograms
#outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots/"
outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/plots/"

saveFig(nJet_trilep, processColors, "h_nJet_trilep", outdir)
saveFig(nJet_SSdilep, processColors, "h_nJet_SSdilep", outdir)
saveFig(nJet_OSdilep, processColors, "h_nJet_OSdilep", outdir)
saveFig(nJet_onelepFO, processColors, "h_nJet_onelepFO", outdir)
saveFig(nJet_dilepFO, processColors, "h_nJet_dilepFO", outdir)

"""saveFig(h_nBJet_trilep, "h_nBJet_trilep", outdir)
saveFig(h_nBJet_SSdilep, "h_nBJet_SSdilep", outdir)
saveFig(h_nBJet_OSdilep, "h_nBJet_OSdilep", outdir)
saveFig(h_nBJet_onelepFO, "h_nBJet_onelepFO", outdir)
saveFig(h_nBJet_dilepFO, "h_nBJet_dilepFO", outdir)"""

print("saved histograms")