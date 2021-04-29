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


#first, we load the txt output from the tableMaker.py script into a dataframe
#we will manipulate these data, save it into a different dataframe, and print to an output file
df = pd.read_csv("/home/users/ksalyer/FCNCAnalysis/analysis/plots/tables/yieldsTable.txt")
df = df.drop(["total signal", "tot sig error", "S/B", "S/B error"], axis=1)
#df = df.drop(["signal hut","signal hut error","signal hct","signal hct error"], axis=1)
#df = df.rename(columns={"total signal":"signal","tot sig error":"signal error"})
#print(df)
print("got yields and stat errors")

#df["signal hut"] = 83.88144*df["signal hut"]/12.539955536
#df["signal hut error"] = 83.88144*df["signal hut error"]/12.539955536
#df["signal hct"] = 83.88144*df["signal hct"]/12.537756236
#df["signal hct error"] = 83.88144*df["signal hct error"]/12.537756236

#now we need to add the SF and OF dilepton cases
nJets = [2, 3, 4]
nBjets = [0, 1, 2]
#nBjets = [1, 2]

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
                round(( np.sqrt( (sf_df["flips error"].values[0]**2)+(of_df["flips error"].values[0]**2) ) ), 2),
                (sf_df["total background"].values[0]+of_df["total background"].values[0]),
                round(( np.sqrt( (sf_df["tot back error"].values[0]**2)+(of_df["tot back error"].values[0]**2) ) ), 2)
                ]]
        new_ss_df = pd.DataFrame( data, columns = df.columns )
        
        df = df.drop([sf_idx[0],of_idx[0]], axis=0)
        df = df.append(new_ss_df, ignore_index=True)
#print(df)
print("combined SF and OF dilepton cases")

"""trilep_df_1b = df.loc[ (df["nLeptons"]=="3l") & (df["nBtags"]==1) ]
trilep_df_2b = df.loc[ (df["nLeptons"]=="3l") & (df["nBtags"]==2) ]
trilep_df = trilep_df_1b
trilep_df = trilep_df.append(trilep_df_2b)
print(trilep_df)
otherTotal = trilep_df["other"].sum()
fakesTotal = trilep_df["fakes"].sum()
flipsTotal = trilep_df["flips"].sum()
bkgTotal = trilep_df["total background"].sum()
hctTotal = trilep_df["signal hct"].sum()
hutTotal = trilep_df["signal hut"].sum()
print(otherTotal)
print(fakesTotal)
print(flipsTotal)
print(bkgTotal)
print(hctTotal)
print(hutTotal)
print("*****************")
dilep_df = df.loc[ (df["nLeptons"]=="SS2l") ]
otherTotal = dilep_df["other"].sum()
fakesTotal = dilep_df["fakes"].sum()
flipsTotal = dilep_df["flips"].sum()
bkgTotal = dilep_df["total background"].sum()
hctTotal = dilep_df["signal hct"].sum()
hutTotal = dilep_df["signal hut"].sum()
print(otherTotal)
print(fakesTotal)
print(flipsTotal)
print(bkgTotal)
print(hctTotal)
print(hutTotal)"""

