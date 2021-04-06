import ROOT
import time
import numpy as np
import sys


# Load histograms
filename = sys.argv[-1]
inFile = ROOT.TFile.Open(filename)
#backgroundFile = sys.argv[-2]
#signalFile = sys.argv[-1]
#bFile = ROOT.TFile.Open(backgroundFile)
#sFile = ROOT.TFile.Open(signalFile)
print("loaded files")

# useful functions   
def saveFig(hist, histColors, legendNames, hist_name, outdir):
    can = ROOT.TCanvas( "c_"+hist_name, "canvas", 800, 800 )

    pad1 = ROOT.TPad( "pad1", "pad1", 0, 0.3, 1, 1.0 )
    pad1.Draw()

    pad1.cd()
    pad1.SetLogy()

    h_stack = ROOT.THStack( "h_stack", hist_name )
    h_signal_hut = ROOT.TH1F()
    h_signal_hct = ROOT.TH1F()
    legend = ROOT.TLegend( 0.7, 0.7, 0.89, 0.89 )

    counter = 0
    signalYMin = 0
    signalYMax = 0
    backgrYMin = 0
    backgrYMax = 0

    signalXMin = 0
    signalXMax = 0
    backgrXMin = 0
    backgrXMax = 0

    print("did all this stuff")

    for h, c, l in zip(hist, histColors, legendNames):
        print("entered this loop")
        if l == "signal_hut":
            h.SetLineColor(c)
            h_signal_hut = h.Clone()
            #h_signal_hut.Scale(0.30954)
            h_signal_hut.SetStats(0)
            h_signal_hut.SetLineWidth(2)
            legend.AddEntry(h_signal_hut, l)
            signalYMax = h_signal_hut.GetMaximum()
            signalYMin = h_signal_hut.GetMinimum()
            signalXMax = h_signal_hut.GetXaxis().GetXmax()
            signalXMin = h_signal_hut.GetXaxis().GetXmin()
            #print(signalYMax,signalYMin,signalXMax,signalXMin)
            print("did hut signal stuff")
        
        elif l == "signal_hct":
            h.SetLineColor(c)
            h_signal_hct = h.Clone()
            #h_signal_hct.Scale(0.30954)
            h_signal_hct.SetStats(0)
            h_signal_hct.SetLineWidth(2)
            legend.AddEntry(h_signal_hct, l)
            print("did hct signal stuff")

        else:
            print("im here")
            #h.SetLineColor(c)
            #print("i set line color")
            #h.SetFillColor(c)
            #print("i set fill color")
            h_stack.Add(h)
            print("i add to stack")
            legend.AddEntry(h, l)
            print("did background stuff")

        
        """h.SetLineColor(c)
        h.SetLineWidth(2)
        if counter == 0:
            h.DrawNormalized()
        else:
            h.DrawNormalized("same")
        legend.AddEntry(h, l)
        counter += 1"""
    
    backgrYMax = h_stack.GetMaximum()
    #print(backgrYMax)
    if backgrYMax>signalYMax:
        h_stack.Draw("hist")
        h_signal_hut.Draw("hist same")
        h_signal_hct.Draw("hist same")
        print("backgrounds bigger")
    else:
        h_signal_hut.Draw("hist")
        #h_signal_hct.Draw("hist")
        h_stack.Draw("hist same")
        h_signal_hut.Draw("hist same")
        h_signal_hct.Draw("hist same")
        print("signals bigger")

    legend.Draw()


    can.SaveAs(outdir+hist_name+".pdf")
    can.SaveAs(outdir+hist_name+".png")

# main loop
#outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots/"
outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/plots/"

processTypes = ["other",
                "fakes",
                "flips",
                "signal_hut",
                "signal_hct"
                ]

processColors = [ROOT.kRed,
                 ROOT.kBlue,
                 ROOT.kOrange+7,
                 ROOT.kPink+7,
                 ROOT.kGreen+2
                ]
"""processTypes = ["signal_hut",
                "signal_hct",
                "rareSM",
                "wjets",
                "DY",
                "ttX",
                "multiboson",
                "ttjets"
                ]
processColors = [ROOT.kGreen+2,
                 ROOT.kGreen+3,
                 ROOT.kPink+7,
                 ROOT.kTeal-5,
                 ROOT.kOrange+7,
                 ROOT.kViolet-5,
                 ROOT.kRed,
                 ROOT.kBlue
                ]"""

leptonSelections = ["trilep",
                    "SS_SF_dilep",
                    "SS_OF_dilep",
                    "OS_SF_dilep",
                    "OS_OF_dilep",
                    "onelepFO",
                    "dilepFO"
                   ]

jetSelections = ["2j",
                 "3j",
                 "ge4j"
                 ]

bJetSelections = ["0b",
                  "1b",
                  "ge2b"
                  ]

plottedVariables = [["nJet", 7, -0.5, 6.5],
                    ["nBJet", 4, -0.5, 3.5], 
                    ["nGoodLeps", 6, -0.5, 5.5],
                    ["leadLepPt", 50, 0, 500],
                    ["leadLepEta", 20, -5, 5],
                    ["leadLepMass", 50, 0, 500],
                    ["leadLepMiniIso", 50, 0, 5],
                    ["leadLepPtRel", 50, 0, 10],
                    ["leadLepPtRatio", 50, 0, 5],
                    ["leadJetPt", 50, 0, 500],
                    ["leadBPt", 50, 0, 500],
                    ["leadBMass", 50, 0, 500],
                    ["jetHT", 100, 0, 1000],
                    ["MET", 50, 0, 500],
                    ["minMT", 50, 0, 500],
                    ["MT_b_MET", 50, 0, 500]
                   ]

for var in plottedVariables:
    v = var[0]
    nbins = var[1]
    xmin = var[2]
    xmax = var[3]
    for l in leptonSelections:
        for j in jetSelections:
            for b in bJetSelections:
                histosToPlot = []
                for p in processTypes:
                    histoName = "h_"+v+"_"+l+"_"+j+"_"+b+"_"+p
                    print(histoName)
                    hist = ROOT.TH1F(histoName, v, nbins, xmin, xmax)
                    hist = inFile.Get(histoName)
                    histosToPlot.append(hist)
                print(len(histosToPlot))
                saveFig(histosToPlot, processColors, processTypes, v, outdir)
                print('saved those histos')
