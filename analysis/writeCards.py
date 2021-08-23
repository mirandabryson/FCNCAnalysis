#code to write datacard from tableMaker.py output
#run with python writeCards.py
#Kaitlin Salyer, April 2021

#import some useful packages
import ROOT
import time
import numpy as np
import sys
import pandas as pd
import os

#hardcoded variables other users should customize
outdir = "/home/users/ksalyer/FranksFCNC/ana/analysis/datacards/"
indir = "test"
outdir = outdir+indir+"/"
if not os.path.exists(outdir): os.makedirs(outdir)
# years = [2016, 2017, 2018]
years = [2016, 2017, 2018]
includeSignalInObs = False


fakeCRStatYld_2016 = [  1292,671,397,
                        1231,1089,803,
                        92,146,205,
                        252,146,41,20,
                        339,193,64,42,
                        5,13,13,6
                        ]
fakeCRStatYld_2017 = [  1727,1003,536,
                        1952,1707,1183,
                        183,246,370,
                        264,137,54,35,
                        443,253,115,36,
                        5,24,28,24
                        ]
fakeCRStatYld_2018 = [  2320,1206,666,
                        2708,2206,1601,
                        259,375,550,
                        420,173,70,22,
                        667,404,138,72,
                        11,45,43,28
                        ]


fakeCRStatErr_2016 = {  "2_2_0":3.50365,"2_3_0":4.99353,"2_4_0":6.52687,
                        "2_2_1":3.60495,"2_3_1":3.88372,"2_4_1":4.56676,
                        "2_2_2":13.1561,"2_3_2":10.5987,"2_4_2":8.83165,
                        "3_1_0":8.31807,"3_2_0":10.6145,"3_3_0":17.0339,"3_4_0":29.254,
                        "3_1_1":7.11159,"3_2_1":9.03126,"3_3_1":16.6831,"3_4_1":19.3909,
                        "3_1_2":53.7054,"3_2_2":33.4056,"3_3_2":31.4495,"3_4_2":66.0103
                        }
fakeCRStatErr_2017 = {  "2_2_0":3.33519,"2_3_0":4.41385,"2_4_0":6.08993,
                        "2_2_1":3.11701,"2_3_1":3.30036,"2_4_1":4.05022,
                        "2_2_2":10.4076,"2_3_2":9.20855,"2_4_2":7.40525,
                        "3_1_0":8.19731,"3_2_0":11.5854,"3_3_0":19.1633,"3_4_0":23.6831,
                        "3_1_1":6.19351,"3_2_1":8.0818,"3_3_1":12.7294,"3_4_1":25.1242,
                        "3_1_2":53.354,"3_2_2":26.9341,"3_3_2":25.3507,"3_4_2":26.0582,
                        }
fakeCRStatErr_2018 = {  "2_2_0":3.22747,"2_3_0":4.51919,"2_4_0":6.10372,
                        "2_2_1":2.9054,"2_3_1":3.22509,"2_4_1":3.87638,
                        "2_2_2":9.39522,"2_3_2":8.25866,"2_4_2":6.87119,
                        "3_1_0":7.3366,"3_2_0":11.4367,"3_3_0":17.4301,"3_4_0":27.1185,
                        "3_1_1":5.62841,"3_2_1":7.37149,"3_3_1":13.5088,"3_4_1":19.717,
                        "3_1_2":59.9883,"3_2_2":23.2358,"3_3_2":23.367,"3_4_2":26.6004
                        }


fakeSystErr_2016 = [    4.46067,5.62097,6.07675,
                        4.76551,4.84993,5.59812,
                        5.03131,5.98169,6.29573,
                        6.79787,6.70704,9.27242,8.82801,
                        6.49155,5.32922,8.69589,6.4532,
                        8.72948,5.47438,7.82636,19.5941
                        ]
fakeSystErr_2017 = [    6.63146,7.24731,9.42543,
                        8.08039,7.56606,9.85621,
                        7.74266,7.26889,8.45383,
                        6.98604,9.96351,10.7108,8.9602,
                        8.04912,9.18872,7.79917,13.3502,
                        40.6501,7.21745,10.4827,10.228
                        ]
fakeSystErr_2018 = [    7.71618,7.72384,7.31554,
                        8.71154,9.50327,10.0837,
                        7.85155,7.64877,8.39966,
                        7.96532,10.14,14.7398,21.8245,
                        9.96087,10.1111,10.4591,13.9245,
                        16.6508,10.7022,13.3193,11.5897
                        ]


