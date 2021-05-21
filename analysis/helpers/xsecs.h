double getXSec( string sampleName ){

    map< string, double > xsecs;

    xsecs["tw_dilep"] = 0.01123;
    xsecs["ttjets"] = 831.762;
    xsecs["tg"] = 2.967;
    xsecs["wg"] = 405.271;
    xsecs["wjets"] = 61334.9;
    xsecs["wwg"] = 0.2147;
    xsecs["ww"] = 0.16975;
    xsecs["www"] = 0.2086;
    xsecs["wwz"] = 0.1651;
    xsecs["wzg"] = 0.04123;
    xsecs["wz"] = 4.4297;
    xsecs["wzz"] = 0.05565;
    xsecs["qqww"] = 0.05390;
    xsecs["zg"] = 405.271;
    xsecs["zz"] = 1.256;
    xsecs["zzz"] = 0.01398;
    xsecs["ggh"] = 0.01181;
    xsecs["ttg_dilep"] = 0.632;
    xsecs["ttg_1lep"] = 0.77;
    xsecs["tthh"] = 0.000757;
    xsecs["tttj"] = 0.000474;
    xsecs["tttt"] = 0.01197;
    xsecs["tttw"] = 0.000788;
    xsecs["ttwh"] = 0.001582;
    xsecs["ttw"] = 0.2043;
    xsecs["ttww"] = 0.01150;
    xsecs["ttwz"] = 0.003884;
    xsecs["ttzh"] = 0.001535;
    xsecs["ttz_m10"] = 0.2529;
    xsecs["ttz_m1-10"] = 0.0493;
    xsecs["ttzz"] = 0.001982;
    xsecs["dyjets_m10-50"] = 18610;
    xsecs["dyjet_m50"] = 6020.85;
    xsecs["vh_nobb"] = 2.1360;
    xsecs["tzq"] = 0.0758;
    xsecs["tth_nobb"] = 0.2710;
    xsecs["signal_hct_atop"] = 83.88144;
    xsecs["signal_hut_atop"] = 83.88144;
    xsecs["signal_hct_top"] = 83.88144;
    xsecs["signal_hut_top"] = 83.88144;

    double xsecForWeight = xsecs[sampleName];

    return xsecForWeight;
}
