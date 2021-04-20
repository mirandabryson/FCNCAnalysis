#code to write datacard from tableMaker.py output
#run with python writeCards.py
#Kaitlin Salyer, April 2021

#import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd

#hardcoded variables other users should customize
outdir = "/home/users/ksalyer/FCNCAnalysis/analysis/datacards/"
outfileName = "datacard_test.txt"


#first, we load the txt output from the tableMaker.py script into a dataframe
#we will manipulate these data, save it into a different dataframe, and print to an output file
df = pd.read_csv("/home/users/ksalyer/FCNCAnalysis/analysis/plots/tables/yieldsTable.txt")
df = df.drop(["total background", "tot back error", "total signal", "tot sig error", "S/B", "S/B error"], axis=1)
print("got yields and stat errors")

#now we need to add the SF and OF dilepton cases
nJets = [2, 3, 4]
nBjets = [0, 1, 2]

for j in nJets:
    for b in nBjets:
        sf_df = df.loc[  (df["nLeptons"]=="SS SF 2l") & (df["nJets"]==j) & (df["nBtags"]==b)  ]
        sf_idx = df.index[  (df["nLeptons"]=="SS SF 2l") & (df["nJets"]==j) & (df["nBtags"]==b)  ].tolist()
        of_df = df.loc[  (df["nLeptons"]=="SS OF 2l") & (df["nJets"]==j) & (df["nBtags"]==b)  ]
        of_idx = df.index[  (df["nLeptons"]=="SS OF 2l") & (df["nJets"]==j) & (df["nBtags"]==b)  ].tolist()

        data = [["SS2l",
                j,
                b,
                (sf_df["signal hut"].values[0]+of_df["signal hut"].values[0]),
                round(( np.sqrt( (sf_df["signal hut error"].values[0]**2)+(of_df["signal hut error"].values[0]**2) ) ), 2),
                (sf_df["signal hct"].values[0]+of_df["signal hct"].values[0]),
                round(( np.sqrt( (sf_df["signal hct error"].values[0]**2)+(of_df["signal hct error"].values[0]**2) ) ), 2),
                (sf_df["other"].values[0]+of_df["other"].values[0]),
                round(( np.sqrt( (sf_df["other error"].values[0]**2)+(of_df["other error"].values[0]**2) ) ), 2),
                (sf_df["fakes"].values[0]+of_df["fakes"].values[0]),
                round(( np.sqrt( (sf_df["fakes error"].values[0]**2)+(of_df["fakes error"].values[0]**2) ) ), 2),
                (sf_df["flips"].values[0]+of_df["flips"].values[0]),
                round(( np.sqrt( (sf_df["flips error"].values[0]**2)+(of_df["flips error"].values[0]**2) ) ), 2)
                ]]
        new_ss_df = pd.DataFrame( data, columns = df.columns )
        
        df = df.drop([sf_idx[0],of_idx[0]], axis=0)
        df = df.append(new_ss_df, ignore_index=True)
print("combined SF and OF dilepton cases")

#now we have imported the data and manipulated it into the categories we want
#signal region bins
nLeps = ["3l", "SS2l"]
nJets = ["2j","3j","4j"]
nBtags = ["0b","1b","2b"]
nProc = ["signal_hut", "signal_hct", "other", "fakes", "flips"]

#make some headers for my dataframe columns
dcColumns = []
for l in nLeps:
    for j in nJets:
        for b in nBtags:
            srName_base = l+"_"+j+"_"+b
            for p in nProc:
                srName = srName_base+"_"+p
                while len(srName) < 20:
                    srName+=" "
                dcColumns.append(srName)


# ok, now I have headers, I can start making the titles for my rows
rowTitles = []
for p in nProc:
    iterator = 0
    while iterator < 18:
        title = p+"_stat_"+str(iterator)
        while len(title) <20:
            title+=" "
        rowTitles.append(title)
        iterator+=1

for p in nProc:
    title = p+"_syst"
    while len(title)<20:
        title+=" "
    rowTitles.append(title)


#dataframe I will print to datacard file
dcard_df = pd.DataFrame(index = rowTitles, columns = dcColumns)
print("defined output dataframe")


#ok, now I want to know the stat uncertainty as a percentage of the yield
for p in nProc:
    proc = p.replace("_"," ")
    statUnc = []
    for l in nLeps:
        for j in nJets:
            jet = j[:-1]
            jet = int(jet)
            for b in nBtags:
                #calculate signal percentage for statistical unc.
                btag = b[:-1]
                btag = int(btag)

                row = df.loc[ (df["nLeptons"]==l) & (df["nJets"]==jet) & (df["nBtags"]==btag) ]
                yld = row[proc].values[0]
                err = row[proc+" error"].values[0]
                
                if yld != 0:
                    dcPercentage = err/yld
                else:
                    dcPercentage = 1

                statUnc.append([l,j,b,dcPercentage])
    for i in range(len(statUnc)):
        lep = statUnc[i][0]
        jet = statUnc[i][1]
        btag = statUnc[i][2]
        unc = statUnc[i][3]

        cTitle = lep+"_"+jet+"_"+btag+"_"+p
        rTitle = p+"_stat_"+str(i)
        while len(cTitle) < 20:
            cTitle+=" "
        while len(rTitle) < 20:
            rTitle+=" "


        for column in dcard_df:
            if column==cTitle:
                filler = str(unc)
                while len(filler)<20:
                    filler+=" "
                dcard_df.at[rTitle,column] = filler
            else:
                filler = "-"
                while len(filler) < 20:
                    filler += " "
                dcard_df.at[rTitle,column] = filler
print("filled stat uncertainties")

#filling dummy systematic uncertainties
for p in nProc:
    if "signal" in p:
        unc = "0.8/1.2"
    elif p == "flips":
        unc = "0.8/1.2"
    elif p == "other":
        unc = "0.7/1.3"
    elif p == "fakes":
        unc = "0.6/1.4"

    while len(unc)<20:
        unc+=" "
    
    rTitle = p+"_syst"
    while len(rTitle)<20:
        rTitle+=" "
    for column in dcard_df:
        if p in column:
            filler = unc
            while len(filler)<20:
                filler+=" "
            dcard_df.at[rTitle,column] = filler
        else:
            filler = "-"
            while len(filler) < 20:
                filler += " "
            dcard_df.at[rTitle,column] = filler
print("filled syst uncertainties")


#define output file and write to output file
outfile = open(outdir+outfileName,"w")
headerRow = "                    "
for c in dcColumns:
    headerRow+=c
    headerRow+="\t"
outfile.write(headerRow)
outfile.write("\n")
outfile.write(dcard_df.to_csv(sep="\t", index=True, header=False))
outfile.close()

