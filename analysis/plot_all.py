from tqdm import tqdm
import json
import os
import numpy as np
import itertools
import uproot
import re

from utils.plotting_utils import write_table

import sys
sys.path.insert(0,'/home/users/{}/.local/lib/python2.7/site-packages/'.format(os.getenv("USER")))
sys.path.append('/home/users/fgolf/fcnc/current/matplottery/')
from matplottery.plotter import plot_stack
from matplottery.utils import Hist1D, MET_LATEX, binomial_obs_z

def remove(rs1,rs2):
    return list(set(rs1)-set(rs2))

#regions = ("br","ml","ss")
regions = ("br","ml","ss")
labels = {}
labels["fcnc"] = {
        "sr"         : ["br", "SR"],
        "ht"         : [regions, r"$H_\mathrm{T}$ (GeV)"],
        "njets"      : [regions, r"$N_\mathrm{jets}$"],
        "met"        : [regions, r"$p_\mathrm{T}^{\mathrm{miss}}$ (GeV)"],
        "mll"        : [regions, r"$m_{ll}$"],
        "nbjets"     : [regions, r"$N_\mathrm{b}$"],
        "nleps"      : [regions, r"$N_\mathrm{leps}$"],
        "llpt"       : [regions, r"ordered $p_{T}$(lep1)"],
        "ltpt"       : [regions, r"ordered $p_{T}$(lep2)"],
        "lleta"      : [regions, r"ordered $\eta$(lep1)"],
        "lteta"      : [regions, r"ordered $\eta$(lep2)"],
        "ljpt"       : [regions, r"ordered $p_{T}$(jet1)"],
        "lbpt"       : [regions, r"ordered $p_{T}$(bjet1)"],
}

do_paper_plots_only = False
if do_paper_plots_only:
    labels["ft"] = {
            "ht"              : [("ttzcr","ttwcr","sr"),r"$H_\mathrm{T}$ (GeV)"],
            "met"             : [("ttzcr","ttwcr","sr"), r"$p_\mathrm{T}^{\mathrm{miss}}$ (GeV)"],
            "njets"           : [("ttzcr","ttwcr","sr"), r"$N_\mathrm{jets}$"],
            "nbtags"          : [("ttzcr","ttwcr","sr"),r"$N_\mathrm{b}$"],
            }
    labels["ss"] = {
            # "TOTAL"      : [("SRHH","SRHL","SRLL","SRML","SRLM"), "Region"],
            "ht"         : [("br",), r"$H_\mathrm{T}$ (GeV)"],
            "met"        : [("br",), r"$p_\mathrm{T}^{\mathrm{miss}}$ (GeV)"],
            "mtmin"      : [("br",), r"$m_\mathrm{T}^\mathrm{min}$ (GeV)"],
            "njets"      : [("br",), r"$N_\mathrm{jets}$"],
            "nbtags"     : [("br",), r"$N_\mathrm{b}$"],
            "charge"     : [("br",), r"SS charge"],
        }

d_label_colors = {}
d_label_colors["fcnc"] = {
#        "fakes" : (r"Nonprompt lep.", [0.85, 0.85, 0.85]),
         "fakes_mc" : (r"MC fakes", [0.85, 0.85, 0.85]),
#        "flips" : (r"Charge misid.", [0.4, 0.4, 0.4]),
         "flips_mc" : (r"Charge misid.", [0.4, 0.4, 0.4]),
         "rares" : (r"Rare", [1.0, 0.4, 1.0]),
#        "tth"   : (r"$t\bar{t}H$", [0.4, 0.4, 0.6]),
#        "ttvv"  : (r"$t\bar{t}VV$" , [0.4, 0.6, 1.0]),
#        "ttw"   : (r"$t\bar{t}W$", [0.0, 0.4, 0.0]),
#        "ttz"   : (r"$t\bar{t}Z$", [0.4, 0.8, 0.4]),
#        "xg"    : (r"$X\gamma$" , [0.4, 0.0, 0.8]),
        }

d_flat_systematics = { }
#d_flat_systematics["ft"] = {
#        "fakes": 0.3,
#        "flips": 0.2,
#        "rares": 0.2,
#        "ttw": 0.4,
#        "ttz": 0.4,
#        "tth": 0.25,
#        "ttvv": 0.11,
#        "xg": 0.11,
#        }
d_flat_systematics["fcnc"] = {
        "fakes": 0.40,
        "flips": 0.2,
        "fakes_mc": 0.40,
        "flips_mc": 0.2,
        "rares": 0.5,
        "ww": 0.3,
        "ttw": 0.3,
        "ttz": 0.3,
        "wz": 0.3,
        "tth": 0.3,
        "xg": 0.5,
        }