if not os.path.exists(outdir): os.makedirs(outdir)

for y in years:
    #first, we load the txt output from the tableMaker.py script into a dataframe
    # #we will manipulate these data, save it into a different dataframe, and print to an output file
    # df = pd.read_csv("/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/tables/"+indir+"/tableMaker_"+str(y)+".txt")
    # fakeEst_df = pd.read_csv("/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/tables/"+indir+"/fakeEstyields_"+str(y)+".txt")
    # flipEst_df = pd.read_csv("/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/tables/"+indir+"/flipEstyields_"+str(y)+".txt")
    df = pd.read_csv("/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/tables/aug09_withST/tableMaker_"+str(y)+".txt")
    fakeEst_df = pd.read_csv("/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/tables/aug09_withST/fakeEstyields_"+str(y)+".txt")
    flipEst_df = pd.read_csv("/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/tables/aug09_withST/flipEstyields_"+str(y)+".txt")
    # print df
    # print fakeEst_df
    # print flipEst_df
    fakeCRStatYld = []
    fakeCRStatErr = {}
    if y == 2016: 
        fakeCRStatYld = fakeCRStatYld_2016
        fakeCRStatErr = fakeCRStatErr_2016
    if y == 2017: 
        fakeCRStatYld = fakeCRStatYld_2017
        fakeCRStatErr = fakeCRStatErr_2017
    if y == 2018: 
        fakeCRStatYld = fakeCRStatYld_2018
        fakeCRStatErr = fakeCRStatErr_2018
    print("got yields and stat errors")

    #now we have imported the data and manipulated it into the categories we want
    #we will do the rest in a loop over signals
    signals = ["signal_tuh","signal_tch"]
    for s in signals:
        outfileName = "datacard_"
        outfileName+=s
        outfileName+="_"
        outfileName+=str(y)
        outfileName+=".txt"

        #signal region bins
        nLeps = [2, 3]
        nJets = [2,3,4]
        nMLJets = [1,2,3,4]
        nBtags = [0,1,2]
        # nBtags = [1,2]
        numBins = (len(nMLJets)+len(nJets))*len(nBtags)
        nProc = ["signal", "rares", "fakes_mc", "flips_mc"]
        numBackgrounds = len(nProc)-1

        #make some headers for my dataframe columns
        dcColumns = []
        binNames = []
        binNamesObs = []
        procNames = []
        procIndex = []
        for l in nLeps:
            if l == 2:
                lep = "dilep"
                numJets = list(nJets)
            if l == 3:
                lep = "trilep"
                numJets = list(nMLJets)
            for j in numJets:
                for b in nBtags:
                    counter = 0
                    srName_base = lep+"_"+str(j)+"_"+str(b)
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
                if p == "fakes_mc":
                    title = "fake_stat_"+str(iterator)
                    numParameters+=1
                    yld = str(fakeCRStatYld[iterator])
                    while len(title) <(16-len(yld)):
                        title += " "
                    title += "gmN "+yld

                else:
                    title = p+"_stat_"+str(iterator)
                    numParameters+=1
                    while len(title) <17:
                        title+=" "
                    title+="lnN"
                rowTitles.append(title)
                iterator+=1
            # print(rowTitles)

        for p in nProc:
            title = p+"_syst"
            while len(title)<17:
                title+=" "
            title+="lnN"
            rowTitles.append(title)
            numParameters+=1


        #dataframe I will print to datacard file
        dcard_df = pd.DataFrame(index = rowTitles, columns = dcColumns)
        # print(dcColumns)
        print("defined output dataframe")


        #ok, now I want to know the stat uncertainty as a percentage of the yield
        for p in nProc:
            if p == "signal":
                proc = s
            else:
                proc = p
            statUnc = []
            for l in nLeps:
                if l == 2:
                    numJets = list(nJets)
                if l == 3:
                    numJets = list(nMLJets)
                for j in numJets:
                    for b in nBtags:
                        # print (p, l, j, b)
                        #calculate signal percentage for statistical unc.
                        if proc == "fakes_mc":
                            srbin = str(l)+"_"+str(j)+"_"+str(b)
                            err = fakeCRStatErr[srbin]/100 -1
                            yld = 1
                            print(yld, err)
                        elif proc == "flips_mc":
                            if l == 3:
                                yld = 0.0
                                err = 0
                            else:
                                row = flipEst_df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                                yld = row['data estimate'].values[0]
                                err = row["data estimate error"].values[0]
                        else:
                            # print df
                            # print df.loc[ (df["nLeptons"]==l) ]
                            # print df.loc[ (df["nJets"]==j) ]
                            # print df.loc[ (df["nBtags"]==b) ]
                            row = df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                            # print row
                            yld = row[proc].values[0]
                            err = row[proc+" error"].values[0]
                        
                        if yld > 0:
                            dcPercentage = round(err/yld,3)
                        else:
                            dcPercentage = 1

                        if dcPercentage>=1:
                            dcPercentage = 1

                        statUnc.append([l,j,b,1+dcPercentage])
            # print(statUnc)
            for i in range(len(statUnc)):
                lep = statUnc[i][0]
                if lep == 2: l = "dilep"
                if lep == 3: l = "trilep"
                jet = statUnc[i][1]
                btag = statUnc[i][2]
                unc = statUnc[i][3]

                cTitle = str(l)+"_"+str(jet)+"_"+str(btag)+"_"+p
                while len(cTitle) < 20:
                    cTitle+=" "

                if p =="fakes_mc":
                    rTitle = "fake_stat_"+str(i)
                    yld = str(fakeCRStatYld[i])
                    while len(rTitle) <(16-len(yld)):
                        rTitle += " "
                    rTitle += "gmN "+yld
                else:
                    rTitle = p+"_stat_"+str(i)
                    while len(rTitle) < 17:
                        rTitle+=" "
                    rTitle+="lnN"
                #print("*************")
                #print(cTitle)
                #print(rTitle)
                #print(unc)


                for column in dcard_df:
                    #print column
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
                #print dcard_df
        print("filled stat uncertainties")
        #print(dcard_df)

        #get MC yields in correct order of bins/processes
        rates = []
        observation = []
        for l in nLeps:
            if l == 2:
                numJets = list(nJets)
            if l == 3:
                numJets = list(nMLJets)
            for j in numJets:
                for b in nBtags:
                    fakerow = fakeEst_df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                    fliprow = flipEst_df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                    row     = df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                    obsYld = row["rares"].values[0] + fakerow['data estimate'].values[0] + fliprow['data estimate'].values[0]
                    if includeSignalInObs: obsYld += row[s].values[0]
                    obsYld = round(obsYld,0)
                    obsString = str(obsYld)
                    while len(obsString)<20:
                        obsString+=" "
                    observation.append(obsString)

                    for p in nProc:
                        if p == "signal":
                            p = s
                            yld = row[p].values[0]
                        elif p == "fakes_mc":
                            fakerow = fakeEst_df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                            yld = fakerow["data estimate"].values[0]
                        elif p == "flips_mc":
                            fliprow = flipEst_df.loc[ (df["nLeptons"]==l) & (df["nJets"]==j) & (df["nBtags"]==b) ]
                            yld = fliprow["data estimate"].values[0]
                        else:
                            yld = row[p].values[0]

                        # if yld<0:
                        if yld<=0:
                            yld = 0.01

                        yldString = str(yld)
                        while len(yldString)<20:
                            yldString+=" "
                        rates.append(yldString)



        #filling dummy systematic uncertainties
        for p in nProc:
            if "signal" in p:
                unc = "0.8/1.2"
            elif p == "flips_mc":
                # if y == 2016: unc = '1.1'
                # if y == 2017: unc = '1.4'
                # if y == 2018: unc = '1.3'
                unc = "0.7/1.3"
            elif p == "rares":
                unc = "0.7/1.3"
            elif p == "fakes_mc":
                unc = "0.6/1.4"

            while len(unc)<20:
                unc+=" "
            
            rTitle = p+"_syst"
            while len(rTitle)<17:
                rTitle+=" "
            rTitle+="lnN"

            for column in dcard_df:
                if ((p in column) and not (p=="flips_mc" and "trilep" in column)):
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
        outfile.write("shapes * * FAKE\n\n")
        outfile.write(binHeadersObs)
        outfile.write(obsHeaders)
        outfile.write("\n")
        outfile.write(binHeaders)
        outfile.write(procHeaders)
        outfile.write(pInxHeaders)
        outfile.write(rateHeaders)
        outfile.write(dcard_df.to_csv(sep="\t", index=True, header=False))
        outfile.close()

