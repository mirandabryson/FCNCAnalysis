from samples_2016 import samples_2016
from samples_2017 import samples_2017
from samples_2018 import samples_2018

def get_sample_path(sample,year):
    year=int(year)
    if year==2016: 
        if sample in samples_2016: return samples_2016[sample]
        else: print("ERROR: Sample %s does not exist in year %d." % (sample,year))
    else if year==2017: 
        if sample in samples_2016: return samples_2016[sample]
        else: print("ERROR: Sample %s does not exist in year %d." % (sample,year))
    else if year==2018: 
        if sample in samples_2016: return samples_2016[sample]
        else: print("ERROR: Sample %s does not exist in year %d." % (sample,year))
    else: print("ERRROR: No samples for year ", year)