# "fakes/ttZ/ttH (30%); flips/WW (20%); WZ/ttW (13%); Xg/Rares (50%)"

# from ../limits/test/crfit/
# after doing testcrbins.py to reduce bins (3 bins from crwsplit)
# and run_all_limits.sh with extra containing --unblinded

# d_crpostfitsf = {'fakes': 1.1948199139074693,
#         'flips': 1.020599049200507,
#         'rares': 1.1224350665249947,
#         'total': 1.2794573639702325,
#         'total_background': 1.3056080457107933,
#         'total_signal': 0.0,
#         'tth': 1.155083830402133,
#         'tttt': 0.0,
#         'ttvv': 1.0550142330872638,
#         'ttw': 1.4807971683302559,
#         'ttz': 1.3958306982737914,
#         'xg': 1.0842022472153388}
# d_crpostfitsf_errs = {'fakes': 0.5330058353969307,
#         'flips': 0.14395684087751284,
#         'rares': 0.3343497393873837,
#         'total': 0.14901268940160062,
#         'total_background': 0.1538191984828496,
#         'total_signal': 0.0,
#         'tth': 0.30185266795309806,
#         'tttt': 0.0,
#         'ttvv': 0.28627852193747866,
#         'ttw': 0.28537781734630363,
#         'ttz': 0.2800949349793666,
#         'xg': 0.3090238224979612}

#d_crpostfitsf = {'fakes': 1.133,
# 'flips': 1.001,
# 'rares': 1.02,
# 'total': 1.2039836025074864,
# 'total_background': 1.2254378772947825,
# 'total_signal': 1.076,
# 'tth': 1.094,
# 'tttt': 1.076,
# 'ttvv': 1.014,
# 'ttw': 1.31,
# 'ttz': 1.266,
# 'xg': 1.017}
#d_crpostfitsf_errs = {'fakes': 0.6836929317614069,
# 'flips': 0.5375067661493199,
# 'rares': 0.2513117714751323,
# 'total': 0.18140301518082388,
# 'total_background': 0.18528878200425344,
# 'total_signal': 0.0,
# 'tth': 0.31260232283875494,
# 'tttt': 0.0,
# 'ttvv': 0.1789620767510818,
# 'ttw': 0.5355134476152815,
# 'ttz': 0.348624399392768,
# 'xg': 0.2526828586109242}

# yuck, gotta make these global for multiprocessing since uproot file objects can't be pickled
files = {}
signames_ = []

def worker(info):
    global files, signames_

    analysis, outputdir, year, lumi, (var, (regions, xlabel)) = info

    sigstrs = [r"fcnc"]

    fnames = []
    for region in regions:

        title = region.upper()
        lumi_ = str(lumi)

        if analysis == "fcnc":
            if title in ["br"]:
                title = "Baseline"
            if title in ["ml","ss"] and (var == "TOTAL"):
                title = title.replace("sr","")

        region_for_hist = region[:]
        if region == "brpostfit":
            region_for_hist = "br"
            def get_sf(proc):
                return d_crpostfitsf.get(proc,1.0)
            bgs = [
                    sum(
                        get_sf(proc)*Hist1D(files[y][proc]["h_{}_{}_{}".format(region_for_hist,var,proc)],
                            label="{} ($\\times${:.2f})".format(label,get_sf(proc)),
                            color=color,
                            dummy=proc,
                            ) for y in files.keys())
                        for proc,(label,color) in d_label_colors[analysis].items()
                        ]
        else:
            bgs = [
                    sum(Hist1D(files[y][proc]["h_{}_{}_{}".format(region_for_hist,var,proc)],label=label,color=color,dummy=proc) for y in files.keys())
                    for proc,(label,color) in d_label_colors[analysis].items()
                    ]

