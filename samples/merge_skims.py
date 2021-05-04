import os
import time
import argparse
from samples_2016 import samples_2016
from samples_2017 import samples_2017
from samples_2018 import samples_2018
from samples import get_sample_path

samples = { 2016 : samples_2016, 2017 : samples_2017, 2018 : samples_2018}

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--out", help="output directory", default="")
    parser.add_argument("-t", "--tag", help="tag for bookkeeping and output directory location", default="fcnc_v3")
    parser.add_argument("-y", "--year", help="year, if you only want to run one", default="")
    parser.add_argument(      "--proc", help="process, if you only want to run one/some. accepts wildcards if quoted.", default="", type=str)
    parser.add_argument(      "--excludeproc", help="opposite of proc", default="", type=str)
    parser.add_argument(      "--skip_already_done", help="skip procs if already in limits folder", action="store_true")
    parser.add_argument(      "--slim", help="smaller subset of processes", action="store_true")
    parser.add_argument(      "--ncpu", help="number of cpus", default=25, type=int)
    parser.add_argument(      "--maxprocs", help="maximum number of chains", default=-1, type=int)
    parser.add_argument("-n", "--dryrun", help="dont actually merge", action="store_true")
    parser.add_argument("-v", "--verbosity", help="verbosity level (0 = default,1,2)", default=0, type=int)

    args = parser.parse_args()
    tag = args.tag
    years = [2016,2017,2018]
    if args.year != "": years = [int(x.strip()) for x in args.year.strip().split()]
    dryrun=False
    if args.dryrun: dryrun=True

    basedirs = {
        2016: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/{}/".format(tag),
        2017: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/{}/".format(tag),
        2018: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/{}/".format(tag),
    }
    outdir = basedirs[2016]
    if args.out != "": outdir = args.out
    procs = [x.strip() for x in args.proc.strip().split()]
    exprocs = [x.strip() for x in args.excludeproc.strip().split()]

    count=0
    for year in years:
        for sname, lname in samples_2016.items():
            if len(procs) and sname not in procs: continue
            if sname in exprocs: continue
            ifnames = []
            ifpath = basedirs[year]+get_sample_path(sname,year,args.tag)
            for f in os.listdir(ifpath):
                if f.endswith('.root'): ifnames.append(f)
            ofpath = outdir+'/{}/{}/'.format(tag,year)
            if not os.path.isdir(ofpath):
                os.system('mkdir -p {}'.format(ofpath))
            ofname = ofpath+'%s.root' % (sname)
            ifnames_long = [ifpath + f for f in ifnames]
            command='hadd -fk %s %s' % (ofname, ' '.join(ifnames_long))
            if args.verbosity: print command
            count += 1
            if not dryrun:
                os.nice(4)
                os.system(command)
                if count%5==0: time.sleep(60)
