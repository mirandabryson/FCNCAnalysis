import ROOT
import time
import numpy as np
import sys

# Load histograms
filename = sys.argv[-1]
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
    hct_max = 0
    hut_max = 0
    back_max = 0

    for h, c, l in zip(hist, histColors, legendNames):
        if l == "signal_hut":
            h.SetLineColor(c)
            h_signal_hut = h.Clone()
            h_signal_hut.SetStats(0)
            h_signal_hut.SetLineWidth(2)
            legend.AddEntry(h_signal_hut, l)
            hut_max = h_signal_hut.GetMaximum()
        
        elif l == "signal_hct":
            h.SetLineColor(c)
            h_signal_hct = h.Clone()
            h_signal_hct.SetStats(0)
            h_signal_hct.SetLineWidth(2)
            legend.AddEntry(h_signal_hct, l)
            hct_max = h_signal_hct.GetMaximum()

        else:
            h.SetLineColor(c)
            h.SetFillColor(c)
            h_stack.Add(h)
            legend.AddEntry(h, l)

        
        """h.SetLineColor(c)
        h.SetLineWidth(2)
        if counter == 0:
            h.DrawNormalized()
        else:
            h.DrawNormalized("same")
        legend.AddEntry(h, l)
        counter += 1"""
    
    back_max = h_stack.GetMaximum()
    #print(backgrYMax)
    if (back_max>hut_max and back_max>hct_max):
        h_stack.Draw("hist")
        h_signal_hut.Draw("hist same")
        h_signal_hct.Draw("hist same")
    elif (hut_max>hct_max and hut_max>back_max):
        h_signal_hut.Draw("hist")
        h_stack.Draw("hist same")
        h_signal_hut.Draw("hist same")
        h_signal_hct.Draw("hist same")
    elif (hct_max>hut_max and hct_max>back_max):
        h_signal_hct.Draw("hist")
        h_stack.Draw("hist same")
        h_signal_hct.Draw("hist same")
        h_signal_hut.Draw("hist same")

    legend.Draw()


    can.SaveAs(outdir+"pdfs/"+hist_name+".pdf")
    can.SaveAs(outdir+"pngs/"+hist_name+".png")

def addHistos(hist, histNames, legendNames, histName, nBins, xmin, xmax):
    
    listOfAddedHistos = []
    for s in legendNames:
        h_combined = ROOT.TH1F("h_combined"+s+histName, histName, nBins, xmin, xmax)
        for h, n in zip(hist, histNames):
            if s in n:
                h_combined.Add(h)
        listOfAddedHistos.append(h_combined)
    return listOfAddedHistos

def getObjFromFile(fname, hname):
    f = ROOT.TFile(fname)
    assert not f.IsZombie()
    f.cd()
    htmp = f.Get(hname)
    if not htmp:  return htmp
    ROOT.gDirectory.cd('PyROOT:/')
    res = htmp.Clone()
    f.Close()
    return res

# main loop
outdir = "/home/users/ksalyer/public_html/dump/FCNC_plots/"
#outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/plots/"

processTypes = ["fakes",
                "flips",
                "other",
                "signal_hut",
                "signal_hct"
                ]

processColors = [ROOT.kPink+7,
                 ROOT.kTeal-5,
                 ROOT.kOrange+7,
                 ROOT.kGreen+2,
                 ROOT.kGreen+3
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
                    #["nGoodLeps", 6, -0.5, 5.5],
                    #["leadLepPt", 50, 0, 500],
                    #["leadLepEta", 20, -5, 5],
                    #["leadLepMass", 50, 0, 500],
                    #["leadLepMiniIso", 50, 0, 5],
                    #["leadLepPtRel", 50, 0, 10],
                    #["leadLepPtRatio", 50, 0, 5],
                    #["leadJetPt", 50, 0, 500],
                    #["leadBPt", 50, 0, 500],
                    #["leadBMass", 50, 0, 500],
                    #["jetHT", 50, 0, 500],
                    #["MET", 50, 0, 500],
                    #["minMT", 50, 0, 500],
                    #["MT_b_MET", 50, 0, 500]
                   ]

for var in plottedVariables:
    v = var[0]
    nbins = var[1]
    xmin = var[2]
    xmax = var[3]
    #print(nbins, xmin, xmax)
    for l in leptonSelections:
        jHistos = []
        jHistoNames = []
        for j in jetSelections:
            bHistos = []
            bHistoNames = []
            for b in bJetSelections:
                histosToPlot = []
                for p in processTypes:
                    histoName = "h_"+v+"_"+l+"_"+j+"_"+b+"_"+p
                    print(histoName)
                    #hist = inFile.Get(histoName)
                    hist = getObjFromFile(filename,histoName)
                    #hist.SetAxisRange(xmin,xmax)
                    #hist.Rebin(nbins)
                    histosToPlot.append(hist)
                    if v == "nJet":
                        jHistos.append(hist)
                        jHistoNames.append(histoName)
                        #print("nJet", histoName)
                    if v == "nBJet":
                        bHistos.append(hist)
                        bHistoNames.append(histoName)
                        #print("btag", histoName)
                #print(len(histosToPlot))
                histFileName = "h_"+v+"_"+l+"_"+j+"_"+b
                saveFig(histosToPlot, processColors, processTypes, histFileName, outdir)
                #print('saved those histos')
            if v == "nBJet":
                histFileName = "h_"+v+"_"+l+"_"+j
                bHistosAdded = addHistos(bHistos, bHistoNames, processTypes, histFileName, nbins, xmin, xmax)
                saveFig(bHistosAdded, processColors, processTypes, histFileName, outdir)
        if v == "nJet":
            histFileName = "h_"+v+"_"+l
            jHistosAdded = addHistos(jHistos, jHistoNames, processTypes, histFileName, nbins, xmin, xmax)
            saveFig(jHistosAdded, processColors, processTypes, histFileName, outdir)
