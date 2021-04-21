#include <iostream>
#include "./flip_ratios.h"

double GetFlipWeight(int lepton_pt, int lepton_eta, int lepton_pdgid){
  double flip_weight;
  int pt_bin;
  int eta_bin;
  
  if (abs(lepton_pdgid) != 11){
    flip_weight = 1;
  }
  else if (abs(lepton_pdgid == 11){
    
    if (lepton_pt < 15){
      flip_weight = 1;
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }
    }
    
    else if (lepton_pt < 40){
      pt_bin = 0;
      if (abs(lepton_eta) < 0.8){
        eta_bin = 0;
      }
    
      else if (abs(lepton_eta) < 1.479){
        eta_bin = 1;
      }
    
      else if (abs(lepton_eta) < 2.4){
        eta_bin = 2;
      }
      
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }

    }
    
    else if (lepton_pt < 60){
      pt_bin = 1;
      if (abs(lepton_eta) < 0.8){
        eta_bin = 0;
      }
    
      else if (abs(lepton_eta) < 1.479){
        eta_bin = 1;
      }
    
      else if (abs(lepton_eta) < 2.4){
        eta_bin = 2;
      }
      
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }

    }
    
    else if (lepton_pt < 80){
      pt_bin = 2;
      if (abs(lepton_eta) < 0.8){
        eta_bin = 0;
      }
    
      else if (abs(lepton_eta) < 1.479){
        eta_bin = 1;
      }
    
      else if (abs(lepton_eta) < 2.4){
        eta_bin = 2;
      }
      
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }
    }
    
    else if (lepton_pt < 100){
      pt_bin = 3;
      if (abs(lepton_eta) < 0.8){
        eta_bin = 0;
      }
    
      else if (abs(lepton_eta) < 1.479){
        eta_bin = 1;
      }
    
      else if (abs(lepton_eta) < 2.4){
        eta_bin = 2;
      }
      
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }

    }
    
    else if (lepton_pt < 200){
      pt_bin = 4;
      if (abs(lepton_eta) < 0.8){
        eta_bin = 0;
      }
    
      else if (abs(lepton_eta) < 1.479){
        eta_bin = 1;
      }
    
      else if (abs(lepton_eta) < 2.4){
        eta_bin = 2;
      }
      
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }

    }
    
    else if (lepton_pt >= 200){
      pt_bin = 5;
      if (abs(lepton_eta) < 0.8){
        eta_bin = 0;
      }
    
      else if (abs(lepton_eta) < 1.479){
        eta_bin = 1;
      }
    
      else if (abs(lepton_eta) < 2.4){
        eta_bin = 2;
      }
      
      else (abs(lepton_eta) >= 2.4){
       return 1;
       cout << "flip_weight.h warning: electron does not meet object definitions." << endl; 
      }

    }
             
   flip_weight = GetFlipRatio(pt_bin, eta_bin);   
  }
    

return flip_weight;
  }
