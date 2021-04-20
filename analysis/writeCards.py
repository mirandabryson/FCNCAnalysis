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






























#print(df.loc[ df["nLeptons"] == "SS SF 2l" ])
#print(df.loc[ df["nJets"]==2 ])
#print(df.loc[ (df["nLeptons"] == "SS SF 2l") & (df["nJets"]==2) ])


#of_df = df.loc[df["nLeptons"] == "SS OF 2l"]



























"""
#Global variables
lumi = 137.
backgrounds = ["flip", "fake", "other"]

#useful functions
def writeCard(v_bin_names, v_bkgYields, v_sigYields):
    outfile = "datacard.txt"

    print("opened datacard")

    for b in v_bin_names:





















void writeCard(vector<string> bin_names, vector<vector<GammaParams> > allyields,vector<vector<float> > mct_transfer_factors,vector<vector<GammaParams> > sigyields);
int main(){
  gErrorIgnoreLevel=6000; // Turns off ROOT errors due to missing branches

  chrono::high_resolution_clock::time_point begTime;
  begTime = chrono::high_resolution_clock::now();

  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////// Defining processes //////////////////////////////////////////


  Palette colors("txt/colors.txt", "default");

  // Cuts in baseline speed up the yield finding
  string baseline         = "";
  NamedFunc baselinef     = "pass&&nvetoleps>=1&&ngoodjets>=2 && ngoodjets<=3 &&pfmet>125&&mt_met_lep>150 && ngoodbtags==2 && nWHLeptons>=1";
  TString single_lep      = "nvetoleps==1&&PassTrackVeto&&PassTauVeto&&nWHLeptons==1";
  TString dilep           = "nvetoleps==2";

  string mc2016_dir       = "/home/users/rheller/wh_babies/babies_v31_2_2019_10_03/s16v3/";
  string mc2016_dir_ttmet = "/home/users/rheller/wh_babies/babies_v30_9_2019_10_05/s16v3/";

  string mc2017_dir       = "/home/users/rheller/wh_babies/babies_v31_2_2019_10_03/f17v2/";
  string mc2017_dir_ttmet = "/home/users/rheller/wh_babies/babies_v30_9_2019_10_05/f17v2/";

  string mc2018_dir       = "/home/users/rheller/wh_babies/babies_v31_2_2019_10_03/a18v1/";
  string mc2018_dir_ttmet = "/home/users/rheller/wh_babies/babies_v30_9_2019_10_07/a18v1/";

  string signal_dir2016   = "/home/users/rheller/wh_babies/babies_signal_s16v3_v32_2019_10_07/";
  string signal_dir2017   = "/home/users/rheller/wh_babies/babies_signal_f17v2_v32_0_2019_10_07/";
  string signal_dir2018   = "/home/users/rheller/wh_babies/babies_signal_a18v1_v32_0_2019_10_07/";



  auto all_top = {mc2016_dir+"*TTJets_1lep_top_s16v3*.root",mc2016_dir+"*TTJets_1lep_tbar_s16v3*",mc2016_dir_ttmet+"*TTJets_1lep_*met150*.root",mc2017_dir+"*TTJets_1lep_top_f17v2*.root",mc2017_dir+"*TTJets_1lep_tbar_f17v2*",mc2017_dir_ttmet+"*TTJets_1lep_*met150*.root",mc2018_dir+"*TTJets_1lep_top_a18v1*.root",mc2018_dir+"*TTJets_1lep_tbar_a18v1*",mc2018_dir_ttmet+"*TTJets_1lep_*met80*.root",mc2016_dir+"*_ST_*.root",mc2017_dir+"*_ST_*.root",mc2018_dir+"*_ST_*.root",mc2016_dir+"*TTJets_2lep_s16v3*.root", mc2016_dir_ttmet+"*TTJets_2lep_*met150*.root",mc2017_dir+"*TTJets_2lep_f17v2*.root", mc2017_dir_ttmet+"*TTJets_2lep_*met150*.root",mc2018_dir+"*TTJets_2lep_a18v1*.root",mc2018_dir_ttmet+"*TTJets_2lep_*met80*.root"};


  auto all_other = {mc2016_dir+"*WW*.root", mc2016_dir+"*WZ*.root",mc2016_dir+"*ZZ*.root",mc2017_dir+"*WW*.root", mc2017_dir+"*WZ*.root",mc2017_dir+"*ZZ*.root",mc2018_dir+"*WW*.root", mc2018_dir+"*WZ*.root",mc2018_dir+"*ZZ*.root",mc2016_dir+"*_TTWJets*.root", mc2016_dir+"*_TTZ*.root",mc2017_dir+"*_TTWJets*.root", mc2017_dir+"*_TTZ*.root",mc2018_dir+"*_TTWJets*.root", mc2018_dir+"*_TTZ*.root"};

  //// Contributions
  auto proc_wjets = Process::MakeShared<Baby_full>("W+jets 2016-2018", Process::Type::background, kCyan-3, {mc2016_dir+"*slim_W*JetsToLNu_s16v3*",mc2016_dir+"*W*Jets_NuPt200_s16v*.root",mc2017_dir+"*slim_W*JetsToLNu_f17v2*",mc2017_dir+"*W*Jets_NuPt200_f17v2*.root",mc2018_dir+"*slim_W*JetsToLNu_a18v1*",mc2018_dir+"*W*Jets_NuPt200_a18v1*.root"},"stitch&&evt!=74125994"&&baselinef);
  auto proc_top = Process::MakeShared<Baby_full>("top 2016-2018", Process::Type::background, kRed,all_top,"stitch"&&baselinef);

  auto proc_other = Process::MakeShared<Baby_full>("TTV and VV 2016-2018", Process::Type::background, kRed,all_other,baselinef);

  auto proc_sig = Process::MakeShared<Baby_full>("2016-2018 TChiWH(750,1)", Process::Type::signal, colors("t1tttt"),
  {signal_dir2016+"*TChiWH*.root",signal_dir2017+"*TChiWH*.root",signal_dir2018+"*TChiWH*.root"},"mass_stop==750&&mass_lsp==1"&&baselinef);

  auto proc_sig_compress = Process::MakeShared<Baby_full>("2016-2018 TChiWH(225,75)", Process::Type::signal, colors("t1tttt"),
  {signal_dir2016+"*TChiWH*.root",signal_dir2017+"*TChiWH*.root",signal_dir2018+"*TChiWH*.root"},"mass_stop==225&&mass_lsp==75"&&baselinef);

    auto proc_sig_medium = Process::MakeShared<Baby_full>("2016-2018 TChiWH(350,150)", Process::Type::signal, colors("t1tttt"),
  {signal_dir2016+"*TChiWH*.root",signal_dir2017+"*TChiWH*.root",signal_dir2018+"*TChiWH*.root"},"mass_stop==350&&mass_lsp==150"&&baselinef);


  vector<shared_ptr<Process> > all_procs_bkg = {proc_top,proc_wjets,proc_other};
  vector<shared_ptr<Process> > sig_procs = {proc_sig,proc_sig_medium,proc_sig_compress};

  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// Defining cuts ///////////////////////////////////////////////
  // baseline defined above

	  vector<NamedFunc> weights; //size_t nsels; 
	  vector<TString> numerators,denominators;
	  vector<TString> leglabels;


	vector<NamedFunc> metbins = {"pfmet>125&&pfmet<=200","pfmet>200&&pfmet<=300","pfmet>300"};	
	vector<NamedFunc> njetbins = {"ngoodjets==2","ngoodjets==3"&&LeadingNonBJetPt_med<100.};
	vector<NamedFunc> deepAK8bins = {max_ak8pfjets_deepdisc_hbb<=0.8,max_ak8pfjets_deepdisc_hbb>0.8};

	vector<string> metnames={"lowmet","medmet","highmet"};
	vector<string> njetnames={"nj2","nj3"};
	vector<string> htagnames={"res","boos"};

    weights= { "weight * w_pu" * yearWeight};

    leglabels = {"Nominal"};

    // nsels = 2*weights.size();

    TString signal_region = single_lep+"&&mct>200&&mbb>90&&mbb<150";
    TString mct_control_region = single_lep+"&&mct>150&&mct<=200&&mbb>90&&mbb<150";

    TString signal_region_boost = single_lep+"&&mct>200&&mbb>90&&mbb<150";
    TString mct_control_region_boost = single_lep+"&&mct<=200&&mbb>90&&mbb<150";

    // for(uint ivar=0;ivar<weights.size();ivar++){
    //   numerators.push_back(numerator);
    //   denominators.push_back(denominator);
    // }
 

  vector<int> proc_options = {0,1};//allbkg, top 
  vector<TString> tags = {"allbkg","top"};

  vector<vector<vector<int> > > indices;

  for(int i=0;i<static_cast<int>(denominators.size());i++){
    //numerator is always top only; W predicted separately.
    indices.push_back(vector<vector<int> >({{proc_options[bkg],2*i,-1},{proc_options[top],2*i+1,1}}));
  }

  PlotMaker pm;
  vector<NamedFunc> allcuts;
  vector<TableRow> table_rows;
  vector<string> bin_names;
  for(uint inj=0;inj<njetbins.size();inj++){
		for(uint imet=0;imet<metbins.size();imet++){
			for(uint ideepAK8=0;ideepAK8<deepAK8bins.size();ideepAK8++){
			if(!boosted && ideepAK8>0) continue;
			NamedFunc totcut = "1";
			
			if(boosted){
				if(ideepAK8==0)  totcut = njetbins[inj] && metbins[imet] && deepAK8bins[ideepAK8] && signal_region;
				else totcut = njetbins[inj] && metbins[imet] && deepAK8bins[ideepAK8] && signal_region_boost;
				bin_names.push_back(njetnames[inj]+"_"+metnames[imet]+"_"+htagnames[ideepAK8]);
			}
			else{ totcut = njetbins[inj] && metbins[imet] && signal_region;
				bin_names.push_back(njetnames[inj]+"_"+metnames[imet]);
			}

			allcuts.push_back(totcut);
			table_rows.push_back(TableRow("", totcut,0,0,weights[0]));
			
			if(boosted){
				if(ideepAK8==0) totcut= njetbins[inj] && metbins[imet] && deepAK8bins[ideepAK8] && mct_control_region;
				else totcut= njetbins[inj] && metbins[imet] && deepAK8bins[ideepAK8] && mct_control_region_boost;
				bin_names.push_back("CR_lowmct_"+njetnames[inj]+"_"+metnames[imet]+"_"+htagnames[ideepAK8]);
			}
			else{
				totcut= njetbins[inj] && metbins[imet] && mct_control_region;
				bin_names.push_back("CR_lowmct_"+njetnames[inj]+"_"+metnames[imet]);
			}
			allcuts.push_back(totcut);
			table_rows.push_back(TableRow("", totcut,0,0,weights[0]));
			

		}
  }
}
  TString tname = "all_bins";
  pm.Push<Table>(tname.Data(),  table_rows, all_procs_bkg, false, false);
  pm.Push<Table>(tname.Data(),  table_rows, sig_procs, false, false);
 
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////// Finding all yields ///////////////////////////////////////////////
  
  pm.min_print_ = true;
  pm.MakePlots(lumi);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////// Calculating preds/kappas and printing table //////////////////////////////////////
	size_t nrows= table_rows.size();
    // allyields: [0] All bkg, [1] tt1l, [2] tt2l, [3] other
   
   //Extract yields
    vector<vector<GammaParams> > allyields(4,vector<GammaParams> (nrows));
    Table * yield_table = static_cast<Table*>(pm.Figures()[0].get());
	allyields[bkg] = yield_table->BackgroundYield(lumi);
	allyields[top] = yield_table->Yield(proc_top.get(), lumi);
	allyields[w] = yield_table->Yield(proc_wjets.get(), lumi);
	allyields[other] = yield_table->Yield(proc_other.get(), lumi);

	vector<vector<GammaParams> > sigyields(sig_procs.size(),vector<GammaParams> (nrows));
	Table * yield_table_sig = static_cast<Table*>(pm.Figures()[1].get());
	sigyields[0] = yield_table_sig->Yield(proc_sig.get(), lumi);
	sigyields[1] = yield_table_sig->Yield(proc_sig_medium.get(), lumi);
	sigyields[2] = yield_table_sig->Yield(proc_sig_compress.get(), lumi);


	vector<vector<float> > mct_transfer_factors;
	float val(1.), valup(1.), valdown(1.);
    //calculate mct transfer factors
    for(size_t ibin=0; ibin<nrows; ibin+=2){ //NB iterating by 2
		vector<vector<float> > entries;
		vector<vector<float> > sumweights;
		vector<float> powers;

		//Numerator
		entries.push_back(vector<float>());
		sumweights.push_back(vector<float>());
		entries.back().push_back(allyields[top][ibin].NEffective()); //numerator includes top yield only
		sumweights.back().push_back(allyields[top][ibin].Weight());
		powers.push_back(1); //+1 indicates numerator

		//Denominator
		entries.push_back(vector<float>());
		sumweights.push_back(vector<float>());
		entries.back().push_back(allyields[bkg][ibin+1].NEffective()); //denominator includes all processes
		sumweights.back().push_back(allyields[bkg][ibin+1].Weight());
		powers.push_back(-1); //-1 indicates denominator

		 // Throwing toys to find ratios and uncertainties
		 //if(igraph!=0)
		 val = calcKappa(entries, sumweights, powers, valdown, valup);
		 if(valdown<0) valdown = 0;
		 mct_transfer_factors.push_back(vector<float>({val, valdown, valup}));

      } // Loop over indices


	  for(size_t irow=0; irow<nrows; irow++){ 
	    // allyields[bkg] = yield_table->BackgroundYield(lumi);
	    cout<<bin_names[irow]<<", MC: "    <<setw(7)<<RoundNumber(allyields[bkg][irow].Yield(),3)<<" pm "<<setw(7)<<RoundNumber(allyields[bkg][irow].Uncertainty(), 3);
	    //cout<<"allyields "<<allyields[bkg]  [idens]<<endl;
	    // allyields[top] = yield_table->Yield(proc_top.get(), lumi);
		  cout<<", top: "    <<setw(7)<<RoundNumber(allyields[top][irow].Yield(), 3);
		  cout<<", signal NC: "    <<setw(7)<<RoundNumber(sigyields[0][irow].Yield(), 3);
		  cout<<", signal medium: "    <<setw(7)<<RoundNumber(sigyields[1][irow].Yield(), 3);
		  cout<<", signal compressed: "    <<setw(7)<<RoundNumber(sigyields[2][irow].Yield(), 3)<<endl;
		  if(irow%2==1) cout<<"mCT ratio: "<<setw(7)<<RoundNumber(mct_transfer_factors[(irow-1)/2][0],3)<<endl;	
	    // allyields[w] = yield_table->Yield(proc_wjets.get(), lumi);
	    // allyields[other] = yield_table->Yield(proc_other.get(), lumi);

	  } // Loop over rows
	 writeCard(bin_names,allyields,mct_transfer_factors,sigyields);
  double seconds = (chrono::duration<double>(chrono::high_resolution_clock::now() - begTime)).count();
  TString hhmmss = HoursMinSec(seconds);
  cout<<endl<<"Finding yields took "<<round(seconds)<<" seconds ("<<hhmmss<<")"<<endl<<endl;

} // main

////////////////////////////////////////// End of main //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void writeCard(vector<string> bin_names, vector<vector<GammaParams> > allyields,vector<vector<float> > mct_transfer_factors,vector<vector<GammaParams> > sigyields){

 	TString outpath = "datacard_template";
 	if(boosted) outpath+="_boosted";
 	if(discovery_mode) outpath+= "_significance";
 	outpath+=".txt";

    cout<<"open "<<outpath<<endl;

    uint nbins = bin_names.size();

    unsigned wname(21), wdist(2), wbin(12);
    for (size_t ibin(0); ibin<nbins; ibin+=2) 
      if(bin_names[ibin].length() > wbin) wbin = bin_names[ibin].length();
    wbin+=1;
    unsigned digit = 2;
    // if (unblind) digit = 0;
    cout<<mct_transfer_factors[0][0]<<endl;
    // --------- write header
    ofstream fcard(outpath);
    int nbg=3;
    int nsyst = 3 + nbins/2 + 3*nbins/2; //one nuisance for every met/njet bin + 3 per bin
    fcard<<"imax "<<nbins/2<<"  number of channels\n";
    fcard<<"jmax "<<nbg<<"  number of backgrounds\n";
    fcard<<"kmax "<<nsyst<<"  number of nuisance parameters\n";
    fcard<<"shapes * * FAKE\n";
    fcard<<endl<<left<<setw(wname)<<"bin"<<setw(wdist)<<" ";
    for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<bin_names[ibin];
    fcard<<endl<<left<<setw(wname)<<"observation"<<setw(wdist)<<" ";
    
    if(!discovery_mode) for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<RoundNumber(allyields[bkg][ibin].Yield(),digit);
 	  else for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<RoundNumber(allyields[bkg][ibin].Yield()+sigyields[0][ibin].Yield(),digit);

    fcard<<endl<<endl<<left<<setw(wname)<<"bin"<<setw(wdist)<<" ";
     for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<bin_names[ibin]<<left<<setw(wbin)<<bin_names[ibin]<<left<<setw(wbin)<<bin_names[ibin]<<left<<setw(wbin)<<bin_names[ibin];
    fcard<<endl<<left<<setw(wname)<<"process"<<setw(wdist)<<" ";
    for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<"sig"<<left<<setw(wbin)<<"top"<<left<<setw(wbin)<<"wjets"<<left<<setw(wbin)<<"other";
    fcard<<endl<<left<<setw(wname)<<"process"<<setw(wdist)<<" ";
    for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<setw(wbin)<<"0"<<setw(wbin)<<"1"<<setw(wbin)<<"2"<<setw(wbin)<<"3";
    fcard<<endl<<left<<setw(wname)<<"rate"<<setw(wdist)<<" ";
     for (size_t ibin(0); ibin<nbins; ibin+=2) 
        fcard<<setw(wbin)<<Form("%.2f",sigyields[0][ibin].Yield())<<setw(wbin)<<Form("%.2f",allyields[1][ibin].Yield())<<setw(wbin)<<Form("%.2f",allyields[2][ibin].Yield())<<setw(wbin)<<Form("%.2f",allyields[3][ibin].Yield())<<setw(wbin);
  
    fcard<<endl;
    float sys_lumi = 1.05;
    float sys_filler = 1.15;
    float sys_sig_filler = 1.15;
    unsigned wsyst(14); unsigned wsystype(wname-wsyst);
    fcard<<endl<<left<<setw(wsyst)<<"lumi"<<setw(wsystype)<<"lnN"<<setw(wdist)<<" ";
    for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<Form("%.2f",sys_lumi)<<left<<setw(wbin)<<"-"<<left<<setw(wbin)<<Form("%.2f",sys_lumi)<<left<<setw(wbin)<<Form("%.2f",sys_lumi);
    fcard<<endl<<left<<setw(wsyst)<<"bkg_flat"<<setw(wsystype)<<"lnN"<<setw(wdist)<<" ";
    for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<"-"<<left<<setw(wbin)<<Form("%.2f",sys_filler)<<left<<setw(wbin)<<Form("%.2f",sys_filler)<<left<<setw(wbin)<<Form("%.2f",sys_filler);
    fcard<<endl<<left<<setw(wsyst)<<"sig_flat"<<setw(wsystype)<<"lnN"<<setw(wdist)<<" ";
    for (size_t ibin(0); ibin<nbins; ibin+=2) fcard<<left<<setw(wbin)<<Form("%.2f",sys_sig_filler)<<left<<setw(wbin)<<"-"<<left<<setw(wbin)<<"-"<<left<<setw(wbin)<<"-";
    
    //Control region stats
    for (size_t ibin(0); ibin<nbins; ibin+=2){
    	fcard<<endl<<left<<setw(wname)<<Form("mCT_CR_stat%i gmN %.0f",static_cast<int>(ibin),allyields[bkg][ibin+1].Yield())<<setw(wdist)<<" ";
    	for(size_t j(0);j<1+(nbg+1)*(ibin/2);j++) fcard<<left<<setw(wbin)<<"-";
    	fcard<<left<<setw(wbin)<<Form("%.2f",mct_transfer_factors[ibin/2][0]);
    	for(size_t j(0);j<(nbg+1)*nbins/2 - (2+(nbg+1)*(ibin/2));j++) fcard<<left<<setw(wbin)<<"-";
    }
    //Uncorrelated BG systematics
    for (size_t ibin(0); ibin<nbins; ibin+=2){
      for(int k(1);k<=nbg;k++){
      fcard<<endl<<left<<setw(wname)<<Form("bkg_flat%i_proc%i lnN",static_cast<int>(ibin),k)<<setw(wdist)<<" ";
      
       for(size_t j(0);j<k+(nbg+1)*(ibin/2);j++) fcard<<left<<setw(wbin)<<"-";
       fcard<<left<<setw(wbin)<<Form("%.2f",sys_filler);
       for(size_t j(0);j<(nbg+1)*nbins/2 - (k+1+(nbg+1)*(ibin/2));j++) fcard<<left<<setw(wbin)<<"-";

      }
    }

    fcard<<endl<<endl;



    cout<<"Wrote headers"<<endl;
    fcard.close();

}
"""