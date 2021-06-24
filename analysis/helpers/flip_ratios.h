#include <vector>
#include <map>

using namespace std;

double GetFlipRatio( int pt_bin, int eta_bin ){
  map< double, std::vector<double> > flip_ratio_map;
  
  flip_ratio_map[40]  = {0.0000098685, 0.0000432454, 0.000334417}  ;
  flip_ratio_map[60]  = {0.00000785161, 0.0000605905, 0.000427148} ;
  flip_ratio_map[80]  = {0.000010967, 0.0000873633, 0.00063545}    ;
  flip_ratio_map[100] = {0.00000532932, 0.00010933, 0.000726637}   ;
  flip_ratio_map[200] = {0.0000300963, 0.000146605, 0.00118509}    ;
  flip_ratio_map[300] = {0.000076572, 0.000227187, 0.00201814}     ;
  
  double flip_ratios = flip_ratio_map[pt_bin][eta_bin];
  
  return flip_ratios;
  
}
