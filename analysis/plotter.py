import numpy as np

import uproot3
import matplotlib.pyplot as plt
import mplhep as hep
plt.style.use(hep.style.CMS)

from yahist import Hist1D, Hist2D

f_in = uproot3.open('/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/v6BabyPlots/fakes_mc_2018_hists.root')

path = '/home/users/ksalyer/FranksFCNC/ana/analysis/outputs/aug02_flavChannel_jet40/'

regions =   [#"mr",
             "os"
             # "sf",
             # "df",
             # "mlsf",
             # "mldf",
             # "ss",
             # "ml",
             #"vrsr_ss",
             #"vrsr_ml",
             #"vrcr_sf",
             #"vrcr_df",
             #"vrcr_mlsf",
             #"vrcr_mldf",
             #"vrcr_flip",
             #"vrsr_flip"
            ]
variables = [   #["njets", 1, r'$N_{jets}$'],
                # ["nbjets", 1, r'$N_{b-jets}$'],
                # ["nleps", 1, r'$N_{leptons}$'],
                # ["neles", 1, r'$N_{electrons}$'],
                # ["nmus", 1, r'$N_{muons}$'],
                # ["ljpt", 5, r'$p_T\ (lead.\ jet)\ (GeV)$'],
                # ["tjpt", 5, r'$p_T\ (sublead.\ jet)\ (GeV)$'],
                # ["llpt", 5, r'$p_T\ (lead.\ lep.)\ (GeV)$'],
                # ["ltpt", 5, r'$p_T\ (sublead.\ lep.)\ (GeV)$'],
                # ["mll", 4, r'$m_{ll}\ (GeV)$'],
                # ['flipSF_inclMET_mee', 1, r'$m_{ee}\ (GeV)$'],
                # ['flipSF_l50MET_mee', 1, r'$m_{ee}\ (GeV)$'],
                # ['flipSF_inclMET_njets', 1, r'$N_{jets}$'],
                # ['flipSF_l50MET_njets', 1, r'$N_{jets}$'],
                # ['flipSF_inclMET_nbjets', 1, r'$N_{b-jets}$'],
                # ['flipSF_l50MET_nbjets', 1, r'$N_{b-jets}$'],
                # #["lleta", 4],
                # #["lteta", 4],
                # ["llminiiso", 1, r'$miniIso\ (lead.\ lep.)\ (GeV)$'],
                # ["ltminiiso", 1, r'$miniIso\ (sublead.\ lep.)\ (GeV)$'],
                # ['met', 1, r'$MET\ (GeV)$'],
                ['flavorChannel', 1, r'$Flavor\ Channel$'],
                # ['flipSFcr_inclMET', 1, r'$sr bin$'],
                # ['flipSFcr_l50MET', 1, r'$sr bin$'],
                # #['vrsr', 1, r'$VRSR$'],
                # #['vrcr', 1, r'$VRCR$']
                # #['vrcr', 1, r'$VRCR$']
            ]
years = ["2016","2017","2018"]
# years = ["2016"]
blind = True


def get_yahist(hist, rebin=1, overflow=True):
    counts = hist.allvalues
    edges = hist.alledges
    w2 = hist.allvariances
    if overflow:
        counts[1] += counts[0]
        counts[-2] += counts[-1]
        w2[1] += w2[1]
        w2[-2] += w2[-1]
        counts = np.array(counts[1:-1])
        edges = np.array(edges[1:-1])
        w2 = np.array(w2[1:-1])
    
    tmp_hist = Hist1D.from_bincounts(counts, edges, np.sqrt(w2), )
    tmp_hist = tmp_hist.rebin(rebin)
    return tmp_hist

def get_total(histos, keys):
    tmp = Hist1D.from_bincounts(np.zeros(len(histos[keys[0]].counts)), histos[keys[0]].edges, )
    for key in keys:
        tmp += histos[key]
    
    return tmp

def add_uncertainty(hist, ax, ratio=False):
    opts = {'step': 'post', 'label': 'Uncertainty', 'hatch': '///',
                    'facecolor': 'none', 'edgecolor': (0, 0, 0, .5), 'linewidth': 0, 'zorder':10.}
    
    if ratio:
        down = np.ones(len(hist.counts)) - hist.errors/hist.counts
        up = np.ones(len(hist.counts)) + hist.errors/hist.counts
    else:
        down = hist.counts-hist.errors
        up = hist.counts+hist.errors
    ax.fill_between(x=hist.edges, y1=np.r_[down, down[-1]], y2=np.r_[up, up[-1]], **opts)