#        data = sum([Hist1D(files[y]["data"]["h_{}_{}_data".format(region_for_hist,var)]) for y in files.keys()])
        # sigcolors = ["red","#5863F8","#FCCA46","#04A777","#944BBB","#233D4D"]
        sigcolors = [[0.75,0.15,0.22],"#5863F8","#FCCA46","#04A777","#944BBB","#233D4D"]
        # print sigcolors
        if region == "brpostfit":
            region_for_hist = "br"
            def get_sf(proc):
                return d_crpostfitsf.get(proc,1.0)
            sigs = [
                    sum(
                        get_sf(signame)*Hist1D(files[y][signame]["h_{}_{}_{}".format(region_for_hist,var,signame)],
                            label="{} ($\\times${:.2f})".format(sigstr,get_sf(signame)),
                            color=sigcolors[isig],
                            dummy=signame,
                            ) for y in files.keys())
                        for isig,(signame,sigstr) in enumerate(zip(signames_,sigstrs))
                        ]
        else:
            sigs = [
                    sum([Hist1D(files[y][signame]["h_{}_{}_{}".format(region_for_hist,var,signame)],color=sigcolors[isig]) for y in files.keys()])
                    for isig,signame in enumerate(signames_)
                    ]
            for isig,sigstr in enumerate(sigstrs):
                sigs[isig].set_attr("label", sigstr)
                if signames_[isig] != "tttt":
                    sigs[isig] *= 10.

        bgs = sorted(bgs, key=lambda bg: bg.get_integral())
        for bg in bgs:
            print type(bg), bg
            # add flat systematic to stat unc in quadrature
            bg._errors = np.hypot(bg._counts*d_flat_systematics[analysis].get(bg.get_attr("dummy"),0.),bg._errors)

#        if analysis == "ss" and region in ["SRML","ml","mlonz","mloffz"]:
#            # remove flips and ww since they are 0 for multilepton regions
#            new_bgs = [bg for bg in bgs if (bg.get_attr("dummy") not in ["flips","ww"])]
#            bgs = new_bgs

#        data.set_attr("label", "Data [{}]".format(int(data.get_integral())))

        # if data.get_integral() < 1e-6: return
        if abs(sum(bgs).get_integral()) < 1e-6: continue

        ax_main_callback = None
        ax_ratio_callback = None
        mpl_legend_params = {}
        ratio_range = [0.,3.]
        xticks = []
        mpl_xtick_params = {}

        # # FIXME FIXME FIXME
        # if analysis == "ss" and year != 2016 and not unblindall:
        #     data._counts *= 0.
        #     data._errors *= 0.
        #     data.set_attr("label", "Data (blind)")

        # # FIXME FIXME FIXME
        # data._counts *= 0.
        # data._errors *= 0.
        # data.set_attr("label", "Data")

        if region in ["ml","ss"] and (var == "TOTAL"):
            ratio_range = [0.,3.]
            mpl_legend_params["fontsize"] = 8
            mpl_legend_params["framealpha"] = 0.4
            mpl_legend_params["ncol"] = 2
            mpl_legend_params["labelspacing"] = 0.12

#            data.poissonify()

            # sbgs = sum(bgs)
            # pulls = binomial_obs_z(data.counts,sbgs.counts,sbgs.errors)
            # mu_pulls = pulls.mean()
            # sig_pulls = pulls.std()

            # if year != 2016 and not unblindall:
            #     data._counts *= 0.
            #     data._errors *= 0.
            #     data.set_attr("label", "Data (blind)")

            def ax_main_callback(ax):
                ax.set_ylim([0.05,ax.get_ylim()[1]*2.0])
                ax.set_yscale("log", nonposy='clip'),

            if region in ["ml","ss"]:
                xticks = range(1,70)
                # def ax_ratio_callback(ax):
                #     ax.text(0.18, -0.6,r"pulls $\mu,\sigma$ = {:.2f},{:.2f}".format(mu_pulls,sig_pulls), color="red", ha="center", va="center", fontsize=10.0, transform = ax.transAxes)
            # if region in ["SRML"]:
            #     def ax_ratio_callback(ax):
            #         ax.text(0.4, -0.6,"off-Z", color="blue", ha="center", va="center", fontsize=10.0, wrap=True, transform = ax.transAxes)
            #         ax.text(0.55, -0.6,"on-Z", color="blue", ha="center", va="center", fontsize=10.0, wrap=True, transform = ax.transAxes)
            #         ax.axvline(x=21.5, color="blue", lw=1.0)
            #         ax.text(0.18, -0.6,"pulls $\mu,\sigma$ = {:.2f},{:.2f}$".format(mu_pulls,sig_pulls), color="red", ha="center", va="center", fontsize=10.0, transform = ax.transAxes)

        elif region.lower() in ["br"]:
            # blind all 2018 and all BDT plots since we will retrain
            # if year == 2018 or (len(files.keys()) > 1) or region.lower in ["srdisc"]:
            #     data._counts *= 0.
            #     data._errors *= 0.
            #     data.set_attr("label", "Data (blind)")
