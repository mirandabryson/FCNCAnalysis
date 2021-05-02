import os
import sys
import time
from samples_2016 import samples_2016
from samples_2017 import samples_2017
from samples_2018 import samples_2018

samples = { 2016 : samples_2016, 2017 : samples_2017, 2018 : samples_2018}

if __name__ == '__main__':
    basedirs = {
        2016: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v3/",
        2017: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v3/",
        2018: "/hadoop/cms/store/user/ksalyer/FCNC_NanoSkim/fcnc_v3/",
    }
    outdir = basedirs[2016]
    if len(sys.argv[1]) > 1: outdir = sys.argv[1]

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
            #os.system(command)
            count += 1
            #if count%5==0: time.sleep(60)