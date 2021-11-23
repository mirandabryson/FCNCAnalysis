import numpy as np

import uproot3
import matplotlib.pyplot as plt
import mplhep as hep
plt.style.use(hep.style.CMS)

from yahist import Hist1D, Hist2D

# f_in = uproot3.open('/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/v6BabyPlots/fakes_mc_2018_hists.root')

# path = '/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/oct27_bdtScore/'
path = '/home/users/ksalyer/FCNCAnalysis/analysis/outputs/nov18_bdtYields/'
# path = '/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/oct28_BDTInputs/'
# sigpath = '/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/aug09_lead25_MET50_jet30_newTriggers_tt2or1l/'

regions =   [ #"mr",
             # "os",
             # "sf",
             # "df",
             # "mlsf",
             # "mldf",
             # "ss",
             # "ml",
             # "mlonz"
             "br",
             #"vrsr_ss",
             #"vrsr_ml",
             #"vrcr_sf",
             #"vrcr_df",
             #"vrcr_mlsf",
             #"vrcr_mldf",
             #"vrcr_flip",
             #"vrsr_flip"
            ]
variables = [   ["bdtScore_hct", 1, r'$HCT\ BDT\ score$'],
                ["bdtScore_hut", 1, r'$HUT\ BDT\ score$'],
                # ["bdtScoreOnZ_hct", 1, r'$HCT\ BDT\ score$'],
                # ["bdtScoreOnZ_hut", 1, r'$HUT\ BDT\ score$'],

                # #onZ
                # ["njOnZ", 1, r'$njets$'],
                # ["nbjOnZ", 1, r'$nbtags$'],
                # ["mOnZ", 1, r'$met$'],
                # ["zll", 1, r'$mll$'],
                
                #jets
                # ["njets", 1, r'$N_{jets}$'],
                # ["nbjets", 1, r'$N_{b-jets}$'],
                # ["fwjpt", 1, r'$Most Forward Jet p_{T}$'],
                
                # ["ljpt", 5, r'$p_T\ (lead.\ jet)\ (GeV)$'],
                # ["ljbscore", 1, r'$lead.\ jet\ b-score$'],
                
                # ["tjpt", 5, r'$p_T\ (sublead.\ jet)\ (GeV)$'],
                # ["tjbscore", 1, r'$sublead.\ jet\ b-score$'],
                
                # ["thirdjpt", 5, r'$p_T\ (subsublead.\ jet)\ (GeV)$'],
                # ["thirdjbscore", 1, r'$subsublead.\ jet\ b-score$'],

                # ["lbpt", 5, r'$p_T\ (lead.\ b-tag)\ (GeV)$'],
                # ["lbscore", 5, r'$lead.\ b-tag\ b-score$'],

                #Leptons
                # ["neles", 1, r'$N_{electrons}$'],
                # ["mll", 1, r'$m_{lead.\ lep,\ sublead.\ lep}$'],

                # ["llpt", 5, r'$p_T\ (lead.\ lep.)\ (GeV)$'],
                # # ["lleta", 1, r'$\eta\ (lead.\ lep.)$'],
                # ["lldxy", 4, r'$dxy\ (lead.\ lep.)$'],
                # ["lldz", 4, r'$dz\ (lead.\ lep.)$'],

                # ["ltpt", 5, r'$p_T\ (sublead.\ lep.)\ (GeV)$'],
                # # ["lteta", 4, r'$\eta\ (sublead.\ lep.)$'],
                # ["ltdxy", 4, r'$dxy\ (sublead.\ lep.)$'],
                # ["ltdz", 4, r'$dz\ (sublead.\ lep.)$'],

                # ["thirdlpt", 5, r'$p_T\ (subsublead.\ lep.)\ (GeV)$'],
                # # ["thirdleta", 4, r'$\eta\ (subsublead.\ lep.)$'],
                # ["thirdldxy", 4, r'$dxy\ (subsublead.\ lep.)$'],
                # ["thirdldz", 4, r'$dz\ (subsublead.\ lep.)$'],

                #Event kinematics
                # ['met', 1, r'$MET\ (GeV)$'],
                # ['ht', 1, r'$HT\ (GeV)$'],
                # ['mt_ll_met', 1, r'$m_{T}\ (lead.\ lep,\ MET)\ (GeV)$'],
                # ['mt_tl_met', 1, r'$m_{T}\ (sublead.\ lep,\ MET)\ (GeV)$'],
                # ['mt_thirdl_met', 1, r'$m_{T}\ (subsublead.\ lep,\ MET)\ (GeV)$'],
            ]