#            data.convert_to_poisson_errors()
            if var.lower() in ["sr"]:
                xticks = range(1,20)
            if region.lower() in ["srdisc"]:
                # def ax_main_callback(ax):
                #     ax.set_ylim([0.1,ax.get_ylim()[1]*1.5])
                #     ax.set_yscale("log", nonposy='clip'),
                xticks = ["CRZ"]+range(1,25)

        if (region.lower() in ["srcr"]) and (var.lower() in ["total"]):
            # if not (unblindall or year == 2016):
            # if year == 2018:
            #     data._counts[2:] *= 0.
            #     data._errors[2:] *= 0.
#            data.set_attr("label", "Data [{}]".format(int(data.get_integral())))
            def ax_main_callback(ax):
                ax.set_ylim([0.1,ax.get_ylim()[1]*1.5])
                ax.set_yscale("log", nonposy='clip'),
            xticks = ["CRZ","CRW"]+range(1,20)
#        if (var.lower() in ["disc"]) and (region.lower() not in ["ttwcr","ttzcr"]):
            # # if not (unblindall or year == 2016):
            # if year == 2018:
            #     data._counts[-10:] *= 0.
            #     data._errors[-10:] *= 0.
#            data.set_attr("label", "Data [{}]".format(int(data.get_integral())))

        if (var.lower() in ["charge","el_charge","mu_charge","q3"]):
            xticks = ["$(-)$","$(+)$",""]
            mpl_xtick_params = dict(rotation=0, fontsize=14)

        # specific plots tuned by hand
        if analysis == "ss":
            if region.lower() == "br":
                if var.lower() == "charge":
                    def ax_main_callback(ax):
                        ax.set_xlim([-1,2.6])
                    def ax_ratio_callback(ax):
                        ax.set_xlim([-1,2.6])

        if len(files.keys()) > 1:
            fname = "{}/run2_{}_{}.pdf".format(outputdir,region,var)
        else:
            fname = "{}/y{}_{}_{}.pdf".format(outputdir,files.keys()[0],region,var)
        fnames.append(fname)

        ylabel="Events"
        #binwidth = data.get_bin_widths()[0]
        binwidth = 1
        if var in ["ht","met","njets","nbtags"]:
            if var in ["ht","met"]:
                ylabel = "Events / {} GeV".format(int(binwidth))
            mpl_legend_params["fontsize"] = 12

            if var in ["njets","nbtags"] and region in ["ttwcr","ttzcr"]:
#                data.poissonify()
                ratio_range = [0.,2.]

            if var in ["njets","nbtags"] and region in ["sr"]:
                ratio_range = [0.,2.]

            # mpl_legend_params["framealpha"] = 0.4
            # mpl_legend_params["ncol"] = 1
            # mpl_legend_params["labelspacing"] = 0.10

        if analysis == "ss":

                if var in ["ht","met","mtmin"] and region in ["br"]:
#                    data.poissonify()
                    mpl_legend_params["fontsize"] = 12
                    ratio_range = [0.,2.]
                    ylabel = "Events / {} GeV".format(int(binwidth))

                if var in ["njets","nbtags"] and region in ["br"]:
                    data.poissonify()
                    mpl_legend_params["fontsize"] = 12
                    ratio_range = [0.,3.]

                if var in ["charge"] and region in ["br"]:
                    data.poissonify()
                    mpl_legend_params["fontsize"] = 12
                    ratio_range = [0.,2.]


        for do_log in [False,True]:
            fname_tmp = str(fname)
            if do_log:
                fname_tmp = fname.replace(".pdf","_log.pdf").replace(".png","_log.png")
