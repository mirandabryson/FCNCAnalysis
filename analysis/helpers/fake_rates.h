namespace y2016{
# include "fr_values/2016_fake_rates.h"
}
namespace y2017{
# include "fr_values/2017_fake_rates.h"
}
namespace y2018{
# include "fr_values/2018_fake_rates.h"
}

float fakeRate(int year, int id, float pt, float eta) { 
    if (year == 2016) return y2016::fakeRate(id, pt, eta);
    else if (year == 2017) return y2017::fakeRate(id, pt, eta);
    else if (year == 2018) return y2018::fakeRate(id, pt, eta);
    else return 0.;
}