# years = ["2016","2017"]#,"2018"]
years = ["2016"]
blind = True


def get_yahist(hist, rebin=1, overflow=True, newEdges=[]):
    counts = hist.allvalues
    edges = hist.alledges
    w2 = hist.allvariances
    if newEdges: 
        edges = newEdges
        sliceCounts = counts[len(edges)-2:]
        counts = counts[:len(edges)-1]
        np.append(counts,sum(sliceCounts))
        neww2 = w2[:len(edges)-1]
        np.append(neww2,sum(counts[len(edges)-2:]))
        w2 = neww2
    # print (edges, len(edges))
    # print(counts, len(counts))
    if overflow:
        counts[1] += counts[0]
        counts[-2] += counts[-1]
        w2[1] += w2[1]
        w2[-2] += w2[-1]
        counts = np.array(counts[1:-1])
        edges = np.array(edges[1:-1])
        w2 = np.array(w2[1:-1])

    
    tmp_hist = Hist1D.from_bincounts(counts, edges, np.sqrt(w2), )
    if rebin!=1: tmp_hist = tmp_hist.rebin(rebin)
    return tmp_hist

def get_total(histos, keys):
    tmp = Hist1D.from_bincounts(np.zeros(len(histos[keys[0]].counts)), histos[keys[0]].edges, )
    for key in keys:
        tmp += histos[key]
    
    return tmp

def add_uncertainty(hist, ax, ratio=False, offset1 = 0.0, offset2 = 0.0):
    opts = {'step': 'post', 'label': 'Uncertainty', 'hatch': '///',
                    'facecolor': 'none', 'edgecolor': (0, 0, 0, .5), 'linewidth': 0, 'zorder':10.}
    error = np.sqrt(hist.errors**2+(offset1*hist.counts)**2+(offset2*hist.counts)**2)
    
    if ratio:
        down = np.nan_to_num(np.ones(len(hist.counts)) - error/hist.counts)
        up = np.nan_to_num(np.ones(len(hist.counts)) + error/hist.counts)
    else:
        down = hist.counts-error
        up = hist.counts+error
    ax.fill_between(x=hist.edges, y1=np.r_[down, down[-1]], y2=np.r_[up, up[-1]], **opts)


