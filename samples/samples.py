from samples_2016 import samples_2016
from samples_2017 import samples_2017
from samples_2018 import samples_2018

def get_sample_path(sample,year,tag):
    year=int(year)
    if year==2016: 
        if sample in samples_2016: return '{}_{}'.format(samples_2016[sample],tag)
        else: print("ERROR: Sample %s does not exist in year %d." % (sample,year))
    elif year==2017: 
        if sample in samples_2017: return '{}_{}'.format(samples_2017[sample],tag)
        else: print("ERROR: Sample %s does not exist in year %d." % (sample,year))
    elif year==2018: 
        if sample in samples_2018: return '{}_{}'.format(samples_2018[sample],tag)
        else: print("ERROR: Sample %s does not exist in year %d." % (sample,year))
    else: print("ERRROR: No samples for year ", year)
