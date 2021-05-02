import os
import time
import argparse
from samples_2016 import samples_2016
from samples_2017 import samples_2017
from samples_2018 import samples_2018

samples = { 2016 : samples_2016, 2017 : samples_2017, 2018 : samples_2018}

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--out", help="output directory", default="/nfs-7/userdata/fgolf/")
    parser.add_argument("-t", "--tag", help="tag for bookkeeping and output directory location", default="v3.08_allyears_tmp")
    parser.add_argument("-y", "--year", help="year, if you only want to run one", default="")
    parser.add_argument(      "--proc", help="process, if you only want to run one/some. accepts wildcards if quoted.", default="", type=str)
    parser.add_argument(      "--excludeproc", help="opposite of proc", default="", type=str)
    parser.add_argument(      "--skip_already_done", help="skip procs if already in limits folder", action="store_true")
    parser.add_argument(      "--slim", help="smaller subset of processes", action="store_true")
    parser.add_argument(      "--ncpu", help="number of cpus", default=25, type=int)
    parser.add_argument(      "--maxprocs", help="maximum number of chains", default=-1, type=int)
    parser.add_argument("-n", "--noloop", help="skip looping/scanchain", action="store_true")
    parser.add_argument("-v", "--verbosity", help="verbosity level (0 = default,1,2)", default=0, type=int)

    args = parser.parse_args()
    print type(args)
    print args

    basedirs = {
        2016: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v3/",
        2017: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v3/",
        2018: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v3/",
    }
    outdir = basedirs[2016]

    count=0
    for year in [2016,2017,2018]:
        for sname, lname in samples_2016.items():
            ifnames = []
            fpath = basedirs[2016] + lname + "/"
            for f in os.listdir(fpath):
                if f.endswith('.root'): ifnames.append(f)
            ofname = basedirs[2016] + lname + "merged/%s.root" % (sname)
            ifnames_long = [fpath + f for f in ifnames]
            command='hadd -f %s %s' % (ofname, ' '.join(ifnames_long))
            print command
            count += 1
            if not test:
                os.system(command)
                if count%5==0: time.sleep(60)