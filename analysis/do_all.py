import os
import sys
import  time
sys.path.append(os.getcwd()+'../')

#proc_to_samples = {
#    'fakes_mc' : ['ttjets','wjets_ht100-200','wjets_ht200-400','wjets_ht400-600','wjets_ht600-800','wjets_ht800-1200'],
#    'flips_mc' : ['ttjets','dyjets_m10-50','dyjets_m50','ww'],
#    'rares_mc'
#}

procs = ['fakes_mc','flips_mc','rares']
years = [2016,2017,2018]

for year in years:
    for proc in procs:
        command='python py_doAll.py --proc {} -y {}'.format(proc,year)
        print command
        os.nice(5)
        os.system(command)
        time.sleep(120)