for y in years:
    for r in regions:
        for var in variables:
            v = var[0]
            if "bdtScore" in v: v+=y
            rebinVal = var[1]
            vname = var[2]
            histName = 'h_'+r+'_'+v+'_'+y
            print (histName)
            if r == 'os':
                hists = {
                    'fakes': uproot3.open(path+'fakes_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_fakes_mc'],
                    'top': uproot3.open(path+'top_'+y+'_hists.root')['h_'+r+'_'+v+'_top'],
                    'dy': uproot3.open(path+'dy_'+y+'_hists.root')['h_'+r+'_'+v+'_dy'],
                    'rares': uproot3.open(path+'os_rares_'+y+'_hists.root')['h_'+r+'_'+v+'_os_rares'],
                    'data': uproot3.open(path+'data_'+y+'_hists.root')['h_'+r+'_'+v+'_data'],
                    'tch': uproot3.open(path+'signal_tch_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tch'],
                    'tuh': uproot3.open(path+'signal_tuh_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tuh'],
                }
            elif r =='br':
                hists = {
                    # 'fakes': uproot3.open(path+'fakes_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_fakes_mc'],
                    # 'flips': uproot3.open(path+'flips_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_flips_mc'],
                    'sf': uproot3.open(path+'data_'+y+'_hists.root')['h_sfest_'+v+'_data'],
                    'mlsf': uproot3.open(path+'data_'+y+'_hists.root')['h_mlsfest_'+v+'_data'],
                    'df': uproot3.open(path+'data_'+y+'_hists.root')['h_dfest_'+v+'_data'],
                    'mldf': uproot3.open(path+'data_'+y+'_hists.root')['h_mldfest_'+v+'_data'],
                    'flips': uproot3.open(path+'data_'+y+'_hists.root')['h_osest_'+v+'_data'],
                    'rares': uproot3.open(path+'rares_'+y+'_hists.root')['h_'+r+'_'+v+'_rares'],
                    #'data': uproot3.open(path+'data_'+y+'_hists.root')['h_'+r+'_'+v+'_data'],
                    'tch': uproot3.open(path+'signal_tch_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tch'],
                    'tuh': uproot3.open(path+'signal_tuh_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tuh'],
                }
            else:
                hists = {
                    'fakes': uproot3.open(path+'fakes_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_fakes_mc'],
                    # 'flips': uproot3.open(path+'flips_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_flips_mc'],
                    # 'fakes': uproot3.open(path+'data_'+y+'_hists.root')['h_mlsfest_'+v+'_data'],
                    # 'flips': uproot3.open(path+'data_'+y+'_hists.root')['h_osest_'+v+'_data'],
                    'rares': uproot3.open(path+'rares_'+y+'_hists.root')['h_'+r+'_'+v+'_rares'],
                    'ttw': uproot3.open(path+'ttw_'+y+'_hists.root')['h_'+r+'_'+v+'_ttw'],
                    'ttz': uproot3.open(path+'ttz_'+y+'_hists.root')['h_'+r+'_'+v+'_ttz'],
                    'tzq': uproot3.open(path+'tzq_'+y+'_hists.root')['h_'+r+'_'+v+'_tzq'],
                    'wz': uproot3.open(path+'wz_'+y+'_hists.root')['h_'+r+'_'+v+'_wz'],
                    'zz': uproot3.open(path+'zz_'+y+'_hists.root')['h_'+r+'_'+v+'_zz'],
                    'data': uproot3.open(path+'data_'+y+'_hists.root')['h_'+r+'_'+v+'_data'],
                    'tch': uproot3.open(path+'signal_tch_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tch'],
                    'tuh': uproot3.open(path+'signal_tuh_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tuh'],
                }

            if 'njets' in v:
                my_histos = { x:get_yahist(hists[x], rebin=rebinVal, overflow=True, newEdges=[float('-inf'),-0.5,0.5,1.5,2.5,3.5,4.5,float('inf')]) for x in hists.keys() }
            elif 'nbjets' in v:
                my_histos = { x:get_yahist(hists[x], rebin=rebinVal, overflow=True, newEdges=[float('-inf'),-0.5,0.5,1.5,2.5,float('inf')]) for x in hists.keys() }
            else:
                my_histos = { x:get_yahist(hists[x], rebin=rebinVal, overflow=True) for x in hists.keys() }

            # flipDataSF = (sum(my_histos['data'].counts)-sum(my_histos['top'].counts))/(sum(my_histos['data_est'].counts))
            # print(flipDataSF)
            # my_histos['data_est'] *= flipDataSF
            # my_histos['dy'] *= flipDataSF
            if r == 'br':
                my_histos['fakes'] = my_histos['sf']+my_histos['mlsf']-my_histos['df']-my_histos['df']-my_histos['mldf']-my_histos['mldf']


            if r == 'os':
                my_histos['fakes'].label = 'Nonprompt'
                my_histos['fakes'].color = '#FF595E'

                # my_histos['tw'].label = 'tW'
                # my_histos['tw'].color = '#FF595E'

                my_histos['top'].label = 'tt2l'
                my_histos['top'].color = '#FFCA3A'

                my_histos['dy'].label = 'Drell Yan'
                my_histos['dy'].color = '#08BDBD'

                my_histos['rares'].label = 'Other'
                my_histos['rares'].color = '#8AC926'

                keys = ['rares', 'fakes', 'dy', 'top']
                # keys = ['rares', 'dy', 'fakes']

            else: 

                my_histos['fakes'].label = 'Nonprompt'
                my_histos['fakes'].color = '#FF595E'

                my_histos['flips'].label = 'Charge flip'
                my_histos['flips'].color = '#FFCA3A'

                my_histos['rares'].label = 'Other'
                my_histos['rares'].color = '#8AC926'

                # my_histos['ttz'].label = 'ttZ'
                # my_histos['ttz'].color = '#8AC926'

                # my_histos['ttw'].label = 'ttW'
                # my_histos['ttw'].color = '#FFCA3A'

                # my_histos['tzq'].label = 'tZq'
                # my_histos['tzq'].color = '#FF99C9'

                # my_histos['wz'].label = 'WZ'
                # my_histos['wz'].color = '#08BDBD'

                # my_histos['zz'].label = 'ZZ'
                # my_histos['zz'].color = '#F96E46'

                # my_histos['rares'].label = 'OtherRares'
                # my_histos['rares'].color = '#6987C9'

                # my_histos['top'].label = 'tt/tw/ttg'
                # my_histos['top'].color = '#FF595E'

                # my_histos['dy'].label = 'DY'
                # my_histos['dy'].color = '#FFCA3A'

                # my_histos['wboson'].label = 'wjets/wg'
                # my_histos['wboson'].color = '#8AC926'

                # my_histos['Higgs'].label = 'Higgs'
                # my_histos['Higgs'].color = '#FF99C9'

                # my_histos['xg'].label = r'$X +\gamma$'
                # my_histos['xg'].color = '#6987C9'

                # my_histos['ttxx'].label = 'ttXX'
                # my_histos['ttxx'].color = '#8AC926'

                # # my_histos['triboson'].label = 'VVV'
                # # my_histos['triboson'].color = '#FF99C9'

                # my_histos['ttx'].label = 'ttX'
                # my_histos['ttx'].color = '#FFCA3A'

                # my_histos['ttw'].label = 'ttW'
                # my_histos['ttw'].color = '#08BDBD'

                # my_histos['multiboson'].label = 'VV/VVV'
                # my_histos['multiboson'].color = '#FF595E'

                keys = ['flips', 'rares', 'fakes']
                # keys = [ 'rares','zz','wz','tzq','ttz', 'ttw','fakes']
                # keys = ['Higgs','xg', 'ttxx','ttx', 'ttw','multiboson']
                # keys = ['wboson','dy','top']
                # keys = ['dy', 'xg', 'wboson','top']

            signals = ['tch', 'tuh']

            total_mc = get_total(my_histos, keys)

            if not (blind and (r == 'ss' """or r == 'ml'""" or r == 'br')): 
                ratio = my_histos['data'].divide(total_mc, )
            #     # ratio_est = my_histos['data_est'].divide(total_mc, )
            #     # ratio_data = my_histos['data'].divide(my_histos['data_est'], )
            else:
                ratio_tch = my_histos['tch'].divide(total_mc, )
                ratio_tuh = my_histos['tuh'].divide(total_mc, )


            # f, ax = plt.subplots()

            fig, (ax, rax) = plt.subplots(2,1,figsize=(10,10), gridspec_kw={"height_ratios": (3, 1), "hspace": 0.05}, sharex=True)
            # fig, ax = plt.subplots(1,1,figsize=(10,10))

            if y == "2016": luminosity = 35.9
            if y == "2017": luminosity = 41.5
            if y == "2018": luminosity = 59.71
            hep.cms.label(
                "Preliminary",
                data=True,
                #year=2018,
                lumi=luminosity,
                loc=0,
                ax=ax,
            )

            hep.histplot(
                [ my_histos[x].counts for x in keys ],
                my_histos['fakes'].edges,
                w2=[ my_histos[x].errors for x in keys ],
                histtype="fill",
                stack=True,
                label=['%s (%.0f)'%(my_histos[x].label, sum(my_histos[x].counts)) for x in keys],
                # label=['%s'%(my_histos[x].label) for x in keys],
                color=[ my_histos[x].color for x in keys ],
                ax=ax)

            if not (blind and (r == 'ss' """or r == 'ml'""" or r == 'br')):
                hep.histplot(
                    my_histos['data'].counts,
                    my_histos['data'].edges,
                    yerr=my_histos['data'].errors,
                    histtype="errorbar",
                    stack=False,
                    label='%s (%.0f)'%('Observation', sum(my_histos['data'].counts)),
                    # label='%s'%('Observation'),
                    color='black',
                    ax=ax)

                # hep.histplot(
                #     my_histos['data_est'].counts,
                #     my_histos['data_est'].edges,
                #     yerr=my_histos['data_est'].errors,
                #     histtype="errorbar",
                #     stack=False,
                #     label='%s (%.0f)'%('Data (est)', sum(my_histos['data_est'].counts)),
                #     color='grey',
                #     ax=ax)

            hep.histplot(
                [my_histos['tch'].counts/100, my_histos['tuh'].counts/100],
                my_histos['tch'].edges,
                w2=[my_histos['tch'].errors/100, my_histos['tuh'].errors/100],
                histtype="step",
                stack=False,
                label=[r'$B(t\to Hc)=0.01$', r'$B(t\to Hu)=0.01$'],
                color=['#525B76','#6A4C93'],
                ax=ax)

            if not (blind and (r == 'ss' """or r == 'ml'""" or r == 'br')):
                print(ratio.counts)
                hep.histplot(
                    ratio.counts,
                    ratio.edges,
                    yerr=my_histos['data'].errors/total_mc.counts,
                    histtype="errorbar",
                    color='black',
                    ax=rax)

            #     # hep.histplot(
            #     #     ratio_est.counts,
            #     #     ratio_est.edges,
            #     #     yerr=my_histos['data_est'].errors/total_mc.counts,
            #     #     histtype="errorbar",
            #     #     color='grey',
            #     #     ax=rax)

            #     # hep.histplot(
            #     #     ratio_data.counts,
            #     #     ratio_data.edges,
            #     #     yerr=my_histos['data'].errors/my_histos['data_est'].counts,
            #     #     histtype="errorbar",
            #     #     color='black',
            #     #     ax=rax)
            # else:
            #     hep.histplot(
            #         [ratio_tch.counts/100, ratio_tuh.counts/100],
            #         ratio_tch.edges,
            #         w2=[ratio_tch.errors/100, ratio_tuh.errors/100],
            #         histtype="errorbar",
            #         color=['#525B76','#6A4C93'],
            #         ax=rax)


            rax.set_ylim(0,1.99)
            # #rax.set_xlabel(r'$p_T\ (lead.\ lep.)\ (GeV)$')
            rax.set_xlabel(vname)
            # if not (blind and (r == 'ss' or r == 'ml' or r == 'br')): rax.set_ylabel(r'Data/Sim.')
            if not (blind and (r == 'ss' """or r == 'ml'""" or r == 'br') or r == 'os'): rax.set_ylabel(r'Obs./Pred.')
            else: rax.set_ylabel(r'Sig./Back.')
            ax.set_ylabel(r'Events')
            ax.set_yscale('log')
            # ax.set_ylim(0.1,1e7)
            # ax.set_xlabel(vname)
            # ax.set_yscale('linear')
            ax.set_ylim(0.1, 10000)

            add_uncertainty(total_mc, rax, ratio=True)
            add_uncertainty(total_mc, ax, offset1= 0.0)

            ax.legend()

            #plt.show()

            fig.savefig('/home/users/ksalyer/public_html/FCNC_plots/'+histName+'.png')
            fig.savefig('/home/users/ksalyer/public_html/FCNC_plots/'+histName+'.pdf')
            #plt.close()