for y in years:
    for r in regions:
        for var in variables:
            v = var[0]
            rebinVal = var[1]
            vname = var[2]
            histName = 'h_'+r+'_'+v+'_'+y
            print (histName)
            if blind and (r == 'ss' or r == 'ml' or r == 'mr'):
                hists = {
                    # 'top': uproot3.open(path+'top_'+y+'_hists.root')['h_'+r+'_'+v+'_top'],
                    # 'dy': uproot3.open(path+'dy_'+y+'_hists.root')['h_'+r+'_'+v+'_dy'],
                    'fakes': uproot3.open(path+'fakes_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_fakes_mc'],
                    'flips': uproot3.open(path+'flips_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_flips_mc'],
                    'rares': uproot3.open(path+'rares_'+y+'_hists.root')['h_'+r+'_'+v+'_rares'],
                    'tch': uproot3.open(path+'signal_tch_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tch'],
                    'tuh': uproot3.open(path+'signal_tuh_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tuh'],
                }
            elif r == 'os':
                hists = {
                    'fakes': uproot3.open(path+'fakes_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_fakes_mc'],
                    #'flips': uproot3.open(path+'flips_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_flips_mc'],
                    'top': uproot3.open(path+'top_'+y+'_hists.root')['h_'+r+'_'+v+'_top'],
                    # 'tw': uproot3.open(path+'tw_'+y+'_hists.root')['h_'+r+'_'+v+'_tw'],
                    # 'top': uproot3.open(path+'tw_'+y+'_hists.root')['h_'+r+'_'+v+'_tw'],
                    'dy': uproot3.open(path+'dy_'+y+'_hists.root')['h_'+r+'_'+v+'_dy'],
                    'rares': uproot3.open(path+'os_rares_'+y+'_hists.root')['h_'+r+'_'+v+'_os_rares'],
                    'data': uproot3.open(path+'data_'+y+'_hists.root')['h_'+r+'_'+v+'_data'],
                    'tch': uproot3.open(path+'signal_tch_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tch'],
                    'tuh': uproot3.open(path+'signal_tuh_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tuh'],
                }
            else:
                hists = {
                    'top': uproot3.open(path+'top_'+y+'_hists.root')['h_'+r+'_'+v+'_top'],
                    'dy': uproot3.open(path+'dy_'+y+'_hists.root')['h_'+r+'_'+v+'_dy'],
                    'wboson': uproot3.open(path+'wboson_'+y+'_hists.root')['h_'+r+'_'+v+'_wboson'],
                    'xg': uproot3.open(path+'xg_'+y+'_hists.root')['h_'+r+'_'+v+'_xg'],
                    # 'diboson': uproot3.open(path+'diboson_'+y+'_hists.root')['h_'+r+'_'+v+'_diboson'],
                    # 'fakes': uproot3.open(path+'fakes_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_fakes_mc'],
                    # 'flips': uproot3.open(path+'flips_mc_'+y+'_hists.root')['h_'+r+'_'+v+'_flips_mc'],
                    'rares': uproot3.open(path+'rares_'+y+'_hists.root')['h_'+r+'_'+v+'_rares'],
                    'data': uproot3.open(path+'data_'+y+'_hists.root')['h_'+r+'_'+v+'_data'],
                    # 'data_est': uproot3.open(path+'data_'+y+'_hists.root')['h_osest_'+v+'_data'],
                    'tch': uproot3.open(path+'signal_tch_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tch'],
                    'tuh': uproot3.open(path+'signal_tuh_'+y+'_hists.root')['h_'+r+'_'+v+'_signal_tuh'],
                }


            my_histos = { x:get_yahist(hists[x], rebin=rebinVal, overflow=True) for x in hists.keys() }

            # flipDataSF = (sum(my_histos['data'].counts)-sum(my_histos['top'].counts))/(sum(my_histos['data_est'].counts))
            # print(flipDataSF)
            # my_histos['data_est'] *= flipDataSF
            # my_histos['dy'] *= flipDataSF


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

                # my_histos['fakes'].label = 'Nonprompt'
                # my_histos['fakes'].color = '#FF595E'

                # my_histos['flips'].label = 'Charge flip'
                # my_histos['flips'].color = '#FFCA3A'

                my_histos['rares'].label = 'Other'
                my_histos['rares'].color = '#8AC926'

                my_histos['top'].label = 'ttbar and tW'
                my_histos['top'].color = '#FFCA3A'

                my_histos['dy'].label = 'Drell Yan'
                my_histos['dy'].color = '#08BDBD'

                my_histos['wboson'].label = 'W+jets and WW'
                my_histos['wboson'].color = '#FF595E'

                my_histos['xg'].label = 'x + gamma'
                my_histos['xg'].color = '#586BA4'

                # my_histos['diboson'].label = 'WW/WZG'
                # my_histos['diboson'].color = '#FF595E'

                # keys = ['rares', 'flips', 'fakes']
                keys = ['dy', 'xg','rares', 'wboson','top']
                # keys = ['dy', 'xg', 'wboson','top']

            signals = ['tch', 'tuh']

            total_mc = get_total(my_histos, keys)

            if not (blind and (r == 'ss' or r == 'ml' or r == 'mr')): 
                ratio = my_histos['data'].divide(total_mc, )
                # ratio_est = my_histos['data_est'].divide(total_mc, )
                # ratio_data = my_histos['data'].divide(my_histos['data_est'], )
            else:
                ratio_tch = my_histos['tch'].divide(total_mc, )
                ratio_tuh = my_histos['tuh'].divide(total_mc, )


            #f, ax = plt.subplots()

            fig, (ax, rax) = plt.subplots(2,1,figsize=(10,10), gridspec_kw={"height_ratios": (3, 1), "hspace": 0.05}, sharex=True)

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
                my_histos['top'].edges,
                w2=[ my_histos[x].errors for x in keys ],
                histtype="fill",
                stack=True,
                label=['%s (%.0f)'%(my_histos[x].label, sum(my_histos[x].counts)) for x in keys],
                color=[ my_histos[x].color for x in keys ],
                ax=ax)

            if not (blind and (r == 'ss' or r == 'ml' or r == 'mr')):
                hep.histplot(
                    my_histos['data'].counts,
                    my_histos['data'].edges,
                    yerr=my_histos['data'].errors,
                    histtype="errorbar",
                    stack=False,
                    label='%s (%.0f)'%('Observation', sum(my_histos['data'].counts)),
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

            if not (blind and (r == 'ss' or r == 'ml' or r == 'mr')):
                hep.histplot(
                    ratio.counts,
                    ratio.edges,
                    yerr=my_histos['data'].errors/total_mc.counts,
                    histtype="errorbar",
                    color='black',
                    ax=rax)

                # hep.histplot(
                #     ratio_est.counts,
                #     ratio_est.edges,
                #     yerr=my_histos['data_est'].errors/total_mc.counts,
                #     histtype="errorbar",
                #     color='grey',
                #     ax=rax)

                # hep.histplot(
                #     ratio_data.counts,
                #     ratio_data.edges,
                #     yerr=my_histos['data'].errors/my_histos['data_est'].counts,
                #     histtype="errorbar",
                #     color='black',
                #     ax=rax)
            else:
                hep.histplot(
                    [ratio_tch.counts/100, ratio_tuh.counts/100],
                    ratio_tch.edges,
                    w2=[ratio_tch.errors/100, ratio_tuh.errors/100],
                    histtype="errorbar",
                    color=['#525B76','#6A4C93'],
                    ax=rax)


            rax.set_ylim(0,1.99)
            #rax.set_xlabel(r'$p_T\ (lead.\ lep.)\ (GeV)$')
            rax.set_xlabel(vname)
            if not (blind and (r == 'ss' or r == 'ml' or r == 'mr')): rax.set_ylabel(r'Data/Sim.')
            # if not (blind and (r == 'ss' or r == 'ml' or r == 'mr') or r == 'os'): rax.set_ylabel(r'Obs./Pred.')
            else: rax.set_ylabel(r'Sig./Back.')
            ax.set_ylabel(r'Events')
            ax.set_yscale('log')
            ax.set_ylim(0.1,1e7)
            # ax.set_yscale('linear')
            # ax.set_ylim(0,200000)

            add_uncertainty(total_mc, rax, ratio=True)
            add_uncertainty(total_mc, ax)

            ax.legend()

            #plt.show()

            fig.savefig('/home/users/ksalyer/public_html/dump/FCNC_plots/'+histName+'.png')
            fig.savefig('/home/users/ksalyer/public_html/dump/FCNC_plots/'+histName+'.pdf')
            #plt.close()