#now we have imported the data and manipulated it into the categories we want
#we will do the rest in a loop over signals
signals = ["signal_hut","signal_hct"]
for s in signals:
    outfileName = "datacard_test_"
    outfileName+=s
    outfileName+=".txt"

    #signal region bins
    nLeps = ["3l", "SS2l"]
    nJets = ["2j","3j","4j"]
    nBtags = ["0b","1b","2b"]
    #nBtags = ["1b","2b"]
    numBins = len(nLeps)*len(nJets)*len(nBtags)
    nProc = ["signal", "other", "fakes", "flips"]
    numBackgrounds = len(nProc)-1

    #make some headers for my dataframe columns
    dcColumns = []
    binNames = []
    binNamesObs = []
    procNames = []
    procIndex = []
    for l in nLeps:
        if l == "3l":
            l = "trilep"
        for j in nJets:
            for b in nBtags:
                counter = 0
                srName_base = l+"_"+j+"_"+b
                binName = srName_base
                while len(binName) < 20:
                    binName+=" "
                binNamesObs.append(binName)
                for p in nProc:
                    srName = srName_base+"_"+p

                    binNames.append(binName)

                    while len(srName) < 20:
                        srName+=" "
                    dcColumns.append(srName)

                    while len(p) < 20:
                        p+=" "
                    procNames.append(p)

                    counterString = str(counter)
                    while len(counterString) < 20:
                        counterString+=" "
                    procIndex.append(counterString)
                    counter+=1

    # ok, now I have headers, I can start making the titles for my rows
    rowTitles = []
    numParameters = 0
    for p in nProc:
        iterator = 0
        while iterator < numBins:
            title = p+"_stat_"+str(iterator)
            numParameters+=1
            while len(title) <17:
                title+=" "
            title+="lnN"
            rowTitles.append(title)
            iterator+=1

    for p in nProc:
        title = p+"_syst"
        while len(title)<17:
            title+=" "
        title+="lnN"
        rowTitles.append(title)
        numParameters+=1


    #dataframe I will print to datacard file
    dcard_df = pd.DataFrame(index = rowTitles, columns = dcColumns)
    print("defined output dataframe")


    #ok, now I want to know the stat uncertainty as a percentage of the yield
    for p in nProc:
        if p == "signal":
            proc = s
            proc = proc.replace("_", " ")
        else:
            proc = p
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
                        dcPercentage = round(err/yld,3)
                    else:
                        dcPercentage = 1

                    statUnc.append([l,j,b,1+dcPercentage])
        #print(statUnc)
        for i in range(len(statUnc)):
            lep = statUnc[i][0]
            if lep=="3l":
                lep="trilep"
            jet = statUnc[i][1]
            btag = statUnc[i][2]
            unc = statUnc[i][3]

            if unc < 0:
                unc = 2.0

            cTitle = lep+"_"+jet+"_"+btag+"_"+p
            rTitle = p+"_stat_"+str(i)
            while len(cTitle) < 20:
                cTitle+=" "
            while len(rTitle) < 17:
                rTitle+=" "
            rTitle+="lnN"

            #print(cTitle)
            #print(rTitle)
            #print(unc)


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
    #print(dcard_df)

    #get MC yields in correct order of bins/processes
    rates = []
    observation = []
    for l in nLeps:
        for j in nJets:
            jet = j[:-1]
            jet = int(jet)
            for b in nBtags:
                btag = b[:-1]
                btag = int(btag)

                row = df.loc[ (df["nLeptons"]==l) & (df["nJets"]==jet) & (df["nBtags"]==btag) ]
                obsYld = row["total background"].values[0]
                obsYld = round(obsYld,0)
                obsString = str(obsYld)
                while len(obsString)<20:
                    obsString+=" "
                observation.append(obsString)

                for p in nProc:
                    if p == "signal":
                        p = s
                        p = p.replace("_", " ")
                        yld = row[p].values[0]
                    else:
                        yld = row[p].values[0]

                    if yld<0:
                        yld = 0.01

                    yldString = str(yld)
                    while len(yldString)<20:
                        yldString+=" "
                    rates.append(yldString)



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
        while len(rTitle)<17:
            rTitle+=" "
        rTitle+="lnN"

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
    binHeadersObs = "bin                 \t"
    for b in binNamesObs:
        binHeadersObs+=b
        binHeadersObs+="\t"
    binHeadersObs+="\n"
    binHeaders = "bin                 \t"
    for b in binNames:
        binHeaders+=b
        binHeaders+="\t"
    binHeaders+="\n"
    procHeaders = "process             \t"
    for p in procNames:
        procHeaders+=p
        procHeaders+="\t"
    procHeaders+="\n"
    pInxHeaders = "process             \t"
    for i in procIndex:
        pInxHeaders+=i
        pInxHeaders+="\t"
    pInxHeaders+="\n"
    rateHeaders = "rate                \t"
    for r in rates:
        rateHeaders+=r
        rateHeaders+="\t"
    rateHeaders+="\n"
    obsHeaders = "observation         \t"
    for o in observation:
        obsHeaders+=o
        obsHeaders+="\t"
    obsHeaders+="\n"
    imaxHeader = "imax "+str(numBins)+" number of channels\n"
    jmaxHeader = "jmax "+str(numBackgrounds)+" number of backgrounds\n"
    kmaxHeader = "kmax "+str(numParameters)+" number of nuisance parameters\n"
    outfile.write(imaxHeader)
    outfile.write(jmaxHeader)
    outfile.write(kmaxHeader)
    outfile.write("shape * * FAKE\n\n")
    outfile.write(binHeadersObs)
    outfile.write(obsHeaders)
    outfile.write("\n")
    outfile.write(binHeaders)
    outfile.write(procHeaders)
    outfile.write(pInxHeaders)
    outfile.write(rateHeaders)
    outfile.write(dcard_df.to_csv(sep="\t", index=True, header=False))
    outfile.close()