#            plot_stack(bgs=bgs, data=data, title=title, xlabel=xlabel, ylabel=ylabel, filename=fname_tmp,
            plot_stack(bgs=bgs, data=bgs[0], title=title, xlabel=xlabel, ylabel=ylabel, filename=fname_tmp,
                       # cms_type = "Preliminary",
                       cms_type = "",
                       lumi = lumi_,
                       ratio_range=ratio_range,
                       sigs=sigs,
                       do_log=do_log,
                       mpl_xtick_params=mpl_xtick_params,
                       mpl_ratio_params={
                           "label":"Data/Pred.",
                           },
                       xticks=xticks,
                       mpl_sig_params={
                           # "hist":False,
                           },
                       ax_main_callback=ax_main_callback,
                       mpl_legend_params=mpl_legend_params,
                       ax_ratio_callback=ax_ratio_callback,
                       do_bkg_syst=True,
                       )

        if (region in ["br","brpostfit","ttwcr","ttzcr"]):
            fname_tmp = fname.replace(".pdf","_stacked.pdf").replace(".png","_stacked.png")
            plot_stack(bgs=bgs+sigs, data=data, title=title, xlabel=xlabel, ylabel=ylabel, filename=fname_tmp,
                       # cms_type = "Preliminary",
                       cms_type = "",
                       lumi = lumi_,
                       ratio_range=ratio_range,
                       # sigs=sigs,
                       do_log=False,
                       mpl_xtick_params=mpl_xtick_params,
                       mpl_ratio_params={
                           "label":"Data/Pred.",
                           },
                       xticks=xticks,
                       mpl_sig_params={
                           # "hist":False,
                           },
                       ax_main_callback=ax_main_callback,
                       mpl_legend_params=mpl_legend_params,
                       ax_ratio_callback=ax_ratio_callback,
                       do_bkg_syst=True,
                       )

        # os.system("ic {}".format(fname))

        # print bgs
        # print data
        # return

        table_info = write_table(bgs[0],bgs,signal=(None if not sigs else sigs[0]),outname=fname.replace(".pdf",".txt"))
        #table_info = write_table(data,bgs,signal=(None if not sigs else sigs[0]),outname=fname.replace(".pdf",".txt"))
        # table_info = write_table(data,bgs,signal=sig,outname=fname.replace(".pdf",".txt"),
        #         binlabels=xticks,signame=sigstrs[0].replace(r"$\times 10$","x10").replace(","," "),csv=True)
    return ", ".join(fnames)

def make_plots(outputdir="plots", inputdir="outputs", year=2017, lumi="41.5", other_years=[], regions=[], signames="signal_hut", doss=False, show_mcfakes=False):
    global files, signames_, other_files
    signames_ = [signames]

    os.system("mkdir -p {}/".format(outputdir))

    analysis = "fcnc"

    if show_mcfakes and ("fakes" in d_label_colors[analysis]):
        del d_label_colors[analysis]["fakes"]
        d_label_colors[analysis]["fakes_mc"] = (r"MC fakes", [0.85, 0.85, 0.85])

    files = {}
    for y in [year]+other_years:
        files[y] = { }
        #for proc in d_label_colors[analysis].keys()+["data"]+signames_:
        for proc in d_label_colors[analysis].keys()+signames_:
            # try:
            ystr = str(y)
            # if any(x in proc for x in ["fs_","rpv_"]): ystr = "2016"
            files[y][proc] = uproot.open("{}/{}_{}_hists.root".format(inputdir,proc,ystr))
            # except IOError:
            #     print("{}/output_{}_{}.root doesn't exist, but ignoring because it's probably signal".format(inputdir,y,proc))

    infos = [[analysis,outputdir,year,lumi,x] for x in labels[analysis].items()]

    # print infos

    # # Smarter. Run the first couple without thread pool so that it doesn't obscure errors when crashing
    # # Then run rest in parallel
    # # wtf. Can't do this because of https://github.com/uqfoundation/pathos/issues/153
    # map(worker,infos[:2])
    # os.nice(10)
    # from multiprocessing import Pool as ThreadPool
    # pool = ThreadPool(15)
    # for res in pool.imap_unordered(worker,infos[1:]):
    #     if res:
    #         print "Wrote {}".format(res)

    # map(worker,infos)

    # Don't be nice for plots since I need them *now*
    # os.nice(4)
    from multiprocessing import Pool as ThreadPool
    #pool = ThreadPool(15)
    pool = ThreadPool(1)
    # print infos
    for res in pool.imap_unordered(worker,infos):
        if res:
            print "Wrote {}".format(res)



if __name__ == "__main__":

    # 131.5

    make_plots(
            outputdir="plots_temp",
            inputdir="outputs",
            year=2018,
            lumi="124.0", # 2016+2017+2018 --> 35.87+41.53+46.57 = 124.0
            other_years = [2016,2017],
            signames = "ttw",
            )
