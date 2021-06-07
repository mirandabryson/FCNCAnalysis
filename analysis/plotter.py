import ROOT
import time
import numpy as np
import sys

# File Inputs
#indir = "./outputs/v6BabyPlots/"
indir = "./outputs/v8Data_triggers_nelnmu/"
year = 2018
sigScale = 0.01


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
    h_data = ROOT.TH1F()
    h_sumBkg = ROOT.TH1F()
    legend = ROOT.TLegend( 0.7, 0.7, 0.89, 0.89 )

    counter = 0
    hct_max = 0
    hut_max = 0
    back_max = 0

    counter = 0
    for h, c, l in zip(hist, histColors, legendNames):
        if l == "signal_tuh":
            h.SetLineColor(c)
            h_signal_hut = h.Clone()
            h_signal_hut.SetStats(0)
            h_signal_hut.SetLineWidth(2)
            h_signal_hut.Scale(sigScale)
            #h_signal_hut.Sumw2()
            legend.AddEntry(h_signal_hut, l)
            hut_max = h_signal_hut.GetMaximum()
        
        elif l == "signal_tch":
            h.SetLineColor(c)
            h_signal_hct = h.Clone()
            h_signal_hct.SetStats(0)
            h_signal_hct.SetLineWidth(2)
            h_signal_hct.Scale(sigScale)
            #h_signal_hct.Sumw2()
            legend.AddEntry(h_signal_hct, l)
            hct_max = h_signal_hct.GetMaximum()

        elif l == "data":
            h.SetLineColor(c)
            h_data = h.Clone()
            h_data.SetStats(0)
            h_data.SetMarkerStyle(ROOT.kFullDotLarge)
            h_data.SetMarkerSize(1)
            #h_data.SetLineWidth(1)
            #h_data.Sumw2()
            legend.AddEntry(h_data, l)

        else:
            if counter==0: h_sumBkg = h.Clone()
            else: h_sumBkg.Add(h)
            h.SetLineColor(ROOT.kGray+2)
            h.SetLineWidth(2)
            h.SetFillColor(c)
            #h.Sumw2()
            h_stack.Add(h)
            legend.AddEntry(h, l)
        counter+=1

        
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
        h_stack.Draw("hist e1")
        h_signal_hut.Draw("hist same e1")
        h_signal_hct.Draw("hist same e1")
        h_data.Draw("hist same p e1")
    elif (hut_max>hct_max and hut_max>back_max):
        h_data.Draw("hist")
        h_signal_hut.Draw("hist same")
        h_stack.Draw("hist same")
        h_signal_hut.Draw("hist same")
        h_signal_hct.Draw("hist same")
        h_data.Draw("hist same")
    elif (hct_max>hut_max and hct_max>back_max):
        h_data.Draw("hist same")
        h_signal_hct.Draw("hist")
        h_stack.Draw("hist same")
        h_signal_hct.Draw("hist same")
        h_signal_hut.Draw("hist same")
        h_data.Draw("hist same")

    legend.Draw()

    #now make ratio plot
    '''can.cd()
    pad2 = ROOT.TPad("pad2", "pad2", 0, 0.05, 1, 0.3)
    pad2.Draw()
    pad2.cd()
    h_ratio = ROOT.TH1F()
    h_ratio = h_sumBkg.Clone()
    #h_ratio.Sumw2()
    h_ratio.SetStats(0)
    h_ratio.Divide(h_data)
    h_ratio.Draw("ep")'''

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

processTypes = ["flips_mc",
                "fakes_mc",
                "rares",
                "signal_tuh",
                "signal_tch",
                "data"
                ]

processColors = [ROOT.kPink+7,
                 ROOT.kOrange+7,
                 ROOT.kTeal-5,
                 ROOT.kGreen+2,
                 ROOT.kGreen+3,
                 ROOT.kBlack
                ]

leptonSelections = ["sf",
                    "df",
                    "mlsf",
                    "mldf",
                   ]


plottedVariables = [["njets", 0],
                    ["nbjets", 0], 
                    ["nleps", 0], 
                    ["neles", 0], 
                    ["nmus", 0], 
                    ["ljpt", 5], 
                    ["tjpt", 5], 
                    ["llpt", 5], 
                    ["ltpt", 5], 
                    ["lleta", 4], 
                    ["lteta", 4], 
                    ["llminiiso", 0], 
                    ["ltminiiso", 0], 
                   ]

for var in plottedVariables:
    v = var[0]
    rebinval = var[1]
    #print(nbins, xmin, xmax)
    for l in leptonSelections:
        histosToPlot = []
        for p in processTypes:
            histoName = "h_"+l+"_"+v+"_"+p
            print(histoName)
            filename = indir+p+"_"+str(year)+"_hists.root"
            print filename
            hist = getObjFromFile(filename,histoName)
            print "got ", histoName, " from ", filename
            if rebinval > 0: hist.Rebin(rebinval)
            histosToPlot.append(hist)
            histFileName = l+"_"+v
        saveFig(histosToPlot, processColors, processTypes, histFileName, outdir)
            